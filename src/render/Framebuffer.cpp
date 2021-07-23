//
// Created by griffinteller on 7/22/21.
//

#include "Framebuffer.h"
#include <stddeps.h>
#include <stdexcept>

uint Framebuffer::getFBO() const
{
    return FBO;
}

uint Framebuffer::getColorTexture() const
{
    return colorTexture;
}

uint Framebuffer::getDepthStencilBuffer() const
{
    return depthStencilBuffer;
}

Framebuffer::Framebuffer(int width, int height, bool useDepthAndStencil, vec4 clearColor)
: FBO (0), colorTexture (0), depthStencilBuffer (0), width (width), height (height), depthAndStencil(useDepthAndStencil),
  clearColor (clearColor)
{
    glGenFramebuffers(1, &FBO);
    glGenTextures(1, &colorTexture);

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (useDepthAndStencil)
    {
        glGenRenderbuffers(1, &depthStencilBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthStencilBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencilBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        throw std::runtime_error("Failed to create postprocessing!");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int Framebuffer::getWidth() const
{
    return width;
}

int Framebuffer::getHeight() const
{
    return height;
}

void Framebuffer::OnWindowSize(int width, int height)
{
    setWidthAndHeight(width, height);
}

void Framebuffer::setWidthAndHeight(int width, int height)
{
    Framebuffer::width = width;
    Framebuffer::height = height;

    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Framebuffer::hasDepthAndStencil() const
{
    return depthAndStencil;
}

void Framebuffer::matchViewport() const
{
    glViewport(0, 0, width, height);
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &FBO);
    glDeleteTextures(1, &colorTexture);

    if (depthAndStencil)
    {
        glDeleteRenderbuffers(1, &depthStencilBuffer);
    }
}

const vec4 &Framebuffer::getClearColor() const
{
    return clearColor;
}

void Framebuffer::setClearColor(const vec4 &clearColor)
{
    Framebuffer::clearColor = clearColor;
}
