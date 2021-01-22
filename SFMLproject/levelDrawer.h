#pragma once
#include <SFML/Graphics.hpp>


#include "camera.h"
#include "level.h"
#include "floorDrawer.h"

class LevelDrawer final
{
public:
	static void draw(sf::RenderWindow& window, Level& level, Camera& camera);
};
