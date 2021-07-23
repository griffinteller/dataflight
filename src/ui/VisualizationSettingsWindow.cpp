//
// Created by griff on 7/3/2021.
//

#include <ImGuiFileDialog/ImGuiFileDialog.h>
#include <iostream>
#include "VisualizationSettingsWindow.h"

VisualizationSettingsWindow::VisualizationSettingsWindow(DataCamera *camera, FramebufferPostprocessing *postprocessing)
: camera (camera), postprocessing (postprocessing)
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

    float camSpeed = camera->getStrafeSpeed();
    step = camSpeed / 30.0f;
    ImGui::InputScalar("Camera Speed", ImGuiDataType_Float, &camSpeed, &step);
    camera->setStrafeSpeed(camSpeed);

    float rotSpeed = camera->getRotateSpeed();
    step = rotSpeed / 30.0f;
    ImGui::InputScalar("Rotate Speed", ImGuiDataType_Float, &rotSpeed, &step);
    camera->setRotateSpeed(rotSpeed);

    float fov = camera->getFovy();
    step = 1.0f;
    ImGui::InputScalar("Field of View", ImGuiDataType_Float, &fov, &step);
    camera->setFovy(fov);

    bool fxaaEnabled = postprocessing->isFilterActive(0);
    ImGui::Checkbox("Anti-Aliasing (FXAA)", &fxaaEnabled);
    postprocessing->setFilterActive(0, fxaaEnabled);

    ImGui::End();
}
