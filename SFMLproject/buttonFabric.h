#pragma once
#include "textObject.h"

class ButtonFabric final
{
	sf::Font& font;
public:
	ButtonFabric(sf::Font& _font):font(_font) {}
	std::shared_ptr<TextObject> createClickableButton(std::string text, size_t size, Vector2 coordinate, std::function<void(Object&)>& mouseOver, std::function<void(Object&)>& mousePressed) const
	{
		TextObject* button = new TextObject(font, text, size);
		button->setPosition(coordinate);
		button->setOnMouseOverFunction(mouseOver);
		button->setOnMousePressedFunction(mousePressed);
		return std::shared_ptr<TextObject>(button);
	}
};
