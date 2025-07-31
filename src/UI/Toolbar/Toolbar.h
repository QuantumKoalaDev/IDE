#pragma once
#include <GL/glew.h>


class Toolbar
{
    public:
        Toolbar(int width, int height, GLuint program);
        ~Toolbar();

        void draw();
    
    private:
        GLuint m_vao;
        GLuint m_vbo;
        GLuint m_program;
};