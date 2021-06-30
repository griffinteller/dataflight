//
// Created by griff on 6/29/2021.
//

#ifndef DATAVISUALIZATION_ICURSORPOSCALLBACK_H
#define DATAVISUALIZATION_ICURSORPOSCALLBACK_H

class ICursorPosCallback
{
public:
    virtual void OnCursorPos(GLFWwindow *window, double xpos, double ypos) = 0;
};

#endif //DATAVISUALIZATION_ICURSORPOSCALLBACK_H
