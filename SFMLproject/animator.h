#pragma once
#include <vector>
#include "pictureObject.h"
#include "textureCollector.h"

class Animator final
{
private:
	std::vector<std::string> states;
	size_t currentState = 0;
public:
	Animator(const std::string& defaultState)
	{
		addState(defaultState);
	}

	void addState(const std::string& state)
	{
		states.emplace_back(state);
	}

	void setDefault(PictureObject object)
	{
		object.getTexture().loadFromFile(states[0]);
	}

	void setNext(PictureObject object)
	{
		currentState = currentState + 1 < states.size()  ? currentState + 1 : 0;
		object.getTexture().loadFromFile(states[currentState]);
	}
	
	
};
