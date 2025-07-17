#version 330 core

layout (std140) uniform TerrainSettings {
    vec2 noiseOffset;
    float noiseScale;
    float terrainHeight;
};

in vec3 vertexColor;
in vec3 vertexPosition;
in vec2 outUV;
out vec4 fragColor;

void main() {
    float height = vertexPosition.y / terrainHeight;
    fragColor = vec4(height, 0, 0, 1);
}