#include "SceneCamera.h"

#include "Logger.h"

#include <imgui.h>

SceneCamera::SceneCamera(ICCore::Window &window, glm::vec3 position, glm::vec3 up, glm::vec3 look)
    : Camera(window, position, up, look) {
    glfwSetWindowUserPointer(window.GetGLFWwindow(), this);

    glfwSetScrollCallback(window.GetGLFWwindow(), [](GLFWwindow *window, double xOffset, double yOffset) {
        auto *self = static_cast<SceneCamera *>(glfwGetWindowUserPointer(window));
        self->Zoom(yOffset);
    });

    glfwSetCursorPosCallback(window.GetGLFWwindow(), [](GLFWwindow *window, double xPos, double yPos) {
        auto *self = static_cast<SceneCamera *>(glfwGetWindowUserPointer(window));
        self->MouseMoved(static_cast<float>(xPos), static_cast<float>(yPos));
    });
}

void SceneCamera::HandleInput() {
    if (_window.GetMouseDown(PAN_INPUT) == GLFW_PRESS) {
        if (_panHeld) {
            Pan();
        } else {
            _panHeld = true;
        }
    } else {
        _panHeld = false;
    }
    if (_window.GetMouseDown(ROTATE_INPUT) == GLFW_PRESS) {
        if (_panHeld) {
            return;
        }

        if (_rotateHeld) {
            Rotate();
        } else {
            _rotateHeld = true;
        }
    } else {
        _rotateHeld = false;
    }
}

void SceneCamera::MouseMoved(float xPos, float yPos) {
    _prevMouseX = _mouseX, _prevMouseY = _mouseY;
    _mouseX = xPos, _mouseY = yPos;
    _mouseDeltaX = _mouseX - _prevMouseX, _mouseDeltaY = _mouseY - _prevMouseY;
}

void SceneCamera::Pan() {
    glm::vec3 newPos = _position;
    glm::vec3 up = glm::normalize(glm::cross(_right, _look));
    newPos += -_mouseDeltaX * _right * PAN_SCALE + _mouseDeltaY * up * PAN_SCALE;
    MoveCamera(newPos);

    _mouseDeltaX = 0, _mouseDeltaY = 0;
}

void SceneCamera::Rotate() {
    glm::vec3 up = glm::normalize(glm::cross(_right, _look));

    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), -_mouseDeltaX * ROTATE_SCALE, up);
    rotation = glm::rotate(rotation, _mouseDeltaY * ROTATE_SCALE, _right);
    _look = rotation * glm::vec4(_look, 1.0f);
    MoveCamera(_position);

    _mouseDeltaX = 0, _mouseDeltaY = 0;
}

void SceneCamera::Zoom(double offset) {
    glm::vec3 newPos = _position;
    newPos += static_cast<float>(offset) * ZOOM_SCALE * _look;
    MoveCamera(newPos);
}
