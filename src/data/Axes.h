//
// Created by griffinteller on 7/18/21.
//

#ifndef DATAVISUALIZATION_AXES_H
#define DATAVISUALIZATION_AXES_H


#include <typedefs.h>
#include <render/Shader.h>

class Axes {

private:
    uint positiveVAO;
    uint negativeVAO;  // will be dashed, dotted, etc, so needs diff dataShader
    uint positiveVBO;
    uint negativeVBO;
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
    explicit Axes(const vec4 colors[], float range = 50);

    uint getPositiveVAO() const;
    uint getNegativeVAO() const;
    const Shader &getPositiveShader() const;
    const Shader &getNegativeShader() const;
};


#endif //DATAVISUALIZATION_AXES_H
