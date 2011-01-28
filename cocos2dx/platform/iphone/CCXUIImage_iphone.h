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

#ifndef __PLATFORM_IPHONE_UIIMAGE_H__
#define __PLATFORM_IPHONE_UIIMAGE_H__

#include <string>
#include "ccxCommon.h"
#include "CCRenderTexture.h"

struct AppResourceEntry;

typedef struct
{
	unsigned int	height;
	unsigned int	width;
	int				bitsPerComponent;
	bool            hasAlpha;
	bool			isPremultipliedAlpha;
	unsigned char   *data;
} tImageInfo;

namespace   cocos2d {
class CCXBitmapDC;

/**
@brief image toolkits
*/
class CCX_DLL UIImage
{
public:
	UIImage(void);
	UIImage(CCXBitmapDC * pBmpDC);
	
	~UIImage(void);

	/** 
	Load the image from the specified path. 
	@param strPath   the absolute file path
	@param imageType the type of image, now only support tow types:
		              - kImageFormatPNG -> png
					  - kImageFormatJPG -> jpeg
    @return  true if load correctly
	 */
	bool initWithContentsOfFile(const std::string &strPath, tImageFormat imageType = kCCImageFormatPNG);
	/**
	Load image from stream buffer.
	@param pBuffer  stream buffer that hold the image data
	@param nLength  the length of data(managed in byte)
	@return true if load correctly
	*/
	bool initWithData(unsigned char *pBuffer, int nLength);

	/// @cond
	bool initWithBuffer(int tx, int ty, unsigned char *pBuffer);
	bool save(const std::string &strFileName, int nFormat);
	/// @endcond

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

    /**
    @brief Set/Get whether pop-up a message box when the image load failed
    @todo not implement now
    */
    static void setIsPopupNotify(bool bNotify);
    static bool getIsPopupNotify();

private:
	tImageInfo m_imageInfo;
	static bool s_bPopupNotify;
};
}//namespace   cocos2d 

#endif // __PLATFORM_IPHONE_UIIMAGE_H__
