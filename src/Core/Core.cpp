#include "Core.h"

#include <Core/ServiceManagement/ServiceManager.h>

Core::Core(
    ThreadSafeQueue<Event>& in, 
    ThreadSafeQueue<Event>& out,
    std::atomic<bool>& run
) : m_running(run), m_eventManager(std::make_shared<EventManager>(in, out))
{
    ServiceManager::registerService("EventManager", m_eventManager);
    m_eventManager.get()->addListener(EventType::Quit, this);
};

Core::~Core()
{
    m_eventManager.get()->removeListener(this);
}

void Core::run()
{
    while (m_running)
    {
        m_eventManager.get()->dispatchEvent();
    }
}

void Core::onEvent(EventType type)
{
    if (type == EventType::Quit) m_running = false;
}