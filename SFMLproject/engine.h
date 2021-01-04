#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "mainMenuScene.h"
#include "scene.h"
#include "animationBearingBall.h"
#include "resourceFileNaming.h"

class Engine final
{
private:
	std::shared_ptr<Scene> activeScene;
	sf::RenderWindow window;
	sf::Event event;

	void checkSfEvents()
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}

		}
	}

	void checkCustomEvents()
	{
		while (!EventOperator::instance()->empty())
		{
			Event event = EventOperator::instance()->pop();
			if (event == Event::eventExit)
				window.close();

			if (event == Event::changingScene)
			{
				activeScene = EventOperator::instance()->getSceneToSwap();
			}
		}
	}

	
public:
	Engine(): window(sf::VideoMode(1500, 900), ResourceFileNaming::windowName)
	{
		window.setPosition({ 0,0 });
		activeScene = std::make_shared<MainMenu>(window);
	}
	~Engine() = default;
	
	void running()
	{
		AnimationBearingBall animation;
		animation.running(window);
		while (window.isOpen())
		{
			checkSfEvents();
			checkCustomEvents();
			window.clear();
			activeScene->render(window);
			window.display();
		}
	}
};
