/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#ifndef __CCSPRIT3DDATA_CACHE_H__
#define __CCSPRIT3DDATA_CACHE_H__

#include <string>
#include <unordered_map>
#include "base/ccTypes.h"
#include "base/CCMap.h"

NS_CC_BEGIN

class Sprite3D;
class Mesh;
class EventListenerCustom;
class EventCustom;
class Texture2D;

class Sprite3DDataCache
{
public:
    struct Sprite3DData
    {
        Mesh* mesh;
        std::string texture;
    };
    
    static Sprite3DDataCache* getInstance();
    static void purgeMeshCache();
    
    bool addSprite3D(const std::string& fileName, Mesh* mesh, const std::string& texture);
    
    Mesh* getSprite3DMesh(const std::string& fileName);
    
    Texture2D* getSprite3DTexture(const std::string& fileName);
    
    void removeAllSprite3DData();
    void removeUnusedSprite3DData();

    
 #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
     void listenBackToForeground(EventCustom* event);
 #endif
    
protected:
    Sprite3DDataCache();
    
    ~Sprite3DDataCache();
    
    static Sprite3DDataCache* _cacheInstance;

    std::unordered_map<std::string, Sprite3DData> _sprite3DDatas; //sprites 
    
 #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
     EventListenerCustom* _backToForegroundlistener;
 #endif
};

NS_CC_END

#endif // __CCSPRIT3DDATA_CACHE_H__
