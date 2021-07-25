//
// Created by griff on 6/27/2021.
//

#ifndef DATAVISUALIZATION_DATACAMERA_H
#define DATAVISUALIZATION_DATACAMERA_H


#include <typedefs.h>
#include <data/DataRepresentation.h>
#include <window/Window.h>
#include <geometry/Transform.h>
#include <data/Axes.h>
#include "Shader.h"
#include "window/CallbackInterfaces.h"
#include "Framebuffer.h"

class DataCamera : public IDrawable, public IFrameCallback
{
private:
    Window *window;
    DataRepresentation *data;
    Axes *axes;
    Transform transform;
    Framebuffer *framebuffer = nullptr;
    float fovy;
    float aspectRatio;
    float nearFrustum;
    float farFrustum;
    float pointSize;
    float axisWidth;
    float dashLength;
    int dataWorld2ViewLoc = 0;
    int dataView2ClipLoc = 0;
    int pointSizeLoc = 0;
    int axesPosWorld2ViewLoc;
    int axesPosView2ClipLoc;
    int axesNegWorld2ViewLoc;
    int axesNegView2ClipLoc;
    int dashLengthLoc;
    int axesPosLineWidthLoc;
    int axesNegLineWidthLoc;
    float strafeSpeed = 20.0f;  // units per second
    float rotateSpeed = 100.0f;  // degrees per pixel

    constexpr static float pointSizeChangeSpeed = 1.0f;

    mat4 world2View() const;
    mat4 view2Clip() const;

    void drawPoints() const;
    void drawAxes() const;

    void loadDataLocs();

public:
    explicit DataCamera(Window *window, DataRepresentation *data, Axes *axes,
                        const Transform &transform = Transform(),
                        float pointSize = 1, float fovy = 45, float aspectRatio = 1, float nearFrustum = 0.1,
                        float farFrustum = 100, float axisWidth = 50, float dashLength = 0.1);

    void OnDraw() override;
    void OnFrame() override;

    Transform &getTransform();

    void setTransform(Transform transform);

    DataRepresentation * getData() const;
    void setData(DataRepresentation *data);

    float getFovy() const;
    void setFovy(float fovy);

    float getAspectRatio() const;
    void setAspectRatio(float aspectRatio);

    float getNearFrustum() const;
    void setNearFrustum(float nearFrustum);

    float getFarFrustum() const;
    void setFarFrustum(float farFrustum);

    float getPointSize() const;
    void setPointSize(float pointSize);

    float getAxisWidth() const;
    void setAxisWidth(float axisWidth);

    float getDashLength() const;
    void setDashLength(float dashLength);

    float getStrafeSpeed() const;
    void setStrafeSpeed(float strafeSpeed);

    float getRotateSpeed() const;
    void setRotateSpeed(float rotateSpeed);

    void setFramebuffer(Framebuffer *framebuffer);
};


#endif //DATAVISUALIZATION_DATACAMERA_H
