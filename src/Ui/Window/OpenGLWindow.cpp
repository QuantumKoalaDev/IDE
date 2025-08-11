#include "OpenGLWindow.h"

#include <Core/EventSystem/Events/Event.h>
#include <Core/EventSystem/Events/ResizeEvent.h>
#include <Core/EventSystem/EventManager/EventManager.h>
#include <Core/ServiceManagement/ServiceManager.h>

#include <iostream>
#include <filesystem>

#ifdef __linux__
std::atomic<bool>* OpenGLWindow::s_runningPtr = nullptr;

static int visualAttribs[] =
{
    GLX_X_RENDERABLE,   True,
    GLX_DRAWABLE_TYPE,  GLX_WINDOW_BIT,
    GLX_RENDER_TYPE,    GLX_RGBA_BIT,
    GLX_X_VISUAL_TYPE,  GLX_TRUE_COLOR,
    GLX_RED_SIZE,       8,
    GLX_GREEN_SIZE,     8,
    GLX_BLUE_SIZE,      8,
    GLX_ALPHA_SIZE,     8,
    GLX_DEPTH_SIZE,     24,
    GLX_STENCIL_SIZE,   8,
    GLX_DOUBLEBUFFER,   True,
    None

};

static int context_attribs[] =
{
    GLX_CONTEXT_MAJOR_VERSION_ARB,  3,
    GLX_CONTEXT_MINOR_VERSION_ARB,  3,
    GLX_CONTEXT_PROFILE_MASK_ARB,   GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
    None
};
#endif

#ifdef _WIN32
static PIXELFORMATDESCRIPTOR pfd =
{
    sizeof(pfd), 1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA, 32,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    24, 8, 0,
    PFD_MAIN_PLANE, 0, 0, 0, 0
};

static int context_attribs[] =
{
    WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
    WGL_CONTEXT_MINOR_VERSION_ARB, 3,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    0
};
#endif

static float vertices[] =
{
    0.8f,   0.8f,
    -0.8f,  -0.8f,
    0.8f,   -0.8f
};

const char* vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec2 aPos;
    void main() {
        gl_Position = vec4(aPos, 0.0, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    uniform vec4 uColor;
    void main() {
        FragColor = uColor;
    }
)";

OpenGLWindow::OpenGLWindow(std::atomic<bool>& run) :
m_running(run)
{
    auto opt = ServiceManager::getService("EventManager");

    if (!opt.has_value())
    {
        std::cerr << "Error" << std::endl;
        return;
    }

    IService& ref = opt.value().get();
    EventManager& evMg = dynamic_cast<EventManager&>(ref);
    evMg.addListener(EventType::Resize, this);
}
            

GLuint OpenGLWindow::createShader(GLenum type, const char* source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char info[512];
        glGetShaderInfoLog(shader, 512, nullptr, info);
        std::cerr << "Shader compilation failed:\n" << info << std::endl;
    }

    return shader;
}

#ifdef _WIN32
LRESULT CALLBACK OpenGLWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // OpenGLWindow* myHwnd = reinterpret_cast<OpenGLWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

        auto opt = ServiceManager::getService("EventManager");

        if (!opt.has_value()) return DefWindowProc(hWnd, uMsg, wParam, lParam);

        IService& ref = opt.value().get();
        EventManager& evMg = dynamic_cast<EventManager&>(ref);


    if (uMsg == WM_CLOSE)
    {
        evMg.pushEvent(std::make_shared<Event>(EventType::Quit), false);
        PostQuitMessage(0);
        return 0;
    }

    switch (uMsg)
    {
    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);

        evMg.pushEvent(std::make_shared<ResizeEvent>(ResizeEvent(width, height)));
        break;
    }
    case WM_KEYDOWN:
    {
        char key = static_cast<char>(wParam);
        std::cout << "Key pressed: " << key << std::endl;
        break;
    }
    case WM_DESTROY:
        evMg.pushEvent(std::make_shared<Event>(EventType::Quit), false);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}
#endif


bool OpenGLWindow::createWindow(const char* title, int height, int width)
{
    #ifdef __linux__
    m_dispaly = XOpenDisplay(nullptr);
    if (!m_dispaly)
    {
        std::cerr << "Could not open X11-Diplay \n";
        return false;
    }

    s_runningPtr = &m_running;
    XSetIOErrorHandler(myIOErrorHandler);

    int fbcount;
    GLXFBConfig* fbc = glXChooseFBConfig(m_dispaly, DefaultScreen(m_dispaly), visualAttribs, &fbcount);
    if (!fbc)
    {
        std::cerr << "GLXBConfig not found\n";
        return false;
    }

    XVisualInfo* vi = glXGetVisualFromFBConfig(m_dispaly, fbc[0]);
    XSetWindowAttributes swa;
    swa.colormap = XCreateColormap(m_dispaly, RootWindow(m_dispaly, vi->screen), vi->visual, AllocNone);
    swa.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask;

    m_win = XCreateWindow(m_dispaly, RootWindow(m_dispaly, vi->screen),
        0, 0, width, height, 0, vi->depth, InputOutput,
        vi->visual, CWColormap | CWEventMask, &swa
    );

    Atom wmDeleteMessage = XInternAtom(m_dispaly, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(m_dispaly, m_win, &wmDeleteMessage, 1);
    m_wmDeleteMessage = wmDeleteMessage;

    XStoreName(m_dispaly, m_win, title);
    XMapWindow(m_dispaly, m_win);

    // Creating OpenGL 3.3 Core Context
    typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
    glXCreateContextAttribsARBProc glXCreateAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB((const GLubyte*)"glXCreateContextAttribsARB");
    
    m_context = glXCreateAttribsARB(m_dispaly, fbc[0], nullptr, True, context_attribs);
    glXMakeCurrent(m_dispaly, m_win, m_context);
    #endif

    #ifdef _WIN32
    WNDCLASS wc = {};
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = "DummyGL";

    if (!RegisterClass(&wc))
    {
        std::cerr << "Failed to register window class\n";
        return false;
    }

    m_hwnd = CreateWindowEx(
        0, wc.lpszClassName, title, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height, 
        nullptr, nullptr, wc.hInstance, nullptr
    );

    if (!m_hwnd)
    {
        std::cerr << "Window could not be created" << std::endl;
        return false;
    }

    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    m_hdc = GetDC(m_hwnd);

    int pf = ChoosePixelFormat(m_hdc, &pfd);
    SetPixelFormat(m_hdc, pf, &pfd);

    HGLRC tempContext = wglCreateContext(m_hdc);
    wglMakeCurrent(m_hdc, tempContext);

    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB =
        (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

    if (!wglCreateContextAttribsARB)
    {
        std::cerr << "wglCreateContextAttribsARB not supported\n";
        return false;
    }

    m_hglrc = wglCreateContextAttribsARB(m_hdc, 0, context_attribs);

    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(tempContext);
    wglMakeCurrent(m_hdc, m_hglrc);

    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    #endif
    
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "GLEW could not be initialized\n";
        return false;
    }

    #ifdef _WIN32
    ShowWindow(m_hwnd, SW_SHOW);
    #endif

    // Shader and Pipeline
    m_vert = createShader(GL_VERTEX_SHADER, vertexShaderSource);
    m_frag = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    m_program = glCreateProgram();
    glAttachShader(m_program, m_vert);
    glAttachShader(m_program, m_frag);
    glLinkProgram(m_program);

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    std::filesystem::path currentPath = std::filesystem::current_path().append("resources/Fonts/Ubuntu-Regular.ttf");
    // m_fontRenderer = new FontRenderer(currentPath.string().c_str(), 20);
    // m_widgetList.push_back(new Toolbar(640, 480, m_program));

    return true;
}

void OpenGLWindow::deleteWindow()
{ 
    #ifdef __linux__
    glDeleteProgram(m_program);
    glDeleteShader(m_vert);
    glDeleteShader(m_frag);
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glXDestroyContext(m_dispaly, m_context);
    XDestroyWindow(m_dispaly, m_win);
    XCloseDisplay(m_dispaly);
    #endif

    #ifdef _WIN32
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(m_hglrc);
    ReleaseDC(m_hwnd, m_hdc);
    DestroyWindow(m_hwnd);
    #endif

    // for (IWidget* widget : m_widgetList)
    // {
    //     delete widget;
    //     widget = nullptr;
    // }
    
}


void OpenGLWindow::draw()
{
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_program);
    GLuint colorLoc = glGetUniformLocation(m_program, "uColor");
    glUniform4f(colorLoc, 0.f, 0.f, 1.f, 1.f);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);


    glBindVertexArray(0);

    #ifdef __linux__
    glXSwapBuffers(m_dispaly, m_win);
    #endif

    #ifdef _WIN32
    SwapBuffers(m_hdc);
    #endif
}

void OpenGLWindow::start()
{
#ifdef __linux__
    while (m_running)
    {
        auto opt = ServiceManager::getService("EventManager");

        if (!opt.has_value()) continue;

        IService& ref = opt.value().get();
        EventManager& evMg = dynamic_cast<EventManager&>(ref);
        evMg.dispatchEvent(true);

        while (XPending(m_dispaly))
        {
            XEvent ev;
            XNextEvent(m_dispaly, &ev);

            if (ev.type == ConfigureNotify)
            {
                int newHeight = ev.xconfigure.height;
                int newWidht = ev.xconfigure.width;

                // glViewport(0, 0, newWidht, newHeight);

                // for (IWidget* widget : m_widgetList)
                // {
                //     widget->resize(newHeight, newWidht);
                // }

                // m_fontRenderer->resize(newWidht, newHeight);

                std::cout << "Fenstergroesse geaendert: " << newWidht << "x" << newHeight << std::endl;
            }

            if (ev.type == KeyPress)
            {
                // Keys => XK_a, XK_Escape, XK_Return
                KeySym keySym = XLookupKeysym(&ev.xkey, 0);

                std::cout << "Taste gedrückt: " << XKeysymToString(keySym) << std::endl;

                // if (keySym == XK_q)
                // {
                //     m_uiToCore.push(Event(EventType::Quit));
                //     // m_running = false;
                // }

                // for (IWidget* widget : m_widgetList)
                // {
                //     if (Textbox* textbox = dynamic_cast<Textbox*>(widget))
                //     {
                        
                //         textbox->write(XKeysymToString(keySym));
                //     }
                // }
            }

            if (ev.type == ClientMessage)
            {
                if ((Atom)ev.xclient.data.l[0] == m_wmDeleteMessage)
                {
                    evMg.pushEvent(std::make_shared<Event>(EventType::Quit), false);
                }
            }
        }

        int x, y;
        Window root_return, child_return;
        int root_x, root_y;
        unsigned int mask_return;

        XQueryPointer(
            m_dispaly,
            m_win,
            &root_return,
            &child_return, 
            &root_x, &root_y,
            &x, &y,
            &mask_return // mouse status (pressed mouse button)
        );
        draw();
        usleep(16000);
    }
#endif

#ifdef _WIN32
    MSG msg;
    while (m_running)
    {
        auto opt = ServiceManager::getService("EventManager");
        if (!opt.has_value()) continue;
        IService& ref = opt.value().get();
        EventManager& evMg = dynamic_cast<EventManager&>(ref);
        evMg.dispatchEvent(true);

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        draw();
        Sleep(16);
    }
#endif
}

// void OpenGLWindow::addWidget(IWidget* widget)
// {
//     m_componentManager.addComponent(widget);
//     //m_widgetList.push_back(widget);
// }

#ifdef __linux__
int OpenGLWindow::myIOErrorHandler(Display* display)
{
    if (s_runningPtr) s_runningPtr->store(false, std::memory_order_relaxed);

    return -1;
}
#endif

void OpenGLWindow::onEvent(std::shared_ptr<Event> event)
{
    if (event.get()->getType() == EventType::Resize)
    {
        std::shared_ptr<ResizeEvent> resEv = std::dynamic_pointer_cast<ResizeEvent>(event);

        glViewport(0, 0, resEv.get()->getWidht(), resEv.get()->getHeight());
    }
}