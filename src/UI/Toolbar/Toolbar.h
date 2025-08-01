#pragma once
#include <GL/glew.h>

#include "../IWidget.h"

class Toolbar : public IWidget
{
    public:
        Toolbar(int windowWidth, int windowHeight, GLuint program);
        ~Toolbar();

        void draw() override;
        void onHover(int cursorX, int cursorY) override;
        void onClick() override {};
        void resize(int windowHeight, int windowWidth) override;
    
    private:
        GLuint m_vao;
        GLuint m_vbo;
        GLuint m_program;

        bool hovered = false;
};