/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include <Foundation/Foundation.h>
#include <UIKit/UIKit.h>
#include "CCImage.h"
#include "CCFileUtils.h"
#include <string>

typedef struct
{
    unsigned int height;
    unsigned int width;
    int         bitsPerComponent;
    bool        hasAlpha;
    bool        isPremultipliedAlpha;
    unsigned char*  data;
} tImageInfo;

static unsigned int nextPOT(unsigned int x)
{
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    return x + 1;
}

typedef enum {
    kCCTexture2DPixelFormat_Automatic = 0,
        //! 32-bit texture: RGBA8888
    kCCTexture2DPixelFormat_RGBA8888,
        //! 24-bit texture: RGBA888
    kCCTexture2DPixelFormat_RGB888,
        //! 16-bit texture without Alpha channel
    kCCTexture2DPixelFormat_RGB565,
        //! 8-bit textures used as masks
    kCCTexture2DPixelFormat_A8,
        //! 16-bit textures: RGBA4444
    kCCTexture2DPixelFormat_RGBA4444,
        //! 16-bit textures: RGB5A1
    kCCTexture2DPixelFormat_RGB5A1,    
    
        //! Default texture format: RGBA8888
    kCCTexture2DPixelFormat_Default = kCCTexture2DPixelFormat_RGBA8888,
    
        // backward compatibility stuff
    kTexture2DPixelFormat_Automatic = kCCTexture2DPixelFormat_Automatic,
    kTexture2DPixelFormat_RGBA8888 = kCCTexture2DPixelFormat_RGBA8888,
    kTexture2DPixelFormat_RGB888 = kCCTexture2DPixelFormat_RGB888,
    kTexture2DPixelFormat_RGB565 = kCCTexture2DPixelFormat_RGB565,
    kTexture2DPixelFormat_A8 = kCCTexture2DPixelFormat_A8,
    kTexture2DPixelFormat_RGBA4444 = kCCTexture2DPixelFormat_RGBA4444,
    kTexture2DPixelFormat_RGB5A1 = kCCTexture2DPixelFormat_RGB5A1,
    kTexture2DPixelFormat_Default = kCCTexture2DPixelFormat_Default
    
} CCTexture2DPixelFormat;

static bool _initPremultipliedATextureWithImage(CGImageRef image, NSUInteger POTWide, NSUInteger POTHigh, tImageInfo *pImageInfo)
{
    NSUInteger            i;
    CGContextRef        context = nil;
    unsigned char*        data = nil;;
    CGColorSpaceRef        colorSpace;
    unsigned char*        tempData;
    unsigned int*        inPixel32;
    unsigned short*        outPixel16;
    bool                hasAlpha;
    CGImageAlphaInfo    info;
    CGSize                imageSize;
    CCTexture2DPixelFormat    pixelFormat;
    
    info = CGImageGetAlphaInfo(image);
    hasAlpha = ((info == kCGImageAlphaPremultipliedLast) || (info == kCGImageAlphaPremultipliedFirst) || (info == kCGImageAlphaLast) || (info == kCGImageAlphaFirst) ? YES : NO);
    
    size_t bpp = CGImageGetBitsPerComponent(image);
    colorSpace = CGImageGetColorSpace(image);
    
    if(colorSpace) {
        if(hasAlpha || bpp >= 8)
            pixelFormat = kCCTexture2DPixelFormat_Default;
        else {
            //CCLOG(@"cocos2d: CCTexture2D: Using RGB565 texture since image has no alpha");
            pixelFormat = kCCTexture2DPixelFormat_RGB565;
        }
    } else  {
        // NOTE: No colorspace means a mask image
        //CCLOG(@"cocos2d: CCTexture2D: Using A8 texture since image is a mask");
        pixelFormat = kCCTexture2DPixelFormat_A8;
    }
    
    imageSize.width = CGImageGetWidth(image);
    imageSize.height = CGImageGetHeight(image);
    //imageSize = CGSizeMake(CGImageGetWidth(image), CGImageGetHeight(image));
    
    // Create the bitmap graphics context
    
    switch(pixelFormat) {      
        case kCCTexture2DPixelFormat_RGBA8888:
        case kCCTexture2DPixelFormat_RGBA4444:
        case kCCTexture2DPixelFormat_RGB5A1:
            colorSpace = CGColorSpaceCreateDeviceRGB();
            //data = malloc(POTHigh * POTWide * 4);
            data = new unsigned char[POTHigh * POTWide * 4];
            info = hasAlpha ? kCGImageAlphaPremultipliedLast : kCGImageAlphaNoneSkipLast; 
            // info = kCGImageAlphaPremultipliedLast;  // issue #886. This patch breaks BMP images.
            context = CGBitmapContextCreate(data, POTWide, POTHigh, 8, 4 * POTWide, colorSpace, info | kCGBitmapByteOrder32Big);                
            CGColorSpaceRelease(colorSpace);
            break;
            
        case kCCTexture2DPixelFormat_RGB565:
            colorSpace = CGColorSpaceCreateDeviceRGB();
            //data = malloc(POTHigh * POTWide * 4);
            data = new unsigned char[POTHigh * POTWide * 4];
            info = kCGImageAlphaNoneSkipLast;
            context = CGBitmapContextCreate(data, POTWide, POTHigh, 8, 4 * POTWide, colorSpace, info | kCGBitmapByteOrder32Big);
            CGColorSpaceRelease(colorSpace);
            break;
        case kCCTexture2DPixelFormat_A8:
            //data = malloc(POTHigh * POTWide);
            data = new unsigned char[POTHigh * POTWide];
            info = kCGImageAlphaOnly; 
            context = CGBitmapContextCreate(data, POTWide, POTHigh, 8, POTWide, NULL, info);
            break;            
        default:
            //[NSException raise:NSInternalInconsistencyException format:@"Invalid pixel format"];
            return false;
    }
    
    CGRect rect;
    rect.size.width = POTWide;
    rect.size.height = POTHigh;
    rect.origin.x = 0;
    rect.origin.y = 0;
    
    //CGContextClearRect(context, CGRectMake(0, 0, POTWide, POTHigh));
    CGContextClearRect(context, rect);
    CGContextTranslateCTM(context, 0, POTHigh - imageSize.height);
    //CGContextDrawImage(context, CGRectMake(0, 0, CGImageGetWidth(image), CGImageGetHeight(image)), image);
    rect.size.width = CGImageGetWidth(image);
    rect.size.height = CGImageGetHeight(image);
    rect.origin.x = 0;
    rect.origin.y = 0;
    //CGContextDrawImage(context, CGRectMake(0, 0, CGImageGetWidth(image), CGImageGetHeight(image)), image);
    CGContextDrawImage(context, rect, image);
    
    // Repack the pixel data into the right format
    
    if(pixelFormat == kCCTexture2DPixelFormat_RGB565) {
        //Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGGBBBBB"
        //tempData = malloc(POTHigh * POTWide * 2);
        tempData = new unsigned char[POTHigh * POTWide * 2];
        inPixel32 = (unsigned int*)data;
        outPixel16 = (unsigned short*)tempData;
        for(i = 0; i < POTWide * POTHigh; ++i, ++inPixel32)
            *outPixel16++ = ((((*inPixel32 >> 0) & 0xFF) >> 3) << 11) | ((((*inPixel32 >> 8) & 0xFF) >> 2) << 5) | ((((*inPixel32 >> 16) & 0xFF) >> 3) << 0);
        //free(data);
        delete[] data;
        data = tempData;
        
    }
    else if (pixelFormat == kCCTexture2DPixelFormat_RGBA4444) {
        //Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRGGGGBBBBAAAA"
        //tempData = malloc(POTHigh * POTWide * 2);
        tempData = new unsigned char[POTHigh * POTWide * 2];
        inPixel32 = (unsigned int*)data;
        outPixel16 = (unsigned short*)tempData;
        for(i = 0; i < POTWide * POTHigh; ++i, ++inPixel32)
            *outPixel16++ = 
            ((((*inPixel32 >> 0) & 0xFF) >> 4) << 12) | // R
            ((((*inPixel32 >> 8) & 0xFF) >> 4) << 8) | // G
            ((((*inPixel32 >> 16) & 0xFF) >> 4) << 4) | // B
            ((((*inPixel32 >> 24) & 0xFF) >> 4) << 0); // A
        
        
        //free(data);
        delete[] data;
        data = tempData;
        
    }
    else if (pixelFormat == kCCTexture2DPixelFormat_RGB5A1) {
        //Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGBBBBBA"
        //tempData = malloc(POTHigh * POTWide * 2);
        tempData = new unsigned char[POTHigh * POTWide * 2];
        inPixel32 = (unsigned int*)data;
        outPixel16 = (unsigned short*)tempData;
        for(i = 0; i < POTWide * POTHigh; ++i, ++inPixel32)
            *outPixel16++ = 
            ((((*inPixel32 >> 0) & 0xFF) >> 3) << 11) | // R
            ((((*inPixel32 >> 8) & 0xFF) >> 3) << 6) | // G
            ((((*inPixel32 >> 16) & 0xFF) >> 3) << 1) | // B
            ((((*inPixel32 >> 24) & 0xFF) >> 7) << 0); // A
                
        //free(data);
        delete[] data;
        data = tempData;
    }
    //self = [self initWithData:data pixelFormat:pixelFormat pixelsWide:POTWide pixelsHigh:POTHigh contentSize:imageSize];
    
    // should be after calling super init
    //s_imageInfo.isPremultipliedAlpha = (info == kCGImageAlphaPremultipliedLast || info == kCGImageAlphaPremultipliedFirst);
    pImageInfo->isPremultipliedAlpha = true;
    pImageInfo->hasAlpha = true;
    //s_imageInfo.hasAlpha = hasAlpha;
    pImageInfo->bitsPerComponent = bpp;
    pImageInfo->width = imageSize.width;
    pImageInfo->height = imageSize.height;
    
    if (pImageInfo->data)
    {
        delete []pImageInfo->data;
    }
    pImageInfo->data = data;
    
    CGContextRelease(context);
    return true;
}

static bool _initWithImage(CGImageRef CGImage, tImageInfo *pImageinfo)
{
    NSUInteger                POTWide, POTHigh;
    
    if(CGImage == NULL) {
            //CCLOG(@"cocos2d: CCTexture2D. Can't create Texture. ccxImage is nil");
        return false;
    }
    
        //CCConfiguration *conf = [CCConfiguration sharedConfiguration];
        // cocos2d::CCConfiguration *conf = cocos2d::CCConfiguration::sharedConfiguration();
    
    POTWide = CGImageGetWidth(CGImage);
    POTHigh = CGImageGetHeight(CGImage);
    
    // unsigned maxTextureSize = conf->getMaxTextureSize();
        // if( POTHigh > maxTextureSize || POTWide > maxTextureSize ) {
    //     return false;
    // }
    
        // always load premultiplied images
    _initPremultipliedATextureWithImage(CGImage, POTWide, POTHigh, pImageinfo);
    
    return true;
}

static bool _initWithFile(const char* path, tImageInfo *pImageinfo)
{
    CGImageRef                CGImage;    
    UIImage                    *jpg;
    UIImage                    *png;
    bool            ret;
    
        // convert jpg to png before loading the texture
    
    NSString *fullPath = [NSString stringWithUTF8String:path];
    jpg = [[UIImage alloc] initWithContentsOfFile: fullPath];
    png = [[UIImage alloc] initWithData:UIImagePNGRepresentation(jpg)];
    CGImage = png.CGImage;    
    
    ret = _initWithImage(CGImage, pImageinfo);
    
    [png release];
    [jpg release];
    
    return ret;
}


static bool _initWithData(void * pBuffer, int length, tImageInfo *pImageinfo)
{
    bool ret = false;
    
    if (pBuffer) {
        CGImageRef                CGImage;
        NSData          *data;
        
        data = [NSData dataWithBytes:pBuffer length:length];
        CGImage = [[UIImage imageWithData:data] CGImage];
        
        ret = _initWithImage(CGImage, pImageinfo);
    }
    
    return ret;
}

static bool _isValidFontName(const char *fontName)
{
    bool ret = false;
    
    NSString *fontNameNS = [NSString stringWithUTF8String:fontName];
    
    for (NSString *familiName in [UIFont familyNames]) {
        if ([familiName isEqualToString:fontNameNS]) {
            ret = true;
            goto out;
        }
        
        for(NSString *font in [UIFont fontNamesForFamilyName: familiName]){
            if ([font isEqualToString: fontNameNS]){
                ret = true;
                goto out;
            }
        }
    }
    
    out:
    return ret;
}

static bool _initWithString(const char * pText, cocos2d::CCImage::ETextAlign eAlign, const char * pFontName, int nSize, tImageInfo* pInfo)
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! pText || ! pInfo);
        
        NSString * string  = [NSString stringWithUTF8String:pText];
        
        // create the font
        NSString * fntName = _isValidFontName(pFontName) ? [NSString stringWithUTF8String:pFontName] : @"MarkerFelt-Wide";
        UIFont * font = [UIFont fontWithName:fntName size:nSize];
        if (! font) 
        {
            font = [UIFont systemFontOfSize:nSize];
        }
        CC_BREAK_IF(! font);
        
        // measure text size with specified font and determine the rectangle to draw text in
        unsigned uHoriFlag = eAlign & 0x0f;
        unsigned uVertFlag = (eAlign & 0xf0) >> 4;
        
        CGSize textSize;    // the size which total text layout need
        CGSize canvasSize;  // the size which malloc for drawtext
        CGRect textRect;    // the rectangle which draw text in
        
        if (0 >= pInfo->width)
        {
            //  the content width no limit, use 0x7fffffff as a big enough bounds
            CGSize contentSize = CGSizeMake(0x7fffffff, 0x7fffffff);
            textSize = [string sizeWithFont:font constrainedToSize:contentSize];
            
            canvasSize    = textSize;
            pInfo->width  = (size_t) textSize.width;
            pInfo->height = (size_t) textSize.height;
            
            textRect = CGRectMake(0, 0, textSize.width, textSize.height);
        }
        else
        {
            //  the content  height no limit, use 0x7fffffff as a big enough height
            CGSize contentSize = CGSizeMake(pInfo->width, 0x7fffffff);
            textSize = [string sizeWithFont:font constrainedToSize:contentSize];
            
            if (0 >= pInfo->height)
            {
                canvasSize    = textSize;
                pInfo->height = (size_t) textSize.height;
                pInfo->width  = (size_t) textSize.width;
                
                textRect = CGRectMake(0, 0, textSize.width, textSize.height);
            }
            else
            {
                canvasSize.width = pInfo->width;
                if (textSize.height <= pInfo->height)
                {
                    canvasSize.height = pInfo->height;
                }
                else
                {
                    // the height of text larger than the specified
                    // let canvas's height larger a little,
                    // make sure the last line of text in specified rectangle draw in canvas
                    size_t lineHeight = (size_t)font.lineHeight;
                    canvasSize.height = ((pInfo->height + lineHeight - 1) / lineHeight) * lineHeight;
                }

                canvasSize = CGSizeMake(pInfo->width, MAX(pInfo->height, (size_t)textSize.height));
                
                textRect.size = textSize;
                textRect.origin.x = (1 == uHoriFlag) ? 0               // align to left
                    : (2 == uHoriFlag) ? pInfo->width - textSize.width // align to right
                    : (pInfo->width - textSize.width) / 2;             // align to center

                textRect.origin.y = (1 == uVertFlag || textSize.height >= pInfo->height) ? 0 // align to top
                    : (2 == uVertFlag) ? pInfo->height - textSize.height // align to bottom
                    : (pInfo->height - textSize.height) / 2;             // align to center
            }

        }
                
        // malloc space to store pixels data
        size_t width  = (size_t)canvasSize.width;
        size_t height = (size_t)canvasSize.height;
        unsigned char* data = new unsigned char[width * height * 4];
        CC_BREAK_IF(! data);
        memset(data, 0, height * width * 4);
        
        // draw text
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        
        CGContextRef context = CGBitmapContextCreate(data, width, height, 8, width * 4, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
        CGColorSpaceRelease(colorSpace);
		CC_BREAK_IF(!context);
        
        CGContextSetRGBFillColor(context, 1, 1, 1, 1);
        CGContextTranslateCTM(context, 0.0f, height);
        CGContextScaleCTM(context, 1.0f, -1.0f); //NOTE: NSString draws in UIKit referential i.e. renders upside-down compared to CGBitmapContext referential
        UIGraphicsPushContext(context);
        
        UITextAlignment align = (2 == uHoriFlag) ? UITextAlignmentRight
                                : (3 == uHoriFlag) ? UITextAlignmentCenter
                                : UITextAlignmentLeft;
        [string drawInRect:textRect withFont:font lineBreakMode:UILineBreakModeWordWrap alignment:align];
        
        UIGraphicsPopContext();
        
        CGContextRelease(context);
               
        // output params
        pInfo->data = data;
        pInfo->hasAlpha = true;
        pInfo->isPremultipliedAlpha = true;
        pInfo->bitsPerComponent = 8;
        bRet = true;
    } while (0);

    return bRet;
}

NS_CC_BEGIN;

CCImage::CCImage()
: m_nWidth(0)
, m_nHeight(0)
, m_nBitsPerComponent(0)
, m_pData(0)
, m_bHasAlpha(false)
, m_bPreMulti(false)
{
    
}

CCImage::~CCImage()
{
    CC_SAFE_DELETE_ARRAY(m_pData);
}

bool CCImage::initWithImageFile(const char * strPath, EImageFormat eImgFmt/* = eFmtPng*/)
{
    CCFileData data(CCFileUtils::fullPathFromRelativePath(strPath), "rb");
    return initWithImageData(data.getBuffer(), data.getSize(), eImgFmt);
}

bool CCImage::initWithImageData(void * pData, int nDataLen, EImageFormat eFmt/* = eSrcFmtPng*/)
{
    bool bRet = false;
    tImageInfo info = {0};
    do 
    {
        CC_BREAK_IF(! pData || nDataLen <= 0);
        bRet = _initWithData(pData, nDataLen, &info);
    } while (0);
    if (bRet)
    {
        m_nHeight = (short)info.height;
        m_nWidth = (short)info.width;
        m_nBitsPerComponent = info.bitsPerComponent;
        m_bHasAlpha = info.hasAlpha;
        m_bPreMulti = info.isPremultipliedAlpha;
        m_pData = info.data;
    }
    return bRet;
}

bool CCImage::initWithString(
             const char * pText, 
             int         nWidth /* = 0 */, 
             int         nHeight /* = 0 */,
             ETextAlign eAlignMask /* = kAlignCenter */,
             const char * pFontName /* = nil */,
             int         nSize /* = 0 */)
{
    tImageInfo info = {0};
    info.width = nWidth;
    info.height = nHeight;
      
    if (! _initWithString(pText, eAlignMask, pFontName, nSize, &info))
    {
        return false;
    }
    m_nHeight = (short)info.height;
    m_nWidth = (short)info.width;
    m_nBitsPerComponent = info.bitsPerComponent;
    m_bHasAlpha = info.hasAlpha;
    m_bPreMulti = info.isPremultipliedAlpha;
    m_pData = info.data;

    return true;
}

NS_CC_END;

