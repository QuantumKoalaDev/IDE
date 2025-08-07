#include "Core.h"

Core::Core(
    ThreadSafeQueue<Event>& in, 
    ThreadSafeQueue<Event>& out,
    std::atomic<bool>& run
) : m_inQueue(in), m_outQueue(out), m_running(run)
{};

void Core::run()
{
    while (m_running)
    {
        Event e = m_inQueue.waitAndPop();

        if (e.getType() == EventType::Quit)
        {
            m_running = false;
            break;
        }
    }
}