/****************************************************************************
Copyright (c) 2009      Jason Booth
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "renderer/CCTextureCache.h"
#include "renderer/backend/Device.h"
#include "renderer/backend/Texture.h"

NS_CC_BEGIN

// implementation RenderTexture
RenderTexture::RenderTexture()
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
    CC_SAFE_RELEASE(_texture2DCopy);
    CC_SAFE_RELEASE(_depthStencilTexture);
    CC_SAFE_RELEASE(_UITextureImage);
}

void RenderTexture::listenToBackground(EventCustom* /*event*/)
{
    // We have not found a way to dispatch the enter background message before the texture data are destroyed.
    // So we disable this pair of message handler at present.
#if CC_ENABLE_CACHE_TEXTURE_DATA
    // to get the rendered texture data
    auto func = [&](Image* uiTextureImage){
        if (uiTextureImage)
        {
            CC_SAFE_RELEASE(_UITextureImage);
            _UITextureImage = uiTextureImage;
            CC_SAFE_RETAIN(_UITextureImage);
            const Size& s = _texture2D->getContentSizeInPixels();
            VolatileTextureMgr::addDataTexture(_texture2D, uiTextureImage->getData(), s.width * s.height * 4, backend::PixelFormat::RGBA8888, s);

            if ( _texture2DCopy )
            {
                VolatileTextureMgr::addDataTexture(_texture2DCopy, uiTextureImage->getData(), s.width * s.height * 4, backend::PixelFormat::RGBA8888, s);
            }
        }
        else
        {
            CCLOG("Cache rendertexture failed!");
        }
        CC_SAFE_RELEASE(uiTextureImage);
    };
    auto callback = std::bind(func, std::placeholders::_1);
    newImage(callback, false);

#endif
}

void RenderTexture::listenToForeground(EventCustom* /*event*/)
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    const Size& s = _texture2D->getContentSizeInPixels();
    //TODO new-renderer: field _depthAndStencilFormat removal
//    if (_depthAndStencilFormat != 0)
//    {
//        setupDepthAndStencil(s.width, s.height);
//    }
    
    _texture2D->setAntiAliasTexParameters();
    if(_texture2DCopy)
    {
        _texture2DCopy->setAntiAliasTexParameters();
    }
#endif
}

RenderTexture * RenderTexture::create(int w, int h, backend::PixelFormat eFormat)
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

RenderTexture * RenderTexture::create(int w ,int h, backend::PixelFormat eFormat, PixelFormat uDepthStencilFormat)
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

    if(ret && ret->initWithWidthAndHeight(w, h, backend::PixelFormat::RGBA8888, PixelFormat::NONE))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool RenderTexture::initWithWidthAndHeight(int w, int h, backend::PixelFormat eFormat)
{
    return initWithWidthAndHeight(w, h, eFormat, PixelFormat::NONE);
}

bool RenderTexture::initWithWidthAndHeight(int w, int h, backend::PixelFormat format, PixelFormat depthStencilFormat)
{
    CCASSERT(format != backend::PixelFormat::A8, "only RGB and RGBA formats are valid for a render texture");

    bool ret = false;
    do
    {
        _fullRect = _rtTextureRect = Rect(0,0,w,h);
        w = (int)(w * CC_CONTENT_SCALE_FACTOR());
        h = (int)(h * CC_CONTENT_SCALE_FACTOR());
        _fullviewPort = Rect(0,0,w,h);
        
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
        
        backend::TextureDescriptor descriptor;
        descriptor.width = powW;
        descriptor.height = powH;
        descriptor.textureUsage = TextureUsage::RENDER_TARGET;
        descriptor.textureFormat = PixelFormat::RGBA8888;
        auto texture = backend::Device::getInstance()->newTexture(descriptor);
        if (! texture)
            break;

        _texture2D = new (std::nothrow) Texture2D();
        if (_texture2D)
        {
            _texture2D->initWithBackendTexture(texture, CC_ENABLE_PREMULTIPLIED_ALPHA != 0);
            _texture2D->setRenderTarget(true);
            texture->release();
        }
        else
            break;

        _renderTargetFlags = RenderTargetFlag::COLOR;

        clearColorAttachment();

        if (PixelFormat::D24S8 == depthStencilFormat)
        {
            _renderTargetFlags = RenderTargetFlag::ALL;
            descriptor.textureFormat = depthStencilFormat;
            texture = backend::Device::getInstance()->newTexture(descriptor);
            if (! texture)
                break;

            _depthStencilTexture = new (std::nothrow) Texture2D;
            if (!_depthStencilTexture)
            {
                texture->release();
                break;
            }

            _depthStencilTexture->initWithBackendTexture(texture);
            texture->release();
        }

        _texture2D->setAntiAliasTexParameters();
        if (_texture2DCopy)
        {
            _texture2DCopy->setAntiAliasTexParameters();
        }

        // retained
        setSprite(Sprite::createWithTexture(_texture2D));

        _texture2D->release();

#if defined(CC_USE_GL) || defined(CC_USE_GLES)
        _sprite->setFlippedY(true);
#endif

#if CC_ENABLE_PREMULTIPLIED_ALPHA != 0
        _sprite->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
        _sprite->setOpacityModifyRGB(true);
#else
        _sprite->setBlendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED);
        _sprite->setOpacityModifyRGB(false);
#endif
        
        // Disabled by default.
        _autoDraw = false;
        
        // add sprite for backward compatibility
        addChild(_sprite);
        
        ret = true;
    } while (0);
    
    return ret;
}

void RenderTexture::setSprite(Sprite* sprite)
{
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    auto sEngine = ScriptEngineManager::getInstance()->getScriptEngine();
    if (sEngine)
    {
        if (sprite)
            sEngine->retainScriptObject(this, sprite);
        if (_sprite)
            sEngine->releaseScriptObject(this, _sprite);
    }
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    CC_SAFE_RETAIN(sprite);
    CC_SAFE_RELEASE(_sprite);
    _sprite = sprite;
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
    beginWithClear(r, g, b, a, 0, 0, ClearFlag::COLOR);
}

void RenderTexture::beginWithClear(float r, float g, float b, float a, float depthValue)
{
    beginWithClear(r, g, b, a, depthValue, 0, ClearFlag::COLOR | ClearFlag::DEPTH);
}

void RenderTexture::beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue)
{
    beginWithClear(r, g, b, a, depthValue, stencilValue, ClearFlag::ALL);
}

void RenderTexture::beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue, ClearFlag flags)
{
    setClearColor(Color4F(r, g, b, a));
    setClearDepth(depthValue);
    setClearStencil(stencilValue);
    setClearFlags(flags);
    begin();
    Director::getInstance()->getRenderer()->clear(_clearFlags, _clearColor, _clearDepth, _clearStencil, _globalZOrder);
}

void RenderTexture::clear(float r, float g, float b, float a)
{
    this->beginWithClear(r, g, b, a);
    this->end();
}

void RenderTexture::clearDepth(float depthValue)
{
    setClearDepth(depthValue);
}

void RenderTexture::clearStencil(int stencilValue)
{
    setClearStencil(stencilValue);
}

void RenderTexture::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    // override visit.
    // Don't call visit on its children
    if (!_visible)
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
    if (isVisitableByVisitingCamera())
    {
        draw(renderer, _modelViewTransform, flags);
    }
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

    // FIX ME: Why need to set _orderOfArrival to 0??
    // Please refer to https://github.com/cocos2d/cocos2d-x/pull/6920
    // setOrderOfArrival(0);
}

bool RenderTexture::saveToFileAsNonPMA(const std::string& filename, bool isRGBA, std::function<void(RenderTexture*, const std::string&)> callback)
{
    std::string basename(filename);
    std::transform(basename.begin(), basename.end(), basename.begin(), ::tolower);

    if (basename.find(".png") != std::string::npos)
    {
        return saveToFileAsNonPMA(filename, Image::Format::PNG, isRGBA, callback);
    }
    else if (basename.find(".jpg") != std::string::npos)
    {
        if (isRGBA) CCLOG("RGBA is not supported for JPG format.");
        return saveToFileAsNonPMA(filename, Image::Format::JPG, false, callback);
    }
    else
    {
        CCLOG("Only PNG and JPG format are supported now!");
    }

    return saveToFileAsNonPMA(filename, Image::Format::JPG, false, callback);
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

bool RenderTexture::saveToFileAsNonPMA(const std::string& fileName, Image::Format format, bool isRGBA, std::function<void(RenderTexture*, const std::string&)> callback)
{
    CCASSERT(format == Image::Format::JPG || format == Image::Format::PNG,
        "the image can only be saved as JPG or PNG format");
    if (isRGBA && format == Image::Format::JPG) CCLOG("RGBA is not supported for JPG format");

    _saveFileCallback = callback;

    std::string fullpath = FileUtils::getInstance()->getWritablePath() + fileName;
    _saveToFileCommand.init(_globalZOrder);
    _saveToFileCommand.func = CC_CALLBACK_0(RenderTexture::onSaveToFile, this, fullpath, isRGBA, true);

    Director::getInstance()->getRenderer()->addCommand(&_saveToFileCommand);
    return true;
}


bool RenderTexture::saveToFile(const std::string& fileName, Image::Format format, bool isRGBA, std::function<void (RenderTexture*, const std::string&)> callback)
{
    CCASSERT(format == Image::Format::JPG || format == Image::Format::PNG,
             "the image can only be saved as JPG or PNG format");
    if (isRGBA && format == Image::Format::JPG) CCLOG("RGBA is not supported for JPG format");
    
    _saveFileCallback = callback;
    
    std::string fullpath = FileUtils::getInstance()->getWritablePath() + fileName;
    _saveToFileCommand.init(_globalZOrder);
    _saveToFileCommand.func = CC_CALLBACK_0(RenderTexture::onSaveToFile, this, fullpath, isRGBA, false);
    
    Director::getInstance()->getRenderer()->addCommand(&_saveToFileCommand);
    return true;
}

void RenderTexture::onSaveToFile(const std::string& filename, bool isRGBA, bool forceNonPMA)
{
    auto callbackFunc = [&, filename, isRGBA, forceNonPMA](Image* image){
        if (image)
        {
            if (forceNonPMA && image->hasPremultipliedAlpha())
            {
                image->reversePremultipliedAlpha();
            }
            image->saveToFile(filename, !isRGBA);
        }
        if(_saveFileCallback)
        {
            _saveFileCallback(this, filename);
        }
        CC_SAFE_DELETE(image);
    };
    newImage(callbackFunc);
}

/* get buffer as Image */
void RenderTexture::newImage(std::function<void(Image*)> imageCallback, bool flipImage)
{
    CCASSERT(_pixelFormat == backend::PixelFormat::RGBA8888, "only RGBA8888 can be saved as image");

    if ((nullptr == _texture2D))
    {
        return ;
    }

    const Size& s = _texture2D->getContentSizeInPixels();

    // to get the image size to save
    //        if the saving image domain exceeds the buffer texture domain,
    //        it should be cut
    int savedBufferWidth = (int)s.width;
    int savedBufferHeight = (int)s.height;
    
    Image *image = new (std::nothrow) Image();
    
    auto initCallback = [&, savedBufferWidth, savedBufferHeight, imageCallback](Image* image, const unsigned char* tempData){
        image->initWithRawData(tempData, savedBufferWidth * savedBufferHeight * 4, savedBufferWidth, savedBufferHeight, 8, _texture2D->hasPremultipliedAlpha());
        imageCallback(image);
    };
    auto callback = std::bind(initCallback, image, std::placeholders::_1);
    
    _texture2D->getBackendTexture()->getBytes(0, 0, savedBufferWidth, savedBufferHeight, flipImage, callback);
    
//    do
//    {
////        // TODO: move this to configuration, so we don't check it every time
////        /*  Certain Qualcomm Adreno GPU's will retain data in memory after a frame buffer switch which corrupts the render to the texture. The solution is to clear the frame buffer before rendering to the texture. However, calling glClear has the unintended result of clearing the current texture. Create a temporary texture to overcome this. At the end of RenderTexture::begin(), switch the attached texture to the second one, call glClear, and then switch back to the original texture. This solution is unnecessary for other devices as they don't have the same issue with switching frame buffers.
////         */
////        if (Configuration::getInstance()->checkForGLExtension("GL_QCOM"))
////        {
////            // -- bind a temporary texture so we can clear the render buffer without losing our texture
////            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureCopy->getName(), 0);
////            CHECK_GL_ERROR_DEBUG();
////            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture->getName(), 0);
////        }
//    } while (0);
}

void RenderTexture::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if (_autoDraw)
    {
        //Begin will create a render group using new render target
        begin();

        //clear screen
        Director::getInstance()->getRenderer()->clear(_clearFlags, _clearColor, _clearDepth, _clearStencil, _globalZOrder);

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

void RenderTexture::onBegin()
{
    Director *director = Director::getInstance();

    _oldProjMatrix = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, _projectionMatrix);

    _oldTransMatrix = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _transformMatrix);

    if(!_keepMatrix)
    {
        director->setProjection(director->getProjection());
        const Size& texSize = _texture2D->getContentSizeInPixels();

        // Calculate the adjustment ratios based on the old and new projections
        Size size = director->getWinSizeInPixels();
        float widthRatio = size.width / texSize.width;
        float heightRatio = size.height / texSize.height;

        Mat4 orthoMatrix;
        Mat4::createOrthographicOffCenter((float)-1.0 / widthRatio, (float)1.0 / widthRatio, (float)-1.0 / heightRatio, (float)1.0 / heightRatio, -1, 1, &orthoMatrix);
        director->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, orthoMatrix);
    }

    Rect viewport;
    viewport.size.width = _fullviewPort.size.width;
    viewport.size.height = _fullviewPort.size.height;
    float viewPortRectWidthRatio = float(viewport.size.width)/_fullRect.size.width;
    float viewPortRectHeightRatio = float(viewport.size.height)/_fullRect.size.height;
    viewport.origin.x = (_fullRect.origin.x - _rtTextureRect.origin.x) * viewPortRectWidthRatio;
    viewport.origin.y = (_fullRect.origin.y - _rtTextureRect.origin.y) * viewPortRectHeightRatio;

    Renderer *renderer =  director->getRenderer();
    
    _oldViewport = renderer->getViewport();
    renderer->setViewPort(viewport.origin.x, viewport.origin.y, viewport.size.width, viewport.size.height);

    _oldColorAttachment = renderer->getColorAttachment();
    _oldDepthAttachment = renderer->getDepthAttachment();
    _oldStencilAttachment = renderer->getStencilAttachment();
    _oldRenderTargetFlag = renderer->getRenderTargetFlag();

    renderer->setRenderTarget(_renderTargetFlags, _texture2D, _depthStencilTexture, _depthStencilTexture);
}

void RenderTexture::onEnd()
{
    Director *director = Director::getInstance();
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, _oldProjMatrix);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _oldTransMatrix);
    
    Renderer *renderer =  Director::getInstance()->getRenderer();
    renderer->setViewPort(_oldViewport.x, _oldViewport.y, _oldViewport.w, _oldViewport.h);
    renderer->setRenderTarget(_oldRenderTargetFlag, _oldColorAttachment, _oldDepthAttachment, _oldStencilAttachment);
}

void RenderTexture::begin()
{
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when setting matrix stack");
    
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    _projectionMatrix = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    _transformMatrix = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
    if(!_keepMatrix)
    {
        director->setProjection(director->getProjection());
        
        const Size& texSize = _texture2D->getContentSizeInPixels();
        
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
    renderer->addCommand(&_beginCommand);
}

void RenderTexture::end()
{
    _endCommand.init(_globalZOrder);
    _endCommand.func = CC_CALLBACK_0(RenderTexture::onEnd, this);

    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when setting matrix stack");
    
    Renderer *renderer = director->getRenderer();
    renderer->addCommand(&_endCommand);
    renderer->popGroup();

    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void RenderTexture::setClearFlags(ClearFlag clearFlags)
{
    _clearFlags = clearFlags;
    if (_clearFlags != ClearFlag::NONE
        && !_depthStencilTexture)
    {
        _clearFlags = ClearFlag::COLOR;
    }
}

void RenderTexture::clearColorAttachment()
{
    auto renderer = Director::getInstance()->getRenderer();
    _beforeClearAttachmentCommand.func = [=]() -> void {
        _oldColorAttachment = renderer->getColorAttachment();
        renderer->setRenderTarget(RenderTargetFlag::COLOR, _texture2D, nullptr, nullptr);
    };
    renderer->addCommand(&_beforeClearAttachmentCommand);

    Color4F color(0.f, 0.f, 0.f, 0.f);
    renderer->clear(ClearFlag::COLOR, color, 1, 0, _globalZOrder);

    _afterClearAttachmentCommand.func = [=]() -> void {
        renderer->setRenderTarget(RenderTargetFlag::COLOR, _oldColorAttachment, nullptr, nullptr);
    };
    renderer->addCommand(&_afterClearAttachmentCommand);
}

NS_CC_END
