#pragma once
#include "vector2.h"


class Movable
{
protected:
	Vector2 coordinate = {0,0};
	float speed = 0;
	float maxSpeed = 0;
private:
	
public:
	Movable(Vector2 coord):coordinate(coord)
	{
		
	}

	void step(Vector2 direction);
	void stepLeft(float stepSize);
	void stepRigth(float stepSize);
	void stepUp(float stepSize);
	void stepDown(float stepSize);
	
	virtual ~Movable() = default;
	
	const Vector2& getCoordinate() const;
	Vector2& getCoordinate();
	
	const float& getSpeed() const;
	float& getSpeed();
};