#include "FontRenderer.h"

#include <iostream>

static const char* vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec4 vertex;
    out vec2 TextCoords;
    uniform mat4 projection;
    void main() {
        gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
        TextCoords = vertex.zw;
    }
)";

static const char* fragmentShaderSource = R"(
    #version 330 core
    in vec2 TextCoords;
    out vec4 FragColor;

    uniform sampler2D text;
    uniform vec3 textColor;

    void main() {
        float alpha = texture(text, TextCoords).r;
        FragColor = vec4(textColor, alpha);
    }
)";

FontRenderer::FontRenderer(const char* fontPath, int fontSize)
{
    m_fontSize = fontSize;

    m_shader = createShaderProgram();

    // FreeType init    
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cerr << "Could not init FreeType\n";
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, fontPath, 0, &face))
    {
        std::cerr << "Failed to load font: " << fontPath << "\n";
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriciton

    for (unsigned char c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cerr << "Failed to load character: " << c << "\n";
            continue;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            std::cerr << "OpenGL Error after glTexImage2D for char " << (int)c << ": " << err << "\n";
            continue;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture,
            Size(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            Bearing(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<GLuint>(face->glyph->advance.x)
        };

        m_characters.insert(std::pair<char, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // VAO + VBO setup
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

FontRenderer::~FontRenderer()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteProgram(m_shader);
}

void FontRenderer::renderText(const std::string& text, float x, float y, float scale, const Color& color)
{
    setOrthoProjection(0.f, 640.f, 0.f, 480.f);

    GLint loc = glGetUniformLocation(m_shader, "textColor");
    if (loc == -1)
        std::cerr << "Uniform 'textColor' not found!" << std::endl;

    GLint loc1 = glGetUniformLocation(m_shader, "projection");
    if (loc1 == -1) {
        std::cerr << "Uniform 'projection' not found or not set!" << std::endl;
    }


    glUseProgram(m_shader);

    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    if (currentProgram != m_shader) {
        std::cerr << "Warning: Shader program not set correctly!" << std::endl;
    }


    glUniform3f(glGetUniformLocation(m_shader, "textColor"), color.r, color.g, color.b);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_FRAMEBUFFER_SRGB);

    glUniform1i(glGetUniformLocation(m_shader, "text"), 0);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_vao);

    for (char c : text)
    {
        Character ch = m_characters[c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        float vertices[6][4] =
        {
             { xpos,    ypos + h,   0.f,    0.f},
             { xpos,    ypos,       0.f,    1.f},
             { xpos + w, ypos,      1.f,    1.f},

             { xpos,    ypos + h,   0.f,    0.f },
             { xpos + w, ypos,       1.f,    1.f },
             { xpos + w, ypos + h,   1.f,    0.f}
        };

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE)
            std::cerr << "Framebuffer not complete: " << std::hex << status << std::endl;


        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get pixels
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}

GLuint FontRenderer::compileShader(const char* src, GLenum type)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info[512];
        glGetShaderInfoLog(shader, 512, nullptr, info);

        std::cerr << "Shader Error: " << info << std::endl;
    }

    return shader;
}

GLuint FontRenderer::createShaderProgram()
{
    GLuint vs = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fs = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);

    GLint success;
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(prog, 512, NULL, infoLog);
        std::cerr << "Shader Program Link Error: " << infoLog << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return prog;
}

void FontRenderer::setOrthoProjection(float left, float right, float bottom, float top)
{
    float projection[16] =
    {
        2.0f / (right - left),      0.f,        0.f,    0.f,
        0.f,        2.f / (top - bottom),       0.f,    0.f,
        0.f,        0.f,                       -1.f,    0.f,
        -(right + left) / (right - left), -(top + bottom) / (top - bottom), 0.f, 1.f
    };

    glUseProgram(m_shader);
    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    if (currentProgram != m_shader) {
        std::cerr << "Warning: Shader program not set correctly!" << std::endl;
    }


    GLint loc = glGetUniformLocation(m_shader, "projection");
    glUniformMatrix4fv(loc, 1, GL_FALSE, projection);
}

void FontRenderer::resize(float windowWidth, float windowHeight)
{
    setOrthoProjection(0.f, windowWidth, 0.f, windowHeight);
}