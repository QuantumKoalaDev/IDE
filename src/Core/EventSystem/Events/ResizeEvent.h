#pragma once
namespace Core::EventSystem::Events
{
	struct ResizeEvent
	{
		ResizeEvent(int width, int height): m_width(width), m_height(height) {}

		int m_width;
		int m_height;
	};
}