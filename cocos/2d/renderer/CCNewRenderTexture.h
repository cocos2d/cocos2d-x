/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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
