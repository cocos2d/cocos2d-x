/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 
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

#include <stdio.h>

#include "support/ccUTF8.h"
#include "CCFontFreeType.h"
#include "CCTextImage.h"
#include "CCFont.h"
#include "CCFontDefinition.h"

NS_CC_BEGIN


FT_Library FontFreeType::_FTlibrary;
bool       FontFreeType::_FTInitialized = false;

FontFreeType * FontFreeType::create(const std::string &fontName, int fontSize, GlyphCollection glyphs, const char *customGlyphs)
{
    if( glyphs == GlyphCollection::DYNAMIC )
    {
        log("ERROR: GlyphCollection::DYNAMIC is not supported yet!");
        return nullptr;
    }
    
    FontFreeType *tempFont =  new FontFreeType();
    
    if (!tempFont)
        return nullptr;
    
    tempFont->setCurrentGlyphCollection(glyphs, customGlyphs);
    
    if (!tempFont->createFontObject(fontName, fontSize))
    {
        delete tempFont;
        return nullptr;
    }
    
    return tempFont;
}

bool FontFreeType::initFreeType()
{
    if (_FTInitialized == false)
    {
        // begin freetype
        if (FT_Init_FreeType( &_FTlibrary ))
            return false;
        
        _FTInitialized = true;
    }
    
    return  _FTInitialized;
}

void FontFreeType::shutdownFreeType()
{
    if (_FTInitialized == true)
    {
        FT_Done_FreeType(_FTlibrary);
    }
}

FT_Library FontFreeType::getFTLibrary()
{
    initFreeType();
    return _FTlibrary;
}

FontFreeType::FontFreeType() : _letterPadding(5)
{
}

bool FontFreeType::createFontObject(const std::string &fontName, int fontSize)
{
    int dpi = 72;
    
    int len = 0;
    unsigned char* data = FileUtils::getInstance()->getFileData(fontName.c_str(), "rb", (unsigned long *)(&len));
    
    if (!data)
        return false;
    
    // create the new face
    FT_Face face;
    
    // create the face from the data
    if (FT_New_Memory_Face(getFTLibrary(), data, len, 0, &face ))
        return false;
    
    //we want to use unicode
    if (FT_Select_Charmap(face, FT_ENCODING_UNICODE))
        return false;
    
    // set the requested font size
	int fontSizePoints = (int)(64.f * fontSize);
	if (FT_Set_Char_Size(face, fontSizePoints, fontSizePoints, dpi, dpi))
        return false;
    
    // store the face globally
    _fontRef = face;
    
    // save font name locally
    _fontName = fontName;
    
    // done and good
    return true;
}

FontFreeType::~FontFreeType()
{
    // release the font
    // TO DO 
}

FontAtlas * FontFreeType::createFontAtlas()
{
    FontDefinitionTTF *def = FontDefinitionTTF::create(this);
    
    if (!def)
        return nullptr;
    
    FontAtlas *atlas = def->createFontAtlas();
    
    // release the font definition, we don't need it anymore
    def->release();
    return atlas;
}

bool FontFreeType::getBBOXFotChar(unsigned short theChar, Rect &outRect) const
{
    if (!_fontRef)
        return false;
    
    // get the ID to the char we need
    int glyph_index = FT_Get_Char_Index(_fontRef, theChar);
    
    if (!glyph_index)
        return false;
    
    // load glyph infos
    if (FT_Load_Glyph(_fontRef, glyph_index, FT_LOAD_DEFAULT))
        return false;
    
    // store result in the passed rectangle
    outRect.origin.x    = 0;
    outRect.origin.y    = - (_fontRef->glyph->metrics.horiBearingY >> 6);
    outRect.size.width  =   (_fontRef->glyph->metrics.width  >> 6);
    outRect.size.height =   (_fontRef->glyph->metrics.height >> 6);
    
    return true;
}

GlyphDef * FontFreeType::getGlyphDefintionsForText(const char *text, int &outNumGlyphs, bool UTF16text) const
{
    unsigned short* utf16String = 0;
    
    if (UTF16text)
    {
        utf16String = (unsigned short*) text;
    }
    else
    {
        utf16String = cc_utf8_to_utf16(text);
    }
    
    //
    if  (!utf16String)
        return 0;
    
    int numChar = cc_wcslen(utf16String);
    if (!numChar)
        return 0;

    // allocate the needed Glyphs
    GlyphDef *glyphs = new GlyphDef[numChar];
    assert(glyphs != nullptr);
    if (!glyphs)
        return 0;
    
    // sore result as CCRect
    for (int c = 0; c < numChar; ++c)
    {
        Rect tempRect;
        
        if (!getBBOXFotChar(utf16String[c], tempRect))
        {
            log("Warning: Cannot find definition for glyph: %c in font:%s", utf16String[c], _fontName.c_str());
            
            tempRect.origin.x       = 0;
            tempRect.origin.y       = 0;
            tempRect.size.width     = 0;
            tempRect.size.height    = 0;
            
            glyphs[c].setRect(tempRect);
            glyphs[c].setUTF16Letter(utf16String[c]);
            glyphs[c].setValid(false);
            glyphs[c].setPadding(_letterPadding);
        }
        else
        {
            glyphs[c].setRect(tempRect);
            glyphs[c].setUTF16Letter(utf16String[c]);
            glyphs[c].setPadding(_letterPadding);
            glyphs[c].setValid(true);
        }
    }
    
    outNumGlyphs = numChar;
    
    // free memory
    if (!UTF16text)
        delete [] utf16String;
    
    // done
    return glyphs;
}

Size * FontFreeType::getAdvancesForTextUTF16(unsigned short *text, int &outNumLetters) const
{
    if (!text)
        return 0;
    
    outNumLetters = cc_wcslen(text);

    if (!outNumLetters)
        return 0;
    
    Size *sizes = new Size[outNumLetters];
    if (!sizes)
        return 0;
    
    for (int c = 0; c < outNumLetters; ++c)
    {
        int advance = 0;
        int kerning = 0;
        
        advance = getAdvanceForChar(text[c]) - getBearingXForChar(text[c]);
        
        if (c < (outNumLetters-1))
            kerning = getHorizontalKerningForChars(text[c], text[c+1]);
        
        sizes[c].width = (advance + kerning);
    }
    
    return sizes;
}

int FontFreeType::getAdvanceForChar(unsigned short theChar) const
{
    if (!_fontRef)
        return 0;
    
    // get the ID to the char we need
    int glyph_index = FT_Get_Char_Index(_fontRef, theChar);
    
    if (!glyph_index)
        return 0;
    
    // load glyph infos
    if (FT_Load_Glyph(_fontRef, glyph_index, FT_LOAD_DEFAULT))
        return 0;
    
    // get to the advance for this glyph
    return (_fontRef->glyph->advance.x >> 6);
}

int FontFreeType::getBearingXForChar(unsigned short theChar) const
{
    
    if (!_fontRef)
        return 0;
    
    // get the ID to the char we need
    int glyphIndex = FT_Get_Char_Index(_fontRef, theChar);
    
    if (!glyphIndex)
        return 0;
    
    // load glyph infos
    if (FT_Load_Glyph(_fontRef, glyphIndex, FT_LOAD_DEFAULT))
        return 0;
    
    return (_fontRef->glyph->metrics.horiBearingX >>6);
}

int  FontFreeType::getHorizontalKerningForChars(unsigned short firstChar, unsigned short secondChar) const
{
    if (!_fontRef)
        return 0;

    bool hasKerning = FT_HAS_KERNING( _fontRef ) != 0;
    
    if (!hasKerning)
        return 0;
    
    // get the ID to the char we need
    int glyphIndex1 = FT_Get_Char_Index(_fontRef, firstChar);
    
    if (!glyphIndex1)
        return 0;
    
    // get the ID to the char we need
    int glyphIndex2 = FT_Get_Char_Index(_fontRef, secondChar);
    
    if (!glyphIndex2)
        return 0;
    
    FT_Vector kerning;
    
    if (FT_Get_Kerning( _fontRef, glyphIndex1, glyphIndex2,  FT_KERNING_DEFAULT,  &kerning))
        return 0;
    
    return (kerning.x >> 6);
}

int FontFreeType::getFontMaxHeight() const
{
    return (_fontRef->size->metrics.height >> 6);
}

unsigned char *   FontFreeType::getGlyphBitmap(unsigned short theChar, int &outWidth, int &outHeight) const
{
    if (!_fontRef)
        return 0;
    
    // get the ID to the char we need
    int glyphIndex = FT_Get_Char_Index(_fontRef, theChar);
    
    if (!glyphIndex)
        return 0;
    
    // load glyph infos
    if (FT_Load_Glyph(_fontRef, glyphIndex, FT_LOAD_DEFAULT))
        return 0;
    
    if (FT_Render_Glyph( _fontRef->glyph, FT_RENDER_MODE_NORMAL ))
        return 0;
    
    outWidth  = _fontRef->glyph->bitmap.width;
    outHeight = _fontRef->glyph->bitmap.rows;
    
    // return the pointer to the bitmap
    return _fontRef->glyph->bitmap.buffer;
}

int FontFreeType::getLetterPadding() const
{
    return _letterPadding;
}

NS_CC_END