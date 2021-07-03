//
// Created by griff on 7/1/2021.
//

#ifndef DATAVISUALIZATION_UICONTEXT_H
#define DATAVISUALIZATION_UICONTEXT_H


#include <typedefs.h>
#include <GLFW/glfw3.h>
#include <stdimgui.h>

class UiContext
{
public:
    UiContext(GLFWwindow *window, const char *glsl_version);

    void render();

    ~UiContext();
};


#endif //DATAVISUALIZATION_UICONTEXT_H
