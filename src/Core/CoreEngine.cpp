#include "CoreEngine.h"

#include <Core/ServiceManagement/ServiceManager.h>
#include <Core/UiResources/Font/FontManager/FontManager.h>

#include <Core/ComponentSystem/ComponentManager/ComponentManager.h>
#include <Core/ComponentSystem/Components/TextBuffer/TextBuffer.h>

#include <memory>

using Core::CoreEngine;
using Core::UiResources::Font::FontManager;


CoreEngine::CoreEngine(
    std::atomic<bool>& run
) : m_running(run), m_eventManager(std::make_shared<EventManager>())
{
    ServiceManager::registerService("EventManager", m_eventManager);
    ServiceManager::registerService("FontManager", std::make_shared<FontManager>());

    m_eventManager.get()->addListener(EventType::Quit, this);
};

CoreEngine::~CoreEngine()
{
    m_eventManager.get()->removeListener(this);
}

void CoreEngine::run()
{
    ComponentManager cmpMg;
    cmpMg.addComponent(new Core::ComponentSystem::TextBuffer(cmpMg.getCurrentId(), "Hello World!"), ComponentType::TextBuffer);

    while (m_running)
    {
        m_eventManager.get()->dispatchEvent();
    }
}

void CoreEngine::onEvent(const Core::EventSystem::Events::Event& event)
{
    if (event.type == EventType::Quit) m_running = false;
}