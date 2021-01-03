#pragma once
#include <SFML/Graphics.hpp>


#include "camera.h"
#include "level.h"
#include "floorDrawer.h"

class LevelDrawer final
{
public:
	static void draw(sf::RenderWindow& window, Level& level, Camera& camera)
	{
		FloorDrawer::draw(window, level.floor, { -1 * (camera.coordinate.x),-1 * (camera.coordinate.y) }, level.levelSize, level.wallSize);
		std::for_each(level.walls.begin(), level.walls.end(), [&window,&camera,&level](Wall& tmp)
		{
			tmp.draw(window,{-1*(camera.coordinate.x),-1*(camera.coordinate.y)},level.levelSize);
			//std::cout << tmp.coordinate.x << " " << tmp.coordinate.y << "\n";
		});
		//std::cout << "\n";
	}
};
