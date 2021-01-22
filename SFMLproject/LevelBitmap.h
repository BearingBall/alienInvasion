#pragma once
#include "level.h"
#include "enemy.h"
#include <array>
#include <iostream>
#include "vectorInt.h"

class Bitmap final
{
private:
	size_t x;
	size_t y;
	std::vector<int> map;
	float wallSize;
	VectorInt startPoint = {0,0};

	void calculateOtherPoint(VectorInt yourPoint, VectorInt otherPoint);
	void diving(VectorInt current);
	bool horizontalStepper(Enemy& enemy, Vector2& currentGlobal) const;
	bool verticalStepper(Enemy& enemy, Vector2& currentGlobal) const;

public:
	Bitmap(Level& level)
	{
		wallSize = level.getWallSize();
		x = level.getLevelSize().x / level.getWallSize();
		y = level.getLevelSize().y / level.getWallSize();
		map.resize(x*y+1);
		std::for_each(map.begin(), map.end(), [this](int& tmp) {tmp = x*y-1; });
		map[x*y] = x * y;
	}

	void load(Level& level);

	Bitmap(Bitmap& other)
	{
		wallSize = other.wallSize;
		x = other.x;
		y = other.y;
		map.resize(x*y + 1);
		for(size_t i = 0; i < x*y + 1; i++)
		{
			map[i] = other.map[i];
		}
	}

	int& point(size_t indexX, size_t indexY);
	void debug();
	void mapRefresh(Creature& player);
	void enemyMove(Enemy& enemy);
};
