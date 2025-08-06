#pragma once

#include <GL/glew.h>
#ifdef __linux__
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glxext.h>
#include <unistd.h>
#endif

#ifdef _WIN32
#include <Windows.h>
#include <GL/wglew.h>
#endif


#include <vector>

#include "../Renderer/FontRenderer/FontRenderer.h"
#include "../Toolbar/Toolbar.h"


class IWidget;
/*
        
*/
class OpenGLWindow
{
    public:
        bool createWindow(const char* title, int height, int width);
        void deleteWindow();

        void start();

        void addWidget(IWidget* widget);

        // gets replaced later
        GLuint getProgramm() const { return m_program; }
        FontRenderer* getFontRenderer() { return m_fontRenderer; }
        
        private:
        #ifdef __linux__
        Display* m_dispaly = nullptr;
        Window m_win;
        GLXContext m_context;
        #endif

        #ifdef _WIN32
        HWND m_hwnd;
        HDC m_hdc;
        HGLRC m_hglrc;
        #endif
        
        GLuint m_program;
        GLuint m_vert;
        GLuint m_frag;
        GLuint m_vao;
        GLuint m_vbo;

        bool m_running = true;
        
        FontRenderer* m_fontRenderer = nullptr;
        std::vector<IWidget*> m_widgetList;
        
        
        GLuint createShader(GLenum type, const char* source);
        void draw();
};