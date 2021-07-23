//
// Created by griff on 7/1/2021.
//

#include "UiContext.h"
#include <iostream>

UiContext *UiContext::activeContext = nullptr;

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

    activeContext = this;
}

void UiContext::render()
{
    initFrame();

    ImGui::DockSpaceOverViewport(nullptr,
                                 ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoDockingInCentralNode);

    for (auto *window : toAdd)
        uiWindows.emplace(window);

    toAdd.clear();

    for (auto *window : toRemove)
        uiWindows.erase(window);

    toRemove.clear();

    for (auto *window : uiWindows)
        window->display();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

UiContext::~UiContext()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UiContext::addUiWindow(UiWindow *window)
{
    toAdd.emplace(window);
}

void UiContext::removeUiWindow(UiWindow *window)
{
    toRemove.emplace(window);
}

UiContext *UiContext::getActiveContext()
{
    return activeContext;
}

void UiContext::initFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}
