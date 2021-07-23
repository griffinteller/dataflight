//
// Created by griffinteller on 7/21/21.
//

#ifndef DATAVISUALIZATION_FRAMEBUFFERPOSTPROCESSING_H
#define DATAVISUALIZATION_FRAMEBUFFERPOSTPROCESSING_H


#include <window/CallbackInterfaces.h>
#include <typedefs.h>
#include <vector>
#include <render/postprocessing/IPostprocessingFilter.h>
#include "Shader.h"
#include "Framebuffer.h"

class FramebufferPostprocessing : public IDrawable
{
    /*
     * Renders a postprocessing to the currently bound postprocessing (the screen if the bound buffer is 0), applying filters
     * that can be added.
     *
     * Post-Processing shaders lower left to be 0,0 and top right to be 1,1 (this makes texcoords easier).
     *
     * Incoming framebuffers should expect only color buffer 0 to be rendered.
     */

private:
    const Framebuffer &incomingFramebuffer;
    uint VAO;
    uint VBO;
    Shader passthroughShader;
    std::vector<IPostprocessingFilter*> filters{};

    static const char *getDefaultVertShaderSource();
    static const char *getDefaultFragShaderSource();

public:
    explicit FramebufferPostprocessing(const Framebuffer &framebuffer);

    void OnDraw() const override;

    void addFilter(IPostprocessingFilter *filter);

    ~FramebufferPostprocessing();
};


#endif //DATAVISUALIZATION_FRAMEBUFFERPOSTPROCESSING_H
