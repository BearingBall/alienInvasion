#include "level.h"

void Level::norming(float& value) const
{
	if ((value / wallSize) - static_cast<int>(value / wallSize) > floatLimit)
	{
		value = (static_cast<int>(value / wallSize)) * wallSize;
	}
}

void Level::norming(Vector2& value) const
{
	norming(value.x);
	norming(value.y);
}

void Level::addWall(std::string& wallName, Vector2 place, Vector2 shift, wallType type)
{
	place += shift;
	norming(place);
	Wall wall(wallName, place, type, wallSize);
	if ((place.x >= 0 && place.y >= 0) && (place.x < levelSize.x && place.y < levelSize.y)
		&& (std::find(walls.begin(), walls.end(), wall) == walls.end()))
	{
		walls.emplace_back(wallName, place, type, wallSize);
	}
}

const float& Level::getWallSize() const
{
	return wallSize;
}

float& Level::getWallSize()
{
	return wallSize;
}

const Vector2& Level::getLevelSize() const
{
	return levelSize;
}

Vector2& Level::getLevelSize()
{
	return levelSize;
}

const PictureObject& Level::getFloor() const
{
	return floor;
}

PictureObject& Level::getFloor()
{
	return floor;
}

const std::vector<Wall>& Level::getWalls() const
{
	return walls;
}

std::vector<Wall>& Level::getWalls()
{
	return walls;
}
