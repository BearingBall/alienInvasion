#pragma once
#include <SFML/Graphics.hpp>
#include "movable.h"
#include "vector2.h"

class Camera final:public Movable
{
private:
	float scrollScaling = 1;
	float expingArea = 50;
	float expingStrongParam = 3;
	
	Vector2 exping(Vector2 velocity) const;
	
public:
	Camera():Movable({0,0})
	{
		speed = 0.005;
		maxSpeed = 400;
	}
	~Camera() = default;

	float& getScrollScaling()
	{
		return scrollScaling;
	}

	void cameraMover(sf::RenderWindow &window, Vector2& playerCoordinate);
};