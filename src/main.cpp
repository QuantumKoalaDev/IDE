#include <iostream>

#include "UI/Window/OpenGLWindow.h"

int main()
{
    OpenGLWindow window;
    bool created = window.createWindow("New Window");

    if (!created)
    {
        std::cerr << "Window could not be initialized\n";
        return 0;
    }

    window.start();

    window.deleteWindow();
    return 0;
}