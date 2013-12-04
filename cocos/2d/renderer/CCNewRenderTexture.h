//
// Created by NiTe Luo on 12/2/13.
//



#ifndef __CCNewRenderTexture_H_
#define __CCNewRenderTexture_H_

#include "CCRenderTexture.h"

NS_CC_BEGIN

class NewRenderTexture : public RenderTexture
{
public:
    static NewRenderTexture* create(int w, int h, Texture2D::PixelFormat eFormat, GLuint uDepthStencilFormat);
    static NewRenderTexture* create(int w, int h, Texture2D::PixelFormat eFormat);
    static NewRenderTexture* create(int w, int h);

    void beginWithClear(float r, float g, float b, float a);
    void beginWithClear(float r, float g, float b, float a, float depthValue);
    void beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue);
    void beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue, GLbitfield flags);

    virtual void begin() override;
    virtual void end() override;
    virtual void draw() override;

    void clearDepth(float depthValue);

protected:
    NewRenderTexture();
    virtual ~NewRenderTexture();

    void onBegin();
    void onEnd();

    //Clear render buffer
    void onClear();
    void onClearDepth();

    kmMat4 _oldTransMatrix, _oldProjMatrix;
    kmMat4 _transformMatrix, _projectionMatrix;
};

NS_CC_END

#endif //__CCNewRenderTexture_H_
