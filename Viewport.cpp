#include "Viewport.h"

#include "imgui_impl_opengl3.h"

Viewport::Viewport(FrameBuffer &frameBuffer, ICCore::Camera &camera)
    : _frameBuffer(frameBuffer),
      _camera(camera) {

}

void Viewport::Render() {
    static ImVec2 lastViewportSize = ImVec2(0, 0);
    ImGui::Begin("Viewport"); {
        ImGui::BeginChild("ViewportRender");

        ImVec2 viewportSize = ImGui::GetContentRegionAvail();

        // Check if resized
        if (viewportSize.x > 0 && viewportSize.y > 0 && (
                viewportSize.x != lastViewportSize.x || viewportSize.y != lastViewportSize.y)) {
            _frameBuffer.RescaleFrameBuffer(viewportSize.x, viewportSize.y);
            lastViewportSize = viewportSize;
            _camera.SetAspectRatio(viewportSize.x / viewportSize.y);
        }

        ImGui::Image((ImTextureID)_frameBuffer.GetFrameTexture(), ImGui::GetContentRegionAvail(), ImVec2(0, 1),
                     ImVec2(1, 0));
    }
    ImGui::EndChild();
    ImGui::End();
}
