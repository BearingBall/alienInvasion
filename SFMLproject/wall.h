#pragma once
#include "movable.h"
#include "pictureObject.h"

enum wallType
{
	wall,
	spawnPoint,
	doorIn,
	doorOut
};

class Wall final: public Movable
{
private:
public:
	float size;
	std::string wallName;
	wallType type;
	PictureObject model;
	Wall(std::string _wallName, Vector2 coord, wallType _type, float _size):Movable(coord),model(wallName),size(_size),wallName(_wallName),type(_type)
	{
		
	}
	
	void draw(sf::RenderWindow& window, Vector2 shift, Vector2 levelSize, float scroll)
	{
		model.refreshSprite(sf::IntRect(0, 0, model.getTexture().getSize().x, model.getTexture().getSize().y));
		model.setPosition((coordinate+shift)*scroll);
		model.getSprite().setScale(sf::Vector2f(size / model.getTexture().getSize().x*scroll, size / model.getTexture().getSize().y*scroll));
		model.draw(window);
	}

	bool operator==(const Wall& other) const
	{
		return coordinate == other.getCoordinate();
	}

};


