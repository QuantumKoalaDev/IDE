#pragma once

#include <Core/EventSystem/Events/EventType.h>

class IEventListener
{
    public:
    virtual void onEvent(EventType type) = 0;
    virtual ~IEventListener() = default;

};