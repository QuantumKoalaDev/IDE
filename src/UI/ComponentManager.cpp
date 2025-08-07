#include "ComponentManager.h"
#include "EventSystem/ResizeEvent.h"

#include "iostream"

ComponentManager::ComponentManager(std::vector<IWidget*> componentList) : m_componentList(componentList), m_parent(nullptr), m_eventManager(EventManager())
{
	m_eventManager.registerListener(this, EventType::Resize);
}

ComponentManager::~ComponentManager()
{
	for (IWidget* widget : m_componentList)
	{
		delete widget;
	}
	m_componentList.clear();

}

void ComponentManager::addComponent(IWidget* widget)
{
	m_componentList.push_back(widget);
}

void ComponentManager::render()
{
	for (IWidget* widget : m_componentList)
	{
		widget->draw();
	}
}

void ComponentManager::setParent(OpenGLWindow* window)
{
	m_parent = window;
}

void ComponentManager::onEvent(Event& event)
{
	if (event.getEventType() != EventType::Resize) return;

	ResizeEvent& resEv = dynamic_cast<ResizeEvent&>(event);

	for (IWidget* widget : m_componentList)
	{
		widget->resize(resEv.getHeight(), resEv.getWidth());
	}
}

EventManager& ComponentManager::getEventManager()
{
	return m_eventManager;
}