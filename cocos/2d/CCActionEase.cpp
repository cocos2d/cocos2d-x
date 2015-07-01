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
// EaseTemplate
//

template<float(*F)(float), float(*I)(float)>
EaseTemplate<F,I>* EaseTemplate<F,I>::create(cocos2d::ActionInterval *action)
{
  EaseTemplate<F,I> *ease = new (std::nothrow) EaseTemplate<F,I>();
  if (ease)
  {
    if (ease->initWithAction(action))
      ease->autorelease();
    else
      CC_SAFE_RELEASE_NULL(ease);
  }
  return ease;
}

template<float(*F)(float), float(*I)(float)>
ActionEase* EaseTemplate<F,I>::clone() const
{
  auto a = new (std::nothrow) EaseTemplate<F,I>();
  a->initWithAction(_inner->clone());
  a->autorelease();
  return a;
}

//
// EaseRateTemplate<F,I>
//

template<float(*F)(float,float), float(*I)(float,float)>
EaseRateTemplate<F,I>* EaseRateTemplate<F,I>::create(ActionInterval* action, float rate)
{
  EaseRateTemplate<F,I> *ease = new (std::nothrow) EaseRateTemplate<F,I>();
  if (action)
  {
    if (ease->initWithAction(action, rate))
      ease->autorelease();
    else
      CC_SAFE_RELEASE_NULL(ease);
  }

  return ease;
}

template<float(*F)(float,float), float(*I)(float,float)>
EaseRateAction* EaseRateTemplate<F,I>::clone() const
{
  auto a = new EaseRateTemplate<F,I>();
  a->initWithAction(_inner->clone(), _rate);
  a->autorelease();
  return a;
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
// EaseElastic Template
//

template<float(*F)(float,float), float(*I)(float,float)>
EaseElasticTemplate<F,I>* EaseElasticTemplate<F,I>::create(ActionInterval* action, float period)
{
  EaseElasticTemplate<F,I> *ease = new (std::nothrow) EaseElasticTemplate<F,I>();
  if (action)
  {
    if (ease->initWithAction(action, period))
      ease->autorelease();
    else
      CC_SAFE_RELEASE_NULL(ease);
  }

  return ease;
}

template<float(*F)(float,float), float(*I)(float,float)>
EaseElastic* EaseElasticTemplate<F,I>::clone() const
{
  auto a = new EaseElasticTemplate<F,I>();
  a->initWithAction(_inner->clone(), _period);
  a->autorelease();
  return a;
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

NS_CC_END
