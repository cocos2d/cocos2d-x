/****************************************************************************
Copyright (c) Microsoft Open Technologies, Inc.  All rights reserved.

The MIT License (MIT)

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

Based upon code from the DirectX Tool Kit by Microsoft Corporation, 
obtained from https://directxtk.codeplex.com
****************************************************************************/

#ifndef __WIC_IMAGE_LOADER_H__
#define __WIC_IMAGE_LOADER_H__

#include "base/ccConfig.h"


#if defined(CC_USE_WIC)

#include <memory>
#include <string>
#include <wincodec.h>
#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN


	typedef const unsigned char* ImageBlob;

struct WICConvert
{
	WICPixelFormatGUID source;
	WICPixelFormatGUID target;
};

class WICImageLoader
{
public:

	WICImageLoader();
	~WICImageLoader();

	int getWidth();
	int getHeight();
	int getImageDataSize();
	WICPixelFormatGUID getPixelFormat();
	int getImageData(ImageBlob rawData, size_t dataLen);
	bool decodeImageData(ImageBlob data, size_t dataLen);
    bool encodeImageData(std::string path, const unsigned char* data, size_t dataLen, WICPixelFormatGUID pixelFormat, int width, int height, GUID containerFormat);

protected:
	bool processImage(IWICBitmapDecoder* decoder);
	size_t getBitsPerPixel(WICPixelFormatGUID format); 
	HRESULT convertFormatIfRequired(IWICBitmapFrameDecode* pFrame, IWICFormatConverter** ppConv);

	static IWICImagingFactory* getWICFactory();

private:
	int _height;
	int _width;
	size_t _dataLen;
	UINT _bpp;
	WICPixelFormatGUID _format;
	BYTE* _data;


	static IWICImagingFactory* _wicFactory;
};

template<typename T>
void SafeRelease(T **ppObj)
{
	if(*ppObj != NULL)
	{
		(*ppObj)->Release();
		*ppObj = NULL;
	}
}


NS_CC_END

#endif
#endif    // #ifndef __WIC_IMAGE_LOADER_H__

