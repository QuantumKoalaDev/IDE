#include "TextBuffer.h"

#include <Core/Constants/Keymap.h>
#include <Core/EventSystem/Events/Event.h>
#include <Core/EventSystem/Events/KeyboardEvent.h>
#include <Core/EventSystem/Events/TextEvents/CreateTextboxEvent.h>
#include <Core//EventSystem/Events//TextEvents/SingleLineUpdateEvent.h>
#include <Core/EventSystem/EventManager/EventManager.h>
#include <Core/UiResources/Datastructures/OffsetVector/OffsetVector.h>
#include <Core/ServiceManagement/IService.h>
#include <Core/ServiceManagement/ServiceManager.h>


#include <iostream>

#include <chrono>

using Core::ComponentSystem::Cursor;
using Core::ComponentSystem::TextBuffer;
using Core::EventSystem::Events::Event;
using Core::EventSystem::Events::TextEvents::CreateTextboxEvent;
using Core::EventSystem::Events::TextEvents::SingleLineUpdateEvent;
using Core::UiResources::Datastructures::OffsetVector;


TextBuffer::TextBuffer(size_t id, const std::string& content) : m_id(id), m_lines({}),
    m_cursor(Cursor{0, 0}), m_dirtyLines({})
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

    m_lines.push_back(currentLine);
    currentLine = "";
    
    size_t start = m_cursor.line > 30 ? m_cursor.line - 30 : 0;
    size_t end = m_cursor.line + 30 < m_lines.size() - 1 ? m_cursor.line + 30 : m_lines.size() - 1;

    std::vector<std::string> sendingLines;
    sendingLines.reserve(end - start + 1);

    for (size_t counter = start; counter <= end; counter++)
    {
        sendingLines.emplace_back(m_lines[start]);
    }

    auto opt = ServiceManager::getService("EventManager");
    if (!opt.has_value()) throw std::runtime_error("TextBuffer: EventManager not availiable");

    IService& ref = opt.value().get();
    EventManager& evMg = dynamic_cast<EventManager&>(opt.value().get());

    evMg.pushEvent(Event(EventType::CreateTextbox, CreateTextboxEvent(id, OffsetVector(std::move(sendingLines), start), m_cursor)));
}

size_t TextBuffer::getId()
{
    return m_id;
}

size_t TextBuffer::getSize()
{
    return m_lines.size();
}

void TextBuffer::getLines(size_t start, size_t end, std::vector<std::string>& lines)
{
    if (m_lines.size() < start) return;
    if (m_lines.size() <= end) end = lines.size() - 1;


    lines.reserve(end - start);

    for (unsigned int i = start; i <= end; i++)
    {
        lines.emplace_back(m_lines[i]);
    }
}

void TextBuffer::setCursor(size_t line, size_t character)
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
        if (m_cursor.character == m_lines[m_cursor.line].size() - 1)
        {
            moveCursor(DOWN);
            if (currentLine != m_cursor.line) m_cursor.character = 0;
            return;
        }
        m_cursor.character += 1;
        break;
    }
}

void TextBuffer::addChar(char c)
{
    std::string& line = m_lines[m_cursor.line];
    auto it = line.begin() + m_cursor.character;
    line.insert(it, c);

    m_dirtyLines.push_back(m_cursor.line);
    m_cursor.character++;

    pushEvent(EventType::ReplaceTextLine, m_cursor.line);
}

void TextBuffer::addString(const std::string& str)
{

    std::string& line = m_lines[m_cursor.line];

    if (m_cursor.character >= line.size()) m_cursor.character = line.size();

    line.insert(m_cursor.character, str);

    m_dirtyLines.push_back(m_cursor.line);
    pushEvent(EventType::ReplaceTextLine, m_cursor.line);

    std::cout << "Wrote string: " << str << "to buffer " << std::chrono::system_clock::now() << '\n';
}

Cursor& TextBuffer::getCursor()
{
    return m_cursor;
}

void TextBuffer::executeEvent(const Core::EventSystem::Events::Event& ev)
{
    m_dirtyLines.clear();

    std::visit([&](auto&& concreteEvent)
    {
        using T = std::decay_t<decltype(concreteEvent)>;

        if constexpr (std::is_same_v < T, Core::EventSystem::Events::KeyboardEvent>)
        {
            handleKeyboardCases(concreteEvent);
        }
    }, ev.event);

    //switch (ev.type)
    //{
    //    case EventType::Keyboard:
    //    {
    //        std::shared_ptr<KeyboardEvent> keyEv = std::dynamic_pointer_cast<KeyboardEvent>(ev);
    //        handleKeyboardCases(keyEv);
    //    }
    //}
}

void TextBuffer::handleKeyboardCases(const Core::EventSystem::Events::KeyboardEvent& keyEv)
{
    switch (keyEv.keycode)
    {
        case Keymapping::ID_ENTER:
        {
            if (m_cursor.line == m_lines.size() - 1) m_lines.push_back(" ");
            else m_lines.insert(m_lines.begin() + m_cursor.line + 1, " ");

            moveCursor(CursorMovement::DOWN);
            m_cursor.character = 0;

            m_dirtyLines.push_back(m_cursor.line);
            pushEvent(EventType::InsertTextLine, m_cursor.line);

            break;
        }
        case Keymapping::ID_BACKSPACE:
        {
            if (m_cursor.line == 0 && m_cursor.character == 0) return;

            if (m_cursor.character == 0)
            {
                m_lines.erase(m_lines.begin() + m_cursor.line);
                moveCursorUpToLineEnd();

                return;
            }

            std::string& line = m_lines[m_cursor.line];
            line.erase(line.begin() + m_cursor.character - 1);
            m_dirtyLines.push_back(m_cursor.line);
            moveCursor(CursorMovement::LEFT);
            break;
        }
        case Keymapping::ID_ARROW_UP:
            moveCursor(CursorMovement::UP);
            break;
        case Keymapping::ID_ARROW_DOWN:
            moveCursor(CursorMovement::DOWN);
            break;
        case Keymapping::ID_ARROW_RIGHT:
            moveCursor(CursorMovement::RIGHT);
            break;
        case Keymapping::ID_ARROW_LEFT:
            moveCursor(CursorMovement::LEFT);
            break;
        case Keymapping::ID_SPACE:
            addString(" ");
            moveCursor(CursorMovement::RIGHT);
            break;
        default:
            addString(Keymapping::InternalToString(keyEv.keycode));
            m_dirtyLines.push_back(m_cursor.line);
            moveCursor(CursorMovement::RIGHT);
    }

    //std::cout << m_lines[m_cursor.line] << std::endl;
}

void TextBuffer::moveCursorUpToLineEnd()
{
    if (m_cursor.line == 0) return;

    unsigned int newLine = m_cursor.line - 1;
    unsigned int newChar = m_lines[newLine].empty() ? 0 : m_lines[newLine].size() - 1;

    setCursor(newLine, newChar);
}

void TextBuffer::pushEvent(EventType type, size_t lineId)
{
    auto opt = ServiceManager::getService("EventManager");

    if (!opt.has_value()) return;
    IService& ref = opt.value().get();
    EventManager& evMg = dynamic_cast<EventManager&>(ref);

    if (type == ReplaceTextLine && m_dirtyLines.size() == 1)
    {
        std::string line = m_lines[m_dirtyLines[0]];
        evMg.pushEvent(Event(type, SingleLineUpdateEvent(m_id, std::move(line), lineId, m_cursor)));

    }

    if (type == EventType::InsertTextLine && m_dirtyLines.size() == 1)
    {
        std::string line = m_lines[m_dirtyLines[0]];
        evMg.pushEvent(Event(type, SingleLineUpdateEvent(m_id, std::move(line), lineId, m_cursor)));
    }
}