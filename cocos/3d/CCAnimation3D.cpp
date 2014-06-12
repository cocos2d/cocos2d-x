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

#include "CCAnimation3D.h"
#include "CCBundle3D.h"

#include "base/ccMacros.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

Animation3D* Animation3D::getOrCreate(const std::string& fileName, const std::string& animationName)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    std::string key = fullPath + "#" + animationName;
    auto animation = Animation3DCache::getInstance()->getAnimation(key);
    if (animation != nullptr)
        return animation;
    
    //load animation here
    auto bundle = Bundle3D::getInstance();
    if (bundle->load(fullPath))
    {
        Animation3DData animationdata;
        animationdata.animation = new Animation3D();
        bundle->loadAnimationData(animationName, &animationdata);
        animation = animationdata.animation;
    }
    
    if (animation)
    {
        Animation3DCache::getInstance()->addAnimation(key, animation);
    }
    
    return animation;
}

Animation3D::Curve* Animation3D::getBoneCurveByName(const std::string& name) const
{
    auto it = _boneCurves.find(name);
    if (it != _boneCurves.end())
        return it->second;
    
    return nullptr;
}

Animation3D::Animation3D()
: _duration(0)
{
    
}
Animation3D::~Animation3D()
{
    for (auto itor : _boneCurves) {
        CC_SAFE_DELETE(itor.second);
    }
//    for (auto itor : _boneTransCurves) {
//        CC_SAFE_RELEASE(itor.second);
//    }
//    _boneTransCurves.clear();
//    
//    for (auto itor : _boneRotCurves) {
//        CC_SAFE_RELEASE(itor.second);
//    }
//    _boneRotCurves.clear();
//    
//    for (auto itor : _boneScaleCurves) {
//        CC_SAFE_RELEASE(itor.second);
//    }
//    _boneScaleCurves.clear();
}

Animation3D::Curve::Curve()
: translateCurve(nullptr)
, rotCurve(nullptr)
, scaleCurve(nullptr)
{
    
}
Animation3D::Curve::~Curve()
{
    CC_SAFE_RELEASE_NULL(translateCurve);
    CC_SAFE_RELEASE_NULL(rotCurve);
    CC_SAFE_RELEASE_NULL(scaleCurve);
}

////////////////////////////////////////////////////////////////
Animation3DCache* Animation3DCache::_cacheInstance = nullptr;

Animation3DCache* Animation3DCache::getInstance()
{
    if (_cacheInstance == nullptr)
        _cacheInstance = new Animation3DCache();
    
    return _cacheInstance;
}
void Animation3DCache::purgeMeshCache()
{
    CC_SAFE_DELETE(_cacheInstance);
}

Animation3D* Animation3DCache::getAnimation(const std::string& key)
{
    auto it = _animations.find(key);
    if (it != _animations.end())
        return it->second;
    return nullptr;
}

void Animation3DCache::addAnimation(const std::string& key, Animation3D* animation)
{
    const auto& it = _animations.find(key);
    if (it != _animations.end())
    {
        return; // already have this key
    }
    _animations[key] = animation;
    animation->retain();
}

void Animation3DCache::removeAllAnimation()
{
    for (auto itor : _animations) {
        CC_SAFE_RELEASE(itor.second);
    }
    _animations.clear();
}
void Animation3DCache::removeUnusedAnimation()
{
    for (auto itor = _animations.begin(); itor != _animations.end(); ) {
        if (itor->second->getReferenceCount() == 1)
        {
            itor->second->release();
            _animations.erase(itor++);
        }
        else
            ++itor;
    }
}

Animation3DCache::Animation3DCache()
{
    
}
Animation3DCache::~Animation3DCache()
{
    removeAllAnimation();
}

NS_CC_END
