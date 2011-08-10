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
#import "CCImage.h"
#import "CCFileUtils.h"
#import <string>

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#if CC_FONT_LABEL_SUPPORT
// FontLabel support
#import "FontLabel/FontManager.h"
#import "FontLabel/FontLabelStringDrawing.h"
#endif// CC_FONT_LABEL_SUPPORT

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
    
    if(colorSpace) 
    {
        if(hasAlpha || bpp >= 8)
        {
            pixelFormat = kCCTexture2DPixelFormat_Default;
        }
        else 
        {
            pixelFormat = kCCTexture2DPixelFormat_RGB565;
        }
    } 
    else  
    {
        // NOTE: No colorspace means a mask image
        pixelFormat = kCCTexture2DPixelFormat_A8;
    }
    
    imageSize.width = CGImageGetWidth(image);
    imageSize.height = CGImageGetHeight(image);
    
    // Create the bitmap graphics context
    
    switch(pixelFormat) 
    {      
        case kCCTexture2DPixelFormat_RGBA8888:
        case kCCTexture2DPixelFormat_RGBA4444:
        case kCCTexture2DPixelFormat_RGB5A1:
            colorSpace = CGColorSpaceCreateDeviceRGB();
            data = new unsigned char[POTHigh * POTWide * 4];
            info = hasAlpha ? kCGImageAlphaPremultipliedLast : kCGImageAlphaNoneSkipLast; 
            context = CGBitmapContextCreate(data, POTWide, POTHigh, 8, 4 * POTWide, colorSpace, info | kCGBitmapByteOrder32Big);                
            CGColorSpaceRelease(colorSpace);
            break;
            
        case kCCTexture2DPixelFormat_RGB565:
            colorSpace = CGColorSpaceCreateDeviceRGB();
            data = new unsigned char[POTHigh * POTWide * 4];
            info = kCGImageAlphaNoneSkipLast;
            context = CGBitmapContextCreate(data, POTWide, POTHigh, 8, 4 * POTWide, colorSpace, info | kCGBitmapByteOrder32Big);
            CGColorSpaceRelease(colorSpace);
            break;
        case kCCTexture2DPixelFormat_A8:
            data = new unsigned char[POTHigh * POTWide];
            info = kCGImageAlphaOnly; 
            context = CGBitmapContextCreate(data, POTWide, POTHigh, 8, POTWide, NULL, info);
            break;            
        default:
            return false;
    }
    
    CGRect rect;
    rect.size.width = POTWide;
    rect.size.height = POTHigh;
    rect.origin.x = 0;
    rect.origin.y = 0;
    
    CGContextClearRect(context, rect);
    CGContextTranslateCTM(context, 0, POTHigh - imageSize.height);
    rect.size.width = CGImageGetWidth(image);
    rect.size.height = CGImageGetHeight(image);
    rect.origin.x = 0;
    rect.origin.y = 0;
    CGContextDrawImage(context, rect, image);
    
    // Repack the pixel data into the right format
    
    if(pixelFormat == kCCTexture2DPixelFormat_RGB565) 
    {
        //Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGGBBBBB"
        tempData = new unsigned char[POTHigh * POTWide * 2];
        inPixel32 = (unsigned int*)data;
        outPixel16 = (unsigned short*)tempData;
        for(i = 0; i < POTWide * POTHigh; ++i, ++inPixel32)
        {
            *outPixel16++ = ((((*inPixel32 >> 0) & 0xFF) >> 3) << 11) | ((((*inPixel32 >> 8) & 0xFF) >> 2) << 5) | ((((*inPixel32 >> 16) & 0xFF) >> 3) << 0);
        }

        delete[] data;
        data = tempData;
        
    }
    else if (pixelFormat == kCCTexture2DPixelFormat_RGBA4444) 
    {
        //Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRGGGGBBBBAAAA"
        tempData = new unsigned char[POTHigh * POTWide * 2];
        inPixel32 = (unsigned int*)data;
        outPixel16 = (unsigned short*)tempData;
        for(i = 0; i < POTWide * POTHigh; ++i, ++inPixel32)
        {
            *outPixel16++ = 
            ((((*inPixel32 >> 0) & 0xFF) >> 4) << 12) | // R
            ((((*inPixel32 >> 8) & 0xFF) >> 4) << 8) | // G
            ((((*inPixel32 >> 16) & 0xFF) >> 4) << 4) | // B
            ((((*inPixel32 >> 24) & 0xFF) >> 4) << 0); // A
        }       
        
        delete[] data;
        data = tempData;
        
    }
    else if (pixelFormat == kCCTexture2DPixelFormat_RGB5A1) 
    {
        //Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGBBBBBA"
        tempData = new unsigned char[POTHigh * POTWide * 2];
        inPixel32 = (unsigned int*)data;
        outPixel16 = (unsigned short*)tempData;
        for(i = 0; i < POTWide * POTHigh; ++i, ++inPixel32)
        {
            *outPixel16++ = 
            ((((*inPixel32 >> 0) & 0xFF) >> 3) << 11) | // R
            ((((*inPixel32 >> 8) & 0xFF) >> 3) << 6) | // G
            ((((*inPixel32 >> 16) & 0xFF) >> 3) << 1) | // B
            ((((*inPixel32 >> 24) & 0xFF) >> 7) << 0); // A
        }
                
        delete[] data;
        data = tempData;
    }
    
    // should be after calling super init
    pImageInfo->isPremultipliedAlpha = true;
    pImageInfo->hasAlpha = true;
    pImageInfo->bitsPerComponent = bpp;
    pImageInfo->width = imageSize.width;
    pImageInfo->height = imageSize.height;
    
    if (pImageInfo->data)
    {
        delete [] pImageInfo->data;
    }
    pImageInfo->data = data;
    
    CGContextRelease(context);
    return true;
}

static bool _initWithImage(CGImageRef CGImage, tImageInfo *pImageinfo)
{
    NSUInteger POTWide, POTHigh;
    
    if(CGImage == NULL) 
    {
        return false;
    }
    
    POTWide = CGImageGetWidth(CGImage);
    POTHigh = CGImageGetHeight(CGImage);
    
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
    
    if (pBuffer) 
    {
        CGImageRef CGImage;
        NSData *data;
        
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
    
    for (NSString *familiName in [UIFont familyNames]) 
    {
        if ([familiName isEqualToString:fontNameNS]) 
        {
            ret = true;
            goto out;
        }
        
        for(NSString *font in [UIFont fontNamesForFamilyName: familiName])
        {
            if ([font isEqualToString: fontNameNS])
            {
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
        
        NSString * str  = [NSString stringWithUTF8String:pText];
        NSString * fntName = [NSString stringWithUTF8String:pFontName];
        CGSize dim;
        
        // create the font   
        id font;
        font = [UIFont fontWithName:fntName size:nSize];  
        if (font)
        {
                dim = [str sizeWithFont:font];
        }      
        
#if CC_FONT_LABEL_SUPPORT
	    if (! font)
	    {
		        font = [[FontManager sharedManager] zFontWithName:fntName pointSize:nSize];
		        if (font)
                {
                        //dim = [str sizeWithZFont:font];
                        dim = [FontLabelStringDrawingHelper sizeWithZFont:str zfont:font];
                }  
	    }
#endif // CC_FONT_LABEL_SUPPORT

        if (! font)
        {
                fntName = _isValidFontName(pFontName) ? fntName : @"MarkerFelt-Wide";
                font = [UIFont fontWithName:fntName size:nSize];
                
                if (! font) 
                {
                        font = [UIFont systemFontOfSize:nSize];
                }
                
                if (font)
                {
                        dim = [str sizeWithFont:font];
                }  
        }
        
        if (pInfo->width != 0 || pInfo->height != 0)
        {
                dim.width = pInfo->width;
                dim.height = pInfo->height;
        }
        else
        {
                pInfo->width = dim.width;
                pInfo->height = dim.height;
        }

        CC_BREAK_IF(! font);
        
        unsigned char* data = new unsigned char[pInfo->width * pInfo->height * 4];
        memset(data, 0, pInfo->width * pInfo->height * 4);
        
        // draw text
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();    
        CGContextRef context = CGBitmapContextCreate(data, dim.width, dim.height, 8, dim.width * 4, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
        CGColorSpaceRelease(colorSpace);
        
		if (! context)
		{
		        delete[] data;
		        break;
		}
        
        CGContextSetRGBFillColor(context, 1, 1, 1, 1);
        CGContextTranslateCTM(context, 0.0f, dim.height);
        CGContextScaleCTM(context, 1.0f, -1.0f); //NOTE: NSString draws in UIKit referential i.e. renders upside-down compared to CGBitmapContext referential
        UIGraphicsPushContext(context);
        
        // measure text size with specified font and determine the rectangle to draw text in
        unsigned uHoriFlag = eAlign & 0x0f;
        UITextAlignment align = (2 == uHoriFlag) ? UITextAlignmentRight
                                : (3 == uHoriFlag) ? UITextAlignmentCenter
                                : UITextAlignmentLeft;
        
        // normal fonts
	if( [font isKindOfClass:[UIFont class] ] )
	{
		[str drawInRect:CGRectMake(0, 0, dim.width, dim.height) withFont:font lineBreakMode:UILineBreakModeWordWrap alignment:align];
	}
	
#if CC_FONT_LABEL_SUPPORT
	else // ZFont class 
	{
		[FontLabelStringDrawingHelper drawInRect:str rect:CGRectMake(0, 0, dim.width, dim.height) withZFont:font lineBreakMode:UILineBreakModeWordWrap alignment:align];
	}
#endif
        
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

bool CCImage::initWithImageData(void * pData, 
                                int nDataLen, 
                                EImageFormat eFmt,
                                int nWidth,
                                int nHeight,
                                int nBitsPerComponent)
{
    bool bRet = false;
    tImageInfo info = {0};
    do 
    {
        CC_BREAK_IF(! pData || nDataLen <= 0);
        if (eFmt == kFmtRawData)
        {
            bRet = _initWithRawData(pData, nDataLen, nWidth, nHeight, nBitsPerComponent);
        }
        else // init with png or jpg file data
        {
            bRet = _initWithData(pData, nDataLen, &info);
            if (bRet)
            {
                m_nHeight = (short)info.height;
                m_nWidth = (short)info.width;
                m_nBitsPerComponent = info.bitsPerComponent;
                m_bHasAlpha = info.hasAlpha;
                m_bPreMulti = info.isPremultipliedAlpha;
                m_pData = info.data;
            }
        }
    } while (0);
    
    return bRet;
}

bool CCImage::_initWithRawData(void *pData, int nDatalen, int nWidth, int nHeight, int nBitsPerComponent)
{
    bool bRet = false;
	do 
	{
		CC_BREAK_IF(0 == nWidth || 0 == nHeight);

		m_nBitsPerComponent = nBitsPerComponent;
		m_nHeight   = (short)nHeight;
		m_nWidth    = (short)nWidth;
		m_bHasAlpha = true;

		// only RGBA8888 surported
		int nBytesPerComponent = 4;
		int nSize = nHeight * nWidth * nBytesPerComponent;
		m_pData = new unsigned char[nSize];
		CC_BREAK_IF(! m_pData);
		memcpy(m_pData, pData, nSize);

		bRet = true;
	} while (0);
	return bRet;
}

bool CCImage::_initWithJpgData(void *pData, int nDatalen)
{
    assert(0);
}

bool CCImage::_initWithPngData(void *pData, int nDatalen)
{
    assert(0);
}

bool CCImage::_saveImageToPNG(const char *pszFilePath, bool bIsToRGB)
{
    assert(0);
}

bool CCImage::_saveImageToJPG(const char *pszFilePath)
{
    assert(0);
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

bool CCImage::saveToFile(const char *pszFilePath, bool bIsToRGB)
{
	bool saveToPNG = false;
	bool needToCopyPixels = false;
	std::string filePath(pszFilePath);
	if (std::string::npos != filePath.find(".png"))
	{
	    saveToPNG = true;
	}
		
	int bitsPerComponent = 8;			
	int bitsPerPixel = m_bHasAlpha ? 32 : 24;
	if ((! saveToPNG) || bIsToRGB)
	{
	    bitsPerPixel = 24;
	}			
	
	int bytesPerRow	= (bitsPerPixel/8) * m_nWidth;
	int myDataLength = bytesPerRow * m_nHeight;
	
	unsigned char *pixels	= m_pData;
	
	// The data has alpha channel, and want to save it with an RGB png file,
    // or want to save as jpg,  remove the alpha channel.
	if ((saveToPNG && m_bHasAlpha && bIsToRGB)
       || (! saveToPNG))
	{
	    pixels = new unsigned char[myDataLength];
	    
	    for (int i = 0; i < m_nHeight; ++i)
		{
			for (int j = 0; j < m_nWidth; ++j)
			{
				pixels[(i * m_nWidth + j) * 3] = m_pData[(i * m_nWidth + j) * 4];
				pixels[(i * m_nWidth + j) * 3 + 1] = m_pData[(i * m_nWidth + j) * 4 + 1];
				pixels[(i * m_nWidth + j) * 3 + 2] = m_pData[(i * m_nWidth + j) * 4 + 2];
			}
		}
		
	    needToCopyPixels = true;
	}
		
	// make data provider with data.
	CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
	if (saveToPNG && m_bHasAlpha && (! bIsToRGB))
	{
	    bitmapInfo |= kCGImageAlphaPremultipliedLast;
	}
	CGDataProviderRef provider		= CGDataProviderCreateWithData(NULL, pixels, myDataLength, NULL);
	CGColorSpaceRef colorSpaceRef	= CGColorSpaceCreateDeviceRGB();
	CGImageRef iref					= CGImageCreate(m_nWidth, m_nHeight,
														bitsPerComponent, bitsPerPixel, bytesPerRow,
														colorSpaceRef, bitmapInfo, provider,
														NULL, false,
														kCGRenderingIntentDefault);
		
	UIImage* image					= [[UIImage alloc] initWithCGImage:iref];
		
	CGImageRelease(iref);	
	CGColorSpaceRelease(colorSpaceRef);
	CGDataProviderRelease(provider);
	
	NSData *data;
				
	if (saveToPNG)
	{
		data = UIImagePNGRepresentation(image);
	}
	else
	{
		data = UIImageJPEGRepresentation(image, 1.0f);
	}
	
	[data writeToFile:[NSString stringWithUTF8String:pszFilePath] atomically:YES];
		
	[image release];
		
	if (needToCopyPixels)
	{
	    delete [] pixels;
	}
	
	return true;
}

NS_CC_END;

