#include "levelDrawer.h"

void LevelDrawer::draw(sf::RenderWindow& window, Level& level, Camera& camera)
{
	FloorDrawer::draw(window, level.getFloor(), camera, level.getWallSize());
	std::for_each(level.getWalls().begin(), level.getWalls().end(),
	              [&window,&camera,&level](Wall& tmp)
	              {
		              tmp.draw(window, camera.getCoordinate() * (-1), level.getLevelSize(), camera.getScrollScaling());
	              });
}
