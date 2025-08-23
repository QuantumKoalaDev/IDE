#include "ComponentManager.h"

#include <Core/EventSystem/EventManager/EventManager.h>
#include <Core/EventSystem/Events/KeyboardEvent.h>
#include <Core/ServiceManagement/ServiceManager.h>

#include <algorithm>
#include <iostream>

ComponentManager::ComponentManager()
{
    auto opt = ServiceManager::getService("EventManager");

    if (!opt.has_value())
    {
        std::cerr << "EventManager for ComponentManger registration was not found!" << std::endl;
        return;
    }
    IService& ref = opt.value().get();
    EventManager& evMg = dynamic_cast<EventManager&>(ref);
    evMg.addListener(EventType::Keyboard, this);
}

ComponentManager::~ComponentManager()
{
    for (IComponent* comp : m_componentList)
    {
        delete comp;
        comp = nullptr;
    }
    m_componentList.clear();
}

unsigned int ComponentManager::getCurrentId() const
{
    return m_currentId;
}

const Context ComponentManager::getCurrentContext() const
{
    return m_currentContext;
}

void ComponentManager::setCurrentContext(Context context, int id)
{
    m_currentContext = context;

    if (id == -1) m_focused = nullptr;

    auto it = std::find_if(m_componentList.begin(), m_componentList.end(), [&](IComponent* comp)
        {
            return comp->getId() == id;
        }
    );

    if (it != m_componentList.end())
    {
        m_focused = *it;
    }
}

int ComponentManager::addComponent(IComponent* comp, ComponentType type)
{
    m_componentList.push_back(comp);
    m_currentId++;

    // TODO:
    // telling the EventManager to send a create<ComponentType / WidgetType> event
    // main ui part should already be created, but e.g. a TextBuffer needs a new CodeEditor Tab

    return comp->getId();
}

void ComponentManager::deleteComponent(unsigned int id)
{
    std::erase_if(m_componentList, [&](IComponent* comp)
    {
        if (comp->getId() == id)
        {
            delete comp;
            return true;
        }
        return false;
    }
    );
}

void ComponentManager::onEvent(const Core::EventSystem::Events::Event& event)
{
    m_currentContext = Context::CODEEDTOR;
    m_focused = m_componentList[0];
    // TODO:
    // Implementing KeybindingManger and including it here

    if (m_focused == nullptr) return;

    if (m_currentContext == Context::CODEEDTOR)
    {
        m_focused->executeEvent(event);
    }
}