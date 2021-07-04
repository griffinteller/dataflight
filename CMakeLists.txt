cmake_minimum_required(VERSION 3.19)
project(DataVisualization)

set(CMAKE_CXX_STANDARD 14)

link_directories(lib/lib-mingw-w64)

include_directories(src)
include_directories(res)
include_directories(lib/include)

add_executable(DataVisualization lib/glad.c src/main.cpp src/window/Window.cpp
        src/render/DataCamera.cpp src/data/DataRepresentation.cpp src/render/Shader.cpp
        src/debug/DataGen.cpp src/geometry/Transform.cpp lib/include/imgui/imgui.cpp
        lib/include/imgui/imgui_demo.cpp lib/include/imgui/imgui_draw.cpp
        lib/include/imgui/imgui_tables.cpp lib/include/imgui/imgui_widgets.cpp
        lib/include/imgui/imgui_impl_glfw.cpp
        lib/include/imgui/imgui_impl_opengl3.cpp src/ui/UiContext.cpp src/ui/VisualizationSettingsWindow.cpp)

target_link_libraries(DataVisualization libglfw3.a)