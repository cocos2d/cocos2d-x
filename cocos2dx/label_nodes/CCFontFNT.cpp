//
//  CCFontFNT.cpp
//  cocos2d_libs
//
//  Created by Carlo Morgantini on 7/24/13.
//
//

#include "CCFontFNT.h"


NS_CC_BEGIN


FontFNT::~FontFNT()
{
    if (_configuration)
        _configuration->release();
}

Size * FontFNT::getAdvancesForTextUTF16(unsigned short *pText, int &outNumLetters)
{
    if (!pText)
        return 0;
    
    outNumLetters = cc_wcslen(pText);
    
    if (!outNumLetters)
        return 0;
    
    Size *pSizes = new Size[outNumLetters];
    if (!pSizes)
        return 0;
    
    for (int c = 0; c<outNumLetters; ++c)
    {
        int advance = 0;
        int kerning = 0;
        
        advance = getAdvanceForChar(pText[c]);
        
        if ( c < (outNumLetters-1) )
            kerning = getHorizontalKerningForChars(pText[c], pText[c+1]);
        
        pSizes[c].width = (advance + kerning);
    }
    
    return pSizes;
}

int  FontFNT::getAdvanceForChar(unsigned short theChar)
{
    tFontDefHashElement *element = NULL;
    
    // unichar is a short, and an int is needed on HASH_FIND_INT
    unsigned int key = theChar;
    HASH_FIND_INT(_configuration->_fontDefDictionary, &key, element);
    if (! element)
        return -1;
    
    return element->fontDef.xAdvance;
}

int  FontFNT::getHorizontalKerningForChars(unsigned short firstChar, unsigned short secondChar)
{
    int ret = 0;
    unsigned int key = (firstChar<<16) | (secondChar & 0xffff);
    
    if( _configuration->_kerningDictionary )
    {
        tKerningHashElement *element = NULL;
        HASH_FIND_INT(_configuration->_kerningDictionary, &key, element);
        
        if(element)
            ret = element->amount;
    }
    
    return ret;
}

Rect FontFNT::getRectForCharInternal(unsigned short theChar)
{
    Rect retRect;
    ccBMFontDef fontDef;
    tFontDefHashElement *element = NULL;
    unsigned int key = theChar;
    
    HASH_FIND_INT(_configuration->_fontDefDictionary, &key, element);
    
    if (element)
    {
        retRect = element->fontDef.rect;
    }
    
    return retRect;
}

Rect FontFNT::getRectForChar(unsigned short theChar)
{
    return getRectForCharInternal(theChar);
}

NS_CC_END