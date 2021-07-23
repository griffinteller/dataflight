#include <iostream>
#include <window/Window.h>
#include <render/DataCamera.h>
#include <debug/DataGen.h>
#include <ui/VisualizationSettingsWindow.h>
#include <ui/DataSettingsWindow.h>
#include <util/StringUtil.h>
#include <data/CSVLoader.h>
#include <render/FramebufferPostprocessing.h>
#include <render/postprocessing/FXAAFilter.h>

int main()
{
    constexpr int width = 1920, height = 1080;

    Window window (width, height, vec4(0.0, 0.0, 0.0, 1.0), false);

    /*CSVLoader csvLoader = CSVLoader("/home/griffinteller/DataVisualization/res/data/spain_climate_clean.csv");
    std::vector<std::string> columns {"HourlyDewPointTemperature", "HourlyDryBulbTemperature", "HourlyRelativeHumidity"};
    DataRepresentation data = DataRepresentation(csvLoader.getBatchedFloatData(columns), columns);*/

    //DataRepresentation data = DataGen::gaussian(vec3(0, 0, 0), 1, 100, 0);

    Framebuffer mainContext (width, height, true);

    Axes axes (Axes::DefaultColors, 200);

    DataCamera camera(&window, nullptr, &axes, Transform(vec3(0, 0, 3)), 10);
    camera.setFramebuffer(&mainContext);
    camera.setDashLength(0.01);
    camera.setFarFrustum(1000);

    FramebufferPostprocessing postprocessing (mainContext);
    FXAAFilter fxaa;
    postprocessing.addFilter(&fxaa);

    UiContext uiContext (window.getHandle(), "#version 430 core");

    VisualizationSettingsWindow visSettings (&camera);
    DataSettingsWindow dataSettings (&camera);

    visSettings.enable();
    dataSettings.enable();

    window.addMainContextDrawable(&camera);
    window.addMainContextDrawable(&postprocessing);
    window.addFrameCallback(&camera);
    window.setUiContext(&uiContext);
    window.addWindowSizeCallback(&mainContext);

    window.startLoop();
}
