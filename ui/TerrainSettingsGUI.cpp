#include "TerrainSettingsGUI.h"

#include <imgui.h>

void TerrainSettingsGUI::Render(TerrainSettings &settings) {
    ImGui::Begin("Terrain Settings");
    {
        ImGui::Text("Terrain Settings");
        ImGui::Separator();
        ImGui::DragFloat("Terrain Height", &settings.terrainHeight, 0.5f);
        ImGui::DragFloat("Noise Scale", &settings.noiseScale, 0.1f);
        ImGui::DragFloat2("Noise Offset", &settings.noiseOffset.x, 0.1f);
    }
    ImGui::End();
}