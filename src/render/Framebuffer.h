//
// Created by griffinteller on 7/22/21.
//

#ifndef DATAVISUALIZATION_FRAMEBUFFER_H
#define DATAVISUALIZATION_FRAMEBUFFER_H


#include <typedefs.h>
#include <window/CallbackInterfaces.h>

class Framebuffer : public IWindowSizeCallback
{
private:
    uint FBO;
    uint colorTexture;
    uint depthStencilBuffer;
    int width;
    int height;
    bool depthAndStencil;
    vec4 clearColor;

public:
    Framebuffer(int width, int height, bool useDepthAndStencil = true, vec4 clearColor = vec4(0, 0, 0, 1));

    uint getFBO() const;
    uint getColorTexture() const;
    uint getDepthStencilBuffer() const;
    int getWidth() const;
    int getHeight() const;
    bool hasDepthAndStencil() const;

    const vec4 &getClearColor() const;

    void setClearColor(const vec4 &clearColor);

    void setWidthAndHeight(int width, int height);
    void OnWindowSize(int width, int height) override;
    void matchViewport() const;

    ~Framebuffer();
};


#endif //DATAVISUALIZATION_FRAMEBUFFER_H
