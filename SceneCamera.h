#pragma once
#include "Camera.h"
#include "Window.h"

class SceneCamera : public ICCore::Camera {
public:
    explicit SceneCamera(ICCore::Window &window, glm::vec3 position, glm::vec3 up = {0.0f, 1.0f, 0.0f},
                         glm::vec3 look = {0.0f, 0.0f, -1.0f});
    ~SceneCamera() = default;

    void HandleInput();

private:
    const int PAN_INPUT = GLFW_MOUSE_BUTTON_LEFT;
    const int ROTATE_INPUT = GLFW_MOUSE_BUTTON_RIGHT;
    const float ZOOM_SCALE = 0.03f;
    const float PAN_SCALE = 0.005f;
    const float ROTATE_SCALE = 0.003f;

    float _mouseX = 0, _mouseY = 0;
    float _prevMouseX = 0, _prevMouseY = 0;
    float _mouseDeltaX = 0, _mouseDeltaY = 0;

    bool _panHeld = false;
    bool _rotateHeld = false;

    void MouseMoved(float xPos, float yPos);
    void Pan();
    void Rotate();
    void Zoom(double offset);
};