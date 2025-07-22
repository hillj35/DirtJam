#pragma once

#include "Camera.h"
#include "FrameBuffer.h"
#include "Mesh.h"
#include "Settings.h"
#include "Shader.h"
#include "Window.h"

class Renderer {
public:
    Renderer(ICCore::Window &window);

    void RenderMesh(ICCore::Camera &camera, ICCore::Mesh &mesh, AppSettings &settings);

    static void RenderViewport();

    static void SetClearColor(float r, float g, float b);

private:
    ICCore::Window &_window;
    unsigned int _terrainSettingsUBO;

    static void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);
};
