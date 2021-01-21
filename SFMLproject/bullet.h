#pragma once
#include "creature.h"
#include "movable.h"
#include "objectCollider.h"
#include "pictureObject.h"
#include "resourceFileNaming.h"

class Bullet final :public Movable
{
private:
	PictureObject model;
	float rotation = 0;
	float defaultSpeed = 1.5;
	bool endOfLife = false;
	Timer life;
public:
	Bullet(Creature& gunOwner, float _rotation):Movable(gunOwner.getCoordinate() + gunOwner.modelBound()/2), model(ResourceFileNaming::bulletName), life(2)
	{
		rotation = _rotation;
		getSpeed() = defaultSpeed;
	}

	void render(sf::RenderWindow& window, Level& level)
	{
		step({ static_cast<float>(cos((rotation-90)/180*M_PI)), static_cast<float>(sin((rotation-90) / 180 * M_PI)) });

		std::for_each(level.getWalls().begin(), level.getWalls().end(),[this](Wall& wall)
		{
			if ((wall.type == wallType::wall)&&(ObjectCollider::isCollides(model,wall.model)))
			{
				endOfLife = true;
			}
		});

		if (life.isTimerOut())
		{
			endOfLife = true;
		}
	}

	PictureObject& getModel()
	{
		return model;
	}

	float& getRotation()
	{
		return rotation;
	}

	bool& getEndOfLife()
	{
		return endOfLife;
	}
};
