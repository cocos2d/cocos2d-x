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

//#include <ImageToolKit/IT_ImageLoader.h> 
#include <TG3.h>
#include "png.h"

//using namespace ImageToolKit;
using namespace std;
namespace   cocos2d {

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

    bool bRet = false;
	do
	{
        // load the image
/************************************************************************/
/*                   Use ImageToolKit load image                        */
// 	    ImageLoader obImgLoader;
//      Image       obImg;
// 	    TUChar *pszPath = new TUChar[strPath.size() + 1];
//      TUString::StrGBToUnicode(pszPath, (const Char *) strPath.c_str());
// 		if (! obImgLoader.loadImage(obImg, pszPath, IT_LOAD_FMT_UNKNOWN))
// 		{
// 			bRet = false;
// 			break;
// 		}
// 
// 		// init bitmap
// 		m_pBitmap = (TBitmap *) obImg.GetTBitmap();
// 		m_pBitmap = m_pBitmap->DupBitmapTo32();
//      delete[] pszPath;
/************************************************************************/

        // use libpng load image
        bRet = loadPng(strPath.c_str());

        // check if the loading action is successful
        if (! bRet)
        {
            break;
        }

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

// now, uphone only support premultiplied data
// so, we only return true
bool UIImage::isPremultipliedAlpha(void)
{
	return true;
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
		TBitmap *pBitmap;
		int nW;
		int nH;
		UINT8 uR;
		UINT8 uB;
		
        if (m_pBitmap == NULL)
        {
            break;
        }

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

		// translate BGRA to RGBA
        for (int i = 0; i < nW; ++i)
		{
			for (int j = 0; j < nH; ++j)
			{
				int baseAddr = (j * nW + i) * 4;

				uB = pBufferRet[baseAddr];
				uR = pBufferRet[baseAddr + 2];

				pBufferRet[baseAddr] = uR;
				pBufferRet[baseAddr + 2] = uB;
			}
		}

		pBitmap->Destroy();
	} while(0);
	
	return pBufferRet;
}

bool UIImage::loadPng(const char* strFileName)
{
    char                header[8]; 
    FILE                *fp;
    png_structp         png_ptr;
    png_infop           info_ptr;
    UInt32               * pBmpData;
    Int32               pos;
    Int32               bitDepth;
    png_uint_32         width;
    png_uint_32         height;
    Int32               interlaceType;
    png_bytep           * rowPointers;
    Int32               colorType;

    pos = 0;
    fp = NULL;
    pBmpData = NULL;

    // open file
    fp = fopen(strFileName, "rb");
    if (!fp)
        return false;

    // read 8 bytes from the beginning of the file
    fread(header, 1, 8, fp); 

    // close the file if it's not a png
    if (png_sig_cmp((png_bytep)header, 0, 8))
    {
        fclose(fp);
        return false;
    }

    // init png_struct
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
    {
        fclose(fp);
        return false;
    }   

    // init png_info
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        fclose(fp);
        return false;
    }

    // if something wrong,close file and return
    if (setjmp(png_jmpbuf(png_ptr)))
    {       
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        png_destroy_info_struct(png_ptr, &info_ptr);
        fclose(fp);
        return false;
    }

    // conect the file pointer to libpng
    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    // read the data of the file
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);

    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bitDepth, &colorType,
        &interlaceType, NULL, NULL);

    if (setjmp(png_jmpbuf(png_ptr)))
    {     
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        png_destroy_info_struct(png_ptr, &info_ptr);
        fclose(fp);
        return false;
    }

    // get the image file data
    rowPointers = png_get_rows(png_ptr, info_ptr);

    // Create a bitmap of 32bits depth
    if(!m_pBitmap)
    {
        m_pBitmap = TBitmap::Create(width, height, 32);
    }
    if(!m_pBitmap)
    {
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        png_destroy_info_struct(png_ptr, &info_ptr);
        fclose(fp);
        return false; 
    }

    // Alpha data
    pBmpData = reinterpret_cast< UInt32* >( m_pBitmap->GetDataPtr() );

    if( info_ptr->color_type & PNG_COLOR_MASK_ALPHA )    {
        for(unsigned int i = 0; i < height; i++)
        {
            for(unsigned int j = 0; j < (4 * width); j += 4)
            {
                *pBmpData++ = RGBA( rowPointers[i][j], rowPointers[i][j + 1], 
                    rowPointers[i][j + 2], rowPointers[i][j + 3] );
            }
        }
    }
    else
    {
        for(unsigned int i = 0; i < height; i++)
        {
            for(unsigned int j = 0; j < (3 * width); j += 3)
            {
                *pBmpData++ = RGB( rowPointers[i][j], rowPointers[i][j + 1], 
                    rowPointers[i][j + 2] );
            }
        }
    }

    // release
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    png_destroy_info_struct(png_ptr, &info_ptr);
    fclose(fp);

    return true;
}
bool UIImage::save(const std::string &strFileName, int nFormat)
{
	/// @todo uiimage::save
	return false;
}
bool UIImage::initWithBuffer(int nX, int nY, unsigned char *pBuffer)
{
	/// @todo uiimage::initwithbuffer
	return false;
}
}
}//namespace   cocos2d 
