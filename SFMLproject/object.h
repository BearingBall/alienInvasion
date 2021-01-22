#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include "vector2.h"

struct Object
{
protected:
	std::function<void(Object&)> OnMousePressedFunction;
	std::function<void(Object&)> OnMouseOverFunction;
	
public:
	virtual void draw(sf::RenderWindow &window) = NULL;
	virtual void setPosition(Vector2 point) = NULL;

	void setOnMousePressedFunction(std::function<void(Object&)>& function);;
	void setOnMouseOverFunction(std::function<void(Object&)>& function);;

	virtual bool ifOnMousePressed(Vector2 point) = NULL;
	virtual bool ifOnMouseOver(Vector2 point) const = NULL;

	bool onMousePressed(Vector2 point);
	bool onMouseOver(Vector2 point);

	virtual void ChangeColour(sf::Color color) = NULL;
	
	Object() = default;
	virtual ~Object() = default;
};
