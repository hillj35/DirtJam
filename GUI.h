#pragma once

#include <Window.h>

class GUI {
public:
    static void InitOpenGL(GLFWwindow *window);

    static void InitFrame();

    static void Render(ICCore::Window &window);

    static void Shutdown();
};