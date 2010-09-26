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

#ifndef __PLATFORM_UPHONE_UIIMAGE_H__
#define __PLATFORM_UPHONE_UIIMAGE_H__

#include <string>
#include "ccxCommon.h"
#include "CCRenderTexture.h"

class TBitmap;
namespace   cocos2d {

// typedef enum {
// 	kImageTypePNG = 0,
// 	kImageTypeJPG = 1,
// } CCXImageType;

typedef struct
{
	unsigned int	height;
	unsigned int	width;
	int				bitsPerComponent;
	bool            hasAlpha;
	bool			isPremultipliedAlpha;
	unsigned char   *data;
} tImageInfo;

class CCX_DLL UIImage
{
public:
	UIImage(void);
	UIImage(TBitmap *bitmap);
	
	UIImage(int nX, int nY, void *buffer);
	~UIImage(void);

	bool initWithContentsOfFile(const std::string &strPath, tImageFormat imageType = kImageFormatPNG);
	bool initWithData(unsigned char *pBuffer, int nLength);
	bool initWithBuffer(int tx, int ty, unsigned char *pBuffer);
//	bool initWithCGImage(CGImageRef pCGImage);

	bool save(const std::string &strFileName, int nFormat);

	unsigned int width(void);
	unsigned int height(void);

	bool isAlphaPixelFormat(void);
	bool isPremultipliedAlpha(void);

	int CGImageGetBitsPerComponent(void);
	int CGImageGetColorSpace(void);

	// convert the bitmap to 256 pixel format, and every component is 8 bits
	unsigned char* getData(void);

private:
    bool loadPng(const char* strFileName);
	bool loadPngFromStream(unsigned char *data, int nLength);
	bool loadJpg(const char *strFileName);

private:
	TBitmap *m_pBitmap;
	tImageInfo m_imageInfo;
};
}//namespace   cocos2d 

#endif // __PLATFORM_UPHONE_UIIMAGE_H__
