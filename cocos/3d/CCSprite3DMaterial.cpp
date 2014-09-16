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

#include "3d/CCSprite3DMaterial.h"

#include "renderer/CCTexture2D.h"

NS_CC_BEGIN

Sprite3DMaterialCache* Sprite3DMaterialCache::_cacheInstance = nullptr;

Sprite3DMaterialCache::Sprite3DMaterialCache()
{
    
}

Sprite3DMaterialCache::~Sprite3DMaterialCache()
{
    removeAllSprite3DMaterial();
}

Sprite3DMaterialCache* Sprite3DMaterialCache::getInstance()
{
    if (! _cacheInstance)
    {
        _cacheInstance = new (std::nothrow) Sprite3DMaterialCache();
    }
    
    return _cacheInstance;
}

void Sprite3DMaterialCache::destroyInstance()
{
    if (_cacheInstance)
    {
        CC_SAFE_DELETE(_cacheInstance);
    }
}

bool Sprite3DMaterialCache::addSprite3DMaterial(const std::string& key, Texture2D* texture)
{
    auto itr = _materials.find(key);
    if (itr == _materials.end())
    {
        CC_SAFE_RETAIN(texture);
        _materials[key] = texture;
        return true;
    }
    return false;
}

Texture2D* Sprite3DMaterialCache::getSprite3DMaterial(const std::string& key)
{
    auto itr = _materials.find(key);
    if (itr != _materials.end())
    {
        return itr->second;
    }
    return nullptr;
}

void Sprite3DMaterialCache::removeAllSprite3DMaterial()
{
    for (auto itr = _materials.begin(); itr != _materials.end(); itr++) {
        CC_SAFE_RELEASE_NULL(itr->second);
    }
    _materials.clear();
}
void Sprite3DMaterialCache::removeUnusedSprite3DMaterial()
{
    for( auto it=_materials.cbegin(); it!=_materials.cend(); /* nothing */) {
        auto value = it->second;
        if( value->getReferenceCount() == 1 ) {
            CCLOG("cocos2d: GLProgramStateCache: removing unused GLProgramState");
            
            value->release();
            _materials.erase(it++);
        } else {
            ++it;
        }
    }
}

NS_CC_END
