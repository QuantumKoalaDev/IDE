#include "ComponentManager.h"

#include <algorithm>

ComponentManager::~ComponentManager()
{
    for (IComponent* comp : m_componentList)
    {
        delete comp;
        comp = nullptr;
    }
    m_componentList.clear();
}

const std::string& ComponentManager::getCurrentContext() const
{
    return m_currentContext;
}

void ComponentManager::setCurrentContext(std::string context, int id)
{
    m_currentContext = context;
    m_currentId = id;
}

int ComponentManager::addComponent(IComponent* comp, ComponentType type)
{
    m_componentList.push_back(comp);
    m_currentId++;

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