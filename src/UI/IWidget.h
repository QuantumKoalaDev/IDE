#pragma once

class IWidget
{
    public:
        virtual ~IWidget() {};

        virtual void draw() = 0;
        virtual void onHover(int cursorX, int cursorY) = 0;
        virtual void onClick() = 0;
        virtual void resize(int windowHeight, int windowWidth) = 0;


        // Position in OpenGL coordinates
        // Draw evtl besser in einem zentralen renderer => draw(position, m_vao, m_program)
};