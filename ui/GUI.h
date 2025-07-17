#pragma once

#include "../FrameBuffer.h"
#include "../Settings.h"

#include <Window.h>

class GUI {
public:
    static void InitOpenGL(GLFWwindow *window);
    static void InitFrame();
    static void Render(AppSettings &settings);
    static void Shutdown();
};