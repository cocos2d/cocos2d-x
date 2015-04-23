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

#ifndef COCOS_2D_POLYSPRITECACHE_H__
#define COCOS_2D_POLYSPRITECACHE_H__

#include <vector>
#include "platform/CCPlatformMacros.h"
#include "2d/CCNode.h"
#include "renderer/CCTrianglesCommand.h"
#include "CCDrawNode.h"
#include "PolySprite.h"

NS_CC_BEGIN

struct CC_DLL PolySpriteInfo
{
    cocos2d::Rect _rect;
    cocos2d::TrianglesCommand::Triangles _triangles;
    cocos2d::Rect _textureRect;
};

typedef std::vector<PolySpriteInfo*> VecPolySpriteInfo;
typedef std::unordered_map<std::string, VecPolySpriteInfo> MapPolySpriteInfo;

class CC_DLL PolySpriteCache: public cocos2d::Ref
{
public:
    virtual ~PolySpriteCache();
    static PolySpriteCache* getInstance();
    static void destroyInstance();
    void   addPolySpriteCache(const std::string& filePath, const PolySpriteInfo& polySpriteInfo);
    PolySpriteInfo* getPolySpriteCache(const std::string& filePath, const cocos2d::Rect& rect);
    void   removePolySpriteCache(const std::string& filePath, const cocos2d::Rect* rect = nullptr);
    void   removeAllPolySpriteCache();
    bool   isPolySpriteCachExist(const std::string& filePath, const cocos2d::Rect& rect);
protected:
    PolySpriteCache();
private:
    void init();
private:
    static PolySpriteCache* _polySpriteCache;
    MapPolySpriteInfo _polySpriteCacheMap;
    
};

NS_CC_END

#endif // #ifndef COCOS_2D_POLYSPRITECACHE_H__
