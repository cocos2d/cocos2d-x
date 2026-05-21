/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "base/CCDirector.h"
#include "2d/CCFontFNT.h"
#include "2d/CCFontFreeType.h"
#include "2d/CCFontAtlas.h"
#include "2d/CCFontCharMap.h"
#include "2d/CCLabel.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

std::unordered_map<std::string, FontAtlas *> FontAtlasCache::_atlasMap;
#define ATLAS_MAP_KEY_PREFIX_BUFFER_SIZE 255

void FontAtlasCache::purgeCachedData()
{
    auto atlasMapCopy = _atlasMap;
    for (auto&& atlas : atlasMapCopy)
    {
        auto refCount = atlas.second->getReferenceCount();
        atlas.second->release();
        if (refCount != 1)
            atlas.second->purgeTexturesAtlas();
    }
    _atlasMap.clear();
}

FontAtlas* FontAtlasCache::getFontAtlasTTF(const _ttfConfig* config)
{
    auto realFontFilename = FileUtils::getInstance()->getNewFilename(config->fontFilePath);  // resolves real file path, to prevent storing multiple atlases for the same file.
    bool useDistanceField = config->distanceFieldEnabled;
    if(config->outlineSize > 0)
    {
        useDistanceField = false;
    }

    std::string key;
    char keyPrefix[ATLAS_MAP_KEY_PREFIX_BUFFER_SIZE];
    snprintf(keyPrefix, ATLAS_MAP_KEY_PREFIX_BUFFER_SIZE, useDistanceField ? "df %.2f %d " : "%.2f %d ", config->fontSize, config->outlineSize);
    std::string atlasName(keyPrefix);
    atlasName += realFontFilename;

    auto it = _atlasMap.find(atlasName);

    if ( it == _atlasMap.end() )
    {
        auto font = FontFreeType::create(realFontFilename, config->fontSize, config->glyphs,
            config->customGlyphs, useDistanceField, (float)config->outlineSize);
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
        return it->second;

    return nullptr;
}

FontAtlas* FontAtlasCache::getFontAtlasFNT(const std::string& fontFileName)
{
    return getFontAtlasFNT(fontFileName, Rect::ZERO, false);
}

FontAtlas* FontAtlasCache::getFontAtlasFNT(const std::string& fontFileName, const std::string& subTextureKey)
{
    const auto realFontFilename = FileUtils::getInstance()->getNewFilename(fontFileName);  // resolves real file path, to prevent storing multiple atlases for the same file.
    std::string atlasName = subTextureKey + " " + realFontFilename;

    const auto it = _atlasMap.find(atlasName);
    if (it == _atlasMap.end())
    {
        const auto font = FontFNT::create(realFontFilename, subTextureKey);

        if (font)
        {
            const auto tempAtlas = font->createFontAtlas();
            if (tempAtlas)
            {
                _atlasMap[atlasName] = tempAtlas;
                return _atlasMap[atlasName];
            }
        }
    }
    else
        return it->second;

    return nullptr;
}

FontAtlas* FontAtlasCache::getFontAtlasFNT(const std::string& fontFileName, const Rect& imageRect, bool imageRotated)
{
    const auto realFontFilename = FileUtils::getInstance()->getNewFilename(fontFileName);  // resolves real file path, to prevent storing multiple atlases for the same file.
    char keyPrefix[ATLAS_MAP_KEY_PREFIX_BUFFER_SIZE];
    snprintf(keyPrefix, ATLAS_MAP_KEY_PREFIX_BUFFER_SIZE, "%.2f %.2f ", imageRect.origin.x, imageRect.origin.y);
    std::string atlasName(keyPrefix);
    atlasName += realFontFilename;
    
    const auto it = _atlasMap.find(atlasName);
    if ( it == _atlasMap.end() )
    {
        const auto font = FontFNT::create(realFontFilename, imageRect, imageRotated);

        if(font)
        {
            const auto tempAtlas = font->createFontAtlas();
            if (tempAtlas)
            {
                _atlasMap[atlasName] = tempAtlas;
                return _atlasMap[atlasName];
            }
        }
    }
    else
        return it->second;
    
    return nullptr;
}

FontAtlas* FontAtlasCache::getFontAtlasFNT(const std::string& fontFileName, const Vec2& imageOffset)
{
    return getFontAtlasFNT(fontFileName, Rect(imageOffset.x, imageOffset.y, 0, 0), false);
}

FontAtlas* FontAtlasCache::getFontAtlasCharMap(const std::string& plistFile)
{
    const std::string& atlasName = plistFile;
    
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
        return it->second;

    return nullptr;
}

FontAtlas* FontAtlasCache::getFontAtlasCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap)
{
    char key[ATLAS_MAP_KEY_PREFIX_BUFFER_SIZE];
    sprintf(key,"name:%p_%d_%d_%d",texture->getBackendTexture(),itemWidth,itemHeight,startCharMap);
    std::string atlasName = key;

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
        return it->second;

    return nullptr;
}

FontAtlas* FontAtlasCache::getFontAtlasCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
    char keyPrefix[ATLAS_MAP_KEY_PREFIX_BUFFER_SIZE];
    snprintf(keyPrefix, ATLAS_MAP_KEY_PREFIX_BUFFER_SIZE, "%d %d %d ", itemWidth, itemHeight, startCharMap);
    std::string atlasName(keyPrefix);
    atlasName += charMapFile;

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
        return it->second;

    return nullptr;
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

void FontAtlasCache::reloadFontAtlasFNT(const std::string& fontFileName, const Rect& imageRect, bool imageRotated)
{
    char keyPrefix[ATLAS_MAP_KEY_PREFIX_BUFFER_SIZE];
    snprintf(keyPrefix, ATLAS_MAP_KEY_PREFIX_BUFFER_SIZE, "%.2f %.2f ", imageRect.origin.x, imageRect.origin.y);
    std::string atlasName(keyPrefix);
    atlasName += fontFileName;
    
    auto it = _atlasMap.find(atlasName);
    if (it != _atlasMap.end())
    {
        CC_SAFE_RELEASE_NULL(it->second);
        _atlasMap.erase(it);
    }
    FontFNT::reloadBMFontResource(fontFileName);
    auto font = FontFNT::create(fontFileName, imageRect, imageRotated);
    if (font)
    {
        auto tempAtlas = font->createFontAtlas();
        if (tempAtlas)
        {
            _atlasMap[atlasName] = tempAtlas;
        }
    }
}

void FontAtlasCache::reloadFontAtlasFNT(const std::string& fontFileName, const Vec2& imageOffset)
{
    reloadFontAtlasFNT(fontFileName, Rect(imageOffset.x, imageOffset.y, 0, 0), false);
}

void FontAtlasCache::unloadFontAtlasTTF(const std::string& fontFileName)
{
    auto item = _atlasMap.begin();
    while (item != _atlasMap.end())
    {
        if (item->first.find(fontFileName) != std::string::npos)
        {
            CC_SAFE_RELEASE_NULL(item->second);
            item = _atlasMap.erase(item);
        }
        else
            item++;
    }
}

NS_CC_END
