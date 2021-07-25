//
// Created by griffinteller on 7/22/21.
//

#include "FXAAFilter.h"
#include <stddeps.h>

FXAAFilter::FXAAFilter()
: shader(getDefaultVertShaderSource(), getDefaultFragShaderSource(), nullptr)
{
    frameBufSizeLoc = glGetUniformLocation(shader.getID(), "frameBufSize");
}

const char *FXAAFilter::getDefaultVertShaderSource()
{
    return
#include <shaders/postprocessing/fullscreenQuad.vert>
        ;
}

const char *FXAAFilter::getDefaultFragShaderSource()
{
    return
#include <shaders/postprocessing/fxaa.frag>
        ;
}

void FXAAFilter::Apply(const Framebuffer *dest, const Framebuffer *src, uint screenQuadVAO)
{
    shader.use();

    if (dest == nullptr)
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    else
        glBindFramebuffer(GL_FRAMEBUFFER, dest->getFBO());

    glUniform2f(frameBufSizeLoc, (float) src->getWidth(), (float) src->getHeight());

    glBindVertexArray(screenQuadVAO);
    glBindTexture(GL_TEXTURE_2D, src->getColorTexture());

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
