//
// Created by griffinteller on 7/22/21.
//

#ifndef DATAVISUALIZATION_FXAAFILTER_H
#define DATAVISUALIZATION_FXAAFILTER_H


#include <render/Shader.h>
#include "IPostprocessingFilter.h"

class FXAAFilter : public IPostprocessingFilter
{
private:
    Shader shader;
    int frameBufSizeLoc;

    static const char *getDefaultVertShaderSource();
    static const char *getDefaultFragShaderSource();

public:
    FXAAFilter();

    void Apply(const Framebuffer *dest, const Framebuffer *src, uint screenQuadVAO) override;
};


#endif //DATAVISUALIZATION_FXAAFILTER_H
