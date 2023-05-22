cmake_minimum_required(VERSION 3.18)
project(DataVisualization)

set(CMAKE_CXX_STANDARD 17)

if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
    link_directories(lib/lib-mingw-w64)
elseif(${CMAKE_SYSTEM_NAME} MATCHES Linux)
    link_directories(lib/lib-linux)
    message(Linux)
else()
    message(CMAKE_SYSTEM_NAME)
    message(FATAL_ERROR No Matching OS found)
endif()

include_directories(src)
include_directories(res)
include_directories(lib/include)

add_executable(DataVisualization lib/glad.c src/main.cpp src/window/Window.cpp
        src/render/DataCamera.cpp src/data/DataRepresentation.cpp src/render/Shader.cpp
        src/debug/DataGen.cpp src/geometry/Transform.cpp lib/include/imgui/imgui.cpp
        lib/include/imgui/imgui_demo.cpp lib/include/imgui/imgui_draw.cpp
        lib/include/imgui/imgui_tables.cpp lib/include/imgui/imgui_widgets.cpp
        lib/include/imgui/imgui_impl_glfw.cpp lib/include/imgui/imgui_impl_opengl3.cpp src/ui/UiContext.cpp
        src/ui/VisualizationSettingsWindow.cpp lib/include/ImGuiFileDialog/ImGuiFileDialog.cpp
        src/ui/DataLoadingWindow.cpp src/ui/UiWindow.cpp src/ui/DataSettingsWindow.cpp src/data/CSVLoader.cpp
        src/util/StringUtil.cpp src/data/Axes.cpp src/render/FramebufferPostprocessing.cpp src/render/Framebuffer.cpp
        src/render/postprocessing/FXAAFilter.cpp src/render/postprocessing/InvertFilter.cpp)

if(${CMAKE_SYSTEM_NAME} MATCHES Linux)
    target_compile_definitions(${PROJECT_NAME} PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
    target_link_libraries(DataVisualization libglfw3.a -lGL -lX11 -lpthread -lXrandr -lXi -ldl)
elseif (${CMAKE_SYSTEM_NAME} MATCHES Windows)
    target_link_libraries(DataVisualization libglfw3.a)
else()
    message(CMAKE_SYSTEM_NAME)
    message(FATAL_ERROR No Matching OS found)
endif()
