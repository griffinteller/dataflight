//
// Created by griff on 6/29/2021.
//

#ifndef DATAVISUALIZATION_TRANSFORM_H
#define DATAVISUALIZATION_TRANSFORM_H


#include <typedefs.h>

class Transform
{
public:
    vec3 position; // third
    quat rotation; // second
    vec3 scale; // first (no shearing)

    explicit Transform(
            vec3 position= vec3(),
            quat rotation = quat(1.0f, 0.0f, 0.0f, 0.0f),
            vec3 scale = vec3(1.0f, 1.0f, 1.0f));

    mat4 local2World() const;
    vec3 getRight() const;
    vec3 getUp() const;
    vec3 getBack() const;
};


#endif //DATAVISUALIZATION_TRANSFORM_H
