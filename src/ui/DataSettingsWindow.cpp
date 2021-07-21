//
// Created by griff on 7/9/2021.
//

#include <stdimgui.h>
#include "DataSettingsWindow.h"

const char DataSettingsWindow::WindowTitle[] = "Data Settings";

void DataSettingsWindow::display()
{
    if (needToDeleteLoadingWindow)  // we do this at the beginning because we need to delete after the last time its
                                    // been drawn
    {
        delete loadingWindow;
        loadingWindow = nullptr;
        needToDeleteLoadingWindow = false;
    }

    ImGui::Begin(WindowTitle);

    if (camera->getData() != nullptr)
        displaySettings();

    // this order is necessary because short-circuit eval would cause button to not show up sometimes
    // this might be behavior that I want but for right now I'm just making the button inactive
    if (ImGui::Button("Load Data") && loadingWindow == nullptr)
        createDataLoadingWindow();

    ImGui::End();
}

DataSettingsWindow::~DataSettingsWindow()
{
    delete loadingWindow;  // delete has built-in null check
}

void DataSettingsWindow::createDataLoadingWindow()
{
    loadingWindow = new DataLoadingWindow(this, camera);
    loadingWindow->enable();
}

void DataSettingsWindow::displaySettings()
{
    ImGui::Text("Settings would go here");
}

DataSettingsWindow::DataSettingsWindow(DataCamera *camera)
: camera(camera)
{
}
