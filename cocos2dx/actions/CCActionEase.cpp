/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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
#include "CCObject.h"

namespace cocos2d {

#ifndef M_PI_X_2
#define M_PI_X_2 (float)M_PI * 2.0f
#endif

	//
	// EaseAction
	//
	CCActionEase* CCActionEase::actionWithAction(cocos2d::CCActionInterval *pAction)
	{
		CCActionEase *pRet = new CCActionEase();
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

	bool CCActionEase::initWithAction(cocos2d::CCActionInterval *pAction)
	{
		assert(pAction != NULL);

		if (CCActionInterval::initWithDuration(pAction->getDuration()))
		{
			m_pOther = pAction;
			pAction->retain();

			return true;
		}

		return false;
	}

	CCObject* CCActionEase::copyWithZone(cocos2d::CCZone *pZone)
	{
		CCZone* pNewZone = NULL;
		CCActionEase* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = (CCActionEase*)(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCActionEase();
			pZone = pNewZone = new CCZone(pCopy);
		}

		CCActionInterval::copyWithZone(pZone);

		pCopy->initWithAction((CCActionInterval *)(m_pOther->copy()->autorelease()));
		
		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	CCActionEase::~CCActionEase(void)
	{
		CC_SAFE_RELEASE(m_pOther);
	}

	void CCActionEase::startWithTarget(CCNode *pTarget)
	{
		CCActionInterval::startWithTarget(pTarget);
		m_pOther->startWithTarget(m_pTarget);
	}

	void CCActionEase::stop(void)
	{
		m_pOther->stop();
		CCActionInterval::stop();
	}

	void CCActionEase::update(cocos2d::ccTime time)
	{
		m_pOther->update(time);
	}

	CCActionInterval* CCActionEase::reverse(void)
	{
		return CCActionEase::actionWithAction(m_pOther->reverse());
	}

	//
	// EaseRateAction
	//
	CCEaseRateAction* CCEaseRateAction::actionWithAction(cocos2d::CCActionInterval *pAction, float fRate)
	{
		CCEaseRateAction *pRet = new CCEaseRateAction();
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

	bool CCEaseRateAction::initWithAction(cocos2d::CCActionInterval *pAction, float fRate)
	{
		if (CCActionEase::initWithAction(pAction))
		{
			m_fRate = fRate;
			return true;
		}

		return false;
	}

	CCObject* CCEaseRateAction::copyWithZone(cocos2d::CCZone *pZone)
	{
		CCZone* pNewZone = NULL;
		CCEaseRateAction* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = (CCEaseRateAction*)(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseRateAction();
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval*)(m_pOther->copy()->autorelease()), m_fRate);

		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	CCEaseRateAction::~CCEaseRateAction(void)
	{
	}

	CCActionInterval* CCEaseRateAction::reverse(void)
	{
		return CCEaseRateAction::actionWithAction(m_pOther->reverse(), 1 / m_fRate);
	}

	//
	// EeseIn
	//
	CCEaseIn* CCEaseIn::actionWithAction(cocos2d::CCActionInterval *pAction, float fRate)
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

	CCObject* CCEaseIn::copyWithZone(cocos2d::CCZone *pZone)
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
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval*)(m_pOther->copy()->autorelease()), m_fRate);

		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseIn::update(cocos2d::ccTime time)
	{
		m_pOther->update(powf(time, m_fRate));
	}

	//
	// EaseOut
	//
	CCEaseOut* CCEaseOut::actionWithAction(cocos2d::CCActionInterval *pAction, float fRate)
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

	CCObject* CCEaseOut::copyWithZone(cocos2d::CCZone *pZone)
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
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval*)(m_pOther->copy()->autorelease()), m_fRate);

		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseOut::update(cocos2d::ccTime time)
	{
		m_pOther->update(powf(time, 1 / m_fRate));
	}

	//
	// EaseInOut
	//
	CCEaseInOut* CCEaseInOut::actionWithAction(cocos2d::CCActionInterval *pAction, float fRate)
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

	CCObject* CCEaseInOut::copyWithZone(cocos2d::CCZone *pZone)
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
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval*)(m_pOther->copy()->autorelease()), m_fRate);

		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseInOut::update(cocos2d::ccTime time)
	{
		int sign = 1;
		int r = (int) m_fRate;

		if (r % 2 == 0)
		{
			sign = -1;
		}

		time *= 2;
        if (time < 1)
		{
			m_pOther->update(0.5f * powf(time, m_fRate));
		}
		else
		{
			m_pOther->update(sign * 0.5f * (powf(time - 2, m_fRate) + sign * 2));
		}
	}

	// InOut and OutIn are symmetrical
	CCActionInterval* CCEaseInOut::reverse(void)
	{
		return CCEaseInOut::actionWithAction(m_pOther->reverse(), m_fRate);
	}

	//
	// EaseExponentialIn
	//
	CCEaseExponentialIn* CCEaseExponentialIn::actionWithAction(CCActionInterval* pAction)
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

	CCObject* CCEaseExponentialIn::copyWithZone(cocos2d::CCZone *pZone)
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
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval *)(m_pOther->copy()->autorelease()));
		
		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseExponentialIn::update(cocos2d::ccTime time)
	{
		m_pOther->update(time == 0 ? 0 : powf(2, 10 * (time/1 - 1)) - 1 * 0.001f);
	}

	CCActionInterval* CCEaseExponentialIn::reverse(void)
	{
		return CCEaseExponentialOut::actionWithAction(m_pOther->reverse());
	}

	//
	// EaseExponentialOut
	//
	CCEaseExponentialOut* CCEaseExponentialOut::actionWithAction(CCActionInterval* pAction)
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

	CCObject* CCEaseExponentialOut::copyWithZone(cocos2d::CCZone *pZone)
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
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval *)(m_pOther->copy()->autorelease()));
		
		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseExponentialOut::update(cocos2d::ccTime time)
	{
		m_pOther->update(time == 1 ? 1 : (-powf(2, -10 * time / 1) + 1));
	}

	CCActionInterval* CCEaseExponentialOut::reverse(void)
	{
		return CCEaseExponentialIn::actionWithAction(m_pOther->reverse());
	}

	//
	// EaseExponentialInOut
	//
	CCEaseExponentialInOut* CCEaseExponentialInOut::actionWithAction(cocos2d::CCActionInterval *pAction)
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

	CCObject* CCEaseExponentialInOut::copyWithZone(cocos2d::CCZone *pZone)
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
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval *)(m_pOther->copy()->autorelease()));
		
		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseExponentialInOut::update(cocos2d::ccTime time)
	{
		time /= 0.5f;
		if (time < 1)
		{
			time = 0.5f * powf(2, 10 * (time - 1));
		}
		else
		{
			time = 0.5f * (-powf(2, 10 * (time - 1)) + 2);
		}

		m_pOther->update(time);
	}

	//
	// EaseSineIn
	//
	CCEaseSineIn* CCEaseSineIn::actionWithAction(CCActionInterval* pAction)
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

	CCObject* CCEaseSineIn::copyWithZone(cocos2d::CCZone *pZone)
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
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval *)(m_pOther->copy()->autorelease()));
		
		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseSineIn::update(cocos2d::ccTime time)
	{
		m_pOther->update(-1 * cosf(time * (float)M_PI_2) + 1);
	}

	CCActionInterval* CCEaseSineIn::reverse(void)
	{
		return CCEaseSineOut::actionWithAction(m_pOther->reverse());
	}

	//
	// EaseSineOut
	//
	CCEaseSineOut* CCEaseSineOut::actionWithAction(CCActionInterval* pAction)
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

	CCObject* CCEaseSineOut::copyWithZone(cocos2d::CCZone *pZone)
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
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval *)(m_pOther->copy()->autorelease()));
		
		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseSineOut::update(cocos2d::ccTime time)
	{
		m_pOther->update(sinf(time * (float)M_PI_2));
	}

	CCActionInterval* CCEaseSineOut::reverse(void)
	{
		return CCEaseSineIn::actionWithAction(m_pOther->reverse());
	}

	//
	// EaseSineInOut
	//
	CCEaseSineInOut* CCEaseSineInOut::actionWithAction(CCActionInterval* pAction)
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

	CCObject* CCEaseSineInOut::copyWithZone(cocos2d::CCZone *pZone)
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
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval *)(m_pOther->copy()->autorelease()));
		
		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseSineInOut::update(cocos2d::ccTime time)
	{
		m_pOther->update(-0.5f * (cosf((float)M_PI * time) - 1));
	}

	//
	// EaseElastic
	//
	CCEaseElastic* CCEaseElastic::actionWithAction(cocos2d::CCActionInterval *pAction)
	{
		CCEaseElastic *pRet = new CCEaseElastic();
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

	CCEaseElastic* CCEaseElastic::actionWithAction(cocos2d::CCActionInterval *pAction, float fPeriod)
	{
		CCEaseElastic *pRet = new CCEaseElastic();
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

	bool CCEaseElastic::initWithAction(cocos2d::CCActionInterval *pAction)
	{
		return initWithAction(pAction, 0.3f);
	}

	bool CCEaseElastic::initWithAction(cocos2d::CCActionInterval *pAction, float fPeriod)
	{
		if (CCActionEase::initWithAction(pAction))
		{
			m_fPeriod = fPeriod;
			return true;
		}

		return false;
	}

	CCObject* CCEaseElastic::copyWithZone(cocos2d::CCZone *pZone)
	{
		CCZone* pNewZone = NULL;
		CCEaseElastic* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = (CCEaseElastic*)(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseElastic();
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval *)(m_pOther->copy()->autorelease()), m_fPeriod);

		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	CCActionInterval* CCEaseElastic::reverse(void)
	{
		assert(0);

		return NULL;
	}

    //
	// EaseElasticIn
	//
	CCEaseElasticIn* CCEaseElasticIn::actionWithAction(CCActionInterval *pAction, float fPeriod)
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

	CCEaseElasticIn* CCEaseElasticIn::actionWithAction(CCActionInterval *pAction)
	{
		CCEaseElasticIn *pRet = new CCEaseElasticIn();
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

	CCObject* CCEaseElasticIn::copyWithZone(cocos2d::CCZone *pZone)
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
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval *)(m_pOther->copy()->autorelease()), m_fPeriod);

		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseElasticIn::update(cocos2d::ccTime time)
	{
		ccTime newT = 0;
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

		m_pOther->update(newT);
	}

	CCActionInterval* CCEaseElasticIn::reverse(void)
	{
		return CCEaseElasticOut::actionWithAction(m_pOther->reverse(), m_fPeriod);
	}

	//
	// EaseElasticOut
	//
	CCEaseElasticOut* CCEaseElasticOut::actionWithAction(CCActionInterval *pAction)
	{
		CCEaseElasticOut *pRet = new CCEaseElasticOut();
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

	CCEaseElasticOut* CCEaseElasticOut::actionWithAction(CCActionInterval *pAction, float fPeriod)
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

	CCObject *CCEaseElasticOut::copyWithZone(cocos2d::CCZone *pZone)
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
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval *)(m_pOther->copy()->autorelease()), m_fPeriod);

		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseElasticOut::update(cocos2d::ccTime time)
	{
		ccTime newT = 0;
		if (time == 0 || time == 1)
		{
			newT = time;
		}
		else
		{
			float s = m_fPeriod / 4;
			newT = powf(2, -10 * time) * sinf((time - s) * M_PI_X_2 / m_fPeriod) + 1;
		}

		m_pOther->update(newT);
	}

	CCActionInterval* CCEaseElasticOut::reverse(void)
	{
		return CCEaseElasticIn::actionWithAction(m_pOther->reverse(), m_fPeriod);
	}

	//
	// EaseElasticInOut
	//
	CCEaseElasticInOut* CCEaseElasticInOut::actionWithAction(CCActionInterval *pAction)
	{
		CCEaseElasticInOut *pRet = new CCEaseElasticInOut();
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

	CCEaseElasticInOut* CCEaseElasticInOut::actionWithAction(CCActionInterval *pAction, float fPeriod)
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

	CCObject* CCEaseElasticInOut::copyWithZone(cocos2d::CCZone *pZone)
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
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval *)(m_pOther->copy()->autorelease()), m_fPeriod);

		CC_SAFE_DELETE(pNewZone);
		return pCopy;

	}

	void CCEaseElasticInOut::update(cocos2d::ccTime time)
	{
		ccTime newT = 0;
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

			ccTime s = m_fPeriod / 4;

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

		m_pOther->update(newT);
	}

	CCActionInterval* CCEaseElasticInOut::reverse(void)
	{
		return CCEaseInOut::actionWithAction(m_pOther->reverse(), m_fPeriod);
	}

	//
	// EaseBounce
	//
	CCEaseBounce* CCEaseBounce::actionWithAction(CCActionInterval* pAction)
	{
		CCEaseBounce *pRet = new CCEaseBounce();
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

	CCObject* CCEaseBounce::copyWithZone(cocos2d::CCZone *pZone)
	{
		CCZone* pNewZone = NULL;
		CCEaseBounce* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = (CCEaseBounce*)(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseBounce();
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval *)(m_pOther->copy()->autorelease()));
		
		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	ccTime CCEaseBounce::bounceTime(cocos2d::ccTime time)
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
	CCEaseBounceIn* CCEaseBounceIn::actionWithAction(CCActionInterval* pAction)
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

	CCObject* CCEaseBounceIn::copyWithZone(cocos2d::CCZone *pZone)
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
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval *)(m_pOther->copy()->autorelease()));
		
		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseBounceIn::update(cocos2d::ccTime time)
	{
		ccTime newT = 1 - bounceTime(1 - time);
		m_pOther->update(newT);
	}

	CCActionInterval* CCEaseBounceIn::reverse(void)
	{
		return CCEaseBounceOut::actionWithAction(m_pOther->reverse());
	}

	//
	// EaseBounceOut
	//
	CCEaseBounceOut* CCEaseBounceOut::actionWithAction(CCActionInterval* pAction)
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

	CCObject* CCEaseBounceOut::copyWithZone(cocos2d::CCZone *pZone)
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
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval *)(m_pOther->copy()->autorelease()));
		
		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseBounceOut::update(cocos2d::ccTime time)
	{
		ccTime newT = bounceTime(time);
		m_pOther->update(newT);
	}

	CCActionInterval* CCEaseBounceOut::reverse(void)
	{
		return CCEaseBounceIn::actionWithAction(m_pOther->reverse());
	}

	//
	// EaseBounceInOut
	//
	CCEaseBounceInOut* CCEaseBounceInOut::actionWithAction(CCActionInterval* pAction)
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

	CCObject* CCEaseBounceInOut::copyWithZone(cocos2d::CCZone *pZone)
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
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval *)(m_pOther->copy()->autorelease()));
		
		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseBounceInOut::update(cocos2d::ccTime time)
	{
		ccTime newT = 0;
		if (time < 0.5f)
		{
			time = time * 2;
			newT = (1 - bounceTime(1 - time)) * 0.5f;
		}
		else
		{
			newT = bounceTime(time * 2 - 1) * 0.5f + 0.5f;
		}

		m_pOther->update(newT);
	}

	//
	// EaseBackIn
	//
	CCEaseBackIn* CCEaseBackIn::actionWithAction(cocos2d::CCActionInterval *pAction)
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

	CCObject* CCEaseBackIn::copyWithZone(cocos2d::CCZone *pZone)
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
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval *)(m_pOther->copy()->autorelease()));
		
		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseBackIn::update(cocos2d::ccTime time)
	{
		ccTime overshoot = 1.70158f;
		m_pOther->update(time * time * ((overshoot + 1) * time - overshoot));
	}

	CCActionInterval* CCEaseBackIn::reverse(void)
	{
		return CCEaseBackOut::actionWithAction(m_pOther->reverse());
	}

	//
	// EaseBackOut
	//
	CCEaseBackOut* CCEaseBackOut::actionWithAction(CCActionInterval* pAction)
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

	CCObject* CCEaseBackOut::copyWithZone(cocos2d::CCZone *pZone)
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
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval *)(m_pOther->copy()->autorelease()));
		
		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseBackOut::update(cocos2d::ccTime time)
	{
		ccTime overshoot = 1.70158f;

		time = time - 1;
		m_pOther->update(time * time * ((overshoot + 1) * time + overshoot) + 1);
	}

	CCActionInterval* CCEaseBackOut::reverse(void)
	{
		return CCEaseBackIn::actionWithAction(m_pOther->reverse());
	}

	//
	// EaseBackInOut
	//
	CCEaseBackInOut* CCEaseBackInOut::actionWithAction(CCActionInterval* pAction)
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

	CCObject* CCEaseBackInOut::copyWithZone(cocos2d::CCZone *pZone)
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
			pZone = pNewZone = new CCZone(pCopy);
		}

		pCopy->initWithAction((CCActionInterval *)(m_pOther->copy()->autorelease()));
		
		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseBackInOut::update(cocos2d::ccTime time)
	{
		ccTime overshoot = 1.70158f * 1.525f;

		time = time * 2;
		if (time < 1)
		{
			m_pOther->update((time * time * ((overshoot + 1) * time - overshoot)) / 2);
		}
		else
		{
			time = time - 2;
			m_pOther->update((time * time * ((overshoot + 1) + overshoot)) / 2 + 1);
		}
	}
}
