#include "Textbox.h"

#include <iostream>
#include <exception>


Textbox::Textbox(FontRenderer* renderer,int windowWidth, int windowHeight, float fontSize, std::string content) :
    m_renderer(renderer), m_fontSize(fontSize), m_windowWidth(windowWidth), m_windowHeight(windowHeight)
{
    std::string currentLine = "";

    for (char c : content)
    {

        if (c == '\n')
        {
            m_lines.push_back(currentLine);
            currentLine = "";
            continue;
        }

        currentLine += c;
    }

    m_lines.push_back(currentLine);
}

Textbox::~Textbox() {}


// === Getter & Setter ===
bool Textbox::isFocused()
{
    return m_focused;
}

void Textbox::setFocus(bool focus)
{
    m_focused = focus;
}

unsigned int Textbox::getLength()
{
    return m_lines.size();
}

int Textbox::getCurrentLine()
{
    return m_currentLine;
}

void Textbox::setCurrentLine(int line)
{
    if (line >= getLength()) throw std::invalid_argument("Textbox::setCurrentLine: line is to big");
    m_currentLine = line;
}


// === Interface Methods
void Textbox::draw()
{
    float lastLine = static_cast<float>(m_windowHeight) - 50.f;

    for (size_t i = 0; i < m_lines.size(); i++)
    {
        m_renderer->renderText(m_lines[i], 1.f, lastLine, m_fontSize / m_renderer->getFontSize(), Color(1.f, 1.f, 1.f));
        lastLine -= m_renderer->getFontSize() * 1.f;
    }
}

void Textbox::resize(int windowHeight, int windowWidth)
{
    std::cout << "Textbox Resized" << std::endl;
    m_windowHeight = windowHeight;
    m_windowWidth = windowWidth;
}

// === Class-Methods ===
void Textbox::write(char* c)
{
    if (strcmp(c, "Down") == 0)
    {
        if (m_currentLine < m_lines.size() - 1) m_currentLine += 1;
        std::cout << "Current Line: " << m_currentLine << std::endl;
        std::cout << "vec Size: " << m_lines.size() << std::endl;
        return;
    }

    if (strcmp(c, "Up") == 0)
    {
        if (m_currentLine > 0) m_currentLine -= 1;
        return;
    }

    m_lines[m_currentLine] += c;
    std::cout << "Written: " << c << "; Line: " << m_lines[m_currentLine] << std::endl;
}
