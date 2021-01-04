#pragma once
#include <SFML/Graphics.hpp>
#include "pictureObject.h"
#include "resourceFileNaming.h"
#include "textObject.h"

class AnimationBearingBall
{
private:
public:
	void running(sf::RenderWindow& window)
	{
		PictureObject man(ResourceFileNaming::soldierName);
		man.sprite.setScale(5, 5);
		sf::Font font;
		font.loadFromFile(ResourceFileNaming::fontName);
		std::string logo = "BearingBall";
		TextObject text(font, logo, 200);
		text.getText().setStyle(sf::Text::Bold);
		text.ChangeColour(sf::Color::Black);
		text.setPosition({ 600, 155 });
		font.loadFromFile(ResourceFileNaming::fontName);
		TextObject text2(font, "loading", 100);
		text2.ChangeColour(sf::Color::Black);
		text2.setPosition({ 700, 360 });
		text2.getText().setStyle(sf::Text::Bold);
		sf::Clock clock;
		sf::Time time = clock.getElapsedTime();

		
		size_t loadingTime = 2000;
		while (time.asMilliseconds() < 2*loadingTime)
		{
			time = clock.getElapsedTime();
			window.clear();
			man.draw(window);
			text.getText().setString(logo.substr(0, time.asMilliseconds()*logo.size() / loadingTime));
			if (time.asMilliseconds() > loadingTime*1.5)
			{
				text.getText().setStyle(sf::Text::Bold | sf::Text::Underlined);
			}
			text.draw(window);
			text2.draw(window);
			window.display();
		}
		
	}
};
