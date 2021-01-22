#include "animator.h"

Animator::Animator(const std::string& defaultState)
{
	addState(defaultState);
}

void Animator::addState(const std::string& state)
{
	states.emplace_back(state);
}

void Animator::setDefault(PictureObject& object)
{
	object.getTexture().loadFromFile(states[0]);
}

void Animator::setNext(PictureObject& object)
{
	currentState = currentState + 1 < states.size() ? currentState + 1 : 0;
	object.getTexture().loadFromFile(states[currentState]);
}