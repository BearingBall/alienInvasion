#pragma once
#include "camera.h"
#include "creature.h"
#include "pictureObject.h"
#include "player.h"

class CreatureDrawer
{
private:
	static void drawHealthBar(sf::RenderWindow& window, Creature& creature, Camera& camera)
	{
		Vector2 barPlace = (creature.getCoordinate() - camera.getCoordinate() - Vector2(10, 20))*camera.getScrollScaling();
		sf::RectangleShape backgroundShape;
		backgroundShape.setFillColor({ 40,0,0 });
		backgroundShape.setPosition({ barPlace.x, barPlace.y });
		backgroundShape.setSize({ creature.modelBound().x * camera.getScrollScaling() , creature.modelBound().y / 8 * camera.getScrollScaling() });
		window.draw(backgroundShape);

		float borderSize = 3;
		sf::RectangleShape barShape;
		barShape.setFillColor({ 180,0,0 });
		barShape.setPosition({ barPlace.x + borderSize, barPlace.y + borderSize });
		barShape.setSize({ creature.modelBound().x* camera.getScrollScaling()*creature.percentageHealth() - borderSize * 2,
			(creature.modelBound().y / 8 * camera.getScrollScaling()) - borderSize * 2 });
		window.draw(barShape);
	}
	
public:
	static void draw(sf::RenderWindow& window, Creature& creature, Camera& camera, float wallSize)
	{
		creature.getModel().setPosition((creature.getCoordinate() - camera.getCoordinate())*camera.getScrollScaling() + creature.modelBound());
		creature.getModel().getSprite().setScale(camera.getScrollScaling(), camera.getScrollScaling());
		creature.getModel().getSprite().setRotation(creature.getRotation());
		creature.getModel().draw(window);
		drawHealthBar(window, creature, camera);
	}

};
