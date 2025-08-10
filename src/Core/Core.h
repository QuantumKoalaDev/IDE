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
     * Initializes the EventManager, registers it as a service,
     * and registers this Core instance as a listener for Quit events.
     * 
     * @param run Reference to an atomic boolean controlling the application's running state.
     */
    Core(std::atomic<bool>& run);

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
     * @param event The event received.
     */
    void onEvent(std::shared_ptr<Event> event) override;
};