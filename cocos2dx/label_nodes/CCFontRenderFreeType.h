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

// this should be here #include "ft2build.h"
// this should bg here #include FT_FREETYPE_H


NS_CC_BEGIN

class FontRenderFreeType : public FontRender
{
public:
    
    FontRenderFreeType(Font *pFont): FontRender(pFont) {}
    virtual ~FontRenderFreeType() {}
    virtual unsigned char * preparePageGlyphData(TextPageDef *thePage, char *fontName, int fontSize);
    
    
    // only a test, needs to go
    static void testRendering();
    
    
private:
    
    bool renderCharAt(unsigned short int charToRender, int posX, int posY, unsigned char *destMemory, int destSize);
    
    static bool InitFreeType();
    static bool CreateFreeTypeFont(const char *fontName, int fontSize, int dpi);
    static void ReleaseFreeType();
    
};

NS_CC_END
 
#endif
