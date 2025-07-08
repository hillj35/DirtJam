#include "Renderer.h"

#include "Camera.h"
#include "Logger.h"
#include "Primitives.h"

int main() {
    ICCore::Logger::Init();

    ICCore::Window window(1280, 720, "Dirt Jam");
    ICCore::Camera camera(window, glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                          glm::vec3(0.0f, 0.0f, -1.0f));
    ICCore::Mesh testCube = ICCore::Cube();

    Renderer renderer(window);

    while (!window.ShouldClose()) {
        Renderer::SetClearColor(1.0f, 0.71f, 0.76f);

        renderer.RenderMesh(camera, testCube);

        window.ProcessInput();
        window.SwapBuffers();
    }

    glfwTerminate();

    return 0;
}