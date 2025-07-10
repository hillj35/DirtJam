#pragma once

#include "FrameBuffer.h"

#include <Window.h>

class GUI {
public:
    static void InitOpenGL(GLFWwindow *window);

    static void InitFrame();

    static void Render(ICCore::Window &window, FrameBuffer &frameBuffer);

    static void Shutdown();

private:
    static void RenderViewport(FrameBuffer &frameBuffer);
};