#pragma once
#include "textObject.h"

class ButtonFabric final
{
	sf::Font& font;
public:
	ButtonFabric(sf::Font& _font):font(_font) {}
	TextObject* createClickableButton(std::string text, size_t size, Vector2 place, std::function<void(Object&)>& mouseOver, std::function<void(Object&)>& mousePressed)
	{
		TextObject* button = new TextObject(font, text, size);
		button->setPosition(place);
		button->setOnMouseOverFunction(mouseOver);
		button->setOnMousePressedFunction(mousePressed);
		return button;
	}
};
