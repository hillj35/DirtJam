#include "Renderer.h"

#include "Settings.h"
#include "opengl/OpenGLShader.h"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Renderer::Renderer(ICCore::Window &window) : _window(window) {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    glViewport(0, 0, window.Width(), window.Height());
    glfwSetFramebufferSizeCallback(window.GetGLFWwindow(), FrameBufferSizeCallback);

    _terrainSettingsUBO = GenerateTerrainUniformBuffer();
}

void Renderer::RenderMesh(ICCore::Camera &camera, ICCore::Mesh &mesh, AppSettings &settings) {
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = camera.GetProjectionMatrix();

    ICCore::IShader &shader = mesh.GetMaterial().GetShader();
    shader.Bind();
    shader.SetUniform("view", view);
    shader.SetUniform("projection", projection);
    shader.SetUniform("model", glm::mat4(1.0f));

    auto vertices = mesh.GetVertices();
    auto indices = mesh.GetIndices();

    glBindBuffer(GL_UNIFORM_BUFFER, _terrainSettingsUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(TerrainSettings), &settings.terrainSettings, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ICCore::Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ICCore::Vertex), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ICCore::Vertex), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(ICCore::Vertex), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(ICCore::Vertex), (void *)(9 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    // glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

void Renderer::SetClearColor(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::FrameBufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
