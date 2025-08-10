#pragma once

#include <Core/EventSystem/ThreadSafeQueue/ThreadSafeQueue.h>
#include <Core/EventSystem/Events/Event.h>

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


#include <atomic>
#include <vector>


class IWidget;

class OpenGLWindow
{
    public:
        OpenGLWindow(std::atomic<bool>& run);

        bool createWindow(const char* title, int height, int width);
        void deleteWindow();

        void start();

        // void addWidget(IWidget* widget);

        // just for testing
        /*void setViewPort(int newWidht, int newHeight) { 
            glViewport(0, 0, newWidht, newHeight);
            for (IWidget* widget : m_widgetList)
            {
                widget->resize(newHeight, newWidht);
            }
        };*/

        // gets replaced later
        GLuint getProgramm() const { return m_program; }
        
        private:
        #ifdef __linux__
        Display* m_dispaly = nullptr;
        Window m_win;
        Atom m_wmDeleteMessage;
        GLXContext m_context;


        static std::atomic<bool>* s_runningPtr;

        static int myIOErrorHandler(Display* display);
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

        std::atomic<bool>& m_running;
        
        // std::vector<IWidget*> m_widgetList;
        
        #ifdef _WIN32
        static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        #endif

        GLuint createShader(GLenum type, const char* source);
        void draw();
};