#pragma once

#include "../IWidget.h"
#include "../Renderer/FontRenderer/FontRenderer.h"


#include <string>
#include <vector>

class Textbox : public IWidget
{
    public:
        Textbox(FontRenderer* renderer, int windowWidth, int windowHeight, float fontSize = 20.f, std::string content = "");
        ~Textbox();

        void setFocus(bool focus) override;
        bool isFocused() override;

        int getCurrentLine();
        void setCurrentLine(int line);
        unsigned int getLength();

        void draw() override;
        void onHover(int cursorX, int cursorY) override { /*TODO*/ }
        void onClick() override { /*TODO*/ }
        void resize(int windowHeight, int windowWith) override;

        void write(char* c);




    private:
        FontRenderer* m_renderer = nullptr;
        std::vector<std::string> m_lines;
        float m_fontSize;

        bool m_hoverd = false;
        bool m_focused = false;

        int m_windowWidth;
        int m_windowHeight;

        int m_currentLine = 0;
};