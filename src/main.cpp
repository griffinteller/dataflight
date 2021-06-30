#include <iostream>
#include <window/Window.h>
#include <render/DataCamera.h>
#include <debug/DataGen.h>
#include <geometry/Transform.h>

int main()
{
    Window window (600, 600, vec4(1.0, 1.0, 1.0, 1.0));
    DataRepresentation data = DataGen::cube(2, 4);
    DataCamera camera (&window, data);

    window.addDrawable(&camera);
    window.addFrameCallback(&camera);

    window.startLoop();

    glfwTerminate();
}
