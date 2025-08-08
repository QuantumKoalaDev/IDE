#include "TextBuffer.h"

TextBuffer::TextBuffer(unsigned int id, const std::string& content) : m_id(id), m_lines({}), 
    m_cursor(Cursor{0, 0})
{
    std::string currentLine = "";

    for (char c : content)
    {
        if (c != '\n')
        {
            currentLine += c;
            continue;
        }

        m_lines.push_back(currentLine);
        currentLine = "";
    }
}

unsigned int TextBuffer::getId()
{
    return m_id;
}

unsigned int TextBuffer::getSize()
{
    return m_lines.size();
}

void TextBuffer::getLines(unsigned int start, unsigned int end, std::vector<std::string>& lines)
{
    if (m_lines.size() < start) return;
    if (m_lines.size() <= end) end = lines.size() - 1;


    lines.reserve(end - start);

    for (unsigned int i = start; i <= end; i++)
    {
        lines.emplace_back(m_lines[i]);
    }
}

void TextBuffer::setCursor(unsigned int line, unsigned int character)
{
    if (m_lines.size() < line) line = m_lines.size() - 1;
    if (m_lines[line].size() < character) character = m_lines[line].size() - 1;

    m_cursor.line = line;
    m_cursor.character = character;
}

void TextBuffer::moveCursor(CursorMovement movement)
{
    switch (movement)
    {
    case UP:
        if (m_cursor.line == 0) return;
        m_cursor.line -= 1;
        break;
    
    case DOWN:
        if (m_cursor.line == m_lines.size() - 1) return;
        m_cursor.line += 1;
        break;

    case LEFT:
        if (m_cursor.character == 0)
        {
            moveCursor(UP);
            return;
        }
        m_cursor.character -= 1;
        break;

    case RIGHT:
        unsigned int currentLine = m_cursor.line;
        if (m_cursor.character == m_lines[m_cursor.character].size() - 1)
        {
            moveCursor(DOWN);
            if (currentLine != m_cursor.line) m_cursor.character = 0;
            return;
        }
        m_cursor.character -= 1;
        break;
    }
}

void TextBuffer::addChar(char c)
{
    std::string& line = m_lines[m_cursor.line];
    auto it = line.begin() + m_cursor.character;
    line.insert(it, c);

    m_cursor.character++;
}

Cursor& TextBuffer::getCursor()
{
    return m_cursor;
}