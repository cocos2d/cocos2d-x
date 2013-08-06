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

#ifndef _FontFreetype_h_
#define _FontFreetype_h_

#include "CCFont.h"
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

NS_CC_BEGIN

class CC_DLL FontFreeType : public Font
{
public:
    
    FontFreeType();
    virtual ~FontFreeType();
    
    virtual Size                *   getAdvancesForTextUTF16(unsigned short *pText, int &outNumLetters);
    
    virtual bool                    createFontObject(const std::string &fontName, int fontSize);
    virtual GlyphDef            *   getGlyphDefintionsForText(const char *pText, int &outNumGlyphs,    bool UTF16text = false);
    unsigned char               *   getGlyphBitmap(unsigned short theChar, int &outWidth, int &outHeight);
    virtual int                     getFontMaxHeight();
    virtual int                     getLetterPadding();
    
private:
    
    bool initFreeType();
    void shutdownFreeType();
    FT_Library getFTLibrary();
    
    bool getBBOXFotChar(unsigned short theChar, Rect &outRect);
    int  getAdvanceForChar(unsigned short theChar);
    int  getBearingXForChar(unsigned short theChar);
    int  getHorizontalKerningForChars(unsigned short firstChar, unsigned short secondChar);
    
    static FT_Library _FTlibrary;
    static bool       _FTInitialized;
    
    FT_Face           _fontRef;
    const int         _letterPadding;
    
    std::string       _fontName;
    
};

NS_CC_END

#endif
