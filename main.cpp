#include "Renderer.h"

#include "Camera.h"
#include "Logger.h"
#include "Primitives.h"
#include "SceneCamera.h"
#include "Settings.h"
#include "ui/GUI.h"
#include "ui/Viewport.h"

int main() {
    ICCore::Logger::Init();
    AppSettings settings;

    ICCore::Window window(1280, 720, "Dirt Jam");
    SceneCamera camera(window, glm::vec3(0.0f, 2.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, -0.5f, -1.0f));
    ICCore::Mesh testPlane = ICCore::Plane(100, 14);

    GUI::InitOpenGL(window.GetGLFWwindow());
    Renderer renderer(window);
    FrameBuffer sceneBuffer(window.Width(), window.Height());
    Viewport viewport(sceneBuffer, camera);

    while (!window.ShouldClose()) {
        // Input
        window.ProcessInput();
        camera.HandleInput();

        GUI::InitFrame();
        Renderer::SetClearColor(0.0f, 0.0f, 0.0f);

        // Render scene into viewport's framebuffer
        sceneBuffer.Bind();
        Renderer::SetClearColor(1.0f, 0.71f, 0.76f);
        renderer.RenderMesh(camera, testPlane, settings);
        sceneBuffer.Unbind();

        viewport.Render();
        GUI::Render(settings);
        window.SwapBuffers();
    }

    GUI::Shutdown();
    glfwTerminate();

    return 0;
}