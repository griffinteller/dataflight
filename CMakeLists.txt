cmake_minimum_required(VERSION 3.19)
project(DataVisualization)

set(CMAKE_CXX_STANDARD 14)

link_directories(dependencies/lib-mingw-w64)

include_directories(src)
include_directories(resources)
include_directories(dependencies/include)

add_executable(DataVisualization dependencies/glad.c src/main.cpp src/window/Window.cpp
        src/render/DataCamera.cpp src/data/DataRepresentation.cpp src/render/Shader.cpp
        src/debug/DataGen.cpp src/geometry/Transform.cpp dependencies/include/imgui/imgui.cpp
        dependencies/include/imgui/imgui_demo.cpp dependencies/include/imgui/imgui_draw.cpp
        dependencies/include/imgui/imgui_tables.cpp dependencies/include/imgui/imgui_widgets.cpp
        dependencies/include/imgui/imgui_impl_glfw.cpp
        dependencies/include/imgui/imgui_impl_opengl3.cpp)

target_link_libraries(DataVisualization libglfw3.a)