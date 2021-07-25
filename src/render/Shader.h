//
// Created by griff on 6/27/2021.
//

#ifndef DATAVISUALIZATION_SHADER_H
#define DATAVISUALIZATION_SHADER_H


#include <typedefs.h>

class Shader
{
private:
    uint ID;

    static uint compileProgram(const char *vert, const char *frag, const char *geom = nullptr);

public:
    Shader(const char *vertexPath, const char *fragmentPath, const char *geometrySource = nullptr);

    void use() const;

    uint getID() const;

    ~Shader();
};


#endif //DATAVISUALIZATION_SHADER_H
