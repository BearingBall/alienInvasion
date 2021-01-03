#pragma once

#include "pictureObject.h"

class FloorDrawer
{
public:
	static void draw(sf::RenderWindow& window, PictureObject& floor, Vector2 shift, Vector2 levelSize, size_t size)
	{
			floor.setPosition({ (0 + shift.x) , (0 + shift.y) });
			//model.sprite.setScale(sf::Vector2f(size / model.texture.getSize().x, size / model.texture.getSize().y));
			floor.draw(window);
	}
};
