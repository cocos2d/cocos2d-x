/****************************************************************************
Copyright (c) 2009      Jason Booth
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "CCConfiguration.h"
#include "CCRenderTexture.h"
#include "CCDirector.h"
#include "platform/CCImage.h"
#include "CCGLProgram.h"
#include "ccGLStateCache.h"
#include "CCConfiguration.h"
#include "ccUtils.h"
#include "CCTextureCache.h"
#include "platform/CCFileUtils.h"
#include "CCGL.h"
#include "CCEventType.h"
#include "CCGrid.h"

#include "renderer/CCRenderer.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCCustomCommand.h"

// extern
#include "kazmath/GL/matrix.h"
#include "CCEventListenerCustom.h"
#include "CCEventDispatcher.h"

NS_CC_BEGIN

// implementation RenderTexture
RenderTexture::RenderTexture()
: _FBO(0)
, _depthRenderBufffer(0)
, _oldFBO(0)
, _texture(0)
, _textureCopy(0)
, _UITextureImage(nullptr)
, _pixelFormat(Texture2D::PixelFormat::RGBA8888)
, _clearFlags(0)
, _clearColor(Color4F(0,0,0,0))
, _clearDepth(0.0f)
, _clearStencil(0)
, _autoDraw(false)
, _sprite(nullptr)
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    // Listen this event to save render texture before come to background.
    // Then it can be restored after coming to foreground on Android.
    auto toBackgroundListener = EventListenerCustom::create(EVENT_COME_TO_BACKGROUND, CC_CALLBACK_1(RenderTexture::listenToBackground, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(toBackgroundListener, this);

    auto toForegroundListener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, CC_CALLBACK_1(RenderTexture::listenToForeground, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(toForegroundListener, this);
#endif
}

RenderTexture::~RenderTexture()
{
    CC_SAFE_RELEASE(_sprite);
    CC_SAFE_RELEASE(_textureCopy);
    
    glDeleteFramebuffers(1, &_FBO);
    if (_depthRenderBufffer)
    {
        glDeleteRenderbuffers(1, &_depthRenderBufffer);
    }
    CC_SAFE_DELETE(_UITextureImage);
}

void RenderTexture::listenToBackground(EventCustom *event)
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    CC_SAFE_DELETE(_UITextureImage);
    
    // to get the rendered texture data
    _UITextureImage = newImage(false);

    if (_UITextureImage)
    {
        const Size& s = _texture->getContentSizeInPixels();
        VolatileTextureMgr::addDataTexture(_texture, _UITextureImage->getData(), s.width * s.height * 4, Texture2D::PixelFormat::RGBA8888, s);
        
        if ( _textureCopy )
        {
            VolatileTextureMgr::addDataTexture(_textureCopy, _UITextureImage->getData(), s.width * s.height * 4, Texture2D::PixelFormat::RGBA8888, s);
        }
    }
    else
    {
        CCLOG("Cache rendertexture failed!");
    }
    
    glDeleteFramebuffers(1, &_FBO);
    _FBO = 0;
#endif
}

void RenderTexture::listenToForeground(EventCustom *event)
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    // -- regenerate frame buffer object and attach the texture
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_oldFBO);
    
    glGenFramebuffers(1, &_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
    
    _texture->setAliasTexParameters();
    
    if ( _textureCopy )
    {
        _textureCopy->setAliasTexParameters();
    }
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture->getName(), 0);
    glBindFramebuffer(GL_FRAMEBUFFER, _oldFBO);
#endif
}

RenderTexture * RenderTexture::create(int w, int h, Texture2D::PixelFormat eFormat)
{
    RenderTexture *ret = new RenderTexture();

    if(ret && ret->initWithWidthAndHeight(w, h, eFormat))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

RenderTexture * RenderTexture::create(int w ,int h, Texture2D::PixelFormat eFormat, GLuint uDepthStencilFormat)
{
    RenderTexture *ret = new RenderTexture();

    if(ret && ret->initWithWidthAndHeight(w, h, eFormat, uDepthStencilFormat))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

RenderTexture * RenderTexture::create(int w, int h)
{
    RenderTexture *ret = new RenderTexture();

    if(ret && ret->initWithWidthAndHeight(w, h, Texture2D::PixelFormat::RGBA8888, 0))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool RenderTexture::initWithWidthAndHeight(int w, int h, Texture2D::PixelFormat eFormat)
{
    return initWithWidthAndHeight(w, h, eFormat, 0);
}

bool RenderTexture::initWithWidthAndHeight(int w, int h, Texture2D::PixelFormat format, GLuint depthStencilFormat)
{
    CCASSERT(format != Texture2D::PixelFormat::A8, "only RGB and RGBA formats are valid for a render texture");

    bool ret = false;
    void *data = nullptr;
    do 
    {
        w = (int)(w * CC_CONTENT_SCALE_FACTOR());
        h = (int)(h * CC_CONTENT_SCALE_FACTOR());

        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_oldFBO);

        // textures must be power of two squared
        int powW = 0;
        int powH = 0;

        if (Configuration::getInstance()->supportsNPOT())
        {
            powW = w;
            powH = h;
        }
        else
        {
            powW = ccNextPOT(w);
            powH = ccNextPOT(h);
        }

        auto dataLen = powW * powH * 4;
        data = malloc(dataLen);
        CC_BREAK_IF(! data);

        memset(data, 0, dataLen);
        _pixelFormat = format;

        _texture = new Texture2D();
        if (_texture)
        {
            _texture->initWithData(data, dataLen, (Texture2D::PixelFormat)_pixelFormat, powW, powH, Size((float)w, (float)h));
        }
        else
        {
            break;
        }
        GLint oldRBO;
        glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRBO);
        
        if (Configuration::getInstance()->checkForGLExtension("GL_QCOM"))
        {
            _textureCopy = new Texture2D();
            if (_textureCopy)
            {
                _textureCopy->initWithData(data, dataLen, (Texture2D::PixelFormat)_pixelFormat, powW, powH, Size((float)w, (float)h));
            }
            else
            {
                break;
            }
        }

        // generate FBO
        glGenFramebuffers(1, &_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, _FBO);

        // associate texture with FBO
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture->getName(), 0);

        if (depthStencilFormat != 0)
        {
            //create and attach depth buffer
            glGenRenderbuffers(1, &_depthRenderBufffer);
            glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBufffer);
            glRenderbufferStorage(GL_RENDERBUFFER, depthStencilFormat, (GLsizei)powW, (GLsizei)powH);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBufffer);

            // if depth format is the one with stencil part, bind same render buffer as stencil attachment
            if (depthStencilFormat == GL_DEPTH24_STENCIL8)
            {
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBufffer);
            }
        }

        // check if it worked (probably worth doing :) )
        CCASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Could not attach texture to framebuffer");

        _texture->setAliasTexParameters();

        // retained
        setSprite(Sprite::createWithTexture(_texture));

        _texture->release();
        _sprite->setScaleY(-1);

        _sprite->setBlendFunc( BlendFunc::ALPHA_PREMULTIPLIED );

        glBindRenderbuffer(GL_RENDERBUFFER, oldRBO);
        glBindFramebuffer(GL_FRAMEBUFFER, _oldFBO);
        
        // Diabled by default.
        _autoDraw = false;
        
        // add sprite for backward compatibility
        addChild(_sprite);
        
        ret = true;
    } while (0);
    
    CC_SAFE_FREE(data);
    
    return ret;
}

void RenderTexture::beginWithClear(float r, float g, float b, float a)
{
    beginWithClear(r, g, b, a, 0, 0, GL_COLOR_BUFFER_BIT);
}

void RenderTexture::beginWithClear(float r, float g, float b, float a, float depthValue)
{
    beginWithClear(r, g, b, a, depthValue, 0, GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void RenderTexture::beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue)
{
    beginWithClear(r, g, b, a, depthValue, stencilValue, GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}

void RenderTexture::beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue, GLbitfield flags)
{
    setClearColor(Color4F(r, g, b, a));

    setClearDepth(depthValue);

    setClearStencil(stencilValue);

    setClearFlags(flags);

    this->begin();

    //clear screen
    _beginWithClearCommand.init(_globalZOrder);
    _beginWithClearCommand.func = CC_CALLBACK_0(RenderTexture::onClear, this);
    Director::getInstance()->getRenderer()->addCommand(&_beginWithClearCommand);
}

//TODO find a better way to clear the screen, there is no need to rebind render buffer there.
void RenderTexture::clear(float r, float g, float b, float a)
{
    this->beginWithClear(r, g, b, a);
    this->end();
}

void RenderTexture::clearDepth(float depthValue)
{
    setClearDepth(depthValue);

    this->begin();

    _clearDepthCommand.init(_globalZOrder);
    _clearDepthCommand.func = CC_CALLBACK_0(RenderTexture::onClearDepth, this);

    Director::getInstance()->getRenderer()->addCommand(&_clearDepthCommand);

    this->end();
}

void RenderTexture::clearStencil(int stencilValue)
{
    // save old stencil value
    int stencilClearValue;
    glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &stencilClearValue);

    glClearStencil(stencilValue);
    glClear(GL_STENCIL_BUFFER_BIT);

    // restore clear color
    glClearStencil(stencilClearValue);
}

void RenderTexture::visit()
{
    // override visit.
	// Don't call visit on its children
    if (!_visible)
    {
        return;
    }
	
	kmGLPushMatrix();
    
    transform();
    _sprite->visit();
    draw();
    
	kmGLPopMatrix();

    _orderOfArrival = 0;
}

bool RenderTexture::saveToFile(const std::string& filename)
{
    bool ret = false;

    Image *image = newImage(true);
    if (image)
    {
        ret = image->saveToFile(filename);
    }

    CC_SAFE_DELETE(image);
    return ret;
}
bool RenderTexture::saveToFile(const std::string& fileName, Image::Format format)
{
    bool ret = false;
    CCASSERT(format == Image::Format::JPG || format == Image::Format::PNG,
             "the image can only be saved as JPG or PNG format");

    Image *image = newImage(true);
    if (image)
    {
        std::string fullpath = FileUtils::getInstance()->getWritablePath() + fileName;
        
        ret = image->saveToFile(fullpath.c_str(), true);
    }

    CC_SAFE_DELETE(image);

    return ret;
}

/* get buffer as Image */
Image* RenderTexture::newImage(bool fliimage)
{
    CCASSERT(_pixelFormat == Texture2D::PixelFormat::RGBA8888, "only RGBA8888 can be saved as image");

    if (nullptr == _texture)
    {
        return nullptr;
    }

    const Size& s = _texture->getContentSizeInPixels();

    // to get the image size to save
    //        if the saving image domain exceeds the buffer texture domain,
    //        it should be cut
    int savedBufferWidth = (int)s.width;
    int savedBufferHeight = (int)s.height;

    GLubyte *buffer = nullptr;
    GLubyte *tempData = nullptr;
    Image *image = new Image();

    do
    {
        CC_BREAK_IF(! (buffer = new GLubyte[savedBufferWidth * savedBufferHeight * 4]));

        if(! (tempData = new GLubyte[savedBufferWidth * savedBufferHeight * 4]))
        {
            delete[] buffer;
            buffer = nullptr;
            break;
        }

        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_oldFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, _FBO);

        //TODO move this to configration, so we don't check it every time
        /*  Certain Qualcomm Andreno gpu's will retain data in memory after a frame buffer switch which corrupts the render to the texture. The solution is to clear the frame buffer before rendering to the texture. However, calling glClear has the unintended result of clearing the current texture. Create a temporary texture to overcome this. At the end of RenderTexture::begin(), switch the attached texture to the second one, call glClear, and then switch back to the original texture. This solution is unnecessary for other devices as they don't have the same issue with switching frame buffers.
         */
        if (Configuration::getInstance()->checkForGLExtension("GL_QCOM"))
        {
            // -- bind a temporary texture so we can clear the render buffer without losing our texture
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureCopy->getName(), 0);
            CHECK_GL_ERROR_DEBUG();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture->getName(), 0);
        }
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glReadPixels(0,0,savedBufferWidth, savedBufferHeight,GL_RGBA,GL_UNSIGNED_BYTE, tempData);
        glBindFramebuffer(GL_FRAMEBUFFER, _oldFBO);

        if ( fliimage ) // -- flip is only required when saving image to file
        {
            // to get the actual texture data
            // #640 the image read from rendertexture is dirty
            for (int i = 0; i < savedBufferHeight; ++i)
            {
                memcpy(&buffer[i * savedBufferWidth * 4],
                       &tempData[(savedBufferHeight - i - 1) * savedBufferWidth * 4],
                       savedBufferWidth * 4);
            }

            image->initWithRawData(buffer, savedBufferWidth * savedBufferHeight * 4, savedBufferWidth, savedBufferHeight, 8);
        }
        else
        {
            image->initWithRawData(tempData, savedBufferWidth * savedBufferHeight * 4, savedBufferWidth, savedBufferHeight, 8);
        }
        
    } while (0);

    CC_SAFE_DELETE_ARRAY(buffer);
    CC_SAFE_DELETE_ARRAY(tempData);

    return image;
}

void RenderTexture::onBegin()
{
    //
    kmGLGetMatrix(KM_GL_PROJECTION, &_oldProjMatrix);
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLLoadMatrix(&_projectionMatrix);

    kmGLGetMatrix(KM_GL_MODELVIEW, &_oldTransMatrix);
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLLoadMatrix(&_transformMatrix);

    Director *director = Director::getInstance();
    director->setProjection(director->getProjection());

    const Size& texSize = _texture->getContentSizeInPixels();

    // Calculate the adjustment ratios based on the old and new projections
    Size size = director->getWinSizeInPixels();
    float widthRatio = size.width / texSize.width;
    float heightRatio = size.height / texSize.height;

    // Adjust the orthographic projection and viewport
    glViewport(0, 0, (GLsizei)size.width, (GLsizei)size.height);


    kmMat4 orthoMatrix;
    kmMat4OrthographicProjection(&orthoMatrix, (float)-1.0 / widthRatio,  (float)1.0 / widthRatio,
            (float)-1.0 / heightRatio, (float)1.0 / heightRatio, -1,1 );
    kmGLMultMatrix(&orthoMatrix);

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_oldFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, _FBO);

    //TODO move this to configration, so we don't check it every time
    /*  Certain Qualcomm Andreno gpu's will retain data in memory after a frame buffer switch which corrupts the render to the texture. The solution is to clear the frame buffer before rendering to the texture. However, calling glClear has the unintended result of clearing the current texture. Create a temporary texture to overcome this. At the end of RenderTexture::begin(), switch the attached texture to the second one, call glClear, and then switch back to the original texture. This solution is unnecessary for other devices as they don't have the same issue with switching frame buffers.
     */
    if (Configuration::getInstance()->checkForGLExtension("GL_QCOM"))
    {
        // -- bind a temporary texture so we can clear the render buffer without losing our texture
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureCopy->getName(), 0);
        CHECK_GL_ERROR_DEBUG();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture->getName(), 0);
    }
}

void RenderTexture::onEnd()
{
    Director *director = Director::getInstance();

    glBindFramebuffer(GL_FRAMEBUFFER, _oldFBO);

    // restore viewport
    director->setViewport();

    //
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLLoadMatrix(&_oldProjMatrix);

    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLLoadMatrix(&_oldTransMatrix);
}

void RenderTexture::onClear()
{
    // save clear color
    GLfloat oldClearColor[4] = {0.0f};
    GLfloat oldDepthClearValue = 0.0f;
    GLint oldStencilClearValue = 0;

    // backup and set
    if (_clearFlags & GL_COLOR_BUFFER_BIT)
    {
        glGetFloatv(GL_COLOR_CLEAR_VALUE, oldClearColor);
        glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
    }

    if (_clearFlags & GL_DEPTH_BUFFER_BIT)
    {
        glGetFloatv(GL_DEPTH_CLEAR_VALUE, &oldDepthClearValue);
        glClearDepth(_clearDepth);
    }

    if (_clearFlags & GL_STENCIL_BUFFER_BIT)
    {
        glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &oldStencilClearValue);
        glClearStencil(_clearStencil);
    }

    // clear
    glClear(_clearFlags);

    // restore
    if (_clearFlags & GL_COLOR_BUFFER_BIT)
    {
        glClearColor(oldClearColor[0], oldClearColor[1], oldClearColor[2], oldClearColor[3]);
    }
    if (_clearFlags & GL_DEPTH_BUFFER_BIT)
    {
        glClearDepth(oldDepthClearValue);
    }
    if (_clearFlags & GL_STENCIL_BUFFER_BIT)
    {
        glClearStencil(oldStencilClearValue);
    }
}

void RenderTexture::onClearDepth()
{
    //! save old depth value
    GLfloat depthClearValue;
    glGetFloatv(GL_DEPTH_CLEAR_VALUE, &depthClearValue);

    glClearDepth(_clearDepth);
    glClear(GL_DEPTH_BUFFER_BIT);

    // restore clear color
    glClearDepth(depthClearValue);
}

void RenderTexture::draw()
{
    if (_autoDraw)
    {
        //Begin will create a render group using new render target
        begin();

        //clear screen
        _clearCommand.init(_globalZOrder);
        _clearCommand.func = CC_CALLBACK_0(RenderTexture::onClear, this);
        Director::getInstance()->getRenderer()->addCommand(&_clearCommand);

        //! make sure all children are drawn
        sortAllChildren();

        for(const auto &child: _children)
        {
            if (child != _sprite)
                child->visit();
        }

        //End will pop the current render group
        end();
    }
}

void RenderTexture::begin()
{
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPushMatrix();
    kmGLGetMatrix(KM_GL_PROJECTION, &_projectionMatrix);

    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPushMatrix();
    kmGLGetMatrix(KM_GL_MODELVIEW, &_transformMatrix);
    
    Director *director = Director::getInstance();
    director->setProjection(director->getProjection());
    
    const Size& texSize = _texture->getContentSizeInPixels();
    
    // Calculate the adjustment ratios based on the old and new projections
    Size size = director->getWinSizeInPixels();
    float widthRatio = size.width / texSize.width;
    float heightRatio = size.height / texSize.height;
    
    kmMat4 orthoMatrix;
    kmMat4OrthographicProjection(&orthoMatrix, (float)-1.0 / widthRatio,  (float)1.0 / widthRatio,
                                 (float)-1.0 / heightRatio, (float)1.0 / heightRatio, -1,1 );
    kmGLMultMatrix(&orthoMatrix);

    _groupCommand.init(_globalZOrder);

    Renderer *renderer =  Director::getInstance()->getRenderer();
    renderer->addCommand(&_groupCommand);
    renderer->pushGroup(_groupCommand.getRenderQueueID());

    _beginCommand.init(_globalZOrder);
    _beginCommand.func = CC_CALLBACK_0(RenderTexture::onBegin, this);

    Director::getInstance()->getRenderer()->addCommand(&_beginCommand);
}

void RenderTexture::end()
{
    _endCommand.init(_globalZOrder);
    _endCommand.func = CC_CALLBACK_0(RenderTexture::onEnd, this);

    Renderer *renderer = Director::getInstance()->getRenderer();
    renderer->addCommand(&_endCommand);
    renderer->popGroup();
    
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPopMatrix();
    
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPopMatrix();
}

NS_CC_END
