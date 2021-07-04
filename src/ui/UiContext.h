//
// Created by griff on 7/1/2021.
//

#ifndef DATAVISUALIZATION_UICONTEXT_H
#define DATAVISUALIZATION_UICONTEXT_H


#include <typedefs.h>
#include <GLFW/glfw3.h>
#include <stdimgui.h>
#include <vector>
#include "IUiWindow.h"

class UiContext
{
private:
    std::vector<IUiWindow*> uiWindows;

public:
    UiContext(GLFWwindow *window, const char *glsl_version);

    void render();

    void addUiWindow(IUiWindow *window);

    ~UiContext();
};


#endif //DATAVISUALIZATION_UICONTEXT_H
