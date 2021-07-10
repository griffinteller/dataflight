//
// Created by griff on 7/3/2021.
//

#ifndef DATAVISUALIZATION_UIWINDOW_H
#define DATAVISUALIZATION_UIWINDOW_H


class UiWindow
{
public:
    virtual void display() = 0;
    void disable();
    void enable();
};


#endif //DATAVISUALIZATION_UIWINDOW_H
