#pragma once
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
	
	//virtual void playCurrentAnimation();

	//virtual void move(Direction direction, Level& level);

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
};
