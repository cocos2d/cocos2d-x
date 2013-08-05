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

#include "cocos2d.h"
#include "CCTextImage.h"
#include "CCFontRenderFreeType.h"

#include <ft2build.h>
#include FT_FREETYPE_H

//#define _DEBUG_FONTS_
#ifdef _DEBUG_FONTS_
#include "CCImage.h"
#endif


NS_CC_BEGIN

bool FontRenderFreeType::renderCharAt(unsigned short int charToRender, int posX, int posY, unsigned char *destMemory, int destSize)
{
    if (!_font)
        return false;
    
    unsigned char *sourceBitmap = 0;
    int sourceWidth  = 0;
    int sourceHeight = 0;
    
    // get the glyph's bitmap
    sourceBitmap = _font->getGlyphBitmap(charToRender, sourceWidth, sourceHeight);
    
    if(!sourceBitmap)
        return false;
    
    int iX = posX;
    int iY = posY;
    
    for (int y = 0; y < sourceHeight; ++y)
    {
        int bitmap_y = y * sourceWidth;
        
        for (int x = 0; x < sourceWidth; ++x)
        {
            unsigned char cTemp = sourceBitmap[bitmap_y + x];
            
            // the final pixel
            int iTemp = cTemp << 24 | cTemp << 16 | cTemp << 8 | cTemp;
            *(int*) &destMemory[(iX + ( iY * destSize ) ) * 4] = iTemp;
            
            iX += 1;
        }
        
        iX  = posX;
        iY += 1;
    }
    
    //everything good
    return true;
}

unsigned char * FontRenderFreeType::preparePageGlyphData(TextPageDef *thePage)
{
    if (!thePage)
        return 0;
    
    if (!_font)
        return 0;
    
    if (thePage->getNumLines() == 0)
        return NULL;
    
    int pageWidth  = thePage->getWidth();
    int pageHeight = thePage->getHeight();
    
    // prepare memory and clean to 0
    int sizeInBytes     = (pageWidth * pageHeight * 4);
    unsigned char* data = new unsigned char[sizeInBytes];
    
    if (!data)
        return 0;
    
    memset(data, 0, sizeInBytes);
    
    int numLines = thePage->getNumLines();
    
    for (int c = 0; c<numLines; ++c)
    {
        TextLineDef *pCurrentLine   = thePage->getLineAt(c);
        
        float origX         = _font->getLetterPadding();
        float origY         = pCurrentLine->getY();
        
        int numGlyphToRender = pCurrentLine->getNumGlyph();
        
        for (int cglyph = 0; cglyph < numGlyphToRender; ++cglyph)
        {
            GlyphDef currGlyph      = pCurrentLine->getGlyphAt(cglyph);
            renderCharAt(currGlyph.getUTF8Letter(), origX, origY, data, pageWidth);
            origX += (currGlyph.getRect().size.width + _font->getLetterPadding());
        }
    }
    
#ifdef _DEBUG_FONTS_
    static int counter = 0;
    char outFilename[512];
    sprintf(outFilename,"carlottone%d", counter);
    ++counter;
    Image *pImage = new Image;
    pImage->initWithRawData(data, (pageWidth * pageWidth * 4), 1024, 1024, 8, false);
    pImage->saveToFile(outFilename);
#endif
    
    // we are done here
    return data;
}


NS_CC_END