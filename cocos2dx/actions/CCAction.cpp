/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.
 
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

#include "CCAction.h"
#include "CCActionInterval.h"
#include "base_nodes/CCNode.h"
#include "support/CCPointExtension.h"
#include "CCDirector.h"
#include "cocoa/CCZone.h"

NS_CC_BEGIN
//
// Action Base Class
//

Action::Action()
:_originalTarget(NULL)
,_target(NULL)
,_tag(kActionTagInvalid)
{
}

Action::~Action()
{
    CCLOGINFO("cocos2d: deallocing");
}

const char* Action::description()
{
    return String::createWithFormat("<Action | Tag = %d>", _tag)->getCString();
}

void Action::startWithTarget(Node *aTarget)
{
    _originalTarget = _target = aTarget;
}

void Action::stop()
{
    _target = NULL;
}

bool Action::isDone()
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
, _innerAction(NULL)
{
}

Speed::~Speed()
{
    CC_SAFE_RELEASE(_innerAction);
}

Speed* Speed::create(ActionInterval* pAction, float fSpeed)
{
    Speed *pRet = new Speed();
    if (pRet && pRet->initWithAction(pAction, fSpeed))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool Speed::initWithAction(ActionInterval *pAction, float fSpeed)
{
    CCAssert(pAction != NULL, "");
    pAction->retain();
    _innerAction = pAction;
    _speed = fSpeed;    
    return true;
}

Speed *Speed::clone() const
{
	// no copy constructor
	auto a = new Speed();
	a->initWithAction(_innerAction->clone(), _speed);
	a->autorelease();
	return  a;
}

Object *Speed::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    Speed* pRet = NULL;
    if(pZone && pZone->_copyObject) //in case of being called at sub class
    {
        pRet = (Speed*)(pZone->_copyObject);
    }
    else
    {
        pRet = new Speed();
        pZone = pNewZone = new Zone(pRet);
    }
    Action::copyWithZone(pZone);

    pRet->initWithAction( (ActionInterval*)(_innerAction->copy()->autorelease()) , _speed );
    
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void Speed::startWithTarget(Node* pTarget)
{
    Action::startWithTarget(pTarget);
    _innerAction->startWithTarget(pTarget);
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

bool Speed::isDone()
{
    return _innerAction->isDone();
}

Speed *Speed::reverse() const
{

	return Speed::create(_innerAction->reverse(), _speed);
}

void Speed::setInnerAction(ActionInterval *pAction)
{
    if (_innerAction != pAction)
    {
        CC_SAFE_RELEASE(_innerAction);
        _innerAction = pAction;
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

Follow* Follow::create(Node *pFollowedNode, const Rect& rect/* = RectZero*/)
{
    Follow *pRet = new Follow();
    if (pRet && pRet->initWithTarget(pFollowedNode, rect))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

Follow* Follow::clone() const
{
	// no copy constructor
	auto a = new Follow();
	a->initWithTarget(_followedNode, _worldRect);
	a->autorelease();
	return a;
}

bool Follow::initWithTarget(Node *pFollowedNode, const Rect& rect/* = RectZero*/)
{
    CCAssert(pFollowedNode != NULL, "");
 
    pFollowedNode->retain();
    _followedNode = pFollowedNode;
	_worldRect = rect;
    if (rect.equals(RectZero))
    {
        _boundarySet = false;
    }
    else
    {
        _boundarySet = true;
    }
    
    _boundaryFullyCovered = false;

    Size winSize = Director::sharedDirector()->getWinSize();
    _fullScreenSize = CCPointMake(winSize.width, winSize.height);
    _halfScreenSize = ccpMult(_fullScreenSize, 0.5f);

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

Object *Follow::copyWithZone(Zone *pZone)
{
    Zone *pNewZone = NULL;
    Follow *pRet = NULL;
    if(pZone && pZone->_copyObject) //in case of being called at sub class
    {
        pRet = (Follow*)(pZone->_copyObject);
    }
    else
    {
        pRet = new Follow();
        pZone = pNewZone = new Zone(pRet);
    }
    Action::copyWithZone(pZone);
    // copy member data
    pRet->_tag = _tag;
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void Follow::step(float dt)
{
    CC_UNUSED_PARAM(dt);

    if(_boundarySet)
    {
        // whole map fits inside a single screen, no need to modify the position - unless map boundaries are increased
        if(_boundaryFullyCovered)
            return;

        Point tempPos = ccpSub( _halfScreenSize, _followedNode->getPosition());

        _target->setPosition(ccp(clampf(tempPos.x, _leftBoundary, _rightBoundary), 
                                   clampf(tempPos.y, _bottomBoundary, _topBoundary)));
    }
    else
    {
        _target->setPosition(ccpSub(_halfScreenSize, _followedNode->getPosition()));
    }
}

bool Follow::isDone()
{
    return ( !_followedNode->isRunning() );
}

void Follow::stop()
{
    _target = NULL;
    Action::stop();
}

NS_CC_END


