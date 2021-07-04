//
// Created by griff on 7/3/2021.
//

#include "VisualizationSettingsWindow.h"

VisualizationSettingsWindow::VisualizationSettingsWindow(DataCamera *camera)
: camera (camera)
{
}

void VisualizationSettingsWindow::display()
{
    ImGui::Begin("Visualization Settings");

    float pointSize = camera->getPointSize();
    float step = pointSize / 30.0f;
    ImGui::InputScalar("Point Size", ImGuiDataType_Float, &pointSize, &step);
    camera->setPointSize(pointSize);

    vec3 &camPosition = camera->getTransform().position;
    step = 1.0f;
    ImGui::InputFloat3("Camera Position", &camPosition.x);
    ImGui::End();
}
