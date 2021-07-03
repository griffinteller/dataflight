//
// Created by griff on 7/1/2021.
//

#include "UiContext.h"
#include <iostream>

UiContext::UiContext(GLFWwindow *window, const char *glsl_version)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void UiContext::render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // TODO: ui logic goes here

    // ImGui::ShowDemoWindow();

    displayVisualizationSettings();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

UiContext::~UiContext()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UiContext::displayVisualizationSettings()
{
    ImGui::Begin("Visualization Settings");

    static float pointSize = 1.0f;
    const float step = 0.001f;
    ImGui::InputScalar("Point Size", ImGuiDataType_Float, &pointSize, &step);

    ImGui::End();
}
