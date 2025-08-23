#pragma once

#include "Event.h"

namespace Core::EventSystem::Events
{
	struct KeyboardEvent
	{
		KeyboardEvent(unsigned int keycode, bool shift, bool ctrl): keycode(keycode), shift(shift), ctrl(ctrl)
		{}

		unsigned int keycode;
		bool shift;
		bool ctrl;
	};
}
