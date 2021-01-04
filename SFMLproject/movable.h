#pragma once
#include "vector2.h"

class Movable
{
protected:
	Vector2 coordinate = {0,0};
	float speed = 0;
	
private:
	
public:
	Movable(Vector2 coord):coordinate(coord)
	{
		
	}

	void stepLeft(float stepSize)
	{
		coordinate.x -= speed*stepSize;
	}
	void stepRigth(float stepSize)
	{
		coordinate.x += speed*stepSize;
	}
	void stepUp(float stepSize)
	{
		coordinate.y -= speed*stepSize;
	}
	void stepDown(float stepSize)
	{
		coordinate.y += speed*stepSize;
	}
	
	virtual ~Movable() = default;

	const Vector2& getCoordinate() const
	{
		return coordinate;
	}

	Vector2& getCoordinate()
	{
		return coordinate;
	}

	const float& getSpeed() const
	{
		return speed;
	}

	float& getSpeed()
	{
		return speed;
	}
};
