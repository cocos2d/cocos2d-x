/****************************************************************************
Copyright (c) 2008-2009 Jason Booth
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.

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

ActionEase::~ActionEase(void)
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

void ActionEase::stop(void)
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
    EaseRateAction *easeRateAction = new (std::nothrow) EaseRateAction();
    if (easeRateAction && easeRateAction->initWithAction(action, rate))
    {
        easeRateAction->autorelease();
        return easeRateAction;
    }
    
    delete easeRateAction;
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

EaseRateAction::~EaseRateAction()
{
}

//
// EeseIn
//

EaseIn* EaseIn::create(ActionInterval *action, float rate)
{
    EaseIn *easeIn = new (std::nothrow) EaseIn();
    if (easeIn && easeIn->initWithAction(action, rate))
    {
        easeIn->autorelease();
        return easeIn;
    }

    delete easeIn;
    return nullptr;
}

EaseIn* EaseIn::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseIn::create(_inner->clone(), _rate);
    
    return nullptr;
}

void EaseIn::update(float time)
{
    _inner->update(tweenfunc::easeIn(time, _rate));
}

EaseIn* EaseIn::reverse() const
{
    return EaseIn::create(_inner->reverse(), 1 / _rate);
}

//
// EaseOut
//
EaseOut* EaseOut::create(ActionInterval *action, float rate)
{
    EaseOut *easeOut = new (std::nothrow) EaseOut();
    if (easeOut && easeOut->initWithAction(action, rate))
    {
        easeOut->autorelease();
        return easeOut;
    }

    delete easeOut;
    return nullptr;
}

EaseOut* EaseOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseOut::create(_inner->clone(), _rate);
    
    return nullptr;
}

void EaseOut::update(float time)
{
    _inner->update(tweenfunc::easeOut(time, _rate));
}

EaseOut* EaseOut::reverse() const
{
    return EaseOut::create(_inner->reverse(), 1 / _rate);
}

//
// EaseInOut
//
EaseInOut* EaseInOut::create(ActionInterval *action, float rate)
{
    EaseInOut *easeInOut = new (std::nothrow) EaseInOut();
    if (easeInOut && easeInOut->initWithAction(action, rate))
    {
        easeInOut->autorelease();
        return easeInOut;
    }

    delete easeInOut;
    return nullptr;
}

EaseInOut* EaseInOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseInOut::create(_inner->clone(), _rate);
    
    return nullptr;
}

void EaseInOut::update(float time)
{
    _inner->update(tweenfunc::easeInOut(time, _rate));
}

// InOut and OutIn are symmetrical
EaseInOut* EaseInOut::reverse() const
{
    return EaseInOut::create(_inner->reverse(), _rate);
}

//
// EaseExponentialIn
//
EaseExponentialIn* EaseExponentialIn::create(ActionInterval* action)
{
    EaseExponentialIn *ret = new (std::nothrow) EaseExponentialIn();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseExponentialIn* EaseExponentialIn::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseExponentialIn::create(_inner->clone());
    
    return nullptr;
}

void EaseExponentialIn::update(float time)
{
    _inner->update(tweenfunc::expoEaseIn(time));
}

ActionEase * EaseExponentialIn::reverse() const
{
    return EaseExponentialOut::create(_inner->reverse());
}

//
// EaseExponentialOut
//
EaseExponentialOut* EaseExponentialOut::create(ActionInterval* action)
{
    EaseExponentialOut *ret = new (std::nothrow) EaseExponentialOut();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseExponentialOut* EaseExponentialOut::clone() const
{
    // no copy constructor
    if (_inner)
        EaseExponentialOut::create(_inner->clone());
    
    return nullptr;
}

void EaseExponentialOut::update(float time)
{
    _inner->update(tweenfunc::expoEaseOut(time));
}

ActionEase* EaseExponentialOut::reverse() const
{
    return EaseExponentialIn::create(_inner->reverse());
}

//
// EaseExponentialInOut
//

EaseExponentialInOut* EaseExponentialInOut::create(ActionInterval *action)
{
    EaseExponentialInOut *ret = new (std::nothrow) EaseExponentialInOut();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseExponentialInOut* EaseExponentialInOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseExponentialInOut::create(_inner->clone());
    
    return nullptr;
}

void EaseExponentialInOut::update(float time)
{
    _inner->update(tweenfunc::expoEaseInOut(time));
}

EaseExponentialInOut* EaseExponentialInOut::reverse() const
{
    return EaseExponentialInOut::create(_inner->reverse());
}

//
// EaseSineIn
//

EaseSineIn* EaseSineIn::create(ActionInterval* action)
{
    EaseSineIn *ret = new (std::nothrow) EaseSineIn();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseSineIn* EaseSineIn::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseSineIn::create(_inner->clone());
    
    return nullptr;
}

void EaseSineIn::update(float time)
{
    _inner->update(tweenfunc::sineEaseIn(time));
}

ActionEase* EaseSineIn::reverse() const
{
    return EaseSineOut::create(_inner->reverse());
}

//
// EaseSineOut
//

EaseSineOut* EaseSineOut::create(ActionInterval* action)
{
    EaseSineOut *ret = new (std::nothrow) EaseSineOut();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseSineOut* EaseSineOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseSineOut::create(_inner->clone());
    
    return nullptr;
}

void EaseSineOut::update(float time)
{
    _inner->update(tweenfunc::sineEaseOut(time));
}

ActionEase* EaseSineOut::reverse(void) const
{
    return EaseSineIn::create(_inner->reverse());
}

//
// EaseSineInOut
//

EaseSineInOut* EaseSineInOut::create(ActionInterval* action)
{
    EaseSineInOut *ret = new (std::nothrow) EaseSineInOut();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseSineInOut* EaseSineInOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseSineInOut::create(_inner->clone());
    
    return nullptr;
}

void EaseSineInOut::update(float time)
{
    _inner->update(tweenfunc::sineEaseInOut(time));
}

EaseSineInOut* EaseSineInOut::reverse() const
{
    return EaseSineInOut::create(_inner->reverse());
}

//
// EaseElastic
//

bool EaseElastic::initWithAction(ActionInterval *action, float period/* = 0.3f*/)
{
    if (ActionEase::initWithAction(action))
    {
        _period = period;
        return true;
    }

    return false;
}

//
// EaseElasticIn
//

EaseElasticIn* EaseElasticIn::create(ActionInterval *action)
{
    return EaseElasticIn::create(action, 0.3f);
}

EaseElasticIn* EaseElasticIn::create(ActionInterval *action, float period/* = 0.3f*/)
{
    EaseElasticIn *ret = new (std::nothrow) EaseElasticIn();
    if (ret && ret->initWithAction(action, period))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseElasticIn* EaseElasticIn::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseElasticIn::create(_inner->clone(), _period);
    
    return nullptr;
}

void EaseElasticIn::update(float time)
{
    _inner->update(tweenfunc::elasticEaseIn(time, _period));
}

EaseElastic* EaseElasticIn::reverse() const
{
    return EaseElasticOut::create(_inner->reverse(), _period);
}

//
// EaseElasticOut
//

EaseElasticOut* EaseElasticOut::create(ActionInterval *action)
{
    return EaseElasticOut::create(action, 0.3f);
}

EaseElasticOut* EaseElasticOut::create(ActionInterval *action, float period/* = 0.3f*/)
{
    EaseElasticOut *ret = new (std::nothrow) EaseElasticOut();
    if (ret && ret->initWithAction(action, period))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseElasticOut* EaseElasticOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseElasticOut::create(_inner->clone(), _period);
    
    return nullptr;
}

void EaseElasticOut::update(float time)
{
    _inner->update(tweenfunc::elasticEaseOut(time, _period));
}

EaseElastic* EaseElasticOut::reverse() const
{
    return EaseElasticIn::create(_inner->reverse(), _period);
}

//
// EaseElasticInOut
//

EaseElasticInOut* EaseElasticInOut::create(ActionInterval *action)
{
    return EaseElasticInOut::create(action, 0.3f);
}

EaseElasticInOut* EaseElasticInOut::create(ActionInterval *action, float period/* = 0.3f*/)
{
    EaseElasticInOut *ret = new (std::nothrow) EaseElasticInOut();
    if (ret && ret->initWithAction(action, period))
    {
        ret->autorelease();
        return ret;
    }
    
    delete ret;
    return nullptr;
}

EaseElasticInOut* EaseElasticInOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseElasticInOut::create(_inner->clone(), _period);
    
    return nullptr;
}

void EaseElasticInOut::update(float time)
{
    _inner->update(tweenfunc::elasticEaseInOut(time, _period));
}

EaseElasticInOut* EaseElasticInOut::reverse() const
{
    return EaseElasticInOut::create(_inner->reverse(), _period);
}

//
// EaseBounce
//

//
// EaseBounceIn
//

EaseBounceIn* EaseBounceIn::create(ActionInterval* action)
{
    EaseBounceIn *ret = new (std::nothrow) EaseBounceIn();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseBounceIn* EaseBounceIn::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseBounceIn::create(_inner->clone());
    
    return nullptr;
}

void EaseBounceIn::update(float time)
{
    _inner->update(tweenfunc::bounceEaseIn(time));
}

EaseBounce* EaseBounceIn::reverse() const
{
    return EaseBounceOut::create(_inner->reverse());
}

//
// EaseBounceOut
//

EaseBounceOut* EaseBounceOut::create(ActionInterval* action)
{
    EaseBounceOut *ret = new (std::nothrow) EaseBounceOut();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseBounceOut* EaseBounceOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseBounceOut::create(_inner->clone());
    
    return nullptr;
}

void EaseBounceOut::update(float time)
{
    _inner->update(tweenfunc::bounceEaseOut(time));
}

EaseBounce* EaseBounceOut::reverse() const
{
    return EaseBounceIn::create(_inner->reverse());
}

//
// EaseBounceInOut
//

EaseBounceInOut* EaseBounceInOut::create(ActionInterval* action)
{
    EaseBounceInOut *ret = new (std::nothrow) EaseBounceInOut();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseBounceInOut* EaseBounceInOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseBounceInOut::create(_inner->clone());
    
    return nullptr;
}

void EaseBounceInOut::update(float time)
{
    _inner->update(tweenfunc::bounceEaseInOut(time));
}

EaseBounceInOut* EaseBounceInOut::reverse() const
{
    return EaseBounceInOut::create(_inner->reverse());
}

//
// EaseBackIn
//

EaseBackIn* EaseBackIn::create(ActionInterval *action)
{
    EaseBackIn *ret = new (std::nothrow) EaseBackIn();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseBackIn* EaseBackIn::clone() const
{
    if (_inner)
        return EaseBackIn::create(_inner->clone());

    return nullptr;
}

void EaseBackIn::update(float time)
{
    _inner->update(tweenfunc::backEaseIn(time));
}

ActionEase* EaseBackIn::reverse() const
{
    return EaseBackOut::create(_inner->reverse());
}

//
// EaseBackOut
//

EaseBackOut* EaseBackOut::create(ActionInterval* action)
{
    EaseBackOut *ret = new (std::nothrow) EaseBackOut();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseBackOut* EaseBackOut::clone() const
{
    if (_inner)
        return EaseBackOut::create(_inner->clone());

    return nullptr;
}

void EaseBackOut::update(float time)
{
    _inner->update(tweenfunc::backEaseOut(time));
}

ActionEase* EaseBackOut::reverse() const
{
    return EaseBackIn::create(_inner->reverse());
}

//
// EaseBackInOut
//

EaseBackInOut* EaseBackInOut::create(ActionInterval* action)
{
    EaseBackInOut *ret = new (std::nothrow) EaseBackInOut();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseBackInOut* EaseBackInOut::clone() const
{
    if (_inner)
        return EaseBackInOut::create(_inner->clone());

    return nullptr;
}

void EaseBackInOut::update(float time)
{
    _inner->update(tweenfunc::backEaseInOut(time));
}

EaseBackInOut* EaseBackInOut::reverse() const
{
    return EaseBackInOut::create(_inner->reverse());
}

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

//
// EaseQuadraticActionIn
//

EaseQuadraticActionIn* EaseQuadraticActionIn::create(ActionInterval* action)
{
    EaseQuadraticActionIn *ret = new (std::nothrow) EaseQuadraticActionIn();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseQuadraticActionIn* EaseQuadraticActionIn::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseQuadraticActionIn::create(_inner->clone());
    
    return nullptr;
}

void EaseQuadraticActionIn::update(float time)
{
    _inner->update(tweenfunc::quadraticIn(time));
}

EaseQuadraticActionIn* EaseQuadraticActionIn::reverse() const
{
    return EaseQuadraticActionIn::create(_inner->reverse());
}

//
// EaseQuadraticActionOut
//

EaseQuadraticActionOut* EaseQuadraticActionOut::create(ActionInterval* action)
{
    EaseQuadraticActionOut *ret = new (std::nothrow) EaseQuadraticActionOut();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseQuadraticActionOut* EaseQuadraticActionOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseQuadraticActionOut::create(_inner->clone());
    
    return nullptr;
}

void EaseQuadraticActionOut::update(float time)
{
    _inner->update(tweenfunc::quadraticOut(time));
}

EaseQuadraticActionOut* EaseQuadraticActionOut::reverse() const
{
    return EaseQuadraticActionOut::create(_inner->reverse());
}

//
// EaseQuadraticActionInOut
//

EaseQuadraticActionInOut* EaseQuadraticActionInOut::create(ActionInterval* action)
{
    EaseQuadraticActionInOut *ret = new (std::nothrow) EaseQuadraticActionInOut();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseQuadraticActionInOut* EaseQuadraticActionInOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseQuadraticActionInOut::create(_inner->clone());
    
    return nullptr;
}

void EaseQuadraticActionInOut::update(float time)
{
    _inner->update(tweenfunc::quadraticInOut(time));
}

EaseQuadraticActionInOut* EaseQuadraticActionInOut::reverse() const
{
    return EaseQuadraticActionInOut::create(_inner->reverse());
}

//
// EaseQuarticActionIn
//

EaseQuarticActionIn* EaseQuarticActionIn::create(ActionInterval* action)
{
    EaseQuarticActionIn *ret = new (std::nothrow) EaseQuarticActionIn();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseQuarticActionIn* EaseQuarticActionIn::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseQuarticActionIn::create(_inner->clone());
    
    return nullptr;
}

void EaseQuarticActionIn::update(float time)
{
    _inner->update(tweenfunc::quartEaseIn(time));
}

EaseQuarticActionIn* EaseQuarticActionIn::reverse() const
{
    return EaseQuarticActionIn::create(_inner->reverse());
}

//
// EaseQuarticActionOut
//

EaseQuarticActionOut* EaseQuarticActionOut::create(ActionInterval* action)
{
    EaseQuarticActionOut *ret = new (std::nothrow) EaseQuarticActionOut();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseQuarticActionOut* EaseQuarticActionOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseQuarticActionOut::create(_inner->clone());
    
    return nullptr;
}

void EaseQuarticActionOut::update(float time)
{
    _inner->update(tweenfunc::quartEaseOut(time));
}

EaseQuarticActionOut* EaseQuarticActionOut::reverse() const
{
    return EaseQuarticActionOut::create(_inner->reverse());
}

//
// EaseQuarticActionInOut
//

EaseQuarticActionInOut* EaseQuarticActionInOut::create(ActionInterval* action)
{
    EaseQuarticActionInOut *ret = new (std::nothrow) EaseQuarticActionInOut();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseQuarticActionInOut* EaseQuarticActionInOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseQuarticActionInOut::create(_inner->clone());
    
    return nullptr;
}

void EaseQuarticActionInOut::update(float time)
{
    _inner->update(tweenfunc::quartEaseInOut(time));
}

EaseQuarticActionInOut* EaseQuarticActionInOut::reverse() const
{
    return EaseQuarticActionInOut::create(_inner->reverse());
}

//
// EaseQuinticActionIn
//

EaseQuinticActionIn* EaseQuinticActionIn::create(ActionInterval* action)
{
    EaseQuinticActionIn *ret = new (std::nothrow) EaseQuinticActionIn();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseQuinticActionIn* EaseQuinticActionIn::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseQuinticActionIn::create(_inner->clone());
    
    return nullptr;
}

void EaseQuinticActionIn::update(float time)
{
    _inner->update(tweenfunc::quintEaseIn(time));
}

EaseQuinticActionIn* EaseQuinticActionIn::reverse() const
{
    return EaseQuinticActionIn::create(_inner->reverse());
}

//
// EaseQuinticActionOut
//

EaseQuinticActionOut* EaseQuinticActionOut::create(ActionInterval* action)
{
    EaseQuinticActionOut *ret = new (std::nothrow) EaseQuinticActionOut();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseQuinticActionOut* EaseQuinticActionOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseQuinticActionOut::create(_inner->clone());
    
    return nullptr;
}

void EaseQuinticActionOut::update(float time)
{
    _inner->update(tweenfunc::quintEaseOut(time));
}

EaseQuinticActionOut* EaseQuinticActionOut::reverse() const
{
    return EaseQuinticActionOut::create(_inner->reverse());
}

//
// EaseQuinticActionInOut
//

EaseQuinticActionInOut* EaseQuinticActionInOut::create(ActionInterval* action)
{
    EaseQuinticActionInOut *ret = new (std::nothrow) EaseQuinticActionInOut();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseQuinticActionInOut* EaseQuinticActionInOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseQuinticActionInOut::create(_inner->clone());
    
    return nullptr;
}

void EaseQuinticActionInOut::update(float time)
{
    _inner->update(tweenfunc::quintEaseInOut(time));
}

EaseQuinticActionInOut* EaseQuinticActionInOut::reverse() const
{
    return EaseQuinticActionInOut::create(_inner->reverse());
}

//
// EaseCircleActionIn
//

EaseCircleActionIn* EaseCircleActionIn::create(ActionInterval* action)
{
    EaseCircleActionIn *ret = new (std::nothrow) EaseCircleActionIn();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseCircleActionIn* EaseCircleActionIn::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseCircleActionIn::create(_inner->clone());
    
    return nullptr;
}

void EaseCircleActionIn::update(float time)
{
    _inner->update(tweenfunc::circEaseIn(time));
}

EaseCircleActionIn* EaseCircleActionIn::reverse() const
{
    return EaseCircleActionIn::create(_inner->reverse());
}

//
// EaseCircleActionOut
//

EaseCircleActionOut* EaseCircleActionOut::create(ActionInterval* action)
{
    EaseCircleActionOut *ret = new (std::nothrow) EaseCircleActionOut();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseCircleActionOut* EaseCircleActionOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseCircleActionOut::create(_inner->clone());
    
    return nullptr;
}

void EaseCircleActionOut::update(float time)
{
    _inner->update(tweenfunc::circEaseOut(time));
}

EaseCircleActionOut* EaseCircleActionOut::reverse() const
{
    return EaseCircleActionOut::create(_inner->reverse());
}

//
// EaseCircleActionInOut
//

EaseCircleActionInOut* EaseCircleActionInOut::create(ActionInterval* action)
{
    EaseCircleActionInOut *ret = new (std::nothrow) EaseCircleActionInOut();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }
    
    delete ret;
    return nullptr;
}

EaseCircleActionInOut* EaseCircleActionInOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseCircleActionInOut::create(_inner->clone());
    
    return nullptr;
}

void EaseCircleActionInOut::update(float time)
{
    _inner->update(tweenfunc::circEaseInOut(time));
}

EaseCircleActionInOut* EaseCircleActionInOut::reverse() const
{
    return EaseCircleActionInOut::create(_inner->reverse());
}

//
// EaseCubicActionIn
//

EaseCubicActionIn* EaseCubicActionIn::create(ActionInterval* action)
{
    EaseCubicActionIn *ret = new (std::nothrow) EaseCubicActionIn();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseCubicActionIn* EaseCubicActionIn::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseCubicActionIn::create(_inner->clone());
    
    return nullptr;
}

void EaseCubicActionIn::update(float time)
{
    _inner->update(tweenfunc::cubicEaseIn(time));
}

EaseCubicActionIn* EaseCubicActionIn::reverse() const
{
    return EaseCubicActionIn::create(_inner->reverse());
}

//
// EaseCubicActionOut
//

EaseCubicActionOut* EaseCubicActionOut::create(ActionInterval* action)
{
    EaseCubicActionOut *ret = new (std::nothrow) EaseCubicActionOut();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseCubicActionOut* EaseCubicActionOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseCubicActionOut::create(_inner->clone());
    
    return nullptr;
}

void EaseCubicActionOut::update(float time)
{
    _inner->update(tweenfunc::cubicEaseOut(time));
}

EaseCubicActionOut* EaseCubicActionOut::reverse() const
{
    return EaseCubicActionOut::create(_inner->reverse());
}

//
// EaseCubicActionInOut
//

EaseCubicActionInOut* EaseCubicActionInOut::create(ActionInterval* action)
{
    EaseCubicActionInOut *ret = new (std::nothrow) EaseCubicActionInOut();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

EaseCubicActionInOut* EaseCubicActionInOut::clone() const
{
    // no copy constructor
    if (_inner)
        return EaseCubicActionInOut::create(_inner->clone());
    
    return nullptr;
}

void EaseCubicActionInOut::update(float time)
{
    _inner->update(tweenfunc::cubicEaseInOut(time));
}

EaseCubicActionInOut* EaseCubicActionInOut::reverse() const
{
    if (_inner)
        return EaseCubicActionInOut::create(_inner->reverse());
    
    return nullptr;
}

NS_CC_END
