//
// Created by griff on 7/9/2021.
//

#ifndef DATAVISUALIZATION_DATASETTINGSWINDOW_H
#define DATAVISUALIZATION_DATASETTINGSWINDOW_H


#include "UiWindow.h"
#include "DataLoadingWindow.h"

class DataSettingsWindow : public UiWindow
{
    friend class DataLoadingWindow;

private:
    bool loadedData = false;
    bool needToDeleteLoadingWindow = false;
    DataLoadingWindow *loadingWindow = nullptr;  // keep this null when not pointing to heap (ie set to null after delete)

    const static char WindowTitle[];

    void displaySettings();
    void createDataLoadingWindow();

public:
    void display() override;

    ~DataSettingsWindow();
};


#endif //DATAVISUALIZATION_DATASETTINGSWINDOW_H
