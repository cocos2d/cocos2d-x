/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 Copyright (c) 2013-2015 Chukong Technologies Inc.
 
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

/// @cond DO_NOT_SHOW

#include "CCFont.h"

#include <string>
#include <ft2build.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#define generic GenericFromFreeTypeLibrary
#define internal InternalFromFreeTypeLibrary
#endif

#include FT_FREETYPE_H
#include FT_STROKER_H

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#undef generic
#undef internal
#endif

NS_CC_BEGIN

class CC_DLL FontFreeType : public Font
{
public:
    static const int DistanceMapSpread;

    static FontFreeType* create(const std::string &fontName, int fontSize, GlyphCollection glyphs, 
        const char *customGlyphs,bool distanceFieldEnabled = false,int outline = 0);

    static void shutdownFreeType();

    bool isDistanceFieldEnabled() const { return _distanceFieldEnabled;}

    float getOutlineSize() const { return _outlineSize; }

    void renderCharAt(unsigned char *dest,int posX, int posY, unsigned char* bitmap,long bitmapWidth,long bitmapHeight); 

    FT_Encoding getEncoding() const { return _encoding; }

    int* getHorizontalKerningForTextUTF16(const std::u16string& text, int &outNumLetters) const override;
    
    unsigned char* getGlyphBitmap(unsigned short theChar, long &outWidth, long &outHeight, Rect &outRect,int &xAdvance);
    
    int getFontAscender() const;

    virtual FontAtlas* createFontAtlas() override;
    virtual int getFontMaxHeight() const override { return _lineHeight; }
private:
    FontFreeType(bool distanceFieldEnabled = false, int outline = 0);
    virtual ~FontFreeType();

    bool createFontObject(const std::string &fontName, int fontSize);

    bool initFreeType();
    FT_Library getFTLibrary();
    
    int getHorizontalKerningForChars(unsigned short firstChar, unsigned short secondChar) const;
    unsigned char* getGlyphBitmapWithOutline(unsigned short code, FT_BBox &bbox);
    
    static FT_Library _FTlibrary;
    static bool       _FTInitialized;
    FT_Face           _fontRef;
    FT_Stroker        _stroker;
    std::string       _fontName;
    bool              _distanceFieldEnabled;
    float             _outlineSize;
    int _lineHeight;
    FontAtlas* _fontAtlas;

    FT_Encoding _encoding;
};

/// @endcond

NS_CC_END

#endif
