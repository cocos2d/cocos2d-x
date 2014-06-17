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

#ifndef __CCANIMATION3D_H__
#define __CCANIMATION3D_H__

#include <unordered_map>

#include "3d/CCAnimationCurve.h"

#include "base/ccMacros.h"
#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "CCBundle3DData.h"

NS_CC_BEGIN

/**
 * static animation data, shared
 */
class Animation3D: public Ref
{
    friend class Bundle3D;
public:
    class Curve
    {
    public:
        typedef AnimationCurve<3> AnimationCurveVec3;
        typedef AnimationCurve<4> AnimationCurveQuat;
        AnimationCurveVec3* translateCurve;
        AnimationCurveQuat* rotCurve;
        AnimationCurveVec3* scaleCurve;
        
        Curve();
        ~Curve();
    };
    
    //read all animation or only the animation with given animationName? animationName == "" read all.
    static Animation3D* getOrCreate(const std::string& filename, const std::string& animationName = "");
    
    float getDuration() const { return _duration; }
    
    Curve* getBoneCurveByName(const std::string& name) const;
    
CC_CONSTRUCTOR_ACCESS:
    
    Animation3D();
    virtual ~Animation3D();  
    
    bool init(const Animation3DData& data);
    
protected:
    
    std::unordered_map<std::string, Curve*> _boneCurves;//bone curves map, key bone name, value AnimationCurve
    
    
    float             _duration; //animation duration
};

class Animation3DCache
{
public:
    static Animation3DCache* getInstance();
    static void destroyInstance();
    
    Animation3D* getAnimation(const std::string& key);
    
    void addAnimation(const std::string& key, Animation3D* animation);
    
    void removeAllAnimations();
    void removeUnusedAnimation();

protected:
    Animation3DCache();
    ~Animation3DCache();
    
    static Animation3DCache* _cacheInstance;
    
    std::unordered_map<std::string, Animation3D*> _animations;
};

NS_CC_END

#endif // __CCANIMATION3D_H__
