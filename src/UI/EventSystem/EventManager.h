#pragma once

#include "Event.h"
#include "EventTypes.h"

#include <vector>
#include <unordered_map>

class IInputListener;

class EventManager
{
public:
	/// @brief Default constructor for EventManager.
	EventManager() {};
	/// @brief Default destructor for EventManager.
	~EventManager();

	/// @brief Registers a listener for a specific key code.
	/// @param listener Pointer to the input listener instance.
	/// @param keyCode The key code the listener should be notified for.
	void registerListener(IInputListener* listener, EventType type);
	
	/// @brief Unregisters a listener from all key codes.
	/// @param listener Pointer to the listener to remove.
	void unregisterListener(IInputListener* listener);

	/// @brief Dispatches all queued events to the appropriate listeners.
	///
	/// This method iterates through the event queue and calls the
	/// handleEvent method of all listeners registered to the corresponding key.
	/// Should be called once per update loop.
	void dispatchEvents();

	/// @brief Adds an event to the event queue.
	/// @param event The input event to queue.
	void addEvents(Event* event);

private:
	std::unordered_map<EventType, std::vector<IInputListener*>> m_listeners;
	std::vector<Event*> m_eventQueue;
};