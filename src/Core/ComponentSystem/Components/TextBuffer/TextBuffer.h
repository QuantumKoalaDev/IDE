#pragma once

#include "Cursor.h"
#include <Core/ComponentSystem/Components/IComponent.h>
#include <Core/EventSystem/Events/Event.h>
#include <Core/EventSystem/Events/KeyboardEvent.h>

#include <memory>
#include <string>
#include <vector>

namespace Core::ComponentSystem
{
    /**
     * @enum CursorMovement
     * @brief Represents the possible directions the cursor can move within a TextBuffer.
     *
     * This enumeration is used to indicate the desired movement direction for cursor operations.
     *
     * - UP:    Move the cursor one line up.
     * - DOWN:  Move the cursor one line down.
     * - RIGHT: Move the cursor one character to the right.
     * - LEFT:  Move the cursor one character to the left.
     */
    enum CursorMovement
    {
        UP,
        DOWN,
        RIGHT,
        LEFT
    };

    /**
     * @class TextBuffer
     * @brief A component that holds and manages lines of text.
     *
     * Splits a given text content into separate lines and stores them internally.
     * Provides access to these lines by range.
     */
    class TextBuffer : public IComponent
    {
        size_t m_id;
        std::vector<std::string> m_lines;
        Core::ComponentSystem::Cursor m_cursor;

        std::vector<size_t> m_dirtyLines;

        void handleKeyboardCases(const Core::EventSystem::Events::KeyboardEvent& keyEv);

        void moveCursorUpToLineEnd();

        void pushEvent(EventType type, size_t lineId);

    public:
        /**
         * @brief Constructs a TextBuffer by splitting content into lines.
         * @param id Unique identifier for this TextBuffer.
         * @param content The full text content to be split into lines.
         */
        TextBuffer(size_t id, const std::string& content = "");

        /**
         * @brief Default destructor.
         */
        ~TextBuffer() {};

        /**
         * @brief Gets the unique ID of this TextBuffer.
         * @return The identifier as an unsigned int.
         */
        size_t getId() override;

        /**
         * @brief Gets the size of the TextBuffer in lines.
         * @return The size as an unsigend int.
         */
        size_t getSize();

        /**
         * @brief Retrieves lines of text in the range [start, end).
         *
         * Copies lines in the specified range into the provided vector.
         * If the requested range exceeds available lines, it adjusts accordingly.
         *
         * @param start The starting line index (inclusive).
         * @param end The ending line index (inclusive).
         * @param lines A vector to receive the requested lines.
         */
        void getLines(size_t start, size_t end, std::vector<std::string>& lines);

        /**
         * @brief Gets the cursor position.
         * @return The cursor position as Cursor.
         */
        Core::ComponentSystem::Cursor& getCursor();

        /**
         * @brief Sets the cursor position within the text buffer.
         *
         * Adjusts the cursor to the specified line and character index.
         * If the requested line or character is out of bounds, it clamps
         * the position to the nearest valid location.
         *
         * @param character The target character index within the line (0-based).
         * @param line The target line number (0-based).
        */
        void setCursor(size_t line, size_t character);

        /**
         * @brief Moves the cursor within the TextBuffer based on the specified movement direction.
         *
         * Adjusts the cursor's position according to the given movement:
         * - UP: Moves the cursor one line up (if not already at the first line).
         * - DOWN: Moves the cursor one line down (if not already at the last line).
         * - LEFT: Moves the cursor one character to the left.
         *         If at the start of a line, moves to the end of the previous line.
         * - RIGHT: Moves the cursor one character to the right.
         *          If at the end of a line, moves to the beginning of the next line.
         *
         * Cursor position is clamped to valid ranges, preventing it from going outside the buffer.
         *
         * @param movement The direction in which to move the cursor.
         */
        void moveCursor(CursorMovement movement);

        /**
         * @brief Inserts a character at the current cursor position in the TextBuffer.
         *
         * The character is inserted into the current line at the cursor's character index.
         * After insertion, the cursor is advanced by one position to the right.
         *
         * @param c The character to be inserted.
        */
        void addChar(char c);

        void addString(const std::string& str);

        void executeEvent(const Core::EventSystem::Events::Event& ev) override;
    };
}
