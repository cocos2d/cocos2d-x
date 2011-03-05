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

#include "CCImage_win32.h"

#include "png.h"

#include "CCBitmapDC.h"

// in order to compile correct in andLinux, because ssTypes(uphone)
// and jmorecfg.h all typedef xxx INT32
#define  QGLOBAL_H
#include "jpeglib.h"
#undef   QGLOBAL_H

//using namespace ImageToolKit;
using namespace std;
namespace   cocos2d {

#define CC_RGB_PREMULTIPLY_APLHA(vr, vg, vb, va) \
	(UINT)(((UINT32)((UINT8)(vr) * ((UINT8)(va) + 1)) >> 8) | \
	((UINT32)((UINT8)(vg) * ((UINT8)(va) + 1) >> 8) << 8) | \
	((UINT32)((UINT8)(vb) * ((UINT8)(va) + 1) >> 8) << 16) | \
	((UINT32)(UINT8)(va) << 24))

typedef struct 
{
	unsigned char* data;
	int size;
	int offset;
}tImageSource;

bool CCImage::s_bPopupNotify = true;

// because we do not want to include "png.h" in CCImage_uphone.h, so we implement
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

CCImage::CCImage(void)
{
	m_imageInfo.hasAlpha = false;
	m_imageInfo.isPremultipliedAlpha = false;
	m_imageInfo.height = 0;
	m_imageInfo.width = 0;
	m_imageInfo.data = NULL;
	m_imageInfo.bitsPerComponent = 0;
}

CCImage::CCImage(CCBitmapDC * pBmpDC)
{
    m_imageInfo.hasAlpha = false;
    m_imageInfo.isPremultipliedAlpha = false;
    m_imageInfo.height = 0;
    m_imageInfo.width = 0;
    m_imageInfo.data = NULL;
    m_imageInfo.bitsPerComponent = 0;
	if (! pBmpDC)
	{
		return;
	}

	struct
	{
		BITMAPINFOHEADER bmiHeader;
		int mask[4];
	} bi = {0};
	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	GetDIBits(pBmpDC->getDC(), pBmpDC->getBitmap(), 0, 0, NULL, (LPBITMAPINFO)&bi, DIB_RGB_COLORS);

	// init imageinfo
	m_imageInfo.height	= (bi.bmiHeader.biHeight < 0) ? - bi.bmiHeader.biHeight : bi.bmiHeader.biHeight;
 	m_imageInfo.width	= bi.bmiHeader.biWidth;
 	m_imageInfo.bitsPerComponent = bi.bmiHeader.biBitCount / 4;
 	m_imageInfo.hasAlpha = true;
 	m_imageInfo.isPremultipliedAlpha = false;
 	m_imageInfo.data = new BYTE[m_imageInfo.height * m_imageInfo.width * 4];

	// copy pixed data
	bi.bmiHeader.biHeight = (bi.bmiHeader.biHeight > 0) ? - bi.bmiHeader.biHeight : bi.bmiHeader.biHeight;
	GetDIBits(pBmpDC->getDC(), pBmpDC->getBitmap(), 0, m_imageInfo.height, m_imageInfo.data, 
		(LPBITMAPINFO)&bi, DIB_RGB_COLORS);

	// change pixel's alpha value to 255, when it's RGB != 0
	COLORREF * pPixel = NULL;
	for (unsigned int y = 0; y < m_imageInfo.height; ++y)
	{
		pPixel = (COLORREF *)m_imageInfo.data + y * m_imageInfo.width;
		for (unsigned int x = 0; x < m_imageInfo.width; ++x)
		{
			COLORREF& clr = *pPixel;
			if (GetRValue(clr) || GetGValue(clr) || GetBValue(clr))
			{
				clr |= 0xff000000;
			}
			++pPixel;
		}
	}
}

CCImage::~CCImage(void)
{
	delete []m_imageInfo.data;
}

bool CCImage::initWithContentsOfFile(const string &strPath, eImageFormat imageType)
{
	bool bRet = false;

	switch (imageType)
	{
	case kCCImageFormatPNG:
		// use libpng load image
		bRet =  loadPng(strPath.c_str());
		break;
	case kCCImageFormatJPG:
		bRet = loadJpg(strPath.c_str());
		break;
	default:
		// unsupported image type
		bRet = false;
		break;
	}

	if (!bRet && s_bPopupNotify)
	{
		// notify the loading error
		std::string strErr = "Load ";
		strErr += strPath;
		strErr += " failed!";
		std::wstring wsErr(strErr.length(), L'');
		std::copy(strErr.begin(), strErr.end(), wsErr.begin());
		MessageBox(NULL, wsErr.c_str(), L"cocos2d-x error", MB_OK);
	}

	return bRet;
}

unsigned int CCImage::width(void)
{
	return m_imageInfo.width;
}

unsigned int CCImage::height(void)
{
	return m_imageInfo.height;
}

bool CCImage::isAlphaPixelFormat(void)
{
	return m_imageInfo.hasAlpha;
}

// now, uphone only support premultiplied data
// so, we only return true
bool CCImage::isPremultipliedAlpha(void)
{
	return m_imageInfo.isPremultipliedAlpha;
}

// compute how many bits every color component 
int CCImage::CGImageGetBitsPerComponent(void)
{
	return m_imageInfo.bitsPerComponent;
}

// now we only support RGBA8888 or RGB888
// so it has color space
int CCImage::CGImageGetColorSpace(void)
{
	return 1;
}

unsigned char* CCImage::getData(void)
{
	return m_imageInfo.data;
}

bool CCImage::loadPng(const char* strFileName)
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

bool CCImage::loadPngFromStream(unsigned char *data, int nLength)
{
	char                header[8]; 
	png_structp         png_ptr;
	png_infop           info_ptr;
	png_bytep           * rowPointers;
	tImageSource        imageSource;
	int					color_type;

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
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		return false;
	}

	// set the read call back function
	imageSource.data = data;
	imageSource.size = nLength;
	imageSource.offset = 0;
	png_set_read_fn(png_ptr, &imageSource, pngReadCallback);

	// read png
	// PNG_TRANSFORM_EXPAND: perform set_expand()
	// PNG_TRANSFORM_PACKING: expand 1, 2 and 4-bit samples to bytes
	// PNG_TRANSFORM_STRIP_16: strip 16-bit samples to 8 bits
	// PNG_TRANSFORM_GRAY_TO_RGB: expand grayscale samples to RGB (or GA to RGBA)
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_GRAY_TO_RGB, NULL);

	png_get_IHDR(png_ptr, info_ptr, &m_imageInfo.width, &m_imageInfo.height, &m_imageInfo.bitsPerComponent, &color_type,
		NULL, NULL, NULL);

	// init image info
	m_imageInfo.isPremultipliedAlpha = true;
	m_imageInfo.hasAlpha = ( info_ptr->color_type & PNG_COLOR_MASK_ALPHA ) ? true : false;

	// allocate memory and read data
	int bytesPerComponent = 3;
    if (m_imageInfo.hasAlpha)
	{
		bytesPerComponent = 4;
	}
	m_imageInfo.data = new unsigned char[m_imageInfo.height * m_imageInfo.width * bytesPerComponent];
	rowPointers = png_get_rows(png_ptr, info_ptr);

	// copy data to image info
	int bytesPerRow = m_imageInfo.width * bytesPerComponent;
	if(m_imageInfo.hasAlpha)
	{
		unsigned int *tmp = (unsigned int *)m_imageInfo.data;
		for(unsigned int i = 0; i < m_imageInfo.height; i++)
		{
			for(int j = 0; j < bytesPerRow; j += 4)
			{
				*tmp++ = CC_RGB_PREMULTIPLY_APLHA( rowPointers[i][j], rowPointers[i][j + 1], 
					rowPointers[i][j + 2], rowPointers[i][j + 3] );
			}
		}
	}
	else
	{
		for (unsigned int j = 0; j < m_imageInfo.height; ++j)
		{
			memcpy(m_imageInfo.data + j * bytesPerRow, rowPointers[j], bytesPerRow);
		}
	}

	// release
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

	return true;
}

bool CCImage::loadJpg(const char *strFileName)
{
	/* these are standard libjpeg structures for reading(decompression) */
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	/* libjpeg data structure for storing one row, that is, scanline of an image */
	JSAMPROW row_pointer[1];

	FILE *infile = fopen( strFileName, "rb" );
	unsigned long location = 0;
	unsigned int i = 0;

	if ( !infile )
	{
		return false;
	}

	/* here we set up the standard libjpeg error handler */
	cinfo.err = jpeg_std_error( &jerr );

	/* setup decompression process and source, then read JPEG header */
	jpeg_create_decompress( &cinfo );

	/* this makes the library read from infile */
	jpeg_stdio_src( &cinfo, infile );

	/* reading the image header which contains image information */
	jpeg_read_header( &cinfo, true );

	// we only support RGB or grayscale
	if (cinfo.jpeg_color_space != JCS_RGB)
	{
		if (cinfo.jpeg_color_space == JCS_GRAYSCALE || cinfo.jpeg_color_space == JCS_YCbCr)
		{
            cinfo.out_color_space = JCS_RGB;
		}
	}
	else
	{
		return false;
	}

	/* Start decompression jpeg here */
	jpeg_start_decompress( &cinfo );

	/* init image info */
	m_imageInfo.width = cinfo.image_width;
	m_imageInfo.height = cinfo.image_height;
	m_imageInfo.hasAlpha = false;
	m_imageInfo.isPremultipliedAlpha = false;
	m_imageInfo.bitsPerComponent = 8;
	m_imageInfo.data = new unsigned char[cinfo.output_width*cinfo.output_height*cinfo.output_components];

	/* now actually read the jpeg into the raw buffer */
	row_pointer[0] = new unsigned char[cinfo.output_width*cinfo.output_components];

	/* read one scan line at a time */
	while( cinfo.output_scanline < cinfo.image_height )
	{
		jpeg_read_scanlines( &cinfo, row_pointer, 1 );
		for( i=0; i<cinfo.image_width*cinfo.num_components;i++) 
			m_imageInfo.data[location++] = row_pointer[0][i];
	}

	/* wrap up decompression, destroy objects, free pointers and close open files */
	jpeg_finish_decompress( &cinfo );
	jpeg_destroy_decompress( &cinfo );
	delete row_pointer[0];
	fclose( infile );

	return true;
}

bool CCImage::save(const std::string &strFileName, int nFormat)
{
	/// @todo CCImage::save
	return false;
}
bool CCImage::initWithData(unsigned char *pBuffer, int nLength)
{
	return loadPngFromStream(pBuffer, nLength);
}

bool CCImage::initWithBuffer(int tx, int ty, unsigned char *pBuffer)
{
	/// @todo need copy pBuffer data
	return false;
}

void CCImage::setIsPopupNotify(bool bNotify)
{
    s_bPopupNotify = bNotify;
}

bool CCImage::getIsPopupNotify()
{
    return s_bPopupNotify;
}

}//namespace   cocos2d 
