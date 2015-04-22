/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
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

#include "PolySpriteCache.h"
#include "3d/CCMesh.h"
#include "3d/CCMeshVertexIndexData.h"

#include "base/CCDirector.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgramCache.h"
#include <vector>

#include "poly2tri/poly2tri.h"
#include "platform/CCFileUtils.h"
using namespace std;

USING_NS_CC;

PolySpriteCache* PolySpriteCache::_polySpriteCache = nullptr;

PolySpriteCache::PolySpriteCache()
{
    
}

PolySpriteCache::~PolySpriteCache()
{
}

PolySpriteCache* PolySpriteCache::getInstance()
{
    if (NULL == _polySpriteCache)
    {
        _polySpriteCache = new (std::nothrow) PolySpriteCache();
        _polySpriteCache->init();
    }
    return _polySpriteCache;
}

void PolySpriteCache::destroyInstance()
{
    CC_SAFE_DELETE(_polySpriteCache);
}

void PolySpriteCache::init()
{
    
}

void PolySpriteCache::addPolySpriteCache(const std::string& filePath, const PolySpriteInfo& polySpriteInfo)
{
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(filePath);
    if (fullpath.size() == 0)
        return;
    
    auto it = _polySpriteCacheMap.find(fullpath);
    if (_polySpriteCacheMap.end() != it)
    {
        VecPolySpriteInfo vecInfo = it->second;
        
        auto infoIt = vecInfo.begin();
        for (; infoIt != vecInfo.end(); infoIt++)
        {
            if ((*infoIt)->_rect.equals(polySpriteInfo._rect))
            {
                (*infoIt)->_triangles = polySpriteInfo._triangles;
                (*infoIt)->_textureRect = polySpriteInfo._textureRect;
                return;
            }
        }
    }
    
    VecPolySpriteInfo vecInfo;
    vecInfo.clear();
    PolySpriteInfo* info = new (std::nothrow)PolySpriteInfo;
    if (nullptr != info)
    {
        info->_rect = polySpriteInfo._rect;
        info->_triangles = polySpriteInfo._triangles;
        info->_textureRect = polySpriteInfo._textureRect;
        
        vecInfo.push_back(info);
        _polySpriteCacheMap[filePath] = vecInfo;
    }
}

PolySpriteInfo* PolySpriteCache::getPolySpriteCache(const std::string& filePath, const cocos2d::Rect& rect)
{
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(filePath);
    if (fullpath.size() == 0)
        return nullptr;
    
    auto it = _polySpriteCacheMap.find(fullpath);
    if (_polySpriteCacheMap.end() == it)
        return nullptr;
    
    auto infoIter = it->second.begin();
    for (; infoIter != it->second.end(); infoIter++)
    {
        if ((*infoIter)->_rect.equals(rect))
            return *infoIter;
    }
    
    return nullptr;
}

void   PolySpriteCache::removePolySpriteCache(const std::string& filePath, const cocos2d::Rect* rect)
{
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(filePath);
    if (fullpath.size() == 0)
        return;
    
    auto it = _polySpriteCacheMap.find(fullpath);
    if (_polySpriteCacheMap.end() == it)
        return;
    
    if (nullptr == rect)
    {
        
    }
    
    auto infoIter = it->second.begin();
    for (; infoIter != it->second.end(); infoIter++)
    {
        
    }
    
    return;
}

void   PolySpriteCache::removeAllPolySpriteCache()
{
    
}

bool PolySpriteCache::isPolySpriteCachExist(const std::string& filePath, const cocos2d::Rect& rect)
{
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(filePath);
    if (fullpath.size() == 0)
        return false;
    
    auto it = _polySpriteCacheMap.find(fullpath);
    if (_polySpriteCacheMap.end() == it)
        return false;
    
    auto infoIter = it->second.begin();
    for (; infoIter != it->second.end(); infoIter++)
    {
        if ((*infoIter)->_rect.equals(rect))
            return true;
    }
    
    return false;
}

USING_NS_CC;
