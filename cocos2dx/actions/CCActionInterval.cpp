/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011 Zynga Inc.
 
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

#include "CCActionInterval.h"
#include "sprite_nodes/CCSprite.h"
#include "base_nodes/CCNode.h"
#include "support/CCPointExtension.h"
#include "CCStdC.h"
#include "CCActionInstant.h"
#include "cocoa/CCZone.h"
#include <stdarg.h>

NS_CC_BEGIN

// Extra action for making a CCSequence or CCSpawn when only adding one action to it.
class ExtraAction : public CCFiniteTimeAction
{
public:
    static ExtraAction* create();
    virtual ExtraAction* clone() const;
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual ExtraAction* reverse(void) const;
    virtual void update(float time);
    virtual void step(float dt);
};

ExtraAction* ExtraAction::create()
{
    ExtraAction* pRet = new ExtraAction();
    if (pRet)
    {
        pRet->autorelease();
    }
    return pRet;
}
ExtraAction* ExtraAction::clone(void) const
{
	// no copy constructor
	auto a = new ExtraAction();
	a->autorelease();
	return a;
}

CCObject* ExtraAction::copyWithZone(CCZone* pZone)
{
    CC_UNUSED_PARAM(pZone);
    ExtraAction* pRet = new ExtraAction();
    return pRet;
}

ExtraAction* ExtraAction::reverse(void) const
{
    return ExtraAction::create();
}

void ExtraAction::update(float time)
{
    CC_UNUSED_PARAM(time);
}

void ExtraAction::step(float dt)
{
    CC_UNUSED_PARAM(dt);
}

//
// IntervalAction
//

bool CCActionInterval::initWithDuration(float d)
{
    _duration = d;

    // prevent division by 0
    // This comparison could be in step:, but it might decrease the performance
    // by 3% in heavy based action games.
    if (_duration == 0)
    {
        _duration = FLT_EPSILON;
    }

    _elapsed = 0;
    _firstTick = true;

    return true;
}

bool CCActionInterval::isDone(void)
{
    return _elapsed >= _duration;
}

void CCActionInterval::step(float dt)
{
    if (_firstTick)
    {
        _firstTick = false;
        _elapsed = 0;
    }
    else
    {
        _elapsed += dt;
    }
    
    this->update(MAX (0,                                  // needed for rewind. elapsed could be negative
                      MIN(1, _elapsed /
                          MAX(_duration, FLT_EPSILON)   // division by 0
                          )
                      )
                 );
}

void CCActionInterval::setAmplitudeRate(float amp)
{
    CC_UNUSED_PARAM(amp);
    // Abstract class needs implementation
    CCAssert(0, "");
}

float CCActionInterval::getAmplitudeRate(void)
{
    // Abstract class needs implementation
    CCAssert(0, "");

    return 0;
}

void CCActionInterval::startWithTarget(CCNode *pTarget)
{
    CCFiniteTimeAction::startWithTarget(pTarget);
    _elapsed = 0.0f;
    _firstTick = true;
}

//
// Sequence
//

CCSequence* CCSequence::createWithTwoActions(CCFiniteTimeAction *pActionOne, CCFiniteTimeAction *pActionTwo)
{
    CCSequence *pSequence = new CCSequence();
    pSequence->initWithTwoActions(pActionOne, pActionTwo);
    pSequence->autorelease();

    return pSequence;
}

CCSequence* CCSequence::create(CCFiniteTimeAction *pAction1, ...)
{
    va_list params;
    va_start(params, pAction1);

    CCSequence *pRet = CCSequence::createWithVariableList(pAction1, params);

    va_end(params);
    
    return pRet;
}

CCSequence* CCSequence::createWithVariableList(CCFiniteTimeAction *pAction1, va_list args)
{
    CCFiniteTimeAction *pNow;
    CCFiniteTimeAction *pPrev = pAction1;
    bool bOneAction = true;

    while (pAction1)
    {
        pNow = va_arg(args, CCFiniteTimeAction*);
        if (pNow)
        {
            pPrev = createWithTwoActions(pPrev, pNow);
            bOneAction = false;
        }
        else
        {
            // If only one action is added to CCSequence, make up a CCSequence by adding a simplest finite time action.
            if (bOneAction)
            {
                pPrev = createWithTwoActions(pPrev, ExtraAction::create());
            }
            break;
        }
    }
    
    return ((CCSequence*)pPrev);
}

CCSequence* CCSequence::create(CCArray* arrayOfActions)
{
    CCSequence* pRet = NULL;
    do 
    {
        unsigned  int count = arrayOfActions->count();
        CC_BREAK_IF(count == 0);

        CCFiniteTimeAction* prev = (CCFiniteTimeAction*)arrayOfActions->objectAtIndex(0);

        if (count > 1)
        {
            for (unsigned int i = 1; i < count; ++i)
            {
                prev = createWithTwoActions(prev, (CCFiniteTimeAction*)arrayOfActions->objectAtIndex(i));
            }
        }
        else
        {
            // If only one action is added to CCSequence, make up a CCSequence by adding a simplest finite time action.
            prev = createWithTwoActions(prev, ExtraAction::create());
        }
        pRet = (CCSequence*)prev;
    }while (0);
    return pRet;
}

bool CCSequence::initWithTwoActions(CCFiniteTimeAction *pActionOne, CCFiniteTimeAction *pActionTwo)
{
    CCAssert(pActionOne != NULL, "");
    CCAssert(pActionTwo != NULL, "");

    float d = pActionOne->getDuration() + pActionTwo->getDuration();
    CCActionInterval::initWithDuration(d);

    _actions[0] = pActionOne;
    pActionOne->retain();

    _actions[1] = pActionTwo;
    pActionTwo->retain();

    return true;
}

CCSequence* CCSequence::clone(void) const
{
	// no copy constructor
	auto a = new CCSequence();
    a->initWithTwoActions((CCFiniteTimeAction*)(_actions[0]->clone()),
							  (CCFiniteTimeAction*)(_actions[1]->clone())
						  );
	a->autorelease();
	return a;
}

CCObject* CCSequence::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCSequence* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCSequence*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCSequence();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithTwoActions(_actions[0]->clone(), _actions[1]->clone());

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

CCSequence::~CCSequence(void)
{
    CC_SAFE_RELEASE(_actions[0]);
    CC_SAFE_RELEASE(_actions[1]);
}

void CCSequence::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    _split = _actions[0]->getDuration() / _duration;
    _last = -1;
}

void CCSequence::stop(void)
{
    // Issue #1305
    if( _last != - 1)
    {
        _actions[_last]->stop();
    }

    CCActionInterval::stop();
}

void CCSequence::update(float t)
{
    int found = 0;
    float new_t = 0.0f;

    if( t < _split ) {
        // action[0]
        found = 0;
        if( _split != 0 )
            new_t = t / _split;
        else
            new_t = 1;

    } else {
        // action[1]
        found = 1;
        if ( _split == 1 )
            new_t = 1;
        else
            new_t = (t-_split) / (1 - _split );
    }

    if ( found==1 ) {

        if( _last == -1 ) {
            // action[0] was skipped, execute it.
            _actions[0]->startWithTarget(_target);
            _actions[0]->update(1.0f);
            _actions[0]->stop();
        }
        else if( _last == 0 )
        {
            // switching to action 1. stop action 0.
            _actions[0]->update(1.0f);
            _actions[0]->stop();
        }
    }
	else if(found==0 && _last==1 )
	{
		// Reverse mode ?
		// XXX: Bug. this case doesn't contemplate when _last==-1, found=0 and in "reverse mode"
		// since it will require a hack to know if an action is on reverse mode or not.
		// "step" should be overriden, and the "reverseMode" value propagated to inner Sequences.
		_actions[1]->update(0);
		_actions[1]->stop();
	}
    // Last action found and it is done.
    if( found == _last && _actions[found]->isDone() )
    {
        return;
    }

    // Last action found and it is done
    if( found != _last )
    {
        _actions[found]->startWithTarget(_target);
    }

    _actions[found]->update(new_t);
    _last = found;
}

CCSequence* CCSequence::reverse() const
{
    return CCSequence::createWithTwoActions(_actions[1]->reverse(), _actions[0]->reverse());
}

//
// Repeat
//

CCRepeat* CCRepeat::create(CCFiniteTimeAction *pAction, unsigned int times)
{
    CCRepeat* pRepeat = new CCRepeat();
    pRepeat->initWithAction(pAction, times);
    pRepeat->autorelease();

    return pRepeat;
}

bool CCRepeat::initWithAction(CCFiniteTimeAction *pAction, unsigned int times)
{
    float d = pAction->getDuration() * times;

    if (CCActionInterval::initWithDuration(d))
    {
        _times = times;
        _innerAction = pAction;
        pAction->retain();

        _actionInstant = dynamic_cast<CCActionInstant*>(pAction) ? true : false;
        //an instant action needs to be executed one time less in the update method since it uses startWithTarget to execute the action
        if (_actionInstant) 
        {
            _times -=1;
        }
        _total = 0;

        return true;
    }

    return false;
}

CCRepeat* CCRepeat::clone(void) const
{
	// no copy constructor
	auto a = new CCRepeat();
	a->initWithAction((CCFiniteTimeAction*)_innerAction->clone(), _times );
	a->autorelease();
	return a;
}


CCObject* CCRepeat::copyWithZone(CCZone *pZone)
{
    
    CCZone* pNewZone = NULL;
    CCRepeat* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCRepeat*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCRepeat();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithAction(_innerAction->clone(), _times);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

CCRepeat::~CCRepeat(void)
{
    CC_SAFE_RELEASE(_innerAction);
}

void CCRepeat::startWithTarget(CCNode *pTarget)
{
    _total = 0;
    _nextDt = _innerAction->getDuration()/_duration;
    CCActionInterval::startWithTarget(pTarget);
    _innerAction->startWithTarget(pTarget);
}

void CCRepeat::stop(void)
{
    _innerAction->stop();
    CCActionInterval::stop();
}

// issue #80. Instead of hooking step:, hook update: since it can be called by any 
// container action like CCRepeat, CCSequence, CCEase, etc..
void CCRepeat::update(float dt)
{
    if (dt >= _nextDt)
    {
        while (dt > _nextDt && _total < _times)
        {

            _innerAction->update(1.0f);
            _total++;

            _innerAction->stop();
            _innerAction->startWithTarget(_target);
            _nextDt += _innerAction->getDuration()/_duration;
        }

        // fix for issue #1288, incorrect end value of repeat
        if(dt >= 1.0f && _total < _times) 
        {
            _total++;
        }

        // don't set an instant action back or update it, it has no use because it has no duration
        if (!_actionInstant)
        {
            if (_total == _times)
            {
                _innerAction->update(1);
                _innerAction->stop();
            }
            else
            {
                // issue #390 prevent jerk, use right update
                _innerAction->update(dt - (_nextDt - _innerAction->getDuration()/_duration));
            }
        }
    }
    else
    {
        _innerAction->update(fmodf(dt * _times,1.0f));
    }
}

bool CCRepeat::isDone(void)
{
    return _total == _times;
}

CCRepeat* CCRepeat::reverse() const
{
    return CCRepeat::create(_innerAction->reverse(), _times);
}

//
// RepeatForever
//
CCRepeatForever::~CCRepeatForever()
{
    CC_SAFE_RELEASE(_innerAction);
}

CCRepeatForever *CCRepeatForever::create(CCActionInterval *pAction)
{
    CCRepeatForever *pRet = new CCRepeatForever();
    if (pRet && pRet->initWithAction(pAction))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCRepeatForever::initWithAction(CCActionInterval *pAction)
{
    CCAssert(pAction != NULL, "");
    pAction->retain();
    _innerAction = pAction;
    return true;
}

CCRepeatForever *CCRepeatForever::clone(void) const
{
	// no copy constructor	
	auto a = new CCRepeatForever();
	a->initWithAction((CCActionInterval*)_innerAction->clone());
	a->autorelease();
	return a;
}

CCObject* CCRepeatForever::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCRepeatForever* pRet = NULL;
    if(pZone && pZone->_copyObject) //in case of being called at sub class
    {
        pRet = (CCRepeatForever*)(pZone->_copyObject);
    }
    else
    {
        pRet = new CCRepeatForever();
        pZone = pNewZone = new CCZone(pRet);
    }
    CCActionInterval::copyWithZone(pZone);
    // win32 : use the _other's copy object.
    pRet->initWithAction(_innerAction->clone());
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCRepeatForever::startWithTarget(CCNode* pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    _innerAction->startWithTarget(pTarget);
}

void CCRepeatForever::step(float dt)
{
    _innerAction->step(dt);
    if (_innerAction->isDone())
    {
        float diff = _innerAction->getElapsed() - _innerAction->getDuration();
        _innerAction->startWithTarget(_target);
        // to prevent jerk. issue #390, 1247
        _innerAction->step(0.0f);
        _innerAction->step(diff);
    }
}

bool CCRepeatForever::isDone()
{
    return false;
}

CCRepeatForever *CCRepeatForever::reverse() const
{
    return CCRepeatForever::create(_innerAction->reverse());
}

//
// Spawn
//

CCSpawn* CCSpawn::create(CCFiniteTimeAction *pAction1, ...)
{
    va_list params;
    va_start(params, pAction1);

    CCSpawn *pRet = CCSpawn::createWithVariableList(pAction1, params);

    va_end(params);
    
    return pRet;
}

CCSpawn* CCSpawn::createWithVariableList(CCFiniteTimeAction *pAction1, va_list args)
{
    CCFiniteTimeAction *pNow;
    CCFiniteTimeAction *pPrev = pAction1;
    bool bOneAction = true;

    while (pAction1)
    {
        pNow = va_arg(args, CCFiniteTimeAction*);
        if (pNow)
        {
            pPrev = createWithTwoActions(pPrev, pNow);
            bOneAction = false;
        }
        else
        {
            // If only one action is added to CCSpawn, make up a CCSpawn by adding a simplest finite time action.
            if (bOneAction)
            {
                pPrev = createWithTwoActions(pPrev, ExtraAction::create());
            }
            break;
        }
    }

    return ((CCSpawn*)pPrev);
}

CCSpawn* CCSpawn::create(CCArray *arrayOfActions)
{
    CCSpawn* pRet = NULL;
    do 
    {
        unsigned  int count = arrayOfActions->count();
        CC_BREAK_IF(count == 0);
        CCFiniteTimeAction* prev = (CCFiniteTimeAction*)arrayOfActions->objectAtIndex(0);
        if (count > 1)
        {
            for (unsigned int i = 1; i < arrayOfActions->count(); ++i)
            {
                prev = createWithTwoActions(prev, (CCFiniteTimeAction*)arrayOfActions->objectAtIndex(i));
            }
        }
        else
        {
            // If only one action is added to CCSpawn, make up a CCSpawn by adding a simplest finite time action.
            prev = createWithTwoActions(prev, ExtraAction::create());
        }
        pRet = (CCSpawn*)prev;
    }while (0);

    return pRet;
}

CCSpawn* CCSpawn::createWithTwoActions(CCFiniteTimeAction *pAction1, CCFiniteTimeAction *pAction2)
{
    CCSpawn *pSpawn = new CCSpawn();
    pSpawn->initWithTwoActions(pAction1, pAction2);
    pSpawn->autorelease();

    return pSpawn;
}

bool CCSpawn:: initWithTwoActions(CCFiniteTimeAction *pAction1, CCFiniteTimeAction *pAction2)
{
    CCAssert(pAction1 != NULL, "");
    CCAssert(pAction2 != NULL, "");

    bool bRet = false;

    float d1 = pAction1->getDuration();
    float d2 = pAction2->getDuration();

    if (CCActionInterval::initWithDuration(MAX(d1, d2)))
    {
        _one = pAction1;
        _two = pAction2;

        if (d1 > d2)
        {
            _two = CCSequence::createWithTwoActions(pAction2, CCDelayTime::create(d1 - d2));
        } 
        else if (d1 < d2)
        {
            _one = CCSequence::createWithTwoActions(pAction1, CCDelayTime::create(d2 - d1));
        }

        _one->retain();
        _two->retain();

        bRet = true;
    }

    
    return bRet;
}

CCSpawn* CCSpawn::clone(void) const
{
	// no copy constructor	
	auto a = new CCSpawn();
    a->initWithTwoActions(_one->clone(), _two->clone());

	a->autorelease();
	return a;
}

CCObject* CCSpawn::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCSpawn* pCopy = NULL;

    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCSpawn*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCSpawn();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithTwoActions(_one->clone(), _two->clone());

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

CCSpawn::~CCSpawn(void)
{
    CC_SAFE_RELEASE(_one);
    CC_SAFE_RELEASE(_two);
}

void CCSpawn::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    _one->startWithTarget(pTarget);
    _two->startWithTarget(pTarget);
}

void CCSpawn::stop(void)
{
    _one->stop();
    _two->stop();
    CCActionInterval::stop();
}

void CCSpawn::update(float time)
{
    if (_one)
    {
        _one->update(time);
    }
    if (_two)
    {
        _two->update(time);
    }
}

CCSpawn* CCSpawn::reverse() const
{
    return CCSpawn::createWithTwoActions(_one->reverse(), _two->reverse());
}

//
// RotateTo
//

CCRotateTo* CCRotateTo::create(float fDuration, float fDeltaAngle)
{
    CCRotateTo* pRotateTo = new CCRotateTo();
    pRotateTo->initWithDuration(fDuration, fDeltaAngle);
    pRotateTo->autorelease();

    return pRotateTo;
}

bool CCRotateTo::initWithDuration(float fDuration, float fDeltaAngle)
{
    if (CCActionInterval::initWithDuration(fDuration))
    {
        _dstAngleX = _dstAngleY = fDeltaAngle;
        return true;
    }

    return false;
}

CCRotateTo* CCRotateTo::create(float fDuration, float fDeltaAngleX, float fDeltaAngleY)
{
    CCRotateTo* pRotateTo = new CCRotateTo();
    pRotateTo->initWithDuration(fDuration, fDeltaAngleX, fDeltaAngleY);
    pRotateTo->autorelease();
    
    return pRotateTo;
}

bool CCRotateTo::initWithDuration(float fDuration, float fDeltaAngleX, float fDeltaAngleY)
{
    if (CCActionInterval::initWithDuration(fDuration))
    {
        _dstAngleX = fDeltaAngleX;
        _dstAngleY = fDeltaAngleY;
        
        return true;
    }
    
    return false;
}

CCRotateTo* CCRotateTo::clone(void) const
{
	// no copy constructor
	auto a = new CCRotateTo();
	a->initWithDuration(_duration, _dstAngleX, _dstAngleY);
	a->autorelease();
	return a;
}

CCObject* CCRotateTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCRotateTo* pCopy = NULL;
    if(pZone && pZone->_copyObject)
    {
        //in case of being called at sub class
        pCopy = (CCRotateTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCRotateTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _dstAngleX, _dstAngleY);

    //Action *copy = [[[self class] allocWithZone: zone] initWithDuration:[self duration] angle: angle];
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCRotateTo::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    
    // Calculate X
    _startAngleX = pTarget->getRotationX();
    if (_startAngleX > 0)
    {
        _startAngleX = fmodf(_startAngleX, 360.0f);
    }
    else
    {
        _startAngleX = fmodf(_startAngleX, -360.0f);
    }

    _diffAngleX = _dstAngleX - _startAngleX;
    if (_diffAngleX > 180)
    {
        _diffAngleX -= 360;
    }
    if (_diffAngleX < -180)
    {
        _diffAngleX += 360;
    }
    
    //Calculate Y: It's duplicated from calculating X since the rotation wrap should be the same
    _startAngleY = _target->getRotationY();

    if (_startAngleY > 0)
    {
        _startAngleY = fmodf(_startAngleY, 360.0f);
    }
    else
    {
        _startAngleY = fmodf(_startAngleY, -360.0f);
    }

    _diffAngleY = _dstAngleY - _startAngleY;
    if (_diffAngleY > 180)
    {
        _diffAngleY -= 360;
    }

    if (_diffAngleY < -180)
    {
        _diffAngleY += 360;
    }
}

void CCRotateTo::update(float time)
{
    if (_target)
    {
        _target->setRotationX(_startAngleX + _diffAngleX * time);
        _target->setRotationY(_startAngleY + _diffAngleY * time);
    }
}

CCRotateTo *CCRotateTo::reverse() const
{
	CCAssert(false, "RotateTo doesn't support the 'reverse' method");
	return nullptr;
}

//
// RotateBy
//

CCRotateBy* CCRotateBy::create(float fDuration, float fDeltaAngle)
{
    CCRotateBy *pRotateBy = new CCRotateBy();
    pRotateBy->initWithDuration(fDuration, fDeltaAngle);
    pRotateBy->autorelease();

    return pRotateBy;
}

bool CCRotateBy::initWithDuration(float fDuration, float fDeltaAngle)
{
    if (CCActionInterval::initWithDuration(fDuration))
    {
        _angleX = _angleY = fDeltaAngle;
        return true;
    }

    return false;
}

CCRotateBy* CCRotateBy::create(float fDuration, float fDeltaAngleX, float fDeltaAngleY)
{
    CCRotateBy *pRotateBy = new CCRotateBy();
    pRotateBy->initWithDuration(fDuration, fDeltaAngleX, fDeltaAngleY);
    pRotateBy->autorelease();
    
    return pRotateBy;
}

bool CCRotateBy::initWithDuration(float fDuration, float fDeltaAngleX, float fDeltaAngleY)
{
    if (CCActionInterval::initWithDuration(fDuration))
    {
        _angleX = fDeltaAngleX;
        _angleY = fDeltaAngleY;
        return true;
    }
    
    return false;
}

CCRotateBy* CCRotateBy::clone(void) const
{
	// no copy constructor
	auto a = new CCRotateBy();
    a->initWithDuration(_duration, _angleX, _angleY);
	a->autorelease();
	return a;
}

CCObject* CCRotateBy::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCRotateBy* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCRotateBy*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCRotateBy();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _angleX, _angleY);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCRotateBy::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    _startAngleX = pTarget->getRotationX();
    _startAngleY = pTarget->getRotationY();
}

void CCRotateBy::update(float time)
{
    // XXX: shall I add % 360
    if (_target)
    {
        _target->setRotationX(_startAngleX + _angleX * time);
        _target->setRotationY(_startAngleY + _angleY * time);
    }
}

CCRotateBy* CCRotateBy::reverse() const
{
    return CCRotateBy::create(_duration, -_angleX, -_angleY);
}

//
// MoveBy
//

CCMoveBy* CCMoveBy::create(float duration, const CCPoint& deltaPosition)
{
    CCMoveBy *pRet = new CCMoveBy();
    pRet->initWithDuration(duration, deltaPosition);
    pRet->autorelease();

    return pRet;
}

bool CCMoveBy::initWithDuration(float duration, const CCPoint& deltaPosition)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        _positionDelta = deltaPosition;
        return true;
    }

    return false;
}

CCMoveBy* CCMoveBy::clone(void) const
{
	// no copy constructor
	auto a = new CCMoveBy();
    a->initWithDuration(_duration, _positionDelta);
	a->autorelease();
	return a;
}

CCObject* CCMoveBy::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCMoveBy* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCMoveBy*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCMoveBy();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _positionDelta);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCMoveBy::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    _previousPosition = _startPosition = pTarget->getPosition();
}

CCMoveBy* CCMoveBy::reverse() const
{
    return CCMoveBy::create(_duration, ccp( -_positionDelta.x, -_positionDelta.y));
}


void CCMoveBy::update(float t)
{
    if (_target)
    {
#if CC_ENABLE_STACKABLE_ACTIONS
        CCPoint currentPos = _target->getPosition();
        CCPoint diff = ccpSub(currentPos, _previousPosition);
        _startPosition = ccpAdd( _startPosition, diff);
        CCPoint newPos =  ccpAdd( _startPosition, ccpMult(_positionDelta, t) );
        _target->setPosition(newPos);
        _previousPosition = newPos;
#else
        _target->setPosition(ccpAdd( _startPosition, ccpMult(_positionDelta, t)));
#endif // CC_ENABLE_STACKABLE_ACTIONS
    }
}

//
// MoveTo
//

CCMoveTo* CCMoveTo::create(float duration, const CCPoint& position)
{
    CCMoveTo *pRet = new CCMoveTo();
    pRet->initWithDuration(duration, position);
    pRet->autorelease();

    return pRet;
}

bool CCMoveTo::initWithDuration(float duration, const CCPoint& position)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        _endPosition = position;
        return true;
    }

    return false;
}

CCMoveTo* CCMoveTo::clone(void) const
{
	// no copy constructor
	auto a = new CCMoveTo();
    a->initWithDuration(_duration, _endPosition);
	a->autorelease();
	return a;
}

CCObject* CCMoveTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCMoveTo* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCMoveTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCMoveTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCMoveBy::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _endPosition);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCMoveTo::startWithTarget(CCNode *pTarget)
{
    CCMoveBy::startWithTarget(pTarget);
    _positionDelta = ccpSub( _endPosition, pTarget->getPosition() );
}


//
// CCSkewTo
//
CCSkewTo* CCSkewTo::create(float t, float sx, float sy)
{
    CCSkewTo *pSkewTo = new CCSkewTo();
    if (pSkewTo)
    {
        if (pSkewTo->initWithDuration(t, sx, sy))
        {
            pSkewTo->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(pSkewTo);
        }
    }

    return pSkewTo;
}

bool CCSkewTo::initWithDuration(float t, float sx, float sy)
{
    bool bRet = false;

    if (CCActionInterval::initWithDuration(t))
    {
        _endSkewX = sx;
        _endSkewY = sy;

        bRet = true;
    }

    return bRet;
}

CCSkewTo* CCSkewTo::clone(void) const
{
	// no copy constructor
	auto a = new CCSkewTo();
	a->initWithDuration(_duration, _endSkewX, _endSkewY);
	a->autorelease();
	return a;
}

CCSkewTo* CCSkewTo::reverse() const
{
	CCAssert(false, "reverse() not supported in CCSkewTo");
	return nullptr;
}

CCObject* CCSkewTo::copyWithZone(CCZone* pZone)
{
    CCZone* pNewZone = NULL;
    CCSkewTo* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCSkewTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCSkewTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _endSkewX, _endSkewY);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCSkewTo::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);

    _startSkewX = pTarget->getSkewX();

    if (_startSkewX > 0)
    {
        _startSkewX = fmodf(_startSkewX, 180.f);
    }
    else
    {
        _startSkewX = fmodf(_startSkewX, -180.f);
    }

    _deltaX = _endSkewX - _startSkewX;

    if (_deltaX > 180)
    {
        _deltaX -= 360;
    }
    if (_deltaX < -180)
    {
        _deltaX += 360;
    }

    _startSkewY = pTarget->getSkewY();

    if (_startSkewY > 0)
    {
        _startSkewY = fmodf(_startSkewY, 360.f);
    }
    else
    {
        _startSkewY = fmodf(_startSkewY, -360.f);
    }

    _deltaY = _endSkewY - _startSkewY;

    if (_deltaY > 180)
    {
        _deltaY -= 360;
    }
    if (_deltaY < -180)
    {
        _deltaY += 360;
    }
}

void CCSkewTo::update(float t)
{
    _target->setSkewX(_startSkewX + _deltaX * t);
    _target->setSkewY(_startSkewY + _deltaY * t);
}

CCSkewTo::CCSkewTo()
: _skewX(0.0)
, _skewY(0.0)
, _startSkewX(0.0)
, _startSkewY(0.0)
, _endSkewX(0.0)
, _endSkewY(0.0)
, _deltaX(0.0)
, _deltaY(0.0)
{
}

//
// CCSkewBy
//
CCSkewBy* CCSkewBy::create(float t, float sx, float sy)
{
    CCSkewBy *pSkewBy = new CCSkewBy();
    if (pSkewBy)
    {
        if (pSkewBy->initWithDuration(t, sx, sy))
        {
            pSkewBy->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(pSkewBy);
        }
    }

    return pSkewBy;
}

CCSkewBy * CCSkewBy::clone() const
{
	// no copy constructor
	auto a = new CCSkewBy();
	a->initWithDuration(_duration, _skewX, _skewY);
	a->autorelease();
	return a;
}

bool CCSkewBy::initWithDuration(float t, float deltaSkewX, float deltaSkewY)
{
    bool bRet = false;

    if (CCSkewTo::initWithDuration(t, deltaSkewX, deltaSkewY))
    {
        _skewX = deltaSkewX;
        _skewY = deltaSkewY;

        bRet = true;
    }

    return bRet;
}

void CCSkewBy::startWithTarget(CCNode *pTarget)
{
    CCSkewTo::startWithTarget(pTarget);
    _deltaX = _skewX;
    _deltaY = _skewY;
    _endSkewX = _startSkewX + _deltaX;
    _endSkewY = _startSkewY + _deltaY;
}

CCSkewBy* CCSkewBy::reverse() const
{
    return CCSkewBy::create(_duration, -_skewX, -_skewY);
}

//
// JumpBy
//

CCJumpBy* CCJumpBy::create(float duration, const CCPoint& position, float height, unsigned int jumps)
{
    CCJumpBy *pJumpBy = new CCJumpBy();
    pJumpBy->initWithDuration(duration, position, height, jumps);
    pJumpBy->autorelease();

    return pJumpBy;
}

bool CCJumpBy::initWithDuration(float duration, const CCPoint& position, float height, unsigned int jumps)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        _delta = position;
        _height = height;
        _jumps = jumps;

        return true;
    }

    return false;
}

CCJumpBy* CCJumpBy::clone(void) const
{
	// no copy constructor
	auto a = new CCJumpBy();
	a->initWithDuration(_duration, _delta, _height, _jumps);
	a->autorelease();
	return a;
}

CCObject* CCJumpBy::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCJumpBy* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCJumpBy*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCJumpBy();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _delta, _height, _jumps);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCJumpBy::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    _previousPos = _startPosition = pTarget->getPosition();
}

void CCJumpBy::update(float t)
{
    // parabolic jump (since v0.8.2)
    if (_target)
    {
        float frac = fmodf( t * _jumps, 1.0f );
        float y = _height * 4 * frac * (1 - frac);
        y += _delta.y * t;

        float x = _delta.x * t;
#if CC_ENABLE_STACKABLE_ACTIONS
        CCPoint currentPos = _target->getPosition();

        CCPoint diff = ccpSub( currentPos, _previousPos );
        _startPosition = ccpAdd( diff, _startPosition);

        CCPoint newPos = ccpAdd( _startPosition, ccp(x,y));
        _target->setPosition(newPos);

        _previousPos = newPos;
#else
        _target->setPosition(ccpAdd( _startPosition, ccp(x,y)));
#endif // !CC_ENABLE_STACKABLE_ACTIONS
    }
}

CCJumpBy* CCJumpBy::reverse() const
{
    return CCJumpBy::create(_duration, ccp(-_delta.x, -_delta.y),
        _height, _jumps);
}

//
// JumpTo
//

CCJumpTo* CCJumpTo::create(float duration, const CCPoint& position, float height, int jumps)
{
    CCJumpTo *pJumpTo = new CCJumpTo();
    pJumpTo->initWithDuration(duration, position, height, jumps);
    pJumpTo->autorelease();

    return pJumpTo;
}

CCJumpTo* CCJumpTo::clone(void) const
{
	// no copy constructor
	auto a = new CCJumpTo();
    a->initWithDuration(_duration, _delta, _height, _jumps);
	a->autorelease();
	return a;
}

CCJumpTo* CCJumpTo::reverse() const
{
	CCAssert(false, "reverse() not supported in CCJumpTo");
	return nullptr;
}

CCObject* CCJumpTo::copyWithZone(CCZone* pZone)
{
    CCZone* pNewZone = NULL;
    CCJumpTo* pCopy = NULL;
    if(pZone && pZone->_copyObject)
    {
        //in case of being called at sub class
        pCopy = (CCJumpTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCJumpTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCJumpBy::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _delta, _height, _jumps);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCJumpTo::startWithTarget(CCNode *pTarget)
{
    CCJumpBy::startWithTarget(pTarget);
    _delta = ccp(_delta.x - _startPosition.x, _delta.y - _startPosition.y);
}

// Bezier cubic formula:
//    ((1 - t) + t)3 = 1 
// Expands to¡­ 
//   (1 - t)3 + 3t(1-t)2 + 3t2(1 - t) + t3 = 1 
static inline float bezierat( float a, float b, float c, float d, float t )
{
    return (powf(1-t,3) * a + 
            3*t*(powf(1-t,2))*b + 
            3*powf(t,2)*(1-t)*c +
            powf(t,3)*d );
}

//
// BezierBy
//

CCBezierBy* CCBezierBy::create(float t, const ccBezierConfig& c)
{
    CCBezierBy *pBezierBy = new CCBezierBy();
    pBezierBy->initWithDuration(t, c);
    pBezierBy->autorelease();

    return pBezierBy;
}

bool CCBezierBy::initWithDuration(float t, const ccBezierConfig& c)
{
    if (CCActionInterval::initWithDuration(t))
    {
        _config = c;
        return true;
    }

    return false;
}

void CCBezierBy::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    _previousPosition = _startPosition = pTarget->getPosition();
}

CCBezierBy* CCBezierBy::clone(void) const
{
	// no copy constructor
	auto a = new CCBezierBy();
	a->initWithDuration(_duration, _config);
	a->autorelease();
	return a;
}

CCObject* CCBezierBy::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCBezierBy* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCBezierBy*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCBezierBy();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _config);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCBezierBy::update(float time)
{
    if (_target)
    {
        float xa = 0;
        float xb = _config.controlPoint_1.x;
        float xc = _config.controlPoint_2.x;
        float xd = _config.endPosition.x;

        float ya = 0;
        float yb = _config.controlPoint_1.y;
        float yc = _config.controlPoint_2.y;
        float yd = _config.endPosition.y;

        float x = bezierat(xa, xb, xc, xd, time);
        float y = bezierat(ya, yb, yc, yd, time);

#if CC_ENABLE_STACKABLE_ACTIONS
        CCPoint currentPos = _target->getPosition();
        CCPoint diff = ccpSub(currentPos, _previousPosition);
        _startPosition = ccpAdd( _startPosition, diff);

        CCPoint newPos = ccpAdd( _startPosition, ccp(x,y));
        _target->setPosition(newPos);

        _previousPosition = newPos;
#else
        _target->setPosition(ccpAdd( _startPosition, ccp(x,y)));
#endif // !CC_ENABLE_STACKABLE_ACTIONS
    }
}

CCBezierBy* CCBezierBy::reverse(void) const
{
    ccBezierConfig r;

    r.endPosition = ccpNeg(_config.endPosition);
    r.controlPoint_1 = ccpAdd(_config.controlPoint_2, ccpNeg(_config.endPosition));
    r.controlPoint_2 = ccpAdd(_config.controlPoint_1, ccpNeg(_config.endPosition));

    CCBezierBy *pAction = CCBezierBy::create(_duration, r);
    return pAction;
}

//
// BezierTo
//

CCBezierTo* CCBezierTo::create(float t, const ccBezierConfig& c)
{
    CCBezierTo *pBezierTo = new CCBezierTo();
    pBezierTo->initWithDuration(t, c);
    pBezierTo->autorelease();

    return pBezierTo;
}

bool CCBezierTo::initWithDuration(float t, const ccBezierConfig &c)
{
    bool bRet = false;
    
    if (CCActionInterval::initWithDuration(t))
    {
        _toConfig = c;
    }
    
    return bRet;
}

CCBezierTo* CCBezierTo::clone(void) const
{
	// no copy constructor
	auto a = new CCBezierTo();
	a->initWithDuration(_duration, _config);
	a->autorelease();
	return a;
}

CCObject* CCBezierTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCBezierBy* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCBezierTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCBezierTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCBezierBy::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _config);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCBezierTo::startWithTarget(CCNode *pTarget)
{
    CCBezierBy::startWithTarget(pTarget);
    _config.controlPoint_1 = ccpSub(_toConfig.controlPoint_1, _startPosition);
    _config.controlPoint_2 = ccpSub(_toConfig.controlPoint_2, _startPosition);
    _config.endPosition = ccpSub(_toConfig.endPosition, _startPosition);
}

CCBezierTo* CCBezierTo::reverse() const
{
	CCAssert(false, "CCBezierTo doesn't support the 'reverse' method");
	return nullptr;
}


//
// ScaleTo
//
CCScaleTo* CCScaleTo::create(float duration, float s)
{
    CCScaleTo *pScaleTo = new CCScaleTo();
    pScaleTo->initWithDuration(duration, s);
    pScaleTo->autorelease();

    return pScaleTo;
}

CCScaleTo* CCScaleTo::create(float duration, float sx, float sy)
{
    CCScaleTo *pScaleTo = new CCScaleTo();
    pScaleTo->initWithDuration(duration, sx, sy);
    pScaleTo->autorelease();

    return pScaleTo;
}

bool CCScaleTo::initWithDuration(float duration, float s)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        _endScaleX = s;
        _endScaleY = s;

        return true;
    }

    return false;
}

bool CCScaleTo::initWithDuration(float duration, float sx, float sy)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        _endScaleX = sx;
        _endScaleY = sy;

        return true;
    }

    return false;
}

CCScaleTo* CCScaleTo::clone(void) const
{
	// no copy constructor
	auto a = new CCScaleTo();
	a->initWithDuration(_duration, _endScaleX, _endScaleY);
	a->autorelease();
	return a;
}

CCScaleTo* CCScaleTo::reverse() const
{
	CCAssert(false, "reverse() not supported in CCScaleTo");
	return nullptr;
}


CCObject* CCScaleTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCScaleTo* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCScaleTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCScaleTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);


    pCopy->initWithDuration(_duration, _endScaleX, _endScaleY);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCScaleTo::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    _startScaleX = pTarget->getScaleX();
    _startScaleY = pTarget->getScaleY();
    _deltaX = _endScaleX - _startScaleX;
    _deltaY = _endScaleY - _startScaleY;
}

void CCScaleTo::update(float time)
{
    if (_target)
    {
        _target->setScaleX(_startScaleX + _deltaX * time);
        _target->setScaleY(_startScaleY + _deltaY * time);
    }
}

//
// ScaleBy
//

CCScaleBy* CCScaleBy::create(float duration, float s)
{
    CCScaleBy *pScaleBy = new CCScaleBy();
    pScaleBy->initWithDuration(duration, s);
    pScaleBy->autorelease();

    return pScaleBy;
}

CCScaleBy* CCScaleBy::create(float duration, float sx, float sy)
{
    CCScaleBy *pScaleBy = new CCScaleBy();
    pScaleBy->initWithDuration(duration, sx, sy);
    pScaleBy->autorelease();

    return pScaleBy;
}

CCScaleBy* CCScaleBy::clone(void) const
{
	// no copy constructor
	auto a = new CCScaleBy();
    a->initWithDuration(_duration, _endScaleX, _endScaleY);
	a->autorelease();
	return a;
}

CCObject* CCScaleBy::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCScaleTo* pCopy = NULL;
    if(pZone && pZone->_copyObject)
    {
        //in case of being called at sub class
        pCopy = (CCScaleBy*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCScaleBy();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCScaleTo::copyWithZone(pZone);


    pCopy->initWithDuration(_duration, _endScaleX, _endScaleY);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCScaleBy::startWithTarget(CCNode *pTarget)
{
    CCScaleTo::startWithTarget(pTarget);
    _deltaX = _startScaleX * _endScaleX - _startScaleX;
    _deltaY = _startScaleY * _endScaleY - _startScaleY;
}

CCScaleBy* CCScaleBy::reverse() const
{
    return CCScaleBy::create(_duration, 1 / _endScaleX, 1 / _endScaleY);
}

//
// Blink
//

CCBlink* CCBlink::create(float duration, unsigned int uBlinks)
{
    CCBlink *pBlink = new CCBlink();
    pBlink->initWithDuration(duration, uBlinks);
    pBlink->autorelease();

    return pBlink;
}

bool CCBlink::initWithDuration(float duration, unsigned int uBlinks)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        _times = uBlinks;
        return true;
    }

    return false;
}

void CCBlink::stop()
{
    _target->setVisible(_originalState);
    CCActionInterval::stop();
}

void CCBlink::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    _originalState = pTarget->isVisible();
}

CCBlink* CCBlink::clone(void) const
{
	// no copy constructor
	auto a = new CCBlink();
	a->initWithDuration(_duration, (unsigned int)_times);
	a->autorelease();
	return a;
}

CCObject* CCBlink::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCBlink* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCBlink*)(pZone->_copyObject);

    }
    else
    {
        pCopy = new CCBlink();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, (unsigned int)_times);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCBlink::update(float time)
{
    if (_target && ! isDone())
    {
        float slice = 1.0f / _times;
        float m = fmodf(time, slice);
        _target->setVisible(m > slice / 2 ? true : false);
    }
}

CCBlink* CCBlink::reverse() const
{
    return CCBlink::create(_duration, _times);
}

//
// FadeIn
//

CCFadeIn* CCFadeIn::create(float d)
{
    CCFadeIn* pAction = new CCFadeIn();

    pAction->initWithDuration(d);
    pAction->autorelease();

    return pAction;
}

CCFadeIn* CCFadeIn::clone() const
{
	// no copy constructor
	auto a = new CCFadeIn();
	a->autorelease();
	return a;
}

CCObject* CCFadeIn::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCFadeIn* pCopy = NULL;
    if(pZone && pZone->_copyObject)
    {
        //in case of being called at sub class
        pCopy = (CCFadeIn*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCFadeIn();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCActionInterval::copyWithZone(pZone);

    CC_SAFE_DELETE(pNewZone);

    return pCopy;
}

void CCFadeIn::update(float time)
{
    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(_target);
    if (pRGBAProtocol)
    {
        pRGBAProtocol->setOpacity((GLubyte)(255 * time));
    }
    /*_target->setOpacity((GLubyte)(255 * time));*/
}

CCActionInterval* CCFadeIn::reverse() const
{
    return CCFadeOut::create(_duration);
}

//
// FadeOut
//

CCFadeOut* CCFadeOut::create(float d)
{
    CCFadeOut* pAction = new CCFadeOut();

    pAction->initWithDuration(d);
    pAction->autorelease();

    return pAction;
}

CCFadeOut* CCFadeOut::clone() const
{
	// no copy constructor
	auto a = new CCFadeOut();
	a->autorelease();
	return a;
}

CCObject* CCFadeOut::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCFadeOut* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCFadeOut*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCFadeOut();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    CC_SAFE_DELETE(pNewZone);

    return pCopy;
}

void CCFadeOut::update(float time)
{
    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(_target);
    if (pRGBAProtocol)
    {
        pRGBAProtocol->setOpacity(GLubyte(255 * (1 - time)));
    }
    /*_target->setOpacity(GLubyte(255 * (1 - time)));*/    
}

CCActionInterval* CCFadeOut::reverse() const
{
    return CCFadeIn::create(_duration);
}

//
// FadeTo
//

CCFadeTo* CCFadeTo::create(float duration, GLubyte opacity)
{
    CCFadeTo *pFadeTo = new CCFadeTo();
    pFadeTo->initWithDuration(duration, opacity);
    pFadeTo->autorelease();

    return pFadeTo;
}

bool CCFadeTo::initWithDuration(float duration, GLubyte opacity)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        _toOpacity = opacity;
        return true;
    }

    return false;
}

CCFadeTo* CCFadeTo::clone() const
{
	// no copy constructor
	auto a = new CCFadeTo();
	a->initWithDuration(_duration, _toOpacity);
	a->autorelease();
	return a;
}

CCFadeTo* CCFadeTo::reverse() const
{
	CCAssert(false, "reverse() not supported in CCFadeTo");
	return nullptr;
}

CCObject* CCFadeTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCFadeTo* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCFadeTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCFadeTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _toOpacity);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCFadeTo::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);

    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pTarget);
    if (pRGBAProtocol)
    {
        _fromOpacity = pRGBAProtocol->getOpacity();
    }
    /*_fromOpacity = pTarget->getOpacity();*/
}

void CCFadeTo::update(float time)
{
    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(_target);
    if (pRGBAProtocol)
    {
        pRGBAProtocol->setOpacity((GLubyte)(_fromOpacity + (_toOpacity - _fromOpacity) * time));
    }
    /*_target->setOpacity((GLubyte)(_fromOpacity + (_toOpacity - _fromOpacity) * time));*/
}

//
// TintTo
//
CCTintTo* CCTintTo::create(float duration, GLubyte red, GLubyte green, GLubyte blue)
{
    CCTintTo *pTintTo = new CCTintTo();
    pTintTo->initWithDuration(duration, red, green, blue);
    pTintTo->autorelease();

    return pTintTo;
}

bool CCTintTo::initWithDuration(float duration, GLubyte red, GLubyte green, GLubyte blue)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        _to = ccc3(red, green, blue);
        return true;
    }

    return false;
}

CCTintTo* CCTintTo::clone() const
{
	// no copy constructor
	auto a = new CCTintTo();
	a->initWithDuration(_duration, _to.r, _to.g, _to.b);
	a->autorelease();
	return a;
}

CCTintTo* CCTintTo::reverse() const
{
	CCAssert(false, "reverse() not supported in CCTintTo");
	return nullptr;
}

CCObject* CCTintTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCTintTo* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCTintTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCTintTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _to.r, _to.g, _to.b);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCTintTo::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(_target);
    if (pRGBAProtocol)
    {
        _from = pRGBAProtocol->getColor();
    }
    /*_from = pTarget->getColor();*/
}

void CCTintTo::update(float time)
{
    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(_target);
    if (pRGBAProtocol)
    {
        pRGBAProtocol->setColor(ccc3(GLubyte(_from.r + (_to.r - _from.r) * time), 
            (GLbyte)(_from.g + (_to.g - _from.g) * time),
            (GLbyte)(_from.b + (_to.b - _from.b) * time)));
    }    
}

//
// TintBy
//

CCTintBy* CCTintBy::create(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue)
{
    CCTintBy *pTintBy = new CCTintBy();
    pTintBy->initWithDuration(duration, deltaRed, deltaGreen, deltaBlue);
    pTintBy->autorelease();

    return pTintBy;
}

bool CCTintBy::initWithDuration(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        _deltaR = deltaRed;
        _deltaG = deltaGreen;
        _deltaB = deltaBlue;

        return true;
    }

    return false;
}

CCTintBy* CCTintBy::clone() const
{
	// no copy constructor
	auto a = new CCTintBy();
	a->initWithDuration(_duration, (GLubyte)_deltaR, (GLubyte)_deltaG, (GLubyte)_deltaB);
	a->autorelease();
	return a;
}

CCObject* CCTintBy::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCTintBy* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCTintBy*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCTintBy();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, (GLubyte)_deltaR, (GLubyte)_deltaG, (GLubyte)_deltaB);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCTintBy::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);

    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pTarget);
    if (pRGBAProtocol)
    {
        ccColor3B color = pRGBAProtocol->getColor();
        _fromR = color.r;
        _fromG = color.g;
        _fromB = color.b;
    }    
}

void CCTintBy::update(float time)
{
    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(_target);
    if (pRGBAProtocol)
    {
        pRGBAProtocol->setColor(ccc3((GLubyte)(_fromR + _deltaR * time),
            (GLubyte)(_fromG + _deltaG * time),
            (GLubyte)(_fromB + _deltaB * time)));
    }    
}

CCTintBy* CCTintBy::reverse() const
{
    return CCTintBy::create(_duration, -_deltaR, -_deltaG, -_deltaB);
}

//
// DelayTime
//
CCDelayTime* CCDelayTime::create(float d)
{
    CCDelayTime* pAction = new CCDelayTime();

    pAction->initWithDuration(d);
    pAction->autorelease();

    return pAction;
}

CCDelayTime* CCDelayTime::clone() const
{
	// no copy constructor
	auto a = new CCDelayTime();
	a->autorelease();
	return a;
}

CCObject* CCDelayTime::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCDelayTime* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCDelayTime*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCDelayTime();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCActionInterval::copyWithZone(pZone);

    CC_SAFE_DELETE(pNewZone);

    return pCopy;
}

void CCDelayTime::update(float time)
{
    CC_UNUSED_PARAM(time);
    return;
}

CCDelayTime* CCDelayTime::reverse() const
{
    return CCDelayTime::create(_duration);
}

//
// ReverseTime
//

CCReverseTime* CCReverseTime::create(CCFiniteTimeAction *pAction)
{
    // casting to prevent warnings
    CCReverseTime *pReverseTime = new CCReverseTime();
    pReverseTime->initWithAction( pAction->clone() );
    pReverseTime->autorelease();

    return pReverseTime;
}

bool CCReverseTime::initWithAction(CCFiniteTimeAction *pAction)
{
    CCAssert(pAction != NULL, "");
    CCAssert(pAction != _other, "");

    if (CCActionInterval::initWithDuration(pAction->getDuration()))
    {
        // Don't leak if action is reused
        CC_SAFE_RELEASE(_other);

        _other = pAction;
        pAction->retain();

        return true;
    }

    return false;
}

CCReverseTime* CCReverseTime::clone() const
{
	// no copy constructor
	auto a = new CCReverseTime();
	a->initWithAction( _other->clone() );
	a->autorelease();
	return a;
}

CCObject* CCReverseTime::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCReverseTime* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCReverseTime*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCReverseTime();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithAction(_other->clone());

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

CCReverseTime::CCReverseTime() : _other(NULL) 
{

}

CCReverseTime::~CCReverseTime(void)
{
    CC_SAFE_RELEASE(_other);
}

void CCReverseTime::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    _other->startWithTarget(pTarget);
}

void CCReverseTime::stop(void)
{
    _other->stop();
    CCActionInterval::stop();
}

void CCReverseTime::update(float time)
{
    if (_other)
    {
        _other->update(1 - time);
    }
}

CCReverseTime* CCReverseTime::reverse() const
{
    return (CCReverseTime*)_other->clone();
}

//
// Animate
//
CCAnimate* CCAnimate::create(CCAnimation *pAnimation)
{
    CCAnimate *pAnimate = new CCAnimate();
    pAnimate->initWithAnimation(pAnimation);
    pAnimate->autorelease();

    return pAnimate;
}

bool CCAnimate::initWithAnimation(CCAnimation *pAnimation)
{
    CCAssert( pAnimation!=NULL, "Animate: argument Animation must be non-NULL");

    float singleDuration = pAnimation->getDuration();

    if ( CCActionInterval::initWithDuration(singleDuration * pAnimation->getLoops() ) ) 
    {
        _nextFrame = 0;
        setAnimation(pAnimation);
        _origFrame = NULL;
        _executedLoops = 0;

        _splitTimes->reserve(pAnimation->getFrames()->count());

        float accumUnitsOfTime = 0;
        float newUnitOfTimeValue = singleDuration / pAnimation->getTotalDelayUnits();

        CCArray* pFrames = pAnimation->getFrames();
        CCARRAY_VERIFY_TYPE(pFrames, CCAnimationFrame*);

        CCObject* pObj = NULL;
        CCARRAY_FOREACH(pFrames, pObj)
        {
            CCAnimationFrame* frame = (CCAnimationFrame*)pObj;
            float value = (accumUnitsOfTime * newUnitOfTimeValue) / singleDuration;
            accumUnitsOfTime += frame->getDelayUnits();
            _splitTimes->push_back(value);
        }    
        return true;
    }
    return false;
}

CCAnimate* CCAnimate::clone() const
{
	// no copy constructor
	auto a = new CCAnimate();
	a->initWithAnimation(_animation->clone());
	a->autorelease();
	return a;
}

CCObject* CCAnimate::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCAnimate* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCAnimate*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCAnimate();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithAnimation(_animation->clone());

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

CCAnimate::CCAnimate()
: _animation(NULL)
, _splitTimes(new std::vector<float>)
, _nextFrame(0)
, _origFrame(NULL)
, _executedLoops(0)
{

}

CCAnimate::~CCAnimate()
{
    CC_SAFE_RELEASE(_animation);
    CC_SAFE_RELEASE(_origFrame);
    CC_SAFE_DELETE(_splitTimes);
}

void CCAnimate::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    CCSprite *pSprite = (CCSprite*)(pTarget);

    CC_SAFE_RELEASE(_origFrame);

    if (_animation->getRestoreOriginalFrame())
    {
        _origFrame = pSprite->displayFrame();
        _origFrame->retain();
    }
    _nextFrame = 0;
    _executedLoops = 0;
}

void CCAnimate::stop(void)
{
    if (_animation->getRestoreOriginalFrame() && _target)
    {
        ((CCSprite*)(_target))->setDisplayFrame(_origFrame);
    }

    CCActionInterval::stop();
}

void CCAnimate::update(float t)
{
    // if t==1, ignore. Animation should finish with t==1
    if( t < 1.0f ) {
        t *= _animation->getLoops();

        // new loop?  If so, reset frame counter
        unsigned int loopNumber = (unsigned int)t;
        if( loopNumber > _executedLoops ) {
            _nextFrame = 0;
            _executedLoops++;
        }

        // new t for animations
        t = fmodf(t, 1.0f);
    }

    CCArray* frames = _animation->getFrames();
    unsigned int numberOfFrames = frames->count();
    CCSpriteFrame *frameToDisplay = NULL;

    for( unsigned int i=_nextFrame; i < numberOfFrames; i++ ) {
        float splitTime = _splitTimes->at(i);

        if( splitTime <= t ) {
            CCAnimationFrame* frame = (CCAnimationFrame*)frames->objectAtIndex(i);
            frameToDisplay = frame->getSpriteFrame();
            ((CCSprite*)_target)->setDisplayFrame(frameToDisplay);

            CCDictionary* dict = frame->getUserInfo();
            if( dict )
            {
                //TODO: [[NSNotificationCenter defaultCenter] postNotificationName:CCAnimationFrameDisplayedNotification object:target_ userInfo:dict];
            }
            _nextFrame = i+1;
        }
        // Issue 1438. Could be more than one frame per tick, due to low frame rate or frame delta < 1/FPS
        else {
            break;
        }
    }
}

CCAnimate* CCAnimate::reverse() const
{
    CCArray* pOldArray = _animation->getFrames();
    CCArray* pNewArray = CCArray::createWithCapacity(pOldArray->count());
   
    CCARRAY_VERIFY_TYPE(pOldArray, CCAnimationFrame*);

    if (pOldArray->count() > 0)
    {
        CCObject* pObj = NULL;
        CCARRAY_FOREACH_REVERSE(pOldArray, pObj)
        {
            CCAnimationFrame* pElement = (CCAnimationFrame*)pObj;
            if (! pElement)
            {
                break;
            }

            pNewArray->addObject(pElement->clone());
        }
    }

    CCAnimation *newAnim = CCAnimation::create(pNewArray, _animation->getDelayPerUnit(), _animation->getLoops());
    newAnim->setRestoreOriginalFrame(_animation->getRestoreOriginalFrame());
    return CCAnimate::create(newAnim);
}

// CCTargetedAction

CCTargetedAction::CCTargetedAction()
: _forcedTarget(NULL)
, _action(NULL)
{

}

CCTargetedAction::~CCTargetedAction()
{
    CC_SAFE_RELEASE(_forcedTarget);
    CC_SAFE_RELEASE(_action);
}

CCTargetedAction* CCTargetedAction::create(CCNode* pTarget, CCFiniteTimeAction* pAction)
{
    CCTargetedAction* p = new CCTargetedAction();
    p->initWithTarget(pTarget, pAction);
    p->autorelease();
    return p;
}


bool CCTargetedAction::initWithTarget(CCNode* pTarget, CCFiniteTimeAction* pAction)
{
    if(CCActionInterval::initWithDuration(pAction->getDuration()))
    {
        CC_SAFE_RETAIN(pTarget);
        _forcedTarget = pTarget;
        CC_SAFE_RETAIN(pAction);
        _action = pAction;
        return true;
    }
    return false;
}

CCTargetedAction* CCTargetedAction::clone() const
{
	// no copy constructor	
	auto a = new CCTargetedAction();
    // win32 : use the _other's copy object.
	a->initWithTarget(_forcedTarget, _action->clone());
	a->autorelease();
	return a;
}

CCTargetedAction* CCTargetedAction::reverse(void) const
{
	// no reverse for this action, just clone it
	return this->clone();
}

CCObject* CCTargetedAction::copyWithZone(CCZone* pZone)
{
    CCZone* pNewZone = NULL;
    CCTargetedAction* pRet = NULL;
    if(pZone && pZone->_copyObject) //in case of being called at sub class
    {
        pRet = (CCTargetedAction*)(pZone->_copyObject);
    }
    else
    {
        pRet = new CCTargetedAction();
        pZone = pNewZone = new CCZone(pRet);
    }
    CCActionInterval::copyWithZone(pZone);
    // win32 : use the _other's copy object.
    pRet->initWithTarget(_forcedTarget, _action->clone());
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCTargetedAction::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    _action->startWithTarget(_forcedTarget);
}

void CCTargetedAction::stop(void)
{
    _action->stop();
}

void CCTargetedAction::update(float time)
{
    _action->update(time);
}

NS_CC_END
