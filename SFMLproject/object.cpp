#include "object.h"

void Object::setOnMousePressedFunction(std::function<void(Object&)>& function)
{
	OnMousePressedFunction = function;
}

void Object::setOnMouseOverFunction(std::function<void(Object&)>& function)
{
	OnMouseOverFunction = function;
}

bool Object::onMousePressed(Vector2 point)
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

bool Object::onMouseOver(Vector2 point)
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
