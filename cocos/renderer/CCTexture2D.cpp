/****************************************************************************
Copyright (c) 2008      Apple Inc. All Rights Reserved.
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



/*
* Support for RGBA_4_4_4_4 and RGBA_5_5_5_1 was copied from:
* https://devforums.apple.com/message/37855#37855 by a1studmuffin
*/

#include "renderer/CCTexture2D.h"

#include "platform/CCGL.h"
#include "platform/CCImage.h"
#include "base/ccUtils.h"
#include "platform/CCDevice.h"
#include "base/ccConfig.h"
#include "base/ccMacros.h"
#include "base/ccUTF8.h"
#include "base/CCConfiguration.h"
#include "platform/CCPlatformMacros.h"
#include "base/CCDirector.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramCache.h"
#include "base/CCNinePatchImageParser.h"
#include "renderer/backend/Device.h"
#include "renderer/backend/StringUtils.h"
#include "renderer/CCTextureUtils.h"

#if CC_ENABLE_CACHE_TEXTURE_DATA
    #include "renderer/CCTextureCache.h"
#endif

NS_CC_BEGIN



namespace {
    typedef Texture2D::PixelFormatInfoMap::value_type PixelFormatInfoMapValue;
    static const PixelFormatInfoMapValue TexturePixelFormatInfoTablesValue[] =
    {
        PixelFormatInfoMapValue(Texture2D::PixelFormat::BGRA8888, Texture2D::PixelFormatInfo(GL_BGRA, GL_BGRA, GL_UNSIGNED_BYTE, 32, false, true)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::RGBA8888, Texture2D::PixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 32, false, true)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::RGBA4444, Texture2D::PixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, 16, false, true)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::RGB5A1, Texture2D::PixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, 16, false, true)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::RGB565, Texture2D::PixelFormatInfo(GL_RGB, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 16, false, false)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::RGB888, Texture2D::PixelFormatInfo(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, 24, false, false)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::A8, Texture2D::PixelFormatInfo(GL_ALPHA, GL_ALPHA, GL_UNSIGNED_BYTE, 8, false, false)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::I8, Texture2D::PixelFormatInfo(GL_LUMINANCE, GL_LUMINANCE, GL_UNSIGNED_BYTE, 8, false, false)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::AI88, Texture2D::PixelFormatInfo(GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, 16, false, true)),
#ifndef CC_USE_METAL
        //OpenGL only
#ifdef GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG
        PixelFormatInfoMapValue(Texture2D::PixelFormat::PVRTC2, Texture2D::PixelFormatInfo(GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 2, true, false)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::PVRTC2A, Texture2D::PixelFormatInfo(GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 2, true, true)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::PVRTC4, Texture2D::PixelFormatInfo(GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, false)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::PVRTC4A, Texture2D::PixelFormatInfo(GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, true)),
#endif
#else
        //Metal && iOS
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        PixelFormatInfoMapValue(Texture2D::PixelFormat::PVRTC2, Texture2D::PixelFormatInfo(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 2, true, false)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::PVRTC2A, Texture2D::PixelFormatInfo(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 2, true, true)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::PVRTC4, Texture2D::PixelFormatInfo(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, false)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::PVRTC4A, Texture2D::PixelFormatInfo(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, true)),
#endif
#endif
        
#ifdef GL_ETC1_RGB8_OES
        PixelFormatInfoMapValue(Texture2D::PixelFormat::ETC, Texture2D::PixelFormatInfo(GL_ETC1_RGB8_OES, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, false)),
#endif
        
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
        PixelFormatInfoMapValue(Texture2D::PixelFormat::S3TC_DXT1, Texture2D::PixelFormatInfo(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, false)),
#endif
        
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
        PixelFormatInfoMapValue(Texture2D::PixelFormat::S3TC_DXT3, Texture2D::PixelFormatInfo(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, 0xFFFFFFFF, 0xFFFFFFFF, 8, true, false)),
#endif
        
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
        PixelFormatInfoMapValue(Texture2D::PixelFormat::S3TC_DXT5, Texture2D::PixelFormatInfo(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 0xFFFFFFFF, 0xFFFFFFFF, 8, true, false)),
#endif
        
#ifdef GL_ATC_RGB_AMD
        PixelFormatInfoMapValue(Texture2D::PixelFormat::ATC_RGB, Texture2D::PixelFormatInfo(GL_ATC_RGB_AMD,
            0xFFFFFFFF, 0xFFFFFFFF, 4, true, false)),
#endif
        
#ifdef GL_ATC_RGBA_EXPLICIT_ALPHA_AMD
        PixelFormatInfoMapValue(Texture2D::PixelFormat::ATC_EXPLICIT_ALPHA, Texture2D::PixelFormatInfo(GL_ATC_RGBA_EXPLICIT_ALPHA_AMD,
            0xFFFFFFFF, 0xFFFFFFFF, 8, true, false)),
#endif
        
#ifdef GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD
        PixelFormatInfoMapValue(Texture2D::PixelFormat::ATC_INTERPOLATED_ALPHA, Texture2D::PixelFormatInfo(GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD,
            0xFFFFFFFF, 0xFFFFFFFF, 8, true, false)),
#endif
        //metal formats
#ifdef CC_USE_METAL
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        PixelFormatInfoMapValue(Texture2D::PixelFormat::MTL_ABGR4, Texture2D::PixelFormatInfo(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 16, false, true)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::MTL_B5G6R5, Texture2D::PixelFormatInfo(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 16, false, false)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::MTL_BGR5A1, Texture2D::PixelFormatInfo(0xFFFFFFFF,0xFFFFFFFF, 0xFFFFFFFF, 16, false, true)),
#endif
#endif
    };

    backend::SamplerFilter GLToBackendMagFilter(GLint magFilter)
    {
        switch (magFilter)
        {
        case GL_LINEAR:
            return backend::SamplerFilter::LINEAR;
        case GL_NEAREST:
            return backend::SamplerFilter::NEAREST;
        default:
            return backend::SamplerFilter::LINEAR;
        }
    }


    GLint toGLAddressMode(backend::SamplerAddressMode addressMode, bool isPow2)
    {
        GLint ret = GL_REPEAT;
        if (!isPow2 && (addressMode != backend::SamplerAddressMode::CLAMP_TO_EDGE))
        {
            cocos2d::log("Change texture wrap mode to CLAMP_TO_EDGE since non-power-of-two texture occur in %s %s %d", __FILE__, __FUNCTION__, __LINE__);
            return GL_CLAMP_TO_EDGE;
        }

        switch (addressMode)
        {
        case backend::SamplerAddressMode::REPEAT:
            ret = GL_REPEAT;
            break;
        case backend::SamplerAddressMode::MIRROR_REPEAT:
            ret = GL_MIRRORED_REPEAT;
            break;
        case backend::SamplerAddressMode::CLAMP_TO_EDGE:
            ret = GL_CLAMP_TO_EDGE;
            break;
        default:
            break;
        }
        return ret;
    }

    backend::SamplerAddressMode GLToBackendAddressMode(int addressMode)
    {
        switch (addressMode)
        {
        case GL_REPEAT:
            return backend::SamplerAddressMode::REPEAT;
        case GL_MIRRORED_REPEAT:
            return backend::SamplerAddressMode::MIRROR_REPEAT;
        case GL_CLAMP_TO_EDGE:
            return backend::SamplerAddressMode::CLAMP_TO_EDGE;
        default:
            return backend::SamplerAddressMode::REPEAT;
        }
    }
}

//CLASS IMPLEMENTATIONS:

//The PixpelFormat corresponding information
const Texture2D::PixelFormatInfoMap Texture2D::_pixelFormatInfoTables(TexturePixelFormatInfoTablesValue,
                                                                     TexturePixelFormatInfoTablesValue + sizeof(TexturePixelFormatInfoTablesValue) / sizeof(TexturePixelFormatInfoTablesValue[0]));

// If the image has alpha, you can create RGBA8 (32-bit) or RGBA4 (16-bit) or RGB5A1 (16-bit)
// Default is: RGBA8888 (32-bit textures)
static Texture2D::PixelFormat g_defaultAlphaPixelFormat = Texture2D::PixelFormat::DEFAULT;


Texture2D::Texture2D()
: _pixelFormat(Texture2D::PixelFormat::DEFAULT)
, _pixelsWide(0)
, _pixelsHigh(0)
, _maxS(0.0)
, _maxT(0.0)
, _hasPremultipliedAlpha(false)
, _hasMipmaps(false)
, _antialiasEnabled(true)
, _ninePatchInfo(nullptr)
, _valid(true)
, _alphaTexture(nullptr)
, _texture(nullptr)
{
}

Texture2D::~Texture2D()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    VolatileTextureMgr::removeTexture(this);
#endif
    CC_SAFE_RELEASE_NULL(_alphaTexture); // ETC1 ALPHA support.

    CCLOGINFO("deallocing Texture2D: %p - id=%u", this, _name);

    CC_SAFE_DELETE(_ninePatchInfo);

    CC_SAFE_RELEASE(_texture);
}


Texture2D::PixelFormat Texture2D::getPixelFormat() const
{
    return _pixelFormat;
}

int Texture2D::getPixelsWide() const
{
    return _pixelsWide;
}

int Texture2D::getPixelsHigh() const
{
    return _pixelsHigh;
}

GLuint Texture2D::getName() const
{
    //TODO coulsonwang
    cocos2d::log("Error in %s %s %d, TODO", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}

backend::Texture* Texture2D::getBackendTexture() const
{
    return _texture;
}

bool Texture2D::getAlphaTextureName() const
{
    return _alphaTexture == nullptr ? 0 : _alphaTexture->getBackendTexture();
}

Size Texture2D::getContentSize() const
{
    Size ret;
    ret.width = _contentSize.width / CC_CONTENT_SCALE_FACTOR();
    ret.height = _contentSize.height / CC_CONTENT_SCALE_FACTOR();
    
    return ret;
}

const Size& Texture2D::getContentSizeInPixels()
{
    return _contentSize;
}

GLfloat Texture2D::getMaxS() const
{
    return _maxS;
}

void Texture2D::setMaxS(GLfloat maxS)
{
    _maxS = maxS;
}

GLfloat Texture2D::getMaxT() const
{
    return _maxT;
}

void Texture2D::setMaxT(GLfloat maxT)
{
    _maxT = maxT;
}

bool Texture2D::hasPremultipliedAlpha() const
{
    return _hasPremultipliedAlpha;
}

bool Texture2D::initWithData(const void *data, ssize_t dataLen, Texture2D::PixelFormat pixelFormat, Texture2D::PixelFormat renderFormat, int pixelsWide, int pixelsHigh, const Size& /*contentSize*/)
{
    CCASSERT(dataLen>0 && pixelsWide>0 && pixelsHigh>0, "Invalid size");

    //if data has no mipmaps, we will consider it has only one mipmap
    MipmapInfo mipmap;
    mipmap.address = (unsigned char*)data;
    mipmap.len = static_cast<int>(dataLen);
    return initWithMipmaps(&mipmap, 1, pixelFormat, renderFormat, pixelsWide, pixelsHigh);
}

bool Texture2D::initWithMipmaps(MipmapInfo* mipmaps, int mipmapsNum, PixelFormat pixelFormat, PixelFormat renderFormat, int pixelsWide, int pixelsHigh)
{
    //the pixelFormat must be a certain value 
    CCASSERT(pixelFormat != PixelFormat::NONE && pixelFormat != PixelFormat::AUTO, "the \"pixelFormat\" param must be a certain value!");
    CCASSERT(pixelsWide > 0 && pixelsHigh > 0, "Invalid size");

    if (mipmapsNum <= 0)
    {
        CCLOG("cocos2d: WARNING: mipmap number is less than 1");
        return false;
    }


    auto formatItr = _pixelFormatInfoTables.find(pixelFormat);
    if (formatItr == _pixelFormatInfoTables.end())
    {
        CCLOG("cocos2d: WARNING: unsupported pixelformat: %lx", (unsigned long)pixelFormat);
#ifdef CC_USE_METAL
        CCASSERT(false, "pixeformat not found in _pixelFormatInfoTables, register required!");
#endif
        return false;
    }

    const PixelFormatInfo& info = formatItr->second;

    if (info.compressed && !Configuration::getInstance()->supportsPVRTC()
        && !Configuration::getInstance()->supportsETC()
        && !Configuration::getInstance()->supportsS3TC()
        && !Configuration::getInstance()->supportsATITC())
    {
        CCLOG("cocos2d: WARNING: PVRTC/ETC images are not supported");
        return false;
    }

    auto device = backend::Device::getInstance();
    backend::TextureDescriptor textureDescriptor;
    textureDescriptor.width = pixelsWide;
    textureDescriptor.height = pixelsHigh;
    textureDescriptor.samplerDescriptor.minFilter = (_antialiasEnabled) ? backend::SamplerFilter::LINEAR : backend::SamplerFilter::NEAREST;
    textureDescriptor.samplerDescriptor.magFilter = (_antialiasEnabled) ? backend::SamplerFilter::LINEAR : backend::SamplerFilter::NEAREST;
    if (mipmapsNum > 1)
    {
        textureDescriptor.samplerDescriptor.mipmapFilter = backend::SamplerFilter::NEAREST;
    }

    unsigned char *data = mipmaps[0].address;

    ssize_t dataLen = mipmaps[0].len;
    unsigned char *outData = data;
    ssize_t outDataLen;
    
    if(renderFormat != pixelFormat) //need conversion
    {
        auto convertedFormat = backend::PixelFormatUtils::convertDataToFormat(data, dataLen, pixelFormat, renderFormat, &outData, &outDataLen);
#ifdef CC_USE_METAL
        CCASSERT(convertedFormat == renderFormat, "PixelFormat convert failed!");
#endif
        if(convertedFormat == renderFormat) pixelFormat = renderFormat;
    }

    backend::StringUtils::PixelFormat format = static_cast<backend::StringUtils::PixelFormat>(pixelFormat);
    CCASSERT(format != backend::StringUtils::PixelFormat::NONE, "PixelFormat should not be NONE");
    
    textureDescriptor.textureFormat = backend::StringUtils::PixelFormat2TextureFormat(format);
    CCASSERT(textureDescriptor.textureFormat != backend::TextureFormat::NONE, "TextureFormat should not be NONE");
    
    textureDescriptor.compressed = info.compressed;
    
    _texture = device->newTexture(textureDescriptor);

    _texture->updateData(outData);
    if(outData && outData != data && outDataLen > 0)
    {
        free(outData);
        outData = nullptr;
        outDataLen = 0;
    }
    
    _contentSize = Size((float)pixelsWide, (float)pixelsHigh);
    _pixelsWide = pixelsWide;
    _pixelsHigh = pixelsHigh;
    _pixelFormat = pixelFormat;
    _maxS = 1;
    _maxT = 1;

    _hasPremultipliedAlpha = false;
    _hasMipmaps = mipmapsNum > 1;

    return true;
}

bool Texture2D::updateWithData(void *data,int offsetX,int offsetY,int width,int height)
{
    if (_texture && width > 0 && height > 0)
    {
        uint8_t* textureData = static_cast<uint8_t*>(data);
        _texture->updateSubData(offsetX, offsetY, width, height, textureData);
        return true;
    }
    return false;
}

// implementation Texture2D (Image)
bool Texture2D::initWithImage(Image *image)
{
    return initWithImage(image, g_defaultAlphaPixelFormat);
}

bool Texture2D::initWithImage(Image *image, PixelFormat format)
{
    if (image == nullptr)
    {
        CCLOG("cocos2d: Texture2D. Can't create Texture. UIImage is nil");
        return false;
    }

    int imageWidth = image->getWidth();
    int imageHeight = image->getHeight();
    this->_filePath = image->getFilePath();
//    Configuration *conf = Configuration::getInstance();
//
//    int maxTextureSize = conf->getMaxTextureSize();
//    if (imageWidth > maxTextureSize || imageHeight > maxTextureSize)
//    {
//        CCLOG("cocos2d: WARNING: Image (%u x %u) is bigger than the supported %u x %u", imageWidth, imageHeight, maxTextureSize, maxTextureSize);
//        return false;
//    }

    unsigned char*   tempData = image->getData();
    Size             imageSize = Size((float)imageWidth, (float)imageHeight);
    PixelFormat      renderFormat = ((PixelFormat::NONE == format) || (PixelFormat::AUTO == format)) ? image->getPixelFormat() : format;
    PixelFormat      imagePixelFormat = image->getPixelFormat();
    size_t           tempDataLen = image->getDataLen();

    
#ifdef CC_USE_METAL
    //compressed format does not need conversion
    switch (imagePixelFormat) {
        case PixelFormat::PVRTC4A:
        case PixelFormat::PVRTC4:
        case PixelFormat::PVRTC2A:
        case PixelFormat::PVRTC2:
        case PixelFormat::A8:
            renderFormat = imagePixelFormat;
        default:
            break;
    }
    //override renderFormat, since some render format is not supported by metal
    switch (renderFormat)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        //packed 16 bits pixels only available on iOS
        case PixelFormat::RGB565:
            renderFormat = PixelFormat::MTL_B5G6R5;
            break;
        case PixelFormat::RGBA4444:
            renderFormat = PixelFormat::MTL_ABGR4;
            break;
        case PixelFormat::RGB5A1:
            renderFormat = PixelFormat::MTL_BGR5A1;
            break;
#else
        case PixelFormat::RGB565:
        case PixelFormat::RGB5A1:
        case PixelFormat::RGBA4444:
#endif
        case PixelFormat::I8:
        case PixelFormat::AI88:
            //TODO: conversion RGBA8888 -> I8(AI88) -> RGBA8888 may happends
            renderFormat = PixelFormat::RGBA8888;
            break;
        default:
            break;
    }
#endif

    if (image->getNumberOfMipmaps() > 1)
    {
        if (renderFormat != image->getPixelFormat())
        {
            CCLOG("cocos2d: WARNING: This image has more than 1 mipmaps and we will not convert the data format");
        }

        //pixel format of data is not converted, renderFormat can be different from pixelFormat
        //it will be done later
        initWithMipmaps(image->getMipmaps(), image->getNumberOfMipmaps(), image->getPixelFormat(), renderFormat, imageWidth, imageHeight);
        
        // set the premultiplied tag
        _hasPremultipliedAlpha = image->hasPremultipliedAlpha();
        
        return true;
    }
    else if (image->isCompressed())
    {
        if (renderFormat != image->getPixelFormat())
        {
            CCLOG("cocos2d: WARNING: This image is compressed and we can't convert it for now");
        }
        
        initWithData(tempData, tempDataLen, image->getPixelFormat(), imageWidth, imageHeight, imageSize);
        
        // set the premultiplied tag
        _hasPremultipliedAlpha = image->hasPremultipliedAlpha();
        
        return true;
    }
    else
    {
        //after conversion, renderFormat == pixelFormat of data
        initWithData(tempData, tempDataLen, imagePixelFormat, renderFormat, imageWidth, imageHeight, imageSize);
        
        // set the premultiplied tag
        _hasPremultipliedAlpha = image->hasPremultipliedAlpha();
        
        return true;
    }
}

// implementation Texture2D (Text)
bool Texture2D::initWithString(const char *text, const std::string& fontName, float fontSize, const Size& dimensions/* = Size(0, 0)*/, TextHAlignment hAlignment/* =  TextHAlignment::CENTER */, TextVAlignment vAlignment/* =  TextVAlignment::TOP */, bool enableWrap /* = false */, int overflow /* = 0 */)
{
    FontDefinition tempDef;
    
    tempDef._shadow._shadowEnabled = false;
    tempDef._stroke._strokeEnabled = false;
   
    
    tempDef._fontName      = fontName;
    tempDef._fontSize      = fontSize;
    tempDef._dimensions    = dimensions;
    tempDef._alignment     = hAlignment;
    tempDef._vertAlignment = vAlignment;
    tempDef._fontFillColor = Color3B::WHITE;
    tempDef._enableWrap    = enableWrap;
    tempDef._overflow      = overflow;

    return initWithString(text, tempDef);
}

bool Texture2D::initWithString(const char *text, const FontDefinition& textDefinition)
{
    if(!text || 0 == strlen(text))
    {
        return false;
    }

#if CC_ENABLE_CACHE_TEXTURE_DATA
    // cache the texture data
    VolatileTextureMgr::addStringTexture(this, text, textDefinition);
#endif

    bool ret = false;
    Device::TextAlign align;
    
    if (TextVAlignment::TOP == textDefinition._vertAlignment)
    {
        align = (TextHAlignment::CENTER == textDefinition._alignment) ? Device::TextAlign::TOP
        : (TextHAlignment::LEFT == textDefinition._alignment) ? Device::TextAlign::TOP_LEFT : Device::TextAlign::TOP_RIGHT;
    }
    else if (TextVAlignment::CENTER == textDefinition._vertAlignment)
    {
        align = (TextHAlignment::CENTER == textDefinition._alignment) ? Device::TextAlign::CENTER
        : (TextHAlignment::LEFT == textDefinition._alignment) ? Device::TextAlign::LEFT : Device::TextAlign::RIGHT;
    }
    else if (TextVAlignment::BOTTOM == textDefinition._vertAlignment)
    {
        align = (TextHAlignment::CENTER == textDefinition._alignment) ? Device::TextAlign::BOTTOM
        : (TextHAlignment::LEFT == textDefinition._alignment) ? Device::TextAlign::BOTTOM_LEFT : Device::TextAlign::BOTTOM_RIGHT;
    }
    else
    {
        CCASSERT(false, "Not supported alignment format!");
        return false;
    }
    
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID) && (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
    CCASSERT(textDefinition._stroke._strokeEnabled == false, "Currently stroke only supported on iOS and Android!");
#endif

    PixelFormat      pixelFormat = g_defaultAlphaPixelFormat;
    unsigned char* outTempData = nullptr;
    ssize_t outTempDataLen = 0;

    int imageWidth;
    int imageHeight;
    auto textDef = textDefinition;
    auto contentScaleFactor = CC_CONTENT_SCALE_FACTOR();
    textDef._fontSize *= contentScaleFactor;
    textDef._dimensions.width *= contentScaleFactor;
    textDef._dimensions.height *= contentScaleFactor;
    textDef._stroke._strokeSize *= contentScaleFactor;
    textDef._shadow._shadowEnabled = false;
    
    bool hasPremultipliedAlpha;
    Data outData = Device::getTextureDataForText(text, textDef, align, imageWidth, imageHeight, hasPremultipliedAlpha);
    if(outData.isNull())
    {
        return false;
    }

    Size  imageSize = Size((float)imageWidth, (float)imageHeight);
    pixelFormat = backend::PixelFormatUtils::convertDataToFormat(outData.getBytes(), imageWidth*imageHeight*4, PixelFormat::RGBA8888, pixelFormat, &outTempData, &outTempDataLen);

    ret = initWithData(outTempData, outTempDataLen, pixelFormat, imageWidth, imageHeight, imageSize);

    if (outTempData != nullptr && outTempData != outData.getBytes())
    {
        free(outTempData);
    }
    _hasPremultipliedAlpha = hasPremultipliedAlpha;

    return ret;
}

bool Texture2D::initWithBackendTexture(backend::Texture *texture)
{
    CC_SAFE_RETAIN(texture);
    CC_SAFE_RELEASE(_texture);
    _texture = texture;
    
    _pixelsWide = _contentSize.width = texture->getWidth();
    _pixelsHigh = _contentSize.height = texture->getHeight();
    return true;
}


//// implementation Texture2D (Drawing)
//
//void Texture2D::drawAtPoint(const Vec2& point)
//{
//    GLfloat    coordinates[] = {
//        0.0f,    _maxT,
//        _maxS,_maxT,
//        0.0f,    0.0f,
//        _maxS,0.0f };
//
//    GLfloat    width = (GLfloat)_pixelsWide * _maxS,
//        height = (GLfloat)_pixelsHigh * _maxT;
//
//    GLfloat        vertices[] = {    
//        point.x,            point.y,
//        width + point.x,    point.y,
//        point.x,            height  + point.y,
//        width + point.x,    height  + point.y };
//
//    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
//    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
//    _shaderProgram->use();
//    _shaderProgram->setUniformsForBuiltins();
//
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, _name);
//
//    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
//    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, coordinates);
//
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//}
//
//void Texture2D::drawInRect(const Rect& rect)
//{
//    GLfloat    coordinates[] = {    
//        0.0f,    _maxT,
//        _maxS,_maxT,
//        0.0f,    0.0f,
//        _maxS,0.0f };
//
//    GLfloat    vertices[] = {    rect.origin.x,        rect.origin.y,                            /*0.0f,*/
//        rect.origin.x + rect.size.width,        rect.origin.y,                            /*0.0f,*/
//        rect.origin.x,                            rect.origin.y + rect.size.height,        /*0.0f,*/
//        rect.origin.x + rect.size.width,        rect.origin.y + rect.size.height,        /*0.0f*/ };
//
//    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
//    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
//    _shaderProgram->use();
//    _shaderProgram->setUniformsForBuiltins();
//
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, _name);
//
//    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
//    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, coordinates);
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//}

bool Texture2D::hasMipmaps() const
{
    return _hasMipmaps;
}

void Texture2D::setAliasTexParameters()
{

    backend::SamplerDescriptor descriptor(false,
        backend::SamplerFilter::NEAREST,
        backend::SamplerFilter::NEAREST,
        backend::SamplerFilter::NEAREST,
        backend::SamplerAddressMode::DONT_CARE,
        backend::SamplerAddressMode::DONT_CARE
    );

    setSamplerDescriptor(descriptor);
}

void Texture2D::setAntiAliasTexParameters()
{

    backend::SamplerDescriptor descriptor(false,
        backend::SamplerFilter::LINEAR,
        backend::SamplerFilter::LINEAR,
        backend::SamplerFilter::LINEAR,
        backend::SamplerAddressMode::DONT_CARE,
        backend::SamplerAddressMode::DONT_CARE
    );
    setSamplerDescriptor(descriptor);
}

const char* Texture2D::getStringForFormat() const
{
    switch (_pixelFormat) 
    {
        case Texture2D::PixelFormat::RGBA8888:
            return  "RGBA8888";

        case Texture2D::PixelFormat::RGB888:
            return  "RGB888";

        case Texture2D::PixelFormat::RGB565:
            return  "RGB565";

        case Texture2D::PixelFormat::RGBA4444:
            return  "RGBA4444";

        case Texture2D::PixelFormat::RGB5A1:
            return  "RGB5A1";

        case Texture2D::PixelFormat::AI88:
            return  "AI88";

        case Texture2D::PixelFormat::A8:
            return  "A8";

        case Texture2D::PixelFormat::I8:
            return  "I8";

        case Texture2D::PixelFormat::PVRTC4:
            return  "PVRTC4";

        case Texture2D::PixelFormat::PVRTC2:
            return  "PVRTC2";

        case Texture2D::PixelFormat::PVRTC2A:
            return "PVRTC2A";
        
        case Texture2D::PixelFormat::PVRTC4A:
            return "PVRTC4A";
            
        case Texture2D::PixelFormat::ETC:
            return "ETC";

        case Texture2D::PixelFormat::S3TC_DXT1:
            return "S3TC_DXT1";
            
        case Texture2D::PixelFormat::S3TC_DXT3:
            return "S3TC_DXT3";

        case Texture2D::PixelFormat::S3TC_DXT5:
            return "S3TC_DXT5";
            
        case Texture2D::PixelFormat::ATC_RGB:
            return "ATC_RGB";

        case Texture2D::PixelFormat::ATC_EXPLICIT_ALPHA:
            return "ATC_EXPLICIT_ALPHA";

        case Texture2D::PixelFormat::ATC_INTERPOLATED_ALPHA:
            return "ATC_INTERPOLATED_ALPHA";
        
        case Texture2D::PixelFormat::MTL_ABGR4:
            return "MTL_ABGR4";
        
        case Texture2D::PixelFormat::MTL_B5G6R5:
            return "MTL_RGB565";
        
        case Texture2D::PixelFormat::MTL_BGR5A1:
            return "MTL_BGR5A1";
            
        default:
            CCASSERT(false , "unrecognized pixel format");
            CCLOG("stringForFormat: %ld, cannot give useful result", (long)_pixelFormat);
            break;
    }

    return  nullptr;
}

//
// Texture options for images that contains alpha
//
// implementation Texture2D (PixelFormat)

void Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat format)
{
    g_defaultAlphaPixelFormat = format;
}

Texture2D::PixelFormat Texture2D::getDefaultAlphaPixelFormat()
{
    return g_defaultAlphaPixelFormat;
}

unsigned int Texture2D::getBitsPerPixelForFormat(Texture2D::PixelFormat format) const
{
    if (format == PixelFormat::NONE || format == PixelFormat::DEFAULT)
    {
        return 0;
    }
    
    return _pixelFormatInfoTables.at(format).bpp;
}

unsigned int Texture2D::getBitsPerPixelForFormat() const
{
    return this->getBitsPerPixelForFormat(_pixelFormat);
}

const Texture2D::PixelFormatInfoMap& Texture2D::getPixelFormatInfoMap()
{
    return _pixelFormatInfoTables;
}

void Texture2D::addSpriteFrameCapInset(SpriteFrame* spritframe, const Rect& capInsets)
{
    if(nullptr == _ninePatchInfo)
    {
        _ninePatchInfo = new (std::nothrow) NinePatchInfo;
    }
    if(nullptr == spritframe)
    {
        _ninePatchInfo->capInsetSize = capInsets;
    }
    else
    {
        _ninePatchInfo->capInsetMap[spritframe] = capInsets;
    }
}

bool Texture2D::isContain9PatchInfo()const
{
    return nullptr != _ninePatchInfo;
}

const Rect& Texture2D::getSpriteFrameCapInset( cocos2d::SpriteFrame *spriteFrame )const
{
    CCASSERT(_ninePatchInfo != nullptr,
             "Can't get the sprite frame capInset when the texture contains no 9-patch info.");
    if(nullptr == spriteFrame)
    {
        return this->_ninePatchInfo->capInsetSize;
    }
    else
    {
        auto &capInsetMap = this->_ninePatchInfo->capInsetMap;
        if(capInsetMap.find(spriteFrame) != capInsetMap.end())
        {
            return capInsetMap.at(spriteFrame);
        }
        else
        {
            return this->_ninePatchInfo->capInsetSize;
        }
    }
}


void Texture2D::removeSpriteFrameCapInset(SpriteFrame* spriteFrame)
{
    if(nullptr != this->_ninePatchInfo)
    {
        auto capInsetMap = this->_ninePatchInfo->capInsetMap;
        if(capInsetMap.find(spriteFrame) != capInsetMap.end())
        {
            capInsetMap.erase(spriteFrame);
        }
    }
}

/// halx99 spec, ANDROID ETC1 ALPHA supports.
void Texture2D::setAlphaTexture(Texture2D* alphaTexture)
{
    if (alphaTexture != nullptr) {
        this->_alphaTexture = alphaTexture;
        this->_alphaTexture->retain();
        this->_hasPremultipliedAlpha = true; // PremultipliedAlpha should be true.
    }
}

Texture2D* Texture2D::getAlphaTexture() const
{
    return _alphaTexture;
}

void Texture2D::setSamplerDescriptor(const backend::SamplerDescriptor &texParams)
{
    _texture->updateSamplerDescriptor(texParams);
}

//TODO: should be reform later
void Texture2D::setTexParameters(const Texture2D::TexParams &params)
{
    backend::SamplerDescriptor sd;
    sd.minFilter = GLToBackendMagFilter(params.minFilter);
    sd.magFilter = GLToBackendMagFilter(params.magFilter);
    sd.mipmapEnabled = true;
    sd.mipmapFilter = backend::SamplerFilter::DONT_CARE;
    sd.tAddressMode = GLToBackendAddressMode(params.wrapT);
    sd.sAddressMode = GLToBackendAddressMode(params.wrapS);
    setSamplerDescriptor(sd);
}

//  TODO coulsonwang
//// implementation Texture2D (GLFilter)
void Texture2D::generateMipmap()
{
//    CCASSERT(_pixelsWide == ccNextPOT(_pixelsWide) && _pixelsHigh == ccNextPOT(_pixelsHigh), "Mipmap texture only works in POT textures");
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, _name);
//    glGenerateMipmap(GL_TEXTURE_2D);
//    _hasMipmaps = true;
//#if CC_ENABLE_CACHE_TEXTURE_DATA
//    VolatileTextureMgr::setHasMipmaps(this, _hasMipmaps);
//#endif
}



NS_CC_END
