#pragma once

#include "Character.h"
#include "Color.h"

#include <map>
#include <string>
#include <array>
#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

class FontRenderer
{
    public:
        FontRenderer(const char* fontPath, int fontSize);
        ~FontRenderer();

        void renderText(const std::string& text, float x, float y, float scale, const Color& color);
        void resize(float windowWith, float windowHeight);


    private:
        std::map<char, Character> m_characters;
        GLuint m_vao;
        GLuint m_vbo;
        GLuint m_shader;

        GLuint compileShader(const char* source, GLenum type);
        GLuint createShaderProgram();
        void setOrthoProjection(float left, float right, float bottom, float top);
};
