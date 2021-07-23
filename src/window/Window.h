//
// Created by griff on 6/27/2021.
//

#ifndef DATAVISUALIZATION_WINDOW_H
#define DATAVISUALIZATION_WINDOW_H


#include <vector>
#include <typedefs.h>
#include <stddeps.h>
#include <ui/UiContext.h>
#include "CallbackInterfaces.h"

class Window
{
private:
    GLFWwindow *handle;
    vec4 clearColor;

    std::vector<IDrawable*> mainContextDrawables;
    std::vector<IFrameCallback*> frameCallbacks;
    std::vector<IKeyCallback*> keyCallbacks;
    std::vector<ICharCallback*> charCallbacks;
    std::vector<ICursorPosCallback*> cursorPosCallbacks;
    std::vector<ICursorEnterCallback*> cursorEnterCallbacks;
    std::vector<IMouseButtonCallback*> mouseButtonCallbacks;
    std::vector<IScrollCallback*> scrollCallbacks;
    std::vector<IFileDropCallback*> fileDropCallbacks;
    std::vector<IWindowSizeCallback*> windowSizeCallbacks;

    UiContext *uiContext = nullptr;
    double lastFrameTime;
    double deltaTime;
    vec2 lastFrameCursorPos;
    vec2 deltaCursorPos;
    int width;
    int height;

    static Window *activeWindow;

    // functions actually passed to glfw. Just call the real callbacks on *activeWindow
    static void staticKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void staticCharCallback(GLFWwindow *window, uint codepoint);
    static void staticCursorPosCallback(GLFWwindow *window, double xpos, double ypos);
    static void staticCursorEnterCallback(GLFWwindow *window, int entered);
    static void staticMouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    static void staticScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
    static void staticFileDropCallback(GLFWwindow *window, int count, const char **paths);
    static void staticWindowSizeCallback(GLFWwindow *window, int width, int height);

    // TODO: set up set to keep track of repeated key sends from OS
    // TODO: set up scrollDelta

    void frameCallback();
    void keyCallback(int key, int scancode, int action, int mods);
    void charCallback(uint codepoint);

    // screen coordinates, relative to top left
    void cursorPosCallback(double xpos, double ypos);

    // entered is a bool (1 = entered, 0 = left)
    void cursorEnterCallback(int entered);

    void mouseButtonCallback(int button, int action, int mods);
    void scrollCallback(double xoffset, double yoffset);

    // paths are temporary. If you want to keep them, you should make a deep copy.
    void fileDropCallback(int count, const char** paths);

    void windowSizeCallback(int width, int height);

    void updateDeltaTime();
    void updateDeltaCursorPos();
    void renderMainContext();
    void renderUi();

    static void messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                GLsizei length, const GLchar* message, const void* userParam);

public:

    // Constructs window res and makes it current opengl context (ie window will show up)
    Window(int width, int height, vec4 clearColor = vec4(1.0, 1.0, 1.0, 1.0), bool debug = false);

    void addMainContextDrawable(IDrawable *drawable);
    void addFrameCallback(IFrameCallback *callbackObj);  // called every frame after clearing but before drawing
    void addKeyCallback(IKeyCallback *keyCallback);
    void addCharCallback(ICharCallback *charCallback);
    void addCursorPosCallback(ICursorPosCallback *cursorPosCallback);
    void addCursorEnterCallback(ICursorEnterCallback *cursorEnterCallback);
    void addMouseButtonCallback(IMouseButtonCallback *mouseButtonCallback);
    void addScrollCallback(IScrollCallback *scrollCallback);
    void addFileDropCallback(IFileDropCallback *fileDropCallback);
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
    static bool getKeyboardLocked() ;
    static bool getMouseLocked() ;

    ~Window();
};


#endif //DATAVISUALIZATION_WINDOW_H
