#pragma once

#include <Core/EventSystem/ThreadSafeQueue/ThreadSafeQueue.h>
#include <Core/EventSystem/Events/Event.h>

#include <atomic>

class IDE
{
    std::atomic<bool> m_running;

    public:
    IDE();
    ~IDE();

    void start();
};