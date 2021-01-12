#pragma once
#include <vector>
#include <algorithm>

#include "enemy.h"
#include "wall.h"

class Level final
{
private:
	const float floatLimit = 0.0001;
	float wallSize = 100;
	Vector2 levelSize;

	PictureObject floor;
	
	std::vector<Wall> walls;
	std::vector<Enemy> enemies;
	
	void norming(float& value) const 
	{
		if ((value / wallSize) - static_cast<int>(value / wallSize) > floatLimit)
		{
			value = (static_cast<int>(value / wallSize))*wallSize;
		}
	}

	void norming(Vector2& value) const
	{
		norming(value.x);
		norming(value.y);
	}
	
public:
	Level(Vector2 _levelSize = { 2000,2000 }):levelSize(_levelSize),floor(ResourceFileNaming::groundName)
	{
		norming(levelSize);
		floor.getTexture().setSmooth(true);
		floor.getTexture().setRepeated(true);
		floor.refreshSprite(sf::IntRect(0, 0, levelSize.x * floor.getTexture().getSize().x / wallSize, levelSize.y*floor.getTexture().getSize().y / wallSize));
		floor.getSprite().setScale(sf::Vector2f(wallSize/ floor.getTexture().getSize().x, wallSize / floor.getTexture().getSize().y));
	}
	~Level() = default;
	
	void addWall(std::string& wallName, Vector2 place, Vector2 shift, wallType type)
	{
		place += shift;
		norming(place);
		Wall wall(wallName, place, type, wallSize);
		if ((place.x >= 0 && place.y >= 0) && (place.x < levelSize.x && place.y < levelSize.y)
			&&(std::find(walls.begin(), walls.end(), wall) == walls.end()))
		{
			walls.emplace_back(wallName, place, type, wallSize);
		}
	}

	const float& getWallSize() const
	{
		return wallSize;
	}
	
	float& getWallSize()
	{
		return wallSize;
	}

	const Vector2& getLevelSize() const
	{
		return levelSize;
	}

	Vector2& getLevelSize()
	{
		return levelSize;
	}

	const PictureObject& getFloor() const
	{
		return floor;
	}

	PictureObject& getFloor()
	{
		return floor;
	}

	const std::vector<Wall>& getWalls() const
	{
		return walls;
	}

	std::vector<Wall>& getWalls()
	{
		return walls;
	}
};
