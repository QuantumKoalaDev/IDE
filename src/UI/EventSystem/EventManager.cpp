#include "EventManager.h"
#include "../Interfaces/IInputListener.h"

EventManager::~EventManager()
{
	for (Event* event : m_eventQueue)
	{
		delete event;
	}
	m_eventQueue.clear();
}

void EventManager::addEvents(Event* event)
{
	m_eventQueue.push_back(event);
}

void EventManager::registerListener(IInputListener* listener, EventType type)
{
	m_listeners[type].push_back(listener);
}

void EventManager::unregisterListener(IInputListener* listener)
{
	for (auto& [key, vec] : m_listeners)
	{
		vec.erase(std::remove(vec.begin(), vec.end(), listener), vec.end());
	}
}

void EventManager::dispatchEvents()
{
	for (Event* event : m_eventQueue)
	{
		Event& eventRef = *event;

		auto it = m_listeners.find(eventRef.getEventType());

		if (it != m_listeners.end())
		{
			for (auto* listener : it->second)
			{
				listener->onEvent(eventRef);
			}
		}
		delete event;
	}
	m_eventQueue.clear();
}