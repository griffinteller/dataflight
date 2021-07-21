//
// Created by griff on 7/3/2021.
//

#ifndef DATAVISUALIZATION_VISUALIZATIONSETTINGSWINDOW_H
#define DATAVISUALIZATION_VISUALIZATIONSETTINGSWINDOW_H


#include <render/DataCamera.h>
#include "UiWindow.h"

#define FILE_DIALOG_KEY "OpenFileKey"

class VisualizationSettingsWindow : public UiWindow
{
private:
    DataCamera *camera;

public:
    explicit VisualizationSettingsWindow(DataCamera *camera);

    void display() override;
};


#endif //DATAVISUALIZATION_VISUALIZATIONSETTINGSWINDOW_H
