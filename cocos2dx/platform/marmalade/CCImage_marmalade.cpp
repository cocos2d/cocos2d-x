/****************************************************************************
 Copyright (c) 2011      cocos2d-x.org   http://cocos2d-x.org
 Copyright (c) 2011      Максим Аксенов
 Copyright (c) 2011      Giovanni Zito, Francis Styck

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
#define FONT_KERNING 2
#define RSHIFT6(num) ((num)>>6)

#include <strings.h>

extern "C"
{
#include <jpeglib.h>
}


#include <string>

// typedef struct 
// {
//     unsigned char* data;
//     int size;
//     int offset;
// }tImageSource;

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
	BitmapDC();
	~BitmapDC();

	void reset();
	bool getBitmap(const char *text, int nWidth, int nHeight, CCImage::ETextAlign eAlignMask, const char * pFontName, uint fontSize);

public:
	unsigned char*		m_pData;
	int					m_iMaxLineWidth;
	int					m_iMaxLineHeight;

private:
	void buildLine(stringstream& ss, FT_Face face, int iCurXCursor, char cLastChar);

	bool divideString(FT_Face face, const char* sText, int iMaxWidth, int iMaxHeight);

	/**
	 * compute the start pos of every line
	 * return value>0 represents the start x pos of the line, while -1 means fail
	 */
	int computeLineStart(FT_Face face, CCImage::ETextAlign eAlignMask, char cText, int iLineIndex);

	bool startsWith(const std::string& str, const std::string& what);
	bool endsWith(const std::string& str, const std::string& what);
	std::string fileNameExtension(const std::string& pathName);
	std::string basename(const std::string& pathName);
	int openFont(const std::string& fontName, uint fontSize);

private:
	FT_Library		m_library;
	FT_Face			m_face ;
	std::string		m_fontName ;
	uint			m_fontSize ;

	int				m_libError;
	int				m_iInterval;
	vector<TextLine> m_vLines;
};

bool BitmapDC::startsWith(const std::string& str, const std::string& what)
{
	bool result = false ;
	if( what.size() <= str.size() ) {
		result = (str.substr( 0, what.size() ) == what) ;
	}
	return result ;
}


bool BitmapDC::endsWith(const std::string& str, const std::string& what)
{
	bool result = false ;
	if( what.size() <= str.size() ) {
		result = (str.substr( str.size() - what.size() ) == what) ;
	}
	return result ;
}

std::string BitmapDC::fileNameExtension(const std::string& pathName)
{
	std::string ext ;
	std::string::size_type pos = pathName.find_last_of(".") ;
	if( pos != std::string::npos && pos != pathName.size()-1 ) {
		ext = pathName.substr(pos+1) ;
	}

	return ext ;
}

std::string BitmapDC::basename(const std::string& pathName)
{
	int pos = pathName.rfind("/"); 
	std::string bn = pathName.substr(pos + 1, pathName.length() - pos + 1);
	return bn ;
}

BitmapDC::BitmapDC() :
	m_face(NULL)
	,m_fontName()
	,m_fontSize(0)
	,m_iInterval(FONT_KERNING)
	,m_pData(NULL)
{
	m_libError = FT_Init_FreeType( &m_library );
	reset();
}

BitmapDC::~BitmapDC()
{
	//  free face
	if( m_face ) {
		FT_Done_Face(m_face);
		m_face = NULL;
	}

	FT_Done_FreeType(m_library);
	//data will be deleted by CCImage
	//	if (m_pData) {
	//		delete [] m_pData;
	//	}
}

void BitmapDC::reset()
{
	m_iMaxLineWidth = 0;
	m_iMaxLineHeight = 0;
	m_vLines.clear();
}

void BitmapDC::buildLine( stringstream& ss, FT_Face face, int iCurXCursor, char cLastChar )
{
	TextLine oTempLine;
	ss << '\0';
	oTempLine.sLineStr = ss.str();
	//get last glyph
	FT_Load_Glyph(face, FT_Get_Char_Index(face, cLastChar), FT_LOAD_DEFAULT);

	oTempLine.iLineWidth =
		iCurXCursor - 
		RSHIFT6( face->glyph->metrics.horiAdvance +
		face->glyph->metrics.horiBearingX
		- face->glyph->metrics.width)/*-iInterval*/;	//TODO interval

	m_iMaxLineWidth = MAX(m_iMaxLineWidth, oTempLine.iLineWidth);
	ss.clear();
	ss.str("");
	m_vLines.push_back(oTempLine);
}

bool BitmapDC::divideString( FT_Face face, const char* sText, int iMaxWidth, int iMaxHeight )
{
	const char* pText = sText;
	int iError = 0;
	int iCurXCursor;
	iError = FT_Load_Glyph(face, FT_Get_Char_Index(face, *pText), FT_LOAD_DEFAULT);
	if (iError) {
		return false;
	}
	iCurXCursor = -RSHIFT6(face->glyph->metrics.horiBearingX);
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
			iCurXCursor = -RSHIFT6(face->glyph->metrics.horiBearingX);
			continue;
		}

		iError = FT_Load_Glyph(face, FT_Get_Char_Index(face, *pText), FT_LOAD_DEFAULT);

		if (iError) {
			return false;
			//break;
		}
		//check its width
		//divide it when exceeding
		if ((iMaxWidth > 0 && iCurXCursor + RSHIFT6(face->glyph->metrics.width) > iMaxWidth)) {
			buildLine(ss, face , iCurXCursor, cLastCh);

			iCurXCursor = -RSHIFT6(face->glyph->metrics.horiBearingX);

		}

		cLastCh = *pText;
		ss << *pText;
		iCurXCursor += RSHIFT6(face->glyph->metrics.horiAdvance) + m_iInterval;
		pText++;

/*
		if (cLastCh == ' ' || cLastCh == ',' || cLastCh == '.' || cLastCh == '!' || cLastCh == '?')
		{
			char *pText_temp = (char *)pText;
			int	iCurXCursor_temp = 0;
			while((strlen(pText_temp) > 0) && (*pText_temp!=' ') && (*pText_temp !=',') && (*pText_temp != '.') && (*pText_temp != '!') && (*pText_temp != '?') && (*pText_temp != '/0') && (*pText_temp != '/n'))
			{
				iError = FT_Load_Glyph(face, FT_Get_Char_Index(face, *pText_temp), FT_LOAD_DEFAULT);

				if (iError) {
					return false;
					//break;
				}
				iCurXCursor_temp += SHIFT6(face->glyph->metrics.horiAdvance) + iInterval;
				if (iCurXCursor + iCurXCursor_temp > iMaxWidth && iMaxWidth > 0)
				{
					buildLine(ss, face , iCurXCursor, cLastCh);

					iCurXCursor = -SHIFT6(face->glyph->metrics.horiBearingX);
				}
				pText_temp++;
			}
		}
*/
	}

	if (iError) {
		return false;
	}

	buildLine(ss,face, iCurXCursor, cLastCh);

	return true;
}

int BitmapDC::computeLineStart( FT_Face face, CCImage::ETextAlign eAlignMask, char cText, int iLineIndex )
{
	int iRet;
	int iError = FT_Load_Glyph(face, FT_Get_Char_Index(face, cText), FT_LOAD_DEFAULT);
	if (iError) {
		return -1;
	}

	if (eAlignMask == CCImage::kAlignCenter) {
		iRet = (m_iMaxLineWidth - m_vLines[iLineIndex].iLineWidth) / 2 - RSHIFT6(face->glyph->metrics.horiBearingX );

	} else if (eAlignMask == CCImage::kAlignRight) {
		iRet = (m_iMaxLineWidth - m_vLines[iLineIndex].iLineWidth) - RSHIFT6(face->glyph->metrics.horiBearingX );
	} else {
		// left or other situation
		iRet = -RSHIFT6(face->glyph->metrics.horiBearingX );
	}
	return iRet;
}

int BitmapDC::openFont(const string& fontName, uint fontSize)
{
	FT_Face aFace ;

	int iError = 0 ;
	if( m_fontName != basename(fontName) || m_fontSize != fontSize ) {
		iError = FT_New_Face( m_library, fontName.c_str(), 0, &aFace );
		if( !iError ) {
			if(m_face) {
				FT_Done_Face(m_face);
			}

			m_face = aFace ;
			m_fontName = basename(fontName) ;
			m_fontSize = fontSize ;
		}
	}

	return iError ;
}

bool BitmapDC::getBitmap( const char *text, int nWidth, int nHeight, CCImage::ETextAlign eAlignMask, const char * pFontName, uint fontSize )
{
	FT_Error iError;

	unsigned char cTemp ;
	int iY, iX, iTemp ;
	uint32 offset, rowOffset ;

	//data will be deleted by CCImage
	//		if (m_pData) {
	//			delete m_pData;
	//		}

	int iCurXCursor, iCurYCursor;
	bool bRet = false;
	if (m_libError) {
		return false;
	}

	do {
		std::string fName = pFontName ;
		
		string ext = fileNameExtension(fName) ;
		if( ext.empty() || (ext != "ttf" && ext != "TTF") ) {
			fName += ".ttf" ;
		}

		if( !m_face || (m_fontName != basename(fName) || m_fontSize != fontSize) ) {

			iError = openFont( fName, fontSize );
			if (iError) {		// try loading from "fonts" folder
				if( !startsWith(fName,"fonts/") ) {
				 	fName = string("fonts/") + fName ;
				}

				iError = openFont( fName, fontSize );
				if (iError) { //no valid font found, try to use default
					
					fName = "fonts/Marker Felt.ttf" ;
					//CCLog("No valid font, use default %s\n", fName.c_str());
					iError = openFont( fName, fontSize );
				}
			}
			CC_BREAK_IF(iError);

			//select utf8 charmap
			iError = FT_Select_Charmap(m_face,FT_ENCODING_UNICODE);
			CC_BREAK_IF(iError);

			iError = FT_Set_Pixel_Sizes(m_face, fontSize,fontSize);
			CC_BREAK_IF(iError);
		}

		iError = divideString(m_face, text, nWidth, nHeight) ? 0 : 1 ;

		//compute the final line width
		m_iMaxLineWidth = MAX(m_iMaxLineWidth, nWidth);

		FT_Pos ascenderPixels = RSHIFT6(m_face->size->metrics.ascender) ;
		FT_Pos descenderPixels = RSHIFT6(m_face->size->metrics.descender) ;

		m_iMaxLineHeight = ascenderPixels - descenderPixels;
		m_iMaxLineHeight *= m_vLines.size();

		//compute the final line height
		m_iMaxLineHeight = MAX(m_iMaxLineHeight, nHeight);

		uint bitmapSize = m_iMaxLineWidth * m_iMaxLineHeight*4 ;

		m_pData = new unsigned char[bitmapSize];
		memset(m_pData,0, bitmapSize);

		const char* pText = text;
		iCurYCursor = ascenderPixels;

		for (size_t i = 0; i < m_vLines.size(); i++) {
			pText = m_vLines[i].sLineStr.c_str();
			//initialize the origin cursor
			iCurXCursor = computeLineStart(m_face, eAlignMask, *pText, i);

			while (*pText != 0) {
				int iError = FT_Load_Glyph(m_face, FT_Get_Char_Index(m_face, *pText), FT_LOAD_RENDER);
				if (iError) {
					break;
				}

				//  convert glyph to bitmap with 256 gray
				//  and get the bitmap
				FT_Bitmap & bitmap = m_face->glyph->bitmap;

				FT_Pos horiBearingYPixels = RSHIFT6(m_face->glyph->metrics.horiBearingY) ;
				FT_Pos horiBearingXPixels = RSHIFT6(m_face->glyph->metrics.horiBearingX) ;
				FT_Pos horiAdvancePixels = RSHIFT6(m_face->glyph->metrics.horiAdvance) ;

				for (int i = 0; i < bitmap.rows; ++i) {

					iY = iCurYCursor + i - horiBearingYPixels;
					if (iY < 0 || iY>=m_iMaxLineHeight) {
						//exceed the height truncate
						continue;
					}

					rowOffset = iY * m_iMaxLineWidth ;

					// if it has gray>0 we set show it as 1, otherwise 0 
					for (int j = 0; j < bitmap.width; ++j) {
						cTemp = bitmap.buffer[i	* bitmap.width + j];
						if( cTemp )
						{
							iX = iCurXCursor + j + horiBearingXPixels;

							offset = (rowOffset + iX) * 4 ;

							IwAssert( GAME, ((offset + 3) < bitmapSize) ) ;

							iTemp = cTemp << 24 | cTemp << 16 | cTemp << 8 | cTemp;
 							*(int*) &m_pData[ offset ] = iTemp ;	// ARGB
						}
					}
				}

				//step to next glyph
				iCurXCursor += horiAdvancePixels + m_iInterval;
				pText++;
			}
			iCurYCursor += ascenderPixels - descenderPixels ;
		}

		//clear all lines
		m_vLines.clear();

		//success;
		if (iError) {
			bRet = false;
		} else
			bRet = true;
	}while(0);

	return bRet;
}








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

		CC_BREAK_IF(! dc.getBitmap(pText, nWidth, nHeight, eAlignMask, pFullFontName, nSize));

		// assign the dc.m_pData to m_pData in order to save time
		m_pData = dc.m_pData;
		CC_BREAK_IF(! m_pData);

		m_nWidth = (short)dc.m_iMaxLineWidth;
		m_nHeight = (short)dc.m_iMaxLineHeight;
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
