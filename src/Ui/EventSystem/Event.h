#pragma once

#include "EventTypes.h"

class Event
{
public:
	Event() : m_eventType(None) {};
	Event(EventType type) : m_eventType(type) {};
	~Event() = default;
	virtual EventType getEventType() const = 0;
	virtual int getKeyCode() const = 0;

protected:
	EventType m_eventType;

};