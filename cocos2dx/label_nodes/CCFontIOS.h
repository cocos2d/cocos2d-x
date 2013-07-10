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

#include "cocos2d.h"
#include "CCFont.h"


NS_CC_BEGIN

class FontIOS : public Font
{
public:
    
    virtual ~FontIOS();
    virtual bool                    createFontObject(const std::string &fontName, int fontSize);
    virtual int                     getUTF8TextLenght(const char *pText);
    virtual Size                    getTextWidthAndHeight(const char *pText);
    virtual GlyphDef            *   getGlyphsForText(const char *pText, int &outNumGlyphs);
    virtual Size                *   getAdvancesForText(const char *pText, int &outNumLetters);
    virtual Size                *   getAdvancesForTextUTF8(unsigned short *pText, int &outNumLetters);
    virtual unsigned short int  *   getUTF8Text(const char *pText, int &outNumLetters);
    virtual const char          *   trimUTF8Text(const char *pText, int newBegin, int newEnd);
    
private:
    
    CTFontRef   _fontRef;
    void *      _fontUI;
    
};

NS_CC_END

#endif
