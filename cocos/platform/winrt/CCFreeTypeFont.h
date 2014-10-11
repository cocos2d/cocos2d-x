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
#include "platform/CCDevice.h"
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

    unsigned char* initWithString(const char * text, const FontDefinition& textDefinition, Device::TextAlign align, int &width, int &height, ssize_t& dataLength);



private:

    unsigned char* getBitmap(Device::TextAlign eAlignMask, int &width, int &height, ssize_t& dataLength);


	unsigned char* loadFont(const char *pFontName, ssize_t* size);

    unsigned char* CCFreeTypeFont::loadSystemFont(const char *pFontName, ssize_t* size);

    FT_Error CCFreeTypeFont::initGlyphs(const char* text);
    FT_Error CCFreeTypeFont::initWordGlyphs(std::vector<TGlyph>& glyphs, const std::string& text, FT_Vector& pen);

	void compute_bbox(std::vector<TGlyph>& glyphs, FT_BBox  *abbox);

    void drawText(FTLineInfo* pInfo, unsigned char* pBuffer, FT_Vector *pen);

    void draw_bitmap(unsigned char* pBuffer, FT_Bitmap*  bitmap,FT_Int x,FT_Int y);

    void initWords(const char* text);

    void reset();

    FT_Vector getPenForAlignment(FTLineInfo* pInfo, Device::TextAlign eAlignMask, int lineNumber, int totalLines);

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

    int             m_fontFillColorR;
    int             m_fontFillColorG;
    int             m_fontFillColorB;
};

NS_CC_END

#endif
