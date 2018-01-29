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
#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgramCache.h"
#include "base/CCNinePatchImageParser.h"

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
        
#ifdef GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG
        PixelFormatInfoMapValue(Texture2D::PixelFormat::PVRTC2, Texture2D::PixelFormatInfo(GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 2, true, false)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::PVRTC2A, Texture2D::PixelFormatInfo(GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 2, true, true)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::PVRTC4, Texture2D::PixelFormatInfo(GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, false)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::PVRTC4A, Texture2D::PixelFormatInfo(GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, true)),
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
    };
}

//CLASS IMPLEMENTATIONS:

//The PixpelFormat corresponding information
const Texture2D::PixelFormatInfoMap Texture2D::_pixelFormatInfoTables(TexturePixelFormatInfoTablesValue,
                                                                     TexturePixelFormatInfoTablesValue + sizeof(TexturePixelFormatInfoTablesValue) / sizeof(TexturePixelFormatInfoTablesValue[0]));

// If the image has alpha, you can create RGBA8 (32-bit) or RGBA4 (16-bit) or RGB5A1 (16-bit)
// Default is: RGBA8888 (32-bit textures)
static Texture2D::PixelFormat g_defaultAlphaPixelFormat = Texture2D::PixelFormat::DEFAULT;

//////////////////////////////////////////////////////////////////////////
//convertor function

// IIIIIIII -> RRRRRRRRGGGGGGGGGBBBBBBBB
void Texture2D::convertI8ToRGB888(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i=0; i < dataLen; ++i)
    {
        *outData++ = data[i];     //R
        *outData++ = data[i];     //G
        *outData++ = data[i];     //B
    }
}

// IIIIIIIIAAAAAAAA -> RRRRRRRRGGGGGGGGBBBBBBBB
void Texture2D::convertAI88ToRGB888(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 1; i < l; i += 2)
    {
        *outData++ = data[i];     //R
        *outData++ = data[i];     //G
        *outData++ = data[i];     //B
    }
}

// IIIIIIII -> RRRRRRRRGGGGGGGGGBBBBBBBBAAAAAAAA
void Texture2D::convertI8ToRGBA8888(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0; i < dataLen; ++i)
    {
        *outData++ = data[i];     //R
        *outData++ = data[i];     //G
        *outData++ = data[i];     //B
        *outData++ = 0xFF;        //A
    }
}

// IIIIIIIIAAAAAAAA -> RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA
void Texture2D::convertAI88ToRGBA8888(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 1; i < l; i += 2)
    {
        *outData++ = data[i];     //R
        *outData++ = data[i];     //G
        *outData++ = data[i];     //B
        *outData++ = data[i + 1]; //A
    }
}

// IIIIIIII -> RRRRRGGGGGGBBBBB
void Texture2D::convertI8ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (int i = 0; i < dataLen; ++i)
    {
        *out16++ = (data[i] & 0x00F8) << 8    //R
            | (data[i] & 0x00FC) << 3         //G
            | (data[i] & 0x00F8) >> 3;        //B
    }
}

// IIIIIIIIAAAAAAAA -> RRRRRGGGGGGBBBBB
void Texture2D::convertAI88ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0, l = dataLen - 1; i < l; i += 2)
    {
        *out16++ = (data[i] & 0x00F8) << 8    //R
            | (data[i] & 0x00FC) << 3         //G
            | (data[i] & 0x00F8) >> 3;        //B
    }
}

// IIIIIIII -> RRRRGGGGBBBBAAAA
void Texture2D::convertI8ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0; i < dataLen; ++i)
    {
        *out16++ = (data[i] & 0x00F0) << 8    //R
        | (data[i] & 0x00F0) << 4             //G
        | (data[i] & 0x00F0)                  //B
        | 0x000F;                             //A
    }
}

// IIIIIIIIAAAAAAAA -> RRRRGGGGBBBBAAAA
void Texture2D::convertAI88ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0, l = dataLen - 1; i < l; i += 2)
    {
        *out16++ = (data[i] & 0x00F0) << 8    //R
        | (data[i] & 0x00F0) << 4             //G
        | (data[i] & 0x00F0)                  //B
        | (data[i+1] & 0x00F0) >> 4;          //A
    }
}

// IIIIIIII -> RRRRRGGGGGBBBBBA
void Texture2D::convertI8ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (int i = 0; i < dataLen; ++i)
    {
        *out16++ = (data[i] & 0x00F8) << 8    //R
            | (data[i] & 0x00F8) << 3         //G
            | (data[i] & 0x00F8) >> 2         //B
            | 0x0001;                         //A
    }
}

// IIIIIIIIAAAAAAAA -> RRRRRGGGGGBBBBBA
void Texture2D::convertAI88ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0, l = dataLen - 1; i < l; i += 2)
    {
        *out16++ = (data[i] & 0x00F8) << 8    //R
            | (data[i] & 0x00F8) << 3         //G
            | (data[i] & 0x00F8) >> 2         //B
            | (data[i + 1] & 0x0080) >> 7;    //A
    }
}

// IIIIIIII -> IIIIIIIIAAAAAAAA
void Texture2D::convertI8ToAI88(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0; i < dataLen; ++i)
    {
        *out16++ = 0xFF00     //A
        | data[i];            //I
    }
}

// IIIIIIIIAAAAAAAA -> AAAAAAAA
void Texture2D::convertAI88ToA8(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 1; i < dataLen; i += 2)
    {
        *outData++ = data[i]; //A
    }
}

// IIIIIIIIAAAAAAAA -> IIIIIIII
void Texture2D::convertAI88ToI8(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 1; i < l; i += 2)
    {
        *outData++ = data[i]; //R
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA
void Texture2D::convertRGB888ToRGBA8888(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 2; i < l; i += 3)
    {
        *outData++ = data[i];         //R
        *outData++ = data[i + 1];     //G
        *outData++ = data[i + 2];     //B
        *outData++ = 0xFF;            //A
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA -> RRRRRRRRGGGGGGGGBBBBBBBB
void Texture2D::convertRGBA8888ToRGB888(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 3; i < l; i += 4)
    {
        *outData++ = data[i];         //R
        *outData++ = data[i + 1];     //G
        *outData++ = data[i + 2];     //B
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> RRRRRGGGGGGBBBBB
void Texture2D::convertRGB888ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0, l = dataLen - 2; i < l; i += 3)
    {
        *out16++ = (data[i] & 0x00F8) << 8    //R
            | (data[i + 1] & 0x00FC) << 3     //G
            | (data[i + 2] & 0x00F8) >> 3;    //B
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA -> RRRRRGGGGGGBBBBB
void Texture2D::convertRGBA8888ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0, l = dataLen - 3; i < l; i += 4)
    {
        *out16++ = (data[i] & 0x00F8) << 8    //R
            | (data[i + 1] & 0x00FC) << 3     //G
            | (data[i + 2] & 0x00F8) >> 3;    //B
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> AAAAAAAA
void Texture2D::convertRGB888ToA8(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 2; i < l; i += 3)
    {
        *outData++ = (data[i] * 299 + data[i + 1] * 587 + data[i + 2] * 114 + 500) / 1000;  //A =  (R*299 + G*587 + B*114 + 500) / 1000
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> IIIIIIII
void Texture2D::convertRGB888ToI8(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 2; i < l; i += 3)
    {
        *outData++ = (data[i] * 299 + data[i + 1] * 587 + data[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA -> IIIIIIII
void Texture2D::convertRGBA8888ToI8(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 3; i < l; i += 4)
    {
        *outData++ = (data[i] * 299 + data[i + 1] * 587 + data[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA -> AAAAAAAA
void Texture2D::convertRGBA8888ToA8(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen -3; i < l; i += 4)
    {
        *outData++ = data[i + 3]; //A
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> IIIIIIIIAAAAAAAA
void Texture2D::convertRGB888ToAI88(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 2; i < l; i += 3)
    {
        *outData++ = (data[i] * 299 + data[i + 1] * 587 + data[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
        *outData++ = 0xFF;
    }
}


// RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA -> IIIIIIIIAAAAAAAA
void Texture2D::convertRGBA8888ToAI88(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 3; i < l; i += 4)
    {
        *outData++ = (data[i] * 299 + data[i + 1] * 587 + data[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
        *outData++ = data[i + 3];
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> RRRRGGGGBBBBAAAA
void Texture2D::convertRGB888ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0, l = dataLen - 2; i < l; i += 3)
    {
        *out16++ = ((data[i] & 0x00F0) << 8           //R
                    | (data[i + 1] & 0x00F0) << 4     //G
                    | (data[i + 2] & 0xF0)            //B
                    |  0x0F);                         //A
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA -> RRRRGGGGBBBBAAAA
void Texture2D::convertRGBA8888ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0, l = dataLen - 3; i < l; i += 4)
    {
        *out16++ = (data[i] & 0x00F0) << 8    //R
        | (data[i + 1] & 0x00F0) << 4         //G
        | (data[i + 2] & 0xF0)                //B
        |  (data[i + 3] & 0xF0) >> 4;         //A
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> RRRRRGGGGGBBBBBA
void Texture2D::convertRGB888ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0, l = dataLen - 2; i < l; i += 3)
    {
        *out16++ = (data[i] & 0x00F8) << 8    //R
            | (data[i + 1] & 0x00F8) << 3     //G
            | (data[i + 2] & 0x00F8) >> 2     //B
            |  0x01;                          //A
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> RRRRRGGGGGBBBBBA
void Texture2D::convertRGBA8888ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0, l = dataLen - 2; i < l; i += 4)
    {
        *out16++ = (data[i] & 0x00F8) << 8    //R
            | (data[i + 1] & 0x00F8) << 3     //G
            | (data[i + 2] & 0x00F8) >> 2     //B
            |  (data[i + 3] & 0x0080) >> 7;   //A
    }
}
// converter function end
//////////////////////////////////////////////////////////////////////////

Texture2D::Texture2D()
: _pixelFormat(Texture2D::PixelFormat::DEFAULT)
, _pixelsWide(0)
, _pixelsHigh(0)
, _name(0)
, _maxS(0.0)
, _maxT(0.0)
, _hasPremultipliedAlpha(false)
, _hasMipmaps(false)
, _shaderProgram(nullptr)
, _antialiasEnabled(true)
, _ninePatchInfo(nullptr)
, _valid(true)
, _alphaTexture(nullptr)
{
}

Texture2D::~Texture2D()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    VolatileTextureMgr::removeTexture(this);
#endif
    CC_SAFE_RELEASE_NULL(_alphaTexture); // ETC1 ALPHA support.

    CCLOGINFO("deallocing Texture2D: %p - id=%u", this, _name);
    CC_SAFE_RELEASE(_shaderProgram);

    CC_SAFE_DELETE(_ninePatchInfo);

    if(_name)
    {
        GL::deleteTexture(_name);
    }
}

void Texture2D::releaseGLTexture()
{
    if(_name)
    {
        GL::deleteTexture(_name);
    }
    _name = 0;
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
    return _name;
}

GLuint Texture2D::getAlphaTextureName() const
{
    return _alphaTexture == nullptr ? 0 : _alphaTexture->getName();
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

GLProgram* Texture2D::getGLProgram() const
{
    return _shaderProgram;
}

void Texture2D::setGLProgram(GLProgram* shaderProgram)
{
    CC_SAFE_RETAIN(shaderProgram);
    CC_SAFE_RELEASE(_shaderProgram);
    _shaderProgram = shaderProgram;
}

bool Texture2D::hasPremultipliedAlpha() const
{
    return _hasPremultipliedAlpha;
}

bool Texture2D::initWithData(const void *data, ssize_t dataLen, Texture2D::PixelFormat pixelFormat, int pixelsWide, int pixelsHigh, const Size& /*contentSize*/)
{
    CCASSERT(dataLen>0 && pixelsWide>0 && pixelsHigh>0, "Invalid size");

    //if data has no mipmaps, we will consider it has only one mipmap
    MipmapInfo mipmap;
    mipmap.address = (unsigned char*)data;
    mipmap.len = static_cast<int>(dataLen);
    return initWithMipmaps(&mipmap, 1, pixelFormat, pixelsWide, pixelsHigh);
}

bool Texture2D::initWithMipmaps(MipmapInfo* mipmaps, int mipmapsNum, PixelFormat pixelFormat, int pixelsWide, int pixelsHigh)
{


    //the pixelFormat must be a certain value 
    CCASSERT(pixelFormat != PixelFormat::NONE && pixelFormat != PixelFormat::AUTO, "the \"pixelFormat\" param must be a certain value!");
    CCASSERT(pixelsWide>0 && pixelsHigh>0, "Invalid size");

    if (mipmapsNum <= 0)
    {
        CCLOG("cocos2d: WARNING: mipmap number is less than 1");
        return false;
    }
    

    if(_pixelFormatInfoTables.find(pixelFormat) == _pixelFormatInfoTables.end())
    {
        CCLOG("cocos2d: WARNING: unsupported pixelformat: %lx", (unsigned long)pixelFormat );
        return false;
    }

    const PixelFormatInfo& info = _pixelFormatInfoTables.at(pixelFormat);

    if (info.compressed && !Configuration::getInstance()->supportsPVRTC()
                        && !Configuration::getInstance()->supportsETC()
                        && !Configuration::getInstance()->supportsS3TC()
                        && !Configuration::getInstance()->supportsATITC())
    {
        CCLOG("cocos2d: WARNING: PVRTC/ETC images are not supported");
        return false;
    }

    //Set the row align only when mipmapsNum == 1 and the data is uncompressed
    if (mipmapsNum == 1 && !info.compressed)
    {
        unsigned int bytesPerRow = pixelsWide * info.bpp / 8;

        if(bytesPerRow % 8 == 0)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 8);
        }
        else if(bytesPerRow % 4 == 0)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        }
        else if(bytesPerRow % 2 == 0)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
        }
        else
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        }
    }else
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    }

    if(_name != 0)
    {
        GL::deleteTexture(_name);
        _name = 0;
    }

    glGenTextures(1, &_name);
    GL::bindTexture2D(_name);

    if (mipmapsNum == 1)
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _antialiasEnabled ? GL_LINEAR : GL_NEAREST);
    }else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _antialiasEnabled ? GL_LINEAR_MIPMAP_NEAREST : GL_NEAREST_MIPMAP_NEAREST);
    }
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _antialiasEnabled ? GL_LINEAR : GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

#if CC_ENABLE_CACHE_TEXTURE_DATA
    if (_antialiasEnabled)
    {
        TexParams texParams = {(GLuint)(_hasMipmaps?GL_LINEAR_MIPMAP_NEAREST:GL_LINEAR),GL_LINEAR,GL_NONE,GL_NONE};
        VolatileTextureMgr::setTexParameters(this, texParams);
    } 
    else
    {
        TexParams texParams = {(GLuint)(_hasMipmaps?GL_NEAREST_MIPMAP_NEAREST:GL_NEAREST),GL_NEAREST,GL_NONE,GL_NONE};
        VolatileTextureMgr::setTexParameters(this, texParams);
    }
#endif

    // clean possible GL error
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        cocos2d::log("OpenGL error 0x%04X in %s %s %d\n", err, __FILE__, __FUNCTION__, __LINE__);
    }
    
    // Specify OpenGL texture image
    int width = pixelsWide;
    int height = pixelsHigh;
    
    for (int i = 0; i < mipmapsNum; ++i)
    {
        unsigned char *data = mipmaps[i].address;
        GLsizei datalen = mipmaps[i].len;

        if (info.compressed)
        {
            glCompressedTexImage2D(GL_TEXTURE_2D, i, info.internalFormat, (GLsizei)width, (GLsizei)height, 0, datalen, data);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, i, info.internalFormat, (GLsizei)width, (GLsizei)height, 0, info.format, info.type, data);
        }

        if (i > 0 && (width != height || ccNextPOT(width) != width ))
        {
            CCLOG("cocos2d: Texture2D. WARNING. Mipmap level %u is not squared. Texture won't render correctly. width=%d != height=%d", i, width, height);
        }

        err = glGetError();
        if (err != GL_NO_ERROR)
        {
            CCLOG("cocos2d: Texture2D: Error uploading compressed texture level: %u . glError: 0x%04X", i, err);
            return false;
        }

        width = MAX(width >> 1, 1);
        height = MAX(height >> 1, 1);
    }

    _contentSize = Size((float)pixelsWide, (float)pixelsHigh);
    _pixelsWide = pixelsWide;
    _pixelsHigh = pixelsHigh;
    _pixelFormat = pixelFormat;
    _maxS = 1;
    _maxT = 1;

    _hasPremultipliedAlpha = false;
    _hasMipmaps = mipmapsNum > 1;

    // shader
    setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE));
    return true;
}

bool Texture2D::updateWithData(const void *data,int offsetX,int offsetY,int width,int height)
{
    if (_name)
    {
        GL::bindTexture2D(_name);
        const PixelFormatInfo& info = _pixelFormatInfoTables.at(_pixelFormat);
        glTexSubImage2D(GL_TEXTURE_2D,0,offsetX,offsetY,width,height,info.format, info.type,data);

        return true;
    }
    return false;
}

std::string Texture2D::getDescription() const
{
    return StringUtils::format("<Texture2D | Name = %u | Dimensions = %ld x %ld | Coordinates = (%.2f, %.2f)>", _name, (long)_pixelsWide, (long)_pixelsHigh, _maxS, _maxT);
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
    Configuration *conf = Configuration::getInstance();

    int maxTextureSize = conf->getMaxTextureSize();
    if (imageWidth > maxTextureSize || imageHeight > maxTextureSize) 
    {
        CCLOG("cocos2d: WARNING: Image (%u x %u) is bigger than the supported %u x %u", imageWidth, imageHeight, maxTextureSize, maxTextureSize);
        return false;
    }

    unsigned char*   tempData = image->getData();
    Size             imageSize = Size((float)imageWidth, (float)imageHeight);
    PixelFormat      pixelFormat = ((PixelFormat::NONE == format) || (PixelFormat::AUTO == format)) ? image->getRenderFormat() : format;
    PixelFormat      renderFormat = image->getRenderFormat();
    size_t           tempDataLen = image->getDataLen();


    if (image->getNumberOfMipmaps() > 1)
    {
        if (pixelFormat != image->getRenderFormat())
        {
            CCLOG("cocos2d: WARNING: This image has more than 1 mipmaps and we will not convert the data format");
        }

        initWithMipmaps(image->getMipmaps(), image->getNumberOfMipmaps(), image->getRenderFormat(), imageWidth, imageHeight);
        
        // set the premultiplied tag
        _hasPremultipliedAlpha = image->hasPremultipliedAlpha();
        
        return true;
    }
    else if (image->isCompressed())
    {
        if (pixelFormat != image->getRenderFormat())
        {
            CCLOG("cocos2d: WARNING: This image is compressed and we can't convert it for now");
        }

        initWithData(tempData, tempDataLen, image->getRenderFormat(), imageWidth, imageHeight, imageSize);
        
        // set the premultiplied tag
        _hasPremultipliedAlpha = image->hasPremultipliedAlpha();
        
        return true;
    }
    else
    {
        unsigned char* outTempData = nullptr;
        ssize_t outTempDataLen = 0;

        pixelFormat = convertDataToFormat(tempData, tempDataLen, renderFormat, pixelFormat, &outTempData, &outTempDataLen);

        initWithData(outTempData, outTempDataLen, pixelFormat, imageWidth, imageHeight, imageSize);


        if (outTempData != nullptr && outTempData != tempData)
        {

            free(outTempData);
        }

        // set the premultiplied tag
        _hasPremultipliedAlpha = image->hasPremultipliedAlpha();
        
        return true;
    }
}

Texture2D::PixelFormat Texture2D::convertI8ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen)
{
    switch (format)
    {
    case PixelFormat::RGBA8888:
        *outDataLen = dataLen*4;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertI8ToRGBA8888(data, dataLen, *outData);
        break;
    case PixelFormat::RGB888:
        *outDataLen = dataLen*3;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertI8ToRGB888(data, dataLen, *outData);
        break;
    case PixelFormat::RGB565:
        *outDataLen = dataLen*2;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertI8ToRGB565(data, dataLen, *outData);
        break;
    case PixelFormat::AI88:
        *outDataLen = dataLen*2;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertI8ToAI88(data, dataLen, *outData);
        break;
    case PixelFormat::RGBA4444:
        *outDataLen = dataLen*2;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertI8ToRGBA4444(data, dataLen, *outData);
        break;
    case PixelFormat::RGB5A1:
        *outDataLen = dataLen*2;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertI8ToRGB5A1(data, dataLen, *outData);
        break;
    default:
        // unsupported conversion or don't need to convert
        if (format != PixelFormat::AUTO && format != PixelFormat::I8)
        {
            CCLOG("Can not convert image format PixelFormat::I8 to format ID:%d, we will use it's origin format PixelFormat::I8", static_cast<int>(format));
        }

        *outData = (unsigned char*)data;
        *outDataLen = dataLen;
        return PixelFormat::I8;
    }

    return format;
}

Texture2D::PixelFormat Texture2D::convertAI88ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen)
{
    switch (format)
    {
    case PixelFormat::RGBA8888:
        *outDataLen = dataLen*2;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertAI88ToRGBA8888(data, dataLen, *outData);
        break;
    case PixelFormat::RGB888:
        *outDataLen = dataLen/2*3;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertAI88ToRGB888(data, dataLen, *outData);
        break;
    case PixelFormat::RGB565:
        *outDataLen = dataLen;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertAI88ToRGB565(data, dataLen, *outData);
        break;
    case PixelFormat::A8:
        *outDataLen = dataLen/2;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertAI88ToA8(data, dataLen, *outData);
        break;
    case PixelFormat::I8:
        *outDataLen = dataLen/2;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertAI88ToI8(data, dataLen, *outData);
        break;
    case PixelFormat::RGBA4444:
        *outDataLen = dataLen;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertAI88ToRGBA4444(data, dataLen, *outData);
        break;
    case PixelFormat::RGB5A1:
        *outDataLen = dataLen;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertAI88ToRGB5A1(data, dataLen, *outData);
        break;
    default:
        // unsupported conversion or don't need to convert
        if (format != PixelFormat::AUTO && format != PixelFormat::AI88)
        {
            CCLOG("Can not convert image format PixelFormat::AI88 to format ID:%d, we will use it's origin format PixelFormat::AI88", static_cast<int>(format));
        }

        *outData = (unsigned char*)data;
        *outDataLen = dataLen;
        return PixelFormat::AI88;
        break;
    }

    return format;
}

Texture2D::PixelFormat Texture2D::convertRGB888ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen)
{
    switch (format)
    {
    case PixelFormat::RGBA8888:
        *outDataLen = dataLen/3*4;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertRGB888ToRGBA8888(data, dataLen, *outData);
        break;
    case PixelFormat::RGB565:
        *outDataLen = dataLen/3*2;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertRGB888ToRGB565(data, dataLen, *outData);
        break;
    case PixelFormat::A8:
        *outDataLen = dataLen/3;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertRGB888ToA8(data, dataLen, *outData);
        break;
    case PixelFormat::I8:
        *outDataLen = dataLen/3;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertRGB888ToI8(data, dataLen, *outData);
        break;
    case PixelFormat::AI88:
        *outDataLen = dataLen/3*2;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertRGB888ToAI88(data, dataLen, *outData);
        break;
    case PixelFormat::RGBA4444:
        *outDataLen = dataLen/3*2;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertRGB888ToRGBA4444(data, dataLen, *outData);
        break;
    case PixelFormat::RGB5A1:
        *outDataLen = dataLen;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertRGB888ToRGB5A1(data, dataLen, *outData);
        break;
    default:
        // unsupported conversion or don't need to convert
        if (format != PixelFormat::AUTO && format != PixelFormat::RGB888)
        {
            CCLOG("Can not convert image format PixelFormat::RGB888 to format ID:%d, we will use it's origin format PixelFormat::RGB888", static_cast<int>(format));
        }

        *outData = (unsigned char*)data;
        *outDataLen = dataLen;
        return PixelFormat::RGB888;
    }
    return format;
}

Texture2D::PixelFormat Texture2D::convertRGBA8888ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen)
{

    switch (format)
    {
    case PixelFormat::RGB888:
        *outDataLen = dataLen/4*3;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertRGBA8888ToRGB888(data, dataLen, *outData);
        break;
    case PixelFormat::RGB565:
        *outDataLen = dataLen/2;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertRGBA8888ToRGB565(data, dataLen, *outData);
        break;
    case PixelFormat::A8:
        *outDataLen = dataLen/4;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertRGBA8888ToA8(data, dataLen, *outData);
        break;
    case PixelFormat::I8:
        *outDataLen = dataLen/4;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertRGBA8888ToI8(data, dataLen, *outData);
        break;
    case PixelFormat::AI88:
        *outDataLen = dataLen/2;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertRGBA8888ToAI88(data, dataLen, *outData);
        break;
    case PixelFormat::RGBA4444:
        *outDataLen = dataLen/2;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertRGBA8888ToRGBA4444(data, dataLen, *outData);
        break;
    case PixelFormat::RGB5A1:
        *outDataLen = dataLen/2;
        *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
        convertRGBA8888ToRGB5A1(data, dataLen, *outData);
        break;
    default:
        // unsupported conversion or don't need to convert
        if (format != PixelFormat::AUTO && format != PixelFormat::RGBA8888)
        {
            CCLOG("Can not convert image format PixelFormat::RGBA8888 to format ID:%d, we will use it's origin format PixelFormat::RGBA8888", static_cast<int>(format));
        }

        *outData = (unsigned char*)data;
        *outDataLen = dataLen;
        return PixelFormat::RGBA8888;
    }

    return format;
}

/*
convert map:
1.PixelFormat::RGBA8888
2.PixelFormat::RGB888
3.PixelFormat::RGB565
4.PixelFormat::A8
5.PixelFormat::I8
6.PixelFormat::AI88
7.PixelFormat::RGBA4444
8.PixelFormat::RGB5A1

gray(5) -> 1235678
gray alpha(6) -> 12345678
rgb(2) -> 1235678
rgba(1) -> 12345678

*/
Texture2D::PixelFormat Texture2D::convertDataToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat originFormat, PixelFormat format, unsigned char** outData, ssize_t* outDataLen)
{
    // don't need to convert
    if (format == originFormat || format == PixelFormat::AUTO)
    {
        *outData = (unsigned char*)data;
        *outDataLen = dataLen;
        return originFormat;
    }
    
    switch (originFormat)
    {
    case PixelFormat::I8:
        return convertI8ToFormat(data, dataLen, format, outData, outDataLen);
    case PixelFormat::AI88:
        return convertAI88ToFormat(data, dataLen, format, outData, outDataLen);
    case PixelFormat::RGB888:
        return convertRGB888ToFormat(data, dataLen, format, outData, outDataLen);
    case PixelFormat::RGBA8888:
        return convertRGBA8888ToFormat(data, dataLen, format, outData, outDataLen);
    default:
        CCLOG("unsupported conversion from format %d to format %d", static_cast<int>(originFormat), static_cast<int>(format));
        *outData = (unsigned char*)data;
        *outDataLen = dataLen;
        return originFormat;
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
    pixelFormat = convertDataToFormat(outData.getBytes(), imageWidth*imageHeight*4, PixelFormat::RGBA8888, pixelFormat, &outTempData, &outTempDataLen);

    ret = initWithData(outTempData, outTempDataLen, pixelFormat, imageWidth, imageHeight, imageSize);

    if (outTempData != nullptr && outTempData != outData.getBytes())
    {
        free(outTempData);
    }
    _hasPremultipliedAlpha = hasPremultipliedAlpha;

    return ret;
}


// implementation Texture2D (Drawing)

void Texture2D::drawAtPoint(const Vec2& point)
{
    GLfloat    coordinates[] = {
        0.0f,    _maxT,
        _maxS,_maxT,
        0.0f,    0.0f,
        _maxS,0.0f };

    GLfloat    width = (GLfloat)_pixelsWide * _maxS,
        height = (GLfloat)_pixelsHigh * _maxT;

    GLfloat        vertices[] = {    
        point.x,            point.y,
        width + point.x,    point.y,
        point.x,            height  + point.y,
        width + point.x,    height  + point.y };

    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD );
    _shaderProgram->use();
    _shaderProgram->setUniformsForBuiltins();

    GL::bindTexture2D( _name );


    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, coordinates);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Texture2D::drawInRect(const Rect& rect)
{
    GLfloat    coordinates[] = {    
        0.0f,    _maxT,
        _maxS,_maxT,
        0.0f,    0.0f,
        _maxS,0.0f };

    GLfloat    vertices[] = {    rect.origin.x,        rect.origin.y,                            /*0.0f,*/
        rect.origin.x + rect.size.width,        rect.origin.y,                            /*0.0f,*/
        rect.origin.x,                            rect.origin.y + rect.size.height,        /*0.0f,*/
        rect.origin.x + rect.size.width,        rect.origin.y + rect.size.height,        /*0.0f*/ };

    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD );
    _shaderProgram->use();
    _shaderProgram->setUniformsForBuiltins();

    GL::bindTexture2D( _name );

    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, coordinates);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Texture2D::PVRImagesHavePremultipliedAlpha(bool haveAlphaPremultiplied)
{
    Image::setPVRImagesHavePremultipliedAlpha(haveAlphaPremultiplied);
}


//
// Use to apply MIN/MAG filter
//
// implementation Texture2D (GLFilter)

void Texture2D::generateMipmap()
{
    CCASSERT(_pixelsWide == ccNextPOT(_pixelsWide) && _pixelsHigh == ccNextPOT(_pixelsHigh), "Mipmap texture only works in POT textures");
    GL::bindTexture2D( _name );
    glGenerateMipmap(GL_TEXTURE_2D);
    _hasMipmaps = true;
#if CC_ENABLE_CACHE_TEXTURE_DATA
    VolatileTextureMgr::setHasMipmaps(this, _hasMipmaps);
#endif
}

bool Texture2D::hasMipmaps() const
{
    return _hasMipmaps;
}

void Texture2D::setTexParameters(const TexParams &texParams)
{
    CCASSERT((_pixelsWide == ccNextPOT(_pixelsWide) || texParams.wrapS == GL_CLAMP_TO_EDGE) &&
        (_pixelsHigh == ccNextPOT(_pixelsHigh) || texParams.wrapT == GL_CLAMP_TO_EDGE),
        "GL_CLAMP_TO_EDGE should be used in NPOT dimensions");

    GL::bindTexture2D( _name );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texParams.minFilter );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texParams.magFilter );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texParams.wrapS );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texParams.wrapT );

#if CC_ENABLE_CACHE_TEXTURE_DATA
    VolatileTextureMgr::setTexParameters(this, texParams);
#endif
}

void Texture2D::setAliasTexParameters()
{
    if (! _antialiasEnabled)
    {
        return;
    }

    _antialiasEnabled = false;

    if (_name == 0)
    {
        return;
    }

    GL::bindTexture2D( _name );

    if( ! _hasMipmaps )
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    }
    else
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST );
    }

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
#if CC_ENABLE_CACHE_TEXTURE_DATA
    TexParams texParams = {(GLuint)(_hasMipmaps?GL_NEAREST_MIPMAP_NEAREST:GL_NEAREST),GL_NEAREST,GL_NONE,GL_NONE};
    VolatileTextureMgr::setTexParameters(this, texParams);
#endif
}

void Texture2D::setAntiAliasTexParameters()
{
    if ( _antialiasEnabled )
    {
        return;
    }

    _antialiasEnabled = true;

    if (_name == 0)
    {
        return;
    }

    GL::bindTexture2D( _name );

    if( ! _hasMipmaps )
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    }
    else
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    }

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
#if CC_ENABLE_CACHE_TEXTURE_DATA
    TexParams texParams = {(GLuint)(_hasMipmaps?GL_LINEAR_MIPMAP_NEAREST:GL_LINEAR),GL_LINEAR,GL_NONE,GL_NONE};
    VolatileTextureMgr::setTexParameters(this, texParams);
#endif
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
NS_CC_END
