//
//  CCTextRender.h
//  TestNewStringStuff
//
//  Created by Carlo Morgantini on 5/28/13.
//
//

#ifndef _FontRender_h
#define _FontRender_h


NS_CC_BEGIN

// FWD
class Font;

class TextPageDef;

class FontRender
{
    
public:
    
             FontRender(Font *pFont) { _font = pFont; }
    virtual ~FontRender() {}
    virtual unsigned char * preparePageGlyphData(TextPageDef *thePage, char *fontName, int fontSize) = 0;
    
protected:
    
    Font * _font;
};

NS_CC_END


#endif
