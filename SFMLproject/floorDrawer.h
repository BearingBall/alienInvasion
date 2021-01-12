#pragma once

#include "pictureObject.h"

class FloorDrawer
{
private:
	inline static const Vector2 startFloorPosition = { 0,0 };
public:
	static void draw(sf::RenderWindow& window, PictureObject& floor, Camera& camera, float wallSize)
	{
		floor.setPosition((startFloorPosition - camera.getCoordinate())*camera.scrollScaling);
		floor.getSprite().setScale( wallSize / floor.getTexture().getSize().x*camera.scrollScaling, wallSize / floor.getTexture().getSize().y*camera.scrollScaling);
		floor.draw(window);
	}
};
