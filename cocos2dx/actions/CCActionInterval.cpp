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

//
// IntervalAction
//
CCActionInterval* CCActionInterval::actionWithDuration(float d)
{
    return CCActionInterval::create(d);
}

CCActionInterval* CCActionInterval::create(float d)
{
    CCActionInterval *pAction = new CCActionInterval();
    pAction->initWithDuration(d);
    pAction->autorelease();

    return pAction;
}

bool CCActionInterval::initWithDuration(float d)
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

    return true;
}

CCObject* CCActionInterval::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCActionInterval* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCActionInterval*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCActionInterval();
        pZone = pNewZone = new CCZone(pCopy);
    }

    
    CCFiniteTimeAction::copyWithZone(pZone);

    CC_SAFE_DELETE(pNewZone);

    pCopy->initWithDuration(m_fDuration);

    return pCopy;
}

bool CCActionInterval::isDone(void)
{
    return m_elapsed >= m_fDuration;
}

void CCActionInterval::step(float dt)
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
    
    this->update(MAX (0,                                  // needed for rewind. elapsed could be negative
                      MIN(1, m_elapsed /
                          MAX(m_fDuration, FLT_EPSILON)   // division by 0
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
    m_elapsed = 0.0f;
    m_bFirstTick = true;
}

CCActionInterval* CCActionInterval::reverse(void)
{
    CCAssert(false, "CCIntervalAction: reverse not implemented.");
    return NULL;
}

//
// Sequence
//
CCSequence* CCSequence::actionOneTwo(CCFiniteTimeAction *pActionOne, CCFiniteTimeAction *pActionTwo)
{
    return CCSequence::createWithTwoActions(pActionOne, pActionTwo);
}

CCSequence* CCSequence::createWithTwoActions(CCFiniteTimeAction *pActionOne, CCFiniteTimeAction *pActionTwo)
{
    CCSequence *pSequence = new CCSequence();
    pSequence->initWithTwoActions(pActionOne, pActionTwo);
    pSequence->autorelease();

    return pSequence;
}

CCFiniteTimeAction* CCSequence::actions(CCFiniteTimeAction *pAction1, ...)
{
    va_list params;
    va_start(params, pAction1);
    
    CCFiniteTimeAction *pRet = CCSequence::create(pAction1, params);
    
    va_end(params);
    
    return pRet;
}

CCFiniteTimeAction* CCSequence::create(CCFiniteTimeAction *pAction1, ...)
{
    va_list params;
    va_start(params, pAction1);

    CCFiniteTimeAction *pRet = CCSequence::create(pAction1, params);

    va_end(params);
    
    return pRet;
}

CCFiniteTimeAction* CCSequence::create(CCFiniteTimeAction *pAction1, va_list args)
{
    CCFiniteTimeAction *pNow;
    CCFiniteTimeAction *pPrev = pAction1;
    
    while (pAction1)
    {
        pNow = va_arg(args, CCFiniteTimeAction*);
        if (pNow)
        {
            pPrev = createWithTwoActions(pPrev, pNow);
        }
        else
        {
            break;
        }
    }
    
    return pPrev;
}

CCFiniteTimeAction* CCSequence::actionWithArray(CCArray* arrayOfActions)
{
    return CCSequence::create(arrayOfActions);
}

CCFiniteTimeAction* CCSequence::create(CCArray* arrayOfActions)
{
    CCFiniteTimeAction* prev = (CCFiniteTimeAction*)arrayOfActions->objectAtIndex(0);

    for (unsigned int i = 1; i < arrayOfActions->count(); ++i)
    {
        prev = createWithTwoActions(prev, (CCFiniteTimeAction*)arrayOfActions->objectAtIndex(i));
    }

    return prev;
}

bool CCSequence::initWithTwoActions(CCFiniteTimeAction *pActionOne, CCFiniteTimeAction *pActionTwo)
{
    CCAssert(pActionOne != NULL, "");
    CCAssert(pActionTwo != NULL, "");

    float d = pActionOne->getDuration() + pActionTwo->getDuration();
    CCActionInterval::initWithDuration(d);

    m_pActions[0] = pActionOne;
    pActionOne->retain();

    m_pActions[1] = pActionTwo;
    pActionTwo->retain();

    return true;
}

CCObject* CCSequence::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCSequence* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCSequence*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCSequence();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithTwoActions((CCFiniteTimeAction*)(m_pActions[0]->copy()->autorelease()), 
                (CCFiniteTimeAction*)(m_pActions[1]->copy()->autorelease()));

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

CCSequence::~CCSequence(void)
{
    CC_SAFE_RELEASE(m_pActions[0]);
    CC_SAFE_RELEASE(m_pActions[1]);
}

void CCSequence::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_split = m_pActions[0]->getDuration() / m_fDuration;
    m_last = -1;
}

void CCSequence::stop(void)
{
    // Issue #1305
    if( m_last != - 1)
    {
        m_pActions[m_last]->stop();
    }

    CCActionInterval::stop();
}

void CCSequence::update(float t)
{
    int found = 0;
    float new_t = 0.0f;

    if( t < m_split ) {
        // action[0]
        found = 0;
        if( m_split != 0 )
            new_t = t / m_split;
        else
            new_t = 1;

    } else {
        // action[1]
        found = 1;
        if ( m_split == 1 )
            new_t = 1;
        else
            new_t = (t-m_split) / (1 - m_split );
    }

    if ( found==1 ) {

        if( m_last == -1 ) {
            // action[0] was skipped, execute it.
            m_pActions[0]->startWithTarget(m_pTarget);
            m_pActions[0]->update(1.0f);
            m_pActions[0]->stop();
        }
        else if( m_last == 0 )
        {
            // switching to action 1. stop action 0.
            m_pActions[0]->update(1.0f);
            m_pActions[0]->stop();
        }
    }

    // Last action found and it is done.
    if( found == m_last && m_pActions[found]->isDone() )
    {
        return;
    }

    // Last action found and it is done
    if( found != m_last )
    {
        m_pActions[found]->startWithTarget(m_pTarget);
    }

    m_pActions[found]->update(new_t);
    m_last = found;
}

CCActionInterval* CCSequence::reverse(void)
{
    return CCSequence::createWithTwoActions(m_pActions[1]->reverse(), m_pActions[0]->reverse());
}

//
// Repeat
//
CCRepeat* CCRepeat::actionWithAction(CCFiniteTimeAction *pAction, unsigned int times)
{
    return CCRepeat::create(pAction, times);
}

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
        m_uTimes = times;
        m_pInnerAction = pAction;
        pAction->retain();

        m_bActionInstant = dynamic_cast<CCActionInstant*>(pAction) ? true : false;
        //an instant action needs to be executed one time less in the update method since it uses startWithTarget to execute the action
        if (m_bActionInstant) 
        {
            m_uTimes -=1;
        }
        m_uTotal = 0;

        return true;
    }

    return false;
}

CCObject* CCRepeat::copyWithZone(CCZone *pZone)
{
    
    CCZone* pNewZone = NULL;
    CCRepeat* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCRepeat*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCRepeat();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithAction((CCFiniteTimeAction*)(m_pInnerAction->copy()->autorelease()), m_uTimes);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

CCRepeat::~CCRepeat(void)
{
    CC_SAFE_RELEASE(m_pInnerAction);
}

void CCRepeat::startWithTarget(CCNode *pTarget)
{
    m_uTotal = 0;
    m_fNextDt = m_pInnerAction->getDuration()/m_fDuration;
    CCActionInterval::startWithTarget(pTarget);
    m_pInnerAction->startWithTarget(pTarget);
}

void CCRepeat::stop(void)
{
    m_pInnerAction->stop();
    CCActionInterval::stop();
}

// issue #80. Instead of hooking step:, hook update: since it can be called by any 
// container action like CCRepeat, CCSequence, CCEase, etc..
void CCRepeat::update(float dt)
{
    if (dt >= m_fNextDt)
    {
        while (dt > m_fNextDt && m_uTotal < m_uTimes)
        {

            m_pInnerAction->update(1.0f);
            m_uTotal++;

            m_pInnerAction->stop();
            m_pInnerAction->startWithTarget(m_pTarget);
            m_fNextDt += m_pInnerAction->getDuration()/m_fDuration;
        }

        // fix for issue #1288, incorrect end value of repeat
        if(dt >= 1.0f && m_uTotal < m_uTimes) 
        {
            m_uTotal++;
        }

        // don't set an instant action back or update it, it has no use because it has no duration
        if (!m_bActionInstant)
        {
            if (m_uTotal == m_uTimes)
            {
                m_pInnerAction->update(1);
                m_pInnerAction->stop();
            }
            else
            {
                // issue #390 prevent jerk, use right update
                m_pInnerAction->update(dt - (m_fNextDt - m_pInnerAction->getDuration()/m_fDuration));
            }
        }
    }
    else
    {
        m_pInnerAction->update(fmodf(dt * m_uTimes,1.0f));
    }
}

bool CCRepeat::isDone(void)
{
    return m_uTotal == m_uTimes;
}

CCActionInterval* CCRepeat::reverse(void)
{
    return CCRepeat::create(m_pInnerAction->reverse(), m_uTimes);
}

//
// RepeatForever
//
CCRepeatForever::~CCRepeatForever()
{
    CC_SAFE_RELEASE(m_pInnerAction);
}

CCRepeatForever *CCRepeatForever::actionWithAction(CCActionInterval *pAction)
{
    return CCRepeatForever::create(pAction);
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
    m_pInnerAction = pAction;
    return true;
}
CCObject* CCRepeatForever::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCRepeatForever* pRet = NULL;
    if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
    {
        pRet = (CCRepeatForever*)(pZone->m_pCopyObject);
    }
    else
    {
        pRet = new CCRepeatForever();
        pZone = pNewZone = new CCZone(pRet);
    }
    CCActionInterval::copyWithZone(pZone);
    // win32 : use the m_pOther's copy object.
    pRet->initWithAction((CCActionInterval*)(m_pInnerAction->copy()->autorelease())); 
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCRepeatForever::startWithTarget(CCNode* pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_pInnerAction->startWithTarget(pTarget);
}

void CCRepeatForever::step(float dt)
{
    m_pInnerAction->step(dt);
    if (m_pInnerAction->isDone())
    {
        float diff = m_pInnerAction->getElapsed() - m_pInnerAction->getDuration();
        m_pInnerAction->startWithTarget(m_pTarget);
        // to prevent jerk. issue #390, 1247
        m_pInnerAction->step(0.0f);
        m_pInnerAction->step(diff);
    }
}

bool CCRepeatForever::isDone()
{
    return false;
}

CCActionInterval *CCRepeatForever::reverse()
{
    return (CCActionInterval*)(CCRepeatForever::create(m_pInnerAction->reverse()));
}

//
// Spawn
//
CCFiniteTimeAction* CCSpawn::actions(CCFiniteTimeAction *pAction1, ...)
{
    va_list params;
    va_start(params, pAction1);
    
    CCFiniteTimeAction *pRet = CCSpawn::create(pAction1, params);
    
    va_end(params);
    
    return pRet;
}

CCFiniteTimeAction* CCSpawn::create(CCFiniteTimeAction *pAction1, ...)
{
    va_list params;
    va_start(params, pAction1);

    CCFiniteTimeAction *pRet = CCSpawn::create(pAction1, params);

    va_end(params);
    
    return pRet;
}

CCFiniteTimeAction* CCSpawn::create(CCFiniteTimeAction *pAction1, va_list args)
{
    CCFiniteTimeAction *pNow;
    CCFiniteTimeAction *pPrev = pAction1;
    
    while (pAction1)
    {
        pNow = va_arg(args, CCFiniteTimeAction*);
        if (pNow)
        {
            pPrev = createWithTwoActions(pPrev, pNow);
        }
        else
        {
            break;
        }
    }

    return pPrev;
}

CCFiniteTimeAction* CCSpawn::actionWithArray(CCArray *arrayOfActions)
{
    return CCSpawn::create(arrayOfActions);
}

CCFiniteTimeAction* CCSpawn::create(CCArray *arrayOfActions)
{
    CCFiniteTimeAction* prev = (CCFiniteTimeAction*)arrayOfActions->objectAtIndex(0);

    for (unsigned int i = 1; i < arrayOfActions->count(); ++i)
    {
        prev = createWithTwoActions(prev, (CCFiniteTimeAction*)arrayOfActions->objectAtIndex(i));
    }

    return prev;
}

CCSpawn* CCSpawn::actionOneTwo(CCFiniteTimeAction *pAction1, CCFiniteTimeAction *pAction2)
{
    return CCSpawn::createWithTwoActions(pAction1, pAction2);
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
        m_pOne = pAction1;
        m_pTwo = pAction2;

        if (d1 > d2)
        {
            m_pTwo = CCSequence::createWithTwoActions(pAction2, CCDelayTime::create(d1 - d2));
        } 
        else if (d1 < d2)
        {
            m_pOne = CCSequence::createWithTwoActions(pAction1, CCDelayTime::create(d2 - d1));
        }

        m_pOne->retain();
        m_pTwo->retain();

        bRet = true;
    }

    
    return bRet;
}

CCObject* CCSpawn::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCSpawn* pCopy = NULL;

    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCSpawn*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCSpawn();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithTwoActions((CCFiniteTimeAction*)(m_pOne->copy()->autorelease()), 
                    (CCFiniteTimeAction*)(m_pTwo->copy()->autorelease()));

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

CCSpawn::~CCSpawn(void)
{
    CC_SAFE_RELEASE(m_pOne);
    CC_SAFE_RELEASE(m_pTwo);
}

void CCSpawn::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_pOne->startWithTarget(pTarget);
    m_pTwo->startWithTarget(pTarget);
}

void CCSpawn::stop(void)
{
    m_pOne->stop();
    m_pTwo->stop();
    CCActionInterval::stop();
}

void CCSpawn::update(float time)
{
    if (m_pOne)
    {
        m_pOne->update(time);
    }
    if (m_pTwo)
    {
        m_pTwo->update(time);
    }
}

CCActionInterval* CCSpawn::reverse(void)
{
    return CCSpawn::createWithTwoActions(m_pOne->reverse(), m_pTwo->reverse());
}

//
// RotateTo
//
CCRotateTo* CCRotateTo::actionWithDuration(float fDuration, float fDeltaAngle)
{
    return CCRotateTo::create(fDuration, fDeltaAngle);
}

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
        m_fDstAngleX = m_fDstAngleY = fDeltaAngle;
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
        m_fDstAngleX = fDeltaAngleX;
        m_fDstAngleY = fDeltaAngleY;
        
        return true;
    }
    
    return false;
}

CCObject* CCRotateTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCRotateTo* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCRotateTo*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCRotateTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_fDstAngleX, m_fDstAngleY);

    //Action *copy = [[[self class] allocWithZone: zone] initWithDuration:[self duration] angle: angle];
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCRotateTo::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    
    // Calculate X
    m_fStartAngleX = pTarget->getRotationX();
    
    m_fDiffAngleX = m_fDstAngleX - m_fStartAngleX;
    if (m_fDiffAngleX > 180)
    {
        m_fDiffAngleX -= 360;
    }
    if (m_fDiffAngleX < -180)
    {
        m_fDiffAngleX += 360;
    }
    
    // Calculate Y
    m_fStartAngleY = m_pTarget->getRotationY();

    if (m_fStartAngleY > 0)
    {
        m_fStartAngleY = fmodf(m_fStartAngleY, 360.0f);
    }
    else
    {
        m_fStartAngleY = fmodf(m_fStartAngleY, -360.0f);
    }

    m_fDiffAngleY = m_fDstAngleY - m_fStartAngleY;
    if (m_fDiffAngleY > 180)
    {
        m_fDiffAngleY -= 360;
    }

    if (m_fDiffAngleY < -180)
    {
        m_fDiffAngleY += 360;
    }
}

void CCRotateTo::update(float time)
{
    if (m_pTarget)
    {
        m_pTarget->setRotationX(m_fStartAngleX + m_fDiffAngleX * time);
        m_pTarget->setRotationY(m_fStartAngleY + m_fDiffAngleY * time);
    }
}

//
// RotateBy
//
CCRotateBy* CCRotateBy::actionWithDuration(float fDuration, float fDeltaAngle)
{
    return CCRotateBy::create(fDuration, fDeltaAngle);
}

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
        m_fAngleX = m_fAngleY = fDeltaAngle;
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
        m_fAngleX = fDeltaAngleX;
        m_fAngleY = fDeltaAngleY;
        return true;
    }
    
    return false;
}

CCObject* CCRotateBy::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCRotateBy* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCRotateBy*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCRotateBy();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_fAngleX, m_fAngleY);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCRotateBy::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_fStartAngleX = pTarget->getRotationX();
    m_fStartAngleY = pTarget->getRotationY();
}

void CCRotateBy::update(float time)
{
    // XXX: shall I add % 360
    if (m_pTarget)
    {
        m_pTarget->setRotationX(m_fStartAngleX + m_fAngleX * time);
        m_pTarget->setRotationY(m_fStartAngleY + m_fAngleY * time);
    }
}

CCActionInterval* CCRotateBy::reverse(void)
{
    return CCRotateBy::create(m_fDuration, -m_fAngleX, -m_fAngleY);
}

//
// MoveTo
//
CCMoveTo* CCMoveTo::actionWithDuration(float duration, const CCPoint& position)
{
    return CCMoveTo::create(duration, position);
}

CCMoveTo* CCMoveTo::create(float duration, const CCPoint& position)
{
    CCMoveTo *pMoveTo = new CCMoveTo();
    pMoveTo->initWithDuration(duration, position);
    pMoveTo->autorelease();

    return pMoveTo;
}

bool CCMoveTo::initWithDuration(float duration, const CCPoint& position)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_endPosition = position;
        return true;
    }

    return false;
}

CCObject* CCMoveTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCMoveTo* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCMoveTo*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCMoveTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_endPosition);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCMoveTo::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_startPosition = pTarget->getPosition();
    m_delta = ccpSub(m_endPosition, m_startPosition);
}

void CCMoveTo::update(float time)
{
    if (m_pTarget)
    {
        m_pTarget->setPosition(ccp(m_startPosition.x + m_delta.x * time,
            m_startPosition.y + m_delta.y * time));
    }
}

//
// MoveBy
//
CCMoveBy* CCMoveBy::actionWithDuration(float duration, const CCPoint& position)
{
    return CCMoveBy::create(duration, position);
}

CCMoveBy* CCMoveBy::create(float duration, const CCPoint& position)
{
    CCMoveBy *pMoveBy = new CCMoveBy();
    pMoveBy->initWithDuration(duration, position);
    pMoveBy->autorelease();

    return pMoveBy;
}

bool CCMoveBy::initWithDuration(float duration, const CCPoint& position)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_delta = position;
        return true;
    }

    return false;
}

CCObject* CCMoveBy::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCMoveBy* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCMoveBy*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCMoveBy();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCMoveTo::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_delta);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCMoveBy::startWithTarget(CCNode *pTarget)
{
    CCPoint dTmp = m_delta;
    CCMoveTo::startWithTarget(pTarget);
    m_delta = dTmp;
}

CCActionInterval* CCMoveBy::reverse(void)
{
    return CCMoveBy::create(m_fDuration, ccp(-m_delta.x, -m_delta.y));
}

//
// CCSkewTo
//
CCSkewTo* CCSkewTo::actionWithDuration(float t, float sx, float sy)
{
    return CCSkewTo::create(t, sx, sy);
}

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
        m_fEndSkewX = sx;
        m_fEndSkewY = sy;

        bRet = true;
    }

    return bRet;
}

CCObject* CCSkewTo::copyWithZone(CCZone* pZone)
{
    CCZone* pNewZone = NULL;
    CCSkewTo* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCSkewTo*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCSkewTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_fEndSkewX, m_fEndSkewY);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCSkewTo::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);

    m_fStartSkewX = pTarget->getSkewX();

    if (m_fStartSkewX > 0)
    {
        m_fStartSkewX = fmodf(m_fStartSkewX, 180.f);
    }
    else
    {
        m_fStartSkewX = fmodf(m_fStartSkewX, -180.f);
    }

    m_fDeltaX = m_fEndSkewX - m_fStartSkewX;

    if (m_fDeltaX > 180)
    {
        m_fDeltaX -= 360;
    }
    if (m_fDeltaX < -180)
    {
        m_fDeltaX += 360;
    }

    m_fStartSkewY = pTarget->getSkewY();

    if (m_fStartSkewY > 0)
    {
        m_fStartSkewY = fmodf(m_fStartSkewY, 360.f);
    }
    else
    {
        m_fStartSkewY = fmodf(m_fStartSkewY, -360.f);
    }

    m_fDeltaY = m_fEndSkewY - m_fStartSkewY;

    if (m_fDeltaY > 180)
    {
        m_fDeltaY -= 360;
    }
    if (m_fDeltaY < -180)
    {
        m_fDeltaY += 360;
    }
}

void CCSkewTo::update(float t)
{
    m_pTarget->setSkewX(m_fStartSkewX + m_fDeltaX * t);
    m_pTarget->setSkewY(m_fStartSkewY + m_fDeltaY * t);
}

CCSkewTo::CCSkewTo()
: m_fSkewX(0.0)
, m_fSkewY(0.0)
, m_fStartSkewX(0.0)
, m_fStartSkewY(0.0)
, m_fEndSkewX(0.0)
, m_fEndSkewY(0.0)
, m_fDeltaX(0.0)
, m_fDeltaY(0.0)
{
}

//
// CCSkewBy
//
CCSkewBy* CCSkewBy::actionWithDuration(float t, float sx, float sy)
{
    return CCSkewBy::create(t, sx, sy);
}

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

bool CCSkewBy::initWithDuration(float t, float deltaSkewX, float deltaSkewY)
{
    bool bRet = false;

    if (CCSkewTo::initWithDuration(t, deltaSkewX, deltaSkewY))
    {
        m_fSkewX = deltaSkewX;
        m_fSkewY = deltaSkewY;

        bRet = true;
    }

    return bRet;
}

void CCSkewBy::startWithTarget(CCNode *pTarget)
{
    CCSkewTo::startWithTarget(pTarget);
    m_fDeltaX = m_fSkewX;
    m_fDeltaY = m_fSkewY;
    m_fEndSkewX = m_fStartSkewX + m_fDeltaX;
    m_fEndSkewY = m_fStartSkewY + m_fDeltaY;
}

CCActionInterval* CCSkewBy::reverse()
{
    return create(m_fDuration, -m_fSkewX, -m_fSkewY);
}

//
// JumpBy
//
CCJumpBy* CCJumpBy::actionWithDuration(float duration, const CCPoint& position, float height, unsigned int jumps)
{
    return CCJumpBy::create(duration, position, height, jumps);
}

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
        m_delta = position;
        m_height = height;
        m_nJumps = jumps;

        return true;
    }

    return false;
}

CCObject* CCJumpBy::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCJumpBy* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCJumpBy*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCJumpBy();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_delta, m_height, m_nJumps);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCJumpBy::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_startPosition = pTarget->getPosition();
}

void CCJumpBy::update(float time)
{
    // parabolic jump (since v0.8.2)
    if (m_pTarget)
    {
        float frac = fmodf(time * m_nJumps, 1.0f);
        float y = m_height * 4 * frac * (1 - frac);
        y += m_delta.y * time;
        float x = m_delta.x * time;
        m_pTarget->setPosition(ccp(m_startPosition.x + x, m_startPosition.y + y));
    }
}

CCActionInterval* CCJumpBy::reverse(void)
{
    return CCJumpBy::create(m_fDuration, ccp(-m_delta.x, -m_delta.y),
        m_height, m_nJumps);
}

//
// JumpTo
//
CCJumpTo* CCJumpTo::actionWithDuration(float duration, const CCPoint& position, float height, int jumps)
{
    return CCJumpTo::create(duration, position, height, jumps);
}

CCJumpTo* CCJumpTo::create(float duration, const CCPoint& position, float height, int jumps)
{
    CCJumpTo *pJumpTo = new CCJumpTo();
    pJumpTo->initWithDuration(duration, position, height, jumps);
    pJumpTo->autorelease();

    return pJumpTo;
}

CCObject* CCJumpTo::copyWithZone(CCZone* pZone)
{
    CCZone* pNewZone = NULL;
    CCJumpTo* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCJumpTo*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCJumpTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCJumpBy::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_delta, m_height, m_nJumps);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCJumpTo::startWithTarget(CCNode *pTarget)
{
    CCJumpBy::startWithTarget(pTarget);
    m_delta = ccp(m_delta.x - m_startPosition.x, m_delta.y - m_startPosition.y);
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
CCBezierBy* CCBezierBy::actionWithDuration(float t, const ccBezierConfig& c)
{
    return CCBezierBy::create(t, c);
}

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
        m_sConfig = c;
        return true;
    }

    return false;
}

void CCBezierBy::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_startPosition = pTarget->getPosition();
}

CCObject* CCBezierBy::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCBezierBy* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCBezierBy*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCBezierBy();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_sConfig);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCBezierBy::update(float time)
{
    if (m_pTarget)
    {
        float xa = 0;
        float xb = m_sConfig.controlPoint_1.x;
        float xc = m_sConfig.controlPoint_2.x;
        float xd = m_sConfig.endPosition.x;

        float ya = 0;
        float yb = m_sConfig.controlPoint_1.y;
        float yc = m_sConfig.controlPoint_2.y;
        float yd = m_sConfig.endPosition.y;

        float x = bezierat(xa, xb, xc, xd, time);
        float y = bezierat(ya, yb, yc, yd, time);
        m_pTarget->setPosition(ccpAdd(m_startPosition, ccp(x, y)));
    }
}

CCActionInterval* CCBezierBy::reverse(void)
{
    ccBezierConfig r;

    r.endPosition = ccpNeg(m_sConfig.endPosition);
    r.controlPoint_1 = ccpAdd(m_sConfig.controlPoint_2, ccpNeg(m_sConfig.endPosition));
    r.controlPoint_2 = ccpAdd(m_sConfig.controlPoint_1, ccpNeg(m_sConfig.endPosition));

    CCBezierBy *pAction = CCBezierBy::create(m_fDuration, r);
    return pAction;
}

//
// BezierTo
//
CCBezierTo* CCBezierTo::actionWithDuration(float t, const ccBezierConfig& c)
{
    return CCBezierTo::create(t, c);
}

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
        m_sToConfig = c;
    }
    
    return bRet;
}

CCObject* CCBezierTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCBezierBy* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCBezierTo*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCBezierTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCBezierBy::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_sConfig);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCBezierTo::startWithTarget(CCNode *pTarget)
{
    CCBezierBy::startWithTarget(pTarget);
    m_sConfig.controlPoint_1 = ccpSub(m_sToConfig.controlPoint_1, m_startPosition);
    m_sConfig.controlPoint_2 = ccpSub(m_sToConfig.controlPoint_2, m_startPosition);
    m_sConfig.endPosition = ccpSub(m_sToConfig.endPosition, m_startPosition);
}

//
// ScaleTo
//
CCScaleTo* CCScaleTo::actionWithDuration(float duration, float s)
{
    return CCScaleTo::create(duration, s);
}

CCScaleTo* CCScaleTo::create(float duration, float s)
{
    CCScaleTo *pScaleTo = new CCScaleTo();
    pScaleTo->initWithDuration(duration, s);
    pScaleTo->autorelease();

    return pScaleTo;
}

bool CCScaleTo::initWithDuration(float duration, float s)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_fEndScaleX = s;
        m_fEndScaleY = s;

        return true;
    }

    return false;
}

CCScaleTo* CCScaleTo::actionWithDuration(float duration, float sx, float sy)
{
    return CCScaleTo::create(duration, sx, sy);
}

CCScaleTo* CCScaleTo::create(float duration, float sx, float sy)
{
    CCScaleTo *pScaleTo = new CCScaleTo();
    pScaleTo->initWithDuration(duration, sx, sy);
    pScaleTo->autorelease();

    return pScaleTo;
}

bool CCScaleTo::initWithDuration(float duration, float sx, float sy)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_fEndScaleX = sx;
        m_fEndScaleY = sy;

        return true;
    }

    return false;
}

CCObject* CCScaleTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCScaleTo* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCScaleTo*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCScaleTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);


    pCopy->initWithDuration(m_fDuration, m_fEndScaleX, m_fEndScaleY);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCScaleTo::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_fStartScaleX = pTarget->getScaleX();
    m_fStartScaleY = pTarget->getScaleY();
    m_fDeltaX = m_fEndScaleX - m_fStartScaleX;
    m_fDeltaY = m_fEndScaleY - m_fStartScaleY;
}

void CCScaleTo::update(float time)
{
    if (m_pTarget)
    {
        m_pTarget->setScaleX(m_fStartScaleX + m_fDeltaX * time);
        m_pTarget->setScaleY(m_fStartScaleY + m_fDeltaY * time);
    }
}

//
// ScaleBy
//
CCScaleBy* CCScaleBy::actionWithDuration(float duration, float s)
{
    return create(duration, s);
}

CCScaleBy* CCScaleBy::actionWithDuration(float duration, float sx, float sy)
{
    return create(duration, sx, sy);
}

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

CCObject* CCScaleBy::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCScaleTo* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCScaleBy*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCScaleBy();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCScaleTo::copyWithZone(pZone);


    pCopy->initWithDuration(m_fDuration, m_fEndScaleX, m_fEndScaleY);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCScaleBy::startWithTarget(CCNode *pTarget)
{
    CCScaleTo::startWithTarget(pTarget);
    m_fDeltaX = m_fStartScaleX * m_fEndScaleX - m_fStartScaleX;
    m_fDeltaY = m_fStartScaleY * m_fEndScaleY - m_fStartScaleY;
}

CCActionInterval* CCScaleBy::reverse(void)
{
    return CCScaleBy::create(m_fDuration, 1 / m_fEndScaleX, 1 / m_fEndScaleY);
}

//
// Blink
//
CCBlink* CCBlink::actionWithDuration(float duration, unsigned int uBlinks)
{
    return CCBlink::create(duration, uBlinks);
}

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
        m_nTimes = uBlinks;
        return true;
    }

    return false;
}

void CCBlink::stop()
{
    m_pTarget->setVisible(m_bOriginalState);
    CCActionInterval::stop();
}

void CCBlink::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_bOriginalState = pTarget->isVisible();
}

CCObject* CCBlink::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCBlink* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCBlink*)(pZone->m_pCopyObject);

    }
    else
    {
        pCopy = new CCBlink();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, (unsigned int)m_nTimes);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCBlink::update(float time)
{
    if (m_pTarget && ! isDone())
    {
        float slice = 1.0f / m_nTimes;
        float m = fmodf(time, slice);
        m_pTarget->setVisible(m > slice / 2 ? true : false);
    }
}

CCActionInterval* CCBlink::reverse(void)
{
    // return 'self'
    return CCBlink::create(m_fDuration, m_nTimes);
}

//
// FadeIn
//
CCFadeIn* CCFadeIn::actionWithDuration(float d)
{
    return CCFadeIn::create(d);
}

CCFadeIn* CCFadeIn::create(float d)
{
    CCFadeIn* pAction = new CCFadeIn();

    pAction->initWithDuration(d);
    pAction->autorelease();

    return pAction;
}

CCObject* CCFadeIn::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCFadeIn* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCFadeIn*)(pZone->m_pCopyObject);
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
    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pTarget);
    if (pRGBAProtocol)
    {
        pRGBAProtocol->setOpacity((GLubyte)(255 * time));
    }
    /*m_pTarget->setOpacity((GLubyte)(255 * time));*/
}

CCActionInterval* CCFadeIn::reverse(void)
{
    return CCFadeOut::create(m_fDuration);
}

//
// FadeOut
//
CCFadeOut* CCFadeOut::actionWithDuration(float d)
{
    return CCFadeOut::create(d);
}

CCFadeOut* CCFadeOut::create(float d)
{
    CCFadeOut* pAction = new CCFadeOut();

    pAction->initWithDuration(d);
    pAction->autorelease();

    return pAction;
}

CCObject* CCFadeOut::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCFadeOut* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCFadeOut*)(pZone->m_pCopyObject);
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
    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pTarget);
    if (pRGBAProtocol)
    {
        pRGBAProtocol->setOpacity(GLubyte(255 * (1 - time)));
    }
    /*m_pTarget->setOpacity(GLubyte(255 * (1 - time)));*/    
}

CCActionInterval* CCFadeOut::reverse(void)
{
    return CCFadeIn::create(m_fDuration);
}

//
// FadeTo
//
CCFadeTo* CCFadeTo::actionWithDuration(float duration, GLubyte opacity)
{
     return CCFadeTo::create(duration, opacity);
}

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
        m_toOpacity = opacity;
        return true;
    }

    return false;
}

CCObject* CCFadeTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCFadeTo* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCFadeTo*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCFadeTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_toOpacity);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCFadeTo::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);

    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pTarget);
    if (pRGBAProtocol)
    {
        m_fromOpacity = pRGBAProtocol->getOpacity();
    }
    /*m_fromOpacity = pTarget->getOpacity();*/
}

void CCFadeTo::update(float time)
{
    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pTarget);
    if (pRGBAProtocol)
    {
        pRGBAProtocol->setOpacity((GLubyte)(m_fromOpacity + (m_toOpacity - m_fromOpacity) * time));
    }
    /*m_pTarget->setOpacity((GLubyte)(m_fromOpacity + (m_toOpacity - m_fromOpacity) * time));*/
}

//
// TintTo
//
CCTintTo* CCTintTo::actionWithDuration(float duration, GLubyte red, GLubyte green, GLubyte blue)
{
    return CCTintTo::create(duration, red, green, blue);
}

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
        m_to = ccc3(red, green, blue);
        return true;
    }

    return false;
}

CCObject* CCTintTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCTintTo* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCTintTo*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCTintTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_to.r, m_to.g, m_to.b);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCTintTo::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pTarget);
    if (pRGBAProtocol)
    {
        m_from = pRGBAProtocol->getColor();
    }
    /*m_from = pTarget->getColor();*/
}

void CCTintTo::update(float time)
{
    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pTarget);
    if (pRGBAProtocol)
    {
        pRGBAProtocol->setColor(ccc3(GLubyte(m_from.r + (m_to.r - m_from.r) * time), 
            (GLbyte)(m_from.g + (m_to.g - m_from.g) * time),
            (GLbyte)(m_from.b + (m_to.b - m_from.b) * time)));
    }    
}

//
// TintBy
//
CCTintBy* CCTintBy::actionWithDuration(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue)
{
    return CCTintBy::create(duration, deltaRed, deltaGreen, deltaBlue);
}

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
        m_deltaR = deltaRed;
        m_deltaG = deltaGreen;
        m_deltaB = deltaBlue;

        return true;
    }

    return false;
}

CCObject* CCTintBy::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCTintBy* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCTintBy*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCTintBy();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, (GLubyte)m_deltaR, (GLubyte)m_deltaG, (GLubyte)m_deltaB);

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
        m_fromR = color.r;
        m_fromG = color.g;
        m_fromB = color.b;
    }    
}

void CCTintBy::update(float time)
{
    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pTarget);
    if (pRGBAProtocol)
    {
        pRGBAProtocol->setColor(ccc3((GLubyte)(m_fromR + m_deltaR * time),
            (GLubyte)(m_fromG + m_deltaG * time),
            (GLubyte)(m_fromB + m_deltaB * time)));
    }    
}

CCActionInterval* CCTintBy::reverse(void)
{
    return CCTintBy::create(m_fDuration, -m_deltaR, -m_deltaG, -m_deltaB);
}

//
// DelayTime
//
CCDelayTime* CCDelayTime::actionWithDuration(float d)
{
    return CCDelayTime::create(d);
}

CCDelayTime* CCDelayTime::create(float d)
{
    CCDelayTime* pAction = new CCDelayTime();

    pAction->initWithDuration(d);
    pAction->autorelease();

    return pAction;
}

CCObject* CCDelayTime::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCDelayTime* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCDelayTime*)(pZone->m_pCopyObject);
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

CCActionInterval* CCDelayTime::reverse(void)
{
    return CCDelayTime::create(m_fDuration);
}

//
// ReverseTime
//
CCReverseTime* CCReverseTime::actionWithAction(CCFiniteTimeAction *pAction)
{
    return CCReverseTime::create(pAction);
}

CCReverseTime* CCReverseTime::create(CCFiniteTimeAction *pAction)
{
    // casting to prevent warnings
    CCReverseTime *pReverseTime = new CCReverseTime();
    pReverseTime->initWithAction(pAction);
    pReverseTime->autorelease();

    return pReverseTime;
}

bool CCReverseTime::initWithAction(CCFiniteTimeAction *pAction)
{
    CCAssert(pAction != NULL, "");
    CCAssert(pAction != m_pOther, "");

    if (CCActionInterval::initWithDuration(pAction->getDuration()))
    {
        // Don't leak if action is reused
        CC_SAFE_RELEASE(m_pOther);

        m_pOther = pAction;
        pAction->retain();

        return true;
    }

    return false;
}

CCObject* CCReverseTime::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCReverseTime* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCReverseTime*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCReverseTime();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithAction((CCFiniteTimeAction*)(m_pOther->copy()->autorelease()));

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

CCReverseTime::CCReverseTime() : m_pOther(NULL) 
{

}

CCReverseTime::~CCReverseTime(void)
{
    CC_SAFE_RELEASE(m_pOther);
}

void CCReverseTime::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_pOther->startWithTarget(pTarget);
}

void CCReverseTime::stop(void)
{
    m_pOther->stop();
    CCActionInterval::stop();
}

void CCReverseTime::update(float time)
{
    if (m_pOther)
    {
        m_pOther->update(1 - time);
    }
}

CCActionInterval* CCReverseTime::reverse(void)
{
    return (CCActionInterval*)(m_pOther->copy()->autorelease());
}

//
// Animate
//
CCAnimate* CCAnimate::actionWithAnimation(CCAnimation *pAnimation)
{
    return CCAnimate::create(pAnimation);
}

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
        m_nNextFrame = 0;
        setAnimation(pAnimation);
        m_pOrigFrame = NULL;
        m_uExecutedLoops = 0;

        m_pSplitTimes->reserve(pAnimation->getFrames()->count());

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
            m_pSplitTimes->push_back(value);
        }    
        return true;
    }
    return false;
}

CCObject* CCAnimate::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCAnimate* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCAnimate*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCAnimate();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithAnimation((CCAnimation*)m_pAnimation->copy()->autorelease());

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

CCAnimate::CCAnimate()
: m_pAnimation(NULL)
, m_pSplitTimes(new std::vector<float>)
, m_nNextFrame(0)
, m_pOrigFrame(NULL)
, m_uExecutedLoops(0)
{

}

CCAnimate::~CCAnimate()
{
    CC_SAFE_RELEASE(m_pAnimation);
    CC_SAFE_RELEASE(m_pOrigFrame);
    CC_SAFE_DELETE(m_pSplitTimes);
}

void CCAnimate::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    CCSprite *pSprite = (CCSprite*)(pTarget);

    CC_SAFE_RELEASE(m_pOrigFrame);

    if (m_pAnimation->getRestoreOriginalFrame())
    {
        m_pOrigFrame = pSprite->displayFrame();
        m_pOrigFrame->retain();
    }
    m_nNextFrame = 0;
    m_uExecutedLoops = 0;
}

void CCAnimate::stop(void)
{
    if (m_pAnimation->getRestoreOriginalFrame() && m_pTarget)
    {
        ((CCSprite*)(m_pTarget))->setDisplayFrame(m_pOrigFrame);
    }

    CCActionInterval::stop();
}

void CCAnimate::update(float t)
{
    // if t==1, ignore. Animation should finish with t==1
    if( t < 1.0f ) {
        t *= m_pAnimation->getLoops();

        // new loop?  If so, reset frame counter
        unsigned int loopNumber = (unsigned int)t;
        if( loopNumber > m_uExecutedLoops ) {
            m_nNextFrame = 0;
            m_uExecutedLoops++;
        }

        // new t for animations
        t = fmodf(t, 1.0f);
    }

    CCArray* frames = m_pAnimation->getFrames();
    unsigned int numberOfFrames = frames->count();
    CCSpriteFrame *frameToDisplay = NULL;

    for( unsigned int i=m_nNextFrame; i < numberOfFrames; i++ ) {
        float splitTime = m_pSplitTimes->at(i);

        if( splitTime <= t ) {
            CCAnimationFrame* frame = (CCAnimationFrame*)frames->objectAtIndex(i);
            frameToDisplay = frame->getSpriteFrame();
            ((CCSprite*)m_pTarget)->setDisplayFrame(frameToDisplay);

            CCDictionary* dict = frame->getUserInfo();
            if( dict )
            {
                //TODO: [[NSNotificationCenter defaultCenter] postNotificationName:CCAnimationFrameDisplayedNotification object:target_ userInfo:dict];
            }
            m_nNextFrame = i+1;

            break;
        }
    }
}

CCActionInterval* CCAnimate::reverse(void)
{
    CCArray* pOldArray = m_pAnimation->getFrames();
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

            pNewArray->addObject((CCAnimationFrame*)(pElement->copy()->autorelease()));
        }
    }

    CCAnimation *newAnim = CCAnimation::create(pNewArray, m_pAnimation->getDelayPerUnit(), m_pAnimation->getLoops());
    newAnim->setRestoreOriginalFrame(m_pAnimation->getRestoreOriginalFrame());
    return create(newAnim);
}

// CCTargetedAction

CCTargetedAction::CCTargetedAction()
: m_pForcedTarget(NULL)
, m_pAction(NULL)
{

}

CCTargetedAction::~CCTargetedAction()
{
    CC_SAFE_RELEASE(m_pForcedTarget);
    CC_SAFE_RELEASE(m_pAction);
}

CCTargetedAction* CCTargetedAction::actionWithTarget(CCNode* pTarget, CCFiniteTimeAction* pAction)
{
    return CCTargetedAction::create(pTarget, pAction);
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
        m_pForcedTarget = pTarget;
        CC_SAFE_RETAIN(pAction);
        m_pAction = pAction;
        return true;
    }
    return false;
}

CCObject* CCTargetedAction::copyWithZone(CCZone* pZone)
{
    CCZone* pNewZone = NULL;
    CCTargetedAction* pRet = NULL;
    if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
    {
        pRet = (CCTargetedAction*)(pZone->m_pCopyObject);
    }
    else
    {
        pRet = new CCTargetedAction();
        pZone = pNewZone = new CCZone(pRet);
    }
    CCActionInterval::copyWithZone(pZone);
    // win32 : use the m_pOther's copy object.
    pRet->initWithTarget(m_pForcedTarget, (CCFiniteTimeAction*)m_pAction->copy()->autorelease()); 
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCTargetedAction::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_pAction->startWithTarget(m_pForcedTarget);
}

void CCTargetedAction::stop(void)
{
    m_pAction->stop();
}

void CCTargetedAction::update(float time)
{
    m_pAction->update(time);
}

NS_CC_END
