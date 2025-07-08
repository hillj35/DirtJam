#include "Camera.h"

#include "Renderer.h"

#include <iostream>
#include <Window.h>

int main() {
    ICCore::Window window(1280, 720, "Demo");
    ICCore::Camera camera(window, glm::vec3(0.0f, 0.0f, 0.0f));

    Renderer::Init(window);

    while (!window.ShouldClose()) {
        Renderer::SetClearColor(1.0f, 1.0f, 0.0f);

        window.ProcessInput();
        window.SwapBuffers();
    }

    glfwTerminate();

    return 0;
}