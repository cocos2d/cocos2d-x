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

#include "SpritePolygonCache.h"
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

SpritePolygonCache* SpritePolygonCache::_SpritePolygonCache = nullptr;

SpritePolygonCache::SpritePolygonCache()
{
    
}

SpritePolygonCache::~SpritePolygonCache()
{
}

SpritePolygonCache* SpritePolygonCache::getInstance()
{
    if (NULL == _SpritePolygonCache)
    {
        _SpritePolygonCache = new (std::nothrow) SpritePolygonCache();
        _SpritePolygonCache->init();
    }
    return _SpritePolygonCache;
}

void SpritePolygonCache::destroyInstance()
{
    CC_SAFE_DELETE(_SpritePolygonCache);
}

void SpritePolygonCache::init()
{
    
}

SpritePolygonInfo* SpritePolygonCache::addSpritePolygonCache(const std::string& filePath, const SpritePolygonInfo& spritePolygonInfo)
{
    auto fullpath = filePath;
    
    auto it = _SpritePolygonCacheMap.find(fullpath);
    if (_SpritePolygonCacheMap.end() != it)
    {
        VecSpritePolygonInfo vecInfo = it->second;
        
        auto infoIt = vecInfo.begin();
        for (; infoIt != vecInfo.end(); infoIt++)
        {
            if ((*infoIt)->_rect.equals(spritePolygonInfo._rect))
            {
                (*infoIt)->_triangles = spritePolygonInfo._triangles;
//                (*infoIt)->_textureRect = SpritePolygonInfo._textureRect;
                return nullptr;
            }
        }
    }
    
    VecSpritePolygonInfo vecInfo;
    vecInfo.clear();
    SpritePolygonInfo* info = new SpritePolygonInfo;
    if (nullptr != info)
    {
        info->_rect = spritePolygonInfo._rect;
        
        info->_triangles.verts = new V3F_C4B_T2F[spritePolygonInfo._triangles.vertCount];
        info->_triangles.indices = new unsigned short[spritePolygonInfo._triangles.indexCount];
        info->_triangles.vertCount = spritePolygonInfo._triangles.vertCount;
        info->_triangles.indexCount = spritePolygonInfo._triangles.indexCount;
        
        memcpy(info->_triangles.verts, spritePolygonInfo._triangles.verts, spritePolygonInfo._triangles.vertCount*sizeof(V3F_C4B_T2F));
        memcpy(info->_triangles.indices, spritePolygonInfo._triangles.indices, spritePolygonInfo._triangles.indexCount*sizeof(unsigned short));
//        info->_textureRect = SpritePolygonInfo._textureRect;
        
        vecInfo.push_back(info);
        _SpritePolygonCacheMap[filePath] = vecInfo;
    }
    return info;
}

SpritePolygonInfo* SpritePolygonCache::getSpritePolygonCache(const std::string& filePath, const cocos2d::Rect& rect)
{
    auto fullpath = filePath;
    
    auto it = _SpritePolygonCacheMap.find(fullpath);
    if (_SpritePolygonCacheMap.end() == it)
        return nullptr;
    
    auto infoIter = it->second.begin();
    for (; infoIter != it->second.end(); infoIter++)
    {
        if ((*infoIter)->_rect.equals(rect))
            return *infoIter;
    }
    
    return nullptr;
}

void   SpritePolygonCache::removeSpritePolygonCache(const std::string& filePath, const cocos2d::Rect* rect)
{
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(filePath);
    if (fullpath.size() == 0)
        return;
    
    auto it = _SpritePolygonCacheMap.find(fullpath);
    if (_SpritePolygonCacheMap.end() == it)
        return;
    
    if (nullptr == rect)
        return;
    
    auto infoIter = it->second.begin();
    bool exist = false;
    for (; infoIter != it->second.end(); infoIter++)
    {
        if((*infoIter)->_rect.equals(*rect))
        {
            exist = true;
            break;
        }
    }
    
    if (exist)
    {
        CC_SAFE_DELETE(*infoIter);
        it->second.erase(infoIter);
    }
    
    return;
}

void SpritePolygonCache::removeAllSpritePolygonCache()
{
    for (std::unordered_map<std::string, VecSpritePolygonInfo>::iterator it = _SpritePolygonCacheMap.begin(); it != _SpritePolygonCacheMap.end(); ++it)
    {
        auto infoIter = it->second.begin();
        for (; infoIter != it->second.end(); infoIter++)
        {
            CC_SAFE_DELETE(*infoIter);
        }
        it->second.clear();
    }
    _SpritePolygonCacheMap.clear();
}

bool SpritePolygonCache::isSpritePolygonCachExist(const std::string& filePath, const cocos2d::Rect& rect)
{
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(filePath);
    if (fullpath.size() == 0)
        return false;
    
    auto it = _SpritePolygonCacheMap.find(fullpath);
    if (_SpritePolygonCacheMap.end() == it)
        return false;
    
    auto infoIter = it->second.begin();
    for (; infoIter != it->second.end(); infoIter++)
    {
        if ((*infoIter)->_rect.equals(rect))
            return true;
    }
    
    return false;
}


void SpritePolygonCache::printInfo(SpritePolygonInfo &info){
    CCLOG("========================");
    CCLOG("%zd, %zd", info._triangles.vertCount, info._triangles.indexCount);

    auto vertEnd = &info._triangles.verts[info._triangles.vertCount];
    for(auto v = info._triangles.verts; v < vertEnd; v++)
    {
        CCLOG("%f, %f", v->vertices.x, v->vertices.y);
    }
    auto indEnd = &info._triangles.indices[info._triangles.indexCount];
    for(auto i = info._triangles.indices; i < indEnd; i+=3)
    {
        CCLOG("%d, %d, %d", *i,*(i+1), *(i+2));
    }
}

USING_NS_CC;
