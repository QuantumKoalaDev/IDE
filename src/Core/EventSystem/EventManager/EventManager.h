#pragma once

#include <Core/EventSystem/Events/Event.h>
#include <Core/EventSystem/Events/EventType.h>
#include <Core/EventSystem/IEventListener.h>
#include <Core/EventSystem/ThreadSafeQueue/ThreadSafeQueue.h>

#include <unordered_map>
#include <vector>

/**
 * @class EventManager
 * @brief Manages event dispatching between core and UI threads, handling event listeners and queues.
 * 
 * This class handles adding/removing event listeners, dispatching events received from the UI thread,
 * pushing events to the UI thread, and notifying listeners about specific event types.
 */
class EventManager
{
    ThreadSafeQueue<Event>& m_coreToUi;
    ThreadSafeQueue<Event>& m_uiToCore;
    std::unordered_map<EventType, std::vector<IEventListener*>> m_EventListenerMap;

    /**
     * @brief Notify all listeners registered for a given event type.
     * @param type The event type to notify listeners about.
     */
    void notify(EventType type);

    public:
    /**
     * @brief Constructs an EventManager with references to thread-safe event queues.
     * @param uiToCore Reference to the queue of events from UI to core.
     * @param coreToUi Reference to the queue of events from core to UI.
     */
    EventManager(ThreadSafeQueue<Event>& uiToCore, ThreadSafeQueue<Event>& coreToUi);
    
    /**
     * @brief Default destructor.
     */
    ~EventManager() {};

    /**
     * @brief Registers a listener for a specific event type.
     * @param type The event type the listener is interested in.
     * @param listener Pointer to the listener to add.
     */
    void addListener(EventType type, IEventListener* listener);
    
    /**
     * @brief Removes a listener from one or all event types.
     * @param listener Pointer to the listener to remove.
     * @param type The event type to remove the listener from. Defaults to None to remove from all.
     */
    void removeListener(IEventListener* listener, EventType type = None);

    /**
     * @brief Dispatches an event received from the UI queue.
     * 
     * Waits for an event from the UI queue and processes it, notifying the appropriate listeners.
     */
    void dispatchEvent();

    /**
     * @brief Pushes an event to the core-to-UI queue.
     * @param event The event to push.
     */
    void pushEvent(Event event);
};
