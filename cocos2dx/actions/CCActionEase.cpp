/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2009 Jason Booth

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
#include "cocoa/CCZone.h"

NS_CC_BEGIN

#ifndef M_PI_X_2
#define M_PI_X_2 (float)M_PI * 2.0f
#endif

//
// EaseAction
//

bool ActionEase::initWithAction(ActionInterval *pAction)
{
    CCAssert(pAction != NULL, "");

    if (ActionInterval::initWithDuration(pAction->getDuration()))
    {
        _inner = pAction;
        pAction->retain();

        return true;
    }

    return false;
}

ActionEase::~ActionEase(void)
{
    CC_SAFE_RELEASE(_inner);
}

void ActionEase::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);
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

bool EaseRateAction::initWithAction(ActionInterval *pAction, float fRate)
{
    if (ActionEase::initWithAction(pAction))
    {
        _rate = fRate;
        return true;
    }

    return false;
}

EaseRateAction::~EaseRateAction(void)
{
}

//
// EeseIn
//

EaseIn* EaseIn::create(ActionInterval *pAction, float fRate)
{
    EaseIn *pRet = new EaseIn();
    if (pRet)
    {
        if (pRet->initWithAction(pAction, fRate))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet;
}

EaseIn* EaseIn::clone() const
{
	// no copy constructor
	auto a = new EaseIn();
	a->initWithAction(_inner->clone(), _rate);
	a->autorelease();
	return a;
}

Object* EaseIn::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    EaseIn* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (EaseIn*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new EaseIn();
        pNewZone = new Zone(pCopy);
    }

    pCopy->initWithAction((ActionInterval*)(_inner->copy()->autorelease()), _rate);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
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
EaseOut* EaseOut::create(ActionInterval *pAction, float fRate)
{
    EaseOut *pRet = new EaseOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction, fRate))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet;   
}

EaseOut* EaseOut::clone() const
{
	// no copy constructor
	auto a = new EaseOut();
	a->initWithAction(_inner->clone(), _rate);
	a->autorelease();
	return a;
}

Object* EaseOut::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    EaseOut* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (EaseOut*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new EaseOut();
        pNewZone = new Zone(pCopy);
    }

    pCopy->initWithAction((ActionInterval*)(_inner->copy()->autorelease()), _rate);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
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
EaseInOut* EaseInOut::create(ActionInterval *pAction, float fRate)
{
    EaseInOut *pRet = new EaseInOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction, fRate))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

EaseInOut* EaseInOut::clone() const
{
	// no copy constructor
	auto a = new EaseInOut();
	a->initWithAction(_inner->clone(), _rate);
	a->autorelease();
	return a;
}

Object* EaseInOut::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    EaseInOut* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (EaseInOut*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new EaseInOut();
        pNewZone = new Zone(pCopy);
    }

    pCopy->initWithAction((ActionInterval*)(_inner->copy()->autorelease()), _rate);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
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
EaseExponentialIn* EaseExponentialIn::create(ActionInterval* pAction)
{
    EaseExponentialIn *pRet = new EaseExponentialIn();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet;    
}

EaseExponentialIn* EaseExponentialIn::clone() const
{
	// no copy constructor
	auto a = new EaseExponentialIn();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

Object* EaseExponentialIn::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    EaseExponentialIn* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (EaseExponentialIn*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new EaseExponentialIn();
        pNewZone = new Zone(pCopy);
    }

    pCopy->initWithAction((ActionInterval *)(_inner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
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
EaseExponentialOut* EaseExponentialOut::create(ActionInterval* pAction)
{
    EaseExponentialOut *pRet = new EaseExponentialOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

EaseExponentialOut* EaseExponentialOut::clone() const
{
	// no copy constructor
	auto a = new EaseExponentialOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

Object* EaseExponentialOut::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    EaseExponentialOut* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (EaseExponentialOut*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new EaseExponentialOut();
        pNewZone = new Zone(pCopy);
    }

    pCopy->initWithAction((ActionInterval *)(_inner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
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

EaseExponentialInOut* EaseExponentialInOut::create(ActionInterval *pAction)
{
    EaseExponentialInOut *pRet = new EaseExponentialInOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

EaseExponentialInOut* EaseExponentialInOut::clone() const
{
	// no copy constructor
	auto a = new EaseExponentialInOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

Object* EaseExponentialInOut::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    EaseExponentialInOut* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (EaseExponentialInOut*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new EaseExponentialInOut();
        pNewZone = new Zone(pCopy);
    }

    pCopy->initWithAction((ActionInterval *)(_inner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
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

EaseSineIn* EaseSineIn::create(ActionInterval* pAction)
{
    EaseSineIn *pRet = new EaseSineIn();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

EaseSineIn* EaseSineIn::clone() const
{
	// no copy constructor
	auto a = new EaseSineIn();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

Object* EaseSineIn::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    EaseSineIn* pCopy = NULL;
    if(pZone && pZone->_copyObject)
    {
        //in case of being called at sub class
        pCopy = (EaseSineIn*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new EaseSineIn();
        pNewZone = new Zone(pCopy);
    }

    pCopy->initWithAction((ActionInterval *)(_inner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
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

EaseSineOut* EaseSineOut::create(ActionInterval* pAction)
{
    EaseSineOut *pRet = new EaseSineOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

EaseSineOut* EaseSineOut::clone() const
{
	// no copy constructor
	auto a = new EaseSineOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

Object* EaseSineOut::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    EaseSineOut* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (EaseSineOut*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new EaseSineOut();
        pNewZone = new Zone(pCopy);
    }

    pCopy->initWithAction((ActionInterval *)(_inner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
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

EaseSineInOut* EaseSineInOut::create(ActionInterval* pAction)
{
    EaseSineInOut *pRet = new EaseSineInOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

EaseSineInOut* EaseSineInOut::clone() const
{
	// no copy constructor
	auto a = new EaseSineInOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

Object* EaseSineInOut::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    EaseSineInOut* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (EaseSineInOut*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new EaseSineInOut();
        pNewZone = new Zone(pCopy);
    }

    pCopy->initWithAction((ActionInterval *)(_inner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
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

bool EaseElastic::initWithAction(ActionInterval *pAction, float fPeriod/* = 0.3f*/)
{
    if (ActionEase::initWithAction(pAction))
    {
        _period = fPeriod;
        return true;
    }

    return false;
}

//
// EaseElasticIn
//

EaseElasticIn* EaseElasticIn::create(ActionInterval *pAction)
{
    return EaseElasticIn::create(pAction, 0.3f);
}

EaseElasticIn* EaseElasticIn::create(ActionInterval *pAction, float fPeriod/* = 0.3f*/)
{
    EaseElasticIn *pRet = new EaseElasticIn();
    if (pRet)
    {
        if (pRet->initWithAction(pAction, fPeriod))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

EaseElasticIn* EaseElasticIn::clone() const
{
	// no copy constructor
	auto a = new EaseElasticIn();
	a->initWithAction(_inner->clone(), _period);
	a->autorelease();
	return a;
}

Object* EaseElasticIn::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    EaseElasticIn* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (EaseElasticIn*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new EaseElasticIn();
        pNewZone = new Zone(pCopy);
    }

    pCopy->initWithAction((ActionInterval *)(_inner->copy()->autorelease()), _period);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
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

EaseElasticOut* EaseElasticOut::create(ActionInterval *pAction)
{
    return EaseElasticOut::create(pAction, 0.3f);
}

EaseElasticOut* EaseElasticOut::create(ActionInterval *pAction, float fPeriod/* = 0.3f*/)
{
    EaseElasticOut *pRet = new EaseElasticOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction, fPeriod))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

EaseElasticOut* EaseElasticOut::clone() const
{
	// no copy constructor
	auto a = new EaseElasticOut();
	a->initWithAction(_inner->clone(), _period);
	a->autorelease();
	return a;
}

Object *EaseElasticOut::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    EaseElasticOut* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (EaseElasticOut*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new EaseElasticOut();
        pNewZone = new Zone(pCopy);
    }

    pCopy->initWithAction((ActionInterval *)(_inner->copy()->autorelease()), _period);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
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

EaseElasticInOut* EaseElasticInOut::create(ActionInterval *pAction)
{
    return EaseElasticInOut::create(pAction, 0.3f);
}

EaseElasticInOut* EaseElasticInOut::create(ActionInterval *pAction, float fPeriod/* = 0.3f*/)
{
    EaseElasticInOut *pRet = new EaseElasticInOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction, fPeriod))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

EaseElasticInOut* EaseElasticInOut::clone() const
{
	// no copy constructor
	auto a = new EaseElasticInOut();
	a->initWithAction(_inner->clone(), _period);
	a->autorelease();
	return a;
}

Object* EaseElasticInOut::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    EaseElasticInOut* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (EaseElasticInOut*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new EaseElasticInOut();
        pNewZone = new Zone(pCopy);
    }

    pCopy->initWithAction((ActionInterval *)(_inner->copy()->autorelease()), _period);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;

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
        if (! _period)
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

EaseBounceIn* EaseBounceIn::create(ActionInterval* pAction)
{
    EaseBounceIn *pRet = new EaseBounceIn();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

EaseBounceIn* EaseBounceIn::clone() const
{
	// no copy constructor
	auto a = new EaseBounceIn();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

Object* EaseBounceIn::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    EaseBounceIn* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (EaseBounceIn*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new EaseBounceIn();
        pNewZone = new Zone(pCopy);
    }

    pCopy->initWithAction((ActionInterval *)(_inner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
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

EaseBounceOut* EaseBounceOut::create(ActionInterval* pAction)
{
    EaseBounceOut *pRet = new EaseBounceOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

EaseBounceOut* EaseBounceOut::clone() const
{
	// no copy constructor
	auto a = new EaseBounceOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

Object* EaseBounceOut::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    EaseBounceOut* pCopy = NULL;
    if(pZone && pZone->_copyObject)
    {
        //in case of being called at sub class
        pCopy = (EaseBounceOut*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new EaseBounceOut();
        pNewZone = new Zone(pCopy);
    }

    pCopy->initWithAction((ActionInterval *)(_inner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
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

EaseBounceInOut* EaseBounceInOut::create(ActionInterval* pAction)
{
    EaseBounceInOut *pRet = new EaseBounceInOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

EaseBounceInOut* EaseBounceInOut::clone() const
{
	// no copy constructor
	auto a = new EaseBounceInOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

Object* EaseBounceInOut::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    EaseBounceInOut* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (EaseBounceInOut*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new EaseBounceInOut();
        pNewZone = new Zone(pCopy);
    }

    pCopy->initWithAction((ActionInterval *)(_inner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
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

EaseBackIn* EaseBackIn::create(ActionInterval *pAction)
{
    EaseBackIn *pRet = new EaseBackIn();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet;
}

EaseBackIn* EaseBackIn::clone() const
{
	// no copy constructor	
	auto a = new EaseBackIn();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

Object* EaseBackIn::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    EaseBackIn* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (EaseBackIn*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new EaseBackIn();
        pNewZone = new Zone(pCopy);
    }

    pCopy->initWithAction((ActionInterval *)(_inner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
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

EaseBackOut* EaseBackOut::create(ActionInterval* pAction)
{
    EaseBackOut *pRet = new EaseBackOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet;
}

EaseBackOut* EaseBackOut::clone() const
{
	// no copy constructor	
	auto a = new EaseBackOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

Object* EaseBackOut::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    EaseBackOut* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (EaseBackOut*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new EaseBackOut();
        pNewZone = new Zone(pCopy);
    }

    pCopy->initWithAction((ActionInterval *)(_inner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
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

EaseBackInOut* EaseBackInOut::create(ActionInterval* pAction)
{
    EaseBackInOut *pRet = new EaseBackInOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet;
}

EaseBackInOut* EaseBackInOut::clone() const
{
	// no copy constructor
	auto a = new EaseBackInOut();
	a->initWithAction(_inner->clone());
	a->autorelease();
	return a;
}

Object* EaseBackInOut::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    EaseBackInOut* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (EaseBackInOut*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new EaseBackInOut();
        pNewZone = new Zone(pCopy);
    }

    pCopy->initWithAction((ActionInterval *)(_inner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
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
