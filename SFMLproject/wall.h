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
	Wall(const std::string& _wallName, Vector2 coord, wallType _type, float _size):Movable(coord),model(wallName),size(_size),wallName(_wallName),type(_type)
	{
		
	}

	void draw(sf::RenderWindow& window, Vector2 shift, Vector2 levelSize, float scroll);

	bool operator==(const Wall& other) const;
};


