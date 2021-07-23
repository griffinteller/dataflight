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
: incomingFramebuffer(framebuffer), VAO(0), VBO(0),
  passthroughShader(getDefaultVertShaderSource(), getDefaultFragShaderSource()),
  intermediateFramebuffer(framebuffer.getWidth(), framebuffer.getHeight(), false)
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

void FramebufferPostprocessing::OnDraw()
{
    if (totalActiveFilters == 0)
    {
        passthroughShader.use();
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, incomingFramebuffer.getColorTexture());
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }
    else if (totalActiveFilters == 1)
    {
        int i = 0;
        while (i < filters.size())
        {
            if (activeFilters[i])
            {
                filters[i]->Apply(nullptr, &incomingFramebuffer, VAO);
                return;
            }

            i++;
        }
    }
    else
    {
        int firstActiveIndex = filters.size();
        int lastActiveIndex = 0;

        for (int i = 0 ; i < filters.size(); i++)
        {
            if (activeFilters[i])
            {
                if (i < firstActiveIndex)
                    firstActiveIndex = i;
                else if (i > lastActiveIndex)  // else is okay because we know there are at least two active filters
                    lastActiveIndex = i;
            }
        }

        int incomingWidth = incomingFramebuffer.getWidth(), incomingHeight = incomingFramebuffer.getHeight();
        int intermediateWidth = intermediateFramebuffer.getWidth(), intermediateHeight = intermediateFramebuffer.getHeight();

        if (incomingWidth != intermediateWidth || incomingHeight != intermediateHeight)
        {
            intermediateFramebuffer.setWidthAndHeight(incomingWidth, incomingHeight);
        }

        intermediateFramebuffer.matchViewport();
        filters[firstActiveIndex]->Apply(&intermediateFramebuffer, &incomingFramebuffer, VAO);

        for (int i = 1; i < filters.size() - 1; i++)
        {
            if (activeFilters[i])
                filters[i]->Apply(&intermediateFramebuffer, &intermediateFramebuffer, VAO);
        }

        filters[lastActiveIndex]->Apply(nullptr, &intermediateFramebuffer, VAO);
    }
}

int FramebufferPostprocessing::addFilter(IPostprocessingFilter *filter, bool active)
{
    filters.push_back(filter);
    activeFilters.push_back(active);

    if (active)
        totalActiveFilters += 1;

    return filters.size() - 1;
}

void FramebufferPostprocessing::setFilterActive(int index, bool active)
{
    bool old = activeFilters[index];

    if (old != active)
    {
        activeFilters[index] = active;

        if (active)
            totalActiveFilters += 1;
        else
            totalActiveFilters -= 1;
    }
}

bool FramebufferPostprocessing::isFilterActive(int index) const
{
    return activeFilters[index];
}
