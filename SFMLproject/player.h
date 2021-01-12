#pragma once
#include "creature.h"

class Player final: public Creature
{
private:
	
public:
	Player(const std::string& name, Vector2 coord, size_t maxHealth ):Creature(name, coord,maxHealth)
	{
		
	}

	Player(const std::string& name, Vector2 coord) :Creature(name, coord)
	{

	}

	Player(const std::string& name) :Creature(name)
	{

	}
	
	~Player() = default;
};