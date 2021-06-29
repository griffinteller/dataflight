#include <iostream>
#include <window/Window.h>
#include <render/DataCamera.h>
#include <debug/DataGen.h>

int main()
{
    Window window (600, 600, vec4(1.0, 1.0, 1.0, 1.0));
    DataRepresentation data = DataGen::cube(2, 4);
    DataCamera camera (data, vec3(0, 0, 3),
                       quat(1.0, 0.0, 0.0, 0.0), 10);

    window.addDrawable(&camera);
    window.startLoop();

    glfwTerminate();
}
