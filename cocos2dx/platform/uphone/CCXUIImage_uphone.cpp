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
	png_bytep           * rowPointers;
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

	// read png info
	png_read_info(png_ptr, info_ptr);

	// init image info
	m_imageInfo.height = info_ptr->height;
	m_imageInfo.width = info_ptr->width;
	m_imageInfo.isPremultipliedAlpha = false;
	// we use CCX_RGA or CCX_RGB to save data
	// so the bitsPerComponet is 32, and it also
	// has the alpha data
	m_imageInfo.bitsPerComponent = 32;
	m_imageInfo.hasAlpha = true;

	// convert to appropriate format, we now only support RGBA8888
	if (info_ptr->color_type == PNG_COLOR_TYPE_PALETTE)
	{
		png_set_packing(png_ptr);
		png_set_palette_to_rgb(png_ptr);
	}
	if (info_ptr->color_type == PNG_COLOR_TYPE_GRAY && info_ptr->bit_depth < 8)
	{
		png_set_expand_gray_1_2_4_to_8(png_ptr);
	}
	if (info_ptr->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
	{
		png_set_gray_to_rgb(png_ptr);
	}
	if (info_ptr->bit_depth == 16)
	{
		png_set_strip_16(png_ptr);
	}

	// expand paletted or RGB images with transparency to full alpha channels so the data will be
	// available as RGBA quatets
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
	{
		png_set_tRNS_to_alpha(png_ptr);
	}

	// add the alpha channel if it has not
	if (info_ptr->color_type == PNG_COLOR_TYPE_RGB || info_ptr->color_type == PNG_COLOR_TYPE_GRAY)
	{
		png_set_add_alpha(png_ptr, 255, PNG_FILLER_AFTER);
	}

	// allocate memory and read data
	m_imageInfo.data = new unsigned char[m_imageInfo.height * m_imageInfo.width * 4];
	rowPointers = (png_bytep*)png_mem_alloc(sizeof(png_bytep) * m_imageInfo.height);
	for (unsigned int i = 0; i < m_imageInfo.height; ++i)
	{
		rowPointers[i] = (png_bytep)png_mem_alloc(m_imageInfo.width * 4);
	}
	png_read_image(png_ptr, rowPointers);

	// copy data to image info
	int bytesPerRow = m_imageInfo.width * 4;
	for (unsigned int j = 0; j < m_imageInfo.height; ++j)
	{
		memcpy(m_imageInfo.data + j * bytesPerRow, rowPointers[j], bytesPerRow);
	}

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
