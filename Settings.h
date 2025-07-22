#pragma once

#include <glm/glm.hpp>
#include <opengl/GLHeader.h>

struct TerrainSettings {
    glm::vec2 noiseOffset = glm::vec2(0.0f);
    float noiseScale = 10.0f;
    float terrainHeight = 15.0f;
};

struct AppSettings {
    TerrainSettings terrainSettings;
};

inline unsigned int GenerateTerrainUniformBuffer() {
    unsigned int uboTerrainSettings;
    glGenBuffers(1, &uboTerrainSettings);
    glBindBuffer(GL_UNIFORM_BUFFER, uboTerrainSettings);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(TerrainSettings), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboTerrainSettings);
    return uboTerrainSettings;
}