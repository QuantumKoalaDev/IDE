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
    ThreadSafeQueue<std::shared_ptr<Event>> m_coreToUi;
    ThreadSafeQueue<std::shared_ptr<Event>> m_uiToCore;
    std::unordered_map<EventType, std::vector<IEventListener*>> m_EventListenerMap;

    /**
     * @brief Notify all listeners registered for a given event type.
     * @param event The event to notify listeners about.
     */
    void notify(std::shared_ptr<Event> event);

    public:
    /**
     * @brief Constructs an EventManager with empty thread-safe event queues.
     * 
     * Initializes the internal queues for core-to-UI and UI-to-core communication,
     * as well as the event listener registry. Events are stored and transferred
     * as shared pointers to avoid unnecessary copies easier processing later on.
     */
    EventManager();
    
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
    void removeListener(IEventListener* listener, EventType type = EventType::NoneEvent);

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
     * @brief Pushes an event into one of the event queues.
     * 
     * Transfers ownership of the event into the specified queue without copying.
     * The event will be processed later by the receiving thread when `dispatchEvent()` is called.
     * 
     * @param event A shard pointer to the event to push. Ownership is moved into the queue.
     * @param ui If true, the event is pushed to the core-to-UI queue;
     *           if false, the event is pushed to the UI-to-core queue. Default is true.
     */
    void pushEvent(std::shared_ptr<Event> event, bool ui = true);
};
