#pragma once
#include "../FrameBuffer.h"
#include "Camera.h"

class Viewport {
public:
    Viewport(FrameBuffer &frameBuffer, ICCore::Camera &camera);

    ~Viewport() = default;

    void Render();

private:
    FrameBuffer &_frameBuffer;
    ICCore::Camera &_camera;
};
