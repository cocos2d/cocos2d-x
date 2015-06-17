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

#ifndef COCOS_2D_SpritePolygonCACHE_H__
#define COCOS_2D_SpritePolygonCACHE_H__

#include <vector>
#include "platform/CCPlatformMacros.h"
#include "2d/CCNode.h"
#include "renderer/CCTrianglesCommand.h"
#include "CCDrawNode.h"

NS_CC_BEGIN

typedef struct CC_DLL _SpritePolygonInfo
{
    cocos2d::Rect _rect;
    cocos2d::TrianglesCommand::Triangles _triangles;
    ~_SpritePolygonInfo()
    {
        if(nullptr != _triangles.verts)
        {
            CC_SAFE_DELETE_ARRAY(_triangles.verts);
        }
        
        if(nullptr != _triangles.indices)
        {
            CC_SAFE_DELETE_ARRAY(_triangles.indices);
        }
    }
} SpritePolygonInfo;

typedef std::vector<SpritePolygonInfo*> VecSpritePolygonInfo;
typedef std::unordered_map<std::string, VecSpritePolygonInfo> MapSpritePolygonInfo;

class CC_DLL SpritePolygonCache: public cocos2d::Ref
{
public:
    virtual ~SpritePolygonCache();
    static SpritePolygonCache* getInstance();
    static void destroyInstance();
    SpritePolygonInfo*   addSpritePolygonCache(const std::string& filePath, const cocos2d::Rect& rect, const cocos2d::TrianglesCommand::Triangles trianglesCommand);
    SpritePolygonInfo* getSpritePolygonCache(const std::string& filePath, const cocos2d::Rect& rect);
    void   removeSpritePolygonCache(const std::string& filePath, const cocos2d::Rect* rect = nullptr);
    void   removeAllSpritePolygonCache();
    bool   isSpritePolygonCachExist(const std::string& filePath, const cocos2d::Rect& rect);
    
    static void printInfo(SpritePolygonInfo &info);
protected:
    SpritePolygonCache();
private:
    void init();
private:
    static SpritePolygonCache* _SpritePolygonCache;
    MapSpritePolygonInfo _SpritePolygonCacheMap;
    
};

NS_CC_END

#endif // #ifndef COCOS_2D_SpritePolygonCACHE_H__
