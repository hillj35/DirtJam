#pragma once
#include "Camera.h"
#include "FrameBuffer.h"

class Viewport {
public:
    Viewport(FrameBuffer &frameBuffer, ICCore::Camera &camera);

    ~Viewport() = default;

    void Render();

private:
    FrameBuffer &_frameBuffer;
    ICCore::Camera &_camera;
};
