#pragma once
#include "movable.h"
#include "vector2.h"

class Camera final:public Movable
{
private:
	float scrollScaling = 1;
	float expingArea = 50;
	float expingStrongParam = 3;
	

	Vector2 exping(Vector2 velocity)
	{
		if (velocity.x > 0)
		{
			velocity.x = (exp((velocity.x - expingArea) / expingStrongParam) + expingArea);
		}
		else
		{
			velocity.x = -1 * (exp((-1 * velocity.x - expingArea) / expingStrongParam) + expingArea);
		}
		if (velocity.y > 0)
		{
			velocity.y = (exp((velocity.y - expingArea) / expingStrongParam) + expingArea);
		}
		else
		{
			velocity.y = -1 * (exp((-1 * velocity.y - expingArea) / expingStrongParam) + expingArea);
		}
		if (velocity.x > maxSpeed)
		{
			velocity.x = maxSpeed;
		}
		if (velocity.y > maxSpeed)
		{
			velocity.y = maxSpeed;
		}
		if (velocity.x < -maxSpeed)
		{
			velocity.x = -maxSpeed;
		}
		if (velocity.y < -maxSpeed)
		{
			velocity.y = -maxSpeed;
		}
		return velocity;
	}
	
public:
	Camera():Movable({0,0})
	{
		speed = 0.001;
		maxSpeed = 400;
	}
	~Camera() = default;

	float& getScrollScaling()
	{
		return scrollScaling;
	}

	void cameraMover(sf::RenderWindow &window, Vector2& playerCoordinate)
	{
		if ((getCoordinate() - (playerCoordinate - Vector2(window.getSize().x, window.getSize().y) / 2 / getScrollScaling())).length() > expingArea)
		{
			getCoordinate() +=
				exping(playerCoordinate - Vector2(window.getSize().x, window.getSize().y) / 2 / getScrollScaling() - getCoordinate())*speed;
		}
		else
		{
			getCoordinate() += (playerCoordinate - Vector2(window.getSize().x, window.getSize().y) / 2 / getScrollScaling() - getCoordinate())*speed;
		}
	}
};
