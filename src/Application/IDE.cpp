#include <Application/IDE.h>
#include <Core/Core.h>
#include <Ui/Window/OpenGLWindow.h>

#include <thread>

constexpr int HEIGHT = 480;
constexpr int WIDHT = 640;

IDE::IDE() : m_running(true) {}
IDE::~IDE() {}

void IDE::start()
{
    Core core(m_uiToCore, m_coreToUi, m_running);

    std::thread coreThread(&Core::run, &core);

    // start + setup Ui
    OpenGLWindow win(m_uiToCore, m_coreToUi, m_running);
    bool success = win.createWindow("New Window", HEIGHT, WIDHT);

    if (!success)
    {
        std::cout << "OpenGL Window could not be initialized" << std::endl;
        return;
    }

    win.start();

    // char input;

    // while (m_running)
    // {
    //     std::cin >> input;

    //     if (input == 'q')
    //     {
    //         std::cout << "Pushed!" << std::endl;
    //         m_uiToCore.push(Event(EventType::Quit));
    //         break;
    //     }
    // }

    std::cout << "Hello User!" << std::endl;

    coreThread.join();
}