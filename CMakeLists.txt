cmake_minimum_required(VERSION 3.19)
project(DataVisualization)

set(CMAKE_CXX_STANDARD 14)

link_directories(dependencies/lib-mingw-w64)

include_directories(src)
include_directories(resources)
include_directories(dependencies/include)

add_executable(DataVisualization dependencies/glad.c src/main.cpp src/window/Window.cpp src/render/DataCamera.cpp src/data/DataRepresentation.cpp src/render/Shader.cpp src/debug/DataGen.cpp)

target_link_libraries(DataVisualization libglfw3.a)