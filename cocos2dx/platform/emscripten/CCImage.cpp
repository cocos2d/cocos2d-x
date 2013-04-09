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
#include <map>

#define szFont_kenning 2

#define RSHIFT6(num) ((num)>>6)

using namespace std;

struct TextLine {
	std::string sLineStr;
	int iLineWidth;
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

    void buildLine(std::stringstream& ss, FT_Face face, int iCurXCursor, char cLastChar )
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
        iCurXCursor = -RSHIFT6(face->glyph->metrics.horiBearingX);
        //init stringstream
        std::stringstream ss;

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
            iCurXCursor += RSHIFT6(face->glyph->metrics.horiAdvance) + iInterval;
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
		int iError = FT_Load_Glyph(face, FT_Get_Char_Index(face, cText),
                                   FT_LOAD_DEFAULT);
		if (iError) {
			return -1;
		}
        
		if (eAlignMask == CCImage::kAlignCenter) {
			iRet = (iMaxLineWidth - vLines[iLineIndex].iLineWidth) / 2
			- RSHIFT6(face->glyph->metrics.horiBearingX );
            
		} else if (eAlignMask == CCImage::kAlignRight) {
			iRet = (iMaxLineWidth - vLines[iLineIndex].iLineWidth)
			- RSHIFT6(face->glyph->metrics.horiBearingX );
		} else {
			// left or other situation
			iRet = -RSHIFT6(face->glyph->metrics.horiBearingX );
		}
		return iRet;
	}
		
	int computeLineStartY( FT_Face face, CCImage::ETextAlign eAlignMask, int txtHeight, int borderHeight ){
		int iRet;
		if (eAlignMask == CCImage::kAlignCenter || eAlignMask == CCImage::kAlignLeft ||
			eAlignMask == CCImage::kAlignRight ) {
			//vertical center
			iRet = (borderHeight - txtHeight)/2 + RSHIFT6(face->size->metrics.ascender);

		} else if (eAlignMask == CCImage::kAlignBottomRight || 
				   eAlignMask == CCImage::kAlignBottom || 
				   eAlignMask == CCImage::kAlignBottomLeft ) {
			//vertical bottom
			iRet = borderHeight - txtHeight + RSHIFT6(face->size->metrics.ascender);
		} else {
			// left or other situation
			iRet = RSHIFT6(face->size->metrics.ascender);
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
        
        unsigned char cTemp ;
        int iY, iX, iTemp ;
        uint32 offset, rowOffset ;

		int iCurXCursor, iCurYCursor;
		bool bRet = false;
		if (libError) {
			return false;
		}
		do {
            std::string fontPath = pFontName;
            if(m_fontCache.count(fontPath))
            {
                face = m_fontCache[fontPath];
            }
            else
            {
                //CCLog("\n\n ---- FT_New_Face with pFontName = %s\n", pFontName);
                iError = FT_New_Face( library, pFontName, 0, &face );

                if (iError) {
                    int len = strlen(pFontName) + 11; // 11 = strlen('fonts/.ttf\0')
                    char *fullPath = (char*)malloc(len);
                    snprintf(fullPath, len, "fonts/%s.ttf", pFontName);
                    iError = FT_New_Face( library, fullPath, 0, &face );
                    free(fullPath);
                }

                if (iError) {
                    //no valid font found use default
                    //CCLog("\n\n ---- no valid font, use default %s\n", pFontName);
                    iError = FT_New_Face( library, "fonts/arial.ttf", 0, &face );
                }

                CC_BREAK_IF(iError);
                m_fontCache[fontPath] = face;
            }
            
			//select utf8 charmap
			iError = FT_Select_Charmap(face,FT_ENCODING_UNICODE);
			CC_BREAK_IF(iError);
            
			iError = FT_Set_Pixel_Sizes(face, fontSize,fontSize);
			CC_BREAK_IF(iError);
            
            iError = divideString(face, text, nWidth, nHeight) ? 0 : 1 ;

            //compute the final line width
            iMaxLineWidth = MAX(iMaxLineWidth, nWidth);

            FT_Pos ascenderPixels = RSHIFT6(face->size->metrics.ascender) ;
            FT_Pos descenderPixels = RSHIFT6(face->size->metrics.descender) ;

            iMaxLineHeight = ascenderPixels - descenderPixels;
            iMaxLineHeight *= vLines.size();

            //compute the final line height
            iMaxLineHeight = MAX(iMaxLineHeight, nHeight);

            uint bitmapSize = iMaxLineWidth * iMaxLineHeight*4 ;

            m_pData = new unsigned char[bitmapSize];
            memset(m_pData,0, bitmapSize);

            const char* pText = text;
            iCurYCursor = ascenderPixels;

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

                    FT_Pos horiBearingYPixels = RSHIFT6(face->glyph->metrics.horiBearingY) ;
                    FT_Pos horiBearingXPixels = RSHIFT6(face->glyph->metrics.horiBearingX) ;
                    FT_Pos horiAdvancePixels = RSHIFT6(face->glyph->metrics.horiAdvance) ;

                    for (int i = 0; i < bitmap.rows; ++i) {

                        iY = iCurYCursor + i - horiBearingYPixels;
                        if (iY < 0 || iY>=iMaxLineHeight) {
                            //exceed the height truncate
                            continue;
                        }

                        rowOffset = iY * iMaxLineWidth ;

                        // if it has gray>0 we set show it as 1, otherwise 0 
                        char cbuf[1024];
                        for (int j = 0; j < bitmap.width; ++j) {
                            cTemp = bitmap.buffer[i	* bitmap.width + j];
                            cbuf[j] = cTemp > 64 ? '*' : ' ';
                            cbuf[j+1] = 0;

                            if( cTemp )
                            {
                                iX = iCurXCursor + j + horiBearingXPixels;

                                offset = (rowOffset + iX) * 4 ;

                                assert( (offset + 3) < bitmapSize ) ;

                                iTemp = cTemp << 24 | cTemp << 16 | cTemp << 8 | cTemp;
                                *(int*) &m_pData[ offset ] = iTemp ;	// ARGB
                            }
                        }

                    }

                    //step to next glyph
                    iCurXCursor += horiAdvancePixels + iInterval;
                    pText++;
                }
                iCurYCursor += ascenderPixels - descenderPixels ;
            }

            //clear all lines
            vLines.clear();

            //success;
            if (iError) {
                bRet = false;
            } else {
                bRet = true;
            }
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
    map<string, FT_Face> m_fontCache;
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
        //CCLog("---- dc.getBitmap is Succesfull... \n");
        
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

