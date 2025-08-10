#pragma once

#include <Core/EventSystem/Events/Event.h>
#include <Core/EventSystem/Events/EventType.h>
#include <Core/EventSystem/IEventListener.h>
#include <Core/EventSystem/ThreadSafeQueue/ThreadSafeQueue.h>
#include <Core/ServiceManagement/IService.h>

#include <unordered_map>
#include <vector>

/**
 * @class EventManager
 * @brief Manages event dispatching between core and UI threads, handling event listeners and queues.
 * 
 * This class handles adding/removing event listeners, dispatching events received from the UI thread,
 * pushing events to the UI thread, and notifying listeners about specific event types.
 */
class EventManager : public IService
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
     * @brief Dispatches an event received from one of the event queues.
     * 
     * Waits for an event from either the UI-to-core queue or the core-to-UI queue, depending on the parameter.
     * After receiving the event, it notifies all registered listeners for that event type.
     * 
     * @param ui If true, waits and processes events from the core-to-UI queue; 
     *             if false, from the UI-to-core queue. Default is false.
     */
    void dispatchEvent(bool ui = false);


    /**
     * @brief Pushes an event to one of the event queues.
     * 
     * Depending on the parameter, the event is pushed either to the core-to-UI queue or the UI-to-core queue.
     * 
     * @param event The event to push.
     * @param ui If true, pushes the event to the core-to-UI queue;
     *           if false, pushes it to the UI-to-core queue. Default is true.
     */
    void pushEvent(Event event, bool ui = true);
};
