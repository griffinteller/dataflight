//
// Created by griffinteller on 7/21/21.
//

#ifndef DATAVISUALIZATION_FRAMEBUFFERDRAWABLE_H
#define DATAVISUALIZATION_FRAMEBUFFERDRAWABLE_H


#include <window/CallbackInterfaces.h>
#include <typedefs.h>
#include "Shader.h"
#include "Framebuffer.h"

class FramebufferDrawable : public IDrawable
{
    /*
     * Renders a framebuffer to the currently bound framebuffer (the screen if the bound buffer is 0), applying filters
     * that can be added.
     *
     * Post-Processing shaders lower left to be 0,0 and top right to be 1,1 (this makes texcoords easier).
     *
     * Incoming framebuffers should expect only color buffer 0 to be rendered.
     */

private:
    const Framebuffer &framebuffer;
    uint VAO;
    uint VBO;
    Shader shader;

    static const char *getDefaultVertShaderSource();
    static const char *getDefaultFragShaderSource();

public:
    explicit FramebufferDrawable(const Framebuffer &framebuffer);

    void OnDraw() const override;

    ~FramebufferDrawable();
};


#endif //DATAVISUALIZATION_FRAMEBUFFERDRAWABLE_H
