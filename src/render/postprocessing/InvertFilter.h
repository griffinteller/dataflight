//
// Created by griffinteller on 7/23/21.
//

#ifndef DATAVISUALIZATION_INVERTFILTER_H
#define DATAVISUALIZATION_INVERTFILTER_H


#include <render/Shader.h>
#include "IPostprocessingFilter.h"

class InvertFilter : public IPostprocessingFilter
{
private:
    Shader shader;

    static const char *getDefaultVertShaderSource();
    static const char *getDefaultFragShaderSource();

public:
    InvertFilter();

    void Apply(const Framebuffer *dest, const Framebuffer *src, uint screenQuadVAO) override;
};


#endif //DATAVISUALIZATION_INVERTFILTER_H
