//
// Created by griff on 6/27/2021.
//

#include <iostream>
#include <functional>
#include "Window.h"

Window *Window::activeWindow = nullptr;

void Window::staticWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, width, height);
    activeWindow->width = width;
    activeWindow->height = height;

    activeWindow->windowSizeCallback(width, height);
}

Window::Window(int width, int height, vec4 clearColor)
: clearColor(clearColor), mainContextDrawables(0), frameCallbacks(0), keyCallbacks(0), charCallbacks(0),
cursorPosCallbacks(0), cursorEnterCallbacks(0), mouseButtonCallbacks(0), scrollCallbacks(0), fileDropCallbacks(0),
windowSizeCallbacks(0)
{
    this->width = width;
    this->height = height;
    activeWindow = this;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  // compat versions
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // no legacy functions
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // needed for mac support, might as well just leave in windows code

    GLFWwindow* window = glfwCreateWindow(width, height, "GLFW Window", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create window!" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // initialize glad with correct func pointer
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window, staticWindowSizeCallback);
    glfwSetKeyCallback(window, staticKeyCallback);
    glfwSetCharCallback(window, staticCharCallback);
    glfwSetCursorPosCallback(window, staticCursorPosCallback);
    glfwSetCursorEnterCallback(window, staticCursorEnterCallback);
    glfwSetMouseButtonCallback(window, staticMouseButtonCallback);
    glfwSetScrollCallback(window, staticScrollCallback);
    glfwSetDropCallback(window, staticFileDropCallback);

    handle = window;
}

GLFWwindow *Window::getHandle() const
{
    return handle;
}

void Window::startLoop()
{
    while (!glfwWindowShouldClose(handle))
    {
        updateDeltaTime();
        updateDeltaCursorPos();

        frameCallback();

        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderMainContext();
        renderUi();

        glfwSwapBuffers(handle);
        glfwPollEvents();
    }
}

void Window::destroy()
{
    glfwDestroyWindow(handle);
}

Window::~Window()
{
    destroy();
}

void Window::addMainContextDrawable(IDrawable *drawable)
{
    mainContextDrawables.push_back(drawable);
}

void Window::addFrameCallback(IFrameCallback *callbackObj)
{
    frameCallbacks.push_back(callbackObj);
}

void Window::frameCallback()
{
    for (IFrameCallback *obj : frameCallbacks)
        obj->OnFrame();
}

void Window::updateDeltaTime()
{
    double nowTime = glfwGetTime();
    deltaTime = nowTime - lastFrameTime;
    lastFrameTime = nowTime;
}

double Window::getDeltaTime() const
{
    return deltaTime;
}

void Window::updateDeltaCursorPos()
{
    double nowX, nowY;
    glfwGetCursorPos(handle, &nowX, &nowY);
    vec2 nowCursorPos (nowX, nowY);
    deltaCursorPos = nowCursorPos - lastFrameCursorPos;
    lastFrameCursorPos = nowCursorPos;
}

const vec2 &Window::getDeltaCursorPos() const
{
    return deltaCursorPos;
}

vec2 Window::getWidthAndHeight() const
{
    return vec2(width, height);
}

float Window::getAspect() const
{
    return (float) width / (float) height;
}

void Window::renderMainContext()
{
    for (IDrawable *drawable : mainContextDrawables)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);  // by default, render to screen
        glViewport(0, 0, width, height);  // by default, render to WHOLE screen
        drawable->OnDraw();
    }
}

void Window::renderUi()
{
    if (uiContext == nullptr)
        return;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);  // by default, render to screen
    glViewport(0, 0, width, height);  // by default, render to WHOLE screen

    uiContext->render();
}

void Window::setUiContext(UiContext *uiContext)
{
    this->uiContext = uiContext;
}

void Window::staticKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    activeWindow->keyCallback(key, scancode, action, mods);
}

void Window::staticCharCallback(GLFWwindow *window, uint codepoint)
{
    activeWindow->charCallback(codepoint);
}

void Window::staticCursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
    activeWindow->cursorPosCallback(xpos, ypos);
}

void Window::staticCursorEnterCallback(GLFWwindow *window, int entered)
{
    activeWindow->cursorEnterCallback(entered);
}

void Window::staticMouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    activeWindow->mouseButtonCallback(button, action, mods);
}

void Window::staticScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
    activeWindow->scrollCallback(xoffset, yoffset);
}

void Window::staticFileDropCallback(GLFWwindow *window, int count, const char **paths)
{
    activeWindow->fileDropCallback(count, paths);
}

void Window::keyCallback(int key, int scancode, int action, int mods)
{
    if (ImGui::GetIO().WantCaptureKeyboard)
        return;

    for (IKeyCallback *callback : keyCallbacks)
        callback->OnKey(key, scancode, action, mods);
}

void Window::charCallback(uint codepoint)
{
    if (ImGui::GetIO().WantCaptureKeyboard)
        return;

    for (ICharCallback *callback : charCallbacks)
        callback->OnChar(codepoint);
}

void Window::cursorPosCallback(double xpos, double ypos)
{
    if (ImGui::GetIO().WantCaptureMouse)
        return;

    for (ICursorPosCallback *callback : cursorPosCallbacks)
        callback->OnCursorPos(xpos, ypos);
}

void Window::cursorEnterCallback(int entered)
{
    if (ImGui::GetIO().WantCaptureMouse)
        return;

    for (ICursorEnterCallback *callback : cursorEnterCallbacks)
        callback->OnCursorEnter(entered);
}

void Window::mouseButtonCallback(int button, int action, int mods)
{
    if (ImGui::GetIO().WantCaptureMouse)
        return;

    for (IMouseButtonCallback *callback : mouseButtonCallbacks)
        callback->OnMouseButton(button, action, mods);
}

void Window::scrollCallback(double xoffset, double yoffset)
{
    if (ImGui::GetIO().WantCaptureMouse)
        return;

    for (IScrollCallback *callback : scrollCallbacks)
        callback->OnScroll(xoffset, yoffset);
}

void Window::fileDropCallback(int count, const char **paths)
{
    for (IFileDropCallback *callback : fileDropCallbacks)
        callback->OnFileDrop(count, paths);
}

void Window::windowSizeCallback(int width, int height)
{
    for (IWindowSizeCallback *callback : windowSizeCallbacks)
    {
        callback->OnWindowSize(width, height);
    }
}

void Window::addKeyCallback(IKeyCallback *keyCallback)
{
    keyCallbacks.push_back(keyCallback);
}

void Window::addCharCallback(ICharCallback *charCallback)
{
    charCallbacks.push_back(charCallback);
}

void Window::addCursorPosCallback(ICursorPosCallback *cursorPosCallback)
{
    cursorPosCallbacks.push_back(cursorPosCallback);
}

void Window::addCursorEnterCallback(ICursorEnterCallback *cursorEnterCallback)
{
    cursorEnterCallbacks.push_back(cursorEnterCallback);
}

void Window::addMouseButtonCallback(IMouseButtonCallback *mouseButtonCallback)
{
    mouseButtonCallbacks.push_back(mouseButtonCallback);
}

void Window::addScrollCallback(IScrollCallback *scrollCallback)
{
    scrollCallbacks.push_back(scrollCallback);
}

void Window::addFileDropCallback(IFileDropCallback *fileDropCallback)
{
    fileDropCallbacks.push_back(fileDropCallback);
}

bool Window::getKeyboardLocked()
{
    return ImGui::GetIO().WantCaptureKeyboard;
}

bool Window::getMouseLocked()
{
    return ImGui::GetIO().WantCaptureMouse;
}

void Window::addWindowSizeCallback(IWindowSizeCallback *windowSizeCallback)
{
    windowSizeCallbacks.push_back(windowSizeCallback);
}
