#pragma once
#include "creatureDrawer.h"
#include "scene.h"
#include "creatureLevelBoxing.h"
#include "resourceFileNaming.h"
#include "animator.h"
#include "timer.h"
#include "enemy.h"
#include "enemyMover.h"


class GameScene final:public Scene
{
private:
	size_t levelNumber;
	Level level;
	Bitmap bitmap;
	Camera camera;
	Creature player;
	Timer playerTimer;
	Animator playerAnimator;
	std::vector<Enemy> enemies;
	size_t enemiesMaxCount = 5;
	Timer enemySpawnTimer;
	size_t wallSize = 100;

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)|| sf::Keyboard::isKeyPressed(sf::Keyboard::W)|| 
			sf::Keyboard::isKeyPressed(sf::Keyboard::S)|| sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (playerTimer.isTimerOut())
			{
				playerAnimator.setNext(player.getModel());
			}
			bitmap.mapRefresh(player);
		}
		else
		{
			playerAnimator.setDefault(player.getModel());
		}
	}

	void isLevelEnded(sf::RenderWindow &window)
	{
		std::vector<Wall>::iterator doorOut = std::find_if(level.getWalls().begin(), level.getWalls().end(), [](Wall& wall) { return wall.type == wallType::doorOut; });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || ((doorOut != level.getWalls().end())&&(CreatureLevelBoxing::isCollision(player.getCoordinate(), 
			player.modelBound(), *doorOut, wallType::doorOut)))||!player.alive())
		{
			EventOperator::instance()->push(Event::changingScene);
			EventOperator::instance()->putSceneToSwap(std::make_shared<MainMenu>(window));
		}
	}

	void playerAnimatorSetUp()
	{
		playerAnimator.addState(ResourceFileNaming::hero1Name);
		playerAnimator.addState(ResourceFileNaming::hero2Name);
		playerAnimator.addState(ResourceFileNaming::hero1Name);
		playerAnimator.addState(ResourceFileNaming::hero0Name);
		playerAnimator.addState(ResourceFileNaming::hero3Name);
		playerAnimator.addState(ResourceFileNaming::hero4Name);
		playerAnimator.addState(ResourceFileNaming::hero3Name);
	}

	void enemySpawning()
	{
		if (enemySpawnTimer.isTimerOut()&&enemies.size()<enemiesMaxCount)
		{
			std::for_each(level.getWalls().begin(), level.getWalls().end(),
			[this](Wall& wall)
			{
				if (wall.type == wallType::spawnPoint)
				{
					enemies.emplace_back(wall.getCoordinate(), 5);
					enemies.back().getSpeed() = 0.3;
				}
			});
		}
	}

	void enemyDrawer(sf::RenderWindow &window)
	{
		std::for_each(enemies.begin(), enemies.end(),
			[this, &window](Enemy& enemy)
		{
			CreatureDrawer::draw(window, enemy, camera, wallSize / 2);
		});
	}
	
public:
	GameScene(sf::RenderWindow &window, size_t _levelNumber) :levelNumber(_levelNumber), level({ 2000,2000 }), player(ResourceFileNaming::hero0Name), playerAnimator(ResourceFileNaming::hero0Name),enemySpawnTimer(3), bitmap(level)
	{
		playerAnimatorSetUp();
		ClassSaver<Level>::download(levelNumber, level);
		bitmap.load(level);
		wallSize = level.getWallSize();
		camera.getScrollScaling() = 3;
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
		camera.cameraMover(window, player.getCoordinate());
		player.rotation(camera, mouse);
		LevelDrawer::draw(window, level, camera);
		CreatureDrawer::draw(window, player, camera, wallSize/2);
		enemySpawning();
		EnemyMover::move(enemies, player, level, bitmap);
		enemyDrawer(window);
	};

	void scroll(int value) override
	{
			
	}
};
