//
// Created by griff on 7/1/2021.
//

#ifndef DATAVISUALIZATION_UICONTEXT_H
#define DATAVISUALIZATION_UICONTEXT_H


#include <typedefs.h>
#include <GLFW/glfw3.h>
#include <stdimgui.h>
#include <vector>
#include <unordered_set>
#include "UiWindow.h"

class UiContext  // singleton
{
private:
    std::unordered_set<UiWindow*> uiWindows;
    std::unordered_set<UiWindow*> toAdd;
    std::unordered_set<UiWindow*> toRemove;

    static UiContext *activeContext;

public:
    UiContext(GLFWwindow *window, const char *glsl_version);

    void render();

    void addUiWindow(UiWindow *window);
    void removeUiWindow(UiWindow *window);

    static UiContext *getActiveContext();

    ~UiContext();
};


#endif //DATAVISUALIZATION_UICONTEXT_H
