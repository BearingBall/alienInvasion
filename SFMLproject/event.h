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

	std::shared_ptr<Scene> sceneToSwap;
	
private:
	std::deque<Event> events;

	EventOperator() = default;
	~EventOperator() = default;
};