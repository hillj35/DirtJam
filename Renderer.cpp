#include "Shader.h"

#include "Renderer.h"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

void Renderer::Init(ICCore::Window &window) {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    glViewport(0, 0, window.Width(), window.Height());
    glfwSetFramebufferSizeCallback(window.GetGLFWwindow(), FrameBufferSizeCallback);
}

void Renderer::RenderObject(ICCore::Camera &camera) {
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = camera.GetProjectionMatrix();

    auto shader = Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    shader.Use();
    shader.SetMat4("view", view);
    shader.SetMat4("projection", projection);
}

void Renderer::SetClearColor(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::FrameBufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
