#include <string.h>

#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <fontconfig/fontconfig.h>

#include "platform/CCFileUtils.h"
#include "platform/CCPlatformMacros.h"
#define __CC_PLATFORM_IMAGE_CPP__
#include "platform/CCImageCommon_cpp.h"
#include "platform/CCImage.h"
#include "platform/tizen/CCApplication.h"

#include "ft2build.h"
#include "CCStdC.h"

#include FT_FREETYPE_H

using namespace std;

// as FcFontMatch is quite an expensive call, cache the results of getFontFile
static std::map<std::string, std::string> fontCache;

struct LineBreakGlyph {
	FT_UInt glyphIndex;
	int paintPosition;
	int glyphWidth;

	int bearingX;
	int kerning;
	int horizAdvance;
};

struct LineBreakLine {
	LineBreakLine() : lineWidth(0) {}

	std::vector<LineBreakGlyph> glyphs;
	int lineWidth;

	void reset() {
		glyphs.clear();
		lineWidth = 0;
	}

	void calculateWidth() {
		lineWidth = 0;
		if ( glyphs.empty() == false ) {
			lineWidth = glyphs.at(glyphs.size() - 1).paintPosition + glyphs.at(glyphs.size() - 1).glyphWidth;
		}
	}
};

NS_CC_BEGIN
class BitmapDC
{
public:
	BitmapDC() {
		libError = FT_Init_FreeType( &library );
		FcInit();
		m_pData = NULL;
		reset();
	}

	~BitmapDC() {
		FT_Done_FreeType(library);
		FcFini();
		//data will be deleted by CCImage
//		if (m_pData) {
//			delete m_pData;
//		}
        reset();
	}

	void reset() {
		iMaxLineWidth = 0;
		iMaxLineHeight = 0;
		textLines.clear();
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

    bool isBreakPoint(FT_UInt currentCharacter, FT_UInt previousCharacter) {
    	if ( previousCharacter == '-' || previousCharacter == '/' || previousCharacter == '\\' ) {
    	   	// we can insert a line break after one of these characters
    	    return true;
    	}
    	return false;
    }

	bool divideString(FT_Face face, const char* sText, int iMaxWidth, int iMaxHeight) {
		const char* pText = sText;
		textLines.clear();
		iMaxLineWidth = 0;

		FT_UInt unicode;
		FT_UInt prevCharacter = 0;
		FT_UInt glyphIndex = 0;
		FT_UInt prevGlyphIndex = 0;
		FT_Vector delta;
		LineBreakLine currentLine;

		int currentPaintPosition = 0;
		int lastBreakIndex = -1;
		bool hasKerning = FT_HAS_KERNING( face );
        while ((unicode=utf8((char**)&pText))) {
            if (unicode == '\n') {
				currentLine.calculateWidth();
				iMaxLineWidth = max(iMaxLineWidth, currentLine.lineWidth);
				textLines.push_back(currentLine);
				currentLine.reset();
				prevGlyphIndex = 0;
				prevCharacter = 0;
				lastBreakIndex = -1;
				currentPaintPosition = 0;
				continue;
			}

            if ( isBreakPoint(unicode, prevCharacter) ) {
            	lastBreakIndex = currentLine.glyphs.size() - 1;
            }

			glyphIndex = FT_Get_Char_Index(face, unicode);
			if (FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT)) {
				return false;
			}

			if (unicode == ' ') {
				currentPaintPosition += face->glyph->metrics.horiAdvance >> 6;
				prevGlyphIndex = glyphIndex;
				prevCharacter = unicode;
				lastBreakIndex = currentLine.glyphs.size();
				continue;
			}

			LineBreakGlyph glyph;
			glyph.glyphIndex = glyphIndex;
			glyph.glyphWidth = face->glyph->metrics.width >> 6;
			glyph.bearingX = face->glyph->metrics.horiBearingX >> 6;
			glyph.horizAdvance = face->glyph->metrics.horiAdvance >> 6;
			glyph.kerning = 0;

			if (prevGlyphIndex != 0 && hasKerning) {
				FT_Get_Kerning(face, prevGlyphIndex, glyphIndex, FT_KERNING_DEFAULT, &delta);
				glyph.kerning = delta.x >> 6;
			}

			if (iMaxWidth > 0 && currentPaintPosition + glyph.bearingX + glyph.kerning + glyph.glyphWidth > iMaxWidth) {

				int glyphCount = currentLine.glyphs.size();
				if ( lastBreakIndex >= 0 && lastBreakIndex < glyphCount && currentPaintPosition + glyph.bearingX + glyph.kerning + glyph.glyphWidth - currentLine.glyphs.at(lastBreakIndex).paintPosition < iMaxWidth ) {
					// we insert a line break at our last break opportunity
					std::vector<LineBreakGlyph> tempGlyphs;
					std::vector<LineBreakGlyph>::iterator it = currentLine.glyphs.begin();
					std::advance(it, lastBreakIndex);
					tempGlyphs.insert(tempGlyphs.begin(), it, currentLine.glyphs.end());
					currentLine.glyphs.erase(it, currentLine.glyphs.end());
					currentLine.calculateWidth();
					iMaxLineWidth = max(iMaxLineWidth, currentLine.lineWidth);
					textLines.push_back(currentLine);
					currentLine.reset();
					currentPaintPosition = 0;
					for ( it = tempGlyphs.begin(); it != tempGlyphs.end(); it++ ) {
						if ( currentLine.glyphs.empty() ) {
							currentPaintPosition = -(*it).bearingX;
							(*it).kerning = 0;
						}
						(*it).paintPosition = currentPaintPosition + (*it).bearingX + (*it).kerning;
						currentLine.glyphs.push_back((*it));
						currentPaintPosition += (*it).kerning + (*it).horizAdvance;
					}
				} else {
					// the current word is too big to fit into one line, insert line break right here
					currentPaintPosition = 0;
					glyph.kerning = 0;
					currentLine.calculateWidth();
					iMaxLineWidth = max(iMaxLineWidth, currentLine.lineWidth);
					textLines.push_back(currentLine);
					currentLine.reset();
				}

				prevGlyphIndex = 0;
				prevCharacter = 0;
				lastBreakIndex = -1;
			} else {
				prevGlyphIndex = glyphIndex;
				prevCharacter = unicode;
			}

			if ( currentLine.glyphs.empty() ) {
				currentPaintPosition = -glyph.bearingX;
			}
			glyph.paintPosition = currentPaintPosition + glyph.bearingX + glyph.kerning;
			currentLine.glyphs.push_back(glyph);
			currentPaintPosition += glyph.kerning + glyph.horizAdvance;
		}

		if ( currentLine.glyphs.empty() == false ) {
			currentLine.calculateWidth();
			iMaxLineWidth = max(iMaxLineWidth, currentLine.lineWidth);
			textLines.push_back(currentLine);
		}
		return true;
	}

	/**
	 * compute the start pos of every line
	 */
	int computeLineStart(FT_Face face, CCImage::ETextAlign eAlignMask, int line) {
				int lineWidth = textLines.at(line).lineWidth;
		if (eAlignMask == CCImage::kAlignCenter || eAlignMask == CCImage::kAlignTop || eAlignMask == CCImage::kAlignBottom) {
			return (iMaxLineWidth - lineWidth) / 2;
		} else if (eAlignMask == CCImage::kAlignRight || eAlignMask == CCImage::kAlignTopRight || eAlignMask == CCImage::kAlignBottomRight) {
			return (iMaxLineWidth - lineWidth);
		}

		// left or other situation
		return 0;
	}

	int computeLineStartY( FT_Face face, CCImage::ETextAlign eAlignMask, int txtHeight, int borderHeight ){
		int baseLinePos = ceilf(FT_MulFix( face->bbox.yMax, face->size->metrics.y_scale )/64.0f);
		if (eAlignMask == CCImage::kAlignCenter || eAlignMask == CCImage::kAlignLeft || eAlignMask == CCImage::kAlignRight) {
			//vertical center
			return (borderHeight - txtHeight) / 2 + baseLinePos;
		} else if (eAlignMask == CCImage::kAlignBottomRight || eAlignMask == CCImage::kAlignBottom || eAlignMask == CCImage::kAlignBottomLeft) {
			//vertical bottom
			return borderHeight - txtHeight + baseLinePos;
		}

		// top alignment
		return baseLinePos;
	}

    std::string getFontFile(const char* family_name) {
    	std::string fontPath = family_name;

    	std::map<std::string, std::string>::iterator it = fontCache.find(family_name);
    	if ( it != fontCache.end() ) {
    		return it->second;
    	}

    	// check if the parameter is a font file shipped with the application
    	std::string lowerCasePath = fontPath;
    	std::transform(lowerCasePath.begin(), lowerCasePath.end(), lowerCasePath.begin(), ::tolower);
    	if ( lowerCasePath.find(".ttf") != std::string::npos ) {
    		fontPath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(fontPath.c_str());

    		FILE *f = fopen(fontPath.c_str(), "r");
    		if ( f ) {
    			fclose(f);
    			fontCache.insert(std::pair<std::string, std::string>(family_name, fontPath));
    			return fontPath;
    		}
    	}

    	// use fontconfig to match the parameter against the fonts installed on the system
    	FcPattern *pattern = FcPatternBuild (0, FC_FAMILY, FcTypeString, family_name, (char *) 0);
    	FcConfigSubstitute(0, pattern, FcMatchPattern);
    	FcDefaultSubstitute(pattern);

    	FcResult result;
    	FcPattern *font = FcFontMatch(0, pattern, &result);
    	if ( font ) {
    		FcChar8 *s = NULL;
    		if ( FcPatternGetString(font, FC_FILE, 0, &s) == FcResultMatch ) {
    			fontPath = (const char*)s;

    			FcPatternDestroy(font);
    			FcPatternDestroy(pattern);

    			fontCache.insert(std::pair<std::string, std::string>(family_name, fontPath));
    			return fontPath;
    		}
    		FcPatternDestroy(font);
    	}
    	FcPatternDestroy(pattern);

    	return family_name;
    }

	bool getBitmap(const char *text, int nWidth, int nHeight, CCImage::ETextAlign eAlignMask, const char * pFontName, float fontSize) {
		if (libError) {
			return false;
		}

		FT_Face face;
		std::string fontfile = getFontFile(pFontName);
		if ( FT_New_Face(library, fontfile.c_str(), 0, &face) ) {
			//no valid font found use default
			if ( FT_New_Face(library, "/usr/share/fonts/TizenSansRegular.ttf", 0, &face) ) {
				return false;
			}
		}

		//select utf8 charmap
		if ( FT_Select_Charmap(face, FT_ENCODING_UNICODE) ) {
			FT_Done_Face(face);
			return false;
		}

		if ( FT_Set_Pixel_Sizes(face, fontSize, fontSize) ) {
			FT_Done_Face(face);
			return false;
		}

		if ( divideString(face, text, nWidth, nHeight) == false ) {
			FT_Done_Face(face);
			return false;
		}

		//compute the final line width
		iMaxLineWidth = MAX(iMaxLineWidth, nWidth);

		//compute the final line height
		iMaxLineHeight = ceilf(FT_MulFix( face->bbox.yMax - face->bbox.yMin, face->size->metrics.y_scale )/64.0f);
		int lineHeight = face->size->metrics.height>>6;
		if ( textLines.size() > 0 ) {
			iMaxLineHeight += (lineHeight * (textLines.size() -1));
		}
		int txtHeight = iMaxLineHeight;
		iMaxLineHeight = MAX(iMaxLineHeight, nHeight);

		m_pData = new unsigned char[iMaxLineWidth * iMaxLineHeight * 4];
		memset(m_pData,0, iMaxLineWidth * iMaxLineHeight*4);

		int iCurYCursor = computeLineStartY(face, eAlignMask, txtHeight, iMaxLineHeight);

		int lineCount = textLines.size();
		for (int line = 0; line < lineCount; line++) {
			int iCurXCursor = computeLineStart(face, eAlignMask, line);

			int glyphCount = textLines.at(line).glyphs.size();
			for (int i = 0; i < glyphCount; i++) {
				LineBreakGlyph glyph = textLines.at(line).glyphs.at(i);

				if (FT_Load_Glyph(face, glyph.glyphIndex, FT_LOAD_RENDER)) {
					continue;
				}

				FT_Bitmap& bitmap = face->glyph->bitmap;
				int yoffset = iCurYCursor - (face->glyph->metrics.horiBearingY >> 6);
				int xoffset = iCurXCursor + glyph.paintPosition;

				for (int y = 0; y < bitmap.rows; ++y) {
                    int iY = yoffset + y;
                    if (iY>=iMaxLineHeight) {
                        //exceed the height truncate
                        break;
                    }
                    iY *= iMaxLineWidth;

                    int bitmap_y = y * bitmap.width;

					for (int x = 0; x < bitmap.width; ++x) {
						unsigned char cTemp = bitmap.buffer[bitmap_y + x];
						if (cTemp == 0) {
							continue;
						}

						int iX = xoffset + x;

						int iTemp = cTemp << 24 | cTemp << 16 | cTemp << 8 | cTemp;
						*(int*) &m_pData[(iY + iX) * 4 + 0] = iTemp;
					}
				}
			}
			// step to next line
			iCurYCursor += lineHeight;
		}

		//  free face
		FT_Done_Face(face);
		return true;
	}

public:
	FT_Library library;

	unsigned char *m_pData;
	int libError;
	std::vector<LineBreakLine> textLines;
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

		//const char* pFullFontName = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pFontName);

		CC_BREAK_IF(! dc.getBitmap(pText, nWidth, nHeight, eAlignMask, pFontName, nSize));

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
