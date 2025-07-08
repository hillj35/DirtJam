#pragma once
#include "Camera.h"
#include "Window.h"

class Renderer {
public:
    static void Init(ICCore::Window &window);

    static void RenderObject(ICCore::Camera &camera);

    static void SetClearColor(float r, float g, float b);

private:
    static void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);
};
