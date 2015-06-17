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

#include "2d/CCRenderTexture.h"

#include "base/ccUtils.h"
#include "platform/CCFileUtils.h"
#include "base/CCEventType.h"
#include "base/CCConfiguration.h"
#include "base/CCDirector.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "renderer/CCRenderer.h"
#include "2d/CCCamera.h"

NS_CC_BEGIN

// implementation RenderTexture
RenderTexture::RenderTexture()
: _keepMatrix(false)
, _rtTextureRect(Rect::ZERO)
, _fullRect(Rect::ZERO)
, _fullviewPort(Rect::ZERO)
, _FBO(0)
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
, _saveFileCallback(nullptr)
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
    // We have not found a way to dispatch the enter background message before the texture data are destroyed.
    // So we disable this pair of message handler at present.
#if 0
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
#endif
}

void RenderTexture::listenToForeground(EventCustom *event)
{
#if 0
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
#endif
}

RenderTexture * RenderTexture::create(int w, int h, Texture2D::PixelFormat eFormat)
{
    RenderTexture *ret = new (std::nothrow) RenderTexture();

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
    RenderTexture *ret = new (std::nothrow) RenderTexture();

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
    RenderTexture *ret = new (std::nothrow) RenderTexture();

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
        _fullRect = _rtTextureRect = Rect(0,0,w,h);
        //Size size = Director::getInstance()->getWinSizeInPixels();
        //_fullviewPort = Rect(0,0,size.width,size.height);
        w = (int)(w * CC_CONTENT_SCALE_FACTOR());
        h = (int)(h * CC_CONTENT_SCALE_FACTOR());
        _fullviewPort = Rect(0,0,w,h);
        
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

        _texture = new (std::nothrow) Texture2D();
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
            _textureCopy = new (std::nothrow) Texture2D();
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
        _sprite->setFlippedY(true);

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

void RenderTexture::setKeepMatrix(bool keepMatrix)
{
    _keepMatrix = keepMatrix;
}

void RenderTexture::setVirtualViewport(const Vec2& rtBegin, const Rect& fullRect, const Rect& fullViewport)
{
    _rtTextureRect.origin.x = rtBegin.x;
    _rtTextureRect.origin.y = rtBegin.y;

    _fullRect = fullRect;

    _fullviewPort = fullViewport;
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

//TODO: find a better way to clear the screen, there is no need to rebind render buffer there.
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

void RenderTexture::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    // override visit.
    // Don't call visit on its children
    if (!_visible || !isVisitableByVisitingCamera())
    {
        return;
    }
    
    uint32_t flags = processParentFlags(parentTransform, parentFlags);

    Director* director = Director::getInstance();
    // IMPORTANT:
    // To ease the migration to v3.0, we still support the Mat4 stack,
    // but it is deprecated and your code should not rely on it
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);

    _sprite->visit(renderer, _modelViewTransform, flags);
    draw(renderer, _modelViewTransform, flags);
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

    // FIX ME: Why need to set _orderOfArrival to 0??
    // Please refer to https://github.com/cocos2d/cocos2d-x/pull/6920
    // setOrderOfArrival(0);
}

bool RenderTexture::saveToFile(const std::string& filename, bool isRGBA, std::function<void (RenderTexture*, const std::string&)> callback)
{
    std::string basename(filename);
    std::transform(basename.begin(), basename.end(), basename.begin(), ::tolower);
    
    if (basename.find(".png") != std::string::npos)
    {
        return saveToFile(filename, Image::Format::PNG, isRGBA, callback);
    }
    else if (basename.find(".jpg") != std::string::npos)
    {
        if (isRGBA) CCLOG("RGBA is not supported for JPG format.");
        return saveToFile(filename, Image::Format::JPG, false, callback);
    }
    else
    {
        CCLOG("Only PNG and JPG format are supported now!");
    }
    
    return saveToFile(filename, Image::Format::JPG, false, callback);
}

bool RenderTexture::saveToFile(const std::string& fileName, Image::Format format, bool isRGBA, std::function<void (RenderTexture*, const std::string&)> callback)
{
    CCASSERT(format == Image::Format::JPG || format == Image::Format::PNG,
             "the image can only be saved as JPG or PNG format");
    if (isRGBA && format == Image::Format::JPG) CCLOG("RGBA is not supported for JPG format");
    
    _saveFileCallback = callback;
    
    std::string fullpath = FileUtils::getInstance()->getWritablePath() + fileName;
    _saveToFileCommand.init(_globalZOrder);
    _saveToFileCommand.func = CC_CALLBACK_0(RenderTexture::onSaveToFile, this, fullpath, isRGBA);
    
    Director::getInstance()->getRenderer()->addCommand(&_saveToFileCommand);
    return true;
}

void RenderTexture::onSaveToFile(const std::string& filename, bool isRGBA)
{
    Image *image = newImage(true);
    if (image)
    {
        image->saveToFile(filename.c_str(), !isRGBA);
    }
    if(_saveFileCallback)
    {
        _saveFileCallback(this, filename);
    }
    CC_SAFE_DELETE(image);
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
    Image *image = new (std::nothrow) Image();

    do
    {
        CC_BREAK_IF(! (buffer = new (std::nothrow) GLubyte[savedBufferWidth * savedBufferHeight * 4]));

        if(! (tempData = new (std::nothrow) GLubyte[savedBufferWidth * savedBufferHeight * 4]))
        {
            delete[] buffer;
            buffer = nullptr;
            break;
        }

        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_oldFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, _FBO);

        // TODO: move this to configration, so we don't check it every time
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
    Director *director = Director::getInstance();
    
    _oldProjMatrix = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, _projectionMatrix);
    
    _oldTransMatrix = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _transformMatrix);
    
    if(!_keepMatrix)
    {
        director->setProjection(director->getProjection());
        const Size& texSize = _texture->getContentSizeInPixels();
        
        // Calculate the adjustment ratios based on the old and new projections
        Size size = director->getWinSizeInPixels();
        float widthRatio = size.width / texSize.width;
        float heightRatio = size.height / texSize.height;
        
        Mat4 orthoMatrix;
        Mat4::createOrthographicOffCenter((float)-1.0 / widthRatio, (float)1.0 / widthRatio, (float)-1.0 / heightRatio, (float)1.0 / heightRatio, -1, 1, &orthoMatrix);
        director->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, orthoMatrix);
    }
    
    //calculate viewport
    {
        Rect viewport;
        viewport.size.width = _fullviewPort.size.width;
        viewport.size.height = _fullviewPort.size.height;
        float viewPortRectWidthRatio = float(viewport.size.width)/_fullRect.size.width;
        float viewPortRectHeightRatio = float(viewport.size.height)/_fullRect.size.height;
        viewport.origin.x = (_fullRect.origin.x - _rtTextureRect.origin.x) * viewPortRectWidthRatio;
        viewport.origin.y = (_fullRect.origin.y - _rtTextureRect.origin.y) * viewPortRectHeightRatio;
        //glViewport(_fullviewPort.origin.x, _fullviewPort.origin.y, (GLsizei)_fullviewPort.size.width, (GLsizei)_fullviewPort.size.height);
        glViewport(viewport.origin.x, viewport.origin.y, (GLsizei)viewport.size.width, (GLsizei)viewport.size.height);
    }

    // Adjust the orthographic projection and viewport
    
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_oldFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, _FBO);

    // TODO: move this to configration, so we don't check it every time
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
    const auto& vp = Camera::getDefaultViewport();
    glViewport(vp._left, vp._bottom, vp._width, vp._height);
    //
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, _oldProjMatrix);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _oldTransMatrix);

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

void RenderTexture::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if (_autoDraw)
    {
        //Begin will create a render group using new render target
        begin();

        //clear screen
        _clearCommand.init(_globalZOrder);
        _clearCommand.func = CC_CALLBACK_0(RenderTexture::onClear, this);
        renderer->addCommand(&_clearCommand);

        //! make sure all children are drawn
        sortAllChildren();

        for(const auto &child: _children)
        {
            if (child != _sprite)
                child->visit(renderer, transform, flags);
        }

        //End will pop the current render group
        end();
    }
}

void RenderTexture::begin()
{
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    _projectionMatrix = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    _transformMatrix = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
    if(!_keepMatrix)
    {
        director->setProjection(director->getProjection());
        
        const Size& texSize = _texture->getContentSizeInPixels();
        
        // Calculate the adjustment ratios based on the old and new projections
        Size size = director->getWinSizeInPixels();
        
        float widthRatio = size.width / texSize.width;
        float heightRatio = size.height / texSize.height;
        
        Mat4 orthoMatrix;
        Mat4::createOrthographicOffCenter((float)-1.0 / widthRatio, (float)1.0 / widthRatio, (float)-1.0 / heightRatio, (float)1.0 / heightRatio, -1, 1, &orthoMatrix);
        director->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, orthoMatrix);
    }

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

    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    
    Renderer *renderer = director->getRenderer();
    renderer->addCommand(&_endCommand);
    renderer->popGroup();
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

}

NS_CC_END
