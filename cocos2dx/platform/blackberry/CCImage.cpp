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

#include <string.h>

#include <vector>
#include <string>
#include <sstream>

#include "CCImage.h"
#include "CCFileUtils.h"

#include "SkTypeface.h"
#include "SkBitmap.h"
#include "SkPaint.h"
#include "SkCanvas.h"

#include "ft2build.h"
#include FT_FREETYPE_H

#define szFont_kenning 2

#define SHIFT6(num) (num>>6)

using namespace std;

struct TextLine {
	string sLineStr;
	int iLineWidth;
};

NS_CC_BEGIN;

class BitmapDC
{
public:
    BitmapDC() : m_pBitmap(NULL),
    m_pPaint(NULL)
    {
    	libError = FT_Init_FreeType( &library );
		iInterval = szFont_kenning;
		m_pData = NULL;
		reset();
    }
    
    ~BitmapDC(void)
    {
    	FT_Done_FreeType(library);
		CC_SAFE_DELETE(m_pPaint);
		CC_SAFE_DELETE(m_pBitmap);
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
		FT_Load_Glyph(face, FT_Get_Char_Index(face, cLastChar),
                      FT_LOAD_DEFAULT);
        
        oTempLine.iLineWidth = iCurXCursor - SHIFT6((face->glyph->metrics.horiAdvance - face->glyph->metrics.horiBearingX - face->glyph->metrics.width))/*-iInterval*/;//TODO interval
		iMaxLineWidth = MAX(iMaxLineWidth, oTempLine.iLineWidth);
		ss.clear();
		ss.str("");
		vLines.push_back(oTempLine);
	}
    
	bool divideString(FT_Face face, const char* sText, int iMaxWidth, int iMaxHeight) {
		const char* pText = sText;
		int iError = 0;
		int iCurXCursor;
		iError = FT_Load_Glyph(face, FT_Get_Char_Index(face, *pText),
                               FT_LOAD_DEFAULT);
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
				iError = FT_Load_Glyph(face, FT_Get_Char_Index(face, *pText),
                                       FT_LOAD_DEFAULT);
				if (iError) {
					return false;
				}
				iCurXCursor = -SHIFT6(face->glyph->metrics.horiBearingX);
				continue;
			}
            
			iError = FT_Load_Glyph(face, FT_Get_Char_Index(face, *pText),
                                   FT_LOAD_DEFAULT);
            
			if (iError) {
				return false;
				//break;
			}
			//check its width
			//divide it when exceeding
			if ((iMaxWidth > 0
                 && iCurXCursor + SHIFT6(face->glyph->metrics.width)
                 > iMaxWidth)) {
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
			//CCLog("\n\n ---- FT_New_Face with pFontName = %s\n", pFontName);
			iError = FT_New_Face( library, pFontName, 0, &face );
            
			if (iError) {
				//no valid font found use default
				//CCLog("\n\n ---- no valid font, use default %s\n", pFontName);
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
            
			//compute the final line height
			iMaxLineHeight = MAX(iMaxLineHeight, nHeight);
			m_pData = new unsigned char[iMaxLineWidth * iMaxLineHeight*4];
			iCurYCursor = SHIFT6(face->size->metrics.ascender);
            
			memset(m_pData,0, iMaxLineWidth * iMaxLineHeight*4);
            
            for (size_t i = 0; i < vLines.size(); i++) {
				pText = vLines[i].sLineStr.c_str();
				//initialize the origin cursor
				iCurXCursor = computeLineStart(face, eAlignMask, *pText, i);
                
				while (*pText != 0) {
					int iError = FT_Load_Glyph(face, FT_Get_Char_Index(face, *pText),
                                               FT_LOAD_RENDER);
					if (iError) {
						break;
					}
                    
					//  convert glyph to bitmap with 256 gray
					//  and get the bitmap
					FT_Bitmap & bitmap = face->glyph->bitmap;
                    

					for (int i = 0; i < bitmap.rows; ++i) {
						for (int j = 0; j < bitmap.width; ++j) {
							//  if it has gray>0 we set show it as 1, o otherwise
							int iY = iCurYCursor + i
							- (face->glyph->metrics.horiBearingY
									>> 6);
							int iX = iCurXCursor
							+ (face->glyph->metrics.horiBearingX
									>> 6) + j;

							if (iY>=iMaxLineHeight) {
								//exceed the height truncate
								continue;
							}

							m_pData[(iY * iMaxLineWidth + iX) * 4 + 1] = bitmap.buffer[i * bitmap.width + j];//R
							m_pData[(iY * iMaxLineWidth + iX) * 4 + 2] = bitmap.buffer[i * bitmap.width + j];//G
							m_pData[(iY * iMaxLineWidth + iX) * 4 + 0] = bitmap.buffer[i * bitmap.width + j];//B

							m_pData[(iY * iMaxLineWidth + iX) * 4 + 3] = bitmap.buffer[i * bitmap.width + j];//alpha
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
    
	bool setFont(const char *pFontName = NULL, int nSize = 0)
	{
		bool bRet = false;
        
		if (m_pPaint)
		{
			delete m_pPaint;
			m_pPaint = NULL;
		}
        
		do
		{
			/* init paint */
			m_pPaint = new SkPaint();
			CC_BREAK_IF(! m_pPaint);
			m_pPaint->setColor(SK_ColorWHITE);
			m_pPaint->setTextSize(nSize);
            
			/* create font */
			SkTypeface *pTypeFace = SkTypeface::CreateFromName(pFontName, SkTypeface::kNormal);
			if (! pTypeFace)
			{
				// let's replace with Arial first before failing
				pTypeFace = SkTypeface::CreateFromName("Arial", SkTypeface::kNormal);
				CCLOG("could not find font %s replacing with Arial\n", pFontName);
                
				if (!pTypeFace)
				{
					CC_SAFE_DELETE(m_pPaint);
					break;
				}
			}
			m_pPaint->setTypeface( pTypeFace );
			/* cannot unref, I don't know why. It may be memory leak, but how to avoid? */
			pTypeFace->unref();
            
			bRet = true;
		} while (0);
        
		return bRet;
	}
    
	bool prepareBitmap(int nWidth, int nHeight)
	{
		// release bitmap
		if (m_pBitmap)
		{
			delete m_pBitmap;
			m_pBitmap = NULL;
		}
		
		if (nWidth > 0 && nHeight > 0)
		{
			/* create and init bitmap */
			m_pBitmap = new SkBitmap();
			if (! m_pBitmap)
			{
				return false;
			}
            
			/* use rgba8888 and alloc memory */
            m_pBitmap->setConfig(SkBitmap::kARGB_8888_Config, nWidth, nHeight);
			if (! m_pBitmap->allocPixels())
			{
				CC_SAFE_DELETE(m_pBitmap);
				return false;
			}
            
			/* start with black/transparent pixels */
			m_pBitmap->eraseColor(0);
		}
        
		return true;
	}
    
	bool drawText(const char *pszText, int nWidth, int nHeight, CCImage::ETextAlign eAlignMask)
    {
        bool bRet = false;
        
        do
        {
            CC_BREAK_IF(! pszText);
            CC_BREAK_IF(! prepareBitmap(nWidth, nHeight));
            
			/* create canvas */
			SkPaint::FontMetrics font;
			m_pPaint->getFontMetrics(&font);
			SkCanvas canvas(*m_pBitmap);
            
			/*
			 * draw text
			 * @todo: alignment
			 */
			canvas.drawText(pszText, strlen(pszText), 0.0, -font.fAscent, *m_pPaint);
			bRet = true;
        } while (0);
        
        return bRet;
    }
    
	bool getTextExtentPoint(const char * pszText, int *pWidth, int *pHeight)
	{
		bool bRet = false;
        
		do
		{
			CC_BREAK_IF(!pszText || !pWidth || !pHeight);
            
			// get text width and height
			if (m_pPaint)
			{
				SkPaint::FontMetrics font;
				m_pPaint->getFontMetrics(&font);
				*pHeight = (int)ceil((font.fDescent - font.fAscent));
				*pWidth = (int)ceil((m_pPaint->measureText(pszText, strlen(pszText))));
                
				bRet = true;
			}
		} while (0);
        
		return bRet;
	}
    
	SkBitmap* getBitmap()
	{
		return m_pBitmap;
	}
public:
	FT_Library library;
	unsigned char *m_pData;
	int libError;
	vector<TextLine> vLines;
	int iInterval;
	int iMaxLineWidth;
	int iMaxLineHeight;
	
private:
    SkPaint  *m_pPaint;
	SkBitmap *m_pBitmap;
    
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
#if (0)
        /* init font with font name and size */
		CC_BREAK_IF(!dc.setFont(pFontName, nSize))
        
		/* compute text width and height */
		if (nWidth <= 0 || nHeight <= 0)
		{
			dc.getTextExtentPoint(pText, &nWidth, &nHeight);
		}
		CC_BREAK_IF(nWidth <= 0 || nHeight <= 0);
        
		CC_BREAK_IF( false == dc.drawText(pText, nWidth, nHeight, eAlignMask) );
        
		/*init image information */
		SkBitmap *pBitmap = dc.getBitmap();
		CC_BREAK_IF(! pBitmap);
        
		int nWidth	= pBitmap->width();
		int nHeight	= pBitmap->height();
		CC_BREAK_IF(nWidth <= 0 || nHeight <= 0);
        
		int nDataLen = pBitmap->rowBytes() * pBitmap->height();
		m_pData = new unsigned char[nDataLen];
		CC_BREAK_IF(! m_pData);
		memcpy((void*) m_pData, pBitmap->getPixels(), nDataLen);
        
		m_nWidth    = (short)nWidth;
		m_nHeight   = (short)nHeight;
		m_bHasAlpha = true;
		m_bPreMulti = true;
		m_nBitsPerComponent = pBitmap->bytesPerPixel();
        
		bRet = true;
#endif
		const char* pFullFontName = CCFileUtils::fullPathFromRelativePath(pFontName);
        //CCLog("-----pText=%s and Font File is %s nWidth= %d,nHeight=%d",pText,pFullFontName,nWidth,nHeight);
        
        CC_BREAK_IF(! dc.getBitmap(pText, nWidth, nHeight, eAlignMask, pFullFontName, nSize));
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

NS_CC_END;

