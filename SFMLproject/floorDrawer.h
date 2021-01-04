#pragma once

#include "pictureObject.h"

class FloorDrawer
{
private:
	inline static const Vector2 startFloorPosition = { 0,0 };
public:
	static void draw(sf::RenderWindow& window, PictureObject& floor, Vector2 shift)
	{
		floor.setPosition(startFloorPosition+shift);
		floor.draw(window);
	}
};
