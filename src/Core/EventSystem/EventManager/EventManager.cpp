#include "EventManager.h"

EventManager::EventManager() {};

void EventManager::dispatchEvent(bool ui)
{
    std::unique_ptr<Event> e;
    if (!ui) e = m_uiToCore.waitAndPop();
    else e = m_coreToUi.waitAndPop();
    notify(e.get()->getType());
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

void EventManager::pushEvent(std::unique_ptr<Event> event, bool ui)
{

    if (ui) m_coreToUi.push(std::move(event));
    else m_uiToCore.push(std::move(event));
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