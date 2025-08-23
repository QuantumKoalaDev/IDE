#pragma once

#include <Core/ComponentSystem/Components/TextBuffer/Cursor.h>
#include <Core/EventSystem/EventManager/EventManager.h>
#include <Core/UiResources/Containers/Color.h>
#include <Core/UiResources/Font/IFontRenderer.h>
#include <Core/UiResources/Datastructures/OffsetVector/OffsetVector.h>

#include <Ui/Widgets/Widget.h>

#include <memory>
#include <vector>

namespace Ui::Widgets
{
	class Textbox : public Widget
	{
		std::shared_ptr<EventManager> m_eventManger;
		std::shared_ptr<Core::UiResources::Font::IFontRenderer> m_fontRenderer;
		Core::UiResources::Datastructures::OffsetVector m_viewPortLines;
		std::vector<int> m_viewPortLineIds;

		int m_width, m_height;

		Core::ComponentSystem::Cursor m_cursor;

		Core::UiResources::Containers::Color m_backgroundColor;
		Core::UiResources::Containers::Color m_fontColor;


		// center(x,y)
		// image => true / false
		// fontSize => in fontRenderer
		// outline => true/ false
		// border => true / false
		// outline + border can be represented by an enum => should be a struct with with and radius and implemented in Widget

		// relative positions are needed for later resizing



	public:
		Textbox(
			unsigned int componentId,
			int width,
			int height,
			int fontSize,
			const std::string& fontPath,
			Core::UiResources::Datastructures::OffsetVector startViewPort,
			Core::ComponentSystem::Cursor
		);

		~Textbox() {};

		void draw() override;
		void resize(int newHeight, int newWidth) override;
		void updateSingleLine(const Core::EventSystem::Events::TextEvents::SingleLineUpdateEvent& ev, EventType type) override;

		void update(size_t lineId, std::string& str);
	};
}

