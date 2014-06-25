/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#include "2d/CCActionInterval.h"
#include "2d/CCSprite.h"
#include "2d/CCNode.h"
#include "CCStdC.h"
#include "2d/CCActionInstant.h"
#include "base/CCDirector.h"
#include "base/CCEventCustom.h"

#include <stdarg.h>

NS_CC_BEGIN

// Extra action for making a Sequence or Spawn when only adding one action to it.
class ExtraAction : public FiniteTimeAction
{
public:
    static ExtraAction* create();
    virtual ExtraAction* clone() const;
    virtual ExtraAction* reverse(void) const;
    virtual void update(float time);
    virtual void step(float dt);
};

ExtraAction* ExtraAction::create()
{
    ExtraAction* ret = new ExtraAction();
    if (ret)
    {
        ret->autorelease();
    }
    return ret;
}
ExtraAction* ExtraAction::clone() const
{
	// no copy constructor
	auto a = new ExtraAction();
	a->autorelease();
	return a;
}

ExtraAction* ExtraAction::reverse() const
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

bool ActionInterval::isDone() const
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
    CCASSERT(0, "");
}

float ActionInterval::getAmplitudeRate()
{
    // Abstract class needs implementation
    CCASSERT(0, "");

    return 0;
}

void ActionInterval::startWithTarget(Node *target)
{
    FiniteTimeAction::startWithTarget(target);
    _elapsed = 0.0f;
    _firstTick = true;
}

//
// Sequence
//

Sequence* Sequence::createWithTwoActions(FiniteTimeAction *actionOne, FiniteTimeAction *actionTwo)
{
    Sequence *sequence = new Sequence();
    sequence->initWithTwoActions(actionOne, actionTwo);
    sequence->autorelease();

    return sequence;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
Sequence* Sequence::variadicCreate(FiniteTimeAction *action1, ...)
{
    va_list params;
    va_start(params, action1);

    Sequence *ret = Sequence::createWithVariableList(action1, params);

    va_end(params);
    
    return ret;
}
#else
Sequence* Sequence::create(FiniteTimeAction *action1, ...)
{
    va_list params;
    va_start(params, action1);

    Sequence *ret = Sequence::createWithVariableList(action1, params);

    va_end(params);
    
    return ret;
}
#endif

Sequence* Sequence::createWithVariableList(FiniteTimeAction *action1, va_list args)
{
    FiniteTimeAction *now;
    FiniteTimeAction *prev = action1;
    bool bOneAction = true;

    while (action1)
    {
        now = va_arg(args, FiniteTimeAction*);
        if (now)
        {
            prev = createWithTwoActions(prev, now);
            bOneAction = false;
        }
        else
        {
            // If only one action is added to Sequence, make up a Sequence by adding a simplest finite time action.
            if (bOneAction)
            {
                prev = createWithTwoActions(prev, ExtraAction::create());
            }
            break;
        }
    }
    
    return ((Sequence*)prev);
}

Sequence* Sequence::create(const Vector<FiniteTimeAction*>& arrayOfActions)
{
    Sequence* ret = nullptr;
    do 
    {
        auto count = arrayOfActions.size();
        CC_BREAK_IF(count == 0);

        auto prev = arrayOfActions.at(0);

        if (count > 1)
        {
            for (int i = 1; i < count; ++i)
            {
                prev = createWithTwoActions(prev, arrayOfActions.at(i));
            }
        }
        else
        {
            // If only one action is added to Sequence, make up a Sequence by adding a simplest finite time action.
            prev = createWithTwoActions(prev, ExtraAction::create());
        }
        ret = static_cast<Sequence*>(prev);
    }while (0);
    return ret;
}

bool Sequence::initWithTwoActions(FiniteTimeAction *actionOne, FiniteTimeAction *actionTwo)
{
    CCASSERT(actionOne != nullptr, "");
    CCASSERT(actionTwo != nullptr, "");

    float d = actionOne->getDuration() + actionTwo->getDuration();
    ActionInterval::initWithDuration(d);

    _actions[0] = actionOne;
    actionOne->retain();

    _actions[1] = actionTwo;
    actionTwo->retain();

    return true;
}

Sequence* Sequence::clone() const
{
	// no copy constructor
	auto a = new Sequence();
    a->initWithTwoActions(_actions[0]->clone(), _actions[1]->clone() );
	a->autorelease();
	return a;
}

Sequence::~Sequence(void)
{
    CC_SAFE_RELEASE(_actions[0]);
    CC_SAFE_RELEASE(_actions[1]);
}

void Sequence::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
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

Repeat* Repeat::create(FiniteTimeAction *action, unsigned int times)
{
    Repeat* repeat = new Repeat();
    repeat->initWithAction(action, times);
    repeat->autorelease();

    return repeat;
}

bool Repeat::initWithAction(FiniteTimeAction *action, unsigned int times)
{
    float d = action->getDuration() * times;

    if (ActionInterval::initWithDuration(d))
    {
        _times = times;
        _innerAction = action;
        action->retain();

        _actionInstant = dynamic_cast<ActionInstant*>(action) ? true : false;
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
	a->initWithAction( _innerAction->clone(), _times );
	a->autorelease();
	return a;
}

Repeat::~Repeat(void)
{
    CC_SAFE_RELEASE(_innerAction);
}

void Repeat::startWithTarget(Node *target)
{
    _total = 0;
    _nextDt = _innerAction->getDuration()/_duration;
    ActionInterval::startWithTarget(target);
    _innerAction->startWithTarget(target);
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
            _nextDt = _innerAction->getDuration()/_duration * (_total+1);
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

bool Repeat::isDone(void) const
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

RepeatForever *RepeatForever::create(ActionInterval *action)
{
    RepeatForever *ret = new RepeatForever();
    if (ret && ret->initWithAction(action))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool RepeatForever::initWithAction(ActionInterval *action)
{
    CCASSERT(action != nullptr, "");
    action->retain();
    _innerAction = action;
    return true;
}

RepeatForever *RepeatForever::clone() const
{
	// no copy constructor	
	auto a = new RepeatForever();
	a->initWithAction(_innerAction->clone());
	a->autorelease();
	return a;
}

void RepeatForever::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);
    _innerAction->startWithTarget(target);
}

void RepeatForever::step(float dt)
{
    _innerAction->step(dt);
    if (_innerAction->isDone())
    {
        float diff = _innerAction->getElapsed() - _innerAction->getDuration();
        if (diff > _innerAction->getDuration())
            diff = fmodf(diff, _innerAction->getDuration());
        _innerAction->startWithTarget(_target);
        // to prevent jerk. issue #390, 1247
        _innerAction->step(0.0f);
        _innerAction->step(diff);
    }
}

bool RepeatForever::isDone() const
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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
Spawn* Spawn::variadicCreate(FiniteTimeAction *action1, ...)
{
    va_list params;
    va_start(params, action1);

    Spawn *ret = Spawn::createWithVariableList(action1, params);

    va_end(params);
    
    return ret;
}
#else
Spawn* Spawn::create(FiniteTimeAction *action1, ...)
{
    va_list params;
    va_start(params, action1);

    Spawn *ret = Spawn::createWithVariableList(action1, params);

    va_end(params);
    
    return ret;
}
#endif

Spawn* Spawn::createWithVariableList(FiniteTimeAction *action1, va_list args)
{
    FiniteTimeAction *now;
    FiniteTimeAction *prev = action1;
    bool oneAction = true;

    while (action1)
    {
        now = va_arg(args, FiniteTimeAction*);
        if (now)
        {
            prev = createWithTwoActions(prev, now);
            oneAction = false;
        }
        else
        {
            // If only one action is added to Spawn, make up a Spawn by adding a simplest finite time action.
            if (oneAction)
            {
                prev = createWithTwoActions(prev, ExtraAction::create());
            }
            break;
        }
    }

    return ((Spawn*)prev);
}

Spawn* Spawn::create(const Vector<FiniteTimeAction*>& arrayOfActions)
{
    Spawn* ret = nullptr;
    do 
    {
        auto count = arrayOfActions.size();
        CC_BREAK_IF(count == 0);
        auto prev = arrayOfActions.at(0);
        if (count > 1)
        {
            for (int i = 1; i < arrayOfActions.size(); ++i)
            {
                prev = createWithTwoActions(prev, arrayOfActions.at(i));
            }
        }
        else
        {
            // If only one action is added to Spawn, make up a Spawn by adding a simplest finite time action.
            prev = createWithTwoActions(prev, ExtraAction::create());
        }
        ret = static_cast<Spawn*>(prev);
    }while (0);

    return ret;
}

Spawn* Spawn::createWithTwoActions(FiniteTimeAction *action1, FiniteTimeAction *action2)
{
    Spawn *spawn = new Spawn();
    spawn->initWithTwoActions(action1, action2);
    spawn->autorelease();

    return spawn;
}

bool Spawn::initWithTwoActions(FiniteTimeAction *action1, FiniteTimeAction *action2)
{
    CCASSERT(action1 != nullptr, "");
    CCASSERT(action2 != nullptr, "");

    bool ret = false;

    float d1 = action1->getDuration();
    float d2 = action2->getDuration();

    if (ActionInterval::initWithDuration(MAX(d1, d2)))
    {
        _one = action1;
        _two = action2;

        if (d1 > d2)
        {
            _two = Sequence::createWithTwoActions(action2, DelayTime::create(d1 - d2));
        } 
        else if (d1 < d2)
        {
            _one = Sequence::createWithTwoActions(action1, DelayTime::create(d2 - d1));
        }

        _one->retain();
        _two->retain();

        ret = true;
    }

    return ret;
}

Spawn* Spawn::clone(void) const
{
	// no copy constructor	
	auto a = new Spawn();
    a->initWithTwoActions(_one->clone(), _two->clone());

	a->autorelease();
	return a;
}

Spawn::~Spawn(void)
{
    CC_SAFE_RELEASE(_one);
    CC_SAFE_RELEASE(_two);
}

void Spawn::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    _one->startWithTarget(target);
    _two->startWithTarget(target);
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

RotateTo* RotateTo::create(float duration, float deltaAngle)
{
    RotateTo* rotateTo = new RotateTo();
    rotateTo->initWithDuration(duration, deltaAngle);
    rotateTo->autorelease();

    return rotateTo;
}

bool RotateTo::initWithDuration(float duration, float deltaAngle)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _dstAngleX = _dstAngleY = deltaAngle;
        return true;
    }

    return false;
}

RotateTo* RotateTo::create(float duration, float deltaAngleX, float deltaAngleY)
{
    RotateTo* rotateTo = new RotateTo();
    rotateTo->initWithDuration(duration, deltaAngleX, deltaAngleY);
    rotateTo->autorelease();
    
    return rotateTo;
}

bool RotateTo::initWithDuration(float duration, float deltaAngleX, float deltaAngleY)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _dstAngleX = deltaAngleX;
        _dstAngleY = deltaAngleY;
        
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

void RotateTo::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    
    // Calculate X
    _startAngleX = target->getRotationSkewX();
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
    _startAngleY = _target->getRotationSkewY();

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
#if CC_USE_PHYSICS
        if (_target->getPhysicsBody() != nullptr && _startAngleX == _startAngleY && _diffAngleX == _diffAngleY)
        {
            _target->setRotation(_startAngleX + _diffAngleX * time);
        }
        else
        {
            // _startAngleX != _startAngleY || _diffAngleX != _diffAngleY
            if (_target->getPhysicsBody() != nullptr)
            {
                CCLOG("RotateTo WARNING: PhysicsBody doesn't support skew rotation");
            }
            
            _target->setRotationSkewX(_startAngleX + _diffAngleX * time);
            _target->setRotationSkewY(_startAngleY + _diffAngleY * time);
        }
#else
        _target->setRotationSkewX(_startAngleX + _diffAngleX * time);
        _target->setRotationSkewY(_startAngleY + _diffAngleY * time);
#endif // CC_USE_PHYSICS
    }
}

RotateTo *RotateTo::reverse() const
{
	CCASSERT(false, "RotateTo doesn't support the 'reverse' method");
	return nullptr;
}

//
// RotateBy
//

RotateBy* RotateBy::create(float duration, float deltaAngle)
{
    RotateBy *rotateBy = new RotateBy();
    rotateBy->initWithDuration(duration, deltaAngle);
    rotateBy->autorelease();

    return rotateBy;
}

RotateBy* RotateBy::create(float duration, float deltaAngleX, float deltaAngleY)
{
    RotateBy *rotateBy = new RotateBy();
    rotateBy->initWithDuration(duration, deltaAngleX, deltaAngleY);
    rotateBy->autorelease();
    
    return rotateBy;
}

RotateBy* RotateBy::create(float duration, const Vec3& deltaAngle3D)
{
    RotateBy *rotateBy = new RotateBy();
    rotateBy->initWithDuration(duration, deltaAngle3D);
    rotateBy->autorelease();

    return rotateBy;
}

RotateBy::RotateBy()
: _is3D(false)
{
}

bool RotateBy::initWithDuration(float duration, float deltaAngle)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _angleZ_X = _angleZ_Y = deltaAngle;
        return true;
    }

    return false;
}

bool RotateBy::initWithDuration(float duration, float deltaAngleX, float deltaAngleY)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _angleZ_X = deltaAngleX;
        _angleZ_Y = deltaAngleY;
        return true;
    }
    
    return false;
}

bool RotateBy::initWithDuration(float duration, const Vec3& deltaAngle3D)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _angle3D = deltaAngle3D;
        _is3D = true;
        return true;
    }

    return false;
}


RotateBy* RotateBy::clone() const
{
	// no copy constructor
	auto a = new RotateBy();
    if(_is3D)
        a->initWithDuration(_duration, _angle3D);
    else
        a->initWithDuration(_duration, _angleZ_X, _angleZ_Y);
	a->autorelease();
	return a;
}

void RotateBy::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    if(_is3D)
    {
        _startAngle3D = target->getRotation3D();
    }
    else
    {
        _startAngleZ_X = target->getRotationSkewX();
        _startAngleZ_Y = target->getRotationSkewY();
    }
}

void RotateBy::update(float time)
{
    // XXX: shall I add % 360
    if (_target)
    {
        if(_is3D)
        {
            Vec3 v;
            v.x = _startAngle3D.x + _angle3D.x * time;
            v.y = _startAngle3D.y + _angle3D.y * time;
            v.z = _startAngle3D.z + _angle3D.z * time;
            _target->setRotation3D(v);
        }
        else
        {
#if CC_USE_PHYSICS
            if (_target->getPhysicsBody() != nullptr && _startAngleZ_X == _startAngleZ_Y && _angleZ_X == _angleZ_Y)
            {
                _target->setRotation(_startAngleZ_X + _angleZ_X * time);
            }
            else
            {
                // _startAngleZ_X != _startAngleZ_Y || _angleZ_X != _angleZ_Y
                if (_target->getPhysicsBody() != nullptr)
                {
                    CCLOG("RotateBy WARNING: PhysicsBody doesn't support skew rotation");
                }
                
                _target->setRotationSkewX(_startAngleZ_X + _angleZ_X * time);
                _target->setRotationSkewY(_startAngleZ_Y + _angleZ_Y * time);
            }
#else
            _target->setRotationSkewX(_startAngleZ_X + _angleZ_X * time);
            _target->setRotationSkewY(_startAngleZ_Y + _angleZ_Y * time);
#endif // CC_USE_PHYSICS
        }
    }
}

RotateBy* RotateBy::reverse() const
{
    if(_is3D)
    {
        Vec3 v;
        v.x = - _angle3D.x;
        v.y = - _angle3D.y;
        v.z = - _angle3D.z;
        return RotateBy::create(_duration, v);
    }
    return RotateBy::create(_duration, -_angleZ_X, -_angleZ_Y);
}

//
// MoveBy
//

MoveBy* MoveBy::create(float duration, const Vec2& deltaPosition)
{
    MoveBy *ret = new MoveBy();
    ret->initWithDuration(duration, deltaPosition);
    ret->autorelease();

    return ret;
}

bool MoveBy::initWithDuration(float duration, const Vec2& deltaPosition)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _positionDelta = deltaPosition;
        return true;
    }

    return false;
}

MoveBy* MoveBy::clone() const
{
	// no copy constructor
	auto a = new MoveBy();
    a->initWithDuration(_duration, _positionDelta);
	a->autorelease();
	return a;
}

void MoveBy::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    _previousPosition = _startPosition = target->getPosition();
}

MoveBy* MoveBy::reverse() const
{
    return MoveBy::create(_duration, Vec2( -_positionDelta.x, -_positionDelta.y));
}


void MoveBy::update(float t)
{
    if (_target)
    {
#if CC_ENABLE_STACKABLE_ACTIONS
        Vec2 currentPos = _target->getPosition();
        Vec2 diff = currentPos - _previousPosition;
        _startPosition = _startPosition + diff;
        Vec2 newPos =  _startPosition + (_positionDelta * t);
        _target->setPosition(newPos);
        _previousPosition = newPos;
#else
        _target->setPosition(_startPosition + _positionDelta * t);
#endif // CC_ENABLE_STACKABLE_ACTIONS
    }
}

//
// MoveTo
//

MoveTo* MoveTo::create(float duration, const Vec2& position)
{
    MoveTo *ret = new MoveTo();
    ret->initWithDuration(duration, position);
    ret->autorelease();

    return ret;
}

bool MoveTo::initWithDuration(float duration, const Vec2& position)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _endPosition = position;
        return true;
    }

    return false;
}

MoveTo* MoveTo::clone() const
{
	// no copy constructor
	auto a = new MoveTo();
    a->initWithDuration(_duration, _endPosition);
	a->autorelease();
	return a;
}

void MoveTo::startWithTarget(Node *target)
{
    MoveBy::startWithTarget(target);
    _positionDelta = _endPosition - target->getPosition();
}


//
// SkewTo
//
SkewTo* SkewTo::create(float t, float sx, float sy)
{
    SkewTo *skewTo = new SkewTo();
    if (skewTo)
    {
        if (skewTo->initWithDuration(t, sx, sy))
        {
            skewTo->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(skewTo);
        }
    }

    return skewTo;
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

SkewTo* SkewTo::clone() const
{
	// no copy constructor
	auto a = new SkewTo();
	a->initWithDuration(_duration, _endSkewX, _endSkewY);
	a->autorelease();
	return a;
}

SkewTo* SkewTo::reverse() const
{
	CCASSERT(false, "reverse() not supported in SkewTo");
	return nullptr;
}

void SkewTo::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);

    _startSkewX = target->getSkewX();

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

    _startSkewY = target->getSkewY();

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
    SkewBy *skewBy = new SkewBy();
    if (skewBy)
    {
        if (skewBy->initWithDuration(t, sx, sy))
        {
            skewBy->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(skewBy);
        }
    }

    return skewBy;
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
    bool ret = false;

    if (SkewTo::initWithDuration(t, deltaSkewX, deltaSkewY))
    {
        _skewX = deltaSkewX;
        _skewY = deltaSkewY;

        ret = true;
    }

    return ret;
}

void SkewBy::startWithTarget(Node *target)
{
    SkewTo::startWithTarget(target);
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

JumpBy* JumpBy::create(float duration, const Vec2& position, float height, int jumps)
{
    JumpBy *jumpBy = new JumpBy();
    jumpBy->initWithDuration(duration, position, height, jumps);
    jumpBy->autorelease();

    return jumpBy;
}

bool JumpBy::initWithDuration(float duration, const Vec2& position, float height, int jumps)
{
    CCASSERT(jumps>=0, "Number of jumps must be >= 0");
    
    if (ActionInterval::initWithDuration(duration) && jumps>=0)
    {
        _delta = position;
        _height = height;
        _jumps = jumps;

        return true;
    }

    return false;
}

JumpBy* JumpBy::clone() const
{
	// no copy constructor
	auto a = new JumpBy();
	a->initWithDuration(_duration, _delta, _height, _jumps);
	a->autorelease();
	return a;
}

void JumpBy::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    _previousPos = _startPosition = target->getPosition();
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
        Vec2 currentPos = _target->getPosition();

        Vec2 diff = currentPos - _previousPos;
        _startPosition = diff + _startPosition;

        Vec2 newPos = _startPosition + Vec2(x,y);
        _target->setPosition(newPos);

        _previousPos = newPos;
#else
        _target->setPosition(_startPosition + Vec2(x,y));
#endif // !CC_ENABLE_STACKABLE_ACTIONS
    }
}

JumpBy* JumpBy::reverse() const
{
    return JumpBy::create(_duration, Vec2(-_delta.x, -_delta.y),
        _height, _jumps);
}

//
// JumpTo
//

JumpTo* JumpTo::create(float duration, const Vec2& position, float height, int jumps)
{
    JumpTo *jumpTo = new JumpTo();
    jumpTo->initWithDuration(duration, position, height, jumps);
    jumpTo->autorelease();

    return jumpTo;
}

JumpTo* JumpTo::clone() const
{
	// no copy constructor
	auto a = new JumpTo();
    a->initWithDuration(_duration, _delta, _height, _jumps);
	a->autorelease();
	return a;
}

JumpTo* JumpTo::reverse() const
{
	CCASSERT(false, "reverse() not supported in JumpTo");
	return nullptr;
}

void JumpTo::startWithTarget(Node *target)
{
    JumpBy::startWithTarget(target);
    _delta = Vec2(_delta.x - _startPosition.x, _delta.y - _startPosition.y);
}

// Bezier cubic formula:
//    ((1 - t) + t)3 = 1 
// Expands to ...
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
    BezierBy *bezierBy = new BezierBy();
    bezierBy->initWithDuration(t, c);
    bezierBy->autorelease();

    return bezierBy;
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

void BezierBy::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    _previousPosition = _startPosition = target->getPosition();
}

BezierBy* BezierBy::clone() const
{
	// no copy constructor
	auto a = new BezierBy();
	a->initWithDuration(_duration, _config);
	a->autorelease();
	return a;
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
        Vec2 currentPos = _target->getPosition();
        Vec2 diff = currentPos - _previousPosition;
        _startPosition = _startPosition + diff;

        Vec2 newPos = _startPosition + Vec2(x,y);
        _target->setPosition(newPos);

        _previousPosition = newPos;
#else
        _target->setPosition( _startPosition + Vec2(x,y));
#endif // !CC_ENABLE_STACKABLE_ACTIONS
    }
}

BezierBy* BezierBy::reverse() const
{
    ccBezierConfig r;

    r.endPosition = -_config.endPosition;
    r.controlPoint_1 = _config.controlPoint_2 + (-_config.endPosition);
    r.controlPoint_2 = _config.controlPoint_1 + (-_config.endPosition);

    BezierBy *action = BezierBy::create(_duration, r);
    return action;
}

//
// BezierTo
//

BezierTo* BezierTo::create(float t, const ccBezierConfig& c)
{
    BezierTo *bezierTo = new BezierTo();
    bezierTo->initWithDuration(t, c);
    bezierTo->autorelease();

    return bezierTo;
}

bool BezierTo::initWithDuration(float t, const ccBezierConfig &c)
{
    if (ActionInterval::initWithDuration(t))
    {
        _toConfig = c;
        return true;
    }
    
    return false;
}

BezierTo* BezierTo::clone() const
{
	// no copy constructor
	auto a = new BezierTo();
	a->initWithDuration(_duration, _toConfig);
	a->autorelease();
	return a;
}

void BezierTo::startWithTarget(Node *target)
{
    BezierBy::startWithTarget(target);
    _config.controlPoint_1 = _toConfig.controlPoint_1 - _startPosition;
    _config.controlPoint_2 = _toConfig.controlPoint_2 - _startPosition;
    _config.endPosition = _toConfig.endPosition - _startPosition;
}

BezierTo* BezierTo::reverse() const
{
	CCASSERT(false, "CCBezierTo doesn't support the 'reverse' method");
	return nullptr;
}


//
// ScaleTo
//
ScaleTo* ScaleTo::create(float duration, float s)
{
    ScaleTo *scaleTo = new ScaleTo();
    scaleTo->initWithDuration(duration, s);
    scaleTo->autorelease();

    return scaleTo;
}

ScaleTo* ScaleTo::create(float duration, float sx, float sy)
{
    ScaleTo *scaleTo = new ScaleTo();
    scaleTo->initWithDuration(duration, sx, sy);
    scaleTo->autorelease();

    return scaleTo;
}

ScaleTo* ScaleTo::create(float duration, float sx, float sy, float sz)
{
    ScaleTo *scaleTo = new ScaleTo();
    scaleTo->initWithDuration(duration, sx, sy, sz);
    scaleTo->autorelease();

    return scaleTo;
}

bool ScaleTo::initWithDuration(float duration, float s)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _endScaleX = s;
        _endScaleY = s;
        _endScaleZ = s;

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
        _endScaleZ = 1.f;

        return true;
    }

    return false;
}

bool ScaleTo::initWithDuration(float duration, float sx, float sy, float sz)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _endScaleX = sx;
        _endScaleY = sy;
        _endScaleZ = sz;

        return true;
    }

    return false;
}

ScaleTo* ScaleTo::clone() const
{
	// no copy constructor
	auto a = new ScaleTo();
	a->initWithDuration(_duration, _endScaleX, _endScaleY, _endScaleZ);
	a->autorelease();
	return a;
}

ScaleTo* ScaleTo::reverse() const
{
	CCASSERT(false, "reverse() not supported in ScaleTo");
	return nullptr;
}


void ScaleTo::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    _startScaleX = target->getScaleX();
    _startScaleY = target->getScaleY();
    _startScaleZ = target->getScaleZ();
    _deltaX = _endScaleX - _startScaleX;
    _deltaY = _endScaleY - _startScaleY;
    _deltaZ = _endScaleZ - _startScaleZ;
}

void ScaleTo::update(float time)
{
    if (_target)
    {
        _target->setScaleX(_startScaleX + _deltaX * time);
        _target->setScaleY(_startScaleY + _deltaY * time);
        _target->setScaleZ(_startScaleZ + _deltaZ * time);
    }
}

//
// ScaleBy
//

ScaleBy* ScaleBy::create(float duration, float s)
{
    ScaleBy *scaleBy = new ScaleBy();
    scaleBy->initWithDuration(duration, s);
    scaleBy->autorelease();

    return scaleBy;
}

ScaleBy* ScaleBy::create(float duration, float sx, float sy)
{
    ScaleBy *scaleBy = new ScaleBy();
    scaleBy->initWithDuration(duration, sx, sy, 1.f);
    scaleBy->autorelease();

    return scaleBy;
}

ScaleBy* ScaleBy::create(float duration, float sx, float sy, float sz)
{
    ScaleBy *scaleBy = new ScaleBy();
    scaleBy->initWithDuration(duration, sx, sy, sz);
    scaleBy->autorelease();

    return scaleBy;
}

ScaleBy* ScaleBy::clone() const
{
	// no copy constructor
	auto a = new ScaleBy();
    a->initWithDuration(_duration, _endScaleX, _endScaleY, _endScaleZ);
	a->autorelease();
	return a;
}

void ScaleBy::startWithTarget(Node *target)
{
    ScaleTo::startWithTarget(target);
    _deltaX = _startScaleX * _endScaleX - _startScaleX;
    _deltaY = _startScaleY * _endScaleY - _startScaleY;
    _deltaZ = _startScaleZ * _endScaleZ - _startScaleZ;
}

ScaleBy* ScaleBy::reverse() const
{
    return ScaleBy::create(_duration, 1 / _endScaleX, 1 / _endScaleY, 1/ _endScaleZ);
}

//
// Blink
//

Blink* Blink::create(float duration, int blinks)
{
    Blink *blink = new Blink();
    blink->initWithDuration(duration, blinks);
    blink->autorelease();

    return blink;
}

bool Blink::initWithDuration(float duration, int blinks)
{
    CCASSERT(blinks>=0, "blinks should be >= 0");
    
    if (ActionInterval::initWithDuration(duration) && blinks>=0)
    {
        _times = blinks;
        return true;
    }

    return false;
}

void Blink::stop()
{
    _target->setVisible(_originalState);
    ActionInterval::stop();
}

void Blink::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    _originalState = target->isVisible();
}

Blink* Blink::clone(void) const
{
	// no copy constructor
	auto a = new Blink();
	a->initWithDuration(_duration, _times);
	a->autorelease();
	return a;
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
    FadeIn* action = new FadeIn();

    action->initWithDuration(d,255.0f);
    action->autorelease();

    return action;
}

FadeIn* FadeIn::clone() const
{
	// no copy constructor
	auto a = new FadeIn();
    a->initWithDuration(_duration,255.0f);
	a->autorelease();
	return a;
}

void FadeIn::setReverseAction(cocos2d::FadeTo *ac)
{
    _reverseAction = ac;
}


FadeTo* FadeIn::reverse() const
{
    auto action = FadeOut::create(_duration);
    action->setReverseAction(const_cast<FadeIn*>(this));
    return action;
    
}

void FadeIn::startWithTarget(cocos2d::Node *target)
{
    ActionInterval::startWithTarget(target);
    
    if (nullptr != _reverseAction) {
        this->_toOpacity = this->_reverseAction->_fromOpacity;
    }else{
        _toOpacity = 255.0f;
    }
    
    if (target) {
        _fromOpacity = target->getOpacity();
    }
}



//
// FadeOut
//

FadeOut* FadeOut::create(float d)
{
    FadeOut* action = new FadeOut();

    action->initWithDuration(d,0.0f);
    action->autorelease();

    return action;
}

FadeOut* FadeOut::clone() const
{
	// no copy constructor
	auto a = new FadeOut();
    a->initWithDuration(_duration,0.0f);
	a->autorelease();
	return a;
}

void FadeOut::startWithTarget(cocos2d::Node *target)
{
    ActionInterval::startWithTarget(target);
    
    if (nullptr != _reverseAction) {
        _toOpacity = _reverseAction->_fromOpacity;
    }else{
        _toOpacity = 0.0f;
    }
    
    if (target) {
        _fromOpacity = target->getOpacity();
    }
}

void FadeOut::setReverseAction(cocos2d::FadeTo *ac)
{
    _reverseAction = ac;
}


FadeTo* FadeOut::reverse() const
{
    auto action = FadeIn::create(_duration);
    action->setReverseAction(const_cast<FadeOut*>(this));
    return action;
}

//
// FadeTo
//

FadeTo* FadeTo::create(float duration, GLubyte opacity)
{
    FadeTo *fadeTo = new FadeTo();
    fadeTo->initWithDuration(duration, opacity);
    fadeTo->autorelease();

    return fadeTo;
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
	CCASSERT(false, "reverse() not supported in FadeTo");
	return nullptr;
}

void FadeTo::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);

    if (target)
    {
        _fromOpacity = target->getOpacity();
    }
    /*_fromOpacity = target->getOpacity();*/
}

void FadeTo::update(float time)
{
    if (_target)
    {
        _target->setOpacity((GLubyte)(_fromOpacity + (_toOpacity - _fromOpacity) * time));
    }
    /*_target->setOpacity((GLubyte)(_fromOpacity + (_toOpacity - _fromOpacity) * time));*/
}

//
// TintTo
//
TintTo* TintTo::create(float duration, GLubyte red, GLubyte green, GLubyte blue)
{
    TintTo *tintTo = new TintTo();
    tintTo->initWithDuration(duration, red, green, blue);
    tintTo->autorelease();

    return tintTo;
}

bool TintTo::initWithDuration(float duration, GLubyte red, GLubyte green, GLubyte blue)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _to = Color3B(red, green, blue);
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
	CCASSERT(false, "reverse() not supported in TintTo");
	return nullptr;
}

void TintTo::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    if (_target)
    {
        _from = _target->getColor();
    }
    /*_from = target->getColor();*/
}

void TintTo::update(float time)
{
    if (_target)
    {
        _target->setColor(Color3B(GLubyte(_from.r + (_to.r - _from.r) * time),
            (GLubyte)(_from.g + (_to.g - _from.g) * time),
            (GLubyte)(_from.b + (_to.b - _from.b) * time)));
    }    
}

//
// TintBy
//

TintBy* TintBy::create(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue)
{
    TintBy *tintBy = new TintBy();
    tintBy->initWithDuration(duration, deltaRed, deltaGreen, deltaBlue);
    tintBy->autorelease();

    return tintBy;
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

void TintBy::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);

    if (target)
    {
        Color3B color = target->getColor();
        _fromR = color.r;
        _fromG = color.g;
        _fromB = color.b;
    }    
}

void TintBy::update(float time)
{
    if (_target)
    {
        _target->setColor(Color3B((GLubyte)(_fromR + _deltaR * time),
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
    DelayTime* action = new DelayTime();

    action->initWithDuration(d);
    action->autorelease();

    return action;
}

DelayTime* DelayTime::clone() const
{
	// no copy constructor
	auto a = new DelayTime();
    a->initWithDuration(_duration);
	a->autorelease();
	return a;
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

ReverseTime* ReverseTime::create(FiniteTimeAction *action)
{
    // casting to prevent warnings
    ReverseTime *reverseTime = new ReverseTime();
    reverseTime->initWithAction( action->clone() );
    reverseTime->autorelease();

    return reverseTime;
}

bool ReverseTime::initWithAction(FiniteTimeAction *action)
{
    CCASSERT(action != nullptr, "");
    CCASSERT(action != _other, "");

    if (ActionInterval::initWithDuration(action->getDuration()))
    {
        // Don't leak if action is reused
        CC_SAFE_RELEASE(_other);

        _other = action;
        action->retain();

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

ReverseTime::ReverseTime() : _other(nullptr)
{

}

ReverseTime::~ReverseTime()
{
    CC_SAFE_RELEASE(_other);
}

void ReverseTime::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    _other->startWithTarget(target);
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
    // XXX: This looks like a bug
    return (ReverseTime*)_other->clone();
}

//
// Animate
//
Animate* Animate::create(Animation *animation)
{
    Animate *animate = new Animate();
    animate->initWithAnimation(animation);
    animate->autorelease();

    return animate;
}

Animate::Animate()
: _splitTimes(new std::vector<float>)
, _nextFrame(0)
, _origFrame(nullptr)
, _executedLoops(0)
, _animation(nullptr)
, _frameDisplayedEvent(nullptr)
{

}

Animate::~Animate()
{
    CC_SAFE_RELEASE(_animation);
    CC_SAFE_RELEASE(_origFrame);
    CC_SAFE_DELETE(_splitTimes);
    CC_SAFE_RELEASE(_frameDisplayedEvent);
}

bool Animate::initWithAnimation(Animation* animation)
{
    CCASSERT( animation!=nullptr, "Animate: argument Animation must be non-nullptr");

    float singleDuration = animation->getDuration();

    if ( ActionInterval::initWithDuration(singleDuration * animation->getLoops() ) )
    {
        _nextFrame = 0;
        setAnimation(animation);
        _origFrame = nullptr;
        _executedLoops = 0;

        _splitTimes->reserve(animation->getFrames().size());

        float accumUnitsOfTime = 0;
        float newUnitOfTimeValue = singleDuration / animation->getTotalDelayUnits();

        auto frames = animation->getFrames();

        for (auto& frame : frames)
        {
            float value = (accumUnitsOfTime * newUnitOfTimeValue) / singleDuration;
            accumUnitsOfTime += frame->getDelayUnits();
            _splitTimes->push_back(value);
        }    
        return true;
    }
    return false;
}

void Animate::setAnimation(cocos2d::Animation *animation)
{
    if (_animation != animation)
    {
        CC_SAFE_RETAIN(animation);
        CC_SAFE_RELEASE(_animation);
        _animation = animation;
    }
}

Animate* Animate::clone() const
{
	// no copy constructor
	auto a = new Animate();
	a->initWithAnimation(_animation->clone());
	a->autorelease();
	return a;
}

void Animate::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    Sprite *sprite = static_cast<Sprite*>(target);

    CC_SAFE_RELEASE(_origFrame);

    if (_animation->getRestoreOriginalFrame())
    {
        _origFrame = sprite->getSpriteFrame();
        _origFrame->retain();
    }
    _nextFrame = 0;
    _executedLoops = 0;
}

void Animate::stop()
{
    if (_animation->getRestoreOriginalFrame() && _target)
    {
        static_cast<Sprite*>(_target)->setSpriteFrame(_origFrame);
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

    auto frames = _animation->getFrames();
    auto numberOfFrames = frames.size();
    SpriteFrame *frameToDisplay = nullptr;

    for( int i=_nextFrame; i < numberOfFrames; i++ ) {
        float splitTime = _splitTimes->at(i);

        if( splitTime <= t ) {
            AnimationFrame* frame = frames.at(i);
            frameToDisplay = frame->getSpriteFrame();
            static_cast<Sprite*>(_target)->setSpriteFrame(frameToDisplay);

            const ValueMap& dict = frame->getUserInfo();
            if ( !dict.empty() )
            {
                if (_frameDisplayedEvent == nullptr)
                    _frameDisplayedEvent = new EventCustom(AnimationFrameDisplayedNotification);
                
                _frameDisplayedEventInfo.target = _target;
                _frameDisplayedEventInfo.userInfo = &dict;
                _frameDisplayedEvent->setUserData(&_frameDisplayedEventInfo);
                Director::getInstance()->getEventDispatcher()->dispatchEvent(_frameDisplayedEvent);
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
    auto oldArray = _animation->getFrames();
    Vector<AnimationFrame*> newArray(oldArray.size());
   
    if (oldArray.size() > 0)
    {
        for (auto iter = oldArray.crbegin(); iter != oldArray.crend(); ++iter)
        {
            AnimationFrame* animFrame = *iter;
            if (!animFrame)
            {
                break;
            }

            newArray.pushBack(animFrame->clone());
        }
    }

    Animation *newAnim = Animation::create(newArray, _animation->getDelayPerUnit(), _animation->getLoops());
    newAnim->setRestoreOriginalFrame(_animation->getRestoreOriginalFrame());
    return Animate::create(newAnim);
}

// TargetedAction

TargetedAction::TargetedAction()
: _action(nullptr)
, _forcedTarget(nullptr)
{

}

TargetedAction::~TargetedAction()
{
    CC_SAFE_RELEASE(_forcedTarget);
    CC_SAFE_RELEASE(_action);
}

TargetedAction* TargetedAction::create(Node* target, FiniteTimeAction* action)
{
    TargetedAction* p = new TargetedAction();
    p->initWithTarget(target, action);
    p->autorelease();
    return p;
}


bool TargetedAction::initWithTarget(Node* target, FiniteTimeAction* action)
{
    if(ActionInterval::initWithDuration(action->getDuration()))
    {
        CC_SAFE_RETAIN(target);
        _forcedTarget = target;
        CC_SAFE_RETAIN(action);
        _action = action;
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

TargetedAction* TargetedAction::reverse() const
{
	// just reverse the internal action
	auto a = new TargetedAction();
	a->initWithTarget(_forcedTarget, _action->reverse());
	a->autorelease();
	return a;
}

void TargetedAction::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    _action->startWithTarget(_forcedTarget);
}

void TargetedAction::stop()
{
    _action->stop();
}

void TargetedAction::update(float time)
{
    _action->update(time);
}

void TargetedAction::setForcedTarget(Node* forcedTarget)
{
    if( _forcedTarget != forcedTarget ) {
        CC_SAFE_RETAIN(forcedTarget);
        CC_SAFE_RELEASE(_forcedTarget);
        _forcedTarget = forcedTarget;
    }
}

NS_CC_END
