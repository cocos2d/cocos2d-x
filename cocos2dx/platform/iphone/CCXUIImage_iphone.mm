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
#include "CCXUIImage_iphone.h"
#include "CCXFileUtils.h"
#include "CCConfiguration.h"
#include "CCXBitmapDC.h"


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

static bool static_initPremultipliedATextureWithImage(CGImageRef image, NSUInteger POTWide, NSUInteger POTHigh, tImageInfo *pImageInfo)
{
	NSUInteger			i;
	CGContextRef		context = nil;
	unsigned char*		data = nil;;
	CGColorSpaceRef		colorSpace;
	unsigned char*		tempData;
	unsigned int*		inPixel32;
	unsigned short*		outPixel16;
	bool				hasAlpha;
	CGImageAlphaInfo	info;
	CGSize				imageSize;
	cocos2d::CCTexture2DPixelFormat	pixelFormat;
	
	info = CGImageGetAlphaInfo(image);
	hasAlpha = ((info == kCGImageAlphaPremultipliedLast) || (info == kCGImageAlphaPremultipliedFirst) || (info == kCGImageAlphaLast) || (info == kCGImageAlphaFirst) ? YES : NO);
	
	size_t bpp = CGImageGetBitsPerComponent(image);
	colorSpace = CGImageGetColorSpace(image);
	
	if(colorSpace) {
		if(hasAlpha || bpp >= 8)
			pixelFormat = cocos2d::kCCTexture2DPixelFormat_Default;
		else {
			//CCLOG(@"cocos2d: CCTexture2D: Using RGB565 texture since image has no alpha");
			pixelFormat = cocos2d::kCCTexture2DPixelFormat_RGB565;
		}
	} else  {
		// NOTE: No colorspace means a mask image
		//CCLOG(@"cocos2d: CCTexture2D: Using A8 texture since image is a mask");
		pixelFormat = cocos2d::kCCTexture2DPixelFormat_A8;
	}
	
	imageSize.width = CGImageGetWidth(image);
	imageSize.height = CGImageGetHeight(image);
	//imageSize = CGSizeMake(CGImageGetWidth(image), CGImageGetHeight(image));
	
	// Create the bitmap graphics context
	
	switch(pixelFormat) {          
		case cocos2d::kCCTexture2DPixelFormat_RGBA8888:
		case cocos2d::kCCTexture2DPixelFormat_RGBA4444:
		case cocos2d::kCCTexture2DPixelFormat_RGB5A1:
			colorSpace = CGColorSpaceCreateDeviceRGB();
			//data = malloc(POTHigh * POTWide * 4);
			data = new unsigned char[POTHigh * POTWide * 4];
			info = hasAlpha ? kCGImageAlphaPremultipliedLast : kCGImageAlphaNoneSkipLast; 
			// info = kCGImageAlphaPremultipliedLast;  // issue #886. This patch breaks BMP images.
			context = CGBitmapContextCreate(data, POTWide, POTHigh, 8, 4 * POTWide, colorSpace, info | kCGBitmapByteOrder32Big);				
			CGColorSpaceRelease(colorSpace);
			break;
			
		case cocos2d::kCCTexture2DPixelFormat_RGB565:
			colorSpace = CGColorSpaceCreateDeviceRGB();
			//data = malloc(POTHigh * POTWide * 4);
			data = new unsigned char[POTHigh * POTWide * 4];
			info = kCGImageAlphaNoneSkipLast;
			context = CGBitmapContextCreate(data, POTWide, POTHigh, 8, 4 * POTWide, colorSpace, info | kCGBitmapByteOrder32Big);
			CGColorSpaceRelease(colorSpace);
			break;
		case cocos2d::kCCTexture2DPixelFormat_A8:
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
	
	if(pixelFormat == cocos2d::kCCTexture2DPixelFormat_RGB565) {
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
	else if (pixelFormat == cocos2d::kCCTexture2DPixelFormat_RGBA4444) {
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
	else if (pixelFormat == cocos2d::kCCTexture2DPixelFormat_RGB5A1) {
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

static bool static_initWithImage(CGImageRef CGImage, tImageInfo *pImageinfo)
{
	NSUInteger				POTWide, POTHigh;
	
	if(CGImage == NULL) {
		//CCLOG(@"cocos2d: CCTexture2D. Can't create Texture. UIImage is nil");
		return false;
	}
	
	//CCConfiguration *conf = [CCConfiguration sharedConfiguration];
	cocos2d::CCConfiguration *conf = cocos2d::CCConfiguration::sharedConfiguration();
    
	POTWide = CGImageGetWidth(CGImage);
	POTHigh = CGImageGetHeight(CGImage);
	
	unsigned maxTextureSize = conf->getMaxTextureSize();
	if( POTHigh > maxTextureSize || POTWide > maxTextureSize ) {
		return false;
	}
	
	// always load premultiplied images
	static_initPremultipliedATextureWithImage(CGImage, POTWide, POTHigh, pImageinfo);
	
	return true;
}

static bool static_initWithData(void * pBuffer, int length, tImageInfo *pImageinfo)
{
	bool ret = false;
	
	if (pBuffer) {
		CGImageRef				CGImage;
		NSData                  *data;
		
		data = [NSData dataWithBytes:pBuffer length:length];
		CGImage = [[UIImage imageWithData:data] CGImage];
		
		ret = static_initWithImage(CGImage, pImageinfo);
	}
	
	return ret;
}

static bool static_initWithFile(const char* path, tImageInfo *pImageinfo)
{
	CGImageRef				CGImage;	
	UIImage					*jpg;
	UIImage					*png;
	bool                    ret;
	
	// convert jpg to png before loading the texture

	NSString *fullPath = [NSString stringWithUTF8String:path];
	jpg = [[UIImage alloc] initWithContentsOfFile: fullPath];
	png = [[UIImage alloc] initWithData:UIImagePNGRepresentation(jpg)];
	CGImage = png.CGImage;	
	
	ret = static_initWithImage(CGImage, pImageinfo);
	
	[png release];
	[jpg release];
	
	return ret;
}


//using namespace ImageToolKit;
using namespace std;
namespace   cocos2d {

bool UIImage::s_bPopupNotify = false;

UIImage::UIImage(void)
{
	m_imageInfo.hasAlpha = false;
	m_imageInfo.isPremultipliedAlpha = false;
	m_imageInfo.height = 0;
	m_imageInfo.width = 0;
	m_imageInfo.data = NULL;
	m_imageInfo.bitsPerComponent = 0;
}

UIImage::UIImage(CCXBitmapDC * pBmpDC)
{
    do 
	{
		CCX_BREAK_IF(! pBmpDC);
		
		// init imageinfo
		int nWidth	= pBmpDC->getWidth();
		int nHeight	= pBmpDC->getHeight();
		CCX_BREAK_IF(nWidth <= 0 || nHeight <= 0);

		int nLen = nWidth * nHeight * 4;
		m_imageInfo.data = new unsigned char [nLen];
		CCX_BREAK_IF(! m_imageInfo.data);
		memcpy(m_imageInfo.data, pBmpDC->getData(), nLen);

		m_imageInfo.height		= nHeight;
		m_imageInfo.width		= nWidth;
		m_imageInfo.hasAlpha	= true;

		m_imageInfo.isPremultipliedAlpha = true;
		m_imageInfo.bitsPerComponent = 8;
	} while (0);
}

UIImage::~UIImage(void)
{
	if (m_imageInfo.data)
	{
		delete []m_imageInfo.data;
	}
}

bool UIImage::initWithContentsOfFile(const string &strPath, tImageFormat imageType)
{
	bool bRet = false;

	switch (imageType)
	{
	case kCCImageFormatPNG:
	case kCCImageFormatJPG:
		bRet = static_initWithFile(strPath.c_str(), &m_imageInfo);
		break;
	default:
		// unsupported image type
		bRet = false;
		break;
	}

	return bRet;
}

unsigned int UIImage::width(void)
{
	return m_imageInfo.width;
}

unsigned int UIImage::height(void)
{
	return m_imageInfo.height;
}

bool UIImage::isAlphaPixelFormat(void)
{
	return m_imageInfo.hasAlpha;
}

// now, uphone only support premultiplied data
// so, we only return true
bool UIImage::isPremultipliedAlpha(void)
{
	return m_imageInfo.isPremultipliedAlpha;
}

// compute how many bits every color component 
int UIImage::CGImageGetBitsPerComponent(void)
{
	return m_imageInfo.bitsPerComponent;
}

// now we only support RGBA8888 or RGB888
// so it has color space
int UIImage::CGImageGetColorSpace(void)
{
	return 1;
}

unsigned char* UIImage::getData(void)
{
	return m_imageInfo.data;
}

bool UIImage::save(const std::string &strFileName, int nFormat)
{
	/// @todo uiimage::save
	return false;
}
bool UIImage::initWithData(unsigned char *pBuffer, int nLength)
{
	return static_initWithData(pBuffer, nLength, &m_imageInfo);
}

bool UIImage::initWithBuffer(int tx, int ty, unsigned char *pBuffer)
{
	/// @todo
	return false;
}

void UIImage::setIsPopupNotify(bool bNotify)
{
    s_bPopupNotify = bNotify;
}

bool UIImage::getIsPopupNotify()
{
    return s_bPopupNotify;
}

}//namespace   cocos2d 
