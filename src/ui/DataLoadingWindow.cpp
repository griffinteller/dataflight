//
// Created by griff on 7/8/2021.
//

#include <ImGuiFileDialog/ImGuiFileDialog.h>
#include <iostream>
#include <data/CSVLoader.h>
#include "DataLoadingWindow.h"
#include "DataSettingsWindow.h"

#define FILE_DIALOG_KEY "FileDialogKey"
#define WINDOW_TITLE "Load Data"

void DataLoadingWindow::displayFileDialog()
{
    ImGuiFileDialog::Instance()->OpenDialog(FILE_DIALOG_KEY, WINDOW_TITLE, ".csv", ".");

    if (ImGuiFileDialog::Instance()->Display(FILE_DIALOG_KEY))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            filePath = ImGuiFileDialog::Instance()->GetFilePathName();
            std::cout << filePath << std::endl;
            fileHasBeenChosen = true;
        }

        ImGuiFileDialog::Instance()->Close();
    }
}

void DataLoadingWindow::displayColumnChoice()
{
    ImGui::Begin(WINDOW_TITLE);

    CSVLoader csvLoader (filePath);
    const std::vector<std::string> &columns = csvLoader.getColumns();

    if (enabledColumns == nullptr)
        enabledColumns = new bool[columns.size()]();  // zeroes memory

    for (int i = 0; i < columns.size(); i++)
    {
        ImGui::Checkbox(columns[i].c_str(), &enabledColumns[i]);
    }

    if (ImGui::Button("OK"))
    {
        std::vector<std::string> columnsToLoad = getEnabledColumnVector(columns, enabledColumns, columns.size());
        auto *data = new DataRepresentation(
                csvLoader.getBatchedFloatData(columnsToLoad),
                columnsToLoad);

        if (camera->getData() != nullptr)
            delete camera->getData();

        camera->setData(data);

        delete[] enabledColumns;
        enabledColumns = nullptr;
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

DataLoadingWindow::DataLoadingWindow(DataSettingsWindow *settingsWindow, DataCamera *camera)
: settingsWindow (settingsWindow), camera (camera)
{
}

DataLoadingWindow::~DataLoadingWindow()
{
    delete[] enabledColumns;  // shouldn't ever be needed, but just in case.
}

std::vector<std::string>
DataLoadingWindow::getEnabledColumnVector(const std::vector<std::string> &columnNames, const bool *enabledArray,
                                          int length)
{
    std::vector<std::string> result;

    for (int i = 0; i < length; i++)
        if (enabledArray[i])
            result.push_back(columnNames[i]);

    return result;
}
