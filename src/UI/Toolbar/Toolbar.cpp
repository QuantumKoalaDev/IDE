#include "Toolbar.h"

#include <GL/gl.h>

#include <iostream>

#define TOOLBAR_HEIGHT 50.0f

Toolbar::Toolbar(int windowWidth, int windowHeight, GLuint program)
{
    m_program = program;

    float y_top = 1.f;
    float y_bottom = 1.f - (TOOLBAR_HEIGHT / windowHeight);
    
    float vertices[] = 
    {
        -1.f,   y_top,
        1.f,    y_top,
        -1.f,   y_bottom,

        1.f,    y_top,
        1.f,    y_bottom,
        -1.f,   y_bottom
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Layout location 0 (shader)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
}

Toolbar::~Toolbar()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vbo);
}

void Toolbar::draw()
{
    glUseProgram(m_program);

    GLuint clolorLoc = glGetUniformLocation(m_program, "uColor");
    glUniform4f(clolorLoc, 1.0f, 0.0f, 0.0f, 1.0f);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Toolbar::onHover(int cursorX, int cursorY)
{
    std::cout << "Hovered" << std::endl;
}

void Toolbar::resize(int windowHeight, int windowWidth)
{
    float y_top = 1.f;
    float y_bottom = 1 - (TOOLBAR_HEIGHT / windowHeight);

    float vertices[] = 
    {
        -1.f,   y_top,
        1.f,    y_top,
        -1.f,   y_bottom,

        1.f,    y_top,
        1.f,    y_bottom,
        -1.f,   y_bottom
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
}