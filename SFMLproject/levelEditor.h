#pragma once

#include <functional>
#include <SFML/Graphics.hpp>



#include "camera.h"
#include "level.h"
#include "levelDrawer.h"
#include "scene.h"
#include "textObject.h"
#include "classSaver.h"

class LevelEditor final : public Scene
{
private:
	wallType currentType = wallType::wall;
	size_t levelNumber;
	std::string fontName = "../ResourceFile/Konstanting.ttf";
	std::string groundName = "../ResourceFile/ground.png";
	std::string wallName = "../ResourceFile/wall.png";
	std::string spawnPointName = "../ResourceFile/spawnPoint.png";
	std::string doorInName = "../ResourceFile/doorIn.png";
	std::string doorOutName = "../ResourceFile/doorOut.png";
	
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

	void setCurrentTypeLabel()
	{
		ButtonFabric fabric(font);
		std::function<void(Object&)> nothing([](Object& object) {});
		std::string name;
		if (currentType == wallType::wall)
		{
			name = "Wall";
		}
		if (currentType == wallType::spawnPoint)
		{
			name = "SpawnPoint";
		}
		if (currentType == wallType::doorIn)
		{
			name = "DoorIn";
		}
		if (currentType == wallType::doorOut)
		{
			name = "DoorOut";
		}
		objects.push_back(std::shared_ptr<TextObject>
			(fabric.createClickableButton(name, 50,
				Vector2(50, 150),
				nothing, nothing)));
	}

	bool differentClickLBM = true;
	bool differentClickQ = true;
public:
	LevelEditor(sf::RenderWindow &window, size_t _levelNumber):levelNumber(_levelNumber),level(groundName,{2000,2000})
	{
		ClassSaver<Level>::download(levelNumber, level);
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
		if (!differentClickLBM)
		{
			std::for_each(objects.begin(), objects.end(),
				[&window, &mouse](std::shared_ptr<Object>& object) { object->onMousePressed(mouse); });


			std::string tmp;
			bool possibleToAdd = true;
			if (currentType == wallType::wall)
			{
				tmp = wallName;
			}
			if (currentType == wallType::spawnPoint)
			{
				tmp = spawnPointName;
			}
			if (currentType == wallType::doorIn)
			{
				tmp = doorInName;
				std::for_each(level.walls.begin(), level.walls.end(), [&possibleToAdd](const Wall& object) { if (object.type == wallType::doorIn) possibleToAdd = false; });
			}
			if (currentType == wallType::doorOut)
			{
				tmp = doorOutName;
				std::for_each(level.walls.begin(), level.walls.end(), [&possibleToAdd](const Wall& object) { if (object.type == wallType::doorOut) possibleToAdd = false; });
			}
			
			if (possibleToAdd)
			level.addWall(tmp, mouse, camera.coordinate, currentType);
		}
	}
	else
	{
		differentClickLBM = false;
	}


	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		std::vector<Wall>::iterator tmp = std::find_if(level.walls.begin(), level.walls.end(), [&mouse](const Wall& object) { return object.model.ifOnMouseOver(mouse); });
		if (tmp != level.walls.end())
		{
			level.walls.erase(tmp);
		}
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

	setCurrentTypeLabel();
	
	std::for_each(objects.begin(), objects.end(),
		[&window](std::shared_ptr<Object>& object) { object->draw(window); });
	
	objects.clear();

}
