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

	void norming(float& value) const;
	void norming(Vector2& value) const;

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

	void addWall(std::string& wallName, Vector2 place, Vector2 shift, wallType type);
	
	const float& getWallSize() const;
	float& getWallSize();

	const Vector2& getLevelSize() const;
	Vector2& getLevelSize();

	const PictureObject& getFloor() const;
	PictureObject& getFloor();
	
	const std::vector<Wall>& getWalls() const;
	std::vector<Wall>& getWalls();
};