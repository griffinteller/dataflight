//
// Created by griff on 6/27/2021.
//

#include <glad/glad.h>

#include <utility>
#include "DataCamera.h"

const vec3 &DataCamera::getPosition() const
{
    return position;
}

void DataCamera::setPosition(const vec3 &pos)
{
    position = pos;
}

void DataCamera::draw() const
{
    glPointSize(pointSize);

    if (smoothed)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    }
    else
    {
        glDisable(GL_POINT_SMOOTH);
        glDisable(GL_BLEND);
    }

    shader.use();
    uint id = shader.getID();

    int world2ViewLoc = glGetUniformLocation(id, "world2View");
    int view2ClipLoc = glGetUniformLocation(id, "view2Clip");

    mat4 world2ViewMat = world2View();
    mat4 view2ClipMat = view2Clip();

    glUniformMatrix4fv(world2ViewLoc, 1, GL_FALSE, glm::value_ptr(world2ViewMat));
    glUniformMatrix4fv(view2ClipLoc, 1, GL_FALSE, glm::value_ptr(view2ClipMat));

    uint VAO = data.getVAO();

    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, data.getSize());
    glBindVertexArray(0);
}

const quat &DataCamera::getRotation() const
{
    return rotation;
}

void DataCamera::setRotation(const quat &rotation)
{
    DataCamera::rotation = rotation;
}

mat4 DataCamera::world2View() const
{
    mat4 matrix (1.0f);
    matrix = glm::translate(matrix, -position);
    return matrix;
}

mat4 DataCamera::view2Clip() const
{
    return glm::perspective(glm::radians(fovy), aspectRatio, nearFrustum, farFrustum);
}

const char *DataCamera::getVertSource()
{
    const char* source =
#include "shaders/basic.vert"
        ;

    return source;
}

const char *DataCamera::getFragSource()
{
    const char* source =
#include "shaders/basic.frag"
    ;

    return source;
}

DataCamera::DataCamera(DataRepresentation data, const vec3 &position, const quat &rotation, float pointSize, float fovy,
                       float aspectRatio, float nearFrustum, float farFrustum, bool smoothed)
                       : data(std::move(data)), position(position),
                       rotation(rotation), fovy(fovy),
                       aspectRatio(aspectRatio), nearFrustum(nearFrustum),
                       farFrustum(farFrustum), pointSize(pointSize),
                       smoothed(smoothed), shader(getVertSource(), getFragSource())
{}

const DataRepresentation &DataCamera::getData() const
{
    return data;
}

void DataCamera::setData(const DataRepresentation &data)
{
    DataCamera::data = data;
}

float DataCamera::getFovy() const
{
    return fovy;
}

void DataCamera::setFovy(float fovy)
{
    DataCamera::fovy = fovy;
}

float DataCamera::getAspectRatio() const
{
    return aspectRatio;
}

void DataCamera::setAspectRatio(float aspectRatio)
{
    DataCamera::aspectRatio = aspectRatio;
}

float DataCamera::getNearFrustum() const
{
    return nearFrustum;
}

void DataCamera::setNearFrustum(float nearFrustum)
{
    DataCamera::nearFrustum = nearFrustum;
}

float DataCamera::getFarFrustum() const
{
    return farFrustum;
}

void DataCamera::setFarFrustum(float farFrustum)
{
    DataCamera::farFrustum = farFrustum;
}

float DataCamera::getPointSize() const
{
    return pointSize;
}

void DataCamera::setPointSize(float pointSize)
{
    DataCamera::pointSize = pointSize;
}

bool DataCamera::isSmoothed() const
{
    return smoothed;
}

void DataCamera::setSmoothed(bool smoothed)
{
    DataCamera::smoothed = smoothed;
}

const Shader &DataCamera::getShader() const
{
    return shader;
}

void DataCamera::setShader(const Shader &shader)
{
    DataCamera::shader = shader;
}
