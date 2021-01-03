#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "mainMenuScene.h"
#include "scene.h"

class Engine final
{
private:
	std::shared_ptr<Scene> activeScene;
	sf::RenderWindow window;
	sf::Event event;
	
public:
	Engine(): window(sf::VideoMode(1500, 900), "Game")
	{
		
	}
	
	~Engine() = default;
	
	void running()
	{
		activeScene = std::make_shared<MainMenu>(window);
		while (window.isOpen())
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
			while (!EventOperator::instance()->empty())
			{
				Event event = EventOperator::instance()->pop();
				if (event == Event::eventExit)
					window.close();
				if (event == Event::changingScene)
				{
					activeScene = EventOperator::instance()->sceneToSwap;
				}
			}
			
			window.clear();
			activeScene->render(window);
			window.display();
		}
	}
};
