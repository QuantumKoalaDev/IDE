#pragma once

/**
 * @brief Represents the position of a cursor within a text buffer.
 * 
 * Contains zero-based indices for line and character position.
 */
struct Cursor
{
    unsigned int line;
    unsigned int character;
};
