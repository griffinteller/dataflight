//
// Created by griff on 6/29/2021.
//

#include "Transform.h"

Transform::Transform(vec3 position, quat rotation, vec3 scale) : position(position),
                                                                 rotation(rotation), scale(scale)
{}

mat4 Transform::local2World() const
{
    glm::mat4 mat (1.0f);
    mat = glm::translate(mat, position);
    mat *= (mat4) rotation;
    mat = glm::scale(mat, scale);
    return mat;
}

vec3 Transform::getRight() const
{
    return (mat3) rotation * vec3(1.0f, 0.0f, 0.0f);
}

vec3 Transform::getUp() const
{
    return (mat3) rotation * vec3(0.0f, 1.0f, 0.0f);
}

vec3 Transform::getBack() const
{
    return (mat3) rotation * vec3(0.0f, 0.0f, 1.0f);
}


