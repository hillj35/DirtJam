#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertexColor;
out vec3 vertexNormal;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);
    vertexNormal = normalize(normal);
    vertexColor = color;
}