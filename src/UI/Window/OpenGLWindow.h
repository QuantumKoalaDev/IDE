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

#include "../ComponentManager.h"
#include "../Renderer/FontRenderer/FontRenderer.h"
#include "../Toolbar/Toolbar.h"
#include "../Interfaces/IInputListener.h"


class IWidget;

class OpenGLWindow : public IInputListener
{
    public:
        bool createWindow(const char* title, int height, int width);
        void deleteWindow();

        void start();

        void addWidget(IWidget* widget);

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
        FontRenderer* getFontRenderer() { return m_fontRenderer; }
        ComponentManager& getComponentManager();

        void onEvent(Event& event) override;

        void resgisterToResize();
        
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
        
        ComponentManager m_componentManager;
        FontRenderer* m_fontRenderer = nullptr;
        std::vector<IWidget*> m_widgetList;
        
        #ifdef _WIN32
        static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        #endif

        GLuint createShader(GLenum type, const char* source);
        void draw();
};