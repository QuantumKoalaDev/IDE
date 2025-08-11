#pragma once

#include <Core/EventSystem/Events/Event.h>

#include <memory>

class IEventListener
{
    public:
    virtual void onEvent(std::shared_ptr<Event> event) = 0;
    virtual ~IEventListener() = default;

};