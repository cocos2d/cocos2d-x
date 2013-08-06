//
//  CCFontFNT.cpp
//  cocos2d_libs
//
//  Created by Carlo Morgantini on 7/24/13.
//
//

#include "CCFontFNT.h"


NS_CC_BEGIN


FontFNT * FontFNT::create(const char* fntFilePath)
{
    CCBMFontConfiguration *newConf = FNTConfigLoadFile(fntFilePath);
    if (!newConf)
        return nullptr;
    
    // add the texture
    Texture2D *tempTexture = TextureCache::getInstance()->addImage(newConf->getAtlasName());
    if ( !tempTexture )
    {
        delete newConf;
        return nullptr;
    }
    
    FontFNT *tempFont =  new FontFNT(newConf);
    
    if (!tempFont)
    {
        delete newConf;
        return nullptr;
    }
    
    return tempFont;
}

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

FontAtlas * FontFNT::createFontAtlas()
{
    FontAtlas *tempAtlas = new FontAtlas(*this);
    if (!tempAtlas)
        return nullptr;
    
    // check that everything is fine with the BMFontCofniguration
    if (!_configuration->_fontDefDictionary)
        return nullptr;
    
    int numGlyphs = _configuration->_characterSet->size();
    if (!numGlyphs)
        return nullptr;
    
    if (_configuration->_commonHeight == 0)
        return nullptr;
    
    // commone height
    tempAtlas->setCommonLineHeight(_configuration->_commonHeight);
    
    
    ccBMFontDef fontDef;
    tFontDefHashElement *current_element, *tmp;
    
    // Purge uniform hash
    HASH_ITER(hh, _configuration->_fontDefDictionary, current_element, tmp)
    {
        
        FontLetterDefinition tempDefinition;
        
        fontDef = current_element->fontDef;
        Rect tempRect;
        
        tempRect = fontDef.rect;
        tempRect = CC_RECT_PIXELS_TO_POINTS(tempRect);
        
        tempDefinition.letteCharUTF16 = fontDef.charID;
        
        tempDefinition.offsetX  = fontDef.xOffset;
        tempDefinition.offsetY  = fontDef.yOffset;
        
        tempDefinition.U        = tempRect.origin.x;
        tempDefinition.V        = tempRect.origin.y;
        
        tempDefinition.width    = tempRect.size.width;
        tempDefinition.height   = tempRect.size.height;
        
        //carloX: only one texture supported FOR NOW
        tempDefinition.textureID = 0;
        
        tempDefinition.anchorX = 0.5f;
        tempDefinition.anchorY = 0.5f;
        
        // add the new definition
        tempAtlas->addLetterDefinition(tempDefinition);
    }
    
    // add the texture (only one texture for now)
    
    Texture2D *tempTexture = TextureCache::getInstance()->addImage(_configuration->getAtlasName());
    if (!tempTexture)
        return 0;
    
    // add the texture
    tempAtlas->addTexture(*tempTexture, 0);
    
    // done
    return tempAtlas;
}


NS_CC_END