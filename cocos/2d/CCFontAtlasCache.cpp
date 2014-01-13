/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#include "CCFontAtlasCache.h"
#include "CCFontAtlasFactory.h"


NS_CC_BEGIN

std::unordered_map<std::string, FontAtlas *> FontAtlasCache::_atlasMap;

FontAtlas * FontAtlasCache::getFontAtlasTTF(const std::string& fontFileName, int size, GlyphCollection glyphs, const char *customGlyphs, bool useDistanceField)
{
    std::string atlasName = generateFontName(fontFileName, size, glyphs, useDistanceField);
    FontAtlas  *tempAtlas = _atlasMap[atlasName];
    
    if ( !tempAtlas )
    {
        tempAtlas = FontAtlasFactory::createAtlasFromTTF(fontFileName, size, glyphs, customGlyphs, useDistanceField);
        if (tempAtlas)
            _atlasMap[atlasName] = tempAtlas;
    }
    else
    {
        tempAtlas->retain();
    }
    
    return tempAtlas;
}

FontAtlas * FontAtlasCache::getFontAtlasFNT(const std::string& fontFileName)
{
    std::string atlasName = generateFontName(fontFileName, 0, GlyphCollection::CUSTOM,false);
    FontAtlas *tempAtlas = _atlasMap[atlasName];
    
    if ( !tempAtlas )
    {
        tempAtlas = FontAtlasFactory::createAtlasFromFNT(fontFileName);
        if (tempAtlas)
            _atlasMap[atlasName] = tempAtlas;
    }
    else
    {
        tempAtlas->retain();
    }
    
    return tempAtlas;
}

std::string FontAtlasCache::generateFontName(const std::string& fontFileName, int size, GlyphCollection theGlyphs, bool useDistanceField)
{
    std::string tempName(fontFileName);
    
    switch (theGlyphs)
    {
        case GlyphCollection::DYNAMIC:
            tempName.append("_DYNAMIC_");
        break;
            
        case GlyphCollection::NEHE:
            tempName.append("_NEHE_");
            break;
            
        case GlyphCollection::ASCII:
            tempName.append("_ASCII_");
            break;
            
        case GlyphCollection::CUSTOM:
            tempName.append("_CUSTOM_");
            break;
            
        default:
            break;
    }
    if(useDistanceField)
        tempName.append("df");
    // std::to_string is not supported on android, using std::stringstream instead.
    std::stringstream ss;
    ss << size;
    return  tempName.append(ss.str());
}

bool FontAtlasCache::releaseFontAtlas(FontAtlas *atlas)
{
    if (nullptr != atlas)
    {
        for( auto &item: _atlasMap )
        {
            if ( item.second == atlas )
            {
                if( atlas->isSingleReference() )
                {
                  _atlasMap.erase(item.first);
                }
                
                atlas->release();
                
                return true;
            }
        }
    }
    
    return false;
}

NS_CC_END
