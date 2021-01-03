#pragma once
#include "movable.h"
#include "vector2.h"

class Camera final:public Movable
{
public:
	Camera():Movable({0,0})
	{
		
	}
	~Camera() = default;
	
};
