#pragma once

#include <Core/EventSystem/IEventListener.h>

#include <Ui/Widgets/Widget.h>

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
#include <unordered_map>
#include <vector>


class IWidget;

class OpenGLWindow : public IEventListener
{

    public:
        OpenGLWindow(std::atomic<bool>& run);

        bool createWindow(const char* title, int height, int width);
        void deleteWindow();

        void start();

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

        std::unordered_map<size_t, std::unique_ptr<Widget>> m_widgetMap =  {};
                
        #ifdef _WIN32
        static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        #endif

        GLuint createShader(GLenum type, const char* source);
        void draw();

        void addWidget(std::unique_ptr<Widget> widget);

        void onEvent(const Core::EventSystem::Events::Event& event) override;
};