#pragma once

#include <Core/ServiceManagement/IService.h>
#include <Core/UiResources/Font/IFontRenderer.h>

#include <memory>
#include <vector>

namespace Core::UiResources::Font
{
	/**
	 * @class FontManager
	 * @brief Manages font renderer instances for different font sizes.
	 *
	 * The FontManager is responsible for storing, retrieving, and managing
	 * instances of IFontRenderer. It keeps track of font renderers by size
	 * and ensures that duplicate renderers for the same size are avoided.
	 *
	 * This class implements the IService interface so it can be registered
	 * and retrieved via the ServiceManager.
	 */
	class FontManager : public IService
	{
		std::vector<std::weak_ptr<IFontRenderer>> m_fontRendererList;

	public:
		/**
		 * @brief Constructs the FontManager and registers it with the ServiceManager.
		 *
		 * When constructed, this FontManager instance automatically registers itself
		 * as a service under the name "FontManager" via the ServiceManager.
		 * This allows other parts of the application to retrieve and use it
		 * without manually creating an instance.
		 */
		FontManager() {};

		/**
		 * @brief Default destructor.
		 */
		~FontManager() {};

		/**
		 * @brief Checks if a font renderer exists for the given font size.
		 *
		 * @param fontSize The font size to look for.
		 * @return True if a renderer for the specified size exists, false otherwise.
		 */
		bool hasRenderer(int fontSize) const;

		/**
		 * @brief Adds a new font renderer to the manager.
		 *
		 * If a renderer with the same font size already exists, the existing one
		 * is returned instead.
		 *
		 * @param renderer Shared pointer to the font renderer to add.
		 * @return A shared pointer to the added or existing font renderer.
		 */
		const std::shared_ptr<IFontRenderer> add(std::shared_ptr<IFontRenderer> renderer);

		/**
		 * @brief Retrieves the font renderer for the given font size.
		 *
		 * @param fontSize The size of the font renderer to retrieve.
		 * @return A shared pointer to the font renderer if found, nullptr otherwise.
		 */
		const std::shared_ptr<IFontRenderer> getRenderer(int fontSize);

	};
}
