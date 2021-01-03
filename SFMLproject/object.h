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

	void setOnMousePressedFunction(std::function<void(Object&)> &function)
	{
		OnMousePressedFunction = function;
	};

	void setOnMouseOverFunction(std::function<void(Object&)> &function)
	{
		OnMouseOverFunction = function;
	};

	virtual bool ifOnMousePressed(Vector2 point) = NULL;
	virtual bool ifOnMouseOver(Vector2 point) = NULL;
	
	bool onMousePressed(Vector2 point)
	{
		if (ifOnMousePressed(point))
		{
			if (OnMousePressedFunction)
			{
				OnMousePressedFunction(*this);
			}
			return true;
		}
		return false;
	}
	
	bool onMouseOver(Vector2 point)
	{
		if (ifOnMouseOver(point))
		{
			if (OnMouseOverFunction)
			{
				OnMouseOverFunction(*this);
			}
			return true;
		}
		return false;
	}

	virtual void ChangeColour(sf::Color color) = NULL;
	
	Object() = default;
	virtual ~Object() = default;
};
