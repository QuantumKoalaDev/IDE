#pragma once

#include "Event.h"

class ResizeEvent : public Event
{
public:
	ResizeEvent(int width, int height) : m_width(width), m_height(height), Event(EventType::Resize) {};
	~ResizeEvent() {}

	EventType getEventType() const override { return m_eventType; }
	int getKeyCode() const override { return -1; }

	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }

private:
	int m_width;
	int m_height;
};