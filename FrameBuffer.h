#pragma once

class FrameBuffer {
public:
    FrameBuffer(float width, float height);

    ~FrameBuffer();

    unsigned int GetFrameTexture();

    void RescaleFrameBuffer(float width, float height);

    void Bind();

    void Unbind();

private:
    unsigned int _fbo;
    unsigned int _texture;
    unsigned int _rbo;

    float _width, _height;
};
