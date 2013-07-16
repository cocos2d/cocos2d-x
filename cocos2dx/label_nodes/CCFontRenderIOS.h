//
//  CCFontRenderIOS.h
//  TestNewStringStuff
//
//  Created by Carlo Morgantini on 5/28/13.
//
//

#ifndef _FontRenderIOS_h
#define _FontRenderIOS_h

#include "CCFontRender.h"

NS_CC_BEGIN

class Font;

class FontRenderIOS : public FontRender
{
    
public:
    
    FontRenderIOS(Font *pFont): FontRender(pFont) {}
    virtual ~FontRenderIOS() {}
    virtual unsigned char * preparePageGlyphData(TextPageDef *thePage, char *fontName, int fontSize);
    
};

NS_CC_END
 
#endif
