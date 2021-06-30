//
// Created by griff on 6/27/2021.
//

#ifndef DATAVISUALIZATION_WINDOW_H
#define DATAVISUALIZATION_WINDOW_H


#include <vector>
#include <typedefs.h>
#include <stddeps.h>
#include <window/IDrawable.h>
#include <window/ICursorPosCallback.h>
#include <window/IFrameCallback.h>

class Window
{
private:
    GLFWwindow *handle;
    vec4 clearColor;
    std::vector<IDrawable*> drawables;
    std::vector<ICursorPosCallback*> cursorPosCallbacks;
    std::vector<IFrameCallback*> frameCallbacks;
    double lastFrameTime;
    double deltaTime;

    void cursorPosCallback(GLFWwindow *window, double xpos, double ypos);
    void frameCallback();
    void updateDeltaTime();

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);

public:

    // Constructs window resources and makes it current opengl context (ie window will show up)
    Window(int width, int height, const vec4 &clearColor = vec4(1.0, 1.0, 1.0, 1.0));

    void addDrawable(IDrawable *drawable);
    void addCursorPosCallback(ICursorPosCallback *callbackObj);
    void addFrameCallback(IFrameCallback *callbackObj);  // called every frame after clearing but before drawing

    // starts render loop
    void startLoop();

    // closes window
    void destroy();

    double getDeltaTime() const;
    GLFWwindow *getHandle() const;

    ~Window();
};


#endif //DATAVISUALIZATION_WINDOW_H
