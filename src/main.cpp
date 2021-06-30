#include <iostream>
#include <window/Window.h>
#include <render/DataCamera.h>
#include <debug/DataGen.h>
#include <geometry/Transform.h>

int main()
{
    Window window (600, 600, vec4(1.0, 1.0, 1.0, 1.0));
    DataRepresentation data = DataGen::gaussian(1, 1000, 0);
    DataCamera camera (&window, data, Transform(vec3(0, 0, 5)));

    window.addDrawable(&camera);
    window.addFrameCallback(&camera);

    window.startLoop();

    glfwTerminate();
}
