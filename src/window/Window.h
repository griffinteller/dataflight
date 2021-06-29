//
// Created by griff on 6/27/2021.
//

#ifndef DATAVISUALIZATION_WINDOW_H
#define DATAVISUALIZATION_WINDOW_H


#include <vector>
#include <typedefs.h>
#include <stddeps.h>
#include <render/IDrawable.h>

class Window
{
private:
    GLFWwindow *handle;
    vec4 clearColor;
    std::vector<IDrawable*> drawables;

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);

public:

    // Constructs window resources and makes it current opengl context (ie window will show up)
    Window(int width, int height, const vec4 &clearColor = vec4(1.0, 1.0, 1.0, 1.0));

    void addDrawable(IDrawable *drawable);

    // starts render loop
    void startLoop();

    // closes window
    void destroy();

    const GLFWwindow *getHandle() const;

    ~Window();
};


#endif //DATAVISUALIZATION_WINDOW_H
