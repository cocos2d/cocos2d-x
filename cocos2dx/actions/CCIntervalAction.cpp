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

namespace cocos2d {

//
// IntervalAction
//
CCIntervalAction* CCIntervalAction::actionWithDuration(ccTime d)
{
	return NULL;
}

CCIntervalAction* CCIntervalAction::initWithDuration(cocos2d::ccTime d)
{
	return NULL;
}

NSObject* CCIntervalAction::copyWithZone(NSZone *pZone)
{
	return NULL;
}

bool CCIntervalAction::isDone(void)
{
	return false;
}

void CCIntervalAction::step(ccTime dt)
{
}

void CCIntervalAction::startWithTarget(NSObject *pTarget)
{
}

CCIntervalAction* CCIntervalAction::reverse(void)
{
	return NULL;
}

//
// Sequence
//
CCSequence* CCSequence::actionOneTwo(cocos2d::CCFiniteTimeAction *pActionOne, cocos2d::CCFiniteTimeAction *pActionTwo)
{
	return NULL;
}

CCSequence* CCSequence::actions(cocos2d::CCFiniteTimeAction *pAction1, ...)
{
	return NULL;
}

CCSequence* CCSequence::initOneTwo(cocos2d::CCFiniteTimeAction *pActionOne, cocos2d::CCFiniteTimeAction *pActionTwo)
{
	return NULL;
}

NSObject* CCSequence::copyWithZone(NSZone *pZone)
{
	return NULL;
}

CCSequence::~CCSequence(void)
{
}

void CCSequence::startWithTarget(cocos2d::NSObject *pTarget)
{
}

void CCSequence::stop(void)
{
}

void CCSequence::update(cocos2d::ccTime time)
{
}

CCIntervalAction* CCSequence::reverse(void)
{
	return NULL;
}

//
// Repeat
//
CCRepeat* CCRepeat::actionWithAction(cocos2d::CCFiniteTimeAction *pAction, unsigned int times)
{
	return NULL;
}

CCRepeat* CCRepeat::initWithAction(cocos2d::CCFiniteTimeAction *pAction, unsigned int times)
{
	return NULL;
}

NSObject* CCRepeat::copyWithZone(cocos2d::NSZone *pZone)
{
	return NULL;
}

CCRepeat::~CCRepeat(void)
{
}

void CCRepeat::startWithTarget(cocos2d::NSObject *pTarget)
{
}

void CCRepeat::stop(void)
{
}

// issue #80. Instead of hooking step:, hook update: since it can be called by any 
// container action like Repeat, Sequence, AccelDeccel, etc..
void CCRepeat::update(cocos2d::ccTime time)
{
}

bool CCRepeat::isDone(void)
{
	return false;
}

CCIntervalAction* CCRepeat::reverse(void)
{
	return NULL;
}

//
// Spawn
//
CCSpawn* CCSpawn::actions(cocos2d::CCFiniteTimeAction *pAction1, ...)
{
	return NULL;
}

CCSpawn* CCSpawn::initOneTwo(cocos2d::CCFiniteTimeAction *pAction1, cocos2d::CCFiniteTimeAction *pAction2)
{
	return NULL;
}

NSObject* CCSpawn::copyWithZone(cocos2d::NSZone *pZone)
{
	return NULL;
}

CCSpawn::~CCSpawn(void)
{
}

void CCSpawn::startWithTarget(cocos2d::NSObject *pTarget)
{
}

void CCSpawn::stop(void)
{
}

void CCSpawn::update(cocos2d::ccTime time)
{
}

CCIntervalAction* CCSpawn::reverse(void)
{
	return NULL;
}

//
// RotateTo
//
CCRotateTo* CCRotateTo::actionWithDuration(cocos2d::ccTime duration, float fDeltaAngle)
{
	return NULL;
}

CCRotateTo* CCRotateTo::initWithDuration(cocos2d::ccTime duration, float fDeltaAngle)
{
	return NULL;
}

NSObject* CCRotateTo::copyWithZone(cocos2d::NSZone *pZone)
{
	return NULL;
}

void CCRotateTo::startWithTarget(cocos2d::NSObject *pTarget)
{
}

void CCRotateTo::update(cocos2d::ccTime time)
{
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
