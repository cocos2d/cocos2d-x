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

#include "CCXUIImage_uphone.h"

//#include <ImageToolKit/IT_ImageLoader.h> 
#include <TG3.h>
#include "png.h"

//using namespace ImageToolKit;
using namespace std;
namespace   cocos2d {

#ifdef _TRANZDA_VM_
#define CCX_RGB(vr,vg,vb) \
	    (ColorRefType)(((UInt32)(UInt8)(vb) << 16) | ((UInt32)(UInt8)(vg) << 8) | (UInt32)(UInt8)(vr) | ((UInt32)0xffL << 24))

#define CCX_RGB_APLHA(vr, vg, vb, va) \
	(ColorRefType)(((UInt32)((UInt8)(vr) * ((UInt8)(va) + 1)) >> 8) | \
	((UInt32)((UInt8)(vg) * ((UInt8)(va) + 1) >> 8) << 8) | \
	((UInt32)((UInt8)(vb) * ((UInt8)(va) + 1) >> 8) << 16) | \
	((UInt32)(UInt8)(va) << 24))

#define CCX_RGBA(vr,vg,vb,va) \
	(((va) == 0xff)?CCX_RGB((vr), (vg), (vb)):CCX_RGB_APLHA((vr), (vg), (vb), (va)))

#else
    #define CCX_RGB RGB
    #define CCX_RGBA RGBA
#endif //_TRANZDA_VM_

typedef struct 
{
	unsigned char* data;
	int size;
	int offset;
}tImageSource;

// because we do not want to include "png.h" in CCXUIImage_uphone.h, so we implement
// the function as a static function
static void pngReadCallback(png_structp png_ptr, png_bytep data, png_size_t length)
{
	tImageSource* isource = (tImageSource*)png_get_io_ptr(png_ptr);

	if((int)(isource->offset + length) <= isource->size)
	{
		memcpy(data, isource->data+isource->offset, length);
		isource->offset += length;
	}
	else
	{
		png_error(png_ptr, "pngReaderCallback failed");
	}
}

static 	void copyImageData(tImageInfo &imageInfo, png_bytep* rowPointers)
{
    // allocate memory
	imageInfo.data = new unsigned char[imageInfo.height * imageInfo.width * 4];
	if (! imageInfo.data)
	{
		return;
	}

	// copy data
	if(imageInfo.hasAlpha)	{
		unsigned int bytesPerRow = imageInfo.width * 4;
		unsigned int *tmp = (unsigned int *)imageInfo.data;
		for(unsigned int i = 0; i < imageInfo.height; i++)
		{
			for(unsigned int j = 0; j < bytesPerRow; j += 4)
			{
				*tmp++ = CCX_RGBA( rowPointers[i][j], rowPointers[i][j + 1], 
					rowPointers[i][j + 2], rowPointers[i][j + 3] );
			}
		}
	}
	else
	{
		unsigned int bytesPerRow = imageInfo.width * 3;
		unsigned int *tmp = (unsigned int *)imageInfo.data;
		for(unsigned int i = 0; i < imageInfo.height; i++)
		{
			for(unsigned int j = 0; j < bytesPerRow; j += 3)
			{
				*tmp++ = CCX_RGB( rowPointers[i][j], rowPointers[i][j + 1], 
					rowPointers[i][j + 2] );
			}
		}
	}
}

UIImage::UIImage(void)
{
	m_pBitmap = NULL;

	m_imageInfo.hasAlpha = false;
	m_imageInfo.isPremultipliedAlpha = false;
	m_imageInfo.height = 0;
	m_imageInfo.width = 0;
	m_imageInfo.data = NULL;
	m_imageInfo.bitsPerComponent = 0;
}

UIImage::UIImage(TBitmap *bitmap)
{
	if (bitmap)
	{
		m_pBitmap = bitmap->DupBitmapTo32();

		// init imageinfo
 		m_imageInfo.data = m_pBitmap->GetDataPtr();
 		m_imageInfo.height = m_pBitmap->GetHeight();
 		m_imageInfo.width = m_pBitmap->GetWidth();
 		m_imageInfo.hasAlpha = m_pBitmap->HasAlphaData();
 		// uphone only support predefined
 		m_imageInfo.isPremultipliedAlpha = true;
 		m_imageInfo.bitsPerComponent = m_pBitmap->GetDepth();
	}
}

UIImage::UIImage(int nX, int nY, void *buffer)
{

}

UIImage::~UIImage(void)
{
	if (m_pBitmap)
	{
		// the m_imageInfo's data points to m_pBitmap,
		// so we don't release m_imageInfo's data
		m_pBitmap->Destroy();
	}
	else
	{
		if (m_imageInfo.data)
		{
			delete []m_imageInfo.data;
		}
	}
}

bool UIImage::initWithContentsOfFile(const string &strPath)
{
    // use libpng load image
    return loadPng(strPath.c_str());
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

// 0 -> it is a mask
// 1 -> other
int UIImage::CGImageGetColorSpace(void)
{
	int nRet = 1;

	if (m_imageInfo.bitsPerComponent == 8)
	{
		nRet = 0;
	}

	return nRet;
}

unsigned char* UIImage::getRGBA8888Data(void)
{
	return m_imageInfo.data;
}

bool UIImage::loadPng(const char* strFileName)
{
    FILE *fp;
	unsigned char *buffer = NULL;
    bool bRet = true;
 
    fp = NULL;

	do 
	{
		// open file
		fp = fopen(strFileName, "rb");
		if (!fp)
		{
			bRet = false;
			break;
		}

		// compute the length of file
		fseek(fp,0,SEEK_END);
		int size = ftell(fp);
		fseek(fp,0,SEEK_SET);

		// allocate enough memory to save the data of file
		buffer = new unsigned char[size];
		if (! buffer)
		{
			bRet = false;
			break;
		}

		// read data
		fread(buffer, sizeof(unsigned char), size, fp);

		bRet = loadPngFromStream(buffer, size);
		delete[] buffer;
	} while (0);
    
	if (fp)
	{
		fclose(fp);
	}

    return bRet;
}

bool UIImage::loadPngFromStream(unsigned char *data, int nLength)
{
	char                header[8]; 
	png_structp         png_ptr;
	png_infop           info_ptr;
	Int32               pos;
	Int32               bitDepth;
	png_uint_32         width;
	png_uint_32         height;
	Int32               interlaceType;
	png_bytep           * rowPointers;
	Int32               colorType;
	tImageSource        imageSource;

	pos = 0;

	// read 8 bytes from the beginning of stream
	unsigned char *tmp = data;
	memcpy(header, tmp, 8);

	// close the file if it's not a png
	if (png_sig_cmp((png_bytep)header, 0, 8))
	{
		return false;
	}

	// init png_struct
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
	{
		return false;
	}   

	// init png_info
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return false;
	}

	// if something wrong,close file and return
	if (setjmp(png_jmpbuf(png_ptr)))
	{       
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		png_destroy_info_struct(png_ptr, &info_ptr);
		return false;
	}

	// set the read call back function
	imageSource.data = data;
	imageSource.size = nLength;
	imageSource.offset = 0;
	png_set_read_fn(png_ptr, &imageSource, pngReadCallback);

	
	// read the data of the file
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND | PNG_TRANSFORM_GRAY_TO_RGB, 0);

	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bitDepth, &colorType,
		&interlaceType, NULL, NULL);

	if (setjmp(png_jmpbuf(png_ptr)))
	{     
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		png_destroy_info_struct(png_ptr, &info_ptr);
		return false;
	}

	// get the image file data
	rowPointers = png_get_rows(png_ptr, info_ptr);

	// init image info
	m_imageInfo.height = height;
	m_imageInfo.width = width;
	m_imageInfo.hasAlpha = info_ptr->color_type & PNG_COLOR_MASK_ALPHA;
	m_imageInfo.isPremultipliedAlpha = false;
	copyImageData(m_imageInfo, rowPointers);
	// we use CCX_RGA or CCX_RGB to save data
	// so the bitsPerComponet is 32, and it also
	// has the alpha data
	m_imageInfo.bitsPerComponent = 32;
	m_imageInfo.hasAlpha = true;

	// release
	png_destroy_read_struct(&png_ptr, NULL, NULL);
	png_destroy_info_struct(png_ptr, &info_ptr);

	return true;
}

bool UIImage::save(const std::string &strFileName, int nFormat)
{
	/// @todo uiimage::save
	return false;
}
bool UIImage::initWithData(unsigned char *pBuffer, int nLength)
{
	return loadPngFromStream(pBuffer, nLength);
}

bool UIImage::initWithBuffer(int tx, int ty, unsigned char *pBuffer)
{
	/// @todo
	return false;
}

}//namespace   cocos2d 
