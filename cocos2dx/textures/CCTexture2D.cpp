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
#include "platform/CCImage.h"
#include "CCGL.h"
#include "support/ccUtils.h"
#include "platform/CCPlatformMacros.h"
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
static Texture2D::PixelFormat g_defaultAlphaPixelFormat = Texture2D::PixelFormat::DEFAULT;

static bool _PVRHaveAlphaPremultiplied = false;

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
        *out16++ = 0xFF00 | in[i];       //AI
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
: _pixelFormat(Texture2D::PixelFormat::DEFAULT)
, _pixelsWide(0)
, _pixelsHigh(0)
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
        GL::deleteTexture(_name);
    }
}

Texture2D::PixelFormat Texture2D::getPixelFormat() const
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

GLProgram* Texture2D::getShaderProgram() const
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

bool Texture2D::initWithData(const void *data, int dataLen, Texture2D::PixelFormat pixelFormat, unsigned int pixelsWide, unsigned int pixelsHigh, const Size& contentSize)
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

bool Texture2D::initWithMipmaps(MipmapInfo* mipmaps, int mipmapsNum, PixelFormat pixelFormat, unsigned int pixelsWide, unsigned int pixelsHigh)
{
    //the pixelFormat must be a certain value 
    CCAssert(pixelFormat != PixelFormat::NONE && pixelFormat != PixelFormat::AUTO, "the \"pixelFormat\" param must be a certain value!");

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

    if (info.compressed && !Configuration::getInstance()->supportsPVRTC() && !Configuration::getInstance()->supportsETC())
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
    


    glGenTextures(1, &_name);
    GL::bindTexture2D(_name);

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
            CCLOG("cocos2d: Texture2D. WARNING. Mipmap level %u is not squared. Texture won't render correctly. width=%u != height=%u", i, width, height);
        }

        GLenum err = glGetError();
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

    setShaderProgram(ShaderCache::getInstance()->programForKey(GLProgram::SHADER_NAME_POSITION_TEXTURE));

    return true;
}


const char* Texture2D::description(void) const
{
    return String::createWithFormat("<Texture2D | Name = %u | Dimensions = %u x %u | Coordinates = (%.2f, %.2f)>", _name, _pixelsWide, _pixelsHigh, _maxS, _maxT)->getCString();
}

// implementation Texture2D (Image)
bool Texture2D::initWithImage(Image *image)
{
    return initWithImage(image, PixelFormat::NONE);
}

bool Texture2D::initWithImage(Image *image, PixelFormat format)
{
    if (image == NULL)
    {
        CCLOG("cocos2d: Texture2D. Can't create Texture. UIImage is nil");
        return false;
    }

    int imageWidth = image->getWidth();
    int imageHeight = image->getHeight();

    Configuration *conf = Configuration::getInstance();

    int maxTextureSize = conf->getMaxTextureSize();
    if (imageWidth > maxTextureSize || imageHeight > maxTextureSize) 
    {
        CCLOG("cocos2d: WARNING: Image (%u x %u) is bigger than the supported %u x %u", imageWidth, imageHeight, maxTextureSize, maxTextureSize);
        return false;
    }

    unsigned char*   tempData = image->getData();
    Size             imageSize = Size((float)imageWidth, (float)imageHeight);
    PixelFormat      pixelFormat = PixelFormat::NONE;
    PixelFormat      renderFormat = image->getRenderFormat();
    size_t	         tempDataLen = image->getDataLen();


    if (image->getNumberOfMipmaps() > 1)
    {
        if (format != PixelFormat::NONE)
        {
            CCLOG("cocos2d: WARNING: This image has more than 1 mipmaps and we will not convert the data format");
        }

        initWithMipmaps(image->getMipmaps(), image->getNumberOfMipmaps(), image->getRenderFormat(), imageWidth, imageHeight);
        return true;
    }
    else if (image->isCompressed())
    {
        if (format != PixelFormat::NONE)
        {
            CCLOG("cocos2d: WARNING: This image is compressed and we cann't convert it for now");
        }

        initWithData(tempData, tempDataLen, image->getRenderFormat(), imageWidth, imageHeight, imageSize);
        return true;
    }
    else
    {
        // compute pixel format
        if (format != PixelFormat::NONE)
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

        // set the premultiplied tag
        if (!image->hasPremultipliedAlpha())
        {
            if (image->getFileType() == Image::Format::PVR)
            {
                _hasPremultipliedAlpha = _PVRHaveAlphaPremultiplied;
            }else
            {
                CCLOG("wanning: We cann't find the data is premultiplied or not, we will assume it's false.");
                _hasPremultipliedAlpha = false;
            }
        }else
        {
            _hasPremultipliedAlpha = image->isPremultipliedAlpha();
        }
        return true;
    }
}

Texture2D::PixelFormat Texture2D::convertI8ToFormat(const unsigned char* data, int dataLen, PixelFormat format, unsigned char** outData, int* outDataLen)
{
    switch (format)
    {
    case PixelFormat::RGBA8888:
        *outDataLen = dataLen*4;
        *outData = new unsigned char[*outDataLen];
        convertI8ToRGBA8888(data, dataLen, *outData);
        break;
    case PixelFormat::RGB888:
        *outDataLen = dataLen*3;
        *outData = new unsigned char[*outDataLen];
        convertI8ToRGB888(data, dataLen, *outData);
        break;
    case PixelFormat::RGB565:
        *outDataLen = dataLen*2;
        *outData = new unsigned char[*outDataLen];
        convertI8ToRGB565(data, dataLen, *outData);
        break;
    case PixelFormat::AI88:
        *outDataLen = dataLen*2;
        *outData = new unsigned char[*outDataLen];
        convertI8ToAI88(data, dataLen, *outData);
        break;
    case PixelFormat::RGBA4444:
        *outDataLen = dataLen*2;
        *outData = new unsigned char[*outDataLen];
        convertI8ToRGBA4444(data, dataLen, *outData);
        break;
    case PixelFormat::RGB5A1:
        *outDataLen = dataLen*2;
        *outData = new unsigned char[*outDataLen];
        convertI8ToRGB5A1(data, dataLen, *outData);
        break;
    default:
        // unsupport convertion or don't need to convert
        if (format != PixelFormat::AUTO && format != PixelFormat::I8)
        {
            CCLOG("Can not convert image format PixelFormat::I8 to format ID:%d, we will use it's origin format PixelFormat::I8", format);
        }

        *outData = (unsigned char*)data;
        *outDataLen = dataLen;
        return PixelFormat::I8;
    }

    return format;
}

Texture2D::PixelFormat Texture2D::convertAI88ToFormat(const unsigned char* data, int dataLen, PixelFormat format, unsigned char** outData, int* outDataLen)
{
    switch (format)
    {
    case PixelFormat::RGBA8888:
        *outDataLen = dataLen*2;
        *outData = new unsigned char[*outDataLen];
        convertAI88ToRGBA8888(data, dataLen, *outData);
        break;
    case PixelFormat::RGB888:
        *outDataLen = dataLen/2*3;
        *outData = new unsigned char[*outDataLen];
        convertAI88ToRGB888(data, dataLen, *outData);
        break;
    case PixelFormat::RGB565:
        *outDataLen = dataLen;
        *outData = new unsigned char[*outDataLen];
        convertAI88ToRGB565(data, dataLen, *outData);
        break;
    case PixelFormat::A8:
        *outDataLen = dataLen/2;
        *outData = new unsigned char[*outDataLen];
        convertAI88ToA8(data, dataLen, *outData);
        break;
    case PixelFormat::I8:
        *outDataLen = dataLen/2;
        *outData = new unsigned char[*outDataLen];
        convertAI88ToI8(data, dataLen, *outData);
        break;
    case PixelFormat::RGBA4444:
        *outDataLen = dataLen;
        *outData = new unsigned char[*outDataLen];
        convertAI88ToRGBA4444(data, dataLen, *outData);
        break;
    case PixelFormat::RGB5A1:
        *outDataLen = dataLen;
        *outData = new unsigned char[*outDataLen];
        convertAI88ToRGB5A1(data, dataLen, *outData);
        break;
    default:
        // unsupport convertion or don't need to convert
        if (format != PixelFormat::AUTO && format != PixelFormat::AI88)
        {
            CCLOG("Can not convert image format PixelFormat::AI88 to format ID:%d, we will use it's origin format PixelFormat::AI88", format);
        }

        *outData = (unsigned char*)data;
        *outDataLen = dataLen;
        return PixelFormat::AI88;
        break;
    }

    return format;
}

Texture2D::PixelFormat Texture2D::convertRGB888ToFormat(const unsigned char* data, int dataLen, PixelFormat format, unsigned char** outData, int* outDataLen)
{
    switch (format)
    {
    case PixelFormat::RGBA8888:
        *outDataLen = dataLen/3*4;
        *outData = new unsigned char[*outDataLen];
        convertRGB888ToRGBA8888(data, dataLen, *outData);
        break;
    case PixelFormat::RGB565:
        *outDataLen = dataLen/3*2;
        *outData = new unsigned char[*outDataLen];
        convertRGB888ToRGB565(data, dataLen, *outData);
        break;
    case PixelFormat::I8:
        *outDataLen = dataLen/3;
        *outData = new unsigned char[*outDataLen];
        convertRGB888ToI8(data, dataLen, *outData);
        break;
    case PixelFormat::AI88:
        *outDataLen = dataLen/3*2;
        *outData = new unsigned char[*outDataLen];
        convertRGB888ToAI88(data, dataLen, *outData);
        break;
    case PixelFormat::RGBA4444:
        *outDataLen = dataLen/3*2;
        *outData = new unsigned char[*outDataLen];
        convertRGB888ToRGBA4444(data, dataLen, *outData);
        break;
    case PixelFormat::RGB5A1:
        *outDataLen = dataLen;
        *outData = new unsigned char[*outDataLen];
        convertRGB888ToRGB5A1(data, dataLen, *outData);
        break;
    default:
        // unsupport convertion or don't need to convert
        if (format != PixelFormat::AUTO && format != PixelFormat::RGB888)
        {
            CCLOG("Can not convert image format PixelFormat::RGB888 to format ID:%d, we will use it's origin format PixelFormat::RGB888", format);
        }

        *outData = (unsigned char*)data;
        *outDataLen = dataLen;
        return PixelFormat::RGB888;
    }
    return format;
}

Texture2D::PixelFormat Texture2D::convertRGBA8888ToFormat(const unsigned char* data, int dataLen, PixelFormat format, unsigned char** outData, int* outDataLen)
{

    switch (format)
    {
    case PixelFormat::RGB888:
        *outDataLen = dataLen/4*3;
        *outData = new unsigned char[*outDataLen];
        convertRGBA8888ToRGB888(data, dataLen, *outData);
        break;
    case PixelFormat::RGB565:
        *outDataLen = dataLen/2;
        *outData = new unsigned char[*outDataLen];
        convertRGBA8888ToRGB565(data, dataLen, *outData);
        break;
    case PixelFormat::A8:
        *outDataLen = dataLen/4;
        *outData = new unsigned char[*outDataLen];
        convertRGBA8888ToA8(data, dataLen, *outData);
        break;
    case PixelFormat::I8:
        *outDataLen = dataLen/4;
        *outData = new unsigned char[*outDataLen];
        convertRGBA8888ToI8(data, dataLen, *outData);
        break;
    case PixelFormat::AI88:
        *outDataLen = dataLen/2;
        *outData = new unsigned char[*outDataLen];
        convertRGBA8888ToAI88(data, dataLen, *outData);
        break;
    case PixelFormat::RGBA4444:
        *outDataLen = dataLen/2;
        *outData = new unsigned char[*outDataLen];
        convertRGBA8888ToRGBA4444(data, dataLen, *outData);
        break;
    case PixelFormat::RGB5A1:
        *outDataLen = dataLen/2;
        *outData = new unsigned char[*outDataLen];
        convertRGBA8888ToRGB5A1(data, dataLen, *outData);
        break;
    default:
        // unsupport convertion or don't need to convert
        if (format != PixelFormat::AUTO && format != PixelFormat::RGBA8888)
        {
            CCLOG("Can not convert image format PixelFormat::RGBA8888 to format ID:%d, we will use it's origin format PixelFormat::RGBA8888", format);
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
Texture2D::PixelFormat Texture2D::convertDataToFormat(const unsigned char* data, int dataLen, PixelFormat originFormat, PixelFormat format, unsigned char** outData, int* outDataLen)
{
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
        CCLOG("unsupport convert for format %d to format %d", originFormat, format);
        *outData = (unsigned char*)data;
        *outDataLen = dataLen;
        return originFormat;
    }
}

// implementation Texture2D (Text)
bool Texture2D::initWithString(const char *text, const char *fontName, float fontSize, const Size& dimensions/* = Size(0, 0)*/, TextHAlignment hAlignment/* =  TextHAlignment::CENTER */, TextVAlignment vAlignment/* =  TextVAlignment::TOP */)
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
    
    if (TextVAlignment::TOP == textDefinition._vertAlignment)
    {
        eAlign = (TextHAlignment::CENTER == textDefinition._alignment) ? Image::TextAlign::TOP
        : (TextHAlignment::LEFT == textDefinition._alignment) ? Image::TextAlign::TOP_LEFT : Image::TextAlign::TOP_RIGHT;
    }
    else if (TextVAlignment::CENTER == textDefinition._vertAlignment)
    {
        eAlign = (TextHAlignment::CENTER == textDefinition._alignment) ? Image::TextAlign::CENTER
        : (TextHAlignment::LEFT == textDefinition._alignment) ? Image::TextAlign::LEFT : Image::TextAlign::RIGHT;
    }
    else if (TextVAlignment::BOTTOM == textDefinition._vertAlignment)
    {
        eAlign = (TextHAlignment::CENTER == textDefinition._alignment) ? Image::TextAlign::BOTTOM
        : (TextHAlignment::LEFT == textDefinition._alignment) ? Image::TextAlign::BOTTOM_LEFT : Image::TextAlign::BOTTOM_RIGHT;
    }
    else
    {
        CCASSERT(false, "Not supported alignment format!");
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

    CCASSERT(requestUnsupported == false, "Currently shadow and stroke only supported on iOS and Android!");

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

    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORDS );
    _shaderProgram->use();
    _shaderProgram->setUniformsForBuiltins();

    GL::bindTexture2D( _name );


#ifdef EMSCRIPTEN
    setGLBufferData(vertices, 8 * sizeof(GLfloat), 0);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);

    setGLBufferData(coordinates, 8 * sizeof(GLfloat), 1);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, 0, 0);
#else
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, 0, coordinates);
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

    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORDS );
    _shaderProgram->use();
    _shaderProgram->setUniformsForBuiltins();

    GL::bindTexture2D( _name );

#ifdef EMSCRIPTEN
    setGLBufferData(vertices, 8 * sizeof(GLfloat), 0);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);

    setGLBufferData(coordinates, 8 * sizeof(GLfloat), 1);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, 0, 0);
#else
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, 0, coordinates);
#endif // EMSCRIPTEN
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Texture2D::PVRImagesHavePremultipliedAlpha(bool haveAlphaPremultiplied)
{
    _PVRHaveAlphaPremultiplied = haveAlphaPremultiplied;
}

    
//
// Use to apply MIN/MAG filter
//
// implementation Texture2D (GLFilter)

void Texture2D::generateMipmap()
{
    CCASSERT( _pixelsWide == ccNextPOT(_pixelsWide) && _pixelsHigh == ccNextPOT(_pixelsHigh), "Mipmap texture only works in POT textures");
    GL::bindTexture2D( _name );
    glGenerateMipmap(GL_TEXTURE_2D);
    _hasMipmaps = true;
}

bool Texture2D::hasMipmaps() const
{
    return _hasMipmaps;
}

void Texture2D::setTexParameters(const ccTexParams &texParams)
{
    CCASSERT( (_pixelsWide == ccNextPOT(_pixelsWide) || texParams.wrapS == GL_CLAMP_TO_EDGE) &&
        (_pixelsHigh == ccNextPOT(_pixelsHigh) || texParams.wrapT == GL_CLAMP_TO_EDGE),
        "GL_CLAMP_TO_EDGE should be used in NPOT dimensions");

    GL::bindTexture2D( _name );
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
    ccTexParams texParams = {(GLuint)(_hasMipmaps?GL_NEAREST_MIPMAP_NEAREST:GL_NEAREST),GL_NEAREST,GL_NONE,GL_NONE};
    VolatileTexture::setTexParameters(this, texParams);
#endif
}

void Texture2D::setAntiAliasTexParameters()
{
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
    ccTexParams texParams = {(GLuint)(_hasMipmaps?GL_LINEAR_MIPMAP_NEAREST:GL_LINEAR),GL_LINEAR,GL_NONE,GL_NONE};
    VolatileTexture::setTexParameters(this, texParams);
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

		default:
			CCASSERT(false , "unrecognized pixel format");
			CCLOG("stringForFormat: %ld, cannot give useful result", (long)_pixelFormat);
			break;
	}

	return  NULL;
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
    if (format == PixelFormat::NONE)
    {
        return 0;
    }
    
	return g_texturePixelFormatInfoTables.at(format).bpp;
}

unsigned int Texture2D::getBitsPerPixelForFormat() const
{
	return this->getBitsPerPixelForFormat(_pixelFormat);
}


NS_CC_END
