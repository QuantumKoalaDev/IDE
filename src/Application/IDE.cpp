#include <Application/IDE.h>
#include <Core/Core.h>
#include <Ui/Window/OpenGLWindow.h>

#include <thread>
#include <iostream>

constexpr int HEIGHT = 480;
constexpr int WIDHT = 640;

IDE::IDE() : m_running(true) {}
IDE::~IDE() {}

void IDE::start()
{
    Core core(m_running);

    std::thread coreThread(&Core::run, &core);

    // start + setup Ui
    OpenGLWindow win(m_running);
    bool success = win.createWindow("New Window", HEIGHT, WIDHT);

    if (!success)
    {
        std::cout << "OpenGL Window could not be initialized" << std::endl;
        return;
    }

    win.start();
    win.deleteWindow();
    std::cout << "Hello User!" << std::endl;

    coreThread.join();
}