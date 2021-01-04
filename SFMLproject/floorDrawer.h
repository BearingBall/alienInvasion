#pragma once

#include "pictureObject.h"

class FloorDrawer
{
public:
	static void draw(sf::RenderWindow& window, PictureObject& floor, Vector2 shift, Vector2 levelSize, size_t size)
	{
			floor.setPosition({ (0 + shift.x) , (0 + shift.y) });
			floor.draw(window);
	}
};
