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
#define __CC_PLATFORM_IMAGE_CPP__
#include "platform/CCImageCommon_cpp.h"

#include <string.h>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "platform/CCImage.h"
#include "platform/CCFileUtils.h"
#include "platform/CCCommon.h"
#include "CCStdC.h"
#include "ft2build.h"
#include FT_FREETYPE_H

#define szFont_kenning 2

#define SHIFT6(num) (num>>6)

using namespace std;

struct TextLine {
	int iLineWidth;
    wchar_t* text;
};

NS_CC_BEGIN

class BitmapDC
{
public:
    BitmapDC()
    {
    	libError = FT_Init_FreeType( &library );
		iInterval = szFont_kenning;
		m_pData = NULL;
		reset();
    }
    
    ~BitmapDC(void)
    {
    	FT_Done_FreeType(library);
    }
    
    void reset() {
		iMaxLineWidth = 0;
		iMaxLineHeight = 0;
		size_t size = vLines.size();
        for (int i=0; i<size; ++i) {
            TextLine line = vLines[i];
            free(line.text);
        }
		vLines.clear();
	}
    

    int utf8(char **p)
    {
        if ((**p & 0x80) == 0x00)
        {
            int a = *((*p)++);

            return a;
        }
        if ((**p & 0xE0) == 0xC0)
        {
            int a = *((*p)++) & 0x1F;
            int b = *((*p)++) & 0x3F;

            return (a << 6) | b;
        }
        if ((**p & 0xF0) == 0xE0)
        {
            int a = *((*p)++) & 0x0F;
            int b = *((*p)++) & 0x3F;
            int c = *((*p)++) & 0x3F;

            return (a << 12) | (b << 6) | c;
        }
        if ((**p & 0xF8) == 0xF0)
        {
            int a = *((*p)++) & 0x07;
            int b = *((*p)++) & 0x3F;
            int c = *((*p)++) & 0x3F;
            int d = *((*p)++) & 0x3F;

            return (a << 18) | (b << 12) | (c << 8) | d;
        }
        return 0;
    }

	void buildLine(wchar_t* buf, size_t buf_len, FT_Face face, int iCurXCursor, FT_UInt cLastChar) {
		TextLine oTempLine;
        wchar_t* text = (wchar_t*)malloc(sizeof(wchar_t) * (buf_len+1));
        memcpy(text, buf, sizeof(wchar_t) * buf_len);
        text[buf_len] = '\0';
        oTempLine.text = text;

		//get last glyph
        int iError = FT_Load_Char(face, cLastChar, FT_LOAD_DEFAULT);

        oTempLine.iLineWidth = iCurXCursor - SHIFT6((face->glyph->metrics.horiAdvance - face->glyph->metrics.horiBearingX - face->glyph->metrics.width))/*-iInterval*/;//TODO interval
		iMaxLineWidth = MAX(iMaxLineWidth, oTempLine.iLineWidth);

        vLines.push_back(oTempLine);
	}

	bool divideString(FT_Face face, const char* sText, int iMaxWidth, int iMaxHeight) {
		int iError = 0;
		int iCurXCursor, iCurYCursor;
		const char* pText = sText;

        FT_UInt unicode = utf8((char**)&pText);
        iError = FT_Load_Char(face, unicode, FT_LOAD_DEFAULT);
		if (iError) {
			return false;
		}
		iCurXCursor = -SHIFT6(face->glyph->metrics.horiBearingX);

		FT_UInt cLastCh = 0;

        pText = sText;
        size_t text_len = 0;
        wchar_t* text_buf = (wchar_t*) malloc(sizeof(wchar_t) * strlen(sText));
        while (unicode=utf8((char**)&pText)) {
            if (unicode == '\n') {
				buildLine(text_buf, text_len, face, iCurXCursor, cLastCh);
                text_len = 0;

                iError = FT_Load_Char(face, unicode, FT_LOAD_DEFAULT);
				if (iError) {
                    free(text_buf);
					return false;
				}
				iCurXCursor = -SHIFT6(face->glyph->metrics.horiBearingX);
				continue;
			}

            iError = FT_Load_Char(face, unicode, FT_LOAD_DEFAULT);

			if (iError) {
                free(text_buf);
				return false;
			}

			//check its width
			//divide it when exceeding
			if ((iMaxWidth > 0
							&& iCurXCursor + SHIFT6(face->glyph->metrics.width)
							> iMaxWidth)) {
				buildLine(text_buf, text_len, face , iCurXCursor, cLastCh);
                text_len = 0;

				iCurXCursor = -SHIFT6(face->glyph->metrics.horiBearingX);
			}

			cLastCh = unicode;
            text_buf[text_len] = unicode;
            ++text_len;
			iCurXCursor += SHIFT6(face->glyph->metrics.horiAdvance) + iInterval;
		}
        
		if (iError) {
            free(text_buf);
			return false;
		}

		buildLine(text_buf, text_len, face, iCurXCursor, cLastCh);
        free(text_buf);

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
		int iError = FT_Load_Glyph(face, FT_Get_Char_Index(face, cText),
                                   FT_LOAD_DEFAULT);
		if (iError) {
			return -1;
		}
        
		if (eAlignMask == CCImage::kAlignCenter) {
			iRet = (iMaxLineWidth - vLines[iLineIndex].iLineWidth) / 2
			- SHIFT6(face->glyph->metrics.horiBearingX );
            
		} else if (eAlignMask == CCImage::kAlignRight) {
			iRet = (iMaxLineWidth - vLines[iLineIndex].iLineWidth)
			- SHIFT6(face->glyph->metrics.horiBearingX );
		} else {
			// left or other situation
			iRet = -SHIFT6(face->glyph->metrics.horiBearingX );
		}
		return iRet;
	}
		
	int computeLineStartY( FT_Face face, CCImage::ETextAlign eAlignMask, int txtHeight, int borderHeight ){
		int iRet;
		if (eAlignMask == CCImage::kAlignCenter || eAlignMask == CCImage::kAlignLeft ||
			eAlignMask == CCImage::kAlignRight ) {
			//vertical center
			iRet = (borderHeight - txtHeight)/2 + SHIFT6(face->size->metrics.ascender);

		} else if (eAlignMask == CCImage::kAlignBottomRight || 
				   eAlignMask == CCImage::kAlignBottom || 
				   eAlignMask == CCImage::kAlignBottomLeft ) {
			//vertical bottom
			iRet = borderHeight - txtHeight + SHIFT6(face->size->metrics.ascender);
		} else {
			// left or other situation
			iRet = SHIFT6(face->size->metrics.ascender);
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
			//CCLog(" ---- FT_New_Face with pFontName = %s", pFontName);
			iError = FT_New_Face( library, pFontName, 0, &face );
            
			if (iError) {
				//no valid font found use default
				//CCLog(" ---- no valid font, use default %s", pFontName);
				iError = FT_New_Face( library, "/usr/fonts/font_repository/monotype/arial.ttf", 0, &face );
			}
			CC_BREAK_IF(iError);
            
			//select utf8 charmap
			iError = FT_Select_Charmap(face,FT_ENCODING_UNICODE);
			CC_BREAK_IF(iError);
            
			iError = FT_Set_Pixel_Sizes(face, fontSize,fontSize);
			CC_BREAK_IF(iError);
            
			iError = divideString(face, text, nWidth, nHeight)?0:1;
            
			//compute the final line width
			iMaxLineWidth = MAX(iMaxLineWidth, nWidth);
            
			iMaxLineHeight = (face->size->metrics.ascender >> 6)
			- (face->size->metrics.descender >> 6);
			iMaxLineHeight *= vLines.size();
            
			int txtHeight = iMaxLineHeight;
            
			//compute the final line height
			iMaxLineHeight = MAX(iMaxLineHeight, nHeight);
			m_pData = new unsigned char[iMaxLineWidth * iMaxLineHeight*4];
//			iCurYCursor = SHIFT6(face->size->metrics.ascender);
        	iCurYCursor = computeLineStartY( face, eAlignMask, txtHeight, iMaxLineHeight );

			memset(m_pData,0, iMaxLineWidth * iMaxLineHeight*4);
            
            size_t lines = vLines.size();
            for (size_t i = 0; i < lines; i++) {
                const wchar_t* text_ptr = vLines[i].text;

				//initialize the origin cursor
				iCurXCursor = computeLineStart(face, eAlignMask, text_ptr[0], i);

                size_t text_len = wcslen(text_ptr);
                for (size_t i=0; i<text_len; ++i) {
                    int iError = FT_Load_Char(face, text_ptr[i], FT_LOAD_RENDER);
					if (iError) {
						break;
					}

					//  convert glyph to bitmap with 256 gray
					//  and get the bitmap
					FT_Bitmap& bitmap = face->glyph->bitmap;

                    int yoffset = iCurYCursor - (face->glyph->metrics.horiBearingY >> 6);
                    int xoffset = iCurXCursor + (face->glyph->metrics.horiBearingX >> 6);
					for (int i = 0; i < bitmap.rows; ++i) {
						for (int j = 0; j < bitmap.width; ++j) {
                            unsigned char cTemp = bitmap.buffer[i * bitmap.width + j];
                            if (cTemp == 0) continue;

							//  if it has gray>0 we set show it as 1, o otherwise
							int iY = yoffset + i;
							int iX = xoffset + j;

							if (iY>=iMaxLineHeight) {
								//exceed the height truncate
								continue;
							}

//							m_pData[(iY * iMaxLineWidth + iX) * 4 + 3] =
//							bitmap.buffer[i * bitmap.width + j] ?
//							0xff : 0;//alpha
//							m_pData[(iY * iMaxLineWidth + iX) * 4 + 1] =
//							bitmap.buffer[i * bitmap.width + j];//R
//							m_pData[(iY * iMaxLineWidth + iX) * 4 + 2] =
//							bitmap.buffer[i * bitmap.width + j];//G
//							m_pData[(iY * iMaxLineWidth + iX) * 4 + 0] =
//							bitmap.buffer[i * bitmap.width + j];//B

							int iTemp = cTemp << 24 | cTemp << 16 | cTemp << 8 | cTemp;
							*(int*) &m_pData[(iY * iMaxLineWidth + iX) * 4 + 0] = iTemp;
						}
					}
					//step to next glyph
					iCurXCursor += (face->glyph->metrics.horiAdvance >> 6)
					+ iInterval;
                    
					pText++;
				}
				iCurYCursor += (face->size->metrics.ascender >> 6)
				- (face->size->metrics.descender >> 6);
			}
			//print all image bitmap
            //			for (int i = 0; i < iMaxLineHeight; i++) {
            //				for (int j = 0; j < iMaxLineWidth; j++) {
            //					printf("%d",
            //							m_pData[(i * iMaxLineWidth + j) * 4] ? 1 : 0);
            //				}
            //				printf("\n");
            //			}
            
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

		std::string fullFontName = pFontName;
    	std::string lowerCasePath = fullFontName;
    	std::transform(lowerCasePath.begin(), lowerCasePath.end(), lowerCasePath.begin(), ::tolower);

    	if ( lowerCasePath.find(".ttf") != std::string::npos ) {
    		fullFontName = CCFileUtils::sharedFileUtils()->fullPathForFilename(pFontName);
    	}
        //CCLog("-----pText=%s and Font File is %s nWidth= %d,nHeight=%d",pText,fullFontName.c_str(),nWidth,nHeight);
        
        CC_BREAK_IF(! dc.getBitmap(pText, nWidth, nHeight, eAlignMask, fullFontName.c_str(), nSize));
        //CCLog("---- dc.getBitmap is Succesfull...");
        
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
        
    } while (0);
    
    return bRet;
}

NS_CC_END

