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
    // std::to_string is not supported on android, using std::stringstream instead.
    std::stringstream ss;
    ss << size;
    return tempName + ss.str();
}

bool CCFontCache::releaseFontDefinition(FontDefinitionTTF *def)
{
    if (def)
    {
        for( auto &item: _fontsMap)
        {
            if ( item.second == def )
            {
                item.second->release();
                _fontsMap.erase(item.first);
                return true;
            }
        }
    }
    
    return false;
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