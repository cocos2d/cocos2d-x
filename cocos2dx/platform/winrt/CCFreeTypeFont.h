/****************************************************************************
Copyright (c) 2010 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

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

#ifndef __PLATFORM_WINRT_FREETYPE_H__
#define __PLATFORM_WINRT_FREETYPE_H__

#include "platform/CCCommon.h"
#include "platform/CCImage.h"
#include <string>
#include <vector>
#include <memory>

#define generic GenericFromFreeTypeLibrary
#define internal InternalFromFreeTypeLibrary
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#undef generic
#undef internal

NS_CC_BEGIN

typedef struct TGlyph_
{
	FT_UInt    index;  // glyph index
    FT_Vector  pos;    // glyph origin on the baseline
	FT_Glyph   image;  // glyph image
} TGlyph, *PGlyph;

typedef struct FontBufferInfo
{
	unsigned char*  pBuffer;  
	unsigned long  size;  
} FontBufferInfo;

typedef struct FTWordInfo
{
	std::vector<TGlyph> glyphs; // glyphs for the word
	FT_BBox             bbox;   // bounding box containing all of the glyphs in the word
} FTWordInfo;


typedef struct FTLineInfo
{
	std::vector<TGlyph> glyphs;     // glyphs for the line text
	FT_BBox             bbox;       // bounding box containing all of the glyphs in the line
    unsigned int        width;      // width of the line     
    FT_Vector           pen;        // current pen position
} FTLineInfo;


class CC_DLL CCFreeTypeFont
{
public:
    CCFreeTypeFont();
    ~CCFreeTypeFont();

	bool initWithString(
        const char* pText, 
        const char* pFontName,
        int         nSize,
        int         width,
        int         height
    );

    unsigned char* getBitmap(
        CCImage::ETextAlign eAlignMask,
        int* outWidth, 
        int* outHeight
    );

#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8

    /// <summary>
    /// These are the officially supported WP8 fonts listed at:
    /// http://msdn.microsoft.com/en-us/library/windows/apps/hh202920(v=vs.105).aspx
    /// </summary>
    enum class SystemFont
    {
        /* UI Fonts */
        SEGOE_WP,               // Latin, Cyrillic, Greek, Arabic, and Hebrew–based languages
        DENG_XIAN,              // Chinese (Simplified)
        MICROSOFT_MHEI,         // Chinese (Traditional)
        YU_GOTHIC,              // Japanese
        MICROSOFT_NEO_GOTHIC,   // Korean
        SEGOE_UI,               // Latin, Cyrillic, Greek, Arabic, and Hebrew–based languages
        NIRMALA_UI,             // India languages
        LEELAWADEE,             // Thai
        SEGOE_UI_SYMBOL,        // Supports various Unicode symbols, including emoji symbols added in Unicode 6.0.

        /* Text display fonts */
        EBRIMA,                 // Nko, Ethiopic, Tifinagh, Vai, and Osmanya
        ESTRANGELO_EDESSA,      // Syriac
        GADUGI,                 // Cherokee, and Unified Canadian Aboriginal Syllabics
        KHMER_UI,               // Khmer
        LAO_UI,                 // Lao
        MICROSOFT_HIMALAYA,     // Tibetan
        MICROSOFT_NEW_TAI_LUE,  // New Tai Lue
        MICROSOFT_TAI_LE,       // Tai Le
        MICROSOFT_UIGHUR,       // Uighur
        MICROSOFT_YI_BAITI,     // Yi
        MONGOLIAN_BAITI,        // Mongolian
        MV_BOLI,                // Thaana
        PHAGS_PA,               // Phags-pa
        SIM_SUN,                // Chinese (Simplified)
        URDU_TYPESETTING,       // Arabic

        /* Additional fonts */
        ARIAL,
        ARIAL_BLACK,
        CALIBRI,
        CALIBRI_LIGHT,
        COMIC_SANS_MS,
        COURIER_NEW,
        GEORGIA,
        LUCIDA_SANS_UNICODE,
        TAHOMA,
        TIMES_NEW_ROMAN,
        TREBUCHET_MS,
        VERDANA,

        /* Mathematical and symbol fonts */
        CAMBRIA_AND_CAMBRIA_MATH,
        WINGDINGS,
        WEBDINGS
    };

    /// <summary>Return the corresponding file name for the requested system font.</summary>
    /// <param name="systemFont">The requested system font.</param>
    /// <returns>The name of the curresponding system font.</returns>
    static const char* getSystemFontFileName(SystemFont systemFont);

#endif

    /// <summary>
    /// Strings is drawn one glyph at a time. If no glyph can be found for a given font then it normally prints out a square.
    /// The fallback fonts are used when a glyph cannot be found for a string.
    /// Setting the fallback fonts loads them to be used as fallbacks in case a glyph can't be found in the otherwise provided fonts.
    /// E.g. When trying to print a chinese character when using Arial.
    /// </summary>
    /// <param name="fonts">These fonts will be used as fallback.</param>
    /// <example> On Windows Phone 8 you could set fallback fonts like this:
    /// <code>
    /// std::vector&lt;const char*&gt; systemFonts;
    /// systemFonts.push_back(CCFreeTypeFont::getSystemFontFileName(CCFreeTypeFont::SystemFont::MICROSOFT_NEO_GOTHIC));
    /// systemFonts.push_back(CCFreeTypeFont::getSystemFontFileName(CCFreeTypeFont::SystemFont::DENG_XIAN));
    /// systemFonts.push_back(CCFreeTypeFont::getSystemFontFileName(CCFreeTypeFont::SystemFont::MICROSOFT_MHEI));
    /// systemFonts.push_back(CCFreeTypeFont::getSystemFontFileName(CCFreeTypeFont::SystemFont::YU_GOTHIC));
    /// CCFreeTypeFont::setFallbackFonts(systemFonts);
    /// </code>
    /// Note that to include CCFreeTypeFont.h you will need to add the following to your C++ Include Directories:
    /// $(ProjectDir)..\..\..\cocos2d-x\cocos2dx\platform\third_party\winrt\freetype\include;
    /// </example>
    static void setFallbackFonts(const std::vector<const char*>& fonts);

private:
	static unsigned char* loadFont(const char *pFontName, unsigned long *size);

    static unsigned char* CCFreeTypeFont::loadSystemFont(const char *pFontName, unsigned long *size);

    FT_Error CCFreeTypeFont::initGlyphs(const char* text);
    FT_Error CCFreeTypeFont::initWordGlyphs(std::vector<TGlyph>& glyphs, const std::string& text, FT_Vector& pen);

	void compute_bbox(std::vector<TGlyph>& glyphs, FT_BBox  *abbox);

    void drawText(FTLineInfo* pInfo, unsigned char* pBuffer, FT_Vector *pen);

    void draw_bitmap(unsigned char* pBuffer, FT_Bitmap*  bitmap,FT_Int x,FT_Int y);

    void initWords(const char* text);

    void reset();

    FT_Vector getPenForAlignment(FTLineInfo* pInfo, CCImage::ETextAlign eAlignMask, int lineNumber, int totalLines);

    FT_Error addWord(const std::string& word);
    void newLine();
    void endLine();

    const std::string m_space;

	std::string		m_text;
	std::string		m_fontName;
	FT_Face			m_face;
	std::vector<FTLineInfo*> m_lines;

    int             m_inWidth;      // requested width of text box
    int             m_inHeight;     // requested height of text box
    int             m_width;        // final bitMap width
    int             m_height;       // final bitMap height
    int             m_textWidth;    // width of text text after word wrapping and line breaks    
    int             m_textHeight;   // height of text text after word wrapping and line breaks  
    int             m_lineHeight;   // height of a line for the font size
    int             m_windowWidth;  // the width of the window

    FTLineInfo*     m_currentLine;  // the current line object to add words to.
};

NS_CC_END

#endif