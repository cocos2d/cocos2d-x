/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 Copyright (c) 2013-2015 Chukong Technologies Inc.
 
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
#include "2d/CCFontAtlasCache.h"

#include <iostream>
#include <sstream>
#include "base/CCDirector.h"
#include "2d/CCFontFNT.h"
#include "2d/CCFontFreeType.h"
#include "2d/CCFontAtlas.h"
#include "2d/CCFontCharMap.h"
#include "2d/CCLabel.h"

NS_CC_BEGIN

std::unordered_map<std::string, FontAtlas *> FontAtlasCache::_atlasMap;

void FontAtlasCache::purgeCachedData()
{
    auto atlasMapCopy = _atlasMap;
    for (auto&& atlas : atlasMapCopy)
    {
        atlas.second->purgeTexturesAtlas();
    }
}

FontAtlas* FontAtlasCache::getFontAtlasTTF(const _ttfConfig* config)
{  
    bool useDistanceField = config->distanceFieldEnabled;
    if(config->outlineSize > 0)
    {
        useDistanceField = false;
    }

    auto atlasName = generateFontName(config->fontFilePath, config->fontSize, useDistanceField);
    atlasName.append("_outline_");
    std::stringstream ss;
    ss << config->outlineSize;
    atlasName.append(ss.str());

    auto it = _atlasMap.find(atlasName);

    if ( it == _atlasMap.end() )
    {
        auto font = FontFreeType::create(config->fontFilePath, config->fontSize, config->glyphs,
            config->customGlyphs, useDistanceField, config->outlineSize);
        if (font)
        {
            auto tempAtlas = font->createFontAtlas();
            if (tempAtlas)
            {
                _atlasMap[atlasName] = tempAtlas;
                return _atlasMap[atlasName];
            }
        }
    }
    else
    {
        _atlasMap[atlasName]->retain();
        return _atlasMap[atlasName];
    }

    return nullptr;
}

FontAtlas* FontAtlasCache::getFontAtlasFNT(const std::string& fontFileName, const Vec2& imageOffset /* = Vec2::ZERO */)
{
    std::string atlasName = generateFontName(fontFileName, 0,false);
    auto it = _atlasMap.find(atlasName);

    if ( it == _atlasMap.end() )
    {
        auto font = FontFNT::create(fontFileName,imageOffset);

        if(font)
        {
            auto tempAtlas = font->createFontAtlas();
            if (tempAtlas)
            {
                _atlasMap[atlasName] = tempAtlas;
                return _atlasMap[atlasName];
            }
        }
    }
    else
    {
        _atlasMap[atlasName]->retain();
        return _atlasMap[atlasName];
    }
    
    return nullptr;
}

FontAtlas* FontAtlasCache::getFontAtlasCharMap(const std::string& plistFile)
{
    std::string atlasName = generateFontName(plistFile, 0,false);
    auto it = _atlasMap.find(atlasName);

    if ( it == _atlasMap.end() )
    {
        auto font = FontCharMap::create(plistFile);

        if(font)
        {
            auto tempAtlas = font->createFontAtlas();
            if (tempAtlas)
            {
                _atlasMap[atlasName] = tempAtlas;
                return _atlasMap[atlasName];
            }
        }
    }
    else
    {
        _atlasMap[atlasName]->retain();
        return _atlasMap[atlasName];
    }

    return nullptr;
}

FontAtlas* FontAtlasCache::getFontAtlasCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap)
{
    char tmp[30];
    sprintf(tmp,"name:%u_%d_%d_%d",texture->getName(),itemWidth,itemHeight,startCharMap);
    std::string atlasName = generateFontName(tmp, 0,false);

    auto it = _atlasMap.find(atlasName);
    if ( it == _atlasMap.end() )
    {
        auto font = FontCharMap::create(texture,itemWidth,itemHeight,startCharMap);

        if(font)
        {
            auto tempAtlas = font->createFontAtlas();
            if (tempAtlas)
            {
                _atlasMap[atlasName] = tempAtlas;
                return _atlasMap[atlasName];
            }
        }
    }
    else
    {
        _atlasMap[atlasName]->retain();
        return _atlasMap[atlasName];
    }

    return nullptr;
}

FontAtlas* FontAtlasCache::getFontAtlasCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
    char tmp[255];
    snprintf(tmp,250,"name:%s_%d_%d_%d",charMapFile.c_str(),itemWidth,itemHeight,startCharMap);

    std::string atlasName = generateFontName(tmp, 0,false);

    auto it = _atlasMap.find(atlasName);
    if ( it == _atlasMap.end() )
    {
        auto font = FontCharMap::create(charMapFile,itemWidth,itemHeight,startCharMap);

        if(font)
        {
            auto tempAtlas = font->createFontAtlas();
            if (tempAtlas)
            {
                _atlasMap[atlasName] = tempAtlas;
                return _atlasMap[atlasName];
            }
        }
    }
    else
    {
        _atlasMap[atlasName]->retain();
        return _atlasMap[atlasName];
    }

    return nullptr;
}

std::string FontAtlasCache::generateFontName(const std::string& fontFileName, int size, bool useDistanceField)
{
    std::string tempName(fontFileName);
    
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
                if (atlas->getReferenceCount() == 1)
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
