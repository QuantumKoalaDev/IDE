#pragma once

namespace Core::EventSystem::Events
{
	struct MouseEvent
	{
		MouseEvent(int x, int y, int keyCode) : x(x), y(y), keyCode(keyCode) {}

		int x;
		int y;
		int keyCode;
	};
}
