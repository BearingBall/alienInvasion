#pragma once
#include <corecrt_math_defines.h>

#include "damagable.h"
#include "movable.h"
#include "level.h"

enum CreatureStrategy
{
	walking,
	attacking,
	staying
};

enum Direction
{
	up,
	down,
	left,
	right
};

class Creature: public Movable, public Damagable
{
private:
	PictureObject model;
	float Rotation = 0;
public:
	Creature(const std::string& name, Vector2 coord = {0,0}, size_t maxHealth = 100):Movable(coord),Damagable(maxHealth),model(name)
	{
		model.getSprite().setOrigin(model.getSprite().getLocalBounds().width / 2, model.getSprite().getLocalBounds().height / 2);
	}
	virtual ~Creature() = default;
	
	const PictureObject& getModel() const
	{
		return model;
	}

	Vector2 modelBound()
	{
		return Vector2(getModel().getSprite().getLocalBounds().width, getModel().getSprite().getLocalBounds().height);
	}

	PictureObject& getModel()
	{
		return model;
	}

	float& getRotation()
	{
		return Rotation;
	}

	const float& getRotation() const
	{
		return Rotation;
	}

	void rotation(Camera& camera, Vector2 pointToRotate)
	{
		const Vector2 playerMouseCoordinate = pointToRotate - (getCoordinate() + modelBound() / 2 - camera.getCoordinate())*camera.scrollScaling;
		rotation(playerMouseCoordinate);
	}

	void rotation(Vector2 pointToRotate)
	{
		if (pointToRotate.y > 0)
		{
			getRotation() = acos(pointToRotate.x / pointToRotate.length()) * 180 / M_PI + 90;
		}
		else
		{
			getRotation() = 360 - acos(pointToRotate.x / pointToRotate.length()) * 180 / M_PI + 90;
		}
	}
};
