#include "Toolbar.h"

#include <GL/gl.h>

Toolbar::Toolbar(int width, int height, GLuint program)
{
    m_program = program;

    float y_top = 1.f;
    float y_bottom = 1.f - (50.f / height);
    
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
    glUniform4f(clolorLoc, 1.0f, 0.0f, 0.0f, 1.0f); // red

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}