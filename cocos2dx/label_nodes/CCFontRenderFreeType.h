//
//  CCFontRenderIOS.h
//  TestNewStringStuff
//
//  Created by Carlo Morgantini on 5/28/13.
//
//

#ifndef _FontRenderFreeType_h
#define _FontRenderFreeType_h

#include "CCFontRender.h"

NS_CC_BEGIN

class FontRenderFreeType : public FontRender
{
public:
    
    virtual ~FontRenderFreeType() {}
    virtual unsigned char * preparePageGlyphData(TextPageDef *thePage, char *fontName, int fontSize);
    static void testRendering();
    
    
};

NS_CC_END
 
#endif
