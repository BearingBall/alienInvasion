#pragma once
#include "camera.h"
#include "creature.h"
#include "pictureObject.h"
#include "player.h"

class CreatureDrawer
{
private:
public:
	static void draw(sf::RenderWindow& window, Creature& creature, Camera& camera, float wallSize)
	{
		creature.getModel().setPosition((creature.getCoordinate() - camera.getCoordinate())*camera.scrollScaling + creature.modelBound());
		creature.getModel().getSprite().setScale(wallSize / creature.getModel().getTexture().getSize().x*camera.scrollScaling, 
			wallSize / creature.getModel().getTexture().getSize().y*camera.scrollScaling);
		creature.getModel().getSprite().setRotation(creature.getRotation());
		
		creature.getModel().draw(window);
	}

};
