#pragma once

#include <Core/UiResources/Containers/Color.h>

#include <string>

namespace Core::UiResources::Font
{
	/**
	 * @brief Interface for font rendering implementations.
	 *
	 * Provides a standard interface for rendering text with a specific font
	 * size and color. Implementations of this interface handle the actual
	 * drawing of text on the screen or render target.
	 */
	class IFontRenderer
	{
	public:
		/**
		 * @brief Default virtual destructor.
		 */
		virtual ~IFontRenderer() = default;

		/**
		 * @brief Retrieves the font size used by this renderer.
		 *
		 * @return The font size as an integer.
		 */
		virtual int getSize() = 0;
		
		 /**
		 * @brief Draws a string of text at the specified position and scale.
		 *
		 * @param text The text string to render.
		 * @param x The x-coordinate of the text position.
		 * @param y The y-coordinate of the text position.
		 * @param scale The scale factor for the text size.
		 * @param color The color to render the text in.
		 */
		virtual void drawText(const std::string& text, float x, float y, float scale, const Core::UiResources::Containers::Color& color) = 0;

	};
}
