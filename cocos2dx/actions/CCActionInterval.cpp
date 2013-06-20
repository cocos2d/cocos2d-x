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

// Extra action for making a Sequence or Spawn when only adding one action to it.
class ExtraAction : public FiniteTimeAction
{
public:
    static ExtraAction* create();
    virtual ExtraAction* clone() const;
    virtual Object* copyWithZone(Zone* pZone);
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

Object* ExtraAction::copyWithZone(Zone* pZone)
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

bool ActionInterval::initWithDuration(float d)
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

bool ActionInterval::isDone(void)
{
    return _elapsed >= _duration;
}

void ActionInterval::step(float dt)
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

void ActionInterval::setAmplitudeRate(float amp)
{
    CC_UNUSED_PARAM(amp);
    // Abstract class needs implementation
    CCAssert(0, "");
}

float ActionInterval::getAmplitudeRate(void)
{
    // Abstract class needs implementation
    CCAssert(0, "");

    return 0;
}

void ActionInterval::startWithTarget(Node *pTarget)
{
    FiniteTimeAction::startWithTarget(pTarget);
    _elapsed = 0.0f;
    _firstTick = true;
}

//
// Sequence
//

Sequence* Sequence::createWithTwoActions(FiniteTimeAction *pActionOne, FiniteTimeAction *pActionTwo)
{
    Sequence *pSequence = new Sequence();
    pSequence->initWithTwoActions(pActionOne, pActionTwo);
    pSequence->autorelease();

    return pSequence;
}

Sequence* Sequence::create(FiniteTimeAction *pAction1, ...)
{
    va_list params;
    va_start(params, pAction1);

    Sequence *pRet = Sequence::createWithVariableList(pAction1, params);

    va_end(params);
    
    return pRet;
}

Sequence* Sequence::createWithVariableList(FiniteTimeAction *pAction1, va_list args)
{
    FiniteTimeAction *pNow;
    FiniteTimeAction *pPrev = pAction1;
    bool bOneAction = true;

    while (pAction1)
    {
        pNow = va_arg(args, FiniteTimeAction*);
        if (pNow)
        {
            pPrev = createWithTwoActions(pPrev, pNow);
            bOneAction = false;
        }
        else
        {
            // If only one action is added to Sequence, make up a Sequence by adding a simplest finite time action.
            if (bOneAction)
            {
                pPrev = createWithTwoActions(pPrev, ExtraAction::create());
            }
            break;
        }
    }
    
    return ((Sequence*)pPrev);
}

Sequence* Sequence::create(Array* arrayOfActions)
{
    Sequence* pRet = NULL;
    do 
    {
        unsigned  int count = arrayOfActions->count();
        CC_BREAK_IF(count == 0);

        FiniteTimeAction* prev = (FiniteTimeAction*)arrayOfActions->objectAtIndex(0);

        if (count > 1)
        {
            for (unsigned int i = 1; i < count; ++i)
            {
                prev = createWithTwoActions(prev, (FiniteTimeAction*)arrayOfActions->objectAtIndex(i));
            }
        }
        else
        {
            // If only one action is added to Sequence, make up a Sequence by adding a simplest finite time action.
            prev = createWithTwoActions(prev, ExtraAction::create());
        }
        pRet = (Sequence*)prev;
    }while (0);
    return pRet;
}

bool Sequence::initWithTwoActions(FiniteTimeAction *pActionOne, FiniteTimeAction *pActionTwo)
{
    CCAssert(pActionOne != NULL, "");
    CCAssert(pActionTwo != NULL, "");

    float d = pActionOne->getDuration() + pActionTwo->getDuration();
    ActionInterval::initWithDuration(d);

    _actions[0] = pActionOne;
    pActionOne->retain();

    _actions[1] = pActionTwo;
    pActionTwo->retain();

    return true;
}

Sequence* Sequence::clone(void) const
{
	// no copy constructor
	auto a = new Sequence();
    a->initWithTwoActions((FiniteTimeAction*)(_actions[0]->clone()),
							  (FiniteTimeAction*)(_actions[1]->clone())
						  );
	a->autorelease();
	return a;
}

Object* Sequence::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    Sequence* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (Sequence*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new Sequence();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);

    pCopy->initWithTwoActions(_actions[0]->clone(), _actions[1]->clone());

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

Sequence::~Sequence(void)
{
    CC_SAFE_RELEASE(_actions[0]);
    CC_SAFE_RELEASE(_actions[1]);
}

void Sequence::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);
    _split = _actions[0]->getDuration() / _duration;
    _last = -1;
}

void Sequence::stop(void)
{
    // Issue #1305
    if( _last != - 1)
    {
        _actions[_last]->stop();
    }

    ActionInterval::stop();
}

void Sequence::update(float t)
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

Sequence* Sequence::reverse() const
{
    return Sequence::createWithTwoActions(_actions[1]->reverse(), _actions[0]->reverse());
}

//
// Repeat
//

Repeat* Repeat::create(FiniteTimeAction *pAction, unsigned int times)
{
    Repeat* pRepeat = new Repeat();
    pRepeat->initWithAction(pAction, times);
    pRepeat->autorelease();

    return pRepeat;
}

bool Repeat::initWithAction(FiniteTimeAction *pAction, unsigned int times)
{
    float d = pAction->getDuration() * times;

    if (ActionInterval::initWithDuration(d))
    {
        _times = times;
        _innerAction = pAction;
        pAction->retain();

        _actionInstant = dynamic_cast<ActionInstant*>(pAction) ? true : false;
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

Repeat* Repeat::clone(void) const
{
	// no copy constructor
	auto a = new Repeat();
	a->initWithAction((FiniteTimeAction*)_innerAction->clone(), _times );
	a->autorelease();
	return a;
}


Object* Repeat::copyWithZone(Zone *pZone)
{
    
    Zone* pNewZone = NULL;
    Repeat* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (Repeat*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new Repeat();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);

    pCopy->initWithAction(_innerAction->clone(), _times);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

Repeat::~Repeat(void)
{
    CC_SAFE_RELEASE(_innerAction);
}

void Repeat::startWithTarget(Node *pTarget)
{
    _total = 0;
    _nextDt = _innerAction->getDuration()/_duration;
    ActionInterval::startWithTarget(pTarget);
    _innerAction->startWithTarget(pTarget);
}

void Repeat::stop(void)
{
    _innerAction->stop();
    ActionInterval::stop();
}

// issue #80. Instead of hooking step:, hook update: since it can be called by any 
// container action like Repeat, Sequence, Ease, etc..
void Repeat::update(float dt)
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

bool Repeat::isDone(void)
{
    return _total == _times;
}

Repeat* Repeat::reverse() const
{
    return Repeat::create(_innerAction->reverse(), _times);
}

//
// RepeatForever
//
RepeatForever::~RepeatForever()
{
    CC_SAFE_RELEASE(_innerAction);
}

RepeatForever *RepeatForever::create(ActionInterval *pAction)
{
    RepeatForever *pRet = new RepeatForever();
    if (pRet && pRet->initWithAction(pAction))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool RepeatForever::initWithAction(ActionInterval *pAction)
{
    CCAssert(pAction != NULL, "");
    pAction->retain();
    _innerAction = pAction;
    return true;
}

RepeatForever *RepeatForever::clone(void) const
{
	// no copy constructor	
	auto a = new RepeatForever();
	a->initWithAction((ActionInterval*)_innerAction->clone());
	a->autorelease();
	return a;
}

Object* RepeatForever::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    RepeatForever* pRet = NULL;
    if(pZone && pZone->_copyObject) //in case of being called at sub class
    {
        pRet = (RepeatForever*)(pZone->_copyObject);
    }
    else
    {
        pRet = new RepeatForever();
        pZone = pNewZone = new Zone(pRet);
    }
    ActionInterval::copyWithZone(pZone);
    // win32 : use the _other's copy object.
    pRet->initWithAction(_innerAction->clone());
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void RepeatForever::startWithTarget(Node* pTarget)
{
    ActionInterval::startWithTarget(pTarget);
    _innerAction->startWithTarget(pTarget);
}

void RepeatForever::step(float dt)
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

bool RepeatForever::isDone()
{
    return false;
}

RepeatForever *RepeatForever::reverse() const
{
    return RepeatForever::create(_innerAction->reverse());
}

//
// Spawn
//

Spawn* Spawn::create(FiniteTimeAction *pAction1, ...)
{
    va_list params;
    va_start(params, pAction1);

    Spawn *pRet = Spawn::createWithVariableList(pAction1, params);

    va_end(params);
    
    return pRet;
}

Spawn* Spawn::createWithVariableList(FiniteTimeAction *pAction1, va_list args)
{
    FiniteTimeAction *pNow;
    FiniteTimeAction *pPrev = pAction1;
    bool bOneAction = true;

    while (pAction1)
    {
        pNow = va_arg(args, FiniteTimeAction*);
        if (pNow)
        {
            pPrev = createWithTwoActions(pPrev, pNow);
            bOneAction = false;
        }
        else
        {
            // If only one action is added to Spawn, make up a Spawn by adding a simplest finite time action.
            if (bOneAction)
            {
                pPrev = createWithTwoActions(pPrev, ExtraAction::create());
            }
            break;
        }
    }

    return ((Spawn*)pPrev);
}

Spawn* Spawn::create(Array *arrayOfActions)
{
    Spawn* pRet = NULL;
    do 
    {
        unsigned  int count = arrayOfActions->count();
        CC_BREAK_IF(count == 0);
        FiniteTimeAction* prev = (FiniteTimeAction*)arrayOfActions->objectAtIndex(0);
        if (count > 1)
        {
            for (unsigned int i = 1; i < arrayOfActions->count(); ++i)
            {
                prev = createWithTwoActions(prev, (FiniteTimeAction*)arrayOfActions->objectAtIndex(i));
            }
        }
        else
        {
            // If only one action is added to Spawn, make up a Spawn by adding a simplest finite time action.
            prev = createWithTwoActions(prev, ExtraAction::create());
        }
        pRet = (Spawn*)prev;
    }while (0);

    return pRet;
}

Spawn* Spawn::createWithTwoActions(FiniteTimeAction *pAction1, FiniteTimeAction *pAction2)
{
    Spawn *pSpawn = new Spawn();
    pSpawn->initWithTwoActions(pAction1, pAction2);
    pSpawn->autorelease();

    return pSpawn;
}

bool Spawn:: initWithTwoActions(FiniteTimeAction *pAction1, FiniteTimeAction *pAction2)
{
    CCAssert(pAction1 != NULL, "");
    CCAssert(pAction2 != NULL, "");

    bool bRet = false;

    float d1 = pAction1->getDuration();
    float d2 = pAction2->getDuration();

    if (ActionInterval::initWithDuration(MAX(d1, d2)))
    {
        _one = pAction1;
        _two = pAction2;

        if (d1 > d2)
        {
            _two = Sequence::createWithTwoActions(pAction2, DelayTime::create(d1 - d2));
        } 
        else if (d1 < d2)
        {
            _one = Sequence::createWithTwoActions(pAction1, DelayTime::create(d2 - d1));
        }

        _one->retain();
        _two->retain();

        bRet = true;
    }

    
    return bRet;
}

Spawn* Spawn::clone(void) const
{
	// no copy constructor	
	auto a = new Spawn();
    a->initWithTwoActions(_one->clone(), _two->clone());

	a->autorelease();
	return a;
}

Object* Spawn::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    Spawn* pCopy = NULL;

    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (Spawn*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new Spawn();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);

    pCopy->initWithTwoActions(_one->clone(), _two->clone());

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

Spawn::~Spawn(void)
{
    CC_SAFE_RELEASE(_one);
    CC_SAFE_RELEASE(_two);
}

void Spawn::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);
    _one->startWithTarget(pTarget);
    _two->startWithTarget(pTarget);
}

void Spawn::stop(void)
{
    _one->stop();
    _two->stop();
    ActionInterval::stop();
}

void Spawn::update(float time)
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

Spawn* Spawn::reverse() const
{
    return Spawn::createWithTwoActions(_one->reverse(), _two->reverse());
}

//
// RotateTo
//

RotateTo* RotateTo::create(float fDuration, float fDeltaAngle)
{
    RotateTo* pRotateTo = new RotateTo();
    pRotateTo->initWithDuration(fDuration, fDeltaAngle);
    pRotateTo->autorelease();

    return pRotateTo;
}

bool RotateTo::initWithDuration(float fDuration, float fDeltaAngle)
{
    if (ActionInterval::initWithDuration(fDuration))
    {
        _dstAngleX = _dstAngleY = fDeltaAngle;
        return true;
    }

    return false;
}

RotateTo* RotateTo::create(float fDuration, float fDeltaAngleX, float fDeltaAngleY)
{
    RotateTo* pRotateTo = new RotateTo();
    pRotateTo->initWithDuration(fDuration, fDeltaAngleX, fDeltaAngleY);
    pRotateTo->autorelease();
    
    return pRotateTo;
}

bool RotateTo::initWithDuration(float fDuration, float fDeltaAngleX, float fDeltaAngleY)
{
    if (ActionInterval::initWithDuration(fDuration))
    {
        _dstAngleX = fDeltaAngleX;
        _dstAngleY = fDeltaAngleY;
        
        return true;
    }
    
    return false;
}

RotateTo* RotateTo::clone(void) const
{
	// no copy constructor
	auto a = new RotateTo();
	a->initWithDuration(_duration, _dstAngleX, _dstAngleY);
	a->autorelease();
	return a;
}

Object* RotateTo::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    RotateTo* pCopy = NULL;
    if(pZone && pZone->_copyObject)
    {
        //in case of being called at sub class
        pCopy = (RotateTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new RotateTo();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _dstAngleX, _dstAngleY);

    //Action *copy = [[[self class] allocWithZone: zone] initWithDuration:[self duration] angle: angle];
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void RotateTo::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);
    
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

void RotateTo::update(float time)
{
    if (_target)
    {
        _target->setRotationX(_startAngleX + _diffAngleX * time);
        _target->setRotationY(_startAngleY + _diffAngleY * time);
    }
}

RotateTo *RotateTo::reverse() const
{
	CCAssert(false, "RotateTo doesn't support the 'reverse' method");
	return nullptr;
}

//
// RotateBy
//

RotateBy* RotateBy::create(float fDuration, float fDeltaAngle)
{
    RotateBy *pRotateBy = new RotateBy();
    pRotateBy->initWithDuration(fDuration, fDeltaAngle);
    pRotateBy->autorelease();

    return pRotateBy;
}

bool RotateBy::initWithDuration(float fDuration, float fDeltaAngle)
{
    if (ActionInterval::initWithDuration(fDuration))
    {
        _angleX = _angleY = fDeltaAngle;
        return true;
    }

    return false;
}

RotateBy* RotateBy::create(float fDuration, float fDeltaAngleX, float fDeltaAngleY)
{
    RotateBy *pRotateBy = new RotateBy();
    pRotateBy->initWithDuration(fDuration, fDeltaAngleX, fDeltaAngleY);
    pRotateBy->autorelease();
    
    return pRotateBy;
}

bool RotateBy::initWithDuration(float fDuration, float fDeltaAngleX, float fDeltaAngleY)
{
    if (ActionInterval::initWithDuration(fDuration))
    {
        _angleX = fDeltaAngleX;
        _angleY = fDeltaAngleY;
        return true;
    }
    
    return false;
}

RotateBy* RotateBy::clone(void) const
{
	// no copy constructor
	auto a = new RotateBy();
    a->initWithDuration(_duration, _angleX, _angleY);
	a->autorelease();
	return a;
}

Object* RotateBy::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    RotateBy* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (RotateBy*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new RotateBy();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _angleX, _angleY);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void RotateBy::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);
    _startAngleX = pTarget->getRotationX();
    _startAngleY = pTarget->getRotationY();
}

void RotateBy::update(float time)
{
    // XXX: shall I add % 360
    if (_target)
    {
        _target->setRotationX(_startAngleX + _angleX * time);
        _target->setRotationY(_startAngleY + _angleY * time);
    }
}

RotateBy* RotateBy::reverse() const
{
    return RotateBy::create(_duration, -_angleX, -_angleY);
}

//
// MoveBy
//

MoveBy* MoveBy::create(float duration, const Point& deltaPosition)
{
    MoveBy *pRet = new MoveBy();
    pRet->initWithDuration(duration, deltaPosition);
    pRet->autorelease();

    return pRet;
}

bool MoveBy::initWithDuration(float duration, const Point& deltaPosition)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _positionDelta = deltaPosition;
        return true;
    }

    return false;
}

MoveBy* MoveBy::clone(void) const
{
	// no copy constructor
	auto a = new MoveBy();
    a->initWithDuration(_duration, _positionDelta);
	a->autorelease();
	return a;
}

Object* MoveBy::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    MoveBy* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (MoveBy*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new MoveBy();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _positionDelta);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void MoveBy::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);
    _previousPosition = _startPosition = pTarget->getPosition();
}

MoveBy* MoveBy::reverse() const
{
    return MoveBy::create(_duration, ccp( -_positionDelta.x, -_positionDelta.y));
}


void MoveBy::update(float t)
{
    if (_target)
    {
#if CC_ENABLE_STACKABLE_ACTIONS
        Point currentPos = _target->getPosition();
        Point diff = ccpSub(currentPos, _previousPosition);
        _startPosition = ccpAdd( _startPosition, diff);
        Point newPos =  ccpAdd( _startPosition, ccpMult(_positionDelta, t) );
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

MoveTo* MoveTo::create(float duration, const Point& position)
{
    MoveTo *pRet = new MoveTo();
    pRet->initWithDuration(duration, position);
    pRet->autorelease();

    return pRet;
}

bool MoveTo::initWithDuration(float duration, const Point& position)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _endPosition = position;
        return true;
    }

    return false;
}

MoveTo* MoveTo::clone(void) const
{
	// no copy constructor
	auto a = new MoveTo();
    a->initWithDuration(_duration, _endPosition);
	a->autorelease();
	return a;
}

Object* MoveTo::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    MoveTo* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (MoveTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new MoveTo();
        pZone = pNewZone = new Zone(pCopy);
    }

    MoveBy::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _endPosition);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void MoveTo::startWithTarget(Node *pTarget)
{
    MoveBy::startWithTarget(pTarget);
    _positionDelta = ccpSub( _endPosition, pTarget->getPosition() );
}


//
// SkewTo
//
SkewTo* SkewTo::create(float t, float sx, float sy)
{
    SkewTo *pSkewTo = new SkewTo();
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

bool SkewTo::initWithDuration(float t, float sx, float sy)
{
    bool bRet = false;

    if (ActionInterval::initWithDuration(t))
    {
        _endSkewX = sx;
        _endSkewY = sy;

        bRet = true;
    }

    return bRet;
}

SkewTo* SkewTo::clone(void) const
{
	// no copy constructor
	auto a = new SkewTo();
	a->initWithDuration(_duration, _endSkewX, _endSkewY);
	a->autorelease();
	return a;
}

SkewTo* SkewTo::reverse() const
{
	CCAssert(false, "reverse() not supported in SkewTo");
	return nullptr;
}

Object* SkewTo::copyWithZone(Zone* pZone)
{
    Zone* pNewZone = NULL;
    SkewTo* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (SkewTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new SkewTo();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _endSkewX, _endSkewY);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void SkewTo::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);

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

void SkewTo::update(float t)
{
    _target->setSkewX(_startSkewX + _deltaX * t);
    _target->setSkewY(_startSkewY + _deltaY * t);
}

SkewTo::SkewTo()
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
// SkewBy
//
SkewBy* SkewBy::create(float t, float sx, float sy)
{
    SkewBy *pSkewBy = new SkewBy();
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

SkewBy * SkewBy::clone() const
{
	// no copy constructor
	auto a = new SkewBy();
	a->initWithDuration(_duration, _skewX, _skewY);
	a->autorelease();
	return a;
}

bool SkewBy::initWithDuration(float t, float deltaSkewX, float deltaSkewY)
{
    bool bRet = false;

    if (SkewTo::initWithDuration(t, deltaSkewX, deltaSkewY))
    {
        _skewX = deltaSkewX;
        _skewY = deltaSkewY;

        bRet = true;
    }

    return bRet;
}

void SkewBy::startWithTarget(Node *pTarget)
{
    SkewTo::startWithTarget(pTarget);
    _deltaX = _skewX;
    _deltaY = _skewY;
    _endSkewX = _startSkewX + _deltaX;
    _endSkewY = _startSkewY + _deltaY;
}

SkewBy* SkewBy::reverse() const
{
    return SkewBy::create(_duration, -_skewX, -_skewY);
}

//
// JumpBy
//

JumpBy* JumpBy::create(float duration, const Point& position, float height, unsigned int jumps)
{
    JumpBy *pJumpBy = new JumpBy();
    pJumpBy->initWithDuration(duration, position, height, jumps);
    pJumpBy->autorelease();

    return pJumpBy;
}

bool JumpBy::initWithDuration(float duration, const Point& position, float height, unsigned int jumps)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _delta = position;
        _height = height;
        _jumps = jumps;

        return true;
    }

    return false;
}

JumpBy* JumpBy::clone(void) const
{
	// no copy constructor
	auto a = new JumpBy();
	a->initWithDuration(_duration, _delta, _height, _jumps);
	a->autorelease();
	return a;
}

Object* JumpBy::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    JumpBy* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (JumpBy*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new JumpBy();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _delta, _height, _jumps);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void JumpBy::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);
    _previousPos = _startPosition = pTarget->getPosition();
}

void JumpBy::update(float t)
{
    // parabolic jump (since v0.8.2)
    if (_target)
    {
        float frac = fmodf( t * _jumps, 1.0f );
        float y = _height * 4 * frac * (1 - frac);
        y += _delta.y * t;

        float x = _delta.x * t;
#if CC_ENABLE_STACKABLE_ACTIONS
        Point currentPos = _target->getPosition();

        Point diff = ccpSub( currentPos, _previousPos );
        _startPosition = ccpAdd( diff, _startPosition);

        Point newPos = ccpAdd( _startPosition, ccp(x,y));
        _target->setPosition(newPos);

        _previousPos = newPos;
#else
        _target->setPosition(ccpAdd( _startPosition, ccp(x,y)));
#endif // !CC_ENABLE_STACKABLE_ACTIONS
    }
}

JumpBy* JumpBy::reverse() const
{
    return JumpBy::create(_duration, ccp(-_delta.x, -_delta.y),
        _height, _jumps);
}

//
// JumpTo
//

JumpTo* JumpTo::create(float duration, const Point& position, float height, int jumps)
{
    JumpTo *pJumpTo = new JumpTo();
    pJumpTo->initWithDuration(duration, position, height, jumps);
    pJumpTo->autorelease();

    return pJumpTo;
}

JumpTo* JumpTo::clone(void) const
{
	// no copy constructor
	auto a = new JumpTo();
    a->initWithDuration(_duration, _delta, _height, _jumps);
	a->autorelease();
	return a;
}

JumpTo* JumpTo::reverse() const
{
	CCAssert(false, "reverse() not supported in JumpTo");
	return nullptr;
}

Object* JumpTo::copyWithZone(Zone* pZone)
{
    Zone* pNewZone = NULL;
    JumpTo* pCopy = NULL;
    if(pZone && pZone->_copyObject)
    {
        //in case of being called at sub class
        pCopy = (JumpTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new JumpTo();
        pZone = pNewZone = new Zone(pCopy);
    }

    JumpBy::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _delta, _height, _jumps);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void JumpTo::startWithTarget(Node *pTarget)
{
    JumpBy::startWithTarget(pTarget);
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

BezierBy* BezierBy::create(float t, const ccBezierConfig& c)
{
    BezierBy *pBezierBy = new BezierBy();
    pBezierBy->initWithDuration(t, c);
    pBezierBy->autorelease();

    return pBezierBy;
}

bool BezierBy::initWithDuration(float t, const ccBezierConfig& c)
{
    if (ActionInterval::initWithDuration(t))
    {
        _config = c;
        return true;
    }

    return false;
}

void BezierBy::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);
    _previousPosition = _startPosition = pTarget->getPosition();
}

BezierBy* BezierBy::clone(void) const
{
	// no copy constructor
	auto a = new BezierBy();
	a->initWithDuration(_duration, _config);
	a->autorelease();
	return a;
}

Object* BezierBy::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    BezierBy* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (BezierBy*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new BezierBy();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _config);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void BezierBy::update(float time)
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
        Point currentPos = _target->getPosition();
        Point diff = ccpSub(currentPos, _previousPosition);
        _startPosition = ccpAdd( _startPosition, diff);

        Point newPos = ccpAdd( _startPosition, ccp(x,y));
        _target->setPosition(newPos);

        _previousPosition = newPos;
#else
        _target->setPosition(ccpAdd( _startPosition, ccp(x,y)));
#endif // !CC_ENABLE_STACKABLE_ACTIONS
    }
}

BezierBy* BezierBy::reverse(void) const
{
    ccBezierConfig r;

    r.endPosition = ccpNeg(_config.endPosition);
    r.controlPoint_1 = ccpAdd(_config.controlPoint_2, ccpNeg(_config.endPosition));
    r.controlPoint_2 = ccpAdd(_config.controlPoint_1, ccpNeg(_config.endPosition));

    BezierBy *pAction = BezierBy::create(_duration, r);
    return pAction;
}

//
// BezierTo
//

BezierTo* BezierTo::create(float t, const ccBezierConfig& c)
{
    BezierTo *pBezierTo = new BezierTo();
    pBezierTo->initWithDuration(t, c);
    pBezierTo->autorelease();

    return pBezierTo;
}

bool BezierTo::initWithDuration(float t, const ccBezierConfig &c)
{
    bool bRet = false;
    
    if (ActionInterval::initWithDuration(t))
    {
        _toConfig = c;
    }
    
    return bRet;
}

BezierTo* BezierTo::clone(void) const
{
	// no copy constructor
	auto a = new BezierTo();
	a->initWithDuration(_duration, _config);
	a->autorelease();
	return a;
}

Object* BezierTo::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    BezierBy* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (BezierTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new BezierTo();
        pZone = pNewZone = new Zone(pCopy);
    }

    BezierBy::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _config);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void BezierTo::startWithTarget(Node *pTarget)
{
    BezierBy::startWithTarget(pTarget);
    _config.controlPoint_1 = ccpSub(_toConfig.controlPoint_1, _startPosition);
    _config.controlPoint_2 = ccpSub(_toConfig.controlPoint_2, _startPosition);
    _config.endPosition = ccpSub(_toConfig.endPosition, _startPosition);
}

BezierTo* BezierTo::reverse() const
{
	CCAssert(false, "CCBezierTo doesn't support the 'reverse' method");
	return nullptr;
}


//
// ScaleTo
//
ScaleTo* ScaleTo::create(float duration, float s)
{
    ScaleTo *pScaleTo = new ScaleTo();
    pScaleTo->initWithDuration(duration, s);
    pScaleTo->autorelease();

    return pScaleTo;
}

ScaleTo* ScaleTo::create(float duration, float sx, float sy)
{
    ScaleTo *pScaleTo = new ScaleTo();
    pScaleTo->initWithDuration(duration, sx, sy);
    pScaleTo->autorelease();

    return pScaleTo;
}

bool ScaleTo::initWithDuration(float duration, float s)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _endScaleX = s;
        _endScaleY = s;

        return true;
    }

    return false;
}

bool ScaleTo::initWithDuration(float duration, float sx, float sy)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _endScaleX = sx;
        _endScaleY = sy;

        return true;
    }

    return false;
}

ScaleTo* ScaleTo::clone(void) const
{
	// no copy constructor
	auto a = new ScaleTo();
	a->initWithDuration(_duration, _endScaleX, _endScaleY);
	a->autorelease();
	return a;
}

ScaleTo* ScaleTo::reverse() const
{
	CCAssert(false, "reverse() not supported in ScaleTo");
	return nullptr;
}


Object* ScaleTo::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    ScaleTo* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (ScaleTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new ScaleTo();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);


    pCopy->initWithDuration(_duration, _endScaleX, _endScaleY);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void ScaleTo::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);
    _startScaleX = pTarget->getScaleX();
    _startScaleY = pTarget->getScaleY();
    _deltaX = _endScaleX - _startScaleX;
    _deltaY = _endScaleY - _startScaleY;
}

void ScaleTo::update(float time)
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

ScaleBy* ScaleBy::create(float duration, float s)
{
    ScaleBy *pScaleBy = new ScaleBy();
    pScaleBy->initWithDuration(duration, s);
    pScaleBy->autorelease();

    return pScaleBy;
}

ScaleBy* ScaleBy::create(float duration, float sx, float sy)
{
    ScaleBy *pScaleBy = new ScaleBy();
    pScaleBy->initWithDuration(duration, sx, sy);
    pScaleBy->autorelease();

    return pScaleBy;
}

ScaleBy* ScaleBy::clone(void) const
{
	// no copy constructor
	auto a = new ScaleBy();
    a->initWithDuration(_duration, _endScaleX, _endScaleY);
	a->autorelease();
	return a;
}

Object* ScaleBy::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    ScaleTo* pCopy = NULL;
    if(pZone && pZone->_copyObject)
    {
        //in case of being called at sub class
        pCopy = (ScaleBy*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new ScaleBy();
        pZone = pNewZone = new Zone(pCopy);
    }

    ScaleTo::copyWithZone(pZone);


    pCopy->initWithDuration(_duration, _endScaleX, _endScaleY);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void ScaleBy::startWithTarget(Node *pTarget)
{
    ScaleTo::startWithTarget(pTarget);
    _deltaX = _startScaleX * _endScaleX - _startScaleX;
    _deltaY = _startScaleY * _endScaleY - _startScaleY;
}

ScaleBy* ScaleBy::reverse() const
{
    return ScaleBy::create(_duration, 1 / _endScaleX, 1 / _endScaleY);
}

//
// Blink
//

Blink* Blink::create(float duration, unsigned int uBlinks)
{
    Blink *pBlink = new Blink();
    pBlink->initWithDuration(duration, uBlinks);
    pBlink->autorelease();

    return pBlink;
}

bool Blink::initWithDuration(float duration, unsigned int uBlinks)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _times = uBlinks;
        return true;
    }

    return false;
}

void Blink::stop()
{
    _target->setVisible(_originalState);
    ActionInterval::stop();
}

void Blink::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);
    _originalState = pTarget->isVisible();
}

Blink* Blink::clone(void) const
{
	// no copy constructor
	auto a = new Blink();
	a->initWithDuration(_duration, (unsigned int)_times);
	a->autorelease();
	return a;
}

Object* Blink::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    Blink* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (Blink*)(pZone->_copyObject);

    }
    else
    {
        pCopy = new Blink();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, (unsigned int)_times);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void Blink::update(float time)
{
    if (_target && ! isDone())
    {
        float slice = 1.0f / _times;
        float m = fmodf(time, slice);
        _target->setVisible(m > slice / 2 ? true : false);
    }
}

Blink* Blink::reverse() const
{
    return Blink::create(_duration, _times);
}

//
// FadeIn
//

FadeIn* FadeIn::create(float d)
{
    FadeIn* pAction = new FadeIn();

    pAction->initWithDuration(d);
    pAction->autorelease();

    return pAction;
}

FadeIn* FadeIn::clone() const
{
	// no copy constructor
	auto a = new FadeIn();
	a->autorelease();
	return a;
}

Object* FadeIn::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    FadeIn* pCopy = NULL;
    if(pZone && pZone->_copyObject)
    {
        //in case of being called at sub class
        pCopy = (FadeIn*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new FadeIn();
        pZone = pNewZone = new Zone(pCopy);
    }
    
    ActionInterval::copyWithZone(pZone);

    CC_SAFE_DELETE(pNewZone);

    return pCopy;
}

void FadeIn::update(float time)
{
    RGBAProtocol *pRGBAProtocol = dynamic_cast<RGBAProtocol*>(_target);
    if (pRGBAProtocol)
    {
        pRGBAProtocol->setOpacity((GLubyte)(255 * time));
    }
    /*_target->setOpacity((GLubyte)(255 * time));*/
}

ActionInterval* FadeIn::reverse() const
{
    return FadeOut::create(_duration);
}

//
// FadeOut
//

FadeOut* FadeOut::create(float d)
{
    FadeOut* pAction = new FadeOut();

    pAction->initWithDuration(d);
    pAction->autorelease();

    return pAction;
}

FadeOut* FadeOut::clone() const
{
	// no copy constructor
	auto a = new FadeOut();
	a->autorelease();
	return a;
}

Object* FadeOut::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    FadeOut* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (FadeOut*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new FadeOut();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);

    CC_SAFE_DELETE(pNewZone);

    return pCopy;
}

void FadeOut::update(float time)
{
    RGBAProtocol *pRGBAProtocol = dynamic_cast<RGBAProtocol*>(_target);
    if (pRGBAProtocol)
    {
        pRGBAProtocol->setOpacity(GLubyte(255 * (1 - time)));
    }
    /*_target->setOpacity(GLubyte(255 * (1 - time)));*/    
}

ActionInterval* FadeOut::reverse() const
{
    return FadeIn::create(_duration);
}

//
// FadeTo
//

FadeTo* FadeTo::create(float duration, GLubyte opacity)
{
    FadeTo *pFadeTo = new FadeTo();
    pFadeTo->initWithDuration(duration, opacity);
    pFadeTo->autorelease();

    return pFadeTo;
}

bool FadeTo::initWithDuration(float duration, GLubyte opacity)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _toOpacity = opacity;
        return true;
    }

    return false;
}

FadeTo* FadeTo::clone() const
{
	// no copy constructor
	auto a = new FadeTo();
	a->initWithDuration(_duration, _toOpacity);
	a->autorelease();
	return a;
}

FadeTo* FadeTo::reverse() const
{
	CCAssert(false, "reverse() not supported in FadeTo");
	return nullptr;
}

Object* FadeTo::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    FadeTo* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (FadeTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new FadeTo();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _toOpacity);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void FadeTo::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);

    RGBAProtocol *pRGBAProtocol = dynamic_cast<RGBAProtocol*>(pTarget);
    if (pRGBAProtocol)
    {
        _fromOpacity = pRGBAProtocol->getOpacity();
    }
    /*_fromOpacity = pTarget->getOpacity();*/
}

void FadeTo::update(float time)
{
    RGBAProtocol *pRGBAProtocol = dynamic_cast<RGBAProtocol*>(_target);
    if (pRGBAProtocol)
    {
        pRGBAProtocol->setOpacity((GLubyte)(_fromOpacity + (_toOpacity - _fromOpacity) * time));
    }
    /*_target->setOpacity((GLubyte)(_fromOpacity + (_toOpacity - _fromOpacity) * time));*/
}

//
// TintTo
//
TintTo* TintTo::create(float duration, GLubyte red, GLubyte green, GLubyte blue)
{
    TintTo *pTintTo = new TintTo();
    pTintTo->initWithDuration(duration, red, green, blue);
    pTintTo->autorelease();

    return pTintTo;
}

bool TintTo::initWithDuration(float duration, GLubyte red, GLubyte green, GLubyte blue)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _to = ccc3(red, green, blue);
        return true;
    }

    return false;
}

TintTo* TintTo::clone() const
{
	// no copy constructor
	auto a = new TintTo();
	a->initWithDuration(_duration, _to.r, _to.g, _to.b);
	a->autorelease();
	return a;
}

TintTo* TintTo::reverse() const
{
	CCAssert(false, "reverse() not supported in TintTo");
	return nullptr;
}

Object* TintTo::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    TintTo* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (TintTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new TintTo();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _to.r, _to.g, _to.b);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void TintTo::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);
    RGBAProtocol *pRGBAProtocol = dynamic_cast<RGBAProtocol*>(_target);
    if (pRGBAProtocol)
    {
        _from = pRGBAProtocol->getColor();
    }
    /*_from = pTarget->getColor();*/
}

void TintTo::update(float time)
{
    RGBAProtocol *pRGBAProtocol = dynamic_cast<RGBAProtocol*>(_target);
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

TintBy* TintBy::create(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue)
{
    TintBy *pTintBy = new TintBy();
    pTintBy->initWithDuration(duration, deltaRed, deltaGreen, deltaBlue);
    pTintBy->autorelease();

    return pTintBy;
}

bool TintBy::initWithDuration(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _deltaR = deltaRed;
        _deltaG = deltaGreen;
        _deltaB = deltaBlue;

        return true;
    }

    return false;
}

TintBy* TintBy::clone() const
{
	// no copy constructor
	auto a = new TintBy();
	a->initWithDuration(_duration, (GLubyte)_deltaR, (GLubyte)_deltaG, (GLubyte)_deltaB);
	a->autorelease();
	return a;
}

Object* TintBy::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    TintBy* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (TintBy*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new TintBy();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, (GLubyte)_deltaR, (GLubyte)_deltaG, (GLubyte)_deltaB);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void TintBy::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);

    RGBAProtocol *pRGBAProtocol = dynamic_cast<RGBAProtocol*>(pTarget);
    if (pRGBAProtocol)
    {
        ccColor3B color = pRGBAProtocol->getColor();
        _fromR = color.r;
        _fromG = color.g;
        _fromB = color.b;
    }    
}

void TintBy::update(float time)
{
    RGBAProtocol *pRGBAProtocol = dynamic_cast<RGBAProtocol*>(_target);
    if (pRGBAProtocol)
    {
        pRGBAProtocol->setColor(ccc3((GLubyte)(_fromR + _deltaR * time),
            (GLubyte)(_fromG + _deltaG * time),
            (GLubyte)(_fromB + _deltaB * time)));
    }    
}

TintBy* TintBy::reverse() const
{
    return TintBy::create(_duration, -_deltaR, -_deltaG, -_deltaB);
}

//
// DelayTime
//
DelayTime* DelayTime::create(float d)
{
    DelayTime* pAction = new DelayTime();

    pAction->initWithDuration(d);
    pAction->autorelease();

    return pAction;
}

DelayTime* DelayTime::clone() const
{
	// no copy constructor
	auto a = new DelayTime();
	a->autorelease();
	return a;
}

Object* DelayTime::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    DelayTime* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (DelayTime*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new DelayTime();
        pZone = pNewZone = new Zone(pCopy);
    }
    
    ActionInterval::copyWithZone(pZone);

    CC_SAFE_DELETE(pNewZone);

    return pCopy;
}

void DelayTime::update(float time)
{
    CC_UNUSED_PARAM(time);
    return;
}

DelayTime* DelayTime::reverse() const
{
    return DelayTime::create(_duration);
}

//
// ReverseTime
//

ReverseTime* ReverseTime::create(FiniteTimeAction *pAction)
{
    // casting to prevent warnings
    ReverseTime *pReverseTime = new ReverseTime();
    pReverseTime->initWithAction( pAction->clone() );
    pReverseTime->autorelease();

    return pReverseTime;
}

bool ReverseTime::initWithAction(FiniteTimeAction *pAction)
{
    CCAssert(pAction != NULL, "");
    CCAssert(pAction != _other, "");

    if (ActionInterval::initWithDuration(pAction->getDuration()))
    {
        // Don't leak if action is reused
        CC_SAFE_RELEASE(_other);

        _other = pAction;
        pAction->retain();

        return true;
    }

    return false;
}

ReverseTime* ReverseTime::clone() const
{
	// no copy constructor
	auto a = new ReverseTime();
	a->initWithAction( _other->clone() );
	a->autorelease();
	return a;
}

Object* ReverseTime::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    ReverseTime* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (ReverseTime*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new ReverseTime();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);

    pCopy->initWithAction(_other->clone());

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

ReverseTime::ReverseTime() : _other(NULL) 
{

}

ReverseTime::~ReverseTime(void)
{
    CC_SAFE_RELEASE(_other);
}

void ReverseTime::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);
    _other->startWithTarget(pTarget);
}

void ReverseTime::stop(void)
{
    _other->stop();
    ActionInterval::stop();
}

void ReverseTime::update(float time)
{
    if (_other)
    {
        _other->update(1 - time);
    }
}

ReverseTime* ReverseTime::reverse() const
{
    return (ReverseTime*)_other->clone();
}

//
// Animate
//
Animate* Animate::create(Animation *pAnimation)
{
    Animate *pAnimate = new Animate();
    pAnimate->initWithAnimation(pAnimation);
    pAnimate->autorelease();

    return pAnimate;
}

bool Animate::initWithAnimation(Animation *pAnimation)
{
    CCAssert( pAnimation!=NULL, "Animate: argument Animation must be non-NULL");

    float singleDuration = pAnimation->getDuration();

    if ( ActionInterval::initWithDuration(singleDuration * pAnimation->getLoops() ) ) 
    {
        _nextFrame = 0;
        setAnimation(pAnimation);
        _origFrame = NULL;
        _executedLoops = 0;

        _splitTimes->reserve(pAnimation->getFrames()->count());

        float accumUnitsOfTime = 0;
        float newUnitOfTimeValue = singleDuration / pAnimation->getTotalDelayUnits();

        Array* pFrames = pAnimation->getFrames();
        CCARRAY_VERIFY_TYPE(pFrames, AnimationFrame*);

        Object* pObj = NULL;
        CCARRAY_FOREACH(pFrames, pObj)
        {
            AnimationFrame* frame = (AnimationFrame*)pObj;
            float value = (accumUnitsOfTime * newUnitOfTimeValue) / singleDuration;
            accumUnitsOfTime += frame->getDelayUnits();
            _splitTimes->push_back(value);
        }    
        return true;
    }
    return false;
}

Animate* Animate::clone() const
{
	// no copy constructor
	auto a = new Animate();
	a->initWithAnimation(_animation->clone());
	a->autorelease();
	return a;
}

Object* Animate::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    Animate* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (Animate*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new Animate();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);

    pCopy->initWithAnimation(_animation->clone());

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

Animate::Animate()
: _animation(NULL)
, _splitTimes(new std::vector<float>)
, _nextFrame(0)
, _origFrame(NULL)
, _executedLoops(0)
{

}

Animate::~Animate()
{
    CC_SAFE_RELEASE(_animation);
    CC_SAFE_RELEASE(_origFrame);
    CC_SAFE_DELETE(_splitTimes);
}

void Animate::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);
    Sprite *pSprite = (Sprite*)(pTarget);

    CC_SAFE_RELEASE(_origFrame);

    if (_animation->getRestoreOriginalFrame())
    {
        _origFrame = pSprite->displayFrame();
        _origFrame->retain();
    }
    _nextFrame = 0;
    _executedLoops = 0;
}

void Animate::stop(void)
{
    if (_animation->getRestoreOriginalFrame() && _target)
    {
        ((Sprite*)(_target))->setDisplayFrame(_origFrame);
    }

    ActionInterval::stop();
}

void Animate::update(float t)
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

    Array* frames = _animation->getFrames();
    unsigned int numberOfFrames = frames->count();
    SpriteFrame *frameToDisplay = NULL;

    for( unsigned int i=_nextFrame; i < numberOfFrames; i++ ) {
        float splitTime = _splitTimes->at(i);

        if( splitTime <= t ) {
            AnimationFrame* frame = (AnimationFrame*)frames->objectAtIndex(i);
            frameToDisplay = frame->getSpriteFrame();
            ((Sprite*)_target)->setDisplayFrame(frameToDisplay);

            Dictionary* dict = frame->getUserInfo();
            if( dict )
            {
                //TODO: [[NSNotificationCenter defaultCenter] postNotificationName:AnimationFrameDisplayedNotification object:target_ userInfo:dict];
            }
            _nextFrame = i+1;
        }
        // Issue 1438. Could be more than one frame per tick, due to low frame rate or frame delta < 1/FPS
        else {
            break;
        }
    }
}

Animate* Animate::reverse() const
{
    Array* pOldArray = _animation->getFrames();
    Array* pNewArray = Array::createWithCapacity(pOldArray->count());
   
    CCARRAY_VERIFY_TYPE(pOldArray, AnimationFrame*);

    if (pOldArray->count() > 0)
    {
        Object* pObj = NULL;
        CCARRAY_FOREACH_REVERSE(pOldArray, pObj)
        {
            AnimationFrame* pElement = (AnimationFrame*)pObj;
            if (! pElement)
            {
                break;
            }

            pNewArray->addObject(pElement->clone());
        }
    }

    Animation *newAnim = Animation::create(pNewArray, _animation->getDelayPerUnit(), _animation->getLoops());
    newAnim->setRestoreOriginalFrame(_animation->getRestoreOriginalFrame());
    return Animate::create(newAnim);
}

// TargetedAction

TargetedAction::TargetedAction()
: _forcedTarget(NULL)
, _action(NULL)
{

}

TargetedAction::~TargetedAction()
{
    CC_SAFE_RELEASE(_forcedTarget);
    CC_SAFE_RELEASE(_action);
}

TargetedAction* TargetedAction::create(Node* pTarget, FiniteTimeAction* pAction)
{
    TargetedAction* p = new TargetedAction();
    p->initWithTarget(pTarget, pAction);
    p->autorelease();
    return p;
}


bool TargetedAction::initWithTarget(Node* pTarget, FiniteTimeAction* pAction)
{
    if(ActionInterval::initWithDuration(pAction->getDuration()))
    {
        CC_SAFE_RETAIN(pTarget);
        _forcedTarget = pTarget;
        CC_SAFE_RETAIN(pAction);
        _action = pAction;
        return true;
    }
    return false;
}

TargetedAction* TargetedAction::clone() const
{
	// no copy constructor	
	auto a = new TargetedAction();
    // win32 : use the _other's copy object.
	a->initWithTarget(_forcedTarget, _action->clone());
	a->autorelease();
	return a;
}

TargetedAction* TargetedAction::reverse(void) const
{
	// no reverse for this action, just clone it
	return this->clone();
}

Object* TargetedAction::copyWithZone(Zone* pZone)
{
    Zone* pNewZone = NULL;
    TargetedAction* pRet = NULL;
    if(pZone && pZone->_copyObject) //in case of being called at sub class
    {
        pRet = (TargetedAction*)(pZone->_copyObject);
    }
    else
    {
        pRet = new TargetedAction();
        pZone = pNewZone = new Zone(pRet);
    }
    ActionInterval::copyWithZone(pZone);
    // win32 : use the _other's copy object.
    pRet->initWithTarget(_forcedTarget, _action->clone());
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void TargetedAction::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);
    _action->startWithTarget(_forcedTarget);
}

void TargetedAction::stop(void)
{
    _action->stop();
}

void TargetedAction::update(float time)
{
    _action->update(time);
}

NS_CC_END
