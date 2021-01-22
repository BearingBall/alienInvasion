#include "buttonFabric.h"

std::shared_ptr<TextObject> ButtonFabric::createClickableButton(std::string text, size_t size,
                Vector2 coordinate, std::function<void(Object&)>& mouseOver, std::function<void(Object&)>& mousePressed) const
{
	TextObject* button = new TextObject(font, text, size);
	button->setPosition(coordinate);
	button->setOnMouseOverFunction(mouseOver);
	button->setOnMousePressedFunction(mousePressed);
	return std::shared_ptr<TextObject>(button);
}
