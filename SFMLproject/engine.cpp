#include "engine.h"

void Engine::checkSfEvents()
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

		if (event.type == sf::Event::MouseWheelScrolled)
		{
			activeScene->scroll(event.mouseWheelScroll.delta);
		}
	}
}

void Engine::checkCustomEvents()
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

void Engine::running()
{
	AnimationBearingBall animation;
	animation.running(window);
	Timer framerate(0.01);
	while (window.isOpen())
	{
		checkSfEvents();
		checkCustomEvents();
		if (framerate.isTimerOut())
		{
			window.clear();
			activeScene->render(window);
			window.display();
		}
	}
}
