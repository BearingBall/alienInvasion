#pragma once
#include "creature.h"
#include "level.h"


class CreatureLevelBoxing final
{
public:
	static bool isCollision(Vector2 coordinate, Vector2 modelSize, Level& level, wallType type)
	{
		bool isCollision = false;
		std::for_each(level.getWalls().begin(), level.getWalls().end(),
			[&coordinate, &level, &modelSize, &isCollision,&type](Wall& wall)
		{
			if ((coordinate.x < wall.getCoordinate().x + level.getWallSize())
				&& (coordinate.x + modelSize.x > wall.getCoordinate().x)
				&& (coordinate.y < wall.getCoordinate().y + level.getWallSize())
				&& (coordinate.y + modelSize.y > wall.getCoordinate().y)
				&& (wall.type == type))
			{
				isCollision = true;
			}
		});
		return isCollision;
	}

	static bool isCollision(Vector2 coordinate, Vector2 modelSize, Wall& wall, wallType type)
	{
		float howDeepCollision = 1;
		if (type == wallType::doorOut)
		{
			howDeepCollision = 0.4;
		}
		return ((coordinate.x < wall.getCoordinate().x + wall.size*howDeepCollision)
			&& (coordinate.x + modelSize.x*howDeepCollision > wall.getCoordinate().x)
			&& (coordinate.y < wall.getCoordinate().y + wall.size*howDeepCollision)
			&& (coordinate.y + modelSize.y*howDeepCollision > wall.getCoordinate().y)
			&& (wall.type == type));
	}
	
	static bool isPossibleToMove(Vector2 coordinate, Level& level, Vector2 modelSize)
	{
		if (coordinate.x < 0) return false;
		if (coordinate.y < 0) return false;
		if (coordinate.x > level.getLevelSize().x - modelSize.x) return false;
		if (coordinate.y > level.getLevelSize().y - modelSize.y) return false;
		return !isCollision(coordinate, modelSize, level, wallType::wall);
	}
	
};
