#include <iostream>
#include <window/Window.h>
#include <render/DataCamera.h>
#include <debug/DataGen.h>
#include <ui/VisualizationSettingsWindow.h>
#include <ui/DataSettingsWindow.h>
#include <util/StringUtil.h>
#include <data/CSVLoader.h>

int main()
{
    /*Window window (1920, 1080, vec4(0.0, 0.0, 0.0, 1.0));
    DataRepresentation data = DataGen::bigaussian(
            vec3(-1.5, 0, 0), vec3(1.5, 0, 0),
            1, 1,
            1000, 1000,
            0);

    DataRepresentation data = DataGen::gaussian(vec3(0, 0, 0), 30, 125000000, 0);

    constexpr char vertSource[] =
#include "shaders/rainbow.vert"
        ;

    constexpr char fragSource[] =
#include "shaders/rainbow.frag"
        ;

    Shader shader (vertSource, fragSource);
    DataCamera camera (&window, &data, &shader, Transform(vec3(70, 70, 70)), 5);
    UiContext uiContext (window.getHandle(), "#version 430 core");

    VisualizationSettingsWindow visSettings (&camera);
    DataSettingsWindow dataSettings;

    visSettings.enable();
    dataSettings.enable();

    window.addMainContextDrawable(&camera);
    window.addFrameCallback(&camera);
    window.setUiContext(&uiContext);

    window.startLoop();

    glfwTerminate();*/

    CSVLoader csvLoader(R"(C:\Users\griff\CLionProjects\DataVisualization\res\data\00841599999.csv)");
    const auto &columns = csvLoader.getColumns();
    for (auto & column : columns)
        std::cout << column << std::endl;

    auto data = csvLoader.getBatchedFloatData({"LATITUDE", "LONGITUDE", "ELEVATION"});
    for (auto & datum : data)
        std::cout << datum << std::endl;
}
