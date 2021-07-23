//
// Created by griff on 7/2/2021.
//

#ifndef DATAVISUALIZATION_CALLBACKINTERFACES_H
#define DATAVISUALIZATION_CALLBACKINTERFACES_H

#include <typedefs.h>

class IKeyCallback
{
public:
    virtual void OnKey(int key, int scancode, int action, int mods) = 0;
};

class ICharCallback
{
public:
    virtual void OnChar(uint codepoint) = 0;
};

class ICursorPosCallback
{
public:
    virtual void OnCursorPos(double xpos, double ypos) = 0;
};

class ICursorEnterCallback
{
public:
    virtual void OnCursorEnter(int entered) = 0;
};

class IMouseButtonCallback
{
public:
    virtual void OnMouseButton(int button, int action, int mods) = 0;
};

class IScrollCallback
{
public:
    virtual void OnScroll(double xoffset, double yoffset) = 0;
};

class IFileDropCallback
{
public:
    virtual void OnFileDrop(int count, const char** paths) = 0;
};

class IDrawable
{
public:
    virtual void OnDraw() = 0;
};

class IFrameCallback
{
public:
    virtual void OnFrame() = 0;
};

class IWindowSizeCallback
{
public:
    virtual void OnWindowSize(int width, int height) = 0;
};

#endif //DATAVISUALIZATION_CALLBACKINTERFACES_H
