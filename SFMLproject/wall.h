#pragma once
#include "movable.h"
#include "pictureObject.h"

class Wall final: public Movable
{
private:
	std::string wallName = "../ResourceFile/wall.png";
	PictureObject model;
	float size;
public:
	Wall(std::string& _wallName, Vector2 coord, float _size = 100):Movable(coord),model(wallName),size(_size),wallName(_wallName)
	{
		
	}
	
	void draw(sf::RenderWindow& window, Vector2 shift, Vector2 levelSize)
	{
		model.refreshSprite(sf::IntRect(0, 0, size, size));
		model.setPosition({ (coordinate.x + shift.x) , (coordinate.y + shift.y) });
		//model.sprite.setScale(sf::Vector2f(size / model.texture.getSize().x, size / model.texture.getSize().y));
		model.draw(window);
	}

	bool operator==(const Wall& other) const
	{
		return (coordinate.x == other.coordinate.x) && (coordinate.y == other.coordinate.y);
	}
	
};
