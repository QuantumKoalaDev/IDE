#pragma once

#include <atomic>
#include <string>

#include <iostream>
#include <thread>

#include "EventSystem/ThreadSafeQueue/ThreadSafeQueue.h"
#include "EventSystem/Events/Event.h"

class Core
{
    ThreadSafeQueue<Event>& m_inQueue;
    ThreadSafeQueue<Event>& m_outQueue;
    std::atomic<bool>& m_running;

    public:
    Core(
        ThreadSafeQueue<Event>& in, 
        ThreadSafeQueue<Event>& out,
        std::atomic<bool>& run
    );
    ~Core() {}

    void run();
};