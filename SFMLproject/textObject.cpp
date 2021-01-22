#include "textObject.h"

void TextObject::draw(sf::RenderWindow& window)
{
	window.draw(text);
}

void TextObject::setPosition(Vector2 point)
{
	text.setPosition(point.x, point.y);
}

bool TextObject::ifOnMousePressed(Vector2 point)
{
	return onMouseOver(point);
}

bool TextObject::ifOnMouseOver(Vector2 point) const
{
	return (point.x > text.getGlobalBounds().left) && (point.x < (text.getGlobalBounds().left + text
	                                                                                            .getGlobalBounds().width
		)) &&
		(point.y > text.getGlobalBounds().top) && (point.y < (text.getGlobalBounds().top + text.getGlobalBounds().height
		));
}

void TextObject::ChangeColour(sf::Color color)
{
	text.setFillColor(color);
}

const sf::Text& TextObject::getText() const
{
	return text;
}

sf::Text& TextObject::getText()
{
	return text;
}
