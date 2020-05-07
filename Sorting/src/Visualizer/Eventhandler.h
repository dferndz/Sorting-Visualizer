#pragma once

#include <list>

template <class T_event>
class EventHandler {
public:
	EventHandler() {

	}

	void operator+= (void(*func)(T_event&)) {
		_handlers.push_back(func);
	}

	void operator-= (void(*func)(T_event&)) {
		_handlers.remove(func);
	}

	void operator() (T_event& event) {
		for (auto handler : _handlers)
			handler(event);
	}

private:
	std::list<void(*)(T_event&)> _handlers;
};