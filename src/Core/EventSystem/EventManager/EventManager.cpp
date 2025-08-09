#include "EventManager.h"

EventManager::EventManager(ThreadSafeQueue<Event>& uiToCore, ThreadSafeQueue<Event>& coreToUi) :
    m_coreToUi(coreToUi), m_uiToCore(uiToCore)
{};

void EventManager::dispatchEvent()
{
    Event e = m_uiToCore.waitAndPop();

    switch (e.getType())
    {
    case Quit:
        notify(EventType::Quit);
        break;

    default:
        break;
    }
}

void EventManager::addListener(EventType type, IEventListener* listener)
{
    m_EventListenerMap[type].push_back(listener);
}

void EventManager::removeListener(IEventListener* listener, EventType type)
{
    if (type == None)
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

void EventManager::pushEvent(Event event)
{
    m_coreToUi.push(event);
}

void EventManager::notify(EventType type)
{
    auto it = m_EventListenerMap.find(type);

    if (it == m_EventListenerMap.end()) return;

    for (auto* listener : it->second)
    {
        listener->onEvent(type);
    }
}