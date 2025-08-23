#pragma once

namespace Core::ComponentSystem
{
    /**
     * @brief Represents the position of a cursor within a text buffer.
     *
     * Contains zero-based indices for line and character position.
     */
    struct Cursor
    {
        size_t line;
        size_t character;
    };
}

