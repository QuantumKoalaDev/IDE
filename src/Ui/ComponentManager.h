#pragma once

#include <vector>
#include "memory"

#include "EventSystem/EventManager.h"
#include "Interfaces/IInputListener.h"
#include "Interfaces/IWidget.h"

class OpenGLWindow;

class ComponentManager : public IInputListener
{
public:
	///  @brief Constructs a ComponentManager with an optional initial list of widgets.
	/// @param componentList: A list of widgets to be managed initially.
	ComponentManager(std::vector<IWidget*> componentList = {});

	/// @brief Destructor
	~ComponentManager();

	EventManager& getEventManager();

	void addComponent(IWidget* widget);

	void render();

	void setParent(OpenGLWindow* window);

	void onEvent(Event& event) override;

private:
	std::vector<IWidget*> m_componentList;
	const OpenGLWindow* m_parent;
	EventManager m_eventManager;
};