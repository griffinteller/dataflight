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
    glEnable(GL_DEPTH_TEST);

    shader.use();

    mat4 world2ViewMat = world2View();
    mat4 view2ClipMat = view2Clip();

    glUniformMatrix4fv(world2ViewLoc, 1, GL_FALSE, glm::value_ptr(world2ViewMat));
    glUniformMatrix4fv(view2ClipLoc, 1, GL_FALSE, glm::value_ptr(view2ClipMat));
    glUniform1f(pointSizeLoc, pointSize);

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

DataCamera::DataCamera(Window &window, DataRepresentation &data, Shader &shader, const Transform &transform,
                       float pointSize,
                       float fovy, float aspectRatio, float nearFrustum, float farFrustum)
                       : window (window), data (data), fovy(fovy), transform (transform),
                         aspectRatio(aspectRatio), nearFrustum(nearFrustum),
                         farFrustum(farFrustum), pointSize(pointSize), shader (shader)
{
    shader.use();
    uint id = shader.getID();

    world2ViewLoc = glGetUniformLocation(id, "world2View");
    view2ClipLoc = glGetUniformLocation(id, "view2Clip");
    pointSizeLoc = glGetUniformLocation(id, "pointSize");
}

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
    aspectRatio = window.getAspect();

    if (!Window::getKeyboardLocked())
    {
        if (glfwGetKey(window.getHandle(), GLFW_KEY_W))
        {
            vec3 back = transform.getBack();
            vec3 toAdd = (float) (-strafeSpeed * window.getDeltaTime()) * back;
            transform.position += toAdd;
        }

        if (glfwGetKey(window.getHandle(), GLFW_KEY_S))
        {
            vec3 back = transform.getBack();
            vec3 toAdd = (float) (strafeSpeed * window.getDeltaTime()) * back;
            transform.position += toAdd;
        }

        if (glfwGetKey(window.getHandle(), GLFW_KEY_A))
        {
            vec3 right = transform.getRight();
            vec3 toAdd = (float) (-strafeSpeed * window.getDeltaTime()) * right;
            transform.position += toAdd;
        }

        if (glfwGetKey(window.getHandle(), GLFW_KEY_D))
        {
            vec3 right = transform.getRight();
            vec3 toAdd = (float) (strafeSpeed * window.getDeltaTime()) * right;
            transform.position += toAdd;
        }

        if (glfwGetKey(window.getHandle(), GLFW_KEY_LEFT_SHIFT))
        {
            vec3 up = transform.getUp();
            vec3 toAdd = (float) (-strafeSpeed * window.getDeltaTime()) * up;
            transform.position += toAdd;
        }

        if (glfwGetKey(window.getHandle(), GLFW_KEY_SPACE))
        {
            vec3 up = transform.getUp();
            vec3 toAdd = (float) (strafeSpeed * window.getDeltaTime()) * up;
            transform.position += toAdd;
        }

        if (glfwGetKey(window.getHandle(), GLFW_KEY_I))
        {
            pointSize *= 1 + pointSizeChangeSpeed * (float) window.getDeltaTime();
        }

        if (glfwGetKey(window.getHandle(), GLFW_KEY_K))
        {
            pointSize /= 1 + pointSizeChangeSpeed * (float) window.getDeltaTime();
        }
    }

    if (!Window::getMouseLocked())
    {
        if (glfwGetMouseButton(window.getHandle(), 0))
        {
            float height = window.getWidthAndHeight().y;
            vec2 deltaDegrees = window.getDeltaCursorPos() * -rotateSpeed / height;
            quat yaw = glm::angleAxis(glm::radians(deltaDegrees.x), vec3(0, 1, 0));
            quat pitch = glm::angleAxis(glm::radians(deltaDegrees.y), transform.getRight());
            transform.rotation = yaw * pitch * transform.rotation;
        }
    }
}

Transform &DataCamera::getTransform()
{
    return transform;
}

void DataCamera::setTransform(const Transform &transform)
{
    DataCamera::transform = transform;
}
