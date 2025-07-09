#include "Renderer.h"

#include "Camera.h"
#include "GUI.h"
#include "Logger.h"
#include "Primitives.h"

int main() {
    ICCore::Logger::Init();

    ICCore::Window window(1280, 720, "Dirt Jam");
    ICCore::Camera camera(window, glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                          glm::vec3(0.0f, 0.0f, -1.0f));
    ICCore::Mesh testCube = ICCore::Cube();

    GUI::InitOpenGL(window.GetGLFWwindow());
    Renderer renderer(window);

    while (!window.ShouldClose()) {
        window.ProcessInput();
        GUI::InitFrame();
        Renderer::SetClearColor(1.0f, 0.71f, 0.76f);

        renderer.RenderMesh(camera, testCube);

        GUI::Render(window);
        window.SwapBuffers();
    }

    GUI::Shutdown();
    glfwTerminate();

    return 0;
}