#pragma once

#include "Event.h"

class KeyboardEvent : public Event
{
public:
	KeyboardEvent(int keyCode, bool shift = false, bool ctrl = false) : m_keyCode(keyCode), m_shift(shift), m_ctrl(ctrl), Event(EventType::Keyboard)
	{}

	~KeyboardEvent() {};

	EventType getType() const { return m_eventType; }
	int getKeyCode() const { return m_keyCode; }
	bool isShift() const { return m_shift; }
	bool isCtrl() const { return m_ctrl; }

private:
	int m_keyCode;
	bool m_shift;
	bool m_ctrl;
};