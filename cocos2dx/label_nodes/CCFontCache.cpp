//
//  CCFontCache.cpp
//  cocos2d_libs
//
//  Created by Carlo Morgantini on 7/22/13.
//
//

#include "CCFontCache.h"

NS_CC_BEGIN


const char *glpyhsASCII = "\"!#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþ";

const char *glpyhsNEHE =  "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";


std::map<std::string, FontDefinitionTTF *> CCFontCache::_fontsMap;

FontDefinitionTTF * CCFontCache::getFontDefinition(const char *fontFileName, int size, GlyphCollection glyphs)
{
    std::string fontName = generateFontName(fontFileName, size);
    FontDefinitionTTF *tempDefinition = _fontsMap[fontName];
    
    if ( !tempDefinition )
    {
        tempDefinition = FontDefinitionTTF::create(fontFileName, size, getGlyphCollection(glyphs));
        if (tempDefinition)
        {
            tempDefinition->retain();
            _fontsMap[fontName] = tempDefinition;
        }
        else
        {
            return 0;
        }
    }
    
    return tempDefinition;
}
    
std::string CCFontCache::generateFontName(const char *fontFileName, int size)
{
    std::string tempName(fontFileName);
    return tempName + std::to_string(size);
}

void CCFontCache::purgeUnusedFonts()
{
    std::map<std::string, FontDefinitionTTF *>::iterator ITER;
    for ( ITER = _fontsMap.begin(); ITER != _fontsMap.end(); ++ITER )
    {
        if ( (*ITER).second->isSingleReference() )
        {
            // remove from memory
            (*ITER).second->release();
            
            // remove from map
            _fontsMap.erase((*ITER).first);
        }
    }
}

const char * CCFontCache::getGlyphCollection(GlyphCollection glyphs)
{
    switch (glyphs)
    {
        case GlyphCollection::NEHE:
            return glpyhsNEHE;
            break;
            
        case GlyphCollection::ASCII:
            return glpyhsASCII;
            break;
            
        default:
            return 0;
            break;
    }
}

NS_CC_END