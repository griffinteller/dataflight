//
// Created by griff on 7/3/2021.
//

#ifndef DATAVISUALIZATION_VISUALIZATIONSETTINGSWINDOW_H
#define DATAVISUALIZATION_VISUALIZATIONSETTINGSWINDOW_H


#include <render/DataCamera.h>
#include <render/FramebufferPostprocessing.h>
#include "UiWindow.h"

#define FILE_DIALOG_KEY "OpenFileKey"

class VisualizationSettingsWindow : public UiWindow
{
private:
    DataCamera *camera;
    FramebufferPostprocessing *postprocessing;

public:
    VisualizationSettingsWindow(DataCamera *camera, FramebufferPostprocessing *postprocessing);

    void display() override;
};


#endif //DATAVISUALIZATION_VISUALIZATIONSETTINGSWINDOW_H
