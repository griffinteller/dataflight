//
// Created by griff on 6/27/2021.
//

#ifndef DATAVISUALIZATION_DATACAMERA_H
#define DATAVISUALIZATION_DATACAMERA_H


#include <typedefs.h>
#include <data/DataRepresentation.h>
#include <window/Window.h>
#include "Shader.h"
#include "IDrawable.h"

class DataCamera : public IDrawable
{
private:
    DataRepresentation data;
    vec3 position;
    quat rotation;
    float fovy;
    float aspectRatio;
    float nearFrustum;
    float farFrustum;
    float pointSize;
    bool smoothed;
    Shader shader;

    mat4 world2View() const;
    mat4 view2Clip() const;

    static const char* getVertSource();
    static const char* getFragSource();

public:
    explicit DataCamera(DataRepresentation data, const vec3 &position = vec3(0.0, 0.0, 0.0),
                        const quat &rotation = quat(1.0, 0.0, 0.0, 0.0), float pointSize = 1, float fovy = 45,
                        float aspectRatio = 1, float nearFrustum = 0.1, float farFrustum = 100, bool smoothed = false);

    void draw() const override;

    void setPosition(const vec3 &pos);
    const vec3 &getPosition() const;

    void setRotation(const quat &rotation);
    const quat &getRotation() const;

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
