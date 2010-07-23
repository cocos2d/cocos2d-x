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
#include "Cocos2dTypes.h"

class TBitmap;

class UIImage
{
public:
	UIImage(void);
	UIImage(INT32 nX, INT32 nY, void *buffer);
	~UIImage(void);

	bool initWithContentsOfFile(const std::string &strPath);
	bool initWithBuffer(INT32 nX, INT32 nY, unsigned char *pBuffer);
//	bool initWithCGImage(CGImageRef pCGImage);

	bool save(const std::string &strFileName, INT32 nFormat);

	UINT32 width(void);
	UINT32 height(void);

	bool isAlphaPixelFormat(void);

	INT32 CGImageGetBitsPerComponent(void);
	INT32 CGImageGetColorSpace(void);
private:
	TBitmap *m_pBitmap;
};

#endif // __PLATFORM_UPHONE_UIIMAGE_H__
