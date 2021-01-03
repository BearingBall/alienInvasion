#pragma once

#include <functional>
#include <SFML/Graphics.hpp>



#include "camera.h"
#include "level.h"
#include "levelDrawer.h"
#include "scene.h"
#include "textObject.h"

class LevelEditor final : public Scene
{
private:
	size_t levelNumber;
	std::string fontName = "../ResourceFile/Konstanting.ttf";
	std::string groundName = "../ResourceFile/ground.png";
	std::string wallName = "../ResourceFile/wall.png";
	sf::Font font;
	Level level;
	Camera camera;
	

	void setTexts(sf::RenderWindow& window)
	{
		ButtonFabric fabric(font);
		std::function<void(Object&)> nothing([](Object& object) {});
		std::function<void(Object&)> ChangeColor([](Object& object) {object.ChangeColour(sf::Color::Red); });
		std::function<void(Object&)> backToMenu([&window](Object& object)
		{
			EventOperator::instance()->push(Event::changingScene);
			EventOperator::instance()->sceneToSwap = std::make_shared<MainMenu>(window);
		});

		objects.push_back(std::shared_ptr<TextObject>
			(fabric.createClickableButton(std::string("Level ") + std::to_string(levelNumber), 50,
				Vector2(50, 50),
				nothing, nothing)));

		objects.push_back(std::shared_ptr<TextObject>
			(fabric.createClickableButton(std::string("Save"), 50,
				Vector2(window.getSize().x - 200, 50),
				ChangeColor, backToMenu)));

	}
		
public:
	LevelEditor(sf::RenderWindow &window, size_t _levelNumber):levelNumber(_levelNumber),level(groundName,{300,300})
	{
		font.loadFromFile(fontName);
		camera.speed = 1;
	}
	
	void render(sf::RenderWindow &window) override;
	
	~LevelEditor() = default;
};

#include "mainMenuScene.h"

inline void LevelEditor::render(sf::RenderWindow& window)
{
	setTexts(window);
	Vector2 mouse(sf::Mouse::getPosition().x - window.getPosition().x, sf::Mouse::getPosition().y - window.getPosition().y - windowBorderSize);
	LevelDrawer::draw(window, level, camera);
	
	std::for_each(objects.begin(), objects.end(),
		[&window, &mouse](std::shared_ptr<Object>& object) { object->onMouseOver(mouse); });

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		std::for_each(objects.begin(), objects.end(),
			[&window, &mouse](std::shared_ptr<Object>& object) { object->onMousePressed(mouse); });

		level.addWall(wallName, mouse,camera.coordinate);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		camera.stepLeft();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		camera.stepRigth();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		camera.stepUp();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		camera.stepDown();
	}
	
	std::for_each(objects.begin(), objects.end(),
		[&window](std::shared_ptr<Object>& object) { object->draw(window); });


	//std::cout <<  << "\n";
	
	objects.clear();

}
