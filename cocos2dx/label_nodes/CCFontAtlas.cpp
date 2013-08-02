//
//  CCFontAtlas.cpp
//  cocos2d_libs
//
//  Created by Carlo Morgantini on 7/18/13.
//
//

#include "cocos2d.h"
#include "CCFontAtlas.h"
#include "CCFont.h"

NS_CC_BEGIN

FontAtlas::FontAtlas(Font &theFont) : _font(theFont)
{
    _font.retain();
}

FontAtlas::~FontAtlas()
{
    _font.release();
    relaseTextures();
}

void FontAtlas::relaseTextures()
{
    for( auto &item: _atlasTextures)
    {
        if ( item.second )
            item.second->release();
    }

    _atlasTextures.clear();
}

void FontAtlas::addLetterDefinition(const FontLetterDefinition &letterDefinition)
{
    _fontLetterDefinitions[letterDefinition.letteCharUTF16] = letterDefinition;
}

bool FontAtlas::getLetterDefinitionForChar(unsigned short  letteCharUTF16, FontLetterDefinition &outDefinition)
{
    auto outIterator = _fontLetterDefinitions.find(letteCharUTF16);
    
    if (outIterator != _fontLetterDefinitions.end())
    {
        outDefinition = (*outIterator).second;
        return true;
    }
    else
    {
        return false;
    }
}

void FontAtlas::addTexture(Texture2D *pTexture, int slot)
{
    pTexture->retain();
    _atlasTextures[slot] = pTexture;
}

Texture2D * FontAtlas::getTexture(int slot)
{
    return _atlasTextures[slot];
}

float FontAtlas::getCommonLineHeight()
{
    return _commonLineHeight;
}

void  FontAtlas::setCommonLineHeight(float newHeight)
{
    _commonLineHeight = newHeight;
}

unsigned short int * FontAtlas::getUTF16Text(const char *pText, int &outNumLetters)
{
    unsigned short* utf16String = cc_utf8_to_utf16(pText);
    
    if(!utf16String)
        return 0;
    
    outNumLetters = cc_wcslen(utf16String);
    return utf16String;
}

Font & FontAtlas::getFont()
{
    return _font;
}


NS_CC_END