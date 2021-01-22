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

	void checkSfEvents();
	void checkCustomEvents();

public:
	Engine(): window(sf::VideoMode(1500, 900), ResourceFileNaming::windowName)
	{
		window.setPosition({ 0,0 });
		activeScene = std::make_shared<MainMenu>(window);
	}
	~Engine() = default;

	void running();
};
