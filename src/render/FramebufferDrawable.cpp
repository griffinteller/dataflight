//
// Created by griffinteller on 7/21/21.
//

#include "FramebufferDrawable.h"
#include <stddeps.h>

const char * FramebufferDrawable::getDefaultVertShaderSource()
{
    return
#include "shaders/framebuffer/fullscreenQuad.vert"
        ;
}

const char *FramebufferDrawable::getDefaultFragShaderSource()
{
    return
#include "shaders/framebuffer/fullscreenQuad.frag"
        ;
}

FramebufferDrawable::FramebufferDrawable(const Framebuffer &framebuffer)
: framebuffer(framebuffer), VAO(0), VBO(0), shader(getDefaultVertShaderSource(), getDefaultFragShaderSource())
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // designed to be drawn by GL_TRIANGLE_STRIP
    constexpr float fullscreenQuadVertices[] =
        {
           0, 0,
           1, 0,
           0, 1,
           1, 1
        };

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(fullscreenQuadVertices), fullscreenQuadVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, (void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
 }

FramebufferDrawable::~FramebufferDrawable()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void FramebufferDrawable::OnDraw() const
{
    shader.use();
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, framebuffer.getColorTexture());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
