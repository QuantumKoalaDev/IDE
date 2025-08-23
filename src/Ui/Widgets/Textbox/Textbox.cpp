#include "Textbox.h"

#include <Core/ServiceManagement/ServiceManager.h>
#include <Core/EventSystem/Events/TextEvents/SingleLineUpdateEvent.h>
#include <Core/UiResources/Font/FontManager/FontManager.h>
#include <Core/UiResources/Font/IFontRenderer.h>

#include <Ui/Renderer/FontRenderer/FontRenderer.h>

#include <iostream>

#include <chrono>

using Core::ComponentSystem::Cursor;
using Core::EventSystem::Events::TextEvents::SingleLineUpdateEvent;
using Core::UiResources::Containers::Color;
using Core::UiResources::Font::FontManager;
using Core::UiResources::Font::IFontRenderer;
using Core::UiResources::Datastructures::OffsetVector;

using Ui::Widgets::Textbox;
using Ui::Renderer::FontRenderer;


Textbox::Textbox(
	unsigned int componentId,
	int width,
	int height,
	int fontSize,
	const std::string& fontPath,
	OffsetVector startViewPort,
	Cursor cursor
) 
	:	m_viewPortLines(std::move(startViewPort)),
		Widget(componentId), 
		m_backgroundColor(Color(0.f, 0.f, 1.f)),
		m_fontColor(Color(1.f, 1.f, 1.f)),
		m_width(width), m_height(height),
		m_cursor(cursor)
{
	auto opt = ServiceManager::getService("FontManager");

	if (!opt.has_value())
	{
		std::cerr << "FontManager could not be loaded in Textbox with id " << componentId << std::endl;
		return;
	}

	IService& ref = opt.value().get();
	FontManager& ftMg = dynamic_cast<FontManager&>(ref);

	bool hasRenderer = ftMg.hasRenderer(fontSize);

	m_fontRenderer = hasRenderer ? ftMg.getRenderer(fontSize) : ftMg.add(std::make_shared<FontRenderer>(fontPath.c_str(), fontSize));
}

void Textbox::draw()
{
	float lastLine = m_height - 50.f;
	int fontSize = m_fontRenderer->getSize();


	for (std::string line : m_viewPortLines.getLines())
	{
		m_fontRenderer->drawText(line, 0.f, lastLine, 1.f, m_fontColor);
		lastLine -= fontSize * 1.f;
	}
}

void Textbox::resize(int newWidht, int newHeight)
{
	std::shared_ptr<FontRenderer> renderer = std::dynamic_pointer_cast<FontRenderer>(m_fontRenderer);
	renderer->resize(newWidht, newHeight);
	// TODO
}

void Textbox::updateSingleLine(const SingleLineUpdateEvent& ev, EventType type)
{
	switch (type)
	{
		case EventType::ReplaceTextLine:
		{
			m_viewPortLines.replaceLine(ev.line, ev.lineId);
			break;
		}
		case EventType::InsertTextLine:
		{
			m_viewPortLines.addLine(ev.line, ev.lineId);
			break;
		}
	}

	std::cout << "Wrote string to viewport: " << ev.line << " " << std::chrono::system_clock::now() << '\n';
}

void Textbox::update(size_t lineId, std::string& str)
{
	m_viewPortLines.replaceLine(str, lineId);
}