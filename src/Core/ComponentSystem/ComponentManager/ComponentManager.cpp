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

int ComponentManager::addComponent(IComponent* comp, ComponentType type)
{
    m_componentList.push_back(comp);
    m_currentId++;

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