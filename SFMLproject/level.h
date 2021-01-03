#pragma once
#include <vector>
#include <algorithm>

#include "enemy.h"
#include "wall.h"

class Level final
{
	
	const float floatLimit = 0.0001;

	void norming(float& value) const 
	{
		if ((value / wallSize) - static_cast<int>(value / wallSize) > floatLimit)
		{
			value = (static_cast<int>(value / wallSize))*wallSize;
		}
	}
public:
	float wallSize = 100;
	Vector2 levelSize;
	Level(std::string groundName, Vector2 _levelSize = { 2000,2000 }):levelSize(_levelSize),floor(groundName)
	{
		norming(levelSize.x);
		norming(levelSize.y);
		floor.texture.setSmooth(true);
		floor.texture.setRepeated(true);
		floor.refreshSprite(sf::IntRect(0, 0, levelSize.x* floor.texture.getSize().x/ wallSize, levelSize.y*floor.texture.getSize().y / wallSize));
		floor.sprite.setScale(sf::Vector2f(wallSize/ floor.texture.getSize().x, wallSize / floor.texture.getSize().y));
	}
	~Level() = default;
	PictureObject floor;
	std::vector<Wall> walls;
	std::vector<Enemy> enemies;
	
	void addWall(std::string& wallName, Vector2 place, Vector2 shift)
	{
		place.x += shift.x;
		place.y += shift.y;
		norming(place.x);
		norming(place.y);
		Wall wall(wallName, place, wallSize);
		if ((place.x >= 0 && place.y >= 0) && (place.x < levelSize.x && place.y < levelSize.y)&&(std::find(walls.begin(), walls.end(), wall) == walls.end()))
		{
			walls.push_back(wall);
		}
	}

	
};
