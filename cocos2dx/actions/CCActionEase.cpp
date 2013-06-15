/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2009 Jason Booth

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

/*
 * Elastic, Back and Bounce actions based on code from:
 * http://github.com/NikhilK/silverlightfx/
 *
 * by http://github.com/NikhilK
 */

#include "CCActionEase.h"
#include "cocoa/CCZone.h"

NS_CC_BEGIN

#ifndef M_PI_X_2
#define M_PI_X_2 (float)M_PI * 2.0f
#endif

//
// EaseAction
//

bool CCActionEase::initWithAction(CCActionInterval *pAction)
{
    CCAssert(pAction != NULL, "");

    if (CCActionInterval::initWithDuration(pAction->getDuration()))
    {
        m_pInner = pAction;
        pAction->retain();

        return true;
    }

    return false;
}

CCActionEase::~CCActionEase(void)
{
    CC_SAFE_RELEASE(m_pInner);
}

void CCActionEase::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_pInner->startWithTarget(m_pTarget);
}

void CCActionEase::stop(void)
{
    m_pInner->stop();
    CCActionInterval::stop();
}

void CCActionEase::update(float time)
{
    m_pInner->update(time);
}

CCActionInterval* CCActionEase::getInnerAction()
{
    return m_pInner;
}

//
// EaseRateAction
//

bool CCEaseRateAction::initWithAction(CCActionInterval *pAction, float fRate)
{
    if (CCActionEase::initWithAction(pAction))
    {
        m_fRate = fRate;
        return true;
    }

    return false;
}

CCEaseRateAction::~CCEaseRateAction(void)
{
}

//
// EeseIn
//

CCEaseIn* CCEaseIn::create(CCActionInterval *pAction, float fRate)
{
    CCEaseIn *pRet = new CCEaseIn();
    if (pRet)
    {
        if (pRet->initWithAction(pAction, fRate))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet;
}

CCEaseIn* CCEaseIn::clone() const
{
	auto a = new CCEaseIn(*this);
	a->initWithAction((CCActionInterval*)m_pInner->clone(), m_fRate);
	a->autorelease();
	return a;
}

CCObject* CCEaseIn::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseIn* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCEaseIn*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseIn();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAction((CCActionInterval*)(m_pInner->copy()->autorelease()), m_fRate);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCEaseIn::update(float time)
{
    m_pInner->update(powf(time, m_fRate));
}

CCEaseIn* CCEaseIn::reverse() const
{
    return CCEaseIn::create(m_pInner->reverse(), 1 / m_fRate);
}

//
// EaseOut
//
CCEaseOut* CCEaseOut::create(CCActionInterval *pAction, float fRate)
{
    CCEaseOut *pRet = new CCEaseOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction, fRate))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet;   
}

CCEaseOut* CCEaseOut::clone() const
{
	auto a = new CCEaseOut(*this);
	a->initWithAction((CCActionInterval*)m_pInner->clone(), m_fRate);
	a->autorelease();
	return a;
}

CCObject* CCEaseOut::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseOut* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCEaseOut*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseOut();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAction((CCActionInterval*)(m_pInner->copy()->autorelease()), m_fRate);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCEaseOut::update(float time)
{
    m_pInner->update(powf(time, 1 / m_fRate));
}

CCEaseOut* CCEaseOut::reverse() const
{
    return CCEaseOut::create(m_pInner->reverse(), 1 / m_fRate);
}

//
// EaseInOut
//
CCEaseInOut* CCEaseInOut::create(CCActionInterval *pAction, float fRate)
{
    CCEaseInOut *pRet = new CCEaseInOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction, fRate))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

CCEaseInOut* CCEaseInOut::clone() const
{
	auto a = new CCEaseInOut(*this);
	a->initWithAction((CCActionInterval*)m_pInner->clone(), m_fRate);
	a->autorelease();
	return a;
}

CCObject* CCEaseInOut::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseInOut* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCEaseInOut*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseInOut();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAction((CCActionInterval*)(m_pInner->copy()->autorelease()), m_fRate);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCEaseInOut::update(float time)
{
    time *= 2;
    if (time < 1)
    {
        m_pInner->update(0.5f * powf(time, m_fRate));
    }
    else
    {
        m_pInner->update(1.0f - 0.5f * powf(2-time, m_fRate));
    }
}

// InOut and OutIn are symmetrical
CCEaseInOut* CCEaseInOut::reverse() const
{
    return CCEaseInOut::create(m_pInner->reverse(), m_fRate);
}

//
// EaseExponentialIn
//
CCEaseExponentialIn* CCEaseExponentialIn::create(CCActionInterval* pAction)
{
    CCEaseExponentialIn *pRet = new CCEaseExponentialIn();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet;    
}

CCEaseExponentialIn* CCEaseExponentialIn::clone() const
{
	auto a = new CCEaseExponentialIn(*this);
	a->initWithAction((CCActionInterval *)m_pInner->clone());
	a->autorelease();
	return a;
}

CCObject* CCEaseExponentialIn::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseExponentialIn* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCEaseExponentialIn*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseExponentialIn();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCEaseExponentialIn::update(float time)
{
    m_pInner->update(time == 0 ? 0 : powf(2, 10 * (time/1 - 1)) - 1 * 0.001f);
}

CCActionEase * CCEaseExponentialIn::reverse() const
{
    return CCEaseExponentialOut::create(m_pInner->reverse());
}

//
// EaseExponentialOut
//
CCEaseExponentialOut* CCEaseExponentialOut::create(CCActionInterval* pAction)
{
    CCEaseExponentialOut *pRet = new CCEaseExponentialOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

CCEaseExponentialOut* CCEaseExponentialOut::clone() const
{
	auto a = new CCEaseExponentialOut(*this);
	a->initWithAction((CCActionInterval *)m_pInner->clone());
	a->autorelease();
	return a;
}

CCObject* CCEaseExponentialOut::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseExponentialOut* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCEaseExponentialOut*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseExponentialOut();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCEaseExponentialOut::update(float time)
{
    m_pInner->update(time == 1 ? 1 : (-powf(2, -10 * time / 1) + 1));
}

CCActionEase* CCEaseExponentialOut::reverse() const
{
    return CCEaseExponentialIn::create(m_pInner->reverse());
}

//
// EaseExponentialInOut
//

CCEaseExponentialInOut* CCEaseExponentialInOut::create(CCActionInterval *pAction)
{
    CCEaseExponentialInOut *pRet = new CCEaseExponentialInOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

CCEaseExponentialInOut* CCEaseExponentialInOut::clone() const
{
	auto a = new CCEaseExponentialInOut(*this);
	a->initWithAction((CCActionInterval *)m_pInner->clone());
	a->autorelease();
	return a;
}

CCObject* CCEaseExponentialInOut::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseExponentialInOut* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCEaseExponentialInOut*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseExponentialInOut();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCEaseExponentialInOut::update(float time)
{
    time /= 0.5f;
    if (time < 1)
    {
        time = 0.5f * powf(2, 10 * (time - 1));
    }
    else
    {
        time = 0.5f * (-powf(2, -10 * (time - 1)) + 2);
    }

    m_pInner->update(time);
}

CCEaseExponentialInOut* CCEaseExponentialInOut::reverse() const
{
    return CCEaseExponentialInOut::create(m_pInner->reverse());
}

//
// EaseSineIn
//

CCEaseSineIn* CCEaseSineIn::create(CCActionInterval* pAction)
{
    CCEaseSineIn *pRet = new CCEaseSineIn();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

CCEaseSineIn* CCEaseSineIn::clone() const
{
	auto a = new CCEaseSineIn(*this);
	a->initWithAction((CCActionInterval *)m_pInner->clone());
	a->autorelease();
	return a;
}

CCObject* CCEaseSineIn::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseSineIn* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCEaseSineIn*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseSineIn();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCEaseSineIn::update(float time)
{
    m_pInner->update(-1 * cosf(time * (float)M_PI_2) + 1);
}

CCActionEase* CCEaseSineIn::reverse() const
{
    return CCEaseSineOut::create(m_pInner->reverse());
}

//
// EaseSineOut
//

CCEaseSineOut* CCEaseSineOut::create(CCActionInterval* pAction)
{
    CCEaseSineOut *pRet = new CCEaseSineOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

CCEaseSineOut* CCEaseSineOut::clone() const
{
	auto a = new CCEaseSineOut(*this);
	a->initWithAction((CCActionInterval *)m_pInner->clone());
	a->autorelease();
	return a;
}

CCObject* CCEaseSineOut::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseSineOut* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCEaseSineOut*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseSineOut();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCEaseSineOut::update(float time)
{
    m_pInner->update(sinf(time * (float)M_PI_2));
}

CCActionEase* CCEaseSineOut::reverse(void) const
{
    return CCEaseSineIn::create(m_pInner->reverse());
}

//
// EaseSineInOut
//

CCEaseSineInOut* CCEaseSineInOut::create(CCActionInterval* pAction)
{
    CCEaseSineInOut *pRet = new CCEaseSineInOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

CCEaseSineInOut* CCEaseSineInOut::clone() const
{
	auto a = new CCEaseSineInOut(*this);
	a->initWithAction((CCActionInterval *)m_pInner->clone());
	a->autorelease();
	return a;
}

CCObject* CCEaseSineInOut::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseSineInOut* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCEaseSineInOut*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseSineInOut();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCEaseSineInOut::update(float time)
{
    m_pInner->update(-0.5f * (cosf((float)M_PI * time) - 1));
}

CCEaseSineInOut* CCEaseSineInOut::reverse() const
{
    return CCEaseSineInOut::create(m_pInner->reverse());
}

//
// EaseElastic
//

bool CCEaseElastic::initWithAction(CCActionInterval *pAction, float fPeriod/* = 0.3f*/)
{
    if (CCActionEase::initWithAction(pAction))
    {
        m_fPeriod = fPeriod;
        return true;
    }

    return false;
}

//
// EaseElasticIn
//

CCEaseElasticIn* CCEaseElasticIn::create(CCActionInterval *pAction)
{
    return CCEaseElasticIn::create(pAction, 0.3f);
}

CCEaseElasticIn* CCEaseElasticIn::create(CCActionInterval *pAction, float fPeriod/* = 0.3f*/)
{
    CCEaseElasticIn *pRet = new CCEaseElasticIn();
    if (pRet)
    {
        if (pRet->initWithAction(pAction, fPeriod))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

CCEaseElasticIn* CCEaseElasticIn::clone() const
{
	auto a = new CCEaseElasticIn(*this);
	a->initWithAction((CCActionInterval *)m_pInner->clone(), m_fPeriod);
	a->autorelease();
	return a;
}

CCObject* CCEaseElasticIn::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseElasticIn* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCEaseElasticIn*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseElasticIn();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()), m_fPeriod);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCEaseElasticIn::update(float time)
{
    float newT = 0;
    if (time == 0 || time == 1)
    {
        newT = time;
    }
    else
    {
        float s = m_fPeriod / 4;
        time = time - 1;
        newT = -powf(2, 10 * time) * sinf((time - s) * M_PI_X_2 / m_fPeriod);
    }

    m_pInner->update(newT);
}

CCEaseElastic* CCEaseElasticIn::reverse() const
{
    return CCEaseElasticOut::create(m_pInner->reverse(), m_fPeriod);
}

//
// EaseElasticOut
//

CCEaseElasticOut* CCEaseElasticOut::create(CCActionInterval *pAction)
{
    return CCEaseElasticOut::create(pAction, 0.3f);
}

CCEaseElasticOut* CCEaseElasticOut::create(CCActionInterval *pAction, float fPeriod/* = 0.3f*/)
{
    CCEaseElasticOut *pRet = new CCEaseElasticOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction, fPeriod))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

CCEaseElasticOut* CCEaseElasticOut::clone() const
{
	auto a = new CCEaseElasticOut(*this);
	a->initWithAction((CCActionInterval *)m_pInner->clone(), m_fPeriod);
	a->autorelease();
	return a;
}

CCObject *CCEaseElasticOut::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseElasticOut* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCEaseElasticOut*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseElasticOut();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()), m_fPeriod);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCEaseElasticOut::update(float time)
{
    float newT = 0;
    if (time == 0 || time == 1)
    {
        newT = time;
    }
    else
    {
        float s = m_fPeriod / 4;
        newT = powf(2, -10 * time) * sinf((time - s) * M_PI_X_2 / m_fPeriod) + 1;
    }

    m_pInner->update(newT);
}

CCEaseElastic* CCEaseElasticOut::reverse() const
{
    return CCEaseElasticIn::create(m_pInner->reverse(), m_fPeriod);
}

//
// EaseElasticInOut
//

CCEaseElasticInOut* CCEaseElasticInOut::create(CCActionInterval *pAction)
{
    return CCEaseElasticInOut::create(pAction, 0.3f);
}

CCEaseElasticInOut* CCEaseElasticInOut::create(CCActionInterval *pAction, float fPeriod/* = 0.3f*/)
{
    CCEaseElasticInOut *pRet = new CCEaseElasticInOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction, fPeriod))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

CCEaseElasticInOut* CCEaseElasticInOut::clone() const
{
	auto a = new CCEaseElasticInOut(*this);
	a->initWithAction((CCActionInterval *)m_pInner->clone(), m_fPeriod);
	a->autorelease();
	return a;
}

CCObject* CCEaseElasticInOut::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseElasticInOut* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCEaseElasticInOut*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseElasticInOut();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()), m_fPeriod);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;

}

void CCEaseElasticInOut::update(float time)
{
    float newT = 0;
    if (time == 0 || time == 1)
    {
        newT = time;
    }
    else
    {
        time = time * 2;
        if (! m_fPeriod)
        {
            m_fPeriod = 0.3f * 1.5f;
        }

        float s = m_fPeriod / 4;

        time = time - 1;
        if (time < 0)
        {
            newT = -0.5f * powf(2, 10 * time) * sinf((time -s) * M_PI_X_2 / m_fPeriod);
        }
        else
        {
            newT = powf(2, -10 * time) * sinf((time - s) * M_PI_X_2 / m_fPeriod) * 0.5f + 1;
        }
    }

    m_pInner->update(newT);
}

CCEaseElasticInOut* CCEaseElasticInOut::reverse() const
{
    return CCEaseElasticInOut::create(m_pInner->reverse(), m_fPeriod);
}

//
// EaseBounce
//

float CCEaseBounce::bounceTime(float time)
{
    if (time < 1 / 2.75)
    {
        return 7.5625f * time * time;
    } else 
    if (time < 2 / 2.75)
    {
        time -= 1.5f / 2.75f;
        return 7.5625f * time * time + 0.75f;
    } else
    if(time < 2.5 / 2.75)
    {
        time -= 2.25f / 2.75f;
        return 7.5625f * time * time + 0.9375f;
    }

    time -= 2.625f / 2.75f;
    return 7.5625f * time * time + 0.984375f;
}

//
// EaseBounceIn
//

CCEaseBounceIn* CCEaseBounceIn::create(CCActionInterval* pAction)
{
    CCEaseBounceIn *pRet = new CCEaseBounceIn();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

CCEaseBounceIn* CCEaseBounceIn::clone() const
{
	auto a = new CCEaseBounceIn(*this);
	a->initWithAction((CCActionInterval *)m_pInner->clone());
	a->autorelease();
	return a;
}

CCObject* CCEaseBounceIn::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseBounceIn* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCEaseBounceIn*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseBounceIn();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCEaseBounceIn::update(float time)
{
    float newT = 1 - bounceTime(1 - time);
    m_pInner->update(newT);
}

CCEaseBounce* CCEaseBounceIn::reverse() const
{
    return CCEaseBounceOut::create(m_pInner->reverse());
}

//
// EaseBounceOut
//

CCEaseBounceOut* CCEaseBounceOut::create(CCActionInterval* pAction)
{
    CCEaseBounceOut *pRet = new CCEaseBounceOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

CCEaseBounceOut* CCEaseBounceOut::clone() const
{
	auto a = new CCEaseBounceOut(*this);
	a->initWithAction((CCActionInterval *)m_pInner->clone());
	a->autorelease();
	return a;
}

CCObject* CCEaseBounceOut::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseBounceOut* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCEaseBounceOut*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseBounceOut();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCEaseBounceOut::update(float time)
{
    float newT = bounceTime(time);
    m_pInner->update(newT);
}

CCEaseBounce* CCEaseBounceOut::reverse() const
{
    return CCEaseBounceIn::create(m_pInner->reverse());
}

//
// EaseBounceInOut
//

CCEaseBounceInOut* CCEaseBounceInOut::create(CCActionInterval* pAction)
{
    CCEaseBounceInOut *pRet = new CCEaseBounceInOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet; 
}

CCEaseBounceInOut* CCEaseBounceInOut::clone() const
{
	auto a = new CCEaseBounceInOut(*this);
	a->initWithAction((CCActionInterval *)m_pInner->clone());
	a->autorelease();
	return a;
}

CCObject* CCEaseBounceInOut::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseBounceInOut* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCEaseBounceInOut*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseBounceInOut();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCEaseBounceInOut::update(float time)
{
    float newT = 0;
    if (time < 0.5f)
    {
        time = time * 2;
        newT = (1 - bounceTime(1 - time)) * 0.5f;
    }
    else
    {
        newT = bounceTime(time * 2 - 1) * 0.5f + 0.5f;
    }

    m_pInner->update(newT);
}

CCEaseBounceInOut* CCEaseBounceInOut::reverse() const
{
    return CCEaseBounceInOut::create(m_pInner->reverse());
}

//
// EaseBackIn
//

CCEaseBackIn* CCEaseBackIn::create(CCActionInterval *pAction)
{
    CCEaseBackIn *pRet = new CCEaseBackIn();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet;
}

CCEaseBackIn* CCEaseBackIn::clone() const
{
	auto a = new CCEaseBackIn(*this);
	a->initWithAction((CCActionInterval *)m_pInner->clone());
	a->autorelease();
	return a;
}

CCObject* CCEaseBackIn::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseBackIn* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCEaseBackIn*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseBackIn();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCEaseBackIn::update(float time)
{
    float overshoot = 1.70158f;
    m_pInner->update(time * time * ((overshoot + 1) * time - overshoot));
}

CCActionEase* CCEaseBackIn::reverse() const
{
    return CCEaseBackOut::create(m_pInner->reverse());
}

//
// EaseBackOut
//

CCEaseBackOut* CCEaseBackOut::create(CCActionInterval* pAction)
{
    CCEaseBackOut *pRet = new CCEaseBackOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet;
}

CCEaseBackOut* CCEaseBackOut::clone() const
{
	auto a = new CCEaseBackOut(*this);
	a->initWithAction((CCActionInterval *)m_pInner->clone());
	a->autorelease();
	return a;
}

CCObject* CCEaseBackOut::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseBackOut* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCEaseBackOut*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseBackOut();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCEaseBackOut::update(float time)
{
    float overshoot = 1.70158f;

    time = time - 1;
    m_pInner->update(time * time * ((overshoot + 1) * time + overshoot) + 1);
}

CCActionEase* CCEaseBackOut::reverse() const
{
    return CCEaseBackIn::create(m_pInner->reverse());
}

//
// EaseBackInOut
//

CCEaseBackInOut* CCEaseBackInOut::create(CCActionInterval* pAction)
{
    CCEaseBackInOut *pRet = new CCEaseBackInOut();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }

    return pRet;
}

CCEaseBackInOut* CCEaseBackInOut::clone() const
{
	auto a = new CCEaseBackInOut(*this);
	a->initWithAction((CCActionInterval *)m_pInner->clone());
	a->autorelease();
	return a;
}

CCObject* CCEaseBackInOut::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseBackInOut* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCEaseBackInOut*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseBackInOut();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCEaseBackInOut::update(float time)
{
    float overshoot = 1.70158f * 1.525f;

    time = time * 2;
    if (time < 1)
    {
        m_pInner->update((time * time * ((overshoot + 1) * time - overshoot)) / 2);
    }
    else
    {
        time = time - 2;
        m_pInner->update((time * time * ((overshoot + 1) * time + overshoot)) / 2 + 1);
    }
}

CCEaseBackInOut* CCEaseBackInOut::reverse() const
{
    return CCEaseBackInOut::create(m_pInner->reverse());
}

NS_CC_END
