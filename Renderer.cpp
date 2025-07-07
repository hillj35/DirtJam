#include "Renderer.h"

#include "Shader.h"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

void RenderObject(ICCore::Camera &camera) {
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = camera.GetProjectionMatrix();

    auto shader = Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    shader.Use();
    shader.SetMat4("view", view);
    shader.SetMat4("projection", projection);
}

void SetClearColor(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
