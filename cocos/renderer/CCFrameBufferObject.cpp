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

#include "CCFrameBufferObject.h"

NS_CC_BEGIN

GLuint FrameBufferObject::_defaultFBO(0);
std::set<FrameBufferObject*> FrameBufferObject::_frameBufferObjects;

RenderTargetBase::RenderTargetBase()
{
    
}

RenderTargetBase::~RenderTargetBase()
{
    
}

bool RenderTargetBase::init(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;
    return true;
}

RenderTarget* RenderTarget::create(unsigned int width, unsigned int height, Texture2D::PixelFormat format/* = Texture2D::PixelFormat::RGBA8888*/)
{
    auto result = new (std::nothrow) RenderTarget();
    if(result && result->init(width, height,format))
    {
        result->autorelease();
        return result;
    }
    else
    {
        CC_SAFE_DELETE(result);
        return nullptr;
    }
}

bool RenderTarget::init(unsigned int width, unsigned int height, Texture2D::PixelFormat format)
{
    if(!RenderTargetBase::init(width, height))
    {
        return false;
    }
    
    _texture = new (std::nothrow) Texture2D();
    if(nullptr == _texture) return false;
    auto dataLen = width * height * 4;
    auto data = malloc(dataLen);
    if( nullptr == data) return false;
    
    memset(data, 0, dataLen);
    if(_texture->initWithData(data, dataLen, format, width, height, Size(width, height)))
    {
        _texture->autorelease();
        CC_SAFE_RETAIN(_texture);
        free(data);
    }
    else
    {
        CC_SAFE_DELETE(_texture);
        free(data);
        return false;
    }
    return true;
}

RenderTarget::RenderTarget()
: _texture(nullptr)
{
}

RenderTarget::~RenderTarget()
{
    CC_SAFE_RELEASE_NULL(_texture);
}

RenderTargetDepthStencil::RenderTargetDepthStencil()
: _depthStencilBuffer(0)
{
}

RenderTargetDepthStencil::~RenderTargetDepthStencil()
{
    if(glIsRenderbuffer(_depthStencilBuffer))
    {
        glDeleteRenderbuffers(1, &_depthStencilBuffer);
        _depthStencilBuffer = 0;
    }
}

bool RenderTargetDepthStencil::init(unsigned int width, unsigned int height)
{
    if(!RenderTargetBase::init(width, height)) return false;
    GLint oldRenderBuffer(0);
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRenderBuffer);
    
    //generate depthStencil
    glGenRenderbuffers(1, &_depthStencilBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthStencilBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, oldRenderBuffer);
    return true;
}


RenderTargetDepthStencil* RenderTargetDepthStencil::create(unsigned int width, unsigned int height)
{
    auto result = new (std::nothrow) RenderTargetDepthStencil();
    
    if(result && result->init(width, height))
    {
        result->autorelease();
        return result;
    }
    else
    {
        CC_SAFE_DELETE(result);
        return nullptr;
    }
}

void FrameBufferObject::initDefaultFBO()
{
    GLint fbo;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &fbo);
    _defaultFBO = fbo;
}

void FrameBufferObject::applyDefaultFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, _defaultFBO);
}

void FrameBufferObject::clearAllFBOs()
{
    for (auto fbo : _frameBufferObjects)
    {
        fbo->clearFBO();
    }
}

FrameBufferObject* FrameBufferObject::create(uint8_t fid, unsigned int width, unsigned int height)
{
    auto result = new (std::nothrow) FrameBufferObject();
    if(result && result->init(fid, width, height))
    {
        result->autorelease();
        return result;
    }
    else
    {
        CC_SAFE_DELETE(result);
        return nullptr;
    }
}

bool FrameBufferObject::init(uint8_t fid, unsigned int width, unsigned int height)
{
    _fid = fid;
    _width = width;
    _height = height;
    
//    _rt = RenderTarget::create(width, height);
//    if(nullptr == _rt) return false;

    
    //generate Frame buffer object
    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    applyDefaultFBO();
    return true;
}

FrameBufferObject::FrameBufferObject()
: _clearColor(Color4F(0, 0, 0, 1))
, _clearDepth(1.0)
, _clearStencil(0)
, _fbo(0)
, _rt(nullptr)
, _rtDepthStencil(nullptr)
{
    _frameBufferObjects.insert(this);
}

FrameBufferObject::~FrameBufferObject()
{
    CC_SAFE_RELEASE_NULL(_rt);
    CC_SAFE_RELEASE_NULL(_rtDepthStencil);
    glDeleteFramebuffers(1, &_fbo);
    _fbo = 0;
    _frameBufferObjects.erase(this);
}

void FrameBufferObject::clearFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
    glClearDepth(_clearDepth);
    glClearStencil(_clearStencil);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    applyDefaultFBO();
}

void FrameBufferObject::AttachRenderTarget(RenderTarget* rt)
{
    CC_ASSERT(rt);
    if(rt->getWidth() != _width || rt->getHeight() != _height)
    {
        CCLOG("Error, attach a render target with different size, Skip.");
        return;
    }
    CC_SAFE_RETAIN(rt);
    CC_SAFE_RELEASE(_rt);
    _rt = rt;
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _rt->getTexture()->getName(), 0);
    applyDefaultFBO();
}

void FrameBufferObject::AttachDepthStencilTarget(RenderTargetDepthStencil* rt)
{
    CC_ASSERT(rt);
    if(rt->getWidth() != _width || rt->getHeight() != _height)
    {
        CCLOG("Error, attach a render target Depth stencil with different size, Skip.");
        return;
    }
    CC_SAFE_RETAIN(rt);
    CC_SAFE_RELEASE(_rtDepthStencil);
    _rtDepthStencil = rt;
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _rtDepthStencil->getDepthStencilBuffer());
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rtDepthStencil->getDepthStencilBuffer());
    
    applyDefaultFBO();
}
NS_CC_END