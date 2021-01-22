#pragma once
#include <vector>
#include "pictureObject.h"

class Animator final
{
private:
	std::vector<std::string> states;
	size_t currentState = 0;
public:
	Animator(const std::string& defaultState);

	void addState(const std::string& state);

	void setDefault(PictureObject& object);

	void setNext(PictureObject& object);
};
