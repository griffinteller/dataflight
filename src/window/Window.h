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
#include <ui/UiContext.h>

class Window
{
private:
    GLFWwindow *handle;
    vec4 clearColor;
    std::vector<IDrawable*> mainContextDrawables;
    UiContext *uiContext = nullptr;
    std::vector<IFrameCallback*> frameCallbacks;
    double lastFrameTime;
    double deltaTime;
    vec2 lastFrameCursorPos;
    vec2 deltaCursorPos;
    int width;
    int height;

    static Window *activeWindow;

    void frameCallback();
    void updateDeltaTime();
    void updateDeltaCursorPos();
    void renderMainContext();
    void renderUi();

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);

public:

    // Constructs window resources and makes it current opengl context (ie window will show up)
    Window(int width, int height, const vec4 &clearColor = vec4(1.0, 1.0, 1.0, 1.0));

    void addMainContextDrawable(IDrawable *drawable);
    void addFrameCallback(IFrameCallback *callbackObj);  // called every frame after clearing but before drawing
    void setUiContext(UiContext *uiContext);

    // starts render loop
    void startLoop();

    // closes window
    void destroy();

    double getDeltaTime() const;
    const vec2 &getDeltaCursorPos() const;
    GLFWwindow *getHandle() const;
    vec2 getWidthAndHeight() const;
    float getAspect() const;

    ~Window();
};


#endif //DATAVISUALIZATION_WINDOW_H
