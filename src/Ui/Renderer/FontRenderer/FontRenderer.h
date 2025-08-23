#pragma once

#include "Character.h"

#include <Core/UiResources/Font/IFontRenderer.h>
#include <Core/UiResources/Containers/Color.h>

#include <map>
#include <string>
#include <array>
#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Ui::Renderer
{
    class FontRenderer : public Core::UiResources::Font::IFontRenderer
    {
    public:
        FontRenderer(const char* fontPath, int fontSize);
        ~FontRenderer();

        void drawText(const std::string& text, float x, float y, float scale, const Core::UiResources::Containers::Color& color) override;
        void resize(float windowWith, float windowHeight);

        int getSize() override { return m_fontSize; }


    private:
        std::map<char, Character> m_characters;
        GLuint m_vao;
        GLuint m_vbo;
        GLuint m_shader;

        float m_fontSize;

        GLuint compileShader(const char* source, GLenum type);
        GLuint createShaderProgram();
        void setOrthoProjection(float left, float right, float bottom, float top);

        void drawDebugBoundingBoxes(const std::string& text, float x, float y, float scale);
    };
}