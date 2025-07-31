#pragma once

#include <GL/glew.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glxext.h>
#include <unistd.h>

#include "../Toolbar/Toolbar.h"

/*
    
*/
class OpenGLWindow
{
    public:
        bool createWindow(char* title);
        void deleteWindow();

        void start();
        
        private:
        Display* m_dispaly = nullptr;
        Window m_win;
        GLXContext m_context;
        
        GLuint m_program;
        GLuint m_vert;
        GLuint m_frag;
        GLuint m_vao;
        GLuint m_vbo;

        bool m_running = true;
        
        Toolbar* m_toolbar = nullptr;
        
        
        GLuint createShader(GLenum type, const char* source);
        void draw();
};