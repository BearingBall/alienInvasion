#pragma once
#include <deque>
#include "scene.h"

enum Event
{
	eventExit,
	changingScene
};

class EventOperator final
{
private:
	std::deque<Event> events;
	std::shared_ptr<Scene> sceneToSwap;
	
	EventOperator() = default;
	~EventOperator() = default;
public:
	static EventOperator* instance()
	{
		static EventOperator inst;
		return &inst;
	}

	bool empty() const
	{
		return events.empty();
	}
	
	void push(Event event)
	{
		events.push_back(event);
	}

	Event pop()
	{
		Event tmp = events.front();
		events.pop_front();
		return tmp;
	}

	void putSceneToSwap(std::shared_ptr<Scene> scene)
	{
		sceneToSwap = scene;
	}
	
	const std::shared_ptr<Scene>& getSceneToSwap() const
	{
		return sceneToSwap;
	}
};