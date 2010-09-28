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

	/** load the image from the specified path 
	    @imageType: the type of image, now only support tow types
		            kImageFormatPNG -> png
					kImageFormatJPG -> jpeg
	 */
	bool initWithContentsOfFile(const std::string &strPath, tImageFormat imageType = kImageFormatPNG);
	bool initWithData(unsigned char *pBuffer, int nLength);
	bool initWithBuffer(int tx, int ty, unsigned char *pBuffer);

	bool save(const std::string &strFileName, int nFormat);

	/** get the image width */
	unsigned int width(void);
	/** get the image height */
	unsigned int height(void);

	/** whether or not the image has alpha channel */
	bool isAlphaPixelFormat(void);
	/** whether or not the r, g, b channels are premultiplied by alpha channel */
	bool isPremultipliedAlpha(void);

	/** get the bit depth of each color channel */
	int CGImageGetBitsPerComponent(void);
	/** the source color space for the image, or 0 if the image is an image mask */
	int CGImageGetColorSpace(void);

	/** get the image data */
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
