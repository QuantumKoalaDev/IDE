#pragma once

#include <atomic>
#include <memory>

#include "EventSystem/Events/Event.h"
#include <Core/EventSystem/EventManager/EventManager.h>
#include <Core/EventSystem/IEventListener.h>
#include "EventSystem/ThreadSafeQueue/ThreadSafeQueue.h"


/**
 * @class Core
 * @brief Core application class that manages the main event loop and listens for events.
 * 
 * The Core class holds an atomic running flag and an EventManager instance.
 * It listens for events, including Quit events, to control the application's lifecycle.
 */
class Core : public IEventListener
{
    std::atomic<bool>& m_running;

    std::shared_ptr<EventManager> m_eventManager;    

    public:
    /**
     * @brief Constructs the Core object.
     * 
     * Initializes the EventManager with the given input/output event queues,
     * registers the EventManager as a service, and registers itself as a listener for Quit events.
     * 
     * @param in Reference to the input event queue (UI to Core).
     * @param out Reference to the output event queue (Core to UI).
     * @param run Reference to an atomic boolean controlling the run state.
     */
    Core(
        ThreadSafeQueue<Event>& in, 
        ThreadSafeQueue<Event>& out,
        std::atomic<bool>& run
    );

    /**
     * @brief Destructor.
     * 
     * Removes this Core instance from the EventManager's listener list.
     */
    ~Core();


    /**
     * @brief Runs the main event loop.
     * 
     * Continuously dispatches events from the EventManager while the running flag is true.
     */
    void run();

    /**
     * @brief Event handler callback.
     * 
     * Called when an event is received. If the event type is Quit, sets the running flag to false to stop the loop.
     * 
     * @param type The event type received.
     */
    void onEvent(EventType type) override;
};