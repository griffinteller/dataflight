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
    Window window (1920, 1080, vec4(0.0, 0.0, 0.0, 1.0), false);

    CSVLoader csvLoader = CSVLoader("/home/griffinteller/DataVisualization/res/data/spain_climate_clean.csv");
    std::vector<std::string> columns {"HourlyDewPointTemperature", "HourlyDryBulbTemperature", "HourlyRelativeHumidity"};
    DataRepresentation data = DataRepresentation(csvLoader.getBatchedFloatData(columns), columns);

    //DataRepresentation data = DataGen::gaussian(vec3(0, 0, 0), 1, 100, 0);

    Axes axes (Axes::DefaultColors);

    DataCamera camera(&window, &data, &axes,Transform(vec3(0, 0, 3)), 5);
    camera.setDashLength(0.01);

    UiContext uiContext (window.getHandle(), "#version 430 core");

    VisualizationSettingsWindow visSettings (&camera);
    DataSettingsWindow dataSettings;

    visSettings.enable();
    dataSettings.enable();

    window.addMainContextDrawable(&camera);
    window.addFrameCallback(&camera);
    window.setUiContext(&uiContext);

    window.startLoop();

    glfwTerminate();
}
