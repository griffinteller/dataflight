//
// Created by griff on 6/27/2021.
//

#ifndef DATAVISUALIZATION_DATACAMERA_H
#define DATAVISUALIZATION_DATACAMERA_H


#include <typedefs.h>
#include <data/DataRepresentation.h>
#include <window/Window.h>
#include <geometry/Transform.h>
#include "Shader.h"
#include "window/CallbackInterfaces.h"

class DataCamera : public IDrawable, public IFrameCallback
{
private:
    Window &window;
    DataRepresentation &data;
    Transform transform;
    float fovy;
    float aspectRatio;
    float nearFrustum;
    float farFrustum;
    float pointSize;
    bool smoothed;
    Shader &shader;
    int world2ViewLoc;
    int view2ClipLoc;
    int pointSizeLoc;

    constexpr static float strafeSpeed = 5.0f;  // units per second
    constexpr static float rotateSpeed = 100.0f;  // degrees per pixel
    constexpr static float pointSizeChangeSpeed = 1.0f; // units per second

    mat4 world2View() const;
    mat4 view2Clip() const;

public:
    explicit DataCamera(Window &window, DataRepresentation &data, Shader &shader,
                        const Transform &transform = Transform(),
                        float pointSize = 1, float fovy = 45, float aspectRatio = 1, float nearFrustum = 0.1,
                        float farFrustum = 100);

    void OnDraw() const override;
    void OnFrame() override;

    Transform &getTransform();

    void setTransform(const Transform &transform);

    const DataRepresentation &getData() const;
    void setData(const DataRepresentation &data);

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

    bool isSmoothed() const;
    void setSmoothed(bool smoothed);

    const Shader &getShader() const;
    void setShader(const Shader &shader);
};


#endif //DATAVISUALIZATION_DATACAMERA_H
