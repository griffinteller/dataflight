#include <iostream>
#include <window/Window.h>
#include <render/DataCamera.h>
#include <debug/DataGen.h>
#include <ui/VisualizationSettingsWindow.h>

int main()
{
    Window window (1920, 1080, vec4(1.0, 1.0, 1.0, 1.0));
    DataRepresentation data = DataGen::bigaussian(
            vec3(-1.5, 0, 0), vec3(1.5, 0, 0),
            1, 1,
            1000, 1000,
            0);

    const char *vertSource =
#include "shaders/basic.vert"
        ;

    const char *fragSource =
#include "shaders/basic.frag"
        ;

    Shader shader (vertSource, fragSource);
    DataCamera camera(window, data, shader, Transform(vec3(0, 0, 5)), 5);
    UiContext uiContext (window.getHandle(), "#version 330 core");
    VisualizationSettingsWindow visSettings (&camera);

    uiContext.addUiWindow(&visSettings);

    window.addMainContextDrawable(&camera);
    window.addFrameCallback(&camera);
    window.setUiContext(&uiContext);

    window.startLoop();

    glfwTerminate();
}
