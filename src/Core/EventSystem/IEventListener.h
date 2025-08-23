#pragma once

#include <Core/EventSystem/Events/Event.h>

#include <memory>

class IEventListener
{
    public:
    virtual void onEvent(const Core::EventSystem::Events::Event& event) = 0;
    virtual ~IEventListener() = default;

};