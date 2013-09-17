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
        item.second->release();
    }
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

void FontAtlas::addTexture(Texture2D &texture, int slot)
{
    texture.retain();
    _atlasTextures[slot] = &texture;
}

Texture2D & FontAtlas::getTexture(int slot)
{
    return *(_atlasTextures[slot]);
}

float FontAtlas::getCommonLineHeight() const
{
    return _commonLineHeight;
}

void  FontAtlas::setCommonLineHeight(float newHeight)
{
    _commonLineHeight = newHeight;
}

Font & FontAtlas::getFont() const
{
    return _font;
}

NS_CC_END