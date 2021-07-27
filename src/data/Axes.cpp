//
// Created by griffinteller on 7/18/21.
//

#include <stddeps.h>
#include <geometry/MeshGeneration.h>
#include "Axes.h"

const vec4 Axes::DefaultColors[] =
        {
            vec4(1.0, 0.0, 0.0, 1.0),
            vec4(0.0, 1.0, 0.0, 1.0),
            vec4(0.0, 0.0, 1.0, 1.0)
        };

Axes::Axes(const vec4 colors[], float range, int verticesPerAxisBase, float baseRadius)
: positiveShader(getSolidVertShaderSource(), getSolidFragShaderSource()),
  negativeShader(getDashedVertShaderSource(), getDashedFragShaderSource()),
  posMeshes {
          MeshGeneration::prism(range, baseRadius, verticesPerAxisBase),
          MeshGeneration::prism(range, baseRadius, verticesPerAxisBase),
          MeshGeneration::prism(range, baseRadius, verticesPerAxisBase)
  },
  negMeshes {
          MeshGeneration::prism(range, baseRadius, verticesPerAxisBase),
          MeshGeneration::prism(range, baseRadius, verticesPerAxisBase),
          MeshGeneration::prism(range, baseRadius, verticesPerAxisBase)
  }
{

}

const char *Axes::getSolidVertShaderSource()
{
    return
#include "shaders/axes/solid.vert"
        ;
}

const char *Axes::getDashedVertShaderSource()
{
    return
#include "shaders/axes/dashed.vert"
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

void Axes::draw(const mat4 &world2View, const mat4 &view2Clip) const
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glEnable(GL_DEPTH_TEST);

    positiveShader.use();
    glUniform4fv()
}
