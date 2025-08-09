#include "Core.h"

Core::Core(
    ThreadSafeQueue<Event>& in, 
    ThreadSafeQueue<Event>& out,
    std::atomic<bool>& run
) : m_running(run), m_eventManager(EventManager(in, out))
{
    m_eventManager.addListener(EventType::Quit, this);
};

Core::~Core()
{
    m_eventManager.removeListener(this);
}

void Core::run()
{
    while (m_running)
    {
        m_eventManager.dispatchEvent();
    }
}

void Core::onEvent(EventType type)
{
    if (type == EventType::Quit) m_running = false;
}