#pragma once

#include <atomic>
#include <string>
#include <memory>

#include <iostream>
#include <thread>

#include "EventSystem/ThreadSafeQueue/ThreadSafeQueue.h"
#include "EventSystem/Events/Event.h"
#include <Core/EventSystem/EventManager/EventManager.h>
#include <Core/EventSystem/IEventListener.h>

class Core : public IEventListener
{
    std::atomic<bool>& m_running;

    std::shared_ptr<EventManager> m_eventManager;    

    public:
    Core(
        ThreadSafeQueue<Event>& in, 
        ThreadSafeQueue<Event>& out,
        std::atomic<bool>& run
    );
    ~Core();

    void run();

    void onEvent(EventType type) override;
};