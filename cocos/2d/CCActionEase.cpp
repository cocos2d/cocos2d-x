/****************************************************************************
Copyright (c) 2008-2009 Jason Booth
Copyright (c) 2010-2012 cocos2d-x.org
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

/*
 * Elastic, Back and Bounce actions based on code from:
 * http://github.com/NikhilK/silverlightfx/
 *
 * by http://github.com/NikhilK
 */

#include "CCActionEase.h"

NS_CC_BEGIN

#ifndef M_PI_X_2
#define M_PI_X_2 (float)M_PI * 2.0f
#endif

//
// EaseAction
//

bool ActionEase::initWithAction(ActionInterval *action)
{
    CCASSERT(action != nullptr, "");

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
    ActionInterval::startWithTarget(target);
    _inner->startWithTarget(_target);
}

void ActionEase::stop(void)
{
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
    EaseIn *easeIn = new EaseIn();
    if (easeIn)
    {
        if (easeIn->initWithAction(action, rate))
        {
            easeIn->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(easeIn);
        }
    }

    return easeIn;
}

EaseIn* EaseIn::clone() const
{
	// no copy constructor
	auto a = new EaseIn();
	a->initWithAction(_inner->clone(), _rate);
	a->autorelease();
	return a;
}

void EaseIn::update(float time)
{
    _inner->update(powf(time, _rate));
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
    EaseOut *easeOut = new EaseOut();
    if (easeOut)
    {
        if (easeOut->initWithAction(action, rate))
        {
            easeOut->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(easeOut);
        }
    }

    return easeOut;
}

EaseOut* EaseOut::clone() const
{
	// no copy constructor
	auto a = new EaseOut();
	a->initWithAction(_inner->clone(), _rate);
	a->autorelease();
	return a;
}

void EaseOut::update(float time)
{
    _inner->update(powf(time, 1 / _rate));
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
    EaseInOut *easeInOut = new EaseInOut();
    if (easeInOut)
    {
        if (easeInOut->initWithAction(action, rate))
        {
            easeInOut->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(easeInOut);
        }
    }

    return easeInOut;
}

EaseInOut* EaseInOut::clone() const
{
	// no copy constructor
	auto a = new EaseInOut();
	a->initWithAction(_inner->clone(), _rate);
	a->autorelease();
	return a;
}

void EaseInOut::update(float time)
{
    time *= 2;
    if (time < 1)
    {
        _inner->update(0.5f * powf(time, _rate));
    }
    else
    {
        _inner->update(1.0f - 0.5f * powf(2-time, _rate));
    }
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
    EaseExponentialIn *ret = new EaseExponentialIn();
    if (ret)
    {
        if (ret->initWithAction(action))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

EaseExponentialIn* EaseExponentialIn::clone() const
{
	// no copy constructor
	auto a = new EaseExponentialIn();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

void EaseExponentialIn::update(float time)
{
    _inner->update(time == 0 ? 0 : powf(2, 10 * (time/1 - 1)) - 1 * 0.001f);
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
    EaseExponentialOut *ret = new EaseExponentialOut();
    if (ret)
    {
        if (ret->initWithAction(action))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

EaseExponentialOut* EaseExponentialOut::clone() const
{
	// no copy constructor
	auto a = new EaseExponentialOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

void EaseExponentialOut::update(float time)
{
    _inner->update(time == 1 ? 1 : (-powf(2, -10 * time / 1) + 1));
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
    EaseExponentialInOut *ret = new EaseExponentialInOut();
    if (ret)
    {
        if (ret->initWithAction(action))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

EaseExponentialInOut* EaseExponentialInOut::clone() const
{
	// no copy constructor
	auto a = new EaseExponentialInOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

void EaseExponentialInOut::update(float time)
{
    time /= 0.5f;
    if (time < 1)
    {
        time = 0.5f * powf(2, 10 * (time - 1));
    }
    else
    {
        time = 0.5f * (-powf(2, -10 * (time - 1)) + 2);
    }

    _inner->update(time);
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
    EaseSineIn *ret = new EaseSineIn();
    if (ret)
    {
        if (ret->initWithAction(action))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

EaseSineIn* EaseSineIn::clone() const
{
	// no copy constructor
	auto a = new EaseSineIn();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

void EaseSineIn::update(float time)
{
    _inner->update(-1 * cosf(time * (float)M_PI_2) + 1);
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
    EaseSineOut *ret = new EaseSineOut();
    if (ret)
    {
        if (ret->initWithAction(action))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

EaseSineOut* EaseSineOut::clone() const
{
	// no copy constructor
	auto a = new EaseSineOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

void EaseSineOut::update(float time)
{
    _inner->update(sinf(time * (float)M_PI_2));
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
    EaseSineInOut *ret = new EaseSineInOut();
    if (ret)
    {
        if (ret->initWithAction(action))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

EaseSineInOut* EaseSineInOut::clone() const
{
	// no copy constructor
	auto a = new EaseSineInOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

void EaseSineInOut::update(float time)
{
    _inner->update(-0.5f * (cosf((float)M_PI * time) - 1));
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
    EaseElasticIn *ret = new EaseElasticIn();
    if (ret)
    {
        if (ret->initWithAction(action, period))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

EaseElasticIn* EaseElasticIn::clone() const
{
	// no copy constructor
	auto a = new EaseElasticIn();
	a->initWithAction(_inner->clone(), _period);
	a->autorelease();
	return a;
}

void EaseElasticIn::update(float time)
{
    float newT = 0;
    if (time == 0 || time == 1)
    {
        newT = time;
    }
    else
    {
        float s = _period / 4;
        time = time - 1;
        newT = -powf(2, 10 * time) * sinf((time - s) * M_PI_X_2 / _period);
    }

    _inner->update(newT);
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
    EaseElasticOut *ret = new EaseElasticOut();
    if (ret)
    {
        if (ret->initWithAction(action, period))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

EaseElasticOut* EaseElasticOut::clone() const
{
	// no copy constructor
	auto a = new EaseElasticOut();
	a->initWithAction(_inner->clone(), _period);
	a->autorelease();
	return a;
}

void EaseElasticOut::update(float time)
{
    float newT = 0;
    if (time == 0 || time == 1)
    {
        newT = time;
    }
    else
    {
        float s = _period / 4;
        newT = powf(2, -10 * time) * sinf((time - s) * M_PI_X_2 / _period) + 1;
    }

    _inner->update(newT);
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
    EaseElasticInOut *ret = new EaseElasticInOut();
    if (ret)
    {
        if (ret->initWithAction(action, period))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

EaseElasticInOut* EaseElasticInOut::clone() const
{
	// no copy constructor
	auto a = new EaseElasticInOut();
	a->initWithAction(_inner->clone(), _period);
	a->autorelease();
	return a;
}

void EaseElasticInOut::update(float time)
{
    float newT = 0;
    if (time == 0 || time == 1)
    {
        newT = time;
    }
    else
    {
        time = time * 2;
        if ( _period == 0)
        {
            _period = 0.3f * 1.5f;
        }

        float s = _period / 4;

        time = time - 1;
        if (time < 0)
        {
            newT = -0.5f * powf(2, 10 * time) * sinf((time -s) * M_PI_X_2 / _period);
        }
        else
        {
            newT = powf(2, -10 * time) * sinf((time - s) * M_PI_X_2 / _period) * 0.5f + 1;
        }
    }

    _inner->update(newT);
}

EaseElasticInOut* EaseElasticInOut::reverse() const
{
    return EaseElasticInOut::create(_inner->reverse(), _period);
}

//
// EaseBounce
//

float EaseBounce::bounceTime(float time)
{
    if (time < 1 / 2.75)
    {
        return 7.5625f * time * time;
    } else 
    if (time < 2 / 2.75)
    {
        time -= 1.5f / 2.75f;
        return 7.5625f * time * time + 0.75f;
    } else
    if(time < 2.5 / 2.75)
    {
        time -= 2.25f / 2.75f;
        return 7.5625f * time * time + 0.9375f;
    }

    time -= 2.625f / 2.75f;
    return 7.5625f * time * time + 0.984375f;
}

//
// EaseBounceIn
//

EaseBounceIn* EaseBounceIn::create(ActionInterval* action)
{
    EaseBounceIn *ret = new EaseBounceIn();
    if (ret)
    {
        if (ret->initWithAction(action))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

EaseBounceIn* EaseBounceIn::clone() const
{
	// no copy constructor
	auto a = new EaseBounceIn();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

void EaseBounceIn::update(float time)
{
    float newT = 1 - bounceTime(1 - time);
    _inner->update(newT);
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
    EaseBounceOut *ret = new EaseBounceOut();
    if (ret)
    {
        if (ret->initWithAction(action))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

EaseBounceOut* EaseBounceOut::clone() const
{
	// no copy constructor
	auto a = new EaseBounceOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

void EaseBounceOut::update(float time)
{
    float newT = bounceTime(time);
    _inner->update(newT);
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
    EaseBounceInOut *ret = new EaseBounceInOut();
    if (ret)
    {
        if (ret->initWithAction(action))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

EaseBounceInOut* EaseBounceInOut::clone() const
{
	// no copy constructor
	auto a = new EaseBounceInOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

void EaseBounceInOut::update(float time)
{
    float newT = 0;
    if (time < 0.5f)
    {
        time = time * 2;
        newT = (1 - bounceTime(1 - time)) * 0.5f;
    }
    else
    {
        newT = bounceTime(time * 2 - 1) * 0.5f + 0.5f;
    }

    _inner->update(newT);
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
    EaseBackIn *ret = new EaseBackIn();
    if (ret)
    {
        if (ret->initWithAction(action))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

EaseBackIn* EaseBackIn::clone() const
{
	// no copy constructor	
	auto a = new EaseBackIn();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

void EaseBackIn::update(float time)
{
    float overshoot = 1.70158f;
    _inner->update(time * time * ((overshoot + 1) * time - overshoot));
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
    EaseBackOut *ret = new EaseBackOut();
    if (ret)
    {
        if (ret->initWithAction(action))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

EaseBackOut* EaseBackOut::clone() const
{
	// no copy constructor	
	auto a = new EaseBackOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

void EaseBackOut::update(float time)
{
    float overshoot = 1.70158f;

    time = time - 1;
    _inner->update(time * time * ((overshoot + 1) * time + overshoot) + 1);
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
    EaseBackInOut *ret = new EaseBackInOut();
    if (ret)
    {
        if (ret->initWithAction(action))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

EaseBackInOut* EaseBackInOut::clone() const
{
	// no copy constructor
	auto a = new EaseBackInOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

void EaseBackInOut::update(float time)
{
    float overshoot = 1.70158f * 1.525f;

    time = time * 2;
    if (time < 1)
    {
        _inner->update((time * time * ((overshoot + 1) * time - overshoot)) / 2);
    }
    else
    {
        time = time - 2;
        _inner->update((time * time * ((overshoot + 1) * time + overshoot)) / 2 + 1);
    }
}

EaseBackInOut* EaseBackInOut::reverse() const
{
    return EaseBackInOut::create(_inner->reverse());
}

NS_CC_END
