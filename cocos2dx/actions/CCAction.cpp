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

CCAction::CCAction()
:_originalTarget(NULL)
,_target(NULL)
,_tag(kCCActionTagInvalid)
{
}

CCAction::~CCAction()
{
    CCLOGINFO("cocos2d: deallocing");
}

const char* CCAction::description()
{
    return CCString::createWithFormat("<CCAction | Tag = %d>", _tag)->getCString();
}

void CCAction::startWithTarget(CCNode *aTarget)
{
    _originalTarget = _target = aTarget;
}

void CCAction::stop()
{
    _target = NULL;
}

bool CCAction::isDone()
{
    return true;
}

void CCAction::step(float dt)
{
    CC_UNUSED_PARAM(dt);
    CCLOG("[Action step]. override me");
}

void CCAction::update(float time)
{
    CC_UNUSED_PARAM(time);
    CCLOG("[Action update]. override me");
}

//
// Speed
//
CCSpeed::CCSpeed()
: _speed(0.0)
, _innerAction(NULL)
{
}

CCSpeed::~CCSpeed()
{
    CC_SAFE_RELEASE(_innerAction);
}

CCSpeed* CCSpeed::create(CCActionInterval* pAction, float fSpeed)
{
    CCSpeed *pRet = new CCSpeed();
    if (pRet && pRet->initWithAction(pAction, fSpeed))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCSpeed::initWithAction(CCActionInterval *pAction, float fSpeed)
{
    CCAssert(pAction != NULL, "");
    pAction->retain();
    _innerAction = pAction;
    _speed = fSpeed;    
    return true;
}

CCSpeed *CCSpeed::clone(void) const
{
	auto a = new CCSpeed(*this);
	a->initWithAction(_innerAction->clone(), _speed);
	a->autorelease();
	return  a;
}

CCObject *CCSpeed::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCSpeed* pRet = NULL;
    if(pZone && pZone->_copyObject) //in case of being called at sub class
    {
        pRet = (CCSpeed*)(pZone->_copyObject);
    }
    else
    {
        pRet = new CCSpeed();
        pZone = pNewZone = new CCZone(pRet);
    }
    CCAction::copyWithZone(pZone);

    pRet->initWithAction( (CCActionInterval*)(_innerAction->copy()->autorelease()) , _speed );
    
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCSpeed::startWithTarget(CCNode* pTarget)
{
    CCAction::startWithTarget(pTarget);
    _innerAction->startWithTarget(pTarget);
}

void CCSpeed::stop()
{
    _innerAction->stop();
    CCAction::stop();
}

void CCSpeed::step(float dt)
{
    _innerAction->step(dt * _speed);
}

bool CCSpeed::isDone()
{
    return _innerAction->isDone();
}

CCSpeed *CCSpeed::reverse() const
{

	return CCSpeed::create(_innerAction->reverse(), _speed);
}

void CCSpeed::setInnerAction(CCActionInterval *pAction)
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
CCFollow::~CCFollow()
{
    CC_SAFE_RELEASE(_followedNode);
}

CCFollow* CCFollow::create(CCNode *pFollowedNode, const CCRect& rect/* = CCRectZero*/)
{
    CCFollow *pRet = new CCFollow();
    if (pRet && pRet->initWithTarget(pFollowedNode, rect))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCFollow* CCFollow::clone(void) const
{
	auto a = new CCFollow(*this);
	a->initWithTarget(_followedNode, _worldRect);
	a->autorelease();
	return a;
}

bool CCFollow::initWithTarget(CCNode *pFollowedNode, const CCRect& rect/* = CCRectZero*/)
{
    CCAssert(pFollowedNode != NULL, "");
 
    pFollowedNode->retain();
    _followedNode = pFollowedNode;
	_worldRect = rect;
    if (rect.equals(CCRectZero))
    {
        _boundarySet = false;
    }
    else
    {
        _boundarySet = true;
    }
    
    _boundaryFullyCovered = false;

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
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

CCObject *CCFollow::copyWithZone(CCZone *pZone)
{
    CCZone *pNewZone = NULL;
    CCFollow *pRet = NULL;
    if(pZone && pZone->_copyObject) //in case of being called at sub class
    {
        pRet = (CCFollow*)(pZone->_copyObject);
    }
    else
    {
        pRet = new CCFollow();
        pZone = pNewZone = new CCZone(pRet);
    }
    CCAction::copyWithZone(pZone);
    // copy member data
    pRet->_tag = _tag;
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCFollow::step(float dt)
{
    CC_UNUSED_PARAM(dt);

    if(_boundarySet)
    {
        // whole map fits inside a single screen, no need to modify the position - unless map boundaries are increased
        if(_boundaryFullyCovered)
            return;

        CCPoint tempPos = ccpSub( _halfScreenSize, _followedNode->getPosition());

        _target->setPosition(ccp(clampf(tempPos.x, _leftBoundary, _rightBoundary), 
                                   clampf(tempPos.y, _bottomBoundary, _topBoundary)));
    }
    else
    {
        _target->setPosition(ccpSub(_halfScreenSize, _followedNode->getPosition()));
    }
}

bool CCFollow::isDone()
{
    return ( !_followedNode->isRunning() );
}

void CCFollow::stop()
{
    _target = NULL;
    CCAction::stop();
}

NS_CC_END


