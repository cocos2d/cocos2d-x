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

class TextPageDef;

class FontRender
{
public:
    
    virtual ~FontRender() {}
    virtual unsigned char * preparePageGlyphData(TextPageDef *thePage, char *fontName, int fontSize) = 0;
};

NS_CC_END


#endif
