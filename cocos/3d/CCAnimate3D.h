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

#ifndef __CCANIMATE3D_H__
#define __CCANIMATE3D_H__

#include <map>
#include <unordered_map>

#include "3d/CCAnimation3D.h"
#include "base/ccMacros.h"
#include "base/CCRef.h"
#include "2d/CCActionInterval.h"

NS_CC_BEGIN

class Bone3D;
class Sprite3D;
/**
 * Animate3D, Animates a Sprite3D given with an Animation3D
 */
class CC_DLL Animate3D: public ActionInterval
{
public:
    
    /**create Animate3D using Animation.*/
    static Animate3D* create(Animation3D* animation);
    
    /**
     * create Animate3D
     * @param animation used to generate animate3D
     * @param formTime 
     * @param duration Time the Animate3D lasts
     * @return Animate3D created using animate
     */
    static Animate3D* create(Animation3D* animation, float fromTime, float duration);
    
    /**
     * create Animate3D by frame section, [startFrame, endFrame)
     * @param animation used to generate animate3D
     * @param startFrame
     * @param endFrame
     * @param frameRate default is 30 per second
     * @return Animate3D created using animate
     */
    static Animate3D* createWithFrames(Animation3D* animation, int startFrame, int endFrame, float frameRate = 30.f);
    
    //
    // Overrides
    //
    virtual void stop() override;
    virtual void step(float dt) override;
    virtual void startWithTarget(Node *target) override;
    virtual Animate3D* reverse() const override;
    virtual Animate3D *clone() const override;
    
    virtual void update(float t) override;
    
    /**get & set speed, negative speed means playing reverse */
    float getSpeed() const;
    void setSpeed(float speed);
    
    /**get & set blend weight, weight must positive*/
    float getWeight() const { return _weight; }
    void setWeight(float weight);
    
    /**get & set origin interval*/
    void setOriginInterval(float interval);
    float getOriginInterval() const {return _originInterval; }
    
    /** get animate transition time between 3d animations */
    static float getTransitionTime() { return _transTime; }
    
    /** set animate transition time between 3d animations */
    static void setTransitionTime(float transTime) { if (transTime >= 0.f) _transTime = transTime; }
    
    /**get & set play reverse, these are deprecated, use set negative speed instead*/
    CC_DEPRECATED_ATTRIBUTE bool getPlayBack() const { return _playReverse; }
    CC_DEPRECATED_ATTRIBUTE void setPlayBack(bool reverse) { _playReverse = reverse; }
    
CC_CONSTRUCTOR_ACCESS:
    
    Animate3D();
    virtual ~Animate3D();
    
    void removeFromMap();
    
    /** init method */
    bool init(Animation3D* animation);
    bool init(Animation3D* animation, float fromTime, float duration);
    bool initWithFrames(Animation3D* animation, int startFrame, int endFrame, float frameRate);
    
protected:
    
    enum class Animate3DState
    {
        FadeIn,
        FadeOut,
        Running,
    };
    Animate3DState _state; //animation state
    Animation3D* _animation; //animation data

    float      _absSpeed; //playing speed
    float      _weight; //blend weight
    float      _start; //start time 0 - 1, used to generate sub Animate3D
    float      _last; //last time 0 - 1, used to generate sub Animate3D
    bool       _playReverse; // is playing reverse
    static float      _transTime; //transition time from one animate3d to another
    float      _accTransTime; // acculate transition time
    float      _lastTime;     // last t (0 - 1)
    float      _originInterval;// save origin interval time
    std::unordered_map<Bone3D*, Animation3D::Curve*> _boneCurves; //weak ref

    //sprite animates
    static std::unordered_map<Sprite3D*, Animate3D*> s_fadeInAnimates;
    static std::unordered_map<Sprite3D*, Animate3D*> s_fadeOutAnimates;
    static std::unordered_map<Sprite3D*, Animate3D*> s_runningAnimates;
};

NS_CC_END

#endif // __CCANIMATE3D_H__
