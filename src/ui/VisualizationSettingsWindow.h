//
// Created by griff on 7/3/2021.
//

#ifndef DATAVISUALIZATION_VISUALIZATIONSETTINGSWINDOW_H
#define DATAVISUALIZATION_VISUALIZATIONSETTINGSWINDOW_H


#include <render/DataCamera.h>
#include "IUiWindow.h"

class VisualizationSettingsWindow : public IUiWindow
{
private:
    DataCamera *camera;

public:
    explicit VisualizationSettingsWindow(DataCamera *camera);

    void display() override;
};


#endif //DATAVISUALIZATION_VISUALIZATIONSETTINGSWINDOW_H
