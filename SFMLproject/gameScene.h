#pragma once
#include "creatureDrawer.h"
#include "scene.h"
#include "creatureLevelBoxing.h"
#define _USE_MATH_DEFINES
#include  <math.h>

class GameScene final:public Scene
{
private:
	size_t levelNumber;
	Level level;
	Camera camera;
	Creature player;
	size_t wallSize = 100;
	float cameraSpeed = 0.001;

	void buttonOperator(sf::RenderWindow& window, Vector2 mouse)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player.stepLeft(1);
			if (!CreatureLevelBoxing::isPossibleToMove(player.getCoordinate(), level, player.modelBound()))
			{
				player.stepRigth(1);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player.stepRigth(1);
			if (!CreatureLevelBoxing::isPossibleToMove(player.getCoordinate(), level,player.modelBound()))
			{
				player.stepLeft(1);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			player.stepUp(1);
			if (!CreatureLevelBoxing::isPossibleToMove(player.getCoordinate(), level,player.modelBound()))
			{
				player.stepDown(1);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			player.stepDown(1);
			if (!CreatureLevelBoxing::isPossibleToMove(player.getCoordinate(), level,player.modelBound()))
			{
				player.stepUp(1);
			}
		}
		
	}

	void isLevelEnded(sf::RenderWindow &window)
	{
		std::vector<Wall>::iterator doorOut = std::find_if(level.getWalls().begin(), level.getWalls().end(), [](Wall& wall) { return wall.type == wallType::doorOut; });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || ((doorOut != level.getWalls().end())&&(CreatureLevelBoxing::isCollision(player.getCoordinate(), 
			player.modelBound(), *doorOut, wallType::doorOut))))
		{
			EventOperator::instance()->push(Event::changingScene);
			EventOperator::instance()->putSceneToSwap(std::make_shared<MainMenu>(window));
		}
	}

	void playerRotation(Vector2 mouse)
	{
		Vector2 playerMouseCoordinate = mouse - (player.getCoordinate() + player.modelBound() / 2 - camera.getCoordinate())*camera.scrollScaling ;
		if (playerMouseCoordinate.y > 0)
		{
			player.getRotation() = acos(playerMouseCoordinate.x / playerMouseCoordinate.length()) * 180 / M_PI + 90;
		}
		else
		{
			player.getRotation() = 360 - acos(playerMouseCoordinate.x / playerMouseCoordinate.length()) * 180 / M_PI + 90;
		}
	}

	void cameraMover(sf::RenderWindow &window)
	{
		camera.getCoordinate() = ((player.getCoordinate() - Vector2(window.getSize().x, window.getSize().y) / 2 / camera.scrollScaling)
			* cameraSpeed +
			camera.getCoordinate()*(1 - cameraSpeed));
	}
	 
public:
	GameScene(sf::RenderWindow &window, size_t _levelNumber) :levelNumber(_levelNumber), level({ 2000,2000 }), player(ResourceFileNaming::heroName)
	{
		ClassSaver<Level>::download(levelNumber, level);
		wallSize = level.getWallSize();
		camera.getSpeed() = 1;
		camera.scrollScaling = 3;
		player.getSpeed() = 0.2;
		const std::vector<Wall>::iterator doorIn = std::find_if(level.getWalls().begin(), level.getWalls().end(), [](const Wall& wall) { return wall.type == wallType::doorIn; });
		if (doorIn != level.getWalls().end())
		{
			player.getCoordinate() = (*doorIn).getCoordinate();
		}
	}
	
	~GameScene()
	{
		
	}
	
	void render(sf::RenderWindow &window) override
	{
		Vector2 mouse(sf::Mouse::getPosition().x - window.getPosition().x, sf::Mouse::getPosition().y - window.getPosition().y - windowBorderSize);
		buttonOperator(window,mouse);
		isLevelEnded(window);
		cameraMover(window);
		playerRotation(mouse);
		LevelDrawer::draw(window, level, camera);
		CreatureDrawer::draw(window, player, camera, wallSize/2);
	};

	void scroll(int value) override
	{
			
	}
};
