//
// Created by griffinteller on 7/23/21.
//

#include "InvertFilter.h"
#include <stddeps.h>

const char *InvertFilter::getDefaultVertShaderSource()
{
    return
#include <shaders/postprocessing/fullscreenQuad.vert>
        ;
}

const char *InvertFilter::getDefaultFragShaderSource()
{
    return
#include <shaders/postprocessing/invert.frag>
        ;
}

InvertFilter::InvertFilter()
: shader (getDefaultVertShaderSource(), getDefaultFragShaderSource())
{
}

void InvertFilter::Apply(const Framebuffer *dest, const Framebuffer *src, uint screenQuadVAO)
{
    shader.use();

    if (dest == nullptr)
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    else
        glBindFramebuffer(GL_FRAMEBUFFER, dest->getFBO());

    glBindVertexArray(screenQuadVAO);
    glBindTexture(GL_TEXTURE_2D, src->getColorTexture());

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


