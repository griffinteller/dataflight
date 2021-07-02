#include <iostream>
#include <window/Window.h>
#include <render/DataCamera.h>
#include <debug/DataGen.h>

int main()
{
    Window window (600, 600, vec4(1.0, 1.0, 1.0, 1.0));
    DataRepresentation data = DataGen::bigaussian(
            vec3(-1.5, 0, 0), vec3(1.5, 0, 0),
            1, 1,
            10000, 10000,
            0);

    DataCamera camera (&window, data, Transform(vec3(0, 0, 5)), 1);

    window.addMainContextDrawable(&camera);
    window.addFrameCallback(&camera);

    window.startLoop();

    glfwTerminate();
}
