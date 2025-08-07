#include "IDE.h"
#include <Core/Core.h>

#include <thread>

IDE::IDE() : m_running(true) {}
IDE::~IDE() {}

void IDE::start()
{
    Core core(m_uiToCore, m_coreToUi, m_running);

    std::thread coreThread(&Core::run, &core);

    // start + setup Ui
    char input;

    while (m_running)
    {
        std::cin >> input;

        if (input == 'q')
        {
            std::cout << "Pushed!" << std::endl;
            m_uiToCore.push(Event(EventType::Quit));
            break;
        }
    }

    std::cout << "Hello User!" << std::endl;

    coreThread.join();
}