#pragma once

#include "EventType.h"

#include <Core/EventSystem/Events/KeyboardEvent.h>
#include <Core/EventSystem/Events/ResizeEvent.h>
#include <Core/EventSystem/Events/MouseEvent.h>
#include <Core/EventSystem/Events/TextEvents/CreateTextboxEvent.h>
#include <Core/EventSystem/Events/TextEvents/SingleLineUpdateEvent.h>
#include <Core/EventSystem/Events/EmptyEvent.h>

#include <variant>

namespace Core::EventSystem::Events
{
    using eventUnion = std::variant <
        // Core -> Ui
        Core::EventSystem::Events::ResizeEvent,
        Core::EventSystem::Events::TextEvents::CreateTextboxEvent,
        Core::EventSystem::Events::TextEvents::SingleLineUpdateEvent,

        // Ui -> Core
        Core::EventSystem::Events::KeyboardEvent,
        Core::EventSystem::Events::MouseEvent,

        // Empty Event
        Core::EventSystem::Events::EmptyEvent
    >;

    struct Event
    {
        Event(): type(EventType::NoneEvent), event(Core::EventSystem::Events::EmptyEvent()) {}
        Event(EventType type, eventUnion event): type(type), event(event) {}


        EventType type;
        eventUnion event;
    };
}
