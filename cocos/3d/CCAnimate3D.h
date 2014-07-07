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

#include "3d/CCAnimation3D.h"

#include "base/ccMacros.h"
#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "2d/CCActionInterval.h"

NS_CC_BEGIN

class Animation3D;
class Bone;
/**
 * Animate3D, Animates a Sprite3D given with an Animation3D
 */
class Animate3D: public ActionInterval
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
    //
    // Overrides
    //
    virtual void step(float dt) override;
    virtual void startWithTarget(Node *target) override;
    virtual Animate3D* reverse() const override;
    virtual Animate3D *clone() const override;
    
    virtual void update(float t) override;
    
    /**get & set speed */
    float getSpeed() const { return _speed; }
    void setSpeed(float speed) { _speed = speed; }
    
    /**get & set blend weight*/
    float getWeight() const { return _weight; }
    void setWeight(float weight) { _weight = weight; }
    
    /**get & set play back*/
    bool getPlayBack() const { return _playBack; }
    void setPlayBack(bool playBack) { _playBack = playBack; }
    
CC_CONSTRUCTOR_ACCESS:
    
    Animate3D();
    virtual ~Animate3D();
    
protected:
    Animation3D* _animation; //animation data

    float      _speed; //playing speed
    float      _weight; //blend weight
    float      _start; //start time 0 - 1, used to generate sub Animate3D
    float      _last; //last time 0 - 1, used to generate sub Animate3D
    bool       _playBack; // is playing back
    std::map<Bone*, Animation3D::Curve*> _boneCurves; //weak ref
};

NS_CC_END

#endif // __CCANIMATE3D_H__
