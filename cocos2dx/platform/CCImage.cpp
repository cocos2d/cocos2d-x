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

#include "CCImage.h"

#include "CCCommon.h"
#include "CCStdC.h"
#include "png.h"
#include <string>

#define  QGLOBAL_H        // defined for uphone
#include "jpeglib.h"
#undef   QGLOBAL_H

#define CC_RGB_PREMULTIPLY_APLHA(vr, vg, vb, va) \
    (unsigned)(((unsigned)((ccxByte)(vr) * ((ccxByte)(va) + 1)) >> 8) | \
    ((unsigned)((ccxByte)(vg) * ((ccxByte)(va) + 1) >> 8) << 8) | \
    ((unsigned)((ccxByte)(vb) * ((ccxByte)(va) + 1) >> 8) << 16) | \
    ((unsigned)(ccxByte)(va) << 24))

typedef struct 
{
    unsigned char* data;
    int size;
    int offset;
}tImageSource;

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

NS_CC_BEGIN;

static void CCMessageBox(const std::string& msg, const std::string& title);

//////////////////////////////////////////////////////////////////////////
// Impliment CCImage
//////////////////////////////////////////////////////////////////////////

CCImage::CCImage()
: m_nWidth(0)
, m_nHeight(0)
, m_nBitsPerComponent(0)
, m_bHasAlpha(false)
, m_bPreMulti(false)
{

}

bool CCImage::initWithImageFile(const char * strPath, EImageFormat eImgFmt/* = eFmtPng*/)
{
    bool bRet = false;
    FILE *fp = 0;
    unsigned char *buffer = NULL;
    do 
    {
        // open file
        fp = fopen(strPath, "rb");
        CC_BREAK_IF(! fp);

        // compute the length of file
        fseek(fp,0,SEEK_END);
        int size = ftell(fp);
        fseek(fp,0,SEEK_SET);

        // allocate enough memory to save the data of file
        buffer = new unsigned char[size];
        CC_BREAK_IF(! buffer);

        // read data
        size = fread(buffer, sizeof(unsigned char), size, fp);

        if (kFmtJpg == eImgFmt)
        {
            bRet = _initWithJpgData(buffer, size);
        }
        else
        {
            bRet = _initWithPngData(buffer, size);
        }
    } while (0);

    CC_SAFE_DELETE_ARRAY(buffer);
    if (fp)
    {
        fclose(fp);
    }
    if (! bRet && CCImage::getIsPopupNotify())
    {
        std::string title = "cocos2d-x error!";
        std::string msg = "Load ";
        msg.append(strPath).append(" failed!");
    
        CCMessageBox(msg, title);
    }
    return bRet;
}

bool CCImage::initWithImageData(void * pData, int nDataLen, EImageFormat eFmt/* = eSrcFmtPng*/)
{
    bool bRet = false;
    do 
    {
    	CC_BREAK_IF(! pData || nDataLen <= 0);

        if (kFmtPng == eFmt)
        {
            bRet = _initWithPngData(pData, nDataLen);
            break;
        }
        else if (kFmtJpg == eFmt)
        {
            bRet = _initWithJpgData(pData, nDataLen);
            break;
        }
    } while (0);
    return bRet;
}

static bool s_bPopupNotify = true;

void CCImage::setIsPopupNotify(bool bNotify)
{
    s_bPopupNotify = bNotify;
}

bool CCImage::getIsPopupNotify()
{
    return s_bPopupNotify;
}

bool CCImage::_initWithJpgData(void * data, int nSize)
{
    /* these are standard libjpeg structures for reading(decompression) */
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    /* libjpeg data structure for storing one row, that is, scanline of an image */
    JSAMPROW row_pointer[1];

    unsigned long location = 0;
    unsigned int i = 0;

    /* here we set up the standard libjpeg error handler */
    cinfo.err = jpeg_std_error( &jerr );

    /* setup decompression process and source, then read JPEG header */
    jpeg_create_decompress( &cinfo );

    /* this makes the library read from infile */
    jpeg_mem_src( &cinfo, (unsigned char *) data, nSize );

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
    m_nWidth  = cinfo.image_width;
    m_nHeight = cinfo.image_height;
    m_bHasAlpha = false;
    m_bPreMulti = false;
    m_nBitsPerComponent = 8;
    m_pData.reset(new ccxByte[cinfo.output_width*cinfo.output_height*cinfo.output_components]);
    ccxByte * pData = m_pData.get();

    /* now actually read the jpeg into the raw buffer */
    row_pointer[0] = new unsigned char[cinfo.output_width*cinfo.output_components];

    /* read one scan line at a time */
    while( cinfo.output_scanline < cinfo.image_height )
    {
        jpeg_read_scanlines( &cinfo, row_pointer, 1 );
        for( i=0; i<cinfo.image_width*cinfo.num_components;i++) 
            pData[location++] = row_pointer[0][i];
    }

    /* wrap up decompression, destroy objects, free pointers and close open files */
    jpeg_finish_decompress( &cinfo );
    jpeg_destroy_decompress( &cinfo );
    delete row_pointer[0];

    return true;
}

bool CCImage::_initWithPngData(void * pData, int nDatalen)
{
    bool bRet = false;
    png_byte        header[8]   = {0}; 
    png_structp     png_ptr =   0;
    png_infop       info_ptr    = 0;

    do 
    {
        // png header len is 8 bytes
    	CC_BREAK_IF(nDatalen < 8);

        // check the data is png or not
        memcpy(header, pData, 8);
        CC_BREAK_IF(png_sig_cmp(header, 0, 8));

        // init png_struct
        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
        CC_BREAK_IF(! png_ptr);

        // init png_info
        info_ptr = png_create_info_struct(png_ptr);
        CC_BREAK_IF(! info_ptr || setjmp(png_jmpbuf(png_ptr)));

        bRet = true;

        // set the read call back function
        tImageSource imageSource;
        imageSource.data    = (unsigned char*)pData;
        imageSource.size    = nDatalen;
        imageSource.offset  = 0;
        png_set_read_fn(png_ptr, &imageSource, pngReadCallback);

        // read png
        // PNG_TRANSFORM_EXPAND: perform set_expand()
        // PNG_TRANSFORM_PACKING: expand 1, 2 and 4-bit samples to bytes
        // PNG_TRANSFORM_STRIP_16: strip 16-bit samples to 8 bits
        // PNG_TRANSFORM_GRAY_TO_RGB: expand grayscale samples to RGB (or GA to RGBA)
        png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND | PNG_TRANSFORM_PACKING 
            | PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_GRAY_TO_RGB, 0);

        int         color_type  = 0;
        png_uint_32 nWidth = 0;
        png_uint_32 nHeight = 0;
        int         nBitsPerComponent = 0;
        png_get_IHDR(png_ptr, info_ptr, &nWidth, &nHeight, &nBitsPerComponent, &color_type, 0, 0, 0);

        // init image info
        m_bPreMulti = true;
        m_bHasAlpha = ( info_ptr->color_type & PNG_COLOR_MASK_ALPHA ) ? true : false;

        // allocate memory and read data
        int bytesPerComponent = 3;
        if (m_bHasAlpha)
        {
            bytesPerComponent = 4;
        }
        m_pData.reset(new ccxByte[nHeight * nWidth * bytesPerComponent]);
        png_bytep * rowPointers = png_get_rows(png_ptr, info_ptr);

        // copy data to image info
        int bytesPerRow = nWidth * bytesPerComponent;
        if(m_bHasAlpha)
        {
            unsigned int *tmp = (unsigned int *)m_pData.get();
            for(unsigned int i = 0; i < nHeight; i++)
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
            for (unsigned int j = 0; j < nHeight; ++j)
            {
                memcpy(m_pData.get() + j * bytesPerRow, rowPointers[j], bytesPerRow);
            }
        }

        m_nHeight   = (ccxInt16)nHeight;
        m_nWidth    = (ccxInt16)nWidth;
        m_nBitsPerComponent      = nBitsPerComponent;
        bRet        = true;
    } while (0);

    if (!png_ptr)
    {
        png_destroy_read_struct(&png_ptr, (info_ptr) ? &info_ptr : 0, 0);
    }
    return bRet;
}

NS_CC_END;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "win32/CCImage_win32.cpp"
#endif 

#if (CC_TARGET_PLATFORM == CC_PLATFORM_UPHONE)
#include "uphone/CCImage_uphone.cpp"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/CCImage_android.cpp"
#endif
