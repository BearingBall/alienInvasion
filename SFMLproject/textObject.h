#pragma once
#include "pictureObject.h"

struct TextObject final : Object
{
private:
	sf::Text text;
public:
	TextObject(sf::Font& font, std::string phrase, size_t size):text(phrase, font, size)
	{
		text.setFillColor(sf::Color::Black);
		text.setOutlineColor(sf::Color::Blue);
		text.setOutlineThickness(3);
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	}

	void draw(sf::RenderWindow &window) override
	{
		window.draw(text);
	}

	void setPosition(Vector2 point) override
	{
		text.setPosition(point.x, point.y);
	}
	
	bool ifOnMousePressed(Vector2 point) override
	{
		return onMouseOver(point);
	}

	bool ifOnMouseOver(Vector2 point) const override
	{
		return (point.x > text.getGlobalBounds().left) && (point.x < (text.getGlobalBounds().left + text.getGlobalBounds().width)) &&
			(point.y > text.getGlobalBounds().top) && (point.y < (text.getGlobalBounds().top + text.getGlobalBounds().height));
	}

	void ChangeColour(sf::Color color) override
	{
		text.setFillColor(color);
	}

	const sf::Text& getText() const
	{
		return text;
	}

	sf::Text& getText()
	{
		return text;
	}
};
