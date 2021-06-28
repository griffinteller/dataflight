//
// Created by griff on 6/27/2021.
//

#ifndef DATAVISUALIZATION_WINDOW_H
#define DATAVISUALIZATION_WINDOW_H


#include <vector>
#include <typedefs.h>
#include <stddeps.h>

class Window
{
private:
    GLFWwindow *handle;
    std::vector<func> loopCallbacks;

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);

public:

    // Constructs window resources and makes it current opengl context (ie window will show up)
    Window(int width, int height);

    // adds callback to be called during the render loop. Callbacks called in order they are added.
    void addLoopCallback(func callback);

    // starts render loop
    void startLoop();

    // closes window
    void destroy();

    const GLFWwindow *getHandle() const;

    ~Window();
};


#endif //DATAVISUALIZATION_WINDOW_H
