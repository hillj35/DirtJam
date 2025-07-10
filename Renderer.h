#pragma once
#include "Shader.h"

#include "Camera.h"
#include "FrameBuffer.h"
#include "Mesh.h"
#include "Window.h"

class Renderer {
public:
    Renderer(ICCore::Window &window);

    void RenderMesh(ICCore::Camera &camera, ICCore::Mesh &mesh);

    static void RenderViewport();

    static void SetClearColor(float r, float g, float b);

private:
    Shader _shader;
    ICCore::Window &_window;

    static void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);
};
