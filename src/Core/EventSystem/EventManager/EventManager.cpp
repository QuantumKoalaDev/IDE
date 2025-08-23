#include "EventManager.h"

#include <iostream>

//#include <chrono>

EventManager::EventManager() {};

void EventManager::dispatchEvent(bool ui)
{
    
    //bool hasEvent;

    if (ui && !m_uiToCore.empty())
    {
        //std::cout << "Dispatch Event started To core:" << std::chrono::system_clock::now() << '\n';
        //Core::EventSystem::Events::Event e;
        //m_uiToCore.tryPop(e);
        std::optional<Core::EventSystem::Events::Event> e = m_uiToCore.pop();

        if (e.has_value())
            notify(e.value());
        //std::cout << "Dispatch Event ended:" << std::chrono::system_clock::now() << '\n';
    }
    else if (!ui && !m_coreToUi.empty())
    {
        //std::cout << "Dispatch Event started To ui:" << std::chrono::system_clock::now() << '\n';
        //Core::EventSystem::Events::Event e;
        //m_coreToUi.tryPop(e);
        std::optional<Core::EventSystem::Events::Event> e = m_coreToUi.pop();
        if (e.has_value())
            notify(e.value());
        //std::cout << "Dispatch Event ended:" << std::chrono::system_clock::now() << '\n';
    }
    //if (!ui) hasEvent = m_uiToCore.tryPop(e);
    //else hasEvent = m_coreToUi.tryPop(e);

    //if (hasEvent) notify(e);

}

void EventManager::addListener(EventType type, IEventListener* listener)
{
    m_EventListenerMap[type].push_back(listener);
}

void EventManager::removeListener(IEventListener* listener, EventType type)
{
    if (type == NoneEvent)
    {
        for (auto& [eventType, listeners] : m_EventListenerMap)
        {
            std::erase_if(listeners, [listener](IEventListener* l)
                {
                    return l == listener;
                }
            );
        }

        return;
    }

    auto it = m_EventListenerMap.find(type);

    if (it == m_EventListenerMap.end()) return;

    std::erase_if(it->second, [listener](IEventListener* l)
        {
            return l == listener;
        }
    );
}

void EventManager::pushEvent(Core::EventSystem::Events::Event event, bool ui)
{

    if (ui) m_coreToUi.push(std::move(event));
    else m_uiToCore.push(std::move(event));
}

void EventManager::notify(Core::EventSystem::Events::Event event)
{
    auto it = m_EventListenerMap.find(event.type);

    if (it == m_EventListenerMap.end()) return;

    for (auto* listener : it->second)
    {
        listener->onEvent(event);
    }
}