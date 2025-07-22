cmake_minimum_required(VERSION 3.31)
project(DirtJam)

set(CMAKE_CXX_STANDARD 23)

# Add ICCore as a subdirectory
add_subdirectory(external/ICCore)

find_package(imgui CONFIG REQUIRED)

add_executable(DirtJam main.cpp
        Renderer.h
        Renderer.cpp
        ui/GUI.h
        ui/GUI.cpp
        FrameBuffer.cpp
        FrameBuffer.h
        ui/Viewport.cpp
        ui/Viewport.h
        SceneCamera.h
        SceneCamera.cpp
        ui/TerrainSettingsGUI.cpp
        ui/TerrainSettingsGUI.h
        Settings.h)

# Link to the ICCore target (defined in ICCore's CMakeLists.txt)
target_link_libraries(DirtJam PRIVATE ICCore imgui::imgui)