#include <string.h>

#include <vector>
#include <string>
#include <sstream>

#include "CCFileUtils.h"

#include "CCPlatformMacros.h"
#include "CCImage.h"
#include "ft2build.h"
#include "CCStdC.h"
#include "platform/CCImageCommon_cpp.h"
#include FT_FREETYPE_H

#define szFont_kenning 2

#define SHIFT6(num) (num>>6)

using namespace std;

struct TextLine {
	string sLineStr;
	int iLineWidth;
};

NS_CC_BEGIN
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
//		if (m_pData) {
//			delete m_pData;
//		}

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

        oTempLine.iLineWidth = iCurXCursor - SHIFT6((face->glyph->metrics.horiAdvance + face->glyph->metrics.horiBearingX - face->glyph->metrics.width))/*-iInterval*/;//TODO interval
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
			iError = FT_New_Face( library, pFontName, 0, &face );

			if (iError) {
				//no valid font found use default
//				CCLog("no valid font, use default %s\n", pFontName);
				iError = FT_New_Face( library, "/usr/share/fonts/truetype/freefont/FreeSerif.ttf", 0, &face );
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

//							m_pData[(iY * iMaxLineWidth + iX) * 4 + 3] =
//							bitmap.buffer[i * bitmap.width + j] ?
//							0xff : 0;//alpha
//							m_pData[(iY * iMaxLineWidth + iX) * 4 + 1] =
//							bitmap.buffer[i * bitmap.width + j];//R
//							m_pData[(iY * iMaxLineWidth + iX) * 4 + 2] =
//							bitmap.buffer[i * bitmap.width + j];//G
//							m_pData[(iY * iMaxLineWidth + iX) * 4 + 0] =
//							bitmap.buffer[i * bitmap.width + j];//B
							int iTemp = 0;
							unsigned char cTemp = bitmap.buffer[i
							* bitmap.width + j];
							iTemp |= (cTemp ? 0xff : 0)<<24;
							iTemp |= cTemp << 16 | cTemp << 8 | cTemp;
							*(int*) &m_pData[(iY * iMaxLineWidth + iX)
							* 4 + 0] = iTemp;
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
		const char * pText,
		int nWidth/* = 0*/,
		int nHeight/* = 0*/,
		ETextAlign eAlignMask/* = kAlignCenter*/,
		const char * pFontName/* = nil*/,
		int nSize/* = 0*/)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(! pText);

		BitmapDC &dc = sharedBitmapDC();

		const char* pFullFontName = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pFontName);

		CC_BREAK_IF(! dc.getBitmap(pText, nWidth, nHeight, eAlignMask, pFullFontName, nSize));

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

NS_CC_END
