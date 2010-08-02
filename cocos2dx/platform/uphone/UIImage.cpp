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

#include "UIImage.h"

#include <ImageToolKit/IT_ImageLoader.h> 
#include <TG3.h>

using namespace ImageToolKit;
using namespace std;

UIImage::UIImage(void)
{
	m_pBitmap = NULL;
}

UIImage::UIImage(int nX, int nY, void *buffer)
{

}

UIImage::~UIImage(void)
{
	if (m_pBitmap)
	{
		m_pBitmap->Destroy();
	}
}

bool UIImage::initWithContentsOfFile(const string &strPath)
{
	if (m_pBitmap)
	{
		return false;
	}

	// load the image

	ImageLoader obImgLoader;
    Image       obImg;
	TUChar *pszPath = new TUChar[strPath.size() + 1];
    TUString::StrGBToUnicode(pszPath, (const Char *) strPath.c_str());
    bool bRet = false;

	do
	{
		// check if the loading action is successful
		if (! obImgLoader.loadImage(obImg, pszPath, IT_LOAD_FMT_UNKNOWN))
		{
			bRet = false;
			break;
		}

		// init bitmap
		m_pBitmap = (TBitmap *) obImg.GetTBitmap();
		m_pBitmap = m_pBitmap->DupBitmapTo32();

		// the hight is 0??
		if (m_pBitmap && m_pBitmap->GetHeight() == 0)
		{
			m_pBitmap->Destroy();
			m_pBitmap = NULL;

			bRet = false;
			break;
		}

		if (m_pBitmap)
		{
			bRet = true;
		}
		else
		{
			bRet = false;
		}
	} while(0);

	delete[] pszPath;
	return bRet;
}

unsigned int UIImage::width(void)
{
	if (! m_pBitmap)
	{
		return 0;
	}

	return m_pBitmap->GetWidth();
}

unsigned int UIImage::height(void)
{
	if (! m_pBitmap)
	{
		return 0;
	}

	return m_pBitmap->GetHeight();
}

bool UIImage::isAlphaPixelFormat(void)
{
	if (! m_pBitmap)
	{
		return false;
	}

	bool bRet;
	if (m_pBitmap->HasAlphaData())
	{
        bRet = true;
	}
	else
	{
		bRet = false;
	}

	return bRet;
}

// compute how many bits every color component 
int UIImage::CGImageGetBitsPerComponent(void)
{
	if (! m_pBitmap)
	{
		return 0;
	}

	int nRet = 0;
	int nRowBytes = m_pBitmap->GetRowBytes();
	if (m_pBitmap->HasAlphaData())
	{
		// it has alpha data, so
		// nRawBytes / 4 -> the bytes of per component
		nRet = nRowBytes / 4 * 8;
	}
	else
	{
		// have not alpha data
		// nRawBytes / 3 -> the bytes of per component
		nRet = nRowBytes / 3 * 8;
	}

	return nRet;
}

// 0 -> it is a mask
// 1 -> other
int UIImage::CGImageGetColorSpace(void)
{
	int nRet = 1;

	if (m_pBitmap->GetRowBytes() == 1)
	{
		nRet = 0;
	}

	return nRet;
}

UINT8* UIImage::getRGBA8888Data(void)
{
	UINT8 *pBufferRet = NULL;

	do {
		const TBitmap *pBitmap;
		int nW;
		int nH;
		
        // convert to RGBA8888 format
		pBitmap = m_pBitmap->DupBitmapTo32();
		if (pBitmap == NULL)
		{
			break;
		}

		// compute width and height
		nW = pBitmap->GetWidth();
		nH = pBitmap->GetHeight();

		// alloc memory and store the bitmap data
		pBufferRet = new UINT8[nW * nH * 4];
		memcpy(pBufferRet, pBitmap->GetDataPtr(), nW * nH * 4);
	} while(0);

	return pBufferRet;
}
