//
// Created by griff on 7/8/2021.
//

#ifndef DATAVISUALIZATION_DATALOADINGWINDOW_H
#define DATAVISUALIZATION_DATALOADINGWINDOW_H


#include "UiWindow.h"

class DataSettingsWindow;

class DataLoadingWindow : public UiWindow
{
private:
    bool fileHasBeenChosen = false;
    DataSettingsWindow *settingsWindow;

    void displayFileDialog();
    void displayColumnChoice();

public:
    explicit DataLoadingWindow(DataSettingsWindow *settingsWindow);

    void display() override;
};


#endif //DATAVISUALIZATION_DATALOADINGWINDOW_H
