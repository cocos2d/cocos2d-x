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

#include <sstream>

NS_CC_BEGIN

std::unordered_map<std::string, FontAtlas *> FontAtlasCache::_atlasMap;
#define ATLAS_MAP_KEY_BUFFER 255

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

    char tmp[ATLAS_MAP_KEY_BUFFER];
    if (useDistanceField) {
        snprintf(tmp, ATLAS_MAP_KEY_BUFFER, "df %.2f %d %s", config->fontSize, config->outlineSize,
                 realFontFilename.c_str());
    } else {
        snprintf(tmp, ATLAS_MAP_KEY_BUFFER, "%.2f %d %s", config->fontSize, config->outlineSize,
                 realFontFilename.c_str());
    }
    std::string atlasName = tmp;

    auto it = _atlasMap.find(atlasName);

    if ( it == _atlasMap.end() )
    {
        auto font = FontFreeType::create(realFontFilename, config->fontSize, config->glyphs,
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
        return it->second;

    return nullptr;
}

FontAtlas* FontAtlasCache::getFontAtlasFNT(const std::string& fontFileName, const Vec2& imageOffset /* = Vec2::ZERO */)
{
    auto realFontFilename = FileUtils::getInstance()->getNewFilename(fontFileName);  // resolves real file path, to prevent storing multiple atlases for the same file.
    char tmp[ATLAS_MAP_KEY_BUFFER];
    snprintf(tmp, ATLAS_MAP_KEY_BUFFER, "%.2f %.2f %s", imageOffset.x, imageOffset.y, realFontFilename.c_str());
    std::string atlasName = tmp;
    
    auto it = _atlasMap.find(atlasName);
    if ( it == _atlasMap.end() )
    {
        auto font = FontFNT::create(realFontFilename, imageOffset);

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

FontAtlas* FontAtlasCache::getFontAtlasCharMap(const std::string& plistFile)
{
    std::string atlasName = plistFile;
    
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
    char tmp[30];
    sprintf(tmp,"name:%u_%d_%d_%d",texture->getName(),itemWidth,itemHeight,startCharMap);
    std::string atlasName = tmp;

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
    char tmp[ATLAS_MAP_KEY_BUFFER];
    snprintf(tmp, ATLAS_MAP_KEY_BUFFER, "%d %d %d %s", itemWidth, itemHeight, startCharMap, charMapFile.c_str());
    std::string atlasName = tmp;

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

void FontAtlasCache::reloadFontAtlasFNT(const std::string& fontFileName, const Vec2& imageOffset/* = Vec2::ZERO*/)
{
    char tmp[ATLAS_MAP_KEY_BUFFER];
    snprintf(tmp, ATLAS_MAP_KEY_BUFFER, "%.2f %.2f %s", imageOffset.x, imageOffset.y, fontFileName.c_str());
    std::string atlasName = tmp;
    
    auto it = _atlasMap.find(atlasName);
    if (it != _atlasMap.end())
    {
        CC_SAFE_RELEASE_NULL(it->second);
        _atlasMap.erase(it);
    }
    FontFNT::reloadBMFontResource(fontFileName);
    auto font = FontFNT::create(fontFileName, imageOffset);
    if (font)
    {
        auto tempAtlas = font->createFontAtlas();
        if (tempAtlas)
        {
            _atlasMap[atlasName] = tempAtlas;
        }
    }

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

std::string FontAtlasCache::getCachedTextureInfo() {
    std::stringstream ss;
    char buf[4096];
    unsigned totalBytes = 0;
    
    for(auto& atlasInfo : _atlasMap) {
        const FontAtlas* atlas = atlasInfo.second;
        if(!atlas) {
            snprintf(buf, sizeof(buf) - 1, "\"%s\" <null>\n", atlasInfo.first.c_str());
        } else {
            auto& textures = atlas->getTextures();
            Size totalSize;
            unsigned bppTotal = 0;
            unsigned atlasBytes = 0;
            for(auto& tm : textures) {
                Texture2D* texture = tm.second;
                auto& textureSize = texture->getContentSizeInPixels();
                auto bpp = texture->getBitsPerPixelForFormat();
                
                totalSize   = totalSize + textureSize;
                bppTotal    += bpp;
                atlasBytes  += textureSize.width * textureSize.height * bpp / 8;
            }
            
            auto count = textures.size();
            snprintf(buf, sizeof(buf) - 1, "\"%s\" rc=%u count=%lu %d x %d @ %ld bpp => %lu KB\n",
                     atlasInfo.first.c_str(),
                     atlas->getReferenceCount(),
                     count,
                     static_cast<int>(totalSize.width/count),
                     static_cast<int>(totalSize.height/count),
                     bppTotal/count,
                     atlasBytes/count / 1024);
            
            totalBytes += atlasBytes;
        }
        
        ss << buf;
    }
    
    // output the tottal size
    snprintf(buf, sizeof(buf) - 1, "FontAtlasCache dumpDebugInfo: %lu textures, for %.1fKB (%.2f MB)\n",
             _atlasMap.size(),
             totalBytes / 1024.0f,
             totalBytes / (1024.0f*1024.0f));
    ss << buf;
    
    return ss.str();
}

NS_CC_END
