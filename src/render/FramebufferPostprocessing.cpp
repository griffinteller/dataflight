//
// Created by griffinteller on 7/21/21.
//

#include "FramebufferPostprocessing.h"
#include <stddeps.h>
#include <stdexcept>

const char * FramebufferPostprocessing::getDefaultVertShaderSource()
{
    return
#include "shaders/postprocessing/fullscreenQuad.vert"
        ;
}

const char *FramebufferPostprocessing::getDefaultFragShaderSource()
{
    return
#include "shaders/postprocessing/fullscreenQuad.frag"
        ;
}

FramebufferPostprocessing::FramebufferPostprocessing(const Framebuffer &framebuffer)
: incomingFramebuffer(framebuffer), VAO(0), VBO(0), passthroughShader(getDefaultVertShaderSource(), getDefaultFragShaderSource())
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

FramebufferPostprocessing::~FramebufferPostprocessing()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void FramebufferPostprocessing::OnDraw() const
{
    if (filters.empty() || !activeFilters[0])
    {
        passthroughShader.use();
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, incomingFramebuffer.getColorTexture());
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }
    else if (filters.size() == 1)
    {
        filters[0]->Apply(nullptr, &incomingFramebuffer, VAO);
    } else
    {
        throw std::domain_error("More than 1 postprocessing filter is not supported at this time.");
    }
}

int FramebufferPostprocessing::addFilter(IPostprocessingFilter *filter, bool active)
{
    filters.push_back(filter);
    activeFilters.push_back(active);
    return filters.size() - 1;
}

void FramebufferPostprocessing::setFilterActive(int index, bool active)
{
    activeFilters[index] = active;
}

bool FramebufferPostprocessing::isFilterActive(int index) const
{
    return activeFilters[index];
}
