cmake_minimum_required(VERSION 3.31)
project(DirtJam)

set(CMAKE_CXX_STANDARD 23)

# Add ICCore as a subdirectory
add_subdirectory(external/ICCore)
add_subdirectory(external/glad)

find_package(imgui CONFIG REQUIRED)

add_executable(DirtJam main.cpp
        Renderer.h
        Renderer.cpp
        GUI.h
        GUI.cpp
        FrameBuffer.cpp
        FrameBuffer.h
        Viewport.cpp
        Viewport.h)

# Link to the ICCore target (defined in ICCore's CMakeLists.txt)
target_link_libraries(DirtJam PRIVATE ICCore glad imgui::imgui)