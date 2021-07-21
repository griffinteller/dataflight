//
// Created by griff on 7/8/2021.
//

#ifndef DATAVISUALIZATION_DATALOADINGWINDOW_H
#define DATAVISUALIZATION_DATALOADINGWINDOW_H


#include <render/DataCamera.h>
#include "UiWindow.h"

class DataSettingsWindow;

class DataLoadingWindow : public UiWindow
{
private:
    bool fileHasBeenChosen = false;
    std::string filePath;
    DataSettingsWindow *settingsWindow;
    DataCamera *camera;

    void displayFileDialog();

    bool *enabledColumns = nullptr;  // might be a way to do this with statics; this works fine tho.
    void displayColumnChoice();

    static std::vector<std::string>
    getEnabledColumnVector(const std::vector<std::string> &columnNames, const bool *enabledArray,
                           int length);

public:
    explicit DataLoadingWindow(DataSettingsWindow *settingsWindow, DataCamera *camera);

    void display() override;

    ~DataLoadingWindow();


};


#endif //DATAVISUALIZATION_DATALOADINGWINDOW_H
