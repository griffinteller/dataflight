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
            1000, 1000,
            0);

    DataCamera camera (&window, data, Transform(vec3(0, 0, 5)), 5);
    UiContext uiContext (window.getHandle(), "#version 330 core");

    window.addMainContextDrawable(&camera);
    window.addFrameCallback(&camera);
    window.setUiContext(&uiContext);

    window.startLoop();

    glfwTerminate();
}
