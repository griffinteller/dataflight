//
// Created by griffinteller on 7/22/21.
//

#ifndef DATAVISUALIZATION_IPOSTPROCESSINGFILTER_H
#define DATAVISUALIZATION_IPOSTPROCESSINGFILTER_H


#include "render/Framebuffer.h"

class IPostprocessingFilter
{
public:
    virtual void Apply(const Framebuffer *dest, const Framebuffer *src, uint screenQuadVAO) = 0;
};


#endif //DATAVISUALIZATION_IPOSTPROCESSINGFILTER_H
