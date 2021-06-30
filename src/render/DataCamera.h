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
#include "window/IDrawable.h"

class DataCamera : public IDrawable, public IFrameCallback
{
private:
    Window *window;
    DataRepresentation data;
    Transform transform;
    float fovy;
    float aspectRatio;
    float nearFrustum;
    float farFrustum;
    float pointSize;
    bool smoothed;
    Shader shader;

    constexpr static float strafeSpeed = 5.0f;  // units per second
    constexpr static float rotateSpeed = 0.3f;  // degrees per pixel

    mat4 world2View() const;
    mat4 view2Clip() const;

    static const char* getVertSource();
    static const char* getFragSource();

public:
    explicit DataCamera(Window *window, DataRepresentation data, const Transform &transform = Transform(),
                        float pointSize = 1, float fovy = 45, float aspectRatio = 1, float nearFrustum = 0.1,
                        float farFrustum = 100, bool smoothed = false);

    void OnDraw() const override;
    void OnFrame() override;

    const Transform &getTransform() const;

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
