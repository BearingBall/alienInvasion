#pragma once
#include "vector2.h"

class Movable
{
	

	
public:
	Vector2 coordinate = {0,0};
	float speed = 0;
	Movable(Vector2 coord):coordinate(coord)
	{
		
	}

	void stepLeft()
	{
		coordinate.x -= speed;
	}
	void stepRigth()
	{
		coordinate.x += speed;
	}
	void stepUp()
	{
		coordinate.y -= speed;
	}
	void stepDown()
	{
		coordinate.y += speed;
	}
	
	virtual ~Movable() = default;
};
