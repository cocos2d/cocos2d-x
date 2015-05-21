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

#include "2d/CCAction.h"
#include "2d/CCActionInterval.h"
#include "2d/CCNode.h"
#include "base/CCDirector.h"
#include "deprecated/CCString.h"

NS_CC_BEGIN
//
// Action Base Class
//

Action::Action()
:_originalTarget(nullptr)
,_target(nullptr)
,_tag(Action::INVALID_TAG)
{
}

Action::~Action()
{
    CCLOGINFO("deallocing Action: %p - tag: %i", this, _tag);
}

std::string Action::description() const
{
    return StringUtils::format("<Action | Tag = %d", _tag);
}

void Action::startWithTarget(Node *aTarget)
{
    _originalTarget = _target = aTarget;
}

void Action::stop()
{
    _target = nullptr;
}

bool Action::isDone() const
{
    return true;
}

void Action::step(float dt)
{
    CC_UNUSED_PARAM(dt);
    CCLOG("[Action step]. override me");
}

void Action::update(float time)
{
    CC_UNUSED_PARAM(time);
    CCLOG("[Action update]. override me");
}

//
// Speed
//
Speed::Speed()
: _speed(0.0)
, _innerAction(nullptr)
{
}

Speed::~Speed()
{
    CC_SAFE_RELEASE(_innerAction);
}

Speed* Speed::create(ActionInterval* action, float speed)
{
    Speed *ret = new (std::nothrow) Speed();
    if (ret && ret->initWithAction(action, speed))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Speed::initWithAction(ActionInterval *action, float speed)
{
    CCASSERT(action != nullptr, "action must not be NULL");
    action->retain();
    _innerAction = action;
    _speed = speed;
    return true;
}

Speed *Speed::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) Speed();
    a->initWithAction(_innerAction->clone(), _speed);
    a->autorelease();
    return a;
}

void Speed::startWithTarget(Node* target)
{
    Action::startWithTarget(target);
    _innerAction->startWithTarget(target);
}

void Speed::stop()
{
    _innerAction->stop();
    Action::stop();
}

void Speed::step(float dt)
{
    _innerAction->step(dt * _speed);
}

bool Speed::isDone() const
{
    return _innerAction->isDone();
}

Speed *Speed::reverse() const
{
    return Speed::create(_innerAction->reverse(), _speed);
}

void Speed::setInnerAction(ActionInterval *action)
{
    if (_innerAction != action)
    {
        CC_SAFE_RELEASE(_innerAction);
        _innerAction = action;
        CC_SAFE_RETAIN(_innerAction);
    }
}

//
// Follow
//
Follow::~Follow()
{
    CC_SAFE_RELEASE(_followedNode);
}

Follow* Follow::create(Node *followedNode, const Rect& rect/* = Rect::ZERO*/)
{
    Follow *follow = new (std::nothrow) Follow();
    if (follow && follow->initWithTarget(followedNode, rect))
    {
        follow->autorelease();
        return follow;
    }
    CC_SAFE_DELETE(follow);
    return nullptr;
}

Follow* Follow::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) Follow();
    a->initWithTarget(_followedNode, _worldRect);
    a->autorelease();
    return a;
}

Follow* Follow::reverse() const
{
    return clone();
}

bool Follow::initWithTarget(Node *followedNode, const Rect& rect/* = Rect::ZERO*/)
{
    CCASSERT(followedNode != nullptr, "FollowedNode can't be NULL");
 
    followedNode->retain();
    _followedNode = followedNode;
    _worldRect = rect;
    _boundarySet = !rect.equals(Rect::ZERO);
    _boundaryFullyCovered = false;

    Size winSize = Director::getInstance()->getWinSize();
    _fullScreenSize.set(winSize.width, winSize.height);
    _halfScreenSize = _fullScreenSize * 0.5f;

    if (_boundarySet)
    {
        _leftBoundary = -((rect.origin.x+rect.size.width) - _fullScreenSize.x);
        _rightBoundary = -rect.origin.x ;
        _topBoundary = -rect.origin.y;
        _bottomBoundary = -((rect.origin.y+rect.size.height) - _fullScreenSize.y);

        if(_rightBoundary < _leftBoundary)
        {
            // screen width is larger than world's boundary width
            //set both in the middle of the world
            _rightBoundary = _leftBoundary = (_leftBoundary + _rightBoundary) / 2;
        }
        if(_topBoundary < _bottomBoundary)
        {
            // screen width is larger than world's boundary width
            //set both in the middle of the world
            _topBoundary = _bottomBoundary = (_topBoundary + _bottomBoundary) / 2;
        }

        if( (_topBoundary == _bottomBoundary) && (_leftBoundary == _rightBoundary) )
        {
            _boundaryFullyCovered = true;
        }
    }
    
    return true;
}

void Follow::step(float dt)
{
    CC_UNUSED_PARAM(dt);

    if(_boundarySet)
    {
        // whole map fits inside a single screen, no need to modify the position - unless map boundaries are increased
        if(_boundaryFullyCovered)
        {
            return;
        }

        Vec2 tempPos = _halfScreenSize - _followedNode->getPosition();

        _target->setPosition(clampf(tempPos.x, _leftBoundary, _rightBoundary),
                                   clampf(tempPos.y, _bottomBoundary, _topBoundary));
    }
    else
    {
        _target->setPosition(_halfScreenSize - _followedNode->getPosition());
    }
}

bool Follow::isDone() const
{
    return ( !_followedNode->isRunning() );
}

void Follow::stop()
{
    _target = nullptr;
    Action::stop();
}

NS_CC_END


