//
// Created by griff on 6/27/2021.
//

#include <iostream>
#include <functional>
#include "Window.h"

Window *Window::activeWindow = nullptr;

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const vec4 &clearColor)
: clearColor(clearColor), drawables(0), cursorPosCallbacks(0), frameCallbacks(0)
{
    activeWindow = this;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // compat versions
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);

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

        for (IDrawable *drawable : drawables)
            drawable->OnDraw();

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

void Window::addDrawable(IDrawable *drawable)
{
    drawables.push_back(drawable);
}

void Window::addCursorPosCallback(ICursorPosCallback *callbackObj)
{
    cursorPosCallbacks.push_back(callbackObj);
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

void Window::cursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
    for(ICursorPosCallback *obj : activeWindow->cursorPosCallbacks)
        obj->OnCursorPos(window, xpos, ypos);
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
