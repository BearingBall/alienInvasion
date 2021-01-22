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

	void draw(sf::RenderWindow& window) override;
	void setPosition(Vector2 point) override;
	
	bool ifOnMousePressed(Vector2 point) override;
	bool ifOnMouseOver(Vector2 point) const override;
	
	void ChangeColour(sf::Color color) override;
	
	const sf::Text& getText() const;
	sf::Text& getText();
};
