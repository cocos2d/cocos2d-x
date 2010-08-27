/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include "CCIntervalAction.h"
#include "ccMacros.h"
#include "CCNode.h"
#include "CGPointExtension.h"
#include "CCDirector.h"
#include "NSZone.h"

namespace   cocos2d {
//
// Action Base Class
//

CCAction::CCAction()
:m_pOriginalTarget(NULL)
,m_pTarget(NULL)
,m_nTag(kCCActionTagInvalid)
{
}
CCAction::~CCAction()
{
	CCLOGINFO("cocos2d: deallocing");
}
CCAction * CCAction::action()
{
	CCAction * pRet = new CCAction();
	pRet->autorelease();
	return pRet;
}

char * CCAction::description()
{
	char *ret = new char[100] ;
	sprintf_s(ret, 100, "<CCAction | Tag = %d>", m_nTag);
	return ret;
}
NSObject* CCAction::copyWithZone(NSZone *pZone)
{
	NSZone *pNewZone = NULL;
	CCAction *pRet = NULL;
	if (pZone && pZone->m_pCopyObject)
	{
		pRet = (CCAction*)(pZone->m_pCopyObject);
	}
	else
	{
		pRet = new CCAction();
		pZone = pNewZone = new NSZone(pRet);
	}
	//copy member data
	pRet->m_nTag = m_nTag;
	CCX_SAFE_DELETE(pNewZone);
	return pRet;
}

void CCAction::startWithTarget(NSObject *aTarget)
{
	m_pOriginalTarget = m_pTarget = aTarget;
}

void CCAction::stop()
{
	m_pTarget = NULL;
}

bool CCAction::isDone()
{
	return true;
}

void CCAction::step(ccTime dt)
{
	CCLOG("[Action step]. override me");
}

void CCAction::update(ccTime time)
{
	CCLOG("[Action update]. override me");
}

//
// FiniteTimeAction
//

CCFiniteTimeAction *CCFiniteTimeAction::reverse()
{
	CCLOG("cocos2d: FiniteTimeAction#reverse: Implement me");
	return NULL;
}

//
// RepeatForever
//
CCRepeatForever::~CCRepeatForever()
{
	m_pOther->release();
}
CCRepeatForever *CCRepeatForever::actionWithAction(CCIntervalAction *pAction)
{
	CCRepeatForever *pRet = new CCRepeatForever();
	if (pRet && pRet->initWithAction(pAction))
	{
		pRet->autorelease();
		return pRet;
	}
	CCX_SAFE_DELETE(pRet);
	return NULL;
}

CCRepeatForever *CCRepeatForever::initWithAction(CCIntervalAction *pAction)
{
	pAction->retain();
	m_pOther = pAction;
	return this;
}
NSObject* CCRepeatForever::copyWithZone(NSZone *pZone)
{
	NSZone* pNewZone = NULL;
	CCRepeatForever* pRet = NULL;
	if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
	{
		pRet = (CCRepeatForever*)(pZone->m_pCopyObject);
	}
	else
	{
		pRet = new CCRepeatForever();
		pZone = pNewZone = new NSZone(pRet);
	}
	__super::copyWithZone(pZone);
	// win32 : use the m_pOther's copy object.
	pRet->initWithAction( (CCIntervalAction*)(m_pOther->copy()->autorelease()) ); 
	CCX_SAFE_DELETE(pNewZone);
	return pRet;
}

void CCRepeatForever::startWithTarget(NSObject* pTarget)
{
	__super::startWithTarget(pTarget);
	m_pOther->startWithTarget(pTarget);
}
 
void CCRepeatForever::step(ccTime dt)
{
	m_pOther->step(dt);
	if (m_pOther->isDone())
	{
		ccTime diff = dt + m_pOther->getDuration() - m_pOther->getElapsed();
		m_pOther->startWithTarget(m_pTarget);
		// to prevent jerk. issue #390
		m_pOther->step(diff);
	}
}

bool CCRepeatForever::isDone()
{
	return false;
}

CCIntervalAction *CCRepeatForever::reverse()
{
	return dynamic_cast<CCIntervalAction*>(CCRepeatForever::actionWithAction(m_pOther->reverse()));
}

//
// Speed
//
CCSpeed::~CCSpeed()
{
	if (m_pOther)
	{
        CCX_SAFE_RELEASE(m_pOther);
	}
	else
	{
		CCX_SAFE_RELEASE(m_pRepeat);
	}
	
}

CCSpeed * CCSpeed::actionWithAction(CCIntervalAction *pAction, float fRate)
{
	CCSpeed *pRet = new CCSpeed();
	if (pRet && pRet->initWithAction(pAction, fRate))
	{
		pRet->autorelease();
		return pRet;
	}
	CCX_SAFE_DELETE(pRet)
	return NULL;
}

CCSpeed* CCSpeed::actionWithAction(CCRepeatForever *pAction, float fRate)
{
	CCSpeed *pRet = new CCSpeed();
	if (pRet && pRet->initWithAction(pAction, fRate))
	{
		pRet->autorelease();
		return pRet;
	}
	CCX_SAFE_DELETE(pRet)
	return NULL;
}

CCSpeed * CCSpeed::initWithAction(CCIntervalAction *pAction, float fRate)
{
	pAction->retain();
	m_pOther = pAction;
	m_pRepeat = NULL;
	m_fSpeed = fRate;	
	return this;
}

CCSpeed* CCSpeed::initWithAction(CCRepeatForever *pAction, float fRate)
{
	pAction->retain();
	m_pRepeat = pAction;
	m_pOther = NULL;
	m_fSpeed = fRate;	
	return this;
}

NSObject *CCSpeed::copyWithZone(NSZone *pZone)
{
	NSZone* pNewZone = NULL;
	CCSpeed* pRet = NULL;
	if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
	{
		pRet = dynamic_cast<CCSpeed*>(pZone->m_pCopyObject);
	}
	else
	{
		pRet = new CCSpeed();
		pZone = pNewZone = new NSZone(pRet);
	}
	__super::copyWithZone(pZone);
	if (m_pOther)
	{
        pRet->initWithAction( dynamic_cast<CCIntervalAction*>(m_pOther->copy()->autorelease()) , m_fSpeed );
	}
	else
	{
        pRet->initWithAction( dynamic_cast<CCIntervalAction*>(m_pRepeat->copy()->autorelease()) , m_fSpeed );
	}
	
	CCX_SAFE_DELETE(pNewZone);
	return pRet;
}

void CCSpeed::startWithTarget(NSObject* pTarget)
{
	__super::startWithTarget(pTarget);
	if (m_pOther)
	{
        m_pOther->startWithTarget(pTarget);
	}
	else
	{
        m_pRepeat->startWithTarget(pTarget);
	}	
}

void CCSpeed::stop()
{
	if (m_pOther)
	{
        m_pOther->stop();
	}
	else
	{
		m_pRepeat->stop();
	}
	__super::stop();
}

void CCSpeed::step(ccTime dt)
{
	if (m_pOther)
	{
        m_pOther->step(dt * m_fSpeed);
	}
    else
	{
		m_pRepeat->step(dt * m_fSpeed);
	}
}

bool CCSpeed::isDone()
{
	if (m_pOther)
	{
        return m_pOther->isDone();
	}
	else
	{
		return m_pRepeat->isDone();
	}
}

CCIntervalAction *CCSpeed::reverse()
{
	if (m_pOther)
	{
        return dynamic_cast<CCIntervalAction*>(CCSpeed::actionWithAction(m_pOther->reverse(), m_fSpeed));
	}
	else
	{
        return dynamic_cast<CCIntervalAction*>(CCSpeed::actionWithAction(m_pRepeat->reverse(), m_fSpeed));
	}
}

//
// Follow
//
CCFollow::~CCFollow()
{
	m_pobFollowedNode->release();
}

CCFollow *CCFollow::actionWithTarget(CCNode *pFollowedNode)
{
	CCFollow *pRet = new CCFollow();
	if (pRet && pRet->initWithTarget(pFollowedNode))
	{
		pRet->autorelease();
		return pRet;
	}
	CCX_SAFE_DELETE(pRet)
	return NULL;
}
CCFollow *CCFollow::actionWithTarget(CCNode *pFollowedNode, CGRect rect)
{
	CCFollow *pRet = new CCFollow();
	if (pRet && pRet->initWithTarget(pFollowedNode, rect))
	{
		pRet->autorelease();
		return pRet;
	}
	CCX_SAFE_DELETE(pRet)
	return NULL;
}

CCFollow *CCFollow::initWithTarget(CCNode *pFollowedNode)
{
	pFollowedNode->retain();
	m_pobFollowedNode = pFollowedNode;
	m_bBoundarySet = false;
	m_bBoundaryFullyCovered = false;

	CGSize winSize = CCDirector::getSharedDirector()->getWinSize();
	m_obFullScreenSize = CGPointMake(winSize.width, winSize.height);
	m_obHalfScreenSize = ccpMult(m_obFullScreenSize, 0.5f);
	return this;
}

CCFollow *CCFollow::initWithTarget(CCNode *pFollowedNode, CGRect rect)
{
	pFollowedNode->retain();
	m_pobFollowedNode = pFollowedNode;
	m_bBoundarySet = true;
	m_bBoundaryFullyCovered = false;

	CGSize winSize = CCDirector::getSharedDirector()->getWinSize();
	m_obFullScreenSize = CGPointMake(winSize.width, winSize.height);
	m_obHalfScreenSize = ccpMult(m_obFullScreenSize, 0.5f);

	m_fLeftBoundary = -((rect.origin.x+rect.size.width) - m_obFullScreenSize.x);
	m_fRightBoundary = -rect.origin.x ;
	m_fTopBoundary = -rect.origin.y;
	m_fBottomBoundary = -((rect.origin.y+rect.size.height) - m_obFullScreenSize.y);

	if(m_fRightBoundary < m_fLeftBoundary)
	{
		// screen width is larger than world's boundary width
		//set both in the middle of the world
		m_fRightBoundary = m_fLeftBoundary = (m_fLeftBoundary + m_fRightBoundary) / 2;
	}
	if(m_fTopBoundary < m_fBottomBoundary)
	{
		// screen width is larger than world's boundary width
		//set both in the middle of the world
		m_fTopBoundary = m_fBottomBoundary = (m_fTopBoundary + m_fBottomBoundary) / 2;
	}

	if( (m_fTopBoundary == m_fBottomBoundary) && (m_fLeftBoundary == m_fRightBoundary) )
	{
		m_bBoundaryFullyCovered = true;
	}
	return this;
}
NSObject *CCFollow::copyWithZone(NSZone *pZone)
{
	NSZone *pNewZone = NULL;
	CCFollow *pRet = NULL;
	if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
	{
		pRet = dynamic_cast<CCFollow*>(pZone->m_pCopyObject);
	}
	else
	{
		pRet = new CCFollow();
		pZone = pNewZone = new NSZone(pRet);
	}
	__super::copyWithZone(pZone);
	// copy member data
	pRet->m_nTag = m_nTag;
	CCX_SAFE_DELETE(pNewZone);
	return pRet;
}
void CCFollow::step(ccTime dt)
{
#define CLAMP(x,y,z) MIN(MAX(x,y),z)

	if(m_bBoundarySet)
	{
		// whole map fits inside a single screen, no need to modify the position - unless map boundaries are increased
		if(m_bBoundaryFullyCovered)
			return;

		CGPoint tempPos = ccpSub( m_obHalfScreenSize, m_pobFollowedNode->getPosition());

		dynamic_cast<CCNode*>(m_pTarget)->setPosition(ccp(CLAMP(tempPos.x, m_fLeftBoundary, m_fRightBoundary), 
								   CLAMP(tempPos.y, m_fBottomBoundary, m_fTopBoundary)));
	}
	else
	{
		dynamic_cast<CCNode*>(m_pTarget)->setPosition(ccpSub(m_obHalfScreenSize, m_pobFollowedNode->getPosition()));
	}
#undef CLAMP
}

bool CCFollow::isDone()
{
	return ( !m_pobFollowedNode->getIsRunning() );
}
void CCFollow::stop()
{
	m_pTarget = NULL;
	__super::stop();
}

}//namespace   cocos2d 


