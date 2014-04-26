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
    _inner->update(tweenfunc::backEaseInOut(time));
}

EaseBackInOut* EaseBackInOut::reverse() const
{
    return EaseBackInOut::create(_inner->reverse());
}




EaseBezierAction* EaseBezierAction::create(cocos2d::ActionInterval* action)
{
	EaseBezierAction *ret = new EaseBezierAction();
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
	auto a = new EaseBezierAction();
	a->initWithAction(_inner->clone());
	a->setBezierParamer(_p0,_p1,_p2,_p3);
	a->autorelease();
	return a;
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
	EaseQuadraticActionIn *ret = new EaseQuadraticActionIn();
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

EaseQuadraticActionIn* EaseQuadraticActionIn::clone() const
{
	// no copy constructor
	auto a = new EaseQuadraticActionIn();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
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
	EaseQuadraticActionOut *ret = new EaseQuadraticActionOut();
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

EaseQuadraticActionOut* EaseQuadraticActionOut::clone() const
{
	// no copy constructor
	auto a = new EaseQuadraticActionOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
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
	EaseQuadraticActionInOut *ret = new EaseQuadraticActionInOut();
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

EaseQuadraticActionInOut* EaseQuadraticActionInOut::clone() const
{
	// no copy constructor
	auto a = new EaseQuadraticActionInOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
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
	EaseQuarticActionIn *ret = new EaseQuarticActionIn();
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

EaseQuarticActionIn* EaseQuarticActionIn::clone() const
{
	// no copy constructor
	auto a = new EaseQuarticActionIn();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
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
	EaseQuarticActionOut *ret = new EaseQuarticActionOut();
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

EaseQuarticActionOut* EaseQuarticActionOut::clone() const
{
	// no copy constructor
	auto a = new EaseQuarticActionOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
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
	EaseQuarticActionInOut *ret = new EaseQuarticActionInOut();
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

EaseQuarticActionInOut* EaseQuarticActionInOut::clone() const
{
	// no copy constructor
	auto a = new EaseQuarticActionInOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
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
	EaseQuinticActionIn *ret = new EaseQuinticActionIn();
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

EaseQuinticActionIn* EaseQuinticActionIn::clone() const
{
	// no copy constructor
	auto a = new EaseQuinticActionIn();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
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
	EaseQuinticActionOut *ret = new EaseQuinticActionOut();
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

EaseQuinticActionOut* EaseQuinticActionOut::clone() const
{
	// no copy constructor
	auto a = new EaseQuinticActionOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
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
	EaseQuinticActionInOut *ret = new EaseQuinticActionInOut();
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

EaseQuinticActionInOut* EaseQuinticActionInOut::clone() const
{
	// no copy constructor
	auto a = new EaseQuinticActionInOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
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
	EaseCircleActionIn *ret = new EaseCircleActionIn();
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

EaseCircleActionIn* EaseCircleActionIn::clone() const
{
	// no copy constructor
	auto a = new EaseCircleActionIn();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
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
	EaseCircleActionOut *ret = new EaseCircleActionOut();
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

EaseCircleActionOut* EaseCircleActionOut::clone() const
{
	// no copy constructor
	auto a = new EaseCircleActionOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
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
	EaseCircleActionInOut *ret = new EaseCircleActionInOut();
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

EaseCircleActionInOut* EaseCircleActionInOut::clone() const
{
	// no copy constructor
	auto a = new EaseCircleActionInOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
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
	EaseCubicActionIn *ret = new EaseCubicActionIn();
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

EaseCubicActionIn* EaseCubicActionIn::clone() const
{
	// no copy constructor
	auto a = new EaseCubicActionIn();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
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
	EaseCubicActionOut *ret = new EaseCubicActionOut();
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

EaseCubicActionOut* EaseCubicActionOut::clone() const
{
	// no copy constructor
	auto a = new EaseCubicActionOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
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
	EaseCubicActionInOut *ret = new EaseCubicActionInOut();
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

EaseCubicActionInOut* EaseCubicActionInOut::clone() const
{
	// no copy constructor
	auto a = new EaseCubicActionInOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

void EaseCubicActionInOut::update(float time)
{
	_inner->update(tweenfunc::cubicEaseInOut(time));
}

EaseCubicActionInOut* EaseCubicActionInOut::reverse() const
{
	return EaseCubicActionInOut::create(_inner->reverse());
}

NS_CC_END
