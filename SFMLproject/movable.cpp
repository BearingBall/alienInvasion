#include "movable.h"

void Movable::step(Vector2 direction)
{
	coordinate += direction * speed;
}

void Movable::stepLeft(float stepSize)
{
	coordinate.x -= speed * stepSize;
}

void Movable::stepRigth(float stepSize)
{
	coordinate.x += speed * stepSize;
}

void Movable::stepUp(float stepSize)
{
	coordinate.y -= speed * stepSize;
}

void Movable::stepDown(float stepSize)
{
	coordinate.y += speed * stepSize;
}

const Vector2& Movable::getCoordinate() const
{
	return coordinate;
}

Vector2& Movable::getCoordinate()
{
	return coordinate;
}

const float& Movable::getSpeed() const
{
	return speed;
}

float& Movable::getSpeed()
{
	return speed;
}
