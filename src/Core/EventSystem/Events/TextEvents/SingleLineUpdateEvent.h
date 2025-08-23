#pragma once

#include <Core/EventSystem/Events/ComponentEvents/ComponentEvent.h>
#include <Core/EventSystem/Events/EventType.h>
#include <Core/ComponentSystem/Components/TextBuffer/Cursor.h>

namespace Core::EventSystem::Events::TextEvents
{
	struct SingleLineUpdateEvent
	{
		SingleLineUpdateEvent(size_t componentId, std::string line, size_t lineId, Core::ComponentSystem::Cursor cursor):
			componentId(componentId), line(std::move(line)), lineId(lineId), cursor(cursor)
		{}

		size_t componentId;
		std::string line;
		size_t lineId;
		Core::ComponentSystem::Cursor cursor;
	};
}