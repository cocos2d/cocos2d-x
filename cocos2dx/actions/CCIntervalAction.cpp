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

#include "CCIntervalAction.h"
#include "CCSprite.h"
#include "CCNode.h"
#include "support/CGPointExtension.h"

#include <float.h>

namespace cocos2d {

//
// IntervalAction
//
CCIntervalAction* CCIntervalAction::actionWithDuration(ccTime d)
{
	CCIntervalAction *pAction = new CCIntervalAction();
	pAction->initWithDuration(d);
	pAction->autorelease();

	return pAction;
}

CCIntervalAction* CCIntervalAction::initWithDuration(cocos2d::ccTime d)
{
	m_fDuration = d;

	// prevent division by 0
	// This comparison could be in step:, but it might decrease the performance
	// by 3% in heavy based action games.
	if (m_fDuration == 0)
	{
		m_fDuration = FLT_EPSILON;
	}

	m_elapsed = 0;
	m_bFirstTick = true;

	return this;
}

NSObject* CCIntervalAction::copyWithZone(NSZone *pZone)
{
	NSZone* pNewZone = NULL;
	CCIntervalAction* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = static_cast<CCIntervalAction*>(pZone->m_pCopyObject);
	}
	else
	{
		// action's base class , must be called using __super::copyWithZone(), after overriding from derived class
		assert(0);  

		pCopy = new CCIntervalAction();
		pZone = pNewZone = new NSZone(pCopy);
	}

	
	__super::copyWithZone(pZone);

	CCX_SAFE_DELETE(pNewZone);

	pCopy->initWithDuration(m_fDuration);

	return pCopy;
}

bool CCIntervalAction::isDone(void)
{
	return m_elapsed > m_fDuration;
}

void CCIntervalAction::step(ccTime dt)
{
	if (m_bFirstTick)
	{
		m_bFirstTick = false;
		m_elapsed = 0;
	}
	else
	{
		m_elapsed += dt;
	}

	update(min(1, m_elapsed/m_fDuration));
}

void CCIntervalAction::startWithTarget(NSObject *pTarget)
{
	__super::startWithTarget(pTarget);
	m_elapsed = 0.0f;
	m_bFirstTick = true;
}

CCIntervalAction* CCIntervalAction::reverse(void)
{
	/*
	 NSException* myException = [NSException
								exceptionWithName:@"ReverseActionNotImplemented"
								reason:@"Reverse Action not implemented"
								userInfo:nil];
	@throw myException;	
	*/
	return NULL;
}

//
// Sequence
//
CCSequence* CCSequence::actionOneTwo(cocos2d::CCFiniteTimeAction *pActionOne, cocos2d::CCFiniteTimeAction *pActionTwo)
{
	CCSequence *pSequence = new CCSequence();
	pSequence->initOneTwo(pActionOne, pActionTwo);
	pSequence->autorelease();

	return pSequence;
}

CCFiniteTimeAction* CCSequence::actions(cocos2d::CCFiniteTimeAction *pAction1, ...)
{
	va_list params;
	va_start(params, pAction1);

	CCFiniteTimeAction *pNow;
	CCFiniteTimeAction *pPrev = pAction1;

	while (pAction1)
	{
		pNow = va_arg(params, CCFiniteTimeAction*);
		if (pNow)
		{
			pPrev = actionOneTwo(pPrev, pNow);
		}
		else
		{
			break;
		}
	}

	va_end(params);
	return pPrev;
}

CCSequence* CCSequence::initOneTwo(cocos2d::CCFiniteTimeAction *pActionOne, cocos2d::CCFiniteTimeAction *pActionTwo)
{
	assert(pActionOne != NULL);
	assert(pActionTwo != NULL);

	ccTime d = pActionOne->getDuration() + pActionTwo->getDuration();
	__super::initWithDuration(d);

	m_pActions[0] = pActionOne;
	pActionOne->retain();

	m_pActions[1] = pActionTwo;
	pActionTwo->retain();

	return this;
}

NSObject* CCSequence::copyWithZone(NSZone *pZone)
{
	NSZone* pNewZone = NULL;
	CCSequence* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = dynamic_cast<CCSequence*>(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCSequence();
		pZone = pNewZone = new NSZone(pCopy);
	}

	__super::copyWithZone(pZone);

	pCopy->initOneTwo(static_cast<CCFiniteTimeAction*>(m_pActions[0]->copy()->autorelease()), 
				static_cast<CCFiniteTimeAction*>(m_pActions[1]->copy()->autorelease()));

	CCX_SAFE_DELETE(pNewZone);
	return pCopy;
}

CCSequence::~CCSequence(void)
{
	m_pActions[0]->release();
	m_pActions[1]->release();
}

void CCSequence::startWithTarget(cocos2d::NSObject *pTarget)
{
	__super::startWithTarget(pTarget);
	m_split = m_pActions[0]->getDuration() / m_fDuration;
	m_last = -1;
}

void CCSequence::stop(void)
{
	m_pActions[0]->stop();
	m_pActions[1]->stop();
	__super::stop();
}

void CCSequence::update(cocos2d::ccTime time)
{
	int found = 0;
	ccTime new_t = 0.0f;

	if (time >= m_split)
	{
		found = 1;
		if (m_split == 1)
		{
			new_t = 1;
		}
		else
		{
			new_t = (time - m_split) / (1 - m_split);
		}
	}
	else
	{
		found = 0;
		if (m_split != 0)
		{
			new_t = time / m_split;
		}
		else
		{
			new_t = 1;
		}
	}

	if (m_last == -1 && found == 1)
	{
		m_pActions[0]->startWithTarget(m_pTarget);
		m_pActions[0]->update(1.0f);
		m_pActions[0]->stop();
	}

	if (m_last != found)
	{
		if (m_last != -1)
		{
			m_pActions[found]->update(1.0f);
			m_pActions[found]->stop();
		}

		m_pActions[found]->startWithTarget(m_pTarget);
	}

	m_pActions[found]->update(new_t);
	m_last = found;
}

CCIntervalAction* CCSequence::reverse(void)
{
	return CCSequence::actionOneTwo(m_pActions[1]->reverse(), m_pActions[0]->reverse());
}

//
// Repeat
//
CCRepeat* CCRepeat::actionWithAction(cocos2d::CCFiniteTimeAction *pAction, unsigned int times)
{
	CCRepeat* pRepeat = new CCRepeat();
	pRepeat->initWithAction(pAction, times);
	pRepeat->autorelease();

	return pRepeat;
}

CCRepeat* CCRepeat::initWithAction(cocos2d::CCFiniteTimeAction *pAction, unsigned int times)
{
	ccTime d = pAction->getDuration() * times;

	if (__super::initWithDuration(d))
	{
        m_uTimes = times;
		m_pOther = pAction;
		pAction->retain();

		m_uTotal = 0;
	}

	return this;
}

NSObject* CCRepeat::copyWithZone(cocos2d::NSZone *pZone)
{
	
	NSZone* pNewZone = NULL;
	CCRepeat* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = dynamic_cast<CCRepeat*>(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCRepeat();
		pZone = pNewZone = new NSZone(pCopy);
	}

	__super::copyWithZone(pZone);

	pCopy->initWithAction(static_cast<CCFiniteTimeAction*>(m_pOther->copy()->autorelease()), m_uTimes);

	CCX_SAFE_DELETE(pNewZone);
	return pCopy;
}

CCRepeat::~CCRepeat(void)
{
	m_pOther->release();
}

void CCRepeat::startWithTarget(cocos2d::NSObject *pTarget)
{
	m_uTotal = 0;
	__super::startWithTarget(pTarget);
	m_pOther->startWithTarget(pTarget);
}

void CCRepeat::stop(void)
{
	m_pOther->stop();
	__super::stop();
}

// issue #80. Instead of hooking step:, hook update: since it can be called by any 
// container action like Repeat, Sequence, AccelDeccel, etc..
void CCRepeat::update(cocos2d::ccTime time)
{
	ccTime t = time * m_uTimes;
	if (t > m_uTotal + 1)
	{
		m_pOther->update(1.0f);
		m_uTotal++;
		m_pOther->stop();
		m_pOther->startWithTarget(m_pTarget);

		// repeat is over?
		if (m_uTotal == m_uTimes)
		{
			// so, set it in the original position
			m_pOther->update(0);
		}
		else
		{
			// no ? start next repeat with the right update
			// to prevent jerk (issue #390)
			m_pOther->update(t - m_uTotal);
		}
	}
	else
	{
		float r = fmodf(t, 1.0f);

		// fix last repeat position
		// else it could be 0.
		if (time == 1.0f)
		{
			r = 1.0f;
			m_uTotal++; // this is the added line
		}

		m_pOther->update(min(r, 1));
	}
}

bool CCRepeat::isDone(void)
{
	return m_uTotal == m_uTimes;
}

CCIntervalAction* CCRepeat::reverse(void)
{
	return CCRepeat::actionWithAction(m_pOther->reverse(), m_uTimes);
}

//
// Spawn
//
CCFiniteTimeAction* CCSpawn::actions(cocos2d::CCFiniteTimeAction *pAction1, ...)
{
	va_list params;
	va_start(params, pAction1);

	CCFiniteTimeAction *pNow;
	CCFiniteTimeAction *pPrev = pAction1;

	while (pAction1)
	{
		pNow = va_arg(params, CCFiniteTimeAction*);
		if (pNow)
		{
			pPrev = actionOneTwo(pPrev, pNow);
		}
		else
		{
			break;
		}
	}

	va_end(params);
	return pPrev;
}

CCSpawn* CCSpawn::actionOneTwo(cocos2d::CCFiniteTimeAction *pAction1, cocos2d::CCFiniteTimeAction *pAction2)
{
	CCSpawn *pSpawn = new CCSpawn();
	pSpawn->initOneTwo(pAction1, pAction2);
	pSpawn->autorelease();

	return pSpawn;
}

CCSpawn* CCSpawn:: initOneTwo(CCFiniteTimeAction *pAction1, CCFiniteTimeAction *pAction2)
{
	assert(pAction1 != NULL);
	assert(pAction2 != NULL);

	ccTime d1 = pAction1->getDuration();
	ccTime d2 = pAction2->getDuration();

	// __super::initWithDuration(fmaxf(d1, d2));
	float maxd = (d1 >= d2 || _isnan(d2)) ? d1 : d2;
	__super::initWithDuration(maxd);

    m_pOne = pAction1;
	m_pTwo = pAction2;

	if (d1 > d2)
	{
		m_pTwo = CCSequence::actionOneTwo(pAction1, CCDelayTime::actionWithDuration(d1 - d2));
	} else
	if (d1 < d2)
	{
		m_pOne = CCSequence::actionOneTwo(pAction1, CCDelayTime::actionWithDuration(d2 - d1));
	}

	pAction1->retain();
	pAction2->retain();
	return this;
}

NSObject* CCSpawn::copyWithZone(cocos2d::NSZone *pZone)
{
	NSZone* pNewZone = NULL;
	CCSpawn* pCopy = NULL;

	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = dynamic_cast<CCSpawn*>(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCSpawn();
		pZone = pNewZone = new NSZone(pCopy);
	}

	__super::copyWithZone(pZone);

	pCopy->initOneTwo(	dynamic_cast<CCFiniteTimeAction*>(m_pOne->copy()->autorelease()), 
					dynamic_cast<CCFiniteTimeAction*>(m_pTwo->copy()->autorelease()));

	CCX_SAFE_DELETE(pNewZone);
	return pCopy;
}

CCSpawn::~CCSpawn(void)
{
	m_pOne->release();
	m_pTwo->release();
}

void CCSpawn::startWithTarget(cocos2d::NSObject *pTarget)
{
	__super::startWithTarget(pTarget);
	m_pOne->startWithTarget(pTarget);
	m_pTwo->startWithTarget(pTarget);
}

void CCSpawn::stop(void)
{
	m_pOne->stop();
	m_pTwo->stop();
	__super::stop();
}

void CCSpawn::update(cocos2d::ccTime time)
{
	m_pOne->update(time);
	m_pTwo->update(time);
}

CCIntervalAction* CCSpawn::reverse(void)
{
	return CCSpawn::actionOneTwo(m_pOne->reverse(), m_pTwo->reverse());
}

//
// RotateTo
//
CCRotateTo* CCRotateTo::actionWithDuration(cocos2d::ccTime duration, float fDeltaAngle)
{
	CCRotateTo* pRotateTo = new CCRotateTo();
	pRotateTo->initWithDuration(duration, fDeltaAngle);
	pRotateTo->autorelease();

	return pRotateTo;
}

CCRotateTo* CCRotateTo::initWithDuration(cocos2d::ccTime duration, float fDeltaAngle)
{
	if (__super::initWithDuration(duration))
	{
		m_fDstAngle = fDeltaAngle;
		return this;
	}

	return NULL;
}

NSObject* CCRotateTo::copyWithZone(cocos2d::NSZone *pZone)
{
	NSZone* pNewZone = NULL;
	CCRotateTo* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject)
	{
		//in case of being called at sub class
		pCopy = dynamic_cast<CCRotateTo*>(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCRotateTo();
		pZone = pNewZone = new NSZone(pCopy);
	}

	__super::copyWithZone(pZone);

	pCopy->initWithDuration(m_fDuration, m_fDstAngle);

	//Action *copy = [[[self class] allocWithZone: zone] initWithDuration:[self duration] angle: angle];
	CCX_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCRotateTo::startWithTarget(cocos2d::NSObject *pTarget)
{
	__super::startWithTarget(pTarget);

	m_fStartAngle = (dynamic_cast<CCNode*>(pTarget))->getRotation();

	if (m_fStartAngle > 0)
	{
		m_fStartAngle = fmodf(m_fStartAngle, 360.0f);
	}
	else
	{
		m_fStartAngle = fmodf(m_fStartAngle, -360.0f);
	}

	m_fDiffAngle = m_fDstAngle - m_fStartAngle;
	if (m_fDiffAngle > 180)
	{
		m_fDiffAngle -= 360;
	}

	if (m_fDiffAngle < -180)
	{
		m_fDiffAngle += 360;
	}
}

void CCRotateTo::update(cocos2d::ccTime time)
{
	(dynamic_cast<CCNode*>(m_pTarget))->setRotation(m_fStartAngle + m_fDiffAngle * time);
}

//
// RotateBy
//
CCRotateBy* CCRotateBy::actionWithDuration(cocos2d::ccTime duration, float fDeltaAngle)
{
	return NULL;
}

CCRotateBy* CCRotateBy::initWithDuration(cocos2d::ccTime duration, float fDeltaAngle)
{
	return NULL;
}

NSObject* CCRotateBy::copyWithZone(cocos2d::NSZone *pZone)
{
	return NULL;
}

void CCRotateBy::startWithTarget(cocos2d::NSObject *pTarget)
{
}

void CCRotateBy::update(cocos2d::ccTime time)
{
}

CCIntervalAction* CCRotateBy::reverse(void)
{
	return NULL;
}

//
// MoveTo
//
CCMoveTo* CCMoveTo::actionWithDuration(cocos2d::ccTime duration, cocos2d::CGPoint position)
{
	return NULL;
}

CCMoveTo* CCMoveTo::initWithDuration(cocos2d::ccTime duration, cocos2d::CGPoint position)
{
	return NULL;
}

NSObject* CCMoveTo::copyWithZone(cocos2d::NSZone *pZone)
{
	return NULL;
}

void CCMoveTo::startWithTarget(NSObject *pTarget)
{
}

void CCMoveTo::update(cocos2d::ccTime time)
{
}

//
// MoveBy
//
CCMoveBy* CCMoveBy::actionWithDuration(cocos2d::ccTime duration, cocos2d::CGPoint position)
{
	return NULL;
}

CCMoveBy* CCMoveBy::initWithDuration(cocos2d::ccTime duration, cocos2d::CGPoint position)
{
	return NULL;
}

NSObject* CCMoveBy::copyWithZone(cocos2d::NSZone *pZone)
{
	return NULL;
}

void CCMoveBy::startWithTarget(cocos2d::NSObject *pTarget)
{
}

CCIntervalAction* CCMoveBy::reverse(void)
{
	return NULL;
}

//
// JumpBy
//
CCJumpBy* CCJumpBy::actionWithDuration(cocos2d::ccTime duration, cocos2d::CGPoint position, cocos2d::ccTime height, int jumps)
{
	return NULL;
}

CCJumpBy* CCJumpBy::initWithDuration(cocos2d::ccTime duration, cocos2d::CGPoint position, cocos2d::ccTime height, int jumps)
{
	return NULL;
}

NSObject* CCJumpBy::copyWithZone(cocos2d::NSZone *pZone)
{
	return NULL;
}

void CCJumpBy::startWithTarget(cocos2d::NSObject *pTarget)
{
}

void CCJumpBy::update(cocos2d::ccTime time)
{
}

CCIntervalAction* CCJumpBy::reverse(void)
{
	return NULL;
}

//
// JumpTo
//
void CCJumpTo::startWithTarget(cocos2d::NSObject *pTarget)
{
}

// Bezier cubic formula:
//	((1 - t) + t)3 = 1 
// Expands to¡­ 
//   (1 - t)3 + 3t(1-t)2 + 3t2(1 - t) + t3 = 1 
static inline float bezierat( float a, float b, float c, float d, ccTime t )
{
	return (powf(1-t,3) * a + 
			3*t*(powf(1-t,2))*b + 
			3*powf(t,2)*(1-t)*c +
			powf(t,3)*d );
}

//
// BezierBy
//
CCBezierBy* CCBezierBy::actionWithDuration(cocos2d::ccTime t, cocos2d::ccBezierConfig c)
{
	return NULL;
}

CCBezierBy* CCBezierBy::initWithDuration(cocos2d::ccTime t, cocos2d::ccBezierConfig c)
{
	return NULL;
}

void CCBezierBy::startWithTarget(cocos2d::NSObject *pTarget)
{
	
}

NSObject* CCBezierBy::copyWithZone(cocos2d::NSZone *pZone)
{
	return NULL;
}

void CCBezierBy::update(cocos2d::ccTime time)
{
}

CCIntervalAction* CCBezierBy::reverse(void)
{
	return NULL;
}

//
// BezierTo
//
void CCBezierTo::startWithTarget(cocos2d::NSObject *pTarget)
{
}

//
// ScaleTo
//
CCScaleTo* CCScaleTo::actionWithDuration(cocos2d::ccTime duration, float s)
{
	return NULL;
}

CCScaleTo* CCScaleTo::initWithDuration(cocos2d::ccTime duration, float s)
{
	return NULL;
}

CCScaleTo* CCScaleTo::actionWithDuration(cocos2d::ccTime duration, float sx, float sy)
{
	return NULL;
}

CCScaleTo* CCScaleTo::initWithDuration(cocos2d::ccTime duration, float sx, float sy)
{
	return NULL;
}

NSObject* CCScaleTo::copyWithZone(cocos2d::NSZone *pZone)
{
	return NULL;
}

void CCScaleTo::startWithTarget(cocos2d::NSObject *pTarget)
{
}

void CCScaleTo::update(cocos2d::ccTime time)
{
}

//
// ScaleBy
//
void CCScaleBy::startWithTarget(cocos2d::NSObject *pTarget)
{
}

CCIntervalAction* CCScaleBy::reverse(void)
{
	return NULL;
}

//
// Blink
//
CCBlink* CCBlink::actionWithDuration(cocos2d::ccTime duration, unsigned int uBlinks)
{
	return NULL;
}

CCBlink* CCBlink::initWithDuration(cocos2d::ccTime duration, unsigned int uBlinks)
{
	return NULL;
}

NSObject* CCBlink::copyWithZone(cocos2d::NSZone *pZone)
{
	return NULL;
}

void CCBlink::update(cocos2d::ccTime time)
{
}

CCIntervalAction* CCBlink::reverse(void)
{
	return NULL;
}

//
// FadeIn
//
void CCFadeIn::update(cocos2d::ccTime time)
{
}

CCIntervalAction* CCFadeIn::reverse(void)
{
	return NULL;
}

//
// FadeOut
//
void CCFadeOut::update(cocos2d::ccTime time)
{
}

CCIntervalAction* CCFadeOut::reverse(void)
{
	return NULL;
}

//
// FadeTo
//
CCFadeTo* CCFadeTo::actionWithDuration(cocos2d::ccTime duration, GLubyte opacity)
{
	return NULL;
}

CCFadeTo* CCFadeTo::initWithDuration(cocos2d::ccTime duration, GLubyte opacity)
{
	return NULL;
}

NSObject* CCFadeTo::copyWithZone(cocos2d::NSZone *pZone)
{
	return NULL;
}

void CCFadeTo::startWithTarget(cocos2d::NSObject *pTarget)
{
}

void CCFadeTo::update(cocos2d::ccTime time)
{
}

//
// TintTo
//
CCTintTo* CCTintTo::actionWithDuration(cocos2d::ccTime duration, GLubyte red, GLubyte green, GLubyte blue)
{
	return NULL;
}

CCTintTo* CCTintTo::initWithDuration(cocos2d::ccTime duration, GLubyte red, GLubyte green, GLubyte blue)
{
	return NULL;
}

NSObject* CCTintTo::copyWithZone(cocos2d::NSZone *pZone)
{
	return NULL;
}

void CCTintTo::startWithTarget(cocos2d::NSObject *pTarget)
{
}

void CCTintTo::update(cocos2d::ccTime time)
{
}

//
// TintBy
//
CCTintBy* CCTintBy::actionWithDuration(cocos2d::ccTime duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue)
{
	return NULL;
}

CCTintBy* CCTintBy::initWithDuration(cocos2d::ccTime duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue)
{
	return NULL;
}

NSObject* CCTintBy::copyWithZone(cocos2d::NSZone *pZone)
{
	return NULL;
}

void CCTintBy::startWithTarget(cocos2d::NSObject *pTarget)
{
}

void CCTintBy::update(cocos2d::ccTime time)
{
}

CCIntervalAction* CCTintBy::reverse(void)
{
	return NULL;
}

//
// DelayTime
//
void CCDelayTime::update(cocos2d::ccTime time)
{
}

CCIntervalAction* CCDelayTime::reverse(void)
{
	return NULL;
}

//
// ReverseTime
//
CCReverseTime* CCReverseTime::actionWithAction(cocos2d::CCFiniteTimeAction *pAction)
{
	return NULL;
}

CCReverseTime* CCReverseTime::initWithAction(cocos2d::CCFiniteTimeAction *pAction)
{
	return NULL;
}

NSObject* CCReverseTime::copyWithZone(cocos2d::NSZone *pZone)
{
	return NULL;
}

CCReverseTime::~CCReverseTime(void)
{
}

void CCReverseTime::startWithTarget(cocos2d::NSObject *pTarget)
{
}

void CCReverseTime::stop(void)
{
}

void CCReverseTime::update(cocos2d::ccTime time)
{
}

CCIntervalAction* CCReverseTime::reverse(void)
{
	return NULL;
}

//
// Animate
//
CCAnimate* CCAnimate::actionWithAnimation(cocos2d::CCAnimation *pAnimation)
{
	return NULL;
}

CCAnimate* CCAnimate::initWithAnimation(cocos2d::CCAnimation *pAnimation)
{
	return NULL;
}

CCAnimate* CCAnimate::actionWithAnimation(cocos2d::CCAnimation *pAnimation, bool bRestoreOriginalFrame)
{
	return NULL;
}

CCAnimate* CCAnimate::initWithAnimation(cocos2d::CCAnimation *pAnimation, bool bRestoreOriginalFrame)
{
	return NULL;
}

CCAnimate* CCAnimate::actionWithDuration(cocos2d::ccTime duration, cocos2d::CCAnimation *pAnimation, bool bRestoreOriginalFrame)
{
	return NULL;
}

CCAnimate* CCAnimate::initWithDuration(cocos2d::ccTime duration, cocos2d::CCAnimation *pAnimation, bool bRestoreOriginalFrame)
{
	return NULL;
}

NSObject* CCAnimate::copyWithZone(cocos2d::NSZone *pZone)
{
	return NULL;
}

CCAnimate::~CCAnimate(void)
{
}

void CCAnimate::startWithTarget(cocos2d::NSObject *pTarget)
{
}

void CCAnimate::stop(void)
{
}

void CCAnimate::update(cocos2d::ccTime time)
{
}

CCIntervalAction* CCAnimate::reverse(void)
{
	return NULL;
}

}
