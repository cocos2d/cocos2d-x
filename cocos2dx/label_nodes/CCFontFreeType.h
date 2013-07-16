//
//  CCFontIOS.h
//  TestNewStringStuff
//
//  Created by Carlo Morgantini on 5/20/13.
//
//

#ifndef _FontFreetype_h
#define _FontFreetype_h

#include "CCFont.h"


#include "ft2build.h"
#include "CCStdC.h"
#include FT_FREETYPE_H

NS_CC_BEGIN

class FontFreeType : public Font
{
public:
    
    FontFreeType();
    virtual ~FontFreeType();
    virtual bool                    createFontObject(const std::string &fontName, int fontSize);
    
    virtual int                     getUTF8TextLenght(const char *pText);
    virtual Size                    getTextWidthAndHeight(const char *pText);
    virtual GlyphDef            *   getGlyphsForText(const char *pText, int &outNumGlyphs);
    virtual Size                *   getAdvancesForText(const char *pText, int &outNumLetters);
    virtual Size                *   getAdvancesForTextUTF8(unsigned short *pText, int &outNumLetters);
    virtual unsigned short int  *   getUTF8Text(const char *pText, int &outNumLetters);
    virtual const char          *   trimUTF8Text(const char *pText, int newBegin, int newEnd);
    virtual int                     getLetterPadding() { return _letterPadding;}
    unsigned char               *   getGlyphBitmap(unsigned short theChar, int &outWidth, int &outHeight);
    
private:
    
    bool initFreeType();
    void shutdownFreeType();
    FT_Library getFTLibrary();
    bool getBBOXFotChar(unsigned short theChar, Rect &outRect);
    int  getAdvanceFotChar(unsigned short theChar);
    int  getHorizontalKerningForChars(unsigned short firstChar, unsigned short secondChar);
    
    static FT_Library _FTlibrary;
    static bool       _FTInitialized;
    FT_Face           _fontRef;
    const int         _letterPadding;
    
    
    
};

NS_CC_END

#endif
