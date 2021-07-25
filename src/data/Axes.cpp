//
// Created by griffinteller on 7/18/21.
//

#include <stddeps.h>
#include "Axes.h"

const vec4 Axes::DefaultColors[] =
        {
            vec4(1.0, 0.0, 0.0, 1.0),
            vec4(0.0, 1.0, 0.0, 1.0),
            vec4(0.0, 0.0, 1.0, 1.0)
        };

Axes::Axes(const vec4 colors[], float range)
: positiveShader(getMainVertShaderSource(), getSolidFragShaderSource(), getMainGeomShaderSource()),
  negativeShader(getMainVertShaderSource(), getDashedFragShaderSource(), getMainGeomShaderSource())
{
    memcpy(Axes::colors, colors, 3 * sizeof(vec4));

    glGenVertexArrays(1, &positiveVAO);
    glGenVertexArrays(1, &negativeVAO);
    glGenBuffers(1, &positiveVBO);
    glGenBuffers(1, &negativeVBO);

    glBindVertexArray(positiveVAO);
    glBindBuffer(GL_ARRAY_BUFFER, positiveVBO);


    const float positiveVerts[] =
            {
                // x quad
                0.0, 0.0, 0.0,
                Axes::colors[0].x, Axes::colors[0].y, Axes::colors[0].z, Axes::colors[0].w,
                range, 0.0, 0.0,
                Axes::colors[0].x, Axes::colors[0].y, Axes::colors[0].z, Axes::colors[0].w,

                // y quad
                0.0, 0.0, 0.0,
                Axes::colors[1].x, Axes::colors[1].y, Axes::colors[1].z, Axes::colors[1].w,
                0.0, range, 0.0,
                Axes::colors[1].x, Axes::colors[1].y, Axes::colors[1].z, Axes::colors[1].w,

                // z quad
                0.0, 0.0, 0.0,
                Axes::colors[2].x, Axes::colors[2].y, Axes::colors[2].z, Axes::colors[2].w,
                0.0, 0.0, range,
                Axes::colors[2].x, Axes::colors[2].y, Axes::colors[2].z, Axes::colors[2].w,
            };

    glBufferData(GL_ARRAY_BUFFER, sizeof(positiveVerts), positiveVerts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * VertexDataWidth, (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(float) * VertexDataWidth, (void *) (sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glBindVertexArray(negativeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, negativeVBO);

    const float negativeVerts[] =
            {
                    // x quad
                    0.0, 0.0, 0.0,
                    Axes::colors[0].x, Axes::colors[0].y, Axes::colors[0].z, Axes::colors[0].w,
                    -range, 0.0, 0.0,
                    Axes::colors[0].x, Axes::colors[0].y, Axes::colors[0].z, Axes::colors[0].w,

                    // y quad
                    0.0, 0.0, 0.0,
                    Axes::colors[1].x, Axes::colors[1].y, Axes::colors[1].z, Axes::colors[1].w,
                    0.0, -range, 0.0,
                    Axes::colors[1].x, Axes::colors[1].y, Axes::colors[1].z, Axes::colors[1].w,

                    // z quad
                    0.0, 0.0, 0.0,
                    Axes::colors[2].x, Axes::colors[2].y, Axes::colors[2].z, Axes::colors[2].w,
                    0.0, 0.0, -range,
                    Axes::colors[2].x, Axes::colors[2].y, Axes::colors[2].z, Axes::colors[2].w,
            };

    glBufferData(GL_ARRAY_BUFFER, sizeof(negativeVerts), negativeVerts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * VertexDataWidth, (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(float) * VertexDataWidth, (void *) (sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

uint Axes::getPositiveVAO() const
{
    return positiveVAO;
}

uint Axes::getNegativeVAO() const
{
    return negativeVAO;
}


const char *Axes::getMainVertShaderSource()
{
    return
#include "shaders/axes/main.vert"
        ;
}

const char *Axes::getSolidFragShaderSource()
{
    return
#include "shaders/axes/solid.frag"
        ;
}

const char *Axes::getDashedFragShaderSource()
{
    return
#include "shaders/axes/dashed.frag"
        ;
}

const Shader &Axes::getPositiveShader() const
{
    return positiveShader;
}

const Shader &Axes::getNegativeShader() const
{
    return negativeShader;
}

Axes::~Axes()
{
    glDeleteVertexArrays(1, &positiveVAO);
    glDeleteVertexArrays(1, &negativeVAO);
    glDeleteBuffers(1, &positiveVBO);
    glDeleteBuffers(1, &negativeVBO);
}

const char *Axes::getMainGeomShaderSource()
{
    return
#include "shaders/axes/main.geom"
        ;
}
