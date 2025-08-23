#include "FontManager.h"

#include <Core/ServiceManagement/ServiceManager.h>

#include <algorithm>
#include <iostream>

using Core::UiResources::Font::FontManager;
using Core::UiResources::Font::IFontRenderer;


bool FontManager::hasRenderer(int fontSize) const
{
	auto it = std::find_if(m_fontRendererList.begin(), m_fontRendererList.end(), [fontSize](std::weak_ptr<IFontRenderer> fr)
		{
			std::shared_ptr<IFontRenderer> frShPtr = fr.lock();
			return frShPtr->getSize() == fontSize;
		}
	);

	return it != m_fontRendererList.end();
}

const std::shared_ptr<IFontRenderer> FontManager::add(std::shared_ptr<IFontRenderer> renderer)
{
	int fontSize = renderer->getSize();
	if (hasRenderer(fontSize)) return getRenderer(fontSize);

	m_fontRendererList.push_back(renderer);
	return renderer;
}

const std::shared_ptr<IFontRenderer> FontManager::getRenderer(int fontSize)
{
	std::erase_if(m_fontRendererList, [](const std::weak_ptr<IFontRenderer>& ptr)
		{
			return ptr.expired();
		}
	);

	auto it = std::find_if(m_fontRendererList.begin(), m_fontRendererList.end(), [fontSize](std::weak_ptr<IFontRenderer> fr)
		{
			if (std::shared_ptr<IFontRenderer> sp = fr.lock()) return sp->getSize() == fontSize;
			return false;
		}
	);

	if (it != m_fontRendererList.end()) return it->lock();

	return nullptr;
}

