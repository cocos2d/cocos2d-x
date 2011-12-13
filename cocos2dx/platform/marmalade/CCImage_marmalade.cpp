/****************************************************************************
 Copyright (c) 2011      cocos2d-x.org   http://cocos2d-x.org
 Copyright (c) 2011      Максим Аксенов
 
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
#include <vector>
#include <string>
#include <sstream> 

#include "CCImage.h"
#include "CCCommon.h"
#include "CCStdC.h"
#include "CCFileUtils.h"
#include "s3eFile.h"
#include "IwUtil.h"
#include "png.h"
#include "ft2build.h"
#include FT_FREETYPE_H 
#define szFont_kenning 2
#define SHIFT6(num) ((num)>>6)

#include <strings.h>

extern "C"
{
#include <jpeglib.h>
}


#include <string>

typedef struct 
{
    unsigned char* data;
    int size;
    int offset;
}tImageSource;

struct TextLine {
	string sLineStr;
	int iLineWidth;
};

NS_CC_BEGIN;

class CC_DLL CCImageHelper
{
public:
	CCImageHelper();
	~CCImageHelper();
	// dummy funcs to help libjpeg
	static void JPEGInitSource(j_decompress_ptr cinfo)
	{
	}

	static boolean JPEGFillInputBuffer(j_decompress_ptr cinfo)
	{
		return 0;
	}

	static void JPEGSkipInputData(j_decompress_ptr cinfo, long num_bytes)
	{
		cinfo->src->next_input_byte += num_bytes;
		cinfo->src->bytes_in_buffer -= num_bytes;
	}

	static void JPEGTermSource(j_decompress_ptr cinfo)
	{
	}
};

class BitmapDC
{
public:
	BitmapDC() {
		libError = FT_Init_FreeType( &library );
		iInterval = szFont_kenning;
		m_pData = NULL;
		reset();
	}

	~BitmapDC() {
		FT_Done_FreeType(library);
		//data will be deleted by CCImage
	//	if (m_pData) {
	//		delete [] m_pData;
	//	}

	}

	void reset() {
		iMaxLineWidth = 0;
		iMaxLineHeight = 0;
		vLines.clear();
	}

	void buildLine(stringstream& ss, FT_Face face, int iCurXCursor, char cLastChar) {
		TextLine oTempLine;
		ss << '\0';
		oTempLine.sLineStr = ss.str();
		//get last glyph
		FT_Load_Glyph(face, FT_Get_Char_Index(face, cLastChar), FT_LOAD_DEFAULT);

		oTempLine.iLineWidth =
			iCurXCursor - 
			SHIFT6( face->glyph->metrics.horiAdvance +
					face->glyph->metrics.horiBearingX
					- face->glyph->metrics.width)/*-iInterval*/;	//TODO interval

		iMaxLineWidth = MAX(iMaxLineWidth, oTempLine.iLineWidth);
		ss.clear();
		ss.str("");
		vLines.push_back(oTempLine);
	}

	bool divideString(FT_Face face, const char* sText, int iMaxWidth, int iMaxHeight) {
		const char* pText = sText;
		int iError = 0;
		int iCurXCursor;
		iError = FT_Load_Glyph(face, FT_Get_Char_Index(face, *pText), FT_LOAD_DEFAULT);
		if (iError) {
			return false;
		}
		iCurXCursor = -SHIFT6(face->glyph->metrics.horiBearingX);
		//init stringstream
		stringstream ss;

		int cLastCh = 0;

		while (*pText != '\0') {
			if (*pText == '\n') {
				buildLine(ss, face, iCurXCursor, cLastCh);

				pText++;
				iError = FT_Load_Glyph(face, FT_Get_Char_Index(face, *pText), FT_LOAD_DEFAULT);
				if (iError) {
					return false;
				}
				iCurXCursor = -SHIFT6(face->glyph->metrics.horiBearingX);
				continue;
			}

			iError = FT_Load_Glyph(face, FT_Get_Char_Index(face, *pText), FT_LOAD_DEFAULT);

			if (iError) {
				return false;
				//break;
			}
			//check its width
			//divide it when exceeding
			if ((iMaxWidth > 0 && iCurXCursor + SHIFT6(face->glyph->metrics.width) > iMaxWidth)) {
				buildLine(ss, face , iCurXCursor, cLastCh);

				iCurXCursor = -SHIFT6(face->glyph->metrics.horiBearingX);

			}

			cLastCh = *pText;
			ss << *pText;
			iCurXCursor += SHIFT6(face->glyph->metrics.horiAdvance) + iInterval;
			pText++;

		}
		if (iError) {
			return false;
		}

		buildLine(ss,face, iCurXCursor, cLastCh);

		return true;
	}

	/**
	 * compute the start pos of every line
	 *
	 * return >0 represent the start x pos of the line
	 * while -1 means fail
	 *
	 */
	int computeLineStart(FT_Face face, CCImage::ETextAlign eAlignMask, char cText,
			int iLineIndex) {
		int iRet;
		int iError = FT_Load_Glyph(face, FT_Get_Char_Index(face, cText), FT_LOAD_DEFAULT);
		if (iError) {
			return -1;
		}

		if (eAlignMask == CCImage::kAlignCenter) {
			iRet = (iMaxLineWidth - vLines[iLineIndex].iLineWidth) / 2 - SHIFT6(face->glyph->metrics.horiBearingX );

		} else if (eAlignMask == CCImage::kAlignRight) {
			iRet = (iMaxLineWidth - vLines[iLineIndex].iLineWidth) - SHIFT6(face->glyph->metrics.horiBearingX );
		} else {
			// left or other situation
			iRet = -SHIFT6(face->glyph->metrics.horiBearingX );
		}
		return iRet;
	}

	bool getBitmap(const char *text, int nWidth, int nHeight, CCImage::ETextAlign eAlignMask, const char * pFontName, float fontSize) {
		FT_Face face;
		FT_Error iError;

		const char* pText = text;
		//data will be deleted by CCImage
//		if (m_pData) {
//			delete m_pData;
//		}

		int iCurXCursor, iCurYCursor;
		bool bRet = false;
		if (libError) {
			return false;
		}
		do {
			iError = FT_New_Face( library, pFontName, 0, &face );
			if (iError) {
				//no valid font found use default
//				CCLog("no valid font, use default %s\n", pFontName);
				iError = FT_New_Face( library, "fonts/Marker Felt.ttf", 0, &face );
			}
			CC_BREAK_IF(iError);

			//select utf8 charmap
			iError = FT_Select_Charmap(face,FT_ENCODING_UNICODE);
			CC_BREAK_IF(iError);

			iError = FT_Set_Pixel_Sizes(face, fontSize,fontSize);
			CC_BREAK_IF(iError);

			iError = divideString(face, text, nWidth, nHeight) ? 0 : 1 ;

			//compute the final line width
			iMaxLineWidth = MAX(iMaxLineWidth, nWidth);

			FT_Pos ascenderPixels = SHIFT6(face->size->metrics.ascender) ;
			FT_Pos descenderPixels = SHIFT6(face->size->metrics.descender) ;

			iMaxLineHeight = ascenderPixels - descenderPixels;
			iMaxLineHeight *= vLines.size();

			//compute the final line height
			iMaxLineHeight = MAX(iMaxLineHeight, nHeight);

			uint bitmapSize = iMaxLineWidth * iMaxLineHeight*4 ;

			m_pData = new unsigned char[bitmapSize];
			iCurYCursor = ascenderPixels;

			memset(m_pData,0, bitmapSize);

			for (size_t i = 0; i < vLines.size(); i++) {
				pText = vLines[i].sLineStr.c_str();
				//initialize the origin cursor
				iCurXCursor = computeLineStart(face, eAlignMask, *pText, i);

				while (*pText != 0) {
					int iError = FT_Load_Glyph(face, FT_Get_Char_Index(face, *pText), FT_LOAD_RENDER);
					if (iError) {
						break;
					}

					//  convert glyph to bitmap with 256 gray
					//  and get the bitmap
					FT_Bitmap & bitmap = face->glyph->bitmap;

					FT_Pos horiBearingYPixels = SHIFT6(face->glyph->metrics.horiBearingY) ;
					FT_Pos horiBearingXPixels = SHIFT6(face->glyph->metrics.horiBearingX) ;
					FT_Pos horiAdvancePixels = SHIFT6(face->glyph->metrics.horiAdvance) ;

					for (int i = 0; i < bitmap.rows; ++i) {
						for (int j = 0; j < bitmap.width; ++j) {
							//  if it has gray>0 we set show it as 1, o otherwise
							int iY = iCurYCursor + i - horiBearingYPixels;
							int iX = iCurXCursor + j + horiBearingXPixels;

							if (iY < 0 || iY>=iMaxLineHeight) {
								//exceed the height truncate
								continue;
							}

							IwAssert( GAME, (((iY * iMaxLineWidth + iX) * 4 + 3) < bitmapSize) ) ;

// 							m_pData[(iY * iMaxLineWidth + iX) * 4 + 3] = bitmap.buffer[i * bitmap.width + j] ? 0xff : 0;//alpha
// 							m_pData[(iY * iMaxLineWidth + iX) * 4 + 1] = bitmap.buffer[i * bitmap.width + j];//R
// 							m_pData[(iY * iMaxLineWidth + iX) * 4 + 2] = bitmap.buffer[i * bitmap.width + j];//G
// 							m_pData[(iY * iMaxLineWidth + iX) * 4 + 0] = bitmap.buffer[i * bitmap.width + j];//B

							int iTemp = 0;
							unsigned char cTemp = bitmap.buffer[i	* bitmap.width + j];
							iTemp |= (cTemp ? 0xff : 0) << 24;
							iTemp |= cTemp << 16 | cTemp << 8 | cTemp;
							*(int*) &m_pData[ (iY * iMaxLineWidth + iX) * 4 ] = iTemp;
						}
					}

					//step to next glyph
					iCurXCursor += horiAdvancePixels + iInterval;
					pText++;
				}
				iCurYCursor += ascenderPixels - descenderPixels ;
			}

			//  free face
			FT_Done_Face(face);
			face = NULL;

			//clear all lines
			vLines.clear();

			//success;
			if (iError) {
				bRet = false;
			} else
			bRet = true;
		}while(0);

		return bRet;
	}
public:
	FT_Library library;
	unsigned char *m_pData;
	int libError;
	vector<TextLine> vLines;
	int iInterval;
	int iMaxLineWidth;
	int iMaxLineHeight;
};

static BitmapDC& sharedBitmapDC()
{
	static BitmapDC s_BmpDC;
	return s_BmpDC;
}
 
//////////////////////////////////////////////////////////////////////////
// Implement CCImage
//////////////////////////////////////////////////////////////////////////

CCImage::CCImage()
: m_nWidth(0)
, m_nHeight(0)
, m_nBitsPerComponent(0)
, m_pData(0)
, m_bHasAlpha(false)
, m_bPreMulti(false)
{
	
}

CCImage::~CCImage()
{
    CC_SAFE_DELETE_ARRAY(m_pData);
}
bool CCImage::initWithImageFile(const char * strPath, EImageFormat eImgFmt/* = eFmtPng*/)
{
	IW_CALLSTACK("UIImage::initWithImageFile");
    CCFileData data(CCFileUtils::fullPathFromRelativePath(strPath), "rb");
    return initWithImageData(data.getBuffer(), data.getSize(), eImgFmt);
}

bool CCImage::initWithImageFileThreadSafe( const char *fullpath, EImageFormat imageType /*= kFmtPng*/ )
{
	CC_UNUSED_PARAM(imageType);
	CCFileData data(fullpath, "rb");
	return initWithImageData(data.getBuffer(), data.getSize(), imageType);
}

bool CCImage::initWithImageData(void * pData, 
								int nDataLen, 
								EImageFormat eFmt,
								int nWidth,
								int nHeight,
								int nBitsPerComponent)
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

bool CCImage::_initWithJpgData(void * data, int nSize)
{	
	IW_CALLSTACK("CCImage::_initWithJpgData");

	bool bRet = false;

	s3eFile* pFile = s3eFileOpenFromMemory(data, nSize);

	IwAssert(GAME, pFile);

    jpeg_decompress_struct cinfo;
    bzero(&cinfo, sizeof(cinfo));

    JSAMPARRAY buffer;      /* Output row buffer */
    int row_stride;     /* physical row width in output buffer */

    jpeg_source_mgr srcmgr;

    srcmgr.bytes_in_buffer = nSize;
    srcmgr.next_input_byte = (JOCTET*) data;
    srcmgr.init_source = CCImageHelper::JPEGInitSource;
    srcmgr.fill_input_buffer = CCImageHelper::JPEGFillInputBuffer;
    srcmgr.skip_input_data = CCImageHelper::JPEGSkipInputData;
    srcmgr.resync_to_restart = jpeg_resync_to_restart;
    srcmgr.term_source = CCImageHelper::JPEGTermSource;

    jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_decompress(&cinfo);
    cinfo.src = &srcmgr;

    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    /* JSAMPLEs per row in output buffer */
    row_stride = cinfo.output_width * cinfo.output_components;

    /* Make a one-row-high sample array that will go away when done with image */
    buffer = (*cinfo.mem->alloc_sarray)
        ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

    int copy_rows  = (int)cinfo.output_height;
    int copy_width = (int)cinfo.output_width;

   if (copy_width < 0 || copy_rows < 0)
    {
        printf("jpeg is fully off screen\n");
        return bRet;
    }
	int startx=0;
	int starty=0;
	int bytesPerPix = 4;
	m_pData = new unsigned char[copy_rows * copy_width * bytesPerPix];
	memset(m_pData,0, copy_rows * copy_width * bytesPerPix);
	// init image info
	m_bPreMulti	= false;
	m_bHasAlpha = false;
	m_nHeight = copy_rows;
	m_nWidth = copy_width;
	m_nBitsPerComponent = bytesPerPix;
	unsigned char *dst = m_pData;
	unsigned char *pData = m_pData;

    while (cinfo.output_scanline < cinfo.output_height)// count through the image
    {
        /* jpeg_read_scanlines expects an array of pointers to scanlines.
         * Here the array is only one element long, but you could ask for
         * more than one scanline at a time if that's more convenient.
         */
        (void) jpeg_read_scanlines(&cinfo, buffer, 1);

        if (starty-- <= 0)// count down from start
        {
            if (copy_rows-- > 0)
            {
                for (int xx=startx; xx < copy_width; xx++)
                {
                    uint8 r = buffer[0][xx*3+0];
                    uint8 b = buffer[0][xx*3+1];
                    uint8 g = buffer[0][xx*3+2];

					*dst++ = r;
					*dst++ = b;
					*dst++ = g;
					*dst++ = 255;
                }
            }
        }
    }

    (void) jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    printf("jpeg display done\n");

	bRet = true;
	return bRet;
}

void userReadData(png_structp pngPtr, png_bytep data, png_size_t length) {
	png_voidp png_pointer = png_get_io_ptr(pngPtr);
	s3eFileRead((char*)data, length, 1, (s3eFile*)png_pointer);
}

#define PNGSIGSIZE 8
bool CCImage::_initWithPngData(void * pData, int nDatalen)
{
	IW_CALLSTACK("CCImage::_initWithPngData");
	
    bool bRet = false;
	
	s3eFile* pFile = s3eFileOpenFromMemory(pData, nDatalen);
	
	IwAssert(GAME, pFile);
	
	png_byte pngsig[PNGSIGSIZE];
	
	bool is_png = false;
	
	s3eFileRead((char*)pngsig, PNGSIGSIZE, 1, pFile);
	
	is_png = png_sig_cmp(pngsig, 0, PNGSIGSIZE) == 0 ? true : false;
	
	if (!is_png)
		return false;
	
	png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	
	if (!pngPtr)
		return false;
	
	png_infop infoPtr = png_create_info_struct(pngPtr);
	
	if (!infoPtr)
		return false;
	
	png_bytep* rowPtrs = NULL;
	m_pData = NULL;
	
	if (setjmp(png_jmpbuf(pngPtr))) {
		png_destroy_read_struct(&pngPtr, &infoPtr,(png_infopp)0);
		if (rowPtrs != NULL) delete [] rowPtrs;
		if (m_pData != NULL) delete [] m_pData;
		
		CCLog("ERROR: An error occured while reading the PNG file");
		
		return false;
	}
	
	png_set_read_fn(pngPtr, pFile, userReadData);
	png_set_sig_bytes(pngPtr, PNGSIGSIZE);
	png_read_info(pngPtr, infoPtr);
	
	
	png_uint_32 bitdepth   = png_get_bit_depth(pngPtr, infoPtr);
	png_uint_32 channels   = png_get_channels(pngPtr, infoPtr);
	png_uint_32 color_type = png_get_color_type(pngPtr, infoPtr);
	
	// Convert palette color to true color
	if (color_type ==PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(pngPtr);
	
	// Convert low bit colors to 8 bit colors
	if (png_get_bit_depth(pngPtr, infoPtr) < 8)
	{
		if (color_type==PNG_COLOR_TYPE_GRAY || color_type==PNG_COLOR_TYPE_GRAY_ALPHA)
			png_set_gray_1_2_4_to_8(pngPtr);
		else
			png_set_packing(pngPtr);
	}

	if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(pngPtr);
	
	// Convert high bit colors to 8 bit colors
	if (bitdepth == 16)
		png_set_strip_16(pngPtr);
	
	// Convert gray color to true color
	if (color_type==PNG_COLOR_TYPE_GRAY || color_type==PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(pngPtr);
	
	// Update the changes
	png_read_update_info(pngPtr, infoPtr);
	
	// init image info
	m_bPreMulti	= true;
	
	unsigned int bytesPerComponent = png_get_channels(pngPtr, infoPtr);
	
	m_bHasAlpha = (bytesPerComponent == 4 ? true : false);
	
	m_nHeight = (unsigned int)png_get_image_height(pngPtr, infoPtr);
	m_nWidth = (unsigned int) png_get_image_width(pngPtr, infoPtr);
	
	m_nBitsPerComponent = (unsigned int)png_get_bit_depth(pngPtr, infoPtr);
	
	m_pData = new unsigned char[m_nHeight * m_nWidth * bytesPerComponent];
	
	unsigned int bytesPerRow = m_nWidth * bytesPerComponent;
	
	{
		unsigned char *ptr = m_pData;
		rowPtrs = new png_bytep[m_nHeight];
				
		for (int i = 0; i < m_nHeight; i++) {
			
			int q = (i) * bytesPerRow;
			
			rowPtrs[i] = (png_bytep)m_pData + q;
		}
		
		png_read_image(pngPtr, rowPtrs);
		
		delete[] (png_bytep)rowPtrs;
		png_destroy_read_struct(&pngPtr, &infoPtr,(png_infopp)0);
		
		s3eFileClose(pFile);
		pFile = 0;
	}
	
	// premultiplay if alpha
	if(m_bHasAlpha)
		for(unsigned int i = 0; i < m_nHeight*bytesPerRow; i += bytesPerComponent){
			*(m_pData + i + 0)	=  (*(m_pData + i + 0) * *(m_pData + i + 3) + 1) >> 8;
			*(m_pData + i + 1)	=  (*(m_pData + i + 1) * *(m_pData + i + 3) + 1) >> 8;					
			*(m_pData + i + 2)	=  (*(m_pData + i + 2) * *(m_pData + i + 3) + 1) >> 8;
			*(m_pData + i + 3)	=   *(m_pData + i + 3);
	}
	

	
	bRet = true;
    return bRet;
}

bool CCImage::initWithString(
							 const char *    pText, 
							 int             nWidth/* = 0*/, 
							 int             nHeight/* = 0*/,
							 ETextAlign      eAlignMask/* = kAlignCenter*/,
							 const char *    pFontName/* = nil*/,
							 int             nSize/* = 0*/)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(! pText);

		BitmapDC &dc = sharedBitmapDC();

		const char* pFullFontName = CCFileUtils::fullPathFromRelativePath(pFontName);

		CC_BREAK_IF(! dc.getBitmap(pText, nWidth, nHeight, eAlignMask, pFullFontName, (float)nSize));

		// assign the dc.m_pData to m_pData in order to save time
		m_pData = dc.m_pData;
		CC_BREAK_IF(! m_pData);

		m_nWidth = (short)dc.iMaxLineWidth;
		m_nHeight = (short)dc.iMaxLineHeight;
		m_bHasAlpha = true;
		m_bPreMulti = true;
		m_nBitsPerComponent = 8;

		bRet = true;

		dc.reset();
	}while (0);

	//do nothing
	return bRet; 
}

bool CCImage::saveToFile(const char *pszFilePath, bool bIsToRGB)
{
	// todo
	return false;
}

bool CCImage::_initWithRawData(void * pData, int nDatalen, int nWidth, int nHeight, int nBitsPerComponent)
{
	// todo
	return false;
}

bool CCImage::_saveImageToPNG(const char * pszFilePath, bool bIsToRGB)
{
	// todo
	return false;
}

bool CCImage::_saveImageToJPG(const char * pszFilePath)
{
	// todo
	return false;
}

NS_CC_END;
