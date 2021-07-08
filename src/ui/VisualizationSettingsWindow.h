//
// Created by griff on 7/3/2021.
//

#ifndef DATAVISUALIZATION_VISUALIZATIONSETTINGSWINDOW_H
#define DATAVISUALIZATION_VISUALIZATIONSETTINGSWINDOW_H


#include <render/DataCamera.h>
#include "IUiWindow.h"

#define FILE_DIALOG_KEY "OpenFileKey"

class VisualizationSettingsWindow : public IUiWindow
{
private:
    DataCamera *camera;
    bool isFileDialogOpen = false;

public:
    explicit VisualizationSettingsWindow(DataCamera *camera);

    void display() override;
    void displayChooseFile();
};


#endif //DATAVISUALIZATION_VISUALIZATIONSETTINGSWINDOW_H
