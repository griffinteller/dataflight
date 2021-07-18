//
// Created by griff on 7/8/2021.
//

#include <ImGuiFileDialog/ImGuiFileDialog.h>
#include <iostream>
#include "DataLoadingWindow.h"
#include "DataSettingsWindow.h"

#define FILE_DIALOG_KEY "FileDialogKey"
#define WINDOW_TITLE "Load Data"

void DataLoadingWindow::displayFileDialog()
{
    ImGuiFileDialog::Instance()->OpenDialog(FILE_DIALOG_KEY, WINDOW_TITLE, ".*", ".");

    if (ImGuiFileDialog::Instance()->Display(FILE_DIALOG_KEY))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::cout << "Would open a file" << std::endl;
            fileHasBeenChosen = true;
        }

        ImGuiFileDialog::Instance()->Close();
    }
}

void DataLoadingWindow::displayColumnChoice()
{
    ImGui::Begin(WINDOW_TITLE);

    ImGui::Text("This is where you would select columns.");

    if (ImGui::Button("OK"))
    {
        settingsWindow->needToDeleteLoadingWindow = true;
        disable();
    }

    ImGui::End();
}

void DataLoadingWindow::display()
{
    if (!fileHasBeenChosen)
        displayFileDialog();
    else
        displayColumnChoice();
}

DataLoadingWindow::DataLoadingWindow(DataSettingsWindow *settingsWindow)
: settingsWindow (settingsWindow)
{
}
