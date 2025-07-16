#version 330 core

in vec3 vertexColor;
in vec3 vertexPosition;
in vec2 outUV;
out vec4 fragColor;

void main() {
    float height = vertexPosition.y / 15.0f;
    fragColor = vec4(height, 0, 0, 1);
}