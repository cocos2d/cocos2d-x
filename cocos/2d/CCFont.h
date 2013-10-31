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

#ifndef _CCFont_h_
#define _CCFont_h_

#include <string>

#include "cocos2d.h"
#include "CCLabel.h"

NS_CC_BEGIN

// fwd
class GlyphDef;
class FontAtlas;


class CC_DLL Font : public Object
{
public:

    // create the font
    static   Font* createWithTTF(const char* fntName, int fontSize, GlyphCollection glyphs, const char *customGlyphs);
    static   Font* createWithFNT(const char* fntFilePath);
    
    virtual  FontAtlas *createFontAtlas() = 0;

    virtual Size                * getAdvancesForTextUTF16(unsigned short *text, int &outNumLetters) const                        = 0;
    virtual const char          * getCurrentGlyphCollection() const;
    
    virtual int                   getLetterPadding()  const                                                                       { return 0;     }
    virtual unsigned char       * getGlyphBitmap(unsigned short theChar, int &outWidth, int &outHeight) const                     { return 0;     }
    virtual GlyphDef            * getGlyphDefintionsForText(const char *text, int &outNumGlyphs, bool    UTF16text = false) const { return 0;     }
    virtual int                   getFontMaxHeight()  const                                                                       { return 0;     }
    virtual Rect                  getRectForChar(unsigned short theChar) const;
    
    virtual int                   getUTF16TextLenght(unsigned short int *text) const; 
    virtual unsigned short int  * getUTF16Text(const char *text, int &outNumLetters) const;
    virtual unsigned short int  * trimUTF16Text(unsigned short int *text, int newBegin, int newEnd) const;
    
protected:
    
    Font();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Font() {}
    void setCurrentGlyphCollection(GlyphCollection glyphs, const char *customGlyphs = 0);
    const char * getGlyphCollection(GlyphCollection glyphs) const;
    
private:
    
    GlyphCollection     _usedGlyphs;
    char              * _customGlyphs;
    static const char * _glyphASCII;
    static const char * _glyphNEHE;
    
};

NS_CC_END


#endif
