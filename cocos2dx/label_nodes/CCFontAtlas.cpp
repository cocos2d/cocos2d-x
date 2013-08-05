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

std::map<int, FontLetterDefinition>             _atlasTextures;
std::map<unsigned short, FontLetterDefinition>  _fontLettersDefinition;


FontAtlas::FontAtlas(Font *theFont) : _font(theFont)
{
    if (_font)
        _font->retain();
}

FontAtlas::~FontAtlas()
{
    _font->release();
    relaseTextures();
}

void FontAtlas::relaseTextures()
{
    for( auto &item: _atlasTextures)
    {
        item.second.release();
    }
}

void FontAtlas::addLetterDefinition(FontLetterDefinition &letterDefinition)
{
    _fontLetterDefinitions[letterDefinition.letteCharUTF16] = letterDefinition;
}

FontLetterDefinition * FontAtlas::getLetterDefinitionForChar(unsigned short  letteCharUTF16)
{
    auto outIterator = _fontLetterDefinitions.find(letteCharUTF16);
    if (outIterator != _fontLetterDefinitions.end())
    {
        return & (*outIterator).second;
    }
    else
    {
        return 0;
    }
}

void FontAtlas::addTexture(Texture2D &texture, int slot)
{
    texture.retain();
    _atlasTextures[slot] = texture;
}

Texture2D & FontAtlas::getTexture(int slot)
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

Font * FontAtlas::getFont()
{
    return _font;
}


NS_CC_END