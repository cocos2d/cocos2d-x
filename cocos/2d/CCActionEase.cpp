/****************************************************************************
Copyright (c) 2008-2009 Jason Booth
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

/*
 * Elastic, Back and Bounce actions based on code from:
 * http://github.com/NikhilK/silverlightfx/
 *
 * by http://github.com/NikhilK
 */

#include "2d/CCActionEase.h"
#include "2d/CCTweenFunction.h"

NS_CC_BEGIN

#ifndef M_PI_X_2
#define M_PI_X_2 (float)M_PI * 2.0f
#endif

//
// EaseAction
//

bool ActionEase::initWithAction(ActionInterval *action)
{
    CCASSERT(action != nullptr, "action couldn't be nullptr!");
    if (action == nullptr)
    {
        return false;
    }

    if (ActionInterval::initWithDuration(action->getDuration()))
    {
        _inner = action;
        action->retain();

        return true;
    }

    return false;
}

ActionEase::~ActionEase()
{
    CC_SAFE_RELEASE(_inner);
}

void ActionEase::startWithTarget(Node *target)
{
    if (target && _inner)
    {
        ActionInterval::startWithTarget(target);
        _inner->startWithTarget(_target);
    }
    else
    {
        log("ActionEase::startWithTarget error: target or _inner is nullptr!");
    }
}

void ActionEase::stop()
{
    if (_inner)
        _inner->stop();
    
    ActionInterval::stop();
}

void ActionEase::update(float time)
{
    _inner->update(time);
}

ActionInterval* ActionEase::getInnerAction()
{
    return _inner;
}

//
// EaseRateAction
//

EaseRateAction* EaseRateAction::create(ActionInterval* action, float rate)
{
    CCASSERT(action != nullptr, "action cannot be nullptr!");

    EaseRateAction *easeRateAction = new (std::nothrow) EaseRateAction();
    if (easeRateAction && easeRateAction->initWithAction(action, rate))
    {
        easeRateAction->autorelease();
        return easeRateAction;
    }

    CC_SAFE_DELETE(easeRateAction);
    return nullptr;
}

bool EaseRateAction::initWithAction(ActionInterval *action, float rate)
{
    if (ActionEase::initWithAction(action))
    {
        _rate = rate;
        return true;
    }

    return false;
}

//
// NOTE: Converting these macros into Templates is desirable, but please see
// issue #16159 [https://github.com/cocos2d/cocos2d-x/pull/16159] for further info
//
#define EASE_TEMPLATE_IMPL(CLASSNAME, TWEEN_FUNC, REVERSE_CLASSNAME) \
CLASSNAME* CLASSNAME::create(cocos2d::ActionInterval *action) \
{ \
    CLASSNAME *ease = new (std::nothrow) CLASSNAME(); \
    if (ease) \
    { \
        if (ease->initWithAction(action)) \
            ease->autorelease(); \
        else \
            CC_SAFE_RELEASE_NULL(ease); \
    } \
    return ease; \
} \
CLASSNAME* CLASSNAME::clone() const \
{ \
    if(_inner) return CLASSNAME::create(_inner->clone()); \
    return nullptr; \
} \
void CLASSNAME::update(float time) { \
    _inner->update(TWEEN_FUNC(time)); \
} \
ActionEase* CLASSNAME::reverse() const { \
    return REVERSE_CLASSNAME::create(_inner->reverse()); \
}

EASE_TEMPLATE_IMPL(EaseExponentialIn, tweenfunc::expoEaseIn, EaseExponentialOut)
EASE_TEMPLATE_IMPL(EaseExponentialOut, tweenfunc::expoEaseOut, EaseExponentialIn)
EASE_TEMPLATE_IMPL(EaseExponentialInOut, tweenfunc::expoEaseInOut, EaseExponentialInOut)
EASE_TEMPLATE_IMPL(EaseSineIn, tweenfunc::sineEaseIn, EaseSineOut)
EASE_TEMPLATE_IMPL(EaseSineOut, tweenfunc::sineEaseOut, EaseSineIn)
EASE_TEMPLATE_IMPL(EaseSineInOut, tweenfunc::sineEaseInOut, EaseSineInOut)
EASE_TEMPLATE_IMPL(EaseBounceIn, tweenfunc::bounceEaseIn, EaseBounceOut)
EASE_TEMPLATE_IMPL(EaseBounceOut, tweenfunc::bounceEaseOut, EaseBounceIn)
EASE_TEMPLATE_IMPL(EaseBounceInOut, tweenfunc::bounceEaseInOut, EaseBounceInOut)
EASE_TEMPLATE_IMPL(EaseBackIn, tweenfunc::backEaseIn, EaseBackOut)
EASE_TEMPLATE_IMPL(EaseBackOut, tweenfunc::backEaseOut, EaseBackIn)
EASE_TEMPLATE_IMPL(EaseBackInOut, tweenfunc::backEaseInOut, EaseBackInOut)
EASE_TEMPLATE_IMPL(EaseQuadraticActionIn, tweenfunc::quadraticIn, EaseQuadraticActionIn)
EASE_TEMPLATE_IMPL(EaseQuadraticActionOut, tweenfunc::quadraticOut, EaseQuadraticActionOut)
EASE_TEMPLATE_IMPL(EaseQuadraticActionInOut, tweenfunc::quadraticInOut, EaseQuadraticActionInOut)
EASE_TEMPLATE_IMPL(EaseQuarticActionIn, tweenfunc::quartEaseIn, EaseQuarticActionIn)
EASE_TEMPLATE_IMPL(EaseQuarticActionOut, tweenfunc::quartEaseOut, EaseQuarticActionOut)
EASE_TEMPLATE_IMPL(EaseQuarticActionInOut, tweenfunc::quartEaseInOut, EaseQuarticActionInOut)
EASE_TEMPLATE_IMPL(EaseQuinticActionIn, tweenfunc::quintEaseIn, EaseQuinticActionIn)
EASE_TEMPLATE_IMPL(EaseQuinticActionOut, tweenfunc::quintEaseOut, EaseQuinticActionOut)
EASE_TEMPLATE_IMPL(EaseQuinticActionInOut, tweenfunc::quintEaseInOut, EaseQuinticActionInOut)
EASE_TEMPLATE_IMPL(EaseCircleActionIn, tweenfunc::circEaseIn, EaseCircleActionIn)
EASE_TEMPLATE_IMPL(EaseCircleActionOut, tweenfunc::circEaseOut, EaseCircleActionOut)
EASE_TEMPLATE_IMPL(EaseCircleActionInOut, tweenfunc::circEaseInOut, EaseCircleActionInOut)
EASE_TEMPLATE_IMPL(EaseCubicActionIn, tweenfunc::cubicEaseIn, EaseCubicActionIn)
EASE_TEMPLATE_IMPL(EaseCubicActionOut, tweenfunc::cubicEaseOut, EaseCubicActionOut)
EASE_TEMPLATE_IMPL(EaseCubicActionInOut, tweenfunc::cubicEaseInOut, EaseCubicActionInOut)

//
// NOTE: Converting these macros into Templates is desirable, but please see
// issue #16159 [https://github.com/cocos2d/cocos2d-x/pull/16159] for further info
//
#define EASERATE_TEMPLATE_IMPL(CLASSNAME, TWEEN_FUNC) \
CLASSNAME* CLASSNAME::create(cocos2d::ActionInterval *action, float rate) \
{ \
    CLASSNAME *ease = new (std::nothrow) CLASSNAME(); \
    if (ease) \
    { \
        if (ease->initWithAction(action, rate)) \
            ease->autorelease(); \
        else \
            CC_SAFE_RELEASE_NULL(ease); \
    } \
    return ease; \
} \
CLASSNAME* CLASSNAME::clone() const \
{ \
    if(_inner) return CLASSNAME::create(_inner->clone(), _rate); \
    return nullptr; \
} \
void CLASSNAME::update(float time) { \
    _inner->update(TWEEN_FUNC(time, _rate)); \
} \
EaseRateAction* CLASSNAME::reverse() const { \
    return CLASSNAME::create(_inner->reverse(), 1.f / _rate); \
}

// NOTE: the original code used the same class for the `reverse()` method
EASERATE_TEMPLATE_IMPL(EaseIn, tweenfunc::easeIn)
EASERATE_TEMPLATE_IMPL(EaseOut, tweenfunc::easeOut)
EASERATE_TEMPLATE_IMPL(EaseInOut, tweenfunc::easeInOut)

//
// EaseElastic
//

bool EaseElastic::initWithAction(ActionInterval *action, float period /* = 0.3f*/)
{
    if (ActionEase::initWithAction(action))
    {
        _period = period;
        return true;
    }

    return false;
}

//
// NOTE: Converting these macros into Templates is desirable, but please see
// issue #16159 [https://github.com/cocos2d/cocos2d-x/pull/16159] for further info
//
#define EASEELASTIC_TEMPLATE_IMPL(CLASSNAME, TWEEN_FUNC, REVERSE_CLASSNAME) \
CLASSNAME* CLASSNAME::create(cocos2d::ActionInterval *action, float period /* = 0.3f*/) \
{ \
    CLASSNAME *ease = new (std::nothrow) CLASSNAME(); \
    if (ease) \
    { \
        if (ease->initWithAction(action, period)) \
            ease->autorelease(); \
        else \
            CC_SAFE_RELEASE_NULL(ease); \
    } \
    return ease; \
} \
CLASSNAME* CLASSNAME::clone() const \
{ \
    if(_inner) return CLASSNAME::create(_inner->clone(), _period); \
    return nullptr; \
} \
void CLASSNAME::update(float time) { \
    _inner->update(TWEEN_FUNC(time, _period)); \
} \
EaseElastic* CLASSNAME::reverse() const { \
    return REVERSE_CLASSNAME::create(_inner->reverse(), _period); \
}

EASEELASTIC_TEMPLATE_IMPL(EaseElasticIn, tweenfunc::elasticEaseIn, EaseElasticOut)
EASEELASTIC_TEMPLATE_IMPL(EaseElasticOut, tweenfunc::elasticEaseOut, EaseElasticIn)
EASEELASTIC_TEMPLATE_IMPL(EaseElasticInOut, tweenfunc::elasticEaseInOut, EaseElasticInOut)

//
// EaseBezierAction
//

EaseBezierAction* EaseBezierAction::create(cocos2d::ActionInterval* action)
{
    EaseBezierAction *ret = new (std::nothrow) EaseBezierAction();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

void EaseBezierAction::setBezierParamer( float p0, float p1, float p2, float p3)
{
    _p0 = p0;
    _p1 = p1;
    _p2 = p2;
    _p3 = p3;
}

EaseBezierAction* EaseBezierAction::clone() const
{
    // no copy constructor
    if (_inner)
    {
        auto ret = EaseBezierAction::create(_inner->clone());
        if (ret)
        {
            ret->setBezierParamer(_p0,_p1,_p2,_p3);
        }
        return ret;
    }

    return nullptr;
}

void EaseBezierAction::update(float time)
{
    _inner->update(tweenfunc::bezieratFunction(_p0,_p1,_p2,_p3,time));
}

EaseBezierAction* EaseBezierAction::reverse() const
{
    EaseBezierAction* reverseAction = EaseBezierAction::create(_inner->reverse());
    reverseAction->setBezierParamer(_p3,_p2,_p1,_p0);
    return reverseAction;
}

NS_CC_END
