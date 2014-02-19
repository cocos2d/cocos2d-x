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
#include <map>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

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
		iInterval = szFont_kenning;
		m_pData = NULL;
		reset();
    }
    
    ~BitmapDC(void)
    {
    }
    
    void reset() {
		iMaxLineWidth = 0;
		iMaxLineHeight = 0;
		vLines.clear();
	}
    
    void buildLine(std::stringstream& ss, TTF_Font *face)
    {
        TextLine oTempLine;
        ss << '\0';
        oTempLine.sLineStr = ss.str();

        int w, h;
        TTF_SizeText(face, oTempLine.sLineStr.c_str(), &w, &h);

        oTempLine.iLineWidth = w;

        iMaxLineWidth = MAX(iMaxLineWidth, oTempLine.iLineWidth);
        ss.clear();
        ss.str("");
        vLines.push_back(oTempLine);
	}

	bool divideString(TTF_Font *face, const char* sText, int iMaxWidth, int iMaxHeight) {
        const char* pText = sText;

        //init stringstream
        std::stringstream ss;
        int w, h;

        while (*pText != '\0') {
            if (*pText == '\n') {
                buildLine(ss, face);

                pText++;
                continue;
            }
     
            //check its width
            //divide it when exceeding
            std::string s = ss.str();
            s.push_back(*pText);
            TTF_SizeText(face, s.c_str(), &w, &h);

            if (iMaxWidth > 0 && (w > iMaxWidth)) {
                buildLine(ss, face);
            }

            ss << *pText;
            pText++;

        }

        buildLine(ss, face);

        return true;
	}

	/**
	 * compute the start pos of every line
	 *
	 * return >0 represent the start x pos of the line
	 * while -1 means fail
	 *
	 */
	int computeLineStart(TTF_Font *face, CCImage::ETextAlign eAlignMask, char cText,
                         int iLineIndex) {
        return 0;
        /*
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
        */
	}
		
	int computeLineStartY( TTF_Font *face, CCImage::ETextAlign eAlignMask, int txtHeight, int borderHeight ){
        return 0;
        /*
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
        */
	}
    
	bool getBitmap(const char *text, int nWidth, int nHeight, CCImage::ETextAlign eAlignMask, const char * pFontName, float fontSize) {
		const char* pText = text;
        // No need to release m_pData here as it is destroyed by CCImage.

		int iCurXCursor;

        TTF_Font *face = TTF_OpenFont(pFontName, fontSize);
        if(!face)
        {
            return false;
        }

        divideString(face, text, nWidth, nHeight);

        //compute the final line width
        iMaxLineWidth = MAX(iMaxLineWidth, nWidth);

        iMaxLineHeight = (int)fontSize;
        iMaxLineHeight *= vLines.size();

        //compute the final line height
        iMaxLineHeight = MAX(iMaxLineHeight, nHeight);

        uint bitmapSize = iMaxLineWidth * iMaxLineHeight * 4;

        m_pData = new unsigned char[bitmapSize];
        memset(m_pData, 0, bitmapSize);

        // XXX: Can this be optimized by inserting newlines into the string and
        // making a single TTF_RenderText_Solid call? Could conceivably just
        // pass back SDL's buffer then, though would need additional logic to
        // call SDL_FreeSurface appropriately.
        for (size_t l = 0; l < vLines.size(); l++) {
            pText = vLines[l].sLineStr.c_str();
            //initialize the origin cursor
            iCurXCursor = computeLineStart(face, eAlignMask, *pText, l);

            SDL_Color color = { 0xff, 0xff, 0xff, 0xff };
            SDL_Surface *tSurf = TTF_RenderText_Solid(face, pText, color);
            SDL_LockSurface(tSurf);
            SDL_UnlockSurface(tSurf);

            // We treat pixels as 32-bit words, since both source and target
            // are rendered as such.
            int *pixels = (int*) tSurf->pixels;
            int *out = (int*)m_pData;

            for(int i = 0; i < tSurf->h; ++i)
            {
                for(int j = 0; j < tSurf->w; ++j)
                {
                    int targetOffset = (l * iMaxLineHeight + i) * iMaxLineWidth + j;
                    int sourceOffset = i * tSurf->w + j;

                    // HTML5 canvas is non-pre-alpha-multiplied, so alpha-multiply here.
                    unsigned char *p = (unsigned char*) &pixels[sourceOffset];
                    out[targetOffset] = CC_RGB_PREMULTIPLY_ALPHA( p[0], p[1], p[2], p[3] );
                }
            }
            SDL_FreeSurface(tSurf);
        }

        //clear all lines
        vLines.clear();

        TTF_CloseFont(face);

        return true;
    }

public:
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

        CC_BREAK_IF(! dc.getBitmap(pText, nWidth, nHeight, eAlignMask, fullFontName.c_str(), nSize));
        
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

