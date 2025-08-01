#include <iostream>

#include "UI/Window/OpenGLWindow.h"
#include "UI/Toolbar/Toolbar.h"
#include "UI/Renderer/FontRenderer/FontRenderer.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main()
{
    OpenGLWindow window;
    bool created = window.createWindow("New Window", WINDOW_HEIGHT, WINDOW_WIDTH);
    if (!created)
    {
        std::cerr << "Window could not be initialized\n";
        return 0;
    }

    window.addWidget(new Toolbar(WINDOW_WIDTH, WINDOW_HEIGHT, window.getProgramm()));

    window.start();

    window.deleteWindow();
    return 0;
}


// ✅ Verwendung

// FontRenderer* font = new FontRenderer("fonts/Roboto-Regular.ttf", 24);
// font->renderText("Hallo Welt", 20.0f, 440.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));