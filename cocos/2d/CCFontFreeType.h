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

#include <string>
#include <ft2build.h>

#include "CCFont.h"

#include FT_FREETYPE_H

NS_CC_BEGIN

class CC_DLL FontFreeType : public Font
{
public:
    
    static FontFreeType * create(const std::string &fontName, int fontSize, GlyphCollection glyphs, const char *customGlyphs);
    
    virtual FontAtlas   * createFontAtlas() override;
    virtual Size        * getAdvancesForTextUTF16(unsigned short *text, int &outNumLetters) const override;
    virtual GlyphDef    * getGlyphDefintionsForText(const char *text, int &outNumGlyphs,    bool UTF16text = false) const override;
    unsigned char       * getGlyphBitmap(unsigned short theChar, int &outWidth, int &outHeight) const override;
    virtual int           getFontMaxHeight() const override;
    virtual int           getLetterPadding() const override;
    
    
protected:
    
    FontFreeType();
    virtual ~FontFreeType();
    bool   createFontObject(const std::string &fontName, int fontSize);
    
private:

    bool initFreeType();
    void shutdownFreeType();
    FT_Library getFTLibrary();
    
    bool getBBOXFotChar(unsigned short theChar, Rect &outRect) const;
    int  getAdvanceForChar(unsigned short theChar) const;
    int  getBearingXForChar(unsigned short theChar) const;
    int  getHorizontalKerningForChars(unsigned short firstChar, unsigned short secondChar) const;
    
    static FT_Library _FTlibrary;
    static bool       _FTInitialized;
    FT_Face           _fontRef;
    const int         _letterPadding;
    std::string       _fontName;
    
};

NS_CC_END

#endif
