#include "Camera.h"

#include <iostream>
#include <Window.h>

int main() {
    ICcore::Window window(1280, 720, "Demo");
    ICCore::Camera camera(window, glm::vec3(0.0f, 0.0f, 0.0f));



    while (!window.ShouldClose()) {
        window.ProcessInput();
        window.SwapBuffers();
    }
    return 0;
}