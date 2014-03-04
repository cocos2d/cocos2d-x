/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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
#include "CCData.h"

#include <string>
#include <ft2build.h>

#include FT_FREETYPE_H

NS_CC_BEGIN

class CC_DLL FontFreeType : public Font
{
public:
    static const int DistanceMapSpread;

    static FontFreeType * create(const std::string &fontName, int fontSize, GlyphCollection glyphs, const char *customGlyphs);

    static void shutdownFreeType();

    void     setDistanceFieldEnabled(bool distanceFieldEnabled);
    bool     isDistanceFieldEnabled() const { return _distanceFieldEnabled;}
    bool     renderCharAt(unsigned short int charToRender, int posX, int posY, unsigned char *destMemory, int destSize); 

    virtual FontAtlas   * createFontAtlas() override;
    virtual int         * getHorizontalKerningForTextUTF16(unsigned short *text, int &outNumLetters) const override;
    
    unsigned char       * getGlyphBitmap(unsigned short theChar, int &outWidth, int &outHeight) const override;
    virtual int           getFontMaxHeight() const override;
    
    bool getBBOXFotChar(unsigned short theChar, Rect &outRect,int &xAdvance) const; 

protected:
    
    FontFreeType();
    virtual ~FontFreeType();
    bool   createFontObject(const std::string &fontName, int fontSize);
    
private:

    bool initFreeType();
    FT_Library getFTLibrary();
    
    int  getHorizontalKerningForChars(unsigned short firstChar, unsigned short secondChar) const;
    
    static FT_Library _FTlibrary;
    static bool       _FTInitialized;
    FT_Face           _fontRef;
    std::string       _fontName;
    Data              _ttfData;
    bool              _distanceFieldEnabled;
};

NS_CC_END

#endif
