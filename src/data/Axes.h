//
// Created by griffinteller on 7/18/21.
//

#ifndef DATAVISUALIZATION_AXES_H
#define DATAVISUALIZATION_AXES_H


#include <typedefs.h>
#include <render/Shader.h>
#include <geometry/Mesh.h>
#include <window/CallbackInterfaces.h>

class Axes
{
private:
    Mesh posMeshes[3];
    Mesh negMeshes[3];
    vec4 colors[4];
    Shader positiveShader;
    Shader negativeShader;

    constexpr static uint VertexDataWidth = 7;

    static const char *getSolidVertShaderSource();
    static const char *getDashedVertShaderSource();
    static const char *getSolidFragShaderSource();
    static const char *getDashedFragShaderSource();

public:
    const static vec4 DefaultColors[3];

    // range is radius (ie (-range, range)) for all axes
    explicit Axes(const vec4 colors[], float range, int verticesPerAxisBase, float baseRadius);

    void draw(const mat4 &world2View, const mat4 &view2Clip) const;
};


#endif //DATAVISUALIZATION_AXES_H
