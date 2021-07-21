//
// Created by griff on 6/27/2021.
//

#include <glad/glad.h>
#include <iostream>
#include "DataCamera.h"

void DataCamera::OnDraw() const
{
    drawAxes();

    if (data != nullptr)
        drawPoints();
}

mat4 DataCamera::world2View() const
{
    return glm::inverse(transform.local2World());
}

mat4 DataCamera::view2Clip() const
{
    return glm::perspective(glm::radians(fovy), aspectRatio, nearFrustum, farFrustum);
}

DataCamera::DataCamera(Window *window, DataRepresentation *data, Axes *axes,
                       const Transform &transform,
                       float pointSize, float fovy, float aspectRatio, float nearFrustum, float farFrustum,
                       float axisWidth, float dashLength)
                       : window (window), data (data), fovy(fovy), transform (transform),
                         aspectRatio(aspectRatio), nearFrustum(nearFrustum),
                         farFrustum(farFrustum), pointSize(pointSize),
                         axisWidth(axisWidth), axes (axes), dashLength(dashLength)
{
    if (data != nullptr)
        loadDataLocs();

    axes->getPositiveShader().use();
    uint id = axes->getPositiveShader().getID();

    axesPosWorld2ViewLoc = glGetUniformLocation(id, "world2View");
    axesPosView2ClipLoc = glGetUniformLocation(id, "view2Clip");

    axes->getNegativeShader().use();
    id = axes->getNegativeShader().getID();

    axesNegWorld2ViewLoc = glGetUniformLocation(id, "world2View");
    axesNegView2ClipLoc = glGetUniformLocation(id, "view2Clip");
    dashLengthLoc = glGetUniformLocation(id, "dashLength");
}

DataRepresentation * DataCamera::getData() const
{
    return data;
}

void DataCamera::setData(DataRepresentation *data)
{
    DataCamera::data = data;
    loadDataLocs();
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

void DataCamera::OnFrame()
{
    aspectRatio = window->getAspect();

    if (!Window::getKeyboardLocked())
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

        if (glfwGetKey(window->getHandle(), GLFW_KEY_I))
        {
            pointSize *= 1 + pointSizeChangeSpeed * (float) window->getDeltaTime();
        }

        if (glfwGetKey(window->getHandle(), GLFW_KEY_K))
        {
            pointSize /= 1 + pointSizeChangeSpeed * (float) window->getDeltaTime();
        }
    }

    if (!Window::getMouseLocked())
    {
        if (glfwGetMouseButton(window->getHandle(), 0))
        {
            float height = window->getWidthAndHeight().y;
            vec2 deltaDegrees = window->getDeltaCursorPos() * -rotateSpeed / height;
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

void DataCamera::setTransform(Transform transform)
{
    DataCamera::transform = transform;
}

void DataCamera::drawPoints() const
{
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);

    data->getShader().use();

    mat4 world2ViewMat = world2View();
    mat4 view2ClipMat = view2Clip();

    glUniformMatrix4fv(dataWorld2ViewLoc, 1, GL_FALSE, glm::value_ptr(world2ViewMat));
    glUniformMatrix4fv(dataView2ClipLoc, 1, GL_FALSE, glm::value_ptr(view2ClipMat));
    glUniform1f(pointSizeLoc, pointSize);

    uint VAO = data->getVAO();

    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, data->getPoints());
    glBindVertexArray(0);
}

void DataCamera::drawAxes() const
{
    glEnable(GL_DEPTH_TEST);

    glLineWidth(axisWidth);

    glBindVertexArray(axes->getPositiveVAO());
    axes->getPositiveShader().use();

    mat4 world2ViewMat = world2View();
    mat4 view2ClipMat = view2Clip();

    glUniformMatrix4fv(axesPosWorld2ViewLoc, 1, GL_FALSE, glm::value_ptr(world2ViewMat));
    glUniformMatrix4fv(axesPosView2ClipLoc, 1, GL_FALSE, glm::value_ptr(view2ClipMat));

    glDrawArrays(GL_LINES, 0, 6);

    glBindVertexArray(axes->getNegativeVAO());
    axes->getNegativeShader().use();

    glUniformMatrix4fv(axesNegWorld2ViewLoc, 1, GL_FALSE, glm::value_ptr(world2ViewMat));
    glUniformMatrix4fv(axesNegView2ClipLoc, 1, GL_FALSE, glm::value_ptr(view2ClipMat));
    glUniform1f(dashLengthLoc, dashLength);

    glDrawArrays(GL_LINES, 0, 6);

    glBindVertexArray(0);
}

float DataCamera::getAxisWidth() const {
    return axisWidth;
}

void DataCamera::setAxisWidth(float axisWidth) {
    DataCamera::axisWidth = axisWidth;
}

float DataCamera::getDashLength() const {
    return dashLength;
}

void DataCamera::setDashLength(float dashLength) {
    DataCamera::dashLength = dashLength;
}

float DataCamera::getStrafeSpeed() const
{
    return strafeSpeed;
}

void DataCamera::setStrafeSpeed(float strafeSpeed)
{
    DataCamera::strafeSpeed = strafeSpeed;
}

float DataCamera::getRotateSpeed() const
{
    return rotateSpeed;
}

void DataCamera::setRotateSpeed(float rotateSpeed)
{
    DataCamera::rotateSpeed = rotateSpeed;
}

void DataCamera::loadDataLocs()
{
    data->getShader().use();
    uint id = data->getShader().getID();

    dataWorld2ViewLoc = glGetUniformLocation(id, "world2View");
    dataView2ClipLoc = glGetUniformLocation(id, "view2Clip");
    pointSizeLoc = glGetUniformLocation(id, "pointSize");
}
