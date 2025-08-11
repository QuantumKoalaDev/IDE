#pragma once

#include "EventType.h"

class Event
{
    EventType m_type;

    public:
    Event() : m_type(EventType::NoneEvent) {};
    Event(EventType type) : m_type(type) {};
    virtual ~Event() = default;
    
    EventType getType() const { return m_type; }
};