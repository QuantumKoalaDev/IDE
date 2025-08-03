#include "OpenGLWindow.h"

#include "../Textbox/Textbox.h"

#include <iostream>
#include <filesystem>


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

bool OpenGLWindow::createWindow(char* title, int height, int width)
{
    #ifdef __linux__
    m_dispaly = XOpenDisplay(nullptr);
    if (!m_dispaly)
    {
        std::cerr << "Could not open X11-Diplay \n";
        return false;
    }

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

    XStoreName(m_dispaly, m_win, title);
    XMapWindow(m_dispaly, m_win);

    // Creating OpenGL 3.3 Core Context
    typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
    glXCreateContextAttribsARBProc glXCreateAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB((const GLubyte*)"glXCreateContextAttribsARB");
    
    m_context = glXCreateAttribsARB(m_dispaly, fbc[0], nullptr, True, context_attribs);
    glXMakeCurrent(m_dispaly, m_win, m_context);
    #endif

    #ifdef _WIN32
    glewExperimental = GL_TRUE;
    #endif
    
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "GLEW could not be initialized\n";
        return false;
    }

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

    std::filesystem::path currentPath = std::filesystem::current_path().append("src/UI/Fonts/Ubuntu-Regular.ttf");
    m_fontRenderer = new FontRenderer(currentPath.c_str(), 20.f);
    m_widgetList.push_back(new Toolbar(640, 480, m_program));

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

    for (IWidget* widget : m_widgetList)
    {
        delete widget;
        widget = nullptr;
    }
    
    delete m_fontRenderer;
    m_fontRenderer = nullptr;
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

    for (IWidget* widget : m_widgetList)
    {
        widget->draw();
    }
    glBindVertexArray(0);

    glXSwapBuffers(m_dispaly, m_win);

}

void OpenGLWindow::start()
{
    while (m_running)
    {
        while (XPending(m_dispaly))
        {
            XEvent ev;
            XNextEvent(m_dispaly, &ev);

            if (ev.type == ConfigureNotify)
            {
                int newHeight = ev.xconfigure.height;
                int newWidht = ev.xconfigure.width;

                glViewport(0, 0, newWidht, newHeight);

                for (IWidget* widget : m_widgetList)
                {
                    widget->resize(newHeight, newWidht);
                }

                m_fontRenderer->resize(newWidht, newHeight);

                std::cout << "Fenstergroesse geaendert: " << newWidht << "x" << newHeight << std::endl;
            }

            if (ev.type == KeyPress)
            {
                // Keys => XK_a, XK_Escape, XK_Return
                KeySym keySym = XLookupKeysym(&ev.xkey, 0);

                std::cout << "Taste gedrückt: " << XKeysymToString(keySym) << std::endl;

                for (IWidget* widget : m_widgetList)
                {
                    if (Textbox* textbox = dynamic_cast<Textbox*>(widget))
                    {
                        
                        textbox->write(XKeysymToString(keySym));
                    }
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
}

void OpenGLWindow::addWidget(IWidget* widget)
{
    m_widgetList.push_back(widget);
}