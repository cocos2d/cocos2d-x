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
#include "cocos2d.h"
#include "support/ccUTF8.h"
#include "CCFontFreeType.h"
#include "CCTextImage.h"

NS_CC_BEGIN


FT_Library FontFreeType::_FTlibrary;
bool       FontFreeType::_FTInitialized = false;



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
    unsigned char* data = NULL;
    int dpi             = 72;
    
    int len = 0;
    data    = FileUtils::getInstance()->getFileData(fontName.c_str(), "rb", (unsigned long *)(&len) );
    
    if (!data)
        return false;
    
    // create the new face
    FT_Face face;
    
    // create the face from the data
    if ( FT_New_Memory_Face(getFTLibrary(), data, len, 0, &face ) )
        return false;
    
    //we want to use unicode
    if( FT_Select_Charmap(face, FT_ENCODING_UNICODE) )
        return false;
    
    // set the requested font size
	int fontSizePoints = (int)(64.f * fontSize);
	if( FT_Set_Char_Size(face, fontSizePoints, fontSizePoints, dpi, dpi) )
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

bool FontFreeType::getBBOXFotChar(unsigned short theChar, Rect &outRect)
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

GlyphDef * FontFreeType::getGlyphDefintionsForText(const char *pText, int &outNumGlyphs, bool UTF16text)
{
    unsigned short* utf16String = 0;
    
    if (UTF16text)
    {
        utf16String = (unsigned short*) pText;
    }
    else
    {
        utf16String = cc_utf8_to_utf16(pText);
    }
    
    //
    if  (!utf16String)
        return 0;
    
    int numChar = cc_wcslen(utf16String);
    if (!numChar)
        return 0;

    // allocate the needed Glyphs
    GlyphDef *pGlyphs = new GlyphDef[numChar];
    assert( pGlyphs != NULL );
    if (!pGlyphs)
        return 0;
    
    // sore result as CCRect
    for (int c=0; c<numChar; ++c)
    {
        Rect tempRect;
        
        if( !getBBOXFotChar(utf16String[c], tempRect) )
        {
            log("Warning: Cannot find definition for glyph: %c in font:%s", utf16String[c], _fontName.c_str());
            
            tempRect.origin.x       = 0;
            tempRect.origin.y       = 0;
            tempRect.size.width     = 0;
            tempRect.size.height    = 0;
            
            pGlyphs[c].setRect(tempRect);
            pGlyphs[c].setUTF16Letter(utf16String[c]);
            pGlyphs[c].setValid(false);
            pGlyphs[c].setPadding(_letterPadding);
            
        }
        else
        {
            
            pGlyphs[c].setRect(tempRect);
            pGlyphs[c].setUTF16Letter(utf16String[c]);
            pGlyphs[c].setPadding(_letterPadding);
            pGlyphs[c].setValid(true);
            
        }
    }
    
    outNumGlyphs = numChar;
    
    // free memory
    if (!UTF16text)
        delete [] utf16String;
    
    // done
    return pGlyphs;
}

Size * FontFreeType::getAdvancesForTextUTF16(unsigned short *pText, int &outNumLetters)
{
    if (!pText)
        return 0;
    
    outNumLetters = cc_wcslen(pText);

    if (!outNumLetters)
        return 0;
    
    Size *pSizes = new Size[outNumLetters];
    if (!pSizes)
        return 0;
    
    for (int c = 0; c<outNumLetters; ++c)
    {
        int advance = 0;
        int kerning = 0;
        
        advance = getAdvanceForChar(pText[c]) - getBearingXForChar(pText[c]);
        
        if ( c < (outNumLetters-1) )
            kerning = getHorizontalKerningForChars(pText[c], pText[c+1]);
        
        pSizes[c].width = (advance + kerning);
    }
    
    return pSizes;
}

int FontFreeType::getAdvanceForChar(unsigned short theChar)
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

int FontFreeType::getBearingXForChar(unsigned short theChar)
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
    
    return (_fontRef->glyph->metrics.horiBearingX >>6);
}

int  FontFreeType::getHorizontalKerningForChars(unsigned short firstChar, unsigned short secondChar)
{
    if (!_fontRef)
        return 0;

    bool hasKerning = FT_HAS_KERNING( _fontRef );
    
    if (!hasKerning)
        return 0;
    
    // get the ID to the char we need
    int glyph_index1 = FT_Get_Char_Index(_fontRef, firstChar);
    
    if (!glyph_index1)
        return 0;
    
    // get the ID to the char we need
    int glyph_index2 = FT_Get_Char_Index(_fontRef, secondChar);
    
    if (!glyph_index2)
        return 0;
    
    FT_Vector kerning;
    
    if (FT_Get_Kerning( _fontRef, glyph_index1, glyph_index2,  FT_KERNING_DEFAULT,  &kerning ))
        return 0;
    
    return ( kerning.x >> 6 );
}

int FontFreeType::getFontMaxHeight()
{
    return (_fontRef->size->metrics.height >> 6);
}

unsigned char *   FontFreeType::getGlyphBitmap(unsigned short theChar, int &outWidth, int &outHeight)
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
    
    if (FT_Render_Glyph( _fontRef->glyph, FT_RENDER_MODE_NORMAL ))
        return 0;
    
    outWidth  = _fontRef->glyph->bitmap.width;
    outHeight = _fontRef->glyph->bitmap.rows;
    
    // return the pointer to the bitmap
    return _fontRef->glyph->bitmap.buffer;
}

int FontFreeType::getLetterPadding()
{
    return _letterPadding;
}

NS_CC_END