#pragma once

namespace Core::UiResources::Containers
{
    /**
     * @brief Represents an RGB color.
     *
     * This struct stores the red, green, and blue components of a color
     * as floating-point values in the range [0.0, 1.0].
     */
    struct Color
    {
        /**
         * @brief Constructs a Color from individual RGB components.
         *
         * @param red The red component (0.0 - 1.0).
         * @param green The green component (0.0 - 1.0).
         * @param blue The blue component (0.0 - 1.0).
         */
        Color(float red, float green, float blue) : r(red), g(green), b(blue) {};

        float r;
        float g;
        float b;
    };
}
