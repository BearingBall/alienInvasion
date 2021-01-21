#pragma once
#include "bullet.h"
#include "camera.h"

class BulletDrawer
{
private:

public:
	static void draw(sf::RenderWindow& window, Bullet& bullet, Camera& camera)
	{
		bullet.getModel().setPosition((bullet.getCoordinate() - camera.getCoordinate())*camera.getScrollScaling());
		bullet.getModel().getSprite().setScale(camera.getScrollScaling(), camera.getScrollScaling());
		bullet.getModel().getSprite().setRotation(bullet.getRotation());
		bullet.getModel().draw(window);
	}

};
