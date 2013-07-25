/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008      Apple Inc. All Rights Reserved.

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

#include "CCTexture2D.h"
#include "ccConfig.h"
#include "ccMacros.h"
#include "CCConfiguration.h"
#include "platform/platform.h"
#include "platform/CCImage.h"
#include "CCGL.h"
#include "support/ccUtils.h"
#include "platform/CCPlatformMacros.h"
#include "textures/CCTextureETC.h"
#include "CCDirector.h"
#include "shaders/CCGLProgram.h"
#include "shaders/ccGLStateCache.h"
#include "shaders/CCShaderCache.h"

#if CC_ENABLE_CACHE_TEXTURE_DATA
    #include "CCTextureCache.h"
#endif

NS_CC_BEGIN

//CLASS IMPLEMENTATIONS:

// If the image has alpha, you can create RGBA8 (32-bit) or RGBA4 (16-bit) or RGB5A1 (16-bit)
// Default is: RGBA8888 (32-bit textures)
static Texture2DPixelFormat g_defaultAlphaPixelFormat = kTexture2DPixelFormat_Default;

// By default PVR images are treated as if they don't have the alpha channel premultiplied
static bool PVRHaveAlphaPremultiplied_ = false;


TexturePixelFormatInfo::TexturePixelFormatInfo(GLenum internalFormat, GLenum format, GLenum type, int bpp, bool compressed, bool alpha)
:internalFormat(internalFormat)
,format(format)
,type(type)
,bpp(bpp)
,compressed(compressed)
,alpha(alpha)
{}

//////////////////////////////////////////////////////////////////////////
//conventer function

// IIIIIIII -> RRRRRRRRGGGGGGGGGBBBBBBBB
void Texture2D::convertI8ToRGB888(const unsigned char* in, int len, unsigned char* out)
{
    for (int i=0; i < len; ++i)
    {
        *out++ = in[i];//R
        *out++ = in[i];//G
        *out++ = in[i];//B
    }
}

// IIIIIIIIAAAAAAAA -> RRRRRRRRGGGGGGGGBBBBBBBB
void Texture2D::convertAI88ToRGB888(const unsigned char* in, int len, unsigned char* out)
{
    for (int i = 0, l = len - 1; i < l; i += 2)
    {
        *out++ = in[i];//R
        *out++ = in[i];//G
        *out++ = in[i];//B
    }
}

// IIIIIIII -> RRRRRRRRGGGGGGGGGBBBBBBBBAAAAAAAA
void Texture2D::convertI8ToRGBA8888(const unsigned char* in, int len, unsigned char* out)
{
    for (int i = 0; i < len; ++i)
    {
        *out++ = in[i];//R
        *out++ = in[i];//G
        *out++ = in[i];//B
        *out++ = 0xFF;//A
    }
}

// IIIIIIIIAAAAAAAA -> RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA
void Texture2D::convertAI88ToRGBA8888(const unsigned char* in, int len, unsigned char* out)
{
    for (int i = 0, l = len - 1; i < l; i += 2)
    {
        *out++ = in[i];//R
        *out++ = in[i];//G
        *out++ = in[i];//B
        *out++ = in[i + 1];//A
    }
}

// IIIIIIII -> RRRRRGGGGGGBBBBB
void Texture2D::convertI8ToRGB565(const unsigned char* in, int len, unsigned char* out)
{
    unsigned short* out16 = (unsigned short*)out;
    for (int i = 0; i < len; ++i)
    {
        *out16++ = (in[i] & 0x00F8) << 8  //R
            | (in[i] & 0x00FC) << 3        //G
            | (in[i] & 0x00F8) >> 3;            //B
    }
}

// IIIIIIIIAAAAAAAA -> RRRRRGGGGGGBBBBB
void Texture2D::convertAI88ToRGB565(const unsigned char* in, int len, unsigned char* out)
{
    unsigned short* out16 = (unsigned short*)out;
    for (int i = 0, l = len - 1; i < l; i += 2)
    {
        *out16++ = (in[i] & 0x00F8) << 8  //R
            | (in[i] & 0x00FC) << 3        //G
            | (in[i] & 0x00F8) >> 3;            //B
    }
}

// IIIIIIII -> RRRRGGGGBBBBAAAA
void Texture2D::convertI8ToRGBA4444(const unsigned char* in, int len, unsigned char* out)
{
    unsigned short* out16 = (unsigned short*)out;
    for (int i = 0; i < len; ++i)
    {
        *out16++ = (in[i] & 0x00F0) << 8 | (in[i] & 0x00F0) << 4 | (in[i] & 0x00F0) | 0x000F; //RGBA
    }
}

// IIIIIIIIAAAAAAAA -> RRRRGGGGBBBBAAAA
void Texture2D::convertAI88ToRGBA4444(const unsigned char* in, int len, unsigned char* out)
{
    unsigned short* out16 = (unsigned short*)out;
    for (int i = 0, l = len - 1; i < l; i += 2)
    {
        *out16++ = (in[i] & 0x00F0) << 8 | (in[i] & 0x00F0) << 4 | (in[i] & 0x00F0) | (in[i+1] & 0x00F0) >> 4; //RGBA
    }
}

// IIIIIIII -> RRRRRGGGGGBBBBBA
void Texture2D::convertI8ToRGB5A1(const unsigned char* in, int len, unsigned char* out)
{
    unsigned short* out16 = (unsigned short*)out;
    for (int i = 0; i < len; ++i)
    {
        *out16++ = (in[i] & 0x00F8) << 8  //R
            | (in[i] & 0x00F8) << 3        //G
            | (in[i] & 0x00F8) >> 2        //B
            | 0x0001;                                      //A
    }
}

// IIIIIIIIAAAAAAAA -> RRRRRGGGGGBBBBBA
void Texture2D::convertAI88ToRGB5A1(const unsigned char* in, int len, unsigned char* out)
{
    unsigned short* out16 = (unsigned short*)out;
    for (int i = 0, l = len - 1; i < l; i += 2)
    {
        *out16++ = (in[i] & 0x00F8) << 8  //R
            | (in[i] & 0x00F8) << 3        //G
            | (in[i] & 0x00F8) >> 2        //B
            | (in[i + 1] & 0x0080) >> 7;         //A
    }
}

// IIIIIIII -> IIIIIIIIAAAAAAAA
void Texture2D::convertI8ToAI88(const unsigned char* in, int len, unsigned char* out)
{
    unsigned short* out16 = (unsigned short*)out;
    for (int i = 0; i < len; ++i)
    {
        *out16++ = (unsigned short)in[i] << 8  //R
            | 0xFF;                            //A
    }
}

// IIIIIIIIAAAAAAAA -> AAAAAAAA
void Texture2D::convertAI88ToA8(const unsigned char* in, int len, unsigned char* out)
{
    for (int i = 1; i < len; i += 2)
    {
        *out++ = in[i]; //A
    }
}

// IIIIIIIIAAAAAAAA -> IIIIIIII
void Texture2D::convertAI88ToI8(const unsigned char* in, int len, unsigned char* out)
{
    for (int i = 0, l = len - 1; i < l; i += 2)
    {
        *out++ = in[i]; //R
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA
void Texture2D::convertRGB888ToRGBA8888(const unsigned char* in, int len, unsigned char* out)
{
    for (int i = 0, l = len - 2; i < l; i += 3)
    {
        *out++ = in[i];
        *out++ = in[i + 1];
        *out++ = in[i + 2];
        *out++ = 0xFF;
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA -> RRRRRRRRGGGGGGGGBBBBBBBB
void Texture2D::convertRGBA8888ToRGB888(const unsigned char* in, int len, unsigned char* out)
{
    for (int i = 0, l = len - 3; i < l; i += 4)
    {
        *out++ = in[i];
        *out++ = in[i + 1];
        *out++ = in[i + 2];
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> RRRRRGGGGGGBBBBB
void Texture2D::convertRGB888ToRGB565(const unsigned char* in, int len, unsigned char* out)
{
    unsigned short* out16 = (unsigned short*)out;
    for (int i = 0, l = len - 2; i < l; i += 3)
    {
        *out16++ = (in[i] & 0x00F8) << 8  //R
            | (in[i + 1] & 0x00FC) << 3        //G
            | (in[i + 2] & 0x00F8) >> 3;            //B
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA -> RRRRRGGGGGGBBBBB
void Texture2D::convertRGBA8888ToRGB565(const unsigned char* in, int len, unsigned char* out)
{
    unsigned short* out16 = (unsigned short*)out;
    for (int i = 0, l = len - 3; i < l; i += 4)
    {
        *out16++ = (in[i] & 0x00F8) << 8  //R
            | (in[i + 1] & 0x00FC) << 3        //G
            | (in[i + 2] & 0x00F8) >> 3;            //B
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> IIIIIIII
void Texture2D::convertRGB888ToI8(const unsigned char* in, int len, unsigned char* out)
{
    for (int i = 0, l = len - 2; i < l; i += 3)
    {
        *out++ = (in[i] * 299 + in[i + 1] * 587 + in[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA -> IIIIIIII
void Texture2D::convertRGBA8888ToI8(const unsigned char* in, int len, unsigned char* out)
{
    for (int i = 0, l = len - 3; i < l; i += 4)
    {
        *out++ = (in[i] * 299 + in[i + 1] * 587 + in[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA -> AAAAAAAA
void Texture2D::convertRGBA8888ToA8(const unsigned char* in, int len, unsigned char* out)
{
    for (int i = 0, l = len -3; i < l; i += 4)
    {
        *out++ = in[i + 3];
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> IIIIIIIIAAAAAAAA
void Texture2D::convertRGB888ToAI88(const unsigned char* in, int len, unsigned char* out)
{
    for (int i = 0, l = len - 2; i < l; i += 3)
    {
        *out++ = (in[i] * 299 + in[i + 1] * 587 + in[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
        *out++ = 0xFF;
    }
}


// RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA -> IIIIIIIIAAAAAAAA
void Texture2D::convertRGBA8888ToAI88(const unsigned char* in, int len, unsigned char* out)
{
    for (int i = 0, l = len - 3; i < l; i += 4)
    {
        *out++ = (in[i] * 299 + in[i + 1] * 587 + in[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
        *out++ = in[i + 3];
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> RRRRGGGGBBBBAAAA
void Texture2D::convertRGB888ToRGBA4444(const unsigned char* in, int len, unsigned char* out)
{
    unsigned short* out16 = (unsigned short*)out;
    for (int i = 0, l = len - 2; i < l; i += 3)
    {
        *out16++ = ((in[i] & 0x00F0) << 8 | (in[i + 1] & 0x00F0) << 4 | (in[i + 2] & 0xF0) |  0x0F); //RGBA
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA -> RRRRGGGGBBBBAAAA
void Texture2D::convertRGBA8888ToRGBA4444(const unsigned char* in, int len, unsigned char* out)
{
    unsigned short* out16 = (unsigned short*)out;
    for (int i = 0, l = len - 3; i < l; i += 4)
    {
        *out16++ = (in[i] & 0x00F0) << 8 | (in[i + 1] & 0x00F0) << 4 | (in[i + 2] & 0xF0) |  (in[i + 3] & 0xF0) >> 4;  //RGBA
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> RRRRRGGGGGBBBBBA
void Texture2D::convertRGB888ToRGB5A1(const unsigned char* in, int len, unsigned char* out)
{
    unsigned short* out16 = (unsigned short*)out;
    for (int i = 0, l = len - 2; i < l; i += 3)
    {
        *out16++ = (in[i] & 0x00F8) << 8  //R
            | (in[i + 1] & 0x00F8) << 3        //G
            | (in[i + 2] & 0x00F8) >> 2        //B
            |  0x01;         //A
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> RRRRRGGGGGBBBBBA
void Texture2D::convertRGBA8888ToRGB5A1(const unsigned char* in, int len, unsigned char* out)
{
    unsigned short* out16 = (unsigned short*)out;
    for (int i = 0, l = len - 2; i < l; i += 4)
    {
        *out16++ = (in[i] & 0x00F8) << 8  //R
            | (in[i + 1] & 0x00F8) << 3        //G
            | (in[i + 2] & 0x00F8) >> 2        //B
            |  (in[i + 3] & 0x0080) >> 7;         //A
    }
}
// conventer function end
//////////////////////////////////////////////////////////////////////////

Texture2D::Texture2D()
: _PVRHaveAlphaPremultiplied(true)
, _pixelsWide(0)
, _pixelsHigh(0)
, _pixelFormat(kTexture2DPixelFormat_None)
, _name(0)
, _maxS(0.0)
, _maxT(0.0)
, _hasPremultipliedAlpha(false)
, _hasMipmaps(false)
, _shaderProgram(NULL)
{
}

Texture2D::~Texture2D()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    VolatileTexture::removeTexture(this);
#endif

    CCLOGINFO("cocos2d: deallocing Texture2D %u.", _name);
    CC_SAFE_RELEASE(_shaderProgram);

    if(_name)
    {
        ccGLDeleteTexture(_name);
    }
}

Texture2DPixelFormat Texture2D::getPixelFormat() const
{
    return _pixelFormat;
}

unsigned int Texture2D::getPixelsWide() const
{
    return _pixelsWide;
}

unsigned int Texture2D::getPixelsHigh() const
{
    return _pixelsHigh;
}

GLuint Texture2D::getName() const
{
    return _name;
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

GLfloat Texture2D::getMaxS()
{
    return _maxS;
}

void Texture2D::setMaxS(GLfloat maxS)
{
    _maxS = maxS;
}

GLfloat Texture2D::getMaxT()
{
    return _maxT;
}

void Texture2D::setMaxT(GLfloat maxT)
{
    _maxT = maxT;
}

GLProgram* Texture2D::getShaderProgram(void)
{
    return _shaderProgram;
}

void Texture2D::setShaderProgram(GLProgram* pShaderProgram)
{
    CC_SAFE_RETAIN(pShaderProgram);
    CC_SAFE_RELEASE(_shaderProgram);
    _shaderProgram = pShaderProgram;
}

void Texture2D::releaseData(void *data)
{
    free(data);
}

void* Texture2D::keepData(void *data, unsigned int length)
{
    CC_UNUSED_PARAM(length);
    //The texture data mustn't be saved because it isn't a mutable texture.
    return data;
}

bool Texture2D::hasPremultipliedAlpha() const
{
    return _hasPremultipliedAlpha;
}

bool Texture2D::initWithData(const void *data, int dataLen, Texture2DPixelFormat pixelFormat, unsigned int pixelsWide, unsigned int pixelsHigh, const Size& contentSize)
{
    //if data has no mipmaps, we will consider it has only one mipmap
    MipmapInfo mipmap;
    mipmap.address = (unsigned char*)data;
    mipmap.len = dataLen;
    return initWithMipmaps(&mipmap, 1, pixelFormat, pixelsWide, pixelsHigh);

    //update information
    _contentSize = contentSize;
    _maxS = contentSize.width / (float)(pixelsWide);
    _maxT = contentSize.height / (float)(pixelsHigh);

}

bool Texture2D::initWithMipmaps(MipmapInfo* mipmaps, int mipmapsNum, Texture2DPixelFormat pixelFormat, unsigned int pixelsWide, unsigned int pixelsHigh)
{
    //the pixelFormat must be a certain value 
    CCAssert(pixelFormat != kTexture2DPixelFormat_None && pixelFormat != kTexture2DPixelFormat_Automatic, "the \"pixelFormat\" param must be a certain value!");

    if (mipmapsNum <= 0)
    {
        CCLOG("cocos2d: WARNING: mipmap number is less than 1");
        return false;
    }
    

    if(g_texturePixelFormatInfoTables.find(pixelFormat) == g_texturePixelFormatInfoTables.end())
    {
        CCLOG("cocos2d: WARNING: unsupported pixelformat: %lx", (unsigned long)pixelFormat );
        return false;
    }

    const TexturePixelFormatInfo& info = g_texturePixelFormatInfoTables.at(pixelFormat);

    if (info.compressed && !Configuration::getInstance()->supportsPVRTC())
    {
        CCLOG("cocos2d: WARNING: PVRTC images are not supported");
        return false;
    }

    //Set the row align only when mipmapsNum == 1
    if (mipmapsNum == 1)
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
    


    glGenTextures(1, &_name);
    ccGLBindTexture2D(_name);

    if (mipmapsNum == 1)
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    }else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    }
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    CHECK_GL_ERROR_DEBUG(); // clean possible GL error
    
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
            CCLog("cocos2d: Texture2D. WARNING. Mipmap level %u is not squared. Texture won't render correctly. width=%u != height=%u", i, width, height);
        }

        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            CCLog("cocos2d: Texture2D: Error uploading compressed texture level: %u . glError: 0x%04X", i, err);
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

    setShaderProgram(ShaderCache::getInstance()->programForKey(kShader_PositionTexture));

    return true;
}


const char* Texture2D::description(void) const
{
    return String::createWithFormat("<Texture2D | Name = %u | Dimensions = %u x %u | Coordinates = (%.2f, %.2f)>", _name, _pixelsWide, _pixelsHigh, _maxS, _maxT)->getCString();
}

// implementation Texture2D (Image)
bool Texture2D::initWithImage(Image *uiImage)
{
    return initWithImage(uiImage, kTexture2DPixelFormat_None);
}

bool Texture2D::initWithImage(Image *uiImage, Texture2DPixelFormat format)
{
    if (uiImage == NULL)
    {
        CCLOG("cocos2d: Texture2D. Can't create Texture. UIImage is nil");
        return false;
    }

    int imageWidth = uiImage->getWidth();
    int imageHeight = uiImage->getHeight();

    Configuration *conf = Configuration::getInstance();

    int maxTextureSize = conf->getMaxTextureSize();
    if (imageWidth > maxTextureSize || imageHeight > maxTextureSize) 
    {
        CCLOG("cocos2d: WARNING: Image (%u x %u) is bigger than the supported %u x %u", imageWidth, imageHeight, maxTextureSize, maxTextureSize);
        return false;
    }


    unsigned char*            tempData = uiImage->getData();
    Size                      imageSize = Size((float)imageWidth, (float)imageHeight);
    Texture2DPixelFormat      pixelFormat;
    Texture2DPixelFormat      renderFormat = uiImage->getRenderFormat();
    size_t	                  tempDataLen = uiImage->getDataLen();


    if (uiImage->getNumberOfMipmaps() > 1)
    {
        if (format != kTexture2DPixelFormat_None)
        {
            CCLog("cocos2d: WARNING: This image has more than 1 mipmaps and we will not convert the data format");
        }

        initWithMipmaps(uiImage->getMipmaps(), uiImage->getNumberOfMipmaps(), uiImage->getRenderFormat(), imageWidth, imageHeight);
        return true;
    }
    else if (uiImage->isCompressed())
    {
        if (format != kTexture2DPixelFormat_None)
        {
            CCLog("cocos2d: WARNING: This image is compressed and we cann't convert it for now");
        }

        initWithData(tempData, tempDataLen, uiImage->getRenderFormat(), imageWidth, imageHeight, imageSize);
        return true;
    }
    else
    {
        // compute pixel format
        if (format != kTexture2DPixelFormat_None)
        {
            pixelFormat = format;
        }else
        {
            pixelFormat = g_defaultAlphaPixelFormat;
        }

        unsigned char* outTempData = NULL;
        int outTempDataLen = 0;

        pixelFormat = convertDataToFormat(tempData, tempDataLen, renderFormat, pixelFormat, &outTempData, &outTempDataLen);

        initWithData(outTempData, outTempDataLen, pixelFormat, imageWidth, imageHeight, imageSize);


        if (outTempData != NULL && outTempData != tempData)
        {

            delete [] outTempData;
        }

        _hasPremultipliedAlpha = uiImage->isPremultipliedAlpha();
        return true;
    }
}

Texture2DPixelFormat Texture2D::convertI8ToFormat(const unsigned char* data, int dataLen, Texture2DPixelFormat format, unsigned char** outData, int* outDataLen)
{
    switch (format)
    {
    case kTexture2DPixelFormat_RGBA8888:
        *outDataLen = dataLen*4;
        *outData = new unsigned char[*outDataLen];
        convertI8ToRGBA8888(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_RGB888:
        *outDataLen = dataLen*3;
        *outData = new unsigned char[*outDataLen];
        convertI8ToRGB888(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_RGB565:
        *outDataLen = dataLen*2;
        *outData = new unsigned char[*outDataLen];
        convertI8ToRGB565(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_AI88:
        *outDataLen = dataLen*2;
        *outData = new unsigned char[*outDataLen];
        convertI8ToAI88(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_RGBA4444:
        *outDataLen = dataLen*2;
        *outData = new unsigned char[*outDataLen];
        convertI8ToRGBA4444(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_RGB5A1:
        *outDataLen = dataLen*2;
        *outData = new unsigned char[*outDataLen];
        convertAI88ToRGB5A1(data, dataLen, *outData);
        break;
    default:
        // unsupport convertion or don't need to convert
        if (format != kTexture2DPixelFormat_Automatic && format != kTexture2DPixelFormat_I8)
        {
            CCLOG("Can not convert image format kTexture2DPixelFormat_I8 to format ID:%d, we will use it's origin format kTexture2DPixelFormat_I8", format);
        }

        *outData = (unsigned char*)data;
        *outDataLen = dataLen;
        return kTexture2DPixelFormat_I8;
    }

    return format;
}

Texture2DPixelFormat Texture2D::convertAI88ToFormat(const unsigned char* data, int dataLen, Texture2DPixelFormat format, unsigned char** outData, int* outDataLen)
{
    switch (format)
    {
    case kTexture2DPixelFormat_RGBA8888:
        *outDataLen = dataLen*2;
        *outData = new unsigned char[*outDataLen];
        convertAI88ToRGBA8888(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_RGB888:
        *outDataLen = dataLen/2*3;
        *outData = new unsigned char[*outDataLen];
        convertAI88ToRGB888(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_RGB565:
        *outDataLen = dataLen;
        *outData = new unsigned char[*outDataLen];
        convertAI88ToRGB565(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_A8:
        *outDataLen = dataLen/2;
        *outData = new unsigned char[*outDataLen];
        convertAI88ToA8(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_I8:
        *outDataLen = dataLen/2;
        *outData = new unsigned char[*outDataLen];
        convertAI88ToI8(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_RGBA4444:
        *outDataLen = dataLen;
        *outData = new unsigned char[*outDataLen];
        convertAI88ToRGBA4444(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_RGB5A1:
        *outDataLen = dataLen;
        *outData = new unsigned char[*outDataLen];
        convertAI88ToRGB5A1(data, dataLen, *outData);
        break;
    default:
        // unsupport convertion or don't need to convert
        if (format != kTexture2DPixelFormat_Automatic && format != kTexture2DPixelFormat_AI88)
        {
            CCLOG("Can not convert image format kTexture2DPixelFormat_AI88 to format ID:%d, we will use it's origin format kTexture2DPixelFormat_AI88", format);
        }

        *outData = (unsigned char*)data;
        *outDataLen = dataLen;
        return kTexture2DPixelFormat_AI88;
        break;
    }

    return format;
}

Texture2DPixelFormat Texture2D::convertRGB888ToFormat(const unsigned char* data, int dataLen, Texture2DPixelFormat format, unsigned char** outData, int* outDataLen)
{
    switch (format)
    {
    case kTexture2DPixelFormat_RGBA8888:
        *outDataLen = dataLen/3*4;
        *outData = new unsigned char[*outDataLen];
        convertRGB888ToRGBA8888(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_RGB565:
        *outDataLen = dataLen/3*2;
        *outData = new unsigned char[*outDataLen];
        convertRGB888ToRGB565(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_I8:
        *outDataLen = dataLen/3;
        *outData = new unsigned char[*outDataLen];
        convertRGB888ToI8(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_AI88:
        *outDataLen = dataLen/3*2;
        *outData = new unsigned char[*outDataLen];
        convertRGB888ToAI88(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_RGBA4444:
        *outDataLen = dataLen/3*2;
        *outData = new unsigned char[*outDataLen];
        convertRGB888ToRGBA4444(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_RGB5A1:
        *outDataLen = dataLen;
        *outData = new unsigned char[*outDataLen];
        convertRGB888ToRGB5A1(data, dataLen, *outData);
        break;
    default:
        // unsupport convertion or don't need to convert
        if (format != kTexture2DPixelFormat_Automatic && format != kTexture2DPixelFormat_RGB888)
        {
            CCLOG("Can not convert image format kTexture2DPixelFormat_RGB888 to format ID:%d, we will use it's origin format kTexture2DPixelFormat_RGB888", format);
        }

        *outData = (unsigned char*)data;
        *outDataLen = dataLen;
        return kTexture2DPixelFormat_RGB888;
    }

    return format;
}

Texture2DPixelFormat Texture2D::convertRGBA8888ToFormat(const unsigned char* data, int dataLen, Texture2DPixelFormat format, unsigned char** outData, int* outDataLen)
{

    switch (format)
    {
    case kTexture2DPixelFormat_RGB888:
        *outDataLen = dataLen/4*3;
        *outData = new unsigned char[*outDataLen];
        convertRGBA8888ToRGB888(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_RGB565:
        *outDataLen = dataLen/2;
        *outData = new unsigned char[*outDataLen];
        convertRGBA8888ToRGB565(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_A8:
        *outDataLen = dataLen/4;
        *outData = new unsigned char[*outDataLen];
        convertRGBA8888ToA8(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_I8:
        *outDataLen = dataLen/4;
        *outData = new unsigned char[*outDataLen];
        convertRGBA8888ToI8(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_AI88:
        *outDataLen = dataLen/2;
        *outData = new unsigned char[*outDataLen];
        convertRGBA8888ToAI88(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_RGBA4444:
        *outDataLen = dataLen/2;
        *outData = new unsigned char[*outDataLen];
        convertRGBA8888ToRGBA4444(data, dataLen, *outData);
        break;
    case kTexture2DPixelFormat_RGB5A1:
        *outDataLen = dataLen/2;
        *outData = new unsigned char[*outDataLen];
        convertRGBA8888ToRGB5A1(data, dataLen, *outData);
        break;
    default:
        // unsupport convertion or don't need to convert
        if (format != kTexture2DPixelFormat_Automatic && format != kTexture2DPixelFormat_RGBA8888)
        {
            CCLOG("Can not convert image format kTexture2DPixelFormat_RGBA8888 to format ID:%d, we will use it's origin format kTexture2DPixelFormat_RGBA8888", format);
        }

        *outData = (unsigned char*)data;
        *outDataLen = dataLen;
        return kTexture2DPixelFormat_RGBA8888;
    }

    return format;
}

/*
convert map:
1.kTexture2DPixelFormat_RGBA8888
2.kTexture2DPixelFormat_RGB888
3.kTexture2DPixelFormat_RGB565
4.kTexture2DPixelFormat_A8
5.kTexture2DPixelFormat_I8
6.kTexture2DPixelFormat_AI88
7.kTexture2DPixelFormat_RGBA4444
8.kTexture2DPixelFormat_RGB5A1

gray(5) -> 1235678
gray alpha(6) -> 12345678
rgb(2) -> 1235678
rgba(1) -> 12345678

*/
Texture2DPixelFormat Texture2D::convertDataToFormat(const unsigned char* data, int dataLen, Texture2DPixelFormat originFormat, Texture2DPixelFormat format, unsigned char** outData, int* outDataLen)
{
    switch (originFormat)
    {
    case kTexture2DPixelFormat_I8:
        return convertI8ToFormat(data, dataLen, format, outData, outDataLen);
    case kTexture2DPixelFormat_AI88:
        return convertAI88ToFormat(data, dataLen, format, outData, outDataLen);
    case kTexture2DPixelFormat_RGB888:
        return convertRGB888ToFormat(data, dataLen, format, outData, outDataLen);
    case kTexture2DPixelFormat_RGBA8888:
        return convertRGBA8888ToFormat(data, dataLen, format, outData, outDataLen);
    default:
        CCLOG("unsupport convert for format %d to format %d", originFormat, format);
        *outData = (unsigned char*)data;
        *outDataLen = dataLen;
        return originFormat;
    }
}

// implementation Texture2D (Text)
bool Texture2D::initWithString(const char *text, const char *fontName, float fontSize)
{
    return initWithString(text,  fontName, fontSize, Size(0,0), kTextAlignmentCenter, kVerticalTextAlignmentTop);
}

bool Texture2D::initWithString(const char *text, const char *fontName, float fontSize, const Size& dimensions, TextAlignment hAlignment, VerticalTextAlignment vAlignment)
{
    FontDefinition tempDef;
    
    tempDef._shadow._shadowEnabled = false;
    tempDef._stroke._strokeEnabled = false;
   
    
    tempDef._fontName      = std::string(fontName);
    tempDef._fontSize      = fontSize;
    tempDef._dimensions    = dimensions;
    tempDef._alignment     = hAlignment;
    tempDef._vertAlignment = vAlignment;
    tempDef._fontFillColor = Color3B::WHITE;

    return initWithString(text, tempDef);
}

bool Texture2D::initWithString(const char *text, const FontDefinition& textDefinition)
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    // cache the texture data
    VolatileTexture::addStringTexture(this, text, textDefinition);
#endif

    bool bRet = false;
    Image::TextAlign eAlign;
    
    if (kVerticalTextAlignmentTop == textDefinition._vertAlignment)
    {
        eAlign = (kTextAlignmentCenter == textDefinition._alignment) ? Image::kAlignTop
        : (kTextAlignmentLeft == textDefinition._alignment) ? Image::kAlignTopLeft : Image::kAlignTopRight;
    }
    else if (kVerticalTextAlignmentCenter == textDefinition._vertAlignment)
    {
        eAlign = (kTextAlignmentCenter == textDefinition._alignment) ? Image::kAlignCenter
        : (kTextAlignmentLeft == textDefinition._alignment) ? Image::kAlignLeft : Image::kAlignRight;
    }
    else if (kVerticalTextAlignmentBottom == textDefinition._vertAlignment)
    {
        eAlign = (kTextAlignmentCenter == textDefinition._alignment) ? Image::kAlignBottom
        : (kTextAlignmentLeft == textDefinition._alignment) ? Image::kAlignBottomLeft : Image::kAlignBottomRight;
    }
    else
    {
        CCAssert(false, "Not supported alignment format!");
        return false;
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

    // handle shadow parameters
    bool  shadowEnabled = false;
    float shadowDX      = 0.0f;
    float shadowDY      = 0.0f;
    float shadowBlur    = 0.0f;
    float shadowOpacity = 0.0f;
    
    if ( textDefinition._shadow._shadowEnabled )
    {
        shadowEnabled =  true;
        shadowDX      = textDefinition._shadow._shadowOffset.width;
        shadowDY      = textDefinition._shadow._shadowOffset.height;
        shadowBlur    = textDefinition._shadow._shadowBlur;
        shadowOpacity = textDefinition._shadow._shadowOpacity;
    }
    
    // handle stroke parameters
    bool strokeEnabled = false;
    float strokeColorR = 0.0f;
    float strokeColorG = 0.0f;
    float strokeColorB = 0.0f;
    float strokeSize   = 0.0f;
    
    if ( textDefinition._stroke._strokeEnabled )
    {
        strokeEnabled = true;
        strokeColorR = textDefinition._stroke._strokeColor.r / 255.0f;
        strokeColorG = textDefinition._stroke._strokeColor.g / 255.0f;
        strokeColorB = textDefinition._stroke._strokeColor.b / 255.0f;
        strokeSize   = textDefinition._stroke._strokeSize;
    }
    
    Image* pImage = new Image();
    do
    {
        CC_BREAK_IF(NULL == pImage);
        
        bRet = pImage->initWithStringShadowStroke(text,
                                                  (int)textDefinition._dimensions.width,
                                                  (int)textDefinition._dimensions.height,
                                                  eAlign,
                                                  textDefinition._fontName.c_str(),
                                                  textDefinition._fontSize,
                                                  textDefinition._fontFillColor.r / 255.0f,
                                                  textDefinition._fontFillColor.g / 255.0f,
                                                  textDefinition._fontFillColor.b / 255.0f,
                                                  shadowEnabled,
                                                  shadowDX,
                                                  shadowDY,
                                                  shadowOpacity,
                                                  shadowBlur,
                                                  strokeEnabled,
                                                  strokeColorR,
                                                  strokeColorG,
                                                  strokeColorB,
                                                  strokeSize);
        
        
        CC_BREAK_IF(!bRet);
        bRet = initWithImage(pImage);
        
    } while (0);
    
    CC_SAFE_RELEASE(pImage);
    
    return bRet;

#else
    bool requestUnsupported = textDefinition._shadow._shadowEnabled || textDefinition._stroke._strokeEnabled;

    CCAssert(requestUnsupported == false, "Currently shadow and stroke only supported on iOS and Android!");

    Image* pImage = new Image();
    do
    {
        CC_BREAK_IF(NULL == pImage);
        bRet = pImage->initWithString(text, (int)textDefinition._dimensions.width, (int)textDefinition._dimensions.height, eAlign, textDefinition._fontName.c_str(), (int)textDefinition._fontSize);
        CC_BREAK_IF(!bRet);
        bRet = initWithImage(pImage);
    } while (0);
    
    CC_SAFE_RELEASE(pImage);

    return bRet;    
#endif
}


// implementation Texture2D (Drawing)

void Texture2D::drawAtPoint(const Point& point)
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

    ccGLEnableVertexAttribs( kVertexAttribFlag_Position | kVertexAttribFlag_TexCoords );
    _shaderProgram->use();
    _shaderProgram->setUniformsForBuiltins();

    ccGLBindTexture2D( _name );


#ifdef EMSCRIPTEN
    setGLBufferData(vertices, 8 * sizeof(GLfloat), 0);
    glVertexAttribPointer(kVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, 0);

    setGLBufferData(coordinates, 8 * sizeof(GLfloat), 1);
    glVertexAttribPointer(kVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, 0);
#else
    glVertexAttribPointer(kVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(kVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, coordinates);
#endif // EMSCRIPTEN

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

    ccGLEnableVertexAttribs( kVertexAttribFlag_Position | kVertexAttribFlag_TexCoords );
    _shaderProgram->use();
    _shaderProgram->setUniformsForBuiltins();

    ccGLBindTexture2D( _name );

#ifdef EMSCRIPTEN
    setGLBufferData(vertices, 8 * sizeof(GLfloat), 0);
    glVertexAttribPointer(kVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, 0);

    setGLBufferData(coordinates, 8 * sizeof(GLfloat), 1);
    glVertexAttribPointer(kVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, 0);
#else
    glVertexAttribPointer(kVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(kVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, coordinates);
#endif // EMSCRIPTEN
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

bool Texture2D::initWithETCFile(const char* file)
{
    bool bRet = false;
    // nothing to do with Object::init
    
    TextureETC *etc = new TextureETC;
    bRet = etc->initWithFile(file);
    
    if (bRet)
    {
        _name = etc->getName();
        _maxS = 1.0f;
        _maxT = 1.0f;
        _pixelsWide = etc->getWidth();
        _pixelsHigh = etc->getHeight();
        _contentSize = Size((float)_pixelsWide, (float)_pixelsHigh);
        _hasPremultipliedAlpha = true;
        
        etc->release();
    }
    else
    {
        CCLOG("cocos2d: Couldn't load ETC image %s", file);
    }
    
    return bRet;
}

void Texture2D::PVRImagesHavePremultipliedAlpha(bool haveAlphaPremultiplied)
{
    PVRHaveAlphaPremultiplied_ = haveAlphaPremultiplied;
}

    
//
// Use to apply MIN/MAG filter
//
// implementation Texture2D (GLFilter)

void Texture2D::generateMipmap()
{
    CCAssert( _pixelsWide == ccNextPOT(_pixelsWide) && _pixelsHigh == ccNextPOT(_pixelsHigh), "Mipmap texture only works in POT textures");
    ccGLBindTexture2D( _name );
    glGenerateMipmap(GL_TEXTURE_2D);
    _hasMipmaps = true;
}

bool Texture2D::hasMipmaps() const
{
    return _hasMipmaps;
}

void Texture2D::setTexParameters(const ccTexParams &texParams)
{
    CCAssert( (_pixelsWide == ccNextPOT(_pixelsWide) || texParams.wrapS == GL_CLAMP_TO_EDGE) &&
        (_pixelsHigh == ccNextPOT(_pixelsHigh) || texParams.wrapT == GL_CLAMP_TO_EDGE),
        "GL_CLAMP_TO_EDGE should be used in NPOT dimensions");

    ccGLBindTexture2D( _name );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texParams.minFilter );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texParams.magFilter );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texParams.wrapS );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texParams.wrapT );

#if CC_ENABLE_CACHE_TEXTURE_DATA
    VolatileTexture::setTexParameters(this, texParams);
#endif
}

void Texture2D::setAliasTexParameters()
{
    ccGLBindTexture2D( _name );

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
    ccTexParams texParams = {(GLuint)(_hasMipmaps?GL_NEAREST_MIPMAP_NEAREST:GL_NEAREST),GL_NEAREST,GL_NONE,GL_NONE};
    VolatileTexture::setTexParameters(this, texParams);
#endif
}

void Texture2D::setAntiAliasTexParameters()
{
    ccGLBindTexture2D( _name );

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
    ccTexParams texParams = {(GLuint)(_hasMipmaps?GL_LINEAR_MIPMAP_NEAREST:GL_LINEAR),GL_LINEAR,GL_NONE,GL_NONE};
    VolatileTexture::setTexParameters(this, texParams);
#endif
}

const char* Texture2D::stringForFormat() const
{
	switch (_pixelFormat) 
	{
		case kTexture2DPixelFormat_RGBA8888:
			return  "RGBA8888";

		case kTexture2DPixelFormat_RGB888:
			return  "RGB888";

		case kTexture2DPixelFormat_RGB565:
			return  "RGB565";

		case kTexture2DPixelFormat_RGBA4444:
			return  "RGBA4444";

		case kTexture2DPixelFormat_RGB5A1:
			return  "RGB5A1";

		case kTexture2DPixelFormat_AI88:
			return  "AI88";

		case kTexture2DPixelFormat_A8:
			return  "A8";

		case kTexture2DPixelFormat_I8:
			return  "I8";

		case kTexture2DPixelFormat_PVRTC4:
			return  "PVRTC4";

		case kTexture2DPixelFormat_PVRTC2:
			return  "PVRTC2";

		default:
			CCAssert(false , "unrecognized pixel format");
			CCLOG("stringForFormat: %ld, cannot give useful result", (long)_pixelFormat);
			break;
	}

	return  NULL;
}

//
// Texture options for images that contains alpha
//
// implementation Texture2D (PixelFormat)

void Texture2D::setDefaultAlphaPixelFormat(Texture2DPixelFormat format)
{
    g_defaultAlphaPixelFormat = format;
}

Texture2DPixelFormat Texture2D::defaultAlphaPixelFormat()
{
    return g_defaultAlphaPixelFormat;
}

unsigned int Texture2D::bitsPerPixelForFormat(Texture2DPixelFormat format) const
{
    if (format == kTexture2DPixelFormat_None)
    {
        return 0;
    }
    
	return g_texturePixelFormatInfoTables.at(format).bpp;
}

unsigned int Texture2D::bitsPerPixelForFormat() const
{
	return this->bitsPerPixelForFormat(_pixelFormat);
}


NS_CC_END
