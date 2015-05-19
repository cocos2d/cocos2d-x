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
#include "poly2tri/poly2tri.h"
#include "MarchingSquare.h"
#include "platform/CCFileUtils.h"
#include "base/CCDirector.h"
#include "renderer/CCTextureCache.h"

USING_NS_CC;

SpritePolygonCache* SpritePolygonCache::s_spritePolygonCache = nullptr;

SpritePolygonCache::SpritePolygonCache()
{
    
}

SpritePolygonCache::~SpritePolygonCache()
{
    removeAllSpritePolygonCache();
}

SpritePolygonCache* SpritePolygonCache::getInstance()
{
    if (nullptr == s_spritePolygonCache)
    {
        s_spritePolygonCache = new (std::nothrow) SpritePolygonCache();
        s_spritePolygonCache->init();
    }
    return s_spritePolygonCache;
}

void SpritePolygonCache::destroyInstance()
{
    CC_SAFE_DELETE(s_spritePolygonCache);
}

void SpritePolygonCache::init()
{
    _spritePolygonCacheMap.reserve(20);
}

SpritePolygonInfo* SpritePolygonCache::addSpritePolygonCache(const std::string& filePath, const cocos2d::Rect& rect, const cocos2d::TrianglesCommand::Triangles& trianglesCommand)
{
    auto fullpath = FileUtils::getInstance()->fullPathForFilename(filePath);;
    
    auto it = _spritePolygonCacheMap.find(fullpath);
    if (_spritePolygonCacheMap.end() != it)
    {
        VecSpritePolygonInfo vecInfo = it->second;
        
        auto infoIt = vecInfo.begin();
        for (; infoIt != vecInfo.end(); infoIt++)
        {
            if ((*infoIt)->_rect.equals(rect))
            {
                CC_SAFE_DELETE_ARRAY((*infoIt)->_triangles.verts);
                CC_SAFE_DELETE_ARRAY((*infoIt)->_triangles.indices);
                (*infoIt)->_triangles.verts = new V3F_C4B_T2F[trianglesCommand.vertCount];
                (*infoIt)->_triangles.indices = new unsigned short[trianglesCommand.indexCount];
                (*infoIt)->_triangles.vertCount = trianglesCommand.vertCount;
                (*infoIt)->_triangles.indexCount = trianglesCommand.indexCount;
                memcpy((*infoIt)->_triangles.verts, trianglesCommand.verts, trianglesCommand.vertCount*sizeof(V3F_C4B_T2F));
                memcpy((*infoIt)->_triangles.indices, trianglesCommand.indices, trianglesCommand.indexCount*sizeof(unsigned short));
                return *infoIt;
            }
        }
    }
    
    VecSpritePolygonInfo vecInfo;
    vecInfo.clear();
    if (it != _spritePolygonCacheMap.end())
    {
        vecInfo = it->second;
    }
    SpritePolygonInfo* info = new SpritePolygonInfo;
    if (nullptr != info)
    {
        info->_rect = rect;
        info->_triangles.verts = new V3F_C4B_T2F[trianglesCommand.vertCount];
        info->_triangles.indices = new unsigned short[trianglesCommand.indexCount];
        info->_triangles.vertCount = trianglesCommand.vertCount;
        info->_triangles.indexCount = trianglesCommand.indexCount;
        memcpy(info->_triangles.verts, trianglesCommand.verts, trianglesCommand.vertCount*sizeof(V3F_C4B_T2F));
        memcpy(info->_triangles.indices, trianglesCommand.indices, trianglesCommand.indexCount*sizeof(unsigned short));
        
        vecInfo.push_back(info);
        _spritePolygonCacheMap[filePath] = vecInfo;
    }
    return info;
}

SpritePolygonInfo* SpritePolygonCache::getSpritePolygonCache(const std::string& filePath, const cocos2d::Rect& rect, float optimization)
{
    SpritePolygonInfo* spritePolygonInfo = nullptr;
    bool isFound = false;
    
    auto fullpath = FileUtils::getInstance()->fullPathForFilename(filePath);
    if(fullpath.size() == 0)
    {
        return nullptr;
    }
    
    auto it = _spritePolygonCacheMap.find(fullpath);
    if (_spritePolygonCacheMap.end() != it)
    {
        auto infoIter = it->second.begin();
        for (; infoIter != it->second.end(); infoIter++)
        {
            if ((*infoIter)->_rect.equals(rect))
            {
                spritePolygonInfo = *infoIter;
                isFound = true;
            }
        }
    }
    
    if(!isFound)//TODO:: for temp.
    {
        //TODO:: can be removed.
        Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(fullpath);
        CCASSERT(texture, "texture was not loaded properly");
        
        //Marching Square
        if(-1 == optimization) optimization = 1.169;
        MarchingSquare marcher(fullpath);
        marcher.trace(rect);
        marcher.optimize(optimization);
        marcher.expand(rect, optimization);
        
        marcher.printPoints();
        auto p = marcher.getPoints();
        SpritePolygonInfo* spi = triangulate(fullpath, rect, p);
        
        calculateUV(spi, texture);//TODO:return spritepolygon and pass to calculateUV();
        spritePolygonInfo = spi;

    }
    return spritePolygonInfo;
}

void SpritePolygonCache::removeSpritePolygonCache(const std::string& filePath, const cocos2d::Rect* rect)
{
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(filePath);
    if (fullpath.size() == 0)
        return;
    
    auto it = _spritePolygonCacheMap.find(fullpath);
    if (_spritePolygonCacheMap.end() == it)
        return;
    
    if (nullptr == rect)
        return;
    
    auto infoIter = it->second.begin();
    for (; infoIter != it->second.end(); infoIter++)
    {
        if((*infoIter)->_rect.equals(*rect))
        {
            CC_SAFE_DELETE(*infoIter);
            it->second.erase(infoIter);
            break;
        }
    }
    
    return;
}

void SpritePolygonCache::removeAllSpritePolygonCache()
{
    for (std::unordered_map<std::string, VecSpritePolygonInfo>::iterator it = _spritePolygonCacheMap.begin(); it != _spritePolygonCacheMap.end(); ++it)
    {
        for (auto infoIter = it->second.begin(); infoIter != it->second.end(); infoIter++)
        {
            CC_SAFE_DELETE(*infoIter);
        }
        it->second.clear();
    }
    _spritePolygonCacheMap.clear();
}

bool SpritePolygonCache::isSpritePolygonCacheExist(const std::string& filePath, const cocos2d::Rect& rect)
{
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(filePath);
    if (fullpath.size() == 0)
        return false;
    
    auto it = _spritePolygonCacheMap.find(fullpath);
    if (_spritePolygonCacheMap.end() == it)
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
        CCLOG("%d, %d, %d,", *i,*(i+1), *(i+2));
    }
    
    auto uvEnd = &info._triangles.verts[info._triangles.vertCount];
    for(auto v = info._triangles.verts; v < uvEnd; v++)
    {
        CCLOG("%f, %f", v->texCoords.u, v->texCoords.v);
    }
}

SpritePolygonInfo* SpritePolygonCache::triangulate(const std::string& file, const cocos2d::Rect& rect, std::vector<cocos2d::Vec2> & verts)
{
    std::vector<p2t::Point*> points;
    for(std::vector<Vec2>::const_iterator it = verts.begin(); it<verts.end(); it++)
    {
        p2t::Point * p = new p2t::Point(it->x, it->y);
        points.push_back(p);
    }
    p2t::CDT cdt(points);
    cdt.Triangulate();
    std::vector<p2t::Triangle*> tris = cdt.GetTriangles();
    
    std::vector<V3F_C4B_T2F> _verts;
    std::vector<unsigned short> _indices;
    unsigned short idx = 0;
    for(std::vector<p2t::Triangle*>::const_iterator ite = tris.begin(); ite < tris.end(); ite++)
    {
        for(int i = 0; i < 3; i++)
        {
            auto p = (*ite)->GetPoint(i);
            auto v3 = Vec3(p->x, p->y, 0);
            bool found = false;
            int j;
            for(j = 0; j < _verts.size(); j++)
            {
                if(_verts[j].vertices == v3)
                {
                    found = true;
                    break;
                }
            }
            if(found)
            {
                //if we found the same vertice, don't add to verts, but use the same vert with indices
                _indices.push_back(j);
            }
            else
            {
                //vert does not exist yet, so we need to create a new one,
                auto c4b = Color4B::WHITE;
                auto t2f = Tex2F(0,0); // don't worry about tex coords now, we calculate that later
                V3F_C4B_T2F vert = {v3,c4b,t2f};
                _verts.push_back(vert);
                _indices.push_back(idx);
                idx++;
            }
        }
    }
    for(auto j : points)
    {
        delete j;
    }
    
    TrianglesCommand::Triangles triangles = {&_verts[0], &_indices[0], (ssize_t)_verts.size(), (ssize_t)_indices.size()};
    return SpritePolygonCache::getInstance()->addSpritePolygonCache(file, rect, triangles);
}

void SpritePolygonCache::calculateUV(SpritePolygonInfo* spritePolygonInfo, const cocos2d::Texture2D* texture2D)
{
    /*
     whole texture UV coordination
     0,0                  1,0
     +---------------------+
     |                     |0.1
     |                     |0.2
     |     +--------+      |0.3
     |     |texRect |      |0.4
     |     |        |      |0.5
     |     |        |      |0.6
     |     +--------+      |0.7
     |                     |0.8
     |                     |0.9
     +---------------------+
     0,1                  1,1
     
     because when we scanned the image upside down, our uv is now upside down too
     */
    
    float scaleFactor = Director::getInstance()->getContentScaleFactor();
    float texWidth  = texture2D->getPixelsWide()/scaleFactor;
    float texHeight = texture2D->getPixelsHigh()/scaleFactor;
    
    if(nullptr != spritePolygonInfo)
    {
        auto end = &spritePolygonInfo->_triangles.verts[spritePolygonInfo->_triangles.vertCount];
        for(auto i = spritePolygonInfo->_triangles.verts; i != end; i++)
        {
            // for every point, offset with the centerpoint
            float u = i->vertices.x / texWidth;
            float v = (texHeight - i->vertices.y) / texHeight;
            i->texCoords.u = u;
            i->texCoords.v = v;
        }
    }
}

USING_NS_CC;
