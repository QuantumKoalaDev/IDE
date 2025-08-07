#pragma once

#include <Core/EventSystem/ThreadSafeQueue/ThreadSafeQueue.h>
#include <Core/EventSystem/Events/Event.h>

#include <atomic>

class IDE
{
    ThreadSafeQueue<Event> m_uiToCore;
    ThreadSafeQueue<Event> m_coreToUi;
    std::atomic<bool> m_running;

    public:
    IDE();
    ~IDE();

    void start();
};