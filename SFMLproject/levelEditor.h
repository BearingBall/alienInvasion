#pragma once

#include <functional>
#include <SFML/Graphics.hpp>

#include "camera.h"
#include "level.h"
#include "levelDrawer.h"
#include "scene.h"
#include "textObject.h"
#include "classSaver.h"
#include "resourceFileNaming.h"

class LevelEditor final : public Scene
{
private:
	wallType currentType = wallType::wall;
	size_t levelNumber;
	
	sf::Font font;
	Level level;
	Camera camera;

	void setTexts(sf::RenderWindow& window)
	{
		ButtonFabric fabric(font);
		std::function<void(Object&)> nothing([](Object& object) {});
		std::function<void(Object&)> ChangeColor([](Object& object) {object.ChangeColour(sf::Color::Red); });
		std::function<void(Object&)> backToMenu([&window,this]( Object& object)
		{
			ClassSaver<Level>::save(levelNumber, level);
			EventOperator::instance()->push(Event::changingScene);
			EventOperator::instance()->putSceneToSwap(std::make_shared<MainMenu>(window));
		});

		std::function<void(Object&)> clearLevel([&window, this](Object& object)
		{
			level.getWalls().clear();
		});

		objects.push_back(fabric.createClickableButton(std::string("Level ") + std::to_string(levelNumber), 50,
				Vector2(50, 50),
				nothing, nothing));

		objects.push_back(fabric.createClickableButton(std::string("Save"), 50,
				Vector2(window.getSize().x - 200, 50),
				ChangeColor, backToMenu));

		objects.push_back(fabric.createClickableButton(std::string("Clear"), 50,
			Vector2(window.getSize().x - 200, 110),
			ChangeColor, clearLevel));
	}


	std::string tokenToString(wallType token)
	{
		if (currentType == wallType::wall)
		{
			return std::string( "Wall");
		}
		if (currentType == wallType::spawnPoint)
		{
			return std::string("SpawnPoint");
		}
		if (currentType == wallType::doorIn)
		{
			return std::string("DoorIn");
		}
		if (currentType == wallType::doorOut)
		{
			return std::string("DoorOut");
		}
	}

	void setCurrentTypeLabel()
	{
		ButtonFabric fabric(font);
		std::function<void(Object&)> nothing([](Object& object) {});
		
		objects.push_back(fabric.createClickableButton(tokenToString(currentType), 50,
				Vector2(50, 150),
				nothing, nothing));
	}

	bool differentClickLBM = true;
	bool differentClickQ = true;


	void buttonOperator(sf::RenderWindow& window, Vector2 mouse)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (!differentClickLBM)
			{
				std::string tmp;
				bool possibleToAdd = true;
				if (currentType == wallType::wall)
				{
					tmp = ResourceFileNaming::wallName;
				}
				if (currentType == wallType::spawnPoint)
				{
					tmp = ResourceFileNaming::spawnPointName;
				}
				if (currentType == wallType::doorIn)
				{
					tmp = ResourceFileNaming::doorInName;
					std::for_each(level.getWalls().begin(), level.getWalls().end(), [&possibleToAdd](const Wall& object) { if (object.type == wallType::doorIn) possibleToAdd = false; });
				}
				if (currentType == wallType::doorOut)
				{
					tmp = ResourceFileNaming::ResourceFileNaming::doorOutName;
					std::for_each(level.getWalls().begin(), level.getWalls().end(), [&possibleToAdd](const Wall& object) { if (object.type == wallType::doorOut) possibleToAdd = false; });
				}

				if (possibleToAdd)
					level.addWall(tmp, mouse, camera.getCoordinate(), currentType);

				std::for_each(objects.begin(), objects.end(),
					[&window, &mouse](std::shared_ptr<Object>& object) { object->onMousePressed(mouse); });
			}
		}
		else
		{
			differentClickLBM = false;
		}


		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			std::vector<Wall>::iterator tmp = std::find_if(level.getWalls().begin(), level.getWalls().end(), [&mouse](const Wall& object) { return object.model.ifOnMouseOver(mouse); });
			if (tmp != level.getWalls().end())
			{
				level.getWalls().erase(tmp);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			camera.stepLeft(1);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			camera.stepRigth(1);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			camera.stepUp(1);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			camera.stepDown(1);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			if (!differentClickQ)
			{
				if (currentType == wallType::wall)
				{
					currentType = wallType::spawnPoint;
				}
				else
					if (currentType == wallType::spawnPoint)
					{
						currentType = wallType::doorIn;
					}
					else
						if (currentType == wallType::doorIn)
						{
							currentType = wallType::doorOut;
						}
						else
							if (currentType == wallType::doorOut)
							{
								currentType = wallType::wall;
							}
			}
			differentClickQ = true;
		}
		else differentClickQ = false;
	}
	
public:
	LevelEditor(sf::RenderWindow &window, size_t _levelNumber):levelNumber(_levelNumber),level({2000,2000})
	{
		ClassSaver<Level>::download(levelNumber, level);
		font.loadFromFile(ResourceFileNaming::fontName);
		camera.getSpeed() = 1;
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

	buttonOperator(window, mouse);
	setCurrentTypeLabel();
	
	std::for_each(objects.begin(), objects.end(),
		[&window](std::shared_ptr<Object>& object) { object->draw(window); });
	
	objects.clear();

}
