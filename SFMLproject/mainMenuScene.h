#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>



#include "buttonFabric.h"
#include "event.h"
#include "object.h"
#include "pictureObject.h"
#include "scene.h"
#include "textObject.h"

class MainMenu final : public Scene
{
private:
	std::string backgroundName = "../ResourceFile/background.png";
	std::string fontName = "../ResourceFile/Konstanting.ttf";
	sf::Font font;
	std::function<void(sf::RenderWindow&)> setCurrentMenuMorph;

	
	void initializeBackground(sf::RenderWindow &window)
	{
		PictureObject* background = new PictureObject(backgroundName);
		background->texture.setSmooth(true);
		background->texture.setRepeated(true);
		background->refreshSprite(sf::IntRect(0, 0, window.getSize().x, window.getSize().x));
		objects.push_back(std::shared_ptr<PictureObject>(background));
	}

	void initializeFont()
	{
		font.loadFromFile(fontName);
	}

	void createMenuMorph1(sf::RenderWindow &window)
	{
		std::function<void(Object&)> nothing([](Object& object) {});
		std::function<void(Object&)> ChangeColor([](Object& object) {object.ChangeColour(sf::Color::Red); });
		std::function<void(Object&)> Exit([&window](Object& object) { EventOperator::instance()->push(Event::eventExit);});

		std::function<void(Object&)> setMorph2([this](Object& object)
		{
			setCurrentMenuMorph = 
				std::function<void(sf::RenderWindow&)>([this](sf::RenderWindow& window) {createMenuMorph2(window); });
		});

		std::function<void(Object&)> setMorph3([this](Object& object)
		{
			setCurrentMenuMorph =
				std::function<void(sf::RenderWindow&)>([this](sf::RenderWindow& window) {createMenuMorph3(window); });
		});
		
		ButtonFabric fabric(font);
	
		objects.push_back(std::shared_ptr<TextObject>
			(fabric.createClickableButton(std::string("NewGame"),100, 
				Vector2(window.getSize().x / 2 - 150, window.getSize().y / 2 - 400), 
				ChangeColor, nothing)));

		objects.push_back(std::shared_ptr<TextObject>
			(fabric.createClickableButton(std::string("Setting"), 100,
				Vector2(window.getSize().x / 2 - 150, window.getSize().y / 2 - 250),
				ChangeColor, setMorph2)));

		objects.push_back(std::shared_ptr<TextObject>
			(fabric.createClickableButton(std::string("LevelEditor"), 100,
				Vector2(window.getSize().x / 2 - 150, window.getSize().y / 2 - 100),
				ChangeColor, setMorph3)));
		
		objects.push_back(std::shared_ptr<TextObject>
			(fabric.createClickableButton(std::string("Exit"), 100,
				Vector2(window.getSize().x / 2 - 150, window.getSize().y / 2 + 50),
				ChangeColor, Exit)));
	}

	void createMenuMorph2(sf::RenderWindow &window)
	{
		std::function<void(Object&)> nothing([](Object& object) {});
		std::function<void(Object&)> ChangeColor([](Object& object) {object.ChangeColour(sf::Color::Red); });
		std::function<void(Object&)> setMorph1([this](Object& object)
		{
			setCurrentMenuMorph =
				std::function<void(sf::RenderWindow&)>([this](sf::RenderWindow& window) {createMenuMorph1(window); });
		});
		std::function<void(Object&)> SetResolution800x600([&window](Object& object) {window.setSize(sf::Vector2u(800, 600)); window.setPosition(sf::Vector2i(0,0)); });
		std::function<void(Object&)> SetResolution1400x900([&window](Object& object) {window.setSize(sf::Vector2u(1400, 900));  window.setPosition(sf::Vector2i(0, 0)); });
		std::function<void(Object&)> SetResolution1920x1080([&window](Object& object) {window.setSize(sf::Vector2u(1920, 1080));  window.setPosition(sf::Vector2i(0, 0)); });

		ButtonFabric fabric(font);
		
		objects.push_back(std::shared_ptr<TextObject>
			(fabric.createClickableButton(std::string("Back"), 50,
				Vector2(window.getSize().x / 6, window.getSize().y / 6 * 5),
				ChangeColor, setMorph1)));

		objects.push_back(std::shared_ptr<TextObject>
			(fabric.createClickableButton(std::string("Resolution"), 50,
				Vector2(window.getSize().x / 6, window.getSize().y / 6),
				nothing, nothing)));

		objects.push_back(std::shared_ptr<TextObject>
			(fabric.createClickableButton(std::string("800x600"), 50,
				Vector2(window.getSize().x / 6 * 1, window.getSize().y / 4),
				ChangeColor, SetResolution800x600)));

		objects.push_back(std::shared_ptr<TextObject>
			(fabric.createClickableButton(std::string("1400x900"), 50,
				Vector2(window.getSize().x / 6 * 2, window.getSize().y / 4),
				ChangeColor, SetResolution1400x900)));

		objects.push_back(std::shared_ptr<TextObject>
			(fabric.createClickableButton(std::string("1920x1080"), 50,
				Vector2(window.getSize().x / 6 * 3, window.getSize().y / 4),
				ChangeColor, SetResolution1920x1080)));
	}

	void createMenuMorph3(sf::RenderWindow &window);
	
public:
	MainMenu(sf::RenderWindow &window)
	{
		initializeFont();
		setCurrentMenuMorph = std::function<void(sf::RenderWindow&)>([this](sf::RenderWindow& window) {createMenuMorph1(window); });
	}
	
	~MainMenu() = default;

	void render(sf::RenderWindow &window) override
	{
		initializeBackground(window);
		setCurrentMenuMorph(window);
		Vector2 mouse(sf::Mouse::getPosition().x - window.getPosition().x, sf::Mouse::getPosition().y - window.getPosition().y - windowBorderSize);
		std::for_each(objects.begin(), objects.end(),
			[&window, &mouse](std::shared_ptr<Object>& object) { object->onMouseOver(mouse); });

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			std::for_each(objects.begin(), objects.end(),
				[&window, &mouse](std::shared_ptr<Object>& object) { object->onMousePressed(mouse); });
		}
		
		std::for_each(objects.begin(), objects.end(),
			[&window](std::shared_ptr<Object>& object) { object->draw(window); });

		objects.clear();
	}
};

#include "levelEditor.h"

inline void MainMenu::createMenuMorph3(sf::RenderWindow& window)
{
	std::function<void(Object&)> setMorph1([this](Object& object)
	{
		setCurrentMenuMorph =
			std::function<void(sf::RenderWindow&)>([this](sf::RenderWindow& window) {createMenuMorph1(window); });
	});
	std::function<void(Object&)> ChangeColor([](Object& object) {object.ChangeColour(sf::Color::Red); });

	ButtonFabric fabric(font);

	for (size_t i = 0; i < 12; ++i)
	{
		std::function<void(Object&)> openEditor([&window, i](Object& object)
		{
			EventOperator::instance()->push(Event::changingScene);
			EventOperator::instance()->sceneToSwap = std::make_shared<LevelEditor>(window, i);
		});


		objects.push_back(std::shared_ptr<TextObject>
			(fabric.createClickableButton(std::string("Level ") + std::to_string(i), 50,
				Vector2(window.getSize().x / 6 * ((i % 4) + 1), window.getSize().y / 6 * ((static_cast<int>(i / 4) + 1))),
				ChangeColor, openEditor)));

	}

	objects.push_back(std::shared_ptr<TextObject>
		(fabric.createClickableButton(std::string("Back"), 50,
			Vector2(window.getSize().x / 6, window.getSize().y / 6 * 5),
			ChangeColor, setMorph1)));
}
