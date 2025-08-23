#pragma once

#include <Core/EventSystem/Events/Event.h>
#include <Core/EventSystem/Events/EventType.h>

#include <Core/ComponentSystem/Components/TextBuffer/Cursor.h>
#include <Core/UiResources/Datastructures/OffsetVector/OffsetVector.h>

#include <string>
#include <vector>

namespace Core::EventSystem::Events::TextEvents
{
	struct CreateTextboxEvent
	{
		CreateTextboxEvent(
			size_t pComponentId,
			Core::UiResources::Datastructures::OffsetVector&& pViewPort,
			Core::ComponentSystem::Cursor pCursor
			) :
			componentId(pComponentId), viewPort(std::move(pViewPort)), cursor(pCursor)
		{}

		size_t componentId;
		Core::UiResources::Datastructures::OffsetVector viewPort;
		Core::ComponentSystem::Cursor cursor;
	};
}