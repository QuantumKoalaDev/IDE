//#pragma once
//
//#include <Core/EventSystem/Events/Event.h>
//#include <Core/EventSystem/Events/EventType.h>
//
//class ComponentEvent : public Event
//{
//	size_t m_componentId;
//
//	public:
//		ComponentEvent(size_t componentId, EventType type) : m_componentId(componentId), Event(type)
//		{}
//
//		~ComponentEvent() {}
//
//		size_t getComponentId() const { return m_componentId; }
//
//};