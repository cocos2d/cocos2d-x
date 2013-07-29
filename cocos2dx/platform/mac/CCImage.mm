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
#include <Cocoa/Cocoa.h>
#include "CCDirector.h"
#include "ccMacros.h"
#include "CCImage.h"
#include "CCFileUtils.h"
#include "CCTexture2D.h"
#include <string>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

NS_CC_BEGIN

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
    Texture2D::PixelFormat    pixelFormat;
    
    info = CGImageGetAlphaInfo(image);
    hasAlpha = ((info == kCGImageAlphaPremultipliedLast) || (info == kCGImageAlphaPremultipliedFirst) || (info == kCGImageAlphaLast) || (info == kCGImageAlphaFirst) ? YES : NO);
    
    size_t bpp = CGImageGetBitsPerComponent(image);
    colorSpace = CGImageGetColorSpace(image);
    
    if(colorSpace) 
    {
        if(hasAlpha || bpp >= 8)
        {
            pixelFormat = Texture2D::PixelFormat::DEFAULT;
        }
        else 
        {
            pixelFormat = Texture2D::PixelFormat::RGB565;
        }
    } 
    else  
    {
        // NOTE: No colorspace means a mask image
        pixelFormat = Texture2D::PixelFormat::A8;
    }
    
    imageSize.width = CGImageGetWidth(image);
    imageSize.height = CGImageGetHeight(image);
    
    // Create the bitmap graphics context
    
    switch(pixelFormat) 
    {      
        case Texture2D::PixelFormat::RGBA8888:
        case Texture2D::PixelFormat::RGBA4444:
        case Texture2D::PixelFormat::RGB5A1:
            colorSpace = CGColorSpaceCreateDeviceRGB();
            data = new unsigned char[POTHigh * POTWide * 4];
            info = hasAlpha ? kCGImageAlphaPremultipliedLast : kCGImageAlphaNoneSkipLast;
            context = CGBitmapContextCreate(data, POTWide, POTHigh, 8, 4 * POTWide, colorSpace, info | kCGBitmapByteOrder32Big);                
            CGColorSpaceRelease(colorSpace);
            break;
            
        case Texture2D::PixelFormat::RGB565:
            colorSpace = CGColorSpaceCreateDeviceRGB();
            data = new unsigned char[POTHigh * POTWide * 4];
            info = kCGImageAlphaNoneSkipLast;
            context = CGBitmapContextCreate(data, POTWide, POTHigh, 8, 4 * POTWide, colorSpace, info | kCGBitmapByteOrder32Big);
            CGColorSpaceRelease(colorSpace);
            break;
        case Texture2D::PixelFormat::A8:
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
    CGContextTranslateCTM(context, 0, 0);
    CGContextDrawImage(context, rect, image);
    
    // Repack the pixel data into the right format
    
    if(pixelFormat == Texture2D::PixelFormat::RGB565) 
    {
        //Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGGBBBBB"
        tempData = new unsigned char[POTHigh * POTWide * 2];
        inPixel32 = (unsigned int*)data;
        outPixel16 = (unsigned short*)tempData;
        for(i = 0; i < POTWide * POTHigh; ++i, ++inPixel32)
        {
            *outPixel16++ = ((((*inPixel32 >> 0) & 0xFF) >> 3) << 11) | ((((*inPixel32 >> 8) & 0xFF) >> 2) << 5) | ((((*inPixel32 >> 16) & 0xFF) >> 3) << 0);
        }

        delete []data;
        data = tempData;
        
    }
    else if (pixelFormat == Texture2D::PixelFormat::RGBA4444) 
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
        
        delete []data;
        data = tempData;
        
    }
    else if (pixelFormat == Texture2D::PixelFormat::RGB5A1) 
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
                
        delete []data;
        data = tempData;
    }
    
    // should be after calling super init
    pImageInfo->isPremultipliedAlpha = true;
    pImageInfo->hasAlpha = true;
    pImageInfo->bitsPerComponent = bpp;
    pImageInfo->width = POTWide;
    pImageInfo->height = POTHigh;
    
    if (pImageInfo->data)
    {
        delete [] pImageInfo->data;
    }
    pImageInfo->data = data;
    
    CGContextRelease(context);
    return true;
}
// TODO: rename _initWithImage, it also makes a draw call.
static bool _initWithImage(CGImageRef CGImage, tImageInfo *pImageinfo, double scaleX, double scaleY)
{
    NSUInteger POTWide, POTHigh;
    
    if(CGImage == NULL) 
    {
        return false;
    }
    
	//if (cocos2d::Image::getIsScaleEnabled())
	if( cocos2d::Director::getInstance()->getContentScaleFactor() > 1.0f )
	{
		POTWide = CGImageGetWidth(CGImage) * scaleX;
		POTHigh = CGImageGetHeight(CGImage) * scaleY;
	}
	else 
	{
		POTWide = CGImageGetWidth(CGImage);
		POTHigh = CGImageGetHeight(CGImage);
	}

    
    // load and draw image
    return _initPremultipliedATextureWithImage(CGImage, POTWide, POTHigh, pImageinfo);
}

static bool _initWithFile(const char* path, tImageInfo *pImageinfo)
{
    CGImageRef                CGImage;    
    NSImage                    *jpg;
    //NSImage                    *png;
    bool            ret;
    
    // convert jpg to png before loading the texture
    
    NSString *fullPath = [NSString stringWithUTF8String:path];
    jpg = [[NSImage alloc] initWithContentsOfFile: fullPath];
    //png = [[NSImage alloc] initWithData:UIImagePNGRepresentation(jpg)];
    CGImageSourceRef source = CGImageSourceCreateWithData((CFDataRef)[jpg TIFFRepresentation], NULL);
    CGImage = CGImageSourceCreateImageAtIndex(source, 0, NULL);
    
    ret = _initWithImage(CGImage, pImageinfo, 1.0, 1.0);
    
    //[png release];
    [jpg release];
    if (CGImage) CFRelease(CGImage);
    if (source) CFRelease(source);
  
    return ret;
}

// TODO: rename _initWithData, it also makes a draw call.
static bool _initWithData(void * pBuffer, int length, tImageInfo *pImageinfo, double scaleX, double scaleY)
{
    bool ret = false;
    
    if (pBuffer) 
    {
        CGImageRef CGImage;
        NSData *data;
        
        data = [NSData dataWithBytes:pBuffer length:length];
		CGImageSourceRef source = CGImageSourceCreateWithData((CFDataRef)data, NULL);
        CGImage = CGImageSourceCreateImageAtIndex(source, 0, NULL);
        
        ret = _initWithImage(CGImage, pImageinfo, scaleX, scaleY);
        if (CGImage) CFRelease(CGImage);
        if (source) CFRelease(source);
    }
    return ret;
}

static bool _isValidFontName(const char *fontName)
{
    bool ret = false;
#if 0 
    NSString *fontNameNS = [NSString stringWithUTF8String:fontName];
    
    for (NSString *familiName in [NSFont familyNames]) 
    {
        if ([familiName isEqualToString:fontNameNS]) 
        {
            ret = true;
            goto out;
        }
        
        for(NSString *font in [NSFont fontNamesForFamilyName: familiName])
        {
            if ([font isEqualToString: fontNameNS])
            {
                ret = true;
                goto out;
            }
        }
    }
    out:
#endif
    return ret;
}

static bool _initWithString(const char * pText, cocos2d::Image::TextAlign eAlign, const char * pFontName, int nSize, tImageInfo* pInfo, cocos2d::Color3B* pStrokeColor)
{
    bool bRet = false;

	CCASSERT(pText, "Invalid pText");
	CCASSERT(pInfo, "Invalid pInfo");
	
	do {
		NSString * string  = [NSString stringWithUTF8String:pText];
		
		// font
		NSFont *font = [[NSFontManager sharedFontManager]
						 fontWithFamily:[NSString stringWithUTF8String:pFontName]
						traits:NSUnboldFontMask | NSUnitalicFontMask
						 weight:0
						 size:nSize];
		
		if (font == nil) {
			font = [[NSFontManager sharedFontManager]
					fontWithFamily:@"Arial"
					traits:NSUnboldFontMask | NSUnitalicFontMask
					weight:0
					size:nSize];
		}
		CC_BREAK_IF(!font);
		
		// color
		NSColor* foregroundColor;
		if (pStrokeColor) {
			foregroundColor = [NSColor colorWithDeviceRed:pStrokeColor->r/255.0 green:pStrokeColor->g/255.0 blue:pStrokeColor->b/255.0 alpha:1];
		} else {
			foregroundColor = [NSColor whiteColor];
		}
		
		
		// alignment, linebreak
		unsigned uHoriFlag = (int)eAlign & 0x0f;
		unsigned uVertFlag = ((int)eAlign >> 4) & 0x0f;
		NSTextAlignment align = (2 == uHoriFlag) ? NSRightTextAlignment
			: (3 == uHoriFlag) ? NSCenterTextAlignment
			: NSLeftTextAlignment;
		
		NSMutableParagraphStyle *paragraphStyle = [[[NSMutableParagraphStyle alloc] init] autorelease];
		[paragraphStyle setParagraphStyle:[NSParagraphStyle defaultParagraphStyle]];
		[paragraphStyle setLineBreakMode:NSLineBreakByCharWrapping];
		[paragraphStyle setAlignment:align];

		// attribute
		NSDictionary* tokenAttributesDict = [NSDictionary dictionaryWithObjectsAndKeys:
											 foregroundColor,NSForegroundColorAttributeName,
											 font, NSFontAttributeName,
											 paragraphStyle, NSParagraphStyleAttributeName, nil];

		// linebreak
		if (pInfo->width > 0) {
			if ([string sizeWithAttributes:tokenAttributesDict].width > pInfo->width) {
				NSMutableString *lineBreak = [[[NSMutableString alloc] init] autorelease];
				NSUInteger length = [string length];
				NSRange range = NSMakeRange(0, 1);
				NSUInteger width = 0;
				NSUInteger lastBreakLocation = 0;
				for (NSUInteger i = 0; i < length; i++) {
					range.location = i;
					NSString *character = [string substringWithRange:range];
					[lineBreak appendString:character];
					if ([@"!?.,-= " rangeOfString:character].location != NSNotFound) { lastBreakLocation = i; }
					width = [lineBreak sizeWithAttributes:tokenAttributesDict].width;
					if (width > pInfo->width) {
						[lineBreak insertString:@"\r\n" atIndex:(lastBreakLocation > 0) ? lastBreakLocation : [lineBreak length] - 1];
					}
				}
				string = lineBreak;
			}
		}

		NSAttributedString *stringWithAttributes =[[[NSAttributedString alloc] initWithString:string
										 attributes:tokenAttributesDict] autorelease];
				
		NSSize realDimensions = [stringWithAttributes size];
		// Mac crashes if the width or height is 0
		CC_BREAK_IF(realDimensions.width <= 0 || realDimensions.height <= 0);
				
		CGSize dimensions = CGSizeMake(pInfo->width, pInfo->height);
		
	
		if(dimensions.width <= 0 && dimensions.height <= 0) {
			dimensions.width = realDimensions.width;
			dimensions.height = realDimensions.height;
		} else if (dimensions.height <= 0) {
			dimensions.height = realDimensions.height;
		}

		NSUInteger POTWide = (NSUInteger)dimensions.width;
		NSUInteger POTHigh = (NSUInteger)(MAX(dimensions.height, realDimensions.height));
		unsigned char*			data;
		//Alignment
			
		CGFloat xPadding = 0;
		switch (align) {
			case NSLeftTextAlignment: xPadding = 0; break;
			case NSCenterTextAlignment: xPadding = (dimensions.width-realDimensions.width)/2.0f; break;
			case NSRightTextAlignment: xPadding = dimensions.width-realDimensions.width; break;
			default: break;
		}

		// 1: TOP
		// 2: BOTTOM
		// 3: CENTER
		CGFloat yPadding = (1 == uVertFlag || realDimensions.height >= dimensions.height) ? (dimensions.height - realDimensions.height)	// align to top
		: (2 == uVertFlag) ? 0																	// align to bottom
		: (dimensions.height - realDimensions.height) / 2.0f;									// align to center
		
		
		NSRect textRect = NSMakeRect(xPadding, POTHigh - dimensions.height + yPadding, realDimensions.width, realDimensions.height);
		//Disable antialias
		
		[[NSGraphicsContext currentContext] setShouldAntialias:NO];	
		
		NSImage *image = [[NSImage alloc] initWithSize:NSMakeSize(POTWide, POTHigh)];
        
		[image lockFocus];
        
        // patch for mac retina display and lableTTF
        [[NSAffineTransform transform] set];
		
		//[stringWithAttributes drawAtPoint:NSMakePoint(xPadding, offsetY)]; // draw at offset position	
		[stringWithAttributes drawInRect:textRect];
		//[stringWithAttributes drawInRect:textRect withAttributes:tokenAttributesDict];
		NSBitmapImageRep *bitmap = [[NSBitmapImageRep alloc] initWithFocusedViewRect:NSMakeRect (0.0f, 0.0f, POTWide, POTHigh)];
		[image unlockFocus];
		
		data = (unsigned char*) [bitmap bitmapData];  //Use the same buffer to improve the performance.
		
		NSUInteger textureSize = POTWide*POTHigh*4;
		
		unsigned char* dataNew = new unsigned char[textureSize];
		if (dataNew) {
			memcpy(dataNew, data, textureSize);
			// output params
			pInfo->width = POTWide;
			pInfo->height = POTHigh;
			pInfo->data = dataNew;
			pInfo->hasAlpha = true;
			pInfo->isPremultipliedAlpha = true;
			pInfo->bitsPerComponent = 8;
			bRet = true;
		}
		[bitmap release];
		[image release];
	} while (0);
    return bRet;
}


static bool _enabledScale = true;

bool isFileExists(const char* szFilePath);

bool isFileExists(const char* szFilePath)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	//TCHAR dirpath[MAX_PATH];
	//MultiByteToWideChar(936,0,szFilePath,-1,dirpath,sizeof(dirpath));
	DWORD dwFileAttr = GetFileAttributesA(szFilePath);
	if (INVALID_FILE_ATTRIBUTES == dwFileAttr
		|| (dwFileAttr&FILE_ATTRIBUTE_DIRECTORY))	{
		return false;
	}		
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	bool bFind = true;
	do 
	{
		struct stat buf;
		int n = stat(szFilePath, &buf);
		if ((0 != n)
			|| !(buf.st_mode&S_IFMT))	
		{
			bFind = false;
		}
	} while (0);
	if (!bFind)
	{
		//std::string strFilenName = s_strRelativePath + szFilePath;
		unsigned char * pBuffer = NULL;
		unzFile pFile = NULL;
		unsigned long pSize = 0;
		
		do 
		{
			pFile = unzOpen(s_strAndroidPackagePath.c_str());
			if(!pFile)break;
			
			int nRet = unzLocateFile(pFile, szFilePath, 1);
			if(UNZ_OK != nRet)
				bFind = false;
			else
				bFind = true;
		} while (0);
		
		if (pFile)
		{
			unzClose(pFile);
		}
	}
	
	return bFind;
#else
	struct stat buf;
	int n = stat(szFilePath, &buf);
	if ((0 != n)
		|| !(buf.st_mode&S_IFMT))	{
		return false;
	}		
	
#endif
	return true;
}

Image::Image()
: _width(0)
, _height(0)
, _bitsPerComponent(0)
, _data(0)
, _hasAlpha(false)
, _preMulti(false)
{
    
}

Image::~Image()
{
    CC_SAFE_DELETE_ARRAY(_data);
}

bool Image::initWithImageFile(const char * strPath, Format eImgFmt/* = eFmtPng*/)
{
    std::string strTemp = FileUtils::getInstance()->fullPathForFilename(strPath);
	if (_enabledScale)
	{
		if (!isFileExists(strTemp.c_str()))
		{
			if (strTemp.rfind("@2x") == std::string::npos)
			{
				int t = strTemp.rfind(".");
				if (t != std::string::npos)
				{
					strTemp.insert(t, "@2x");
				}
/*				Size size = Director::getInstance()->getWinSize();		
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
				_scaleX = size.width/800.0f;
				_scaleY = size.height/480.0f;
	#else
				_scaleX = size.width/960.0f;
				_scaleY = size.height/640.0f;
				
	#endif
*/
			}
		}    
		else
		{
//			_scaleX = 1.0;
//			_scaleY = 1.0;
		}
	}
	
//	FileData tempData(strTemp.c_str(), "rb");			
//	return initWithImageData(tempData.getBuffer(), tempData.getSize(), eImgFmt);

	unsigned long fileSize = 0;
	unsigned char* pFileData = FileUtils::getInstance()->getFileData(strTemp.c_str(), "rb", &fileSize);
	bool ret = initWithImageData(pFileData, fileSize, eImgFmt);
	delete []pFileData;
	return ret;
}

bool Image::initWithImageFileThreadSafe(const char *fullpath, Format imageType)
{
    /*
     * FileUtils::fullPathFromRelativePath() is not thread-safe, it use autorelease().
     */
    bool bRet = false;
    unsigned long nSize = 0;
    unsigned char* pBuffer = FileUtils::getInstance()->getFileData(fullpath, "rb", &nSize);
    if (pBuffer != NULL && nSize > 0)
    {
        bRet = initWithImageData(pBuffer, nSize, imageType);
    }
    CC_SAFE_DELETE_ARRAY(pBuffer);
    return bRet;
}



/*
// please uncomment this and integrate it somehow if you know what your doing, thanks
bool Image::potImageData(unsigned int POTWide, unsigned int POTHigh)
{
	unsigned char*			data = NULL;
	unsigned char*			tempData =NULL;
	unsigned int*				inPixel32 = NULL;
	unsigned short*			outPixel16 = NULL;
	bool					hasAlpha;
	Texture2D::PixelFormat	pixelFormat;
	
	hasAlpha = this->hasAlpha();
	
	size_t bpp = this->getBitsPerComponent();
	
    // compute pixel format
	if(hasAlpha)
	{
		pixelFormat = Texture2D::defaultAlphaPixelFormat();
	}
	else
	{
		if (bpp >= 8)
		{
			pixelFormat = Texture2D::PixelFormat::RGB888;
		}
		else
		{
			CCLOG("cocos2d: Texture2D: Using RGB565 texture since image has no alpha");
			pixelFormat = Texture2D::PixelFormat::RGB565;
		}
	}
	
	switch(pixelFormat) {          
		case Texture2D::PixelFormat::RGBA8888:
		case Texture2D::PixelFormat::RGBA4444:
		case Texture2D::PixelFormat::RGB5A1:
		case Texture2D::PixelFormat::RGB565:
		case Texture2D::PixelFormat::A8:
			tempData = (unsigned char*)(this->getData());
			CCASSERT(tempData != NULL, "NULL image data.");
			
			if(this->getWidth() == (short)POTWide && this->getHeight() == (short)POTHigh)
			{
				data = new unsigned char[POTHigh * POTWide * 4];
				memcpy(data, tempData, POTHigh * POTWide * 4);
			}
			else
			{
				data = new unsigned char[POTHigh * POTWide * 4];
				memset(data, 0, POTHigh * POTWide * 4);
				
				unsigned char* pPixelData = (unsigned char*) tempData;
				unsigned char* pTargetData = (unsigned char*) data;
				
				int imageHeight = this->getHeight();
				for(int y = 0; y < imageHeight; ++y)
				{
					memcpy(pTargetData+POTWide*4*y, pPixelData+(this->getWidth())*4*y, (this->getWidth())*4);
				}
			}
			
			break;    
		case Texture2D::PixelFormat::RGB888:
			tempData = (unsigned char*)(this->getData());
			CCASSERT(tempData != NULL, "NULL image data.");
			if(this->getWidth() == (short)POTWide && this->getHeight() == (short)POTHigh)
			{
				data = new unsigned char[POTHigh * POTWide * 3];
				memcpy(data, tempData, POTHigh * POTWide * 3);
			}
			else
			{
				data = new unsigned char[POTHigh * POTWide * 3];
				memset(data, 0, POTHigh * POTWide * 3);
				
				unsigned char* pPixelData = (unsigned char*) tempData;
				unsigned char* pTargetData = (unsigned char*) data;
				
				int imageHeight = this->getHeight();
				for(int y = 0; y < imageHeight; ++y)
				{
					memcpy(pTargetData+POTWide*3*y, pPixelData+(this->getWidth())*3*y, (this->getWidth())*3);
				}
			}
			break;   
		default:
			CCASSERT(0, "Invalid pixel format");
	}
	
	// Repack the pixel data into the right format
	
	if(pixelFormat == Texture2D::PixelFormat::RGB565) {
		//Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGGBBBBB"
		tempData = new unsigned char[POTHigh * POTWide * 2];
		inPixel32 = (unsigned int*)data;
		outPixel16 = (unsigned short*)tempData;
		
		unsigned int length = POTWide * POTHigh;
		for(unsigned int i = 0; i < length; ++i, ++inPixel32)
		{
			*outPixel16++ = 
			((((*inPixel32 >> 0) & 0xFF) >> 3) << 11) |  // R
			((((*inPixel32 >> 8) & 0xFF) >> 2) << 5) |   // G
			((((*inPixel32 >> 16) & 0xFF) >> 3) << 0);   // B
		}
		
		delete [] data;
		data = tempData;
	}
	else if (pixelFormat == Texture2D::PixelFormat::RGBA4444) {
		//Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRGGGGBBBBAAAA"
		tempData = new unsigned char[POTHigh * POTWide * 2];
		inPixel32 = (unsigned int*)data;
		outPixel16 = (unsigned short*)tempData;
		
		unsigned int length = POTWide * POTHigh;
		for(unsigned int i = 0; i < length; ++i, ++inPixel32)
		{
			*outPixel16++ = 
			((((*inPixel32 >> 0) & 0xFF) >> 4) << 12) | // R
			((((*inPixel32 >> 8) & 0xFF) >> 4) << 8) | // G
			((((*inPixel32 >> 16) & 0xFF) >> 4) << 4) | // B
			((((*inPixel32 >> 24) & 0xFF) >> 4) << 0); // A
		}
		
		delete [] data;
		data = tempData;
	}
	else if (pixelFormat == Texture2D::PixelFormat::RGB5A1) {
		//Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGBBBBBA"
		tempData = new unsigned char[POTHigh * POTWide * 2];
		inPixel32 = (unsigned int*)data;
		outPixel16 = (unsigned short*)tempData;
		
		unsigned int length = POTWide * POTHigh;
		for(unsigned int i = 0; i < length; ++i, ++inPixel32)
		{
			*outPixel16++ = 
			((((*inPixel32 >> 0) & 0xFF) >> 3) << 11) | // R
			((((*inPixel32 >> 8) & 0xFF) >> 3) << 6) | // G
			((((*inPixel32 >> 16) & 0xFF) >> 3) << 1) | // B
			((((*inPixel32 >> 24) & 0xFF) >> 7) << 0); // A
		}
		
		delete []data;
		data = tempData;
	}
	else if (pixelFormat == Texture2D::PixelFormat::A8)
	{
		// fix me, how to convert to A8
		pixelFormat = Texture2D::PixelFormat::RGBA8888;
		
		//
		//The code can not work, how to convert to A8?
		//
		//tempData = new unsigned char[POTHigh * POTWide];
		//inPixel32 = (unsigned int*)data;
		//outPixel8 = tempData;
		 
		//unsigned int length = POTWide * POTHigh;
		//for(unsigned int i = 0; i < length; ++i, ++inPixel32)
		//{
		//    *outPixel8++ = (*inPixel32 >> 24) & 0xFF;
		//}
		 
		//delete []data;
		//data = tempData;
		 
	}
	
	if (data)
	{
		CC_SAFE_DELETE_ARRAY(_data);
		_data = data;
	}
	return true;	
}
*/

//bool Image::initWithImageData(void * pData, int nDataLen, EImageFormat eFmt/* = eSrcFmtPng*/)
bool Image::initWithImageData(void * pData, 
                           int nDataLen, 
                           Format eFmt,
                           int nWidth,
                           int nHeight,
                           int nBitsPerComponent)
{
    bool bRet = false;
    tImageInfo info = {0};
    do 
    {
        CC_BREAK_IF(! pData || nDataLen <= 0);
        
        if (eFmt == Format::RAW_DATA)
        {
            bRet = initWithRawData(pData, nDataLen, nWidth, nHeight, nBitsPerComponent, false);
        }
        else if (eFmt == Image::Format::WEBP)
        {
            bRet = initWithWebpData(pData, nDataLen);
        }
        else
        {
            bRet = _initWithData(pData, nDataLen, &info, 1.0f, 1.0f);//_scaleX, _scaleY);
            if (bRet)
            {
                _height = (short)info.height;
                _width = (short)info.width;
                _bitsPerComponent = info.bitsPerComponent;
                if (eFmt == Format::JPG)
                {
                    _hasAlpha = true;
                    _preMulti = false;
                }
                else
                {
                    _hasAlpha = info.hasAlpha;
                    _preMulti = info.isPremultipliedAlpha;
                }
                _data = info.data;
            }
        }
    } while (0);
	
    return bRet;
}

bool Image::initWithRawData(void *pData, int nDatalen, int nWidth, int nHeight, int nBitsPerComponent, bool bPreMulti)
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(0 == nWidth || 0 == nHeight);
        
        _bitsPerComponent = nBitsPerComponent;
        _height   = (short)nHeight;
        _width    = (short)nWidth;
        _hasAlpha = true;
        
        // only RGBA8888 supported
        int nBytesPerComponent = 4;
        int nSize = nHeight * nWidth * nBytesPerComponent;
        _data = new unsigned char[nSize];
        CC_BREAK_IF(! _data);
        memcpy(_data, pData, nSize);
        
        bRet = true;
    } while (0);
    return bRet;
}

bool Image::initWithString(
	const char *    pText, 
	int             nWidth, 
	int             nHeight,
	TextAlign      eAlignMask,
	const char *    pFontName,
	int             nSize)
{
    tImageInfo info = {0};
    info.width = nWidth;
    info.height = nHeight;
	
    if (! _initWithString(pText, eAlignMask, pFontName, nSize, &info, NULL)) //pStrokeColor))
    {
        return false;
    }
    _height = (short)info.height;
    _width = (short)info.width;
    _bitsPerComponent = info.bitsPerComponent;
    _hasAlpha = info.hasAlpha;
    _preMulti = info.isPremultipliedAlpha;
	if (_data) {
		CC_SAFE_DELETE_ARRAY(_data);
	}
    _data = info.data;

    return true;
}

bool Image::saveToFile(const char *pszFilePath, bool bIsToRGB)
{
	assert(false);
	return false;
}



NS_CC_END

