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
    
    _colorTexture = new (std::nothrow) Texture2D();
    auto dataLen = width * height * 4;
    auto data = malloc(dataLen);
    if(nullptr == data || nullptr == _colorTexture)
        return false;
    
    memset(data, 0, dataLen);
    _colorTexture->initWithData(data, dataLen, Texture2D::PixelFormat::RGBA8888, width, height, Size(width, height));
    free(data);
    
    GLint oldRenderBuffer(0);
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRenderBuffer);
    
    //generate depthStencil
    glGenRenderbuffers(1, &_depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, oldRenderBuffer);
    //generate Frame buffer object
    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _depthBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorTexture->getName(), 0);
    applyDefaultFBO();
    return true;
}

FrameBufferObject::FrameBufferObject()
: _clearColor(Color4F(0, 0, 0, 1))
, _clearDepth(1.0)
, _clearStencil(0)
, _colorTexture(nullptr)
{
    _frameBufferObjects.insert(this);
}

FrameBufferObject::~FrameBufferObject()
{
    CC_SAFE_RELEASE_NULL(_colorTexture);
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

NS_CC_END