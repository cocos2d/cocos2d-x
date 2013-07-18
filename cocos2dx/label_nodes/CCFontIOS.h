//
//  CCFontIOS.h
//  TestNewStringStuff
//
//  Created by Carlo Morgantini on 5/20/13.
//
//

#ifndef _FontIOS_h
#define _FontIOS_h

#include <CoreText/CTFont.h>

#include "CCFont.h"

NS_CC_BEGIN

class FontIOS : public Font
{
public:
    
    virtual ~FontIOS();
    virtual bool                    createFontObject(const std::string &fontName, int fontSize);
    
    virtual GlyphDef            *   getGlyphsForText(const char *pText, int &outNumGlyphs,    bool UTF16text = false);
    virtual Size                *   getAdvancesForText(const char *pText, int &outNumLetters, bool UTF16text = false);
    virtual Size                    getTextWidthAndHeight(const char *pText, bool UTF16text = false);
    virtual Size                *   getAdvancesForTextUTF16(unsigned short *pText, int &outNumLetters);
    virtual unsigned short int  *   getUTF16Text(const char *pText, int &outNumLetters);
    
    virtual int                   getLetterPadding()                                                                { return 0; }
    virtual unsigned char       * getGlyphBitmap(unsigned short theChar, int &outWidth, int &outHeight)             { return 0; }
    virtual unsigned short int  * trimUTF16Text(unsigned short int *pText, int newBegin, int newEnd)                { return 0; }
    virtual int                   getUTF16TextLenght(unsigned short int *pText)                                     { return 0; }
    
    
private:
    
    CTFontRef   _fontRef;
    void *      _fontUI;
    
};

NS_CC_END

#endif
