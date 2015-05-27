/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#ifndef __CC_FRAME_BUFFER_H__
#define __CC_FRAME_BUFFER_H__

#include "base/CCRef.h"
#include "platform/CCGL.h"
#include "renderer/CCTexture2D.h"
#include <set>
NS_CC_BEGIN

class RenderTargetBase : public Ref
{
protected:
    RenderTargetBase();
    virtual ~RenderTargetBase();
    bool init(unsigned int width, unsigned int height);

public:
    unsigned int getWidth() const { return _width; }
    unsigned int getHeight() const { return _height; }
    
protected:
    unsigned int _width;
    unsigned int _height;
    
};

class RenderTarget : public RenderTargetBase
{
public:
    
    static RenderTarget* create(unsigned int width, unsigned int height, Texture2D::PixelFormat format = Texture2D::PixelFormat::RGBA8888);
    
    bool init(unsigned int width, unsigned int height, Texture2D::PixelFormat format);
    
    Texture2D* getTexture() const { return _texture; }
CC_CONSTRUCTOR_ACCESS:
    RenderTarget();
    virtual ~RenderTarget();
    
protected:
    Texture2D* _texture;
};

class RenderTargetDepthStencil : public RenderTargetBase
{
public:
    
    static RenderTargetDepthStencil* create(unsigned int width, unsigned int height);
    
    bool init(unsigned int width, unsigned int height);
    
    GLuint getDepthStencilBuffer() const { return _depthStencilBuffer; }
CC_CONSTRUCTOR_ACCESS:
    RenderTargetDepthStencil();
    virtual ~RenderTargetDepthStencil();
    
protected:
    GLuint _depthStencilBuffer;
};

class CC_DLL FrameBufferObject : public Ref
{
public:
    static FrameBufferObject* create(uint8_t fid, unsigned int width, unsigned int height);
    
    bool init(uint8_t fid, unsigned int width, unsigned int height);
public:
    GLuint getFBO() const { return _fbo; }
    GLuint getFID() const { return _fid; }
    //call glclear to clear frame buffer object
    void clearFBO();
    
    void setClearColor(const Color4F& color) { _clearColor = color;}
    void setClearDepth(float depth) { _clearDepth = depth; }
    void setClearStencil(int8_t stencil) { _clearStencil = stencil; }
    const Color4F& getClearColor() const { return _clearColor; }
    float getClearDepth() const { return _clearDepth; }
    int8_t getClearStencil() const { return _clearStencil; }
    
    RenderTarget* getRenderTarget() const { return _rt; }
    RenderTargetDepthStencil* getDepthStencilTarget() const { return _rtDepthStencil; }
    void AttachRenderTarget(RenderTarget* rt);
    void AttachDepthStencilTarget(RenderTargetDepthStencil* rt);
    
CC_CONSTRUCTOR_ACCESS:
    FrameBufferObject();
    virtual ~FrameBufferObject();
private:
    //openGL content for FrameBuffer
    GLuint _fbo;
    //
    uint8_t _fid;
    //
    Color4F _clearColor;
    float   _clearDepth;
    int8_t  _clearStencil;
    int _width;
    int _height;
    RenderTarget* _rt;
    RenderTargetDepthStencil* _rtDepthStencil;
public:
    static void initDefaultFBO();
    static void applyDefaultFBO();
    static void clearAllFBOs();
private:
    static GLuint _defaultFBO;
    static std::set<FrameBufferObject*> _frameBufferObjects;
};

NS_CC_END

#endif /* defined(__CC_FRAME_BUFFER_H__) */
