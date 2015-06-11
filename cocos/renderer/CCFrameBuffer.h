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

class GLView;
class EventListenerCustom;

namespace experimental {

/**
 Viewport is a normalized to FrameBufferObject
 But for default FBO, the size is absolute.
 */
struct CC_DLL Viewport
{
    Viewport(float left, float bottom, float width, float height);
    Viewport();
    
    float _left;
    float _bottom;
    float _width;
    float _height;
};
    
class CC_DLL RenderTargetBase : public Ref
{
public:
    enum class Type
    {
        RenderBuffer,
        Texture2D,
    };
protected:
    RenderTargetBase();
    virtual ~RenderTargetBase();
    bool init(unsigned int width, unsigned int height);

public:
    
    virtual Texture2D* getTexture() const { return nullptr; }
    virtual GLuint getBuffer() const { return 0; }
    
    unsigned int getWidth() const { return _width; }
    unsigned int getHeight() const { return _height; }
    Type getType() const { return _type; }
protected:
    Type _type;
    unsigned int _width;
    unsigned int _height;
    
};

class CC_DLL RenderTarget : public RenderTargetBase
{
public:
    
    static RenderTarget* create(unsigned int width, unsigned int height, Texture2D::PixelFormat format = Texture2D::PixelFormat::RGBA8888);
    
    bool init(unsigned int width, unsigned int height, Texture2D::PixelFormat format);
    
    virtual Texture2D* getTexture() const { return _texture; }
CC_CONSTRUCTOR_ACCESS:
    RenderTarget();
    virtual ~RenderTarget();
    
protected:
    Texture2D* _texture;
#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _rebuildTextureListener;
#endif
};

class CC_DLL RenderTargetRenderBuffer : public RenderTargetBase
{
public:
    
    static RenderTargetRenderBuffer* create(unsigned int width, unsigned int height);
    
    bool init(unsigned int width, unsigned int height);
    
    virtual GLuint getBuffer() const { return _colorBuffer; }
    
CC_CONSTRUCTOR_ACCESS:
    RenderTargetRenderBuffer();
    virtual ~RenderTargetRenderBuffer();
    
protected:
    GLenum _format;
    GLuint _colorBuffer;
#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _reBuildRenderBufferListener;
#endif
};

class CC_DLL RenderTargetDepthStencil : public RenderTargetBase
{
public:
    
    static RenderTargetDepthStencil* create(unsigned int width, unsigned int height);
    
    bool init(unsigned int width, unsigned int height);
    
    virtual GLuint getBuffer() const { return _depthStencilBuffer; }
    
    CC_DEPRECATED(3.7) GLuint getDepthStencilBuffer() const { return _depthStencilBuffer; }
CC_CONSTRUCTOR_ACCESS:
    RenderTargetDepthStencil();
    virtual ~RenderTargetDepthStencil();
    
protected:

    GLuint _depthStencilBuffer;
#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _reBuildDepthStencilListener;
#endif
};

class CC_DLL FrameBuffer : public Ref
{
public:
    static FrameBuffer* create(uint8_t fid, unsigned int width, unsigned int height);
    
    bool init(uint8_t fid, unsigned int width, unsigned int height);
public:
    GLuint getFBO() const { return _fbo; }
    GLuint getFID() const { return _fid; }
    //call glclear to clear frame buffer object
    void clearFBO();
    void applyFBO();
    void setClearColor(const Color4F& color) { _clearColor = color;}
    void setClearDepth(float depth) { _clearDepth = depth; }
    void setClearStencil(int8_t stencil) { _clearStencil = stencil; }
    const Color4F& getClearColor() const { return _clearColor; }
    float getClearDepth() const { return _clearDepth; }
    int8_t getClearStencil() const { return _clearStencil; }
    
    RenderTargetBase* getRenderTarget() const { return _rt; }
    RenderTargetDepthStencil* getDepthStencilTarget() const { return _rtDepthStencil; }
    void attachRenderTarget(RenderTargetBase* rt);
    void attachDepthStencilTarget(RenderTargetDepthStencil* rt);
    
    bool isDefaultFBO() const { return _isDefault; }
    unsigned int getWidth() const { return _width; }
    unsigned int getHeight() const { return _height; }

CC_CONSTRUCTOR_ACCESS:
    FrameBuffer();
    virtual ~FrameBuffer();
    bool initWithGLView(GLView* view);
private:
    //openGL content for FrameBuffer
    GLuint _fbo;
    //dirty flag for fbo binding
    bool _fboBindingDirty;
    //
    uint8_t _fid;
    //
    Color4F _clearColor;
    float   _clearDepth;
    int8_t  _clearStencil;
    int _width;
    int _height;
    RenderTargetBase* _rt;
    RenderTargetDepthStencil* _rtDepthStencil;
    bool _isDefault;
public:
    static FrameBuffer* getOrCreateDefaultFBO(GLView* glView);
    static void applyDefaultFBO();
    static void clearAllFBOs();
private:
    //static GLuint _defaultFBO;
    static FrameBuffer* _defaultFBO;
    static std::set<FrameBuffer*> _frameBuffers;
    
private:
#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _dirtyFBOListener;
#endif
};
} // end of namespace experimental

NS_CC_END

#endif /* defined(__CC_FRAME_BUFFER_H__) */
