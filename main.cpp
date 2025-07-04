#include <iostream>
#include <Window.h>

int main() {
    std::cout << "Hello, World!" << std::endl;

    ICcore::Window window(1280, 720, "Demo");

    while (!window.ShouldClose()) {
        window.ProcessInput();
        window.SwapBuffers();
    }
    return 0;
}