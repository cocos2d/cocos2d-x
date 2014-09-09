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

#include "3d/CCAnimate3D.h"
#include "3d/CCSprite3D.h"
#include "3d/CCSkeleton3D.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

std::unordered_map<Sprite3D*, Animate3D*> Animate3D::s_fadeInAnimates;
std::unordered_map<Sprite3D*, Animate3D*> Animate3D::s_fadeOutAnimates;
std::unordered_map<Sprite3D*, Animate3D*> Animate3D::s_runningAnimates;
float      Animate3D::_transTime = 0.1f;

//create Animate3D using Animation.
Animate3D* Animate3D::create(Animation3D* animation)
{
    auto animate = new (std::nothrow) Animate3D();
    animate->_animation = animation;
    animation->retain();
    
    animate->autorelease();
    animate->setDuration(animation->getDuration());
    
    return animate;
}

Animate3D* Animate3D::create(Animation3D* animation, float fromTime, float duration)
{
    auto animate = Animate3D::create(animation);
    
    float fullDuration = animation->getDuration();
    if (duration > fullDuration - fromTime)
        duration = fullDuration - fromTime;
    
    animate->_start = fromTime / fullDuration;
    animate->_last = duration / fullDuration;
    animate->setDuration(duration);
    
    return  animate;
}

/** returns a clone of action */
Animate3D* Animate3D::clone() const
{
    auto animate = const_cast<Animate3D*>(this);
    auto copy = Animate3D::create(animate->_animation);
    
    copy->_absSpeed = _absSpeed;
    copy->_weight = _weight;
    copy->_elapsed = _elapsed;
    copy->_start = _start;
    copy->_last = _last;
    copy->_playReverse = _playReverse;
    copy->setDuration(animate->getDuration());

    return copy;
}

/** returns a new action that performs the exactly the reverse action */
Animate3D* Animate3D::reverse() const
{
    auto animate = clone();
    animate->_playReverse = !animate->_playReverse;
    return animate;
}

//! called before the action start. It will also set the target.
void Animate3D::startWithTarget(Node *target)
{
    Sprite3D* sprite = dynamic_cast<Sprite3D*>(target);
    CCASSERT(sprite && sprite->getSkeleton() && _animation, "Animate3D apply to Sprite3D only");
    
    ActionInterval::startWithTarget(target);
    
    _boneCurves.clear();
    auto skin = sprite->getSkeleton();
    bool hasCurve = false;
    for (unsigned int  i = 0; i < skin->getBoneCount(); i++) {
        auto bone = skin->getBoneByIndex(i);
        auto curve = _animation->getBoneCurveByName(bone->getName());
        if (curve)
        {
            _boneCurves[bone] = curve;
            hasCurve = true;
        }
    }
    if (!hasCurve)
    {
        CCLOG("warning: no animation finde for the skeleton");
    }
    
    auto runningAction = s_runningAnimates.find(sprite);
    if (runningAction != s_runningAnimates.end())
    {
        //make the running action fade out
        auto action = (*runningAction).second;
        if (action != this)
        {
            s_fadeOutAnimates[sprite] = action;
            action->_state = Animate3D::Animate3DState::FadeOut;
            action->_accTransTime = 0.0f;
            action->_weight = 1.0f;
            action->_lastTime = 0.f;
            
            s_fadeInAnimates[sprite] = this;
            _accTransTime = 0.0f;
            _state = Animate3D::Animate3DState::FadeIn;
            _weight = 0.f;
            _lastTime = 0.f;
        }
    }
    else
    {
        s_runningAnimates[sprite] = this;
        _state = Animate3D::Animate3DState::Running;
        _weight = 1.0f;
    }
}

void Animate3D::stop()
{
    removeFromMap();
    
    ActionInterval::stop();
}

//! called every frame with it's delta time. DON'T override unless you know what you are doing.
void Animate3D::step(float dt)
{
    ActionInterval::step(dt * _absSpeed);
}

void Animate3D::update(float t)
{
    if (_target)
    {
        if (_state == Animate3D::Animate3DState::FadeIn && _lastTime > 0.f)
        {
            _accTransTime += (t - _lastTime) * getDuration();
            
            _weight = _accTransTime / _transTime;
            if (_weight >= 1.0f)
            {
                _accTransTime = _transTime;
                _weight = 1.0f;
                _state = Animate3D::Animate3DState::Running;
                Sprite3D* sprite = static_cast<Sprite3D*>(_target);
                s_fadeInAnimates.erase(sprite);
                s_runningAnimates[sprite] = this;
            }
        }
        else if (_state == Animate3D::Animate3DState::FadeOut && _lastTime > 0.f)
        {
            _accTransTime += (t - _lastTime) * getDuration();
            
            _weight = 1 - _accTransTime / _transTime;
            if (_weight <= 0.0f)
            {
                _accTransTime = _transTime;
                _weight = 0.0f;
                
                Sprite3D* sprite = static_cast<Sprite3D*>(_target);
                s_fadeOutAnimates.erase(sprite);
            }
        }
        _lastTime = t;
        
        if (_weight > 0.0f)
        {
            float transDst[3], rotDst[4], scaleDst[3];
            float* trans = nullptr, *rot = nullptr, *scale = nullptr;
            if (_playReverse)
                t = 1 - t;
            
            t = _start + t * _last;
            for (const auto& it : _boneCurves) {
                auto bone = it.first;
                auto curve = it.second;
                if (curve->translateCurve)
                {
                    curve->translateCurve->evaluate(t, transDst, EvaluateType::INT_LINEAR);
                    trans = &transDst[0];
                }
                if (curve->rotCurve)
                {
                    curve->rotCurve->evaluate(t, rotDst, EvaluateType::INT_QUAT_SLERP);
                    rot = &rotDst[0];
                }
                if (curve->scaleCurve)
                {
                    curve->scaleCurve->evaluate(t, scaleDst, EvaluateType::INT_LINEAR);
                    scale = &scaleDst[0];
                }
                bone->setAnimationValue(trans, rot, scale, this, _weight);
            }
        }
    }
}

float Animate3D::getSpeed() const
{
    return _playReverse ? -_absSpeed : _absSpeed;
}
void Animate3D::setSpeed(float speed)
{
    _absSpeed = fabsf(speed);
    _playReverse = speed < 0;
}

void Animate3D::setWeight(float weight)
{
    CCASSERT(weight >= 0.0f, "invalid weight");
    _weight = fabsf(weight);
}

Animate3D::Animate3D()
: _absSpeed(1.f)
, _weight(1.f)
, _start(0.f)
, _last(1.f)
, _animation(nullptr)
, _playReverse(false)
, _state(Animate3D::Animate3DState::Running)
, _accTransTime(0.0f)
, _lastTime(0.0f)
{
    
}
Animate3D::~Animate3D()
{
    removeFromMap();
    
    CC_SAFE_RELEASE(_animation);
}

void Animate3D::removeFromMap()
{
    //remove this action from map
    if (_target)
    {
        Sprite3D* sprite = static_cast<Sprite3D*>(_target);
        if (_state == Animate3D::Animate3DState::FadeIn)
            s_fadeInAnimates.erase(sprite);
        else if (_state == Animate3D::Animate3DState::FadeOut)
            s_fadeOutAnimates.erase(sprite);
        else
            s_runningAnimates.erase(sprite);
    }
}

NS_CC_END
