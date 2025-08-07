#pragma once

#include "EventType.h"

class Event
{
    EventType m_type;

    public:
    Event(EventType type) : m_type(type) {};
    
    EventType getType() { return m_type; }
};