#pragma once

#include "Event.h"
#include "EventType.h"

/**
 * @class ResizeEvent
 * @brief Represents a window resize event.
 *
 * Contains the new width and height of the resized window.
 */
class ResizeEvent : public Event
{
	int m_width;
	int m_height;

	public:
	/**
	 * @class ResizeEvent
	 * @brief Represents a window resize event.
	 *
	 * Contains the new width and height of the resized window.
	 */
	ResizeEvent(int width, int height) : m_width(width), m_height(height), Event(EventType::Resize)
	{}
	/**
	 * @brief Destructor.
	 */
	~ResizeEvent() {}

	/**
	 * @brief Returns the new height of the window.
	 * @return Height in pixels.
	 */
	int getHeight() const { return m_height; }

	/**
	 * @brief Returns the new width of the window.
	 * @return Width in pixels.
	 */
	int getWidht() const { return m_width; }
};