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
#include "textures/CCTexturePVR.h"
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

Texture2D::Texture2D()
: _PVRHaveAlphaPremultiplied(true)
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

bool Texture2D::hasPremultipliedAlpha()
{
    return _hasPremultipliedAlpha;
}

bool Texture2D::initWithData(const void *data, Texture2DPixelFormat pixelFormat, unsigned int pixelsWide, unsigned int pixelsHigh, const Size& contentSize)
{
    unsigned int bitsPerPixel;
    //Hack: bitsPerPixelForFormat returns wrong number for RGB_888 textures. See function.
    if(pixelFormat == kTexture2DPixelFormat_RGB888)
    {
        bitsPerPixel = 24;
    }
    else
    {
        bitsPerPixel = bitsPerPixelForFormat(pixelFormat);
    }

    unsigned int bytesPerRow = pixelsWide * bitsPerPixel / 8;

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


    glGenTextures(1, &_name);
    ccGLBindTexture2D(_name);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    // Specify OpenGL texture image

    switch(pixelFormat)
    {
    case kTexture2DPixelFormat_RGBA8888:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)pixelsWide, (GLsizei)pixelsHigh, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        break;
    case kTexture2DPixelFormat_RGB888:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei)pixelsWide, (GLsizei)pixelsHigh, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        break;
    case kTexture2DPixelFormat_RGBA4444:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)pixelsWide, (GLsizei)pixelsHigh, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, data);
        break;
    case kTexture2DPixelFormat_RGB5A1:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)pixelsWide, (GLsizei)pixelsHigh, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, data);
        break;
    case kTexture2DPixelFormat_RGB565:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei)pixelsWide, (GLsizei)pixelsHigh, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, data);
        break;
    case kTexture2DPixelFormat_AI88:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, (GLsizei)pixelsWide, (GLsizei)pixelsHigh, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data);
        break;
    case kTexture2DPixelFormat_A8:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, (GLsizei)pixelsWide, (GLsizei)pixelsHigh, 0, GL_ALPHA, GL_UNSIGNED_BYTE, data);
        break;
    case kTexture2DPixelFormat_I8:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, (GLsizei)pixelsWide, (GLsizei)pixelsHigh, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
        break;
    default:
        CCAssert(0, "NSInternalInconsistencyException");

    }

    _contentSize = contentSize;
    _pixelsWide = pixelsWide;
    _pixelsHigh = pixelsHigh;
    _pixelFormat = pixelFormat;
    _maxS = contentSize.width / (float)(pixelsWide);
    _maxT = contentSize.height / (float)(pixelsHigh);

    _hasPremultipliedAlpha = false;
    _hasMipmaps = false;

    setShaderProgram(ShaderCache::sharedShaderCache()->programForKey(kShader_PositionTexture));

    return true;
}


const char* Texture2D::description(void)
{
    return String::createWithFormat("<Texture2D | Name = %u | Dimensions = %u x %u | Coordinates = (%.2f, %.2f)>", _name, _pixelsWide, _pixelsHigh, _maxS, _maxT)->getCString();
}

// implementation Texture2D (Image)

bool Texture2D::initWithImage(Image *uiImage)
{
    if (uiImage == NULL)
    {
        CCLOG("cocos2d: Texture2D. Can't create Texture. UIImage is nil");
        return false;
    }
    
    unsigned int imageWidth = uiImage->getWidth();
    unsigned int imageHeight = uiImage->getHeight();
    
    Configuration *conf = Configuration::sharedConfiguration();
    
    unsigned maxTextureSize = conf->getMaxTextureSize();
    if (imageWidth > maxTextureSize || imageHeight > maxTextureSize) 
    {
        CCLOG("cocos2d: WARNING: Image (%u x %u) is bigger than the supported %u x %u", imageWidth, imageHeight, maxTextureSize, maxTextureSize);
        return false;
    }
    
    // always load premultiplied images
    return initPremultipliedATextureWithImage(uiImage, imageWidth, imageHeight);
}

bool Texture2D::initPremultipliedATextureWithImage(Image *image, unsigned int width, unsigned int height)
{
    unsigned char*            tempData = image->getData();
    unsigned int*             inPixel32  = NULL;
    unsigned char*            inPixel8 = NULL;
    unsigned short*           outPixel16 = NULL;
    bool                      hasAlpha = image->hasAlpha();
    Size                    imageSize = CCSizeMake((float)(image->getWidth()), (float)(image->getHeight()));
    Texture2DPixelFormat    pixelFormat;
    size_t                    bpp = image->getBitsPerComponent();

    // compute pixel format
    if (hasAlpha)
    {
    	pixelFormat = g_defaultAlphaPixelFormat;
    }
    else
    {
        if (bpp >= 8)
        {
            pixelFormat = kTexture2DPixelFormat_RGB888;
        }
        else 
        {
            pixelFormat = kTexture2DPixelFormat_RGB565;
        }
        
    }
    
    // Repack the pixel data into the right format
    unsigned int length = width * height;

    if (pixelFormat == kTexture2DPixelFormat_RGB565)
    {
        if (hasAlpha)
        {
            // Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGGBBBBB"
            
            tempData = new unsigned char[width * height * 2];
            outPixel16 = (unsigned short*)tempData;
            inPixel32 = (unsigned int*)image->getData();
            
            for(unsigned int i = 0; i < length; ++i, ++inPixel32)
            {
                *outPixel16++ = 
                ((((*inPixel32 >>  0) & 0xFF) >> 3) << 11) |  // R
                ((((*inPixel32 >>  8) & 0xFF) >> 2) << 5)  |  // G
                ((((*inPixel32 >> 16) & 0xFF) >> 3) << 0);    // B
            }
        }
        else 
        {
            // Convert "RRRRRRRRRGGGGGGGGBBBBBBBB" to "RRRRRGGGGGGBBBBB"
            
            tempData = new unsigned char[width * height * 2];
            outPixel16 = (unsigned short*)tempData;
            inPixel8 = (unsigned char*)image->getData();
            
            for(unsigned int i = 0; i < length; ++i)
            {
                *outPixel16++ = 
                (((*inPixel8++ & 0xFF) >> 3) << 11) |  // R
                (((*inPixel8++ & 0xFF) >> 2) << 5)  |  // G
                (((*inPixel8++ & 0xFF) >> 3) << 0);    // B
            }
        }    
    }
    else if (pixelFormat == kTexture2DPixelFormat_RGBA4444)
    {
        // Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRGGGGBBBBAAAA"
        
        inPixel32 = (unsigned int*)image->getData();  
        tempData = new unsigned char[width * height * 2];
        outPixel16 = (unsigned short*)tempData;
        
        for(unsigned int i = 0; i < length; ++i, ++inPixel32)
        {
            *outPixel16++ = 
            ((((*inPixel32 >> 0) & 0xFF) >> 4) << 12) | // R
            ((((*inPixel32 >> 8) & 0xFF) >> 4) <<  8) | // G
            ((((*inPixel32 >> 16) & 0xFF) >> 4) << 4) | // B
            ((((*inPixel32 >> 24) & 0xFF) >> 4) << 0);  // A
        }
    }
    else if (pixelFormat == kTexture2DPixelFormat_RGB5A1)
    {
        // Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGBBBBBA"
        inPixel32 = (unsigned int*)image->getData();   
        tempData = new unsigned char[width * height * 2];
        outPixel16 = (unsigned short*)tempData;
        
        for(unsigned int i = 0; i < length; ++i, ++inPixel32)
        {
            *outPixel16++ = 
            ((((*inPixel32 >> 0) & 0xFF) >> 3) << 11) | // R
            ((((*inPixel32 >> 8) & 0xFF) >> 3) <<  6) | // G
            ((((*inPixel32 >> 16) & 0xFF) >> 3) << 1) | // B
            ((((*inPixel32 >> 24) & 0xFF) >> 7) << 0);  // A
        }
    }
    else if (pixelFormat == kTexture2DPixelFormat_A8)
    {
        // Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "AAAAAAAA"
        inPixel32 = (unsigned int*)image->getData();
        tempData = new unsigned char[width * height];
        unsigned char *outPixel8 = tempData;
        
        for(unsigned int i = 0; i < length; ++i, ++inPixel32)
        {
            *outPixel8++ = (*inPixel32 >> 24) & 0xFF;  // A
        }
    }
    
    if (hasAlpha && pixelFormat == kTexture2DPixelFormat_RGB888)
    {
        // Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRRRRGGGGGGGGBBBBBBBB"
        inPixel32 = (unsigned int*)image->getData();
        tempData = new unsigned char[width * height * 3];
        unsigned char *outPixel8 = tempData;
        
        for(unsigned int i = 0; i < length; ++i, ++inPixel32)
        {
            *outPixel8++ = (*inPixel32 >> 0) & 0xFF; // R
            *outPixel8++ = (*inPixel32 >> 8) & 0xFF; // G
            *outPixel8++ = (*inPixel32 >> 16) & 0xFF; // B
        }
    }
    
    initWithData(tempData, pixelFormat, width, height, imageSize);
    
    if (tempData != image->getData())
    {
        delete [] tempData;
    }

    _hasPremultipliedAlpha = image->isPremultipliedAlpha();
    return true;
}

// implementation Texture2D (Text)
bool Texture2D::initWithString(const char *text, const char *fontName, float fontSize)
{
    return initWithString(text,  fontName, fontSize, CCSizeMake(0,0), kTextAlignmentCenter, kVerticalTextAlignmentTop);
}

bool Texture2D::initWithString(const char *text, const char *fontName, float fontSize, const Size& dimensions, TextAlignment hAlignment, VerticalTextAlignment vAlignment)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
        ccFontDefinition tempDef;
        
        tempDef._shadow._shadowEnabled = false;
        tempDef._stroke._strokeEnabled = false;
       
        
        tempDef._fontName      = std::string(fontName);
        tempDef._fontSize      = fontSize;
        tempDef._dimensions    = dimensions;
        tempDef._alignment     = hAlignment;
        tempDef._vertAlignment = vAlignment;
        tempDef._fontFillColor = ccWHITE;
    
        return initWithString(text, &tempDef);
    
    
    #else
    
    
    #if CC_ENABLE_CACHE_TEXTURE_DATA
        // cache the texture data
        VolatileTexture::addStringTexture(this, text, dimensions, hAlignment, vAlignment, fontName, fontSize);
    #endif
        
        bool bRet = false;
        Image::ETextAlign eAlign;
        
        if (kVerticalTextAlignmentTop == vAlignment)
        {
            eAlign = (kTextAlignmentCenter == hAlignment) ? Image::kAlignTop
            : (kTextAlignmentLeft == hAlignment) ? Image::kAlignTopLeft : Image::kAlignTopRight;
        }
        else if (kVerticalTextAlignmentCenter == vAlignment)
        {
            eAlign = (kTextAlignmentCenter == hAlignment) ? Image::kAlignCenter
            : (kTextAlignmentLeft == hAlignment) ? Image::kAlignLeft : Image::kAlignRight;
        }
        else if (kVerticalTextAlignmentBottom == vAlignment)
        {
            eAlign = (kTextAlignmentCenter == hAlignment) ? Image::kAlignBottom
            : (kTextAlignmentLeft == hAlignment) ? Image::kAlignBottomLeft : Image::kAlignBottomRight;
        }
        else
        {
            CCAssert(false, "Not supported alignment format!");
            return false;
        }
        
        do
        {
            Image* pImage = new Image();
            CC_BREAK_IF(NULL == pImage);
            bRet = pImage->initWithString(text, (int)dimensions.width, (int)dimensions.height, eAlign, fontName, (int)fontSize);
            CC_BREAK_IF(!bRet);
            bRet = initWithImage(pImage);
            CC_SAFE_RELEASE(pImage);
        } while (0);
    
    
        return bRet;
    
    
    #endif
    
}

bool Texture2D::initWithString(const char *text, ccFontDefinition *textDefinition)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    #if CC_ENABLE_CACHE_TEXTURE_DATA
        // cache the texture data
        VolatileTexture::addStringTexture(this, text, dimensions, hAlignment, vAlignment, fontName, fontSize);
    #endif
        
        bool bRet = false;
        Image::ETextAlign eAlign;
        
        if (kVerticalTextAlignmentTop == textDefinition->_vertAlignment)
        {
            eAlign = (kTextAlignmentCenter == textDefinition->_alignment) ? Image::kAlignTop
            : (kTextAlignmentLeft == textDefinition->_alignment) ? Image::kAlignTopLeft : Image::kAlignTopRight;
        }
        else if (kVerticalTextAlignmentCenter == textDefinition->_vertAlignment)
        {
            eAlign = (kTextAlignmentCenter == textDefinition->_alignment) ? Image::kAlignCenter
            : (kTextAlignmentLeft == textDefinition->_alignment) ? Image::kAlignLeft : Image::kAlignRight;
        }
        else if (kVerticalTextAlignmentBottom == textDefinition->_vertAlignment)
        {
            eAlign = (kTextAlignmentCenter == textDefinition->_alignment) ? Image::kAlignBottom
            : (kTextAlignmentLeft == textDefinition->_alignment) ? Image::kAlignBottomLeft : Image::kAlignBottomRight;
        }
        else
        {
            CCAssert(false, "Not supported alignment format!");
            return false;
        }
        
        // handle shadow parameters
        bool  shadowEnabled = false;
        float shadowDX      = 0.0f;
        float shadowDY      = 0.0f;
        float shadowBlur    = 0.0f;
        float shadowOpacity = 0.0f;
        
        if ( textDefinition->_shadow._shadowEnabled )
        {
            shadowEnabled =  true;
            shadowDX      = textDefinition->_shadow._shadowOffset.width;
            shadowDY      = textDefinition->_shadow._shadowOffset.height;
            shadowBlur    = textDefinition->_shadow._shadowBlur;
            shadowOpacity = textDefinition->_shadow._shadowOpacity;
        }
        
        // handle stroke parameters
        bool strokeEnabled = false;
        float strokeColorR = 0.0f;
        float strokeColorG = 0.0f;
        float strokeColorB = 0.0f;
        float strokeSize   = 0.0f;
        
        if ( textDefinition->_stroke._strokeEnabled )
        {
            strokeEnabled = true;
            strokeColorR = textDefinition->_stroke._strokeColor.r / 255.0f;
            strokeColorG = textDefinition->_stroke._strokeColor.g / 255.0f;
            strokeColorB = textDefinition->_stroke._strokeColor.b / 255.0f;
            strokeSize   = textDefinition->_stroke._strokeSize;
        }
        
        Image* pImage = new Image();
        do
        {
            CC_BREAK_IF(NULL == pImage);
            
            bRet = pImage->initWithStringShadowStroke(text,
                                                      (int)textDefinition->_dimensions.width,
                                                      (int)textDefinition->_dimensions.height,
                                                      eAlign,
                                                      textDefinition->_fontName.c_str(),
                                                      textDefinition->_fontSize,
                                                      textDefinition->_fontFillColor.r / 255.0f,
                                                      textDefinition->_fontFillColor.g / 255.0f,
                                                      textDefinition->_fontFillColor.b / 255.0f,
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
    
        CCAssert(false, "Currently only supported on iOS and Android!");
        return false;
    
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

bool Texture2D::initWithPVRFile(const char* file)
{
    bool bRet = false;
    // nothing to do with Object::init
    
    TexturePVR *pvr = new TexturePVR;
    bRet = pvr->initWithContentsOfFile(file);
        
    if (bRet)
    {
        pvr->setRetainName(true); // don't dealloc texture on release
        
        _name = pvr->getName();
        _maxS = 1.0f;
        _maxT = 1.0f;
        _pixelsWide = pvr->getWidth();
        _pixelsHigh = pvr->getHeight();
        _contentSize = CCSizeMake((float)_pixelsWide, (float)_pixelsHigh);
        _hasPremultipliedAlpha = PVRHaveAlphaPremultiplied_;
        _pixelFormat = pvr->getFormat();
        _hasMipmaps = pvr->getNumberOfMipmaps() > 1;       

        pvr->release();
    }
    else
    {
        CCLOG("cocos2d: Couldn't load PVR image %s", file);
    }

    return bRet;
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
        _contentSize = CCSizeMake((float)_pixelsWide, (float)_pixelsHigh);
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

bool Texture2D::hasMipmaps()
{
    return _hasMipmaps;
}

void Texture2D::setTexParameters(ccTexParams *texParams)
{
    CCAssert( (_pixelsWide == ccNextPOT(_pixelsWide) || texParams->wrapS == GL_CLAMP_TO_EDGE) &&
        (_pixelsHigh == ccNextPOT(_pixelsHigh) || texParams->wrapT == GL_CLAMP_TO_EDGE),
        "GL_CLAMP_TO_EDGE should be used in NPOT dimensions");

    ccGLBindTexture2D( _name );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texParams->minFilter );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texParams->magFilter );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texParams->wrapS );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texParams->wrapT );

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
    VolatileTexture::setTexParameters(this, &texParams);
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
    VolatileTexture::setTexParameters(this, &texParams);
#endif
}

const char* Texture2D::stringForFormat()
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

unsigned int Texture2D::bitsPerPixelForFormat(Texture2DPixelFormat format)
{
	unsigned int ret=0;

	switch (format) {
		case kTexture2DPixelFormat_RGBA8888:
			ret = 32;
			break;
		case kTexture2DPixelFormat_RGB888:
			// It is 32 and not 24, since its internal representation uses 32 bits.
			ret = 32;
			break;
		case kTexture2DPixelFormat_RGB565:
			ret = 16;
			break;
		case kTexture2DPixelFormat_RGBA4444:
			ret = 16;
			break;
		case kTexture2DPixelFormat_RGB5A1:
			ret = 16;
			break;
		case kTexture2DPixelFormat_AI88:
			ret = 16;
			break;
		case kTexture2DPixelFormat_A8:
			ret = 8;
			break;
		case kTexture2DPixelFormat_I8:
			ret = 8;
			break;
		case kTexture2DPixelFormat_PVRTC4:
			ret = 4;
			break;
		case kTexture2DPixelFormat_PVRTC2:
			ret = 2;
			break;
		default:
			ret = -1;
			CCAssert(false , "unrecognized pixel format");
			CCLOG("bitsPerPixelForFormat: %ld, cannot give useful result", (long)format);
			break;
	}
	return ret;
}

unsigned int Texture2D::bitsPerPixelForFormat()
{
	return this->bitsPerPixelForFormat(_pixelFormat);
}


NS_CC_END
