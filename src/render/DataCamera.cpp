//
// Created by griff on 6/27/2021.
//

#include <glad/glad.h>
#include <utility>
#include <iostream>
#include "DataCamera.h"

void DataCamera::OnDraw() const
{
    glEnable(GL_PROGRAM_POINT_SIZE);

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
    glDrawArrays(GL_POINTS, 0, data.getSize() - 3);
    glBindVertexArray(0);
}

mat4 DataCamera::world2View() const
{
    return glm::inverse(transform.local2World());
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

DataCamera::DataCamera(Window *window, DataRepresentation data, const Transform &transform, float pointSize, float fovy,
                       float aspectRatio, float nearFrustum, float farFrustum, bool smoothed)
                       : window(window), data(std::move(data)), fovy(fovy), transform (transform),
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

void DataCamera::OnFrame()
{
    if (glfwGetKey(window->getHandle(), GLFW_KEY_W))
    {
        vec3 back = transform.getBack();
        vec3 toAdd = (float) (-strafeSpeed * window->getDeltaTime()) * back;
        transform.position += toAdd;
    }

    if (glfwGetKey(window->getHandle(), GLFW_KEY_S))
    {
        vec3 back = transform.getBack();
        vec3 toAdd = (float) (strafeSpeed * window->getDeltaTime()) * back;
        transform.position += toAdd;
    }

    if (glfwGetKey(window->getHandle(), GLFW_KEY_A))
    {
        vec3 right = transform.getRight();
        vec3 toAdd = (float) (-strafeSpeed * window->getDeltaTime()) * right;
        transform.position += toAdd;
    }

    if (glfwGetKey(window->getHandle(), GLFW_KEY_D))
    {
        vec3 right = transform.getRight();
        vec3 toAdd = (float) (strafeSpeed * window->getDeltaTime()) * right;
        transform.position += toAdd;
    }

    if (glfwGetKey(window->getHandle(), GLFW_KEY_LEFT_SHIFT))
    {
        vec3 up = transform.getUp();
        vec3 toAdd = (float) (-strafeSpeed * window->getDeltaTime()) * up;
        transform.position += toAdd;
    }

    if (glfwGetKey(window->getHandle(), GLFW_KEY_SPACE))
    {
        vec3 up = transform.getUp();
        vec3 toAdd = (float) (strafeSpeed * window->getDeltaTime()) * up;
        transform.position += toAdd;
    }

    if (glfwGetMouseButton(window->getHandle(), 0))
    {
        vec2 deltaDegrees = window->getDeltaCursorPos() * -rotateSpeed;
        quat yaw = glm::angleAxis(glm::radians(deltaDegrees.x), vec3(0, 1, 0));
        quat pitch = glm::angleAxis(glm::radians(deltaDegrees.y), transform.getRight());
        transform.rotation = yaw * pitch * transform.rotation;
    }
}

const Transform &DataCamera::getTransform() const
{
    return transform;
}

void DataCamera::setTransform(const Transform &transform)
{
    DataCamera::transform = transform;
}
