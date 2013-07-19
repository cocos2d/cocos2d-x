//
//  CCFontAtlas.cpp
//  cocos2d_libs
//
//  Created by Carlo Morgantini on 7/18/13.
//
//

#include "cocos2d.h"
#include "CCFontAtlas.h"

NS_CC_BEGIN

std::map<int, FontLetterDefinition>             _atlasTextures;
std::map<unsigned short, FontLetterDefinition>  _fontLettersDefinition;


void FontAtlas::addLetterDefinition(FontLetterDefinition &letterDefinition)
{
    _fontLetterDefinitions[letterDefinition.letteCharUTF16] = letterDefinition;
}

FontLetterDefinition & FontAtlas::getLetterDefinitionForChar(unsigned short  letteCharUTF16)
{
    return _fontLetterDefinitions[letteCharUTF16];
}

void FontAtlas::addTexture(Texture2D *pTexture, int slot)
{
    _atlasTextures[slot] = pTexture;
}

Texture2D * FontAtlas::getTexture(int slot)
{
    return _atlasTextures[slot];
}

NS_CC_END