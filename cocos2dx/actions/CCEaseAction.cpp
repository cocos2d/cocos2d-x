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

#include "CCEaseAction.h"
#include "NSObject.h"

/*
 * Elastic, Back and Bounce actions based on code from:
 * http://github.com/NikhilK/silverlightfx/
 *
 * by http://github.com/NikhilK
 */
namespace cocos2d {

#ifndef M_PI_X_2
#define M_PI_X_2 (float)M_PI * 2.0f
#endif

	//
	// EaseAction
	//
	CCEaseAction* CCEaseAction::actionWithAction(cocos2d::CCIntervalAction *pAction)
	{
		CCEaseAction *pEaseAction = new CCEaseAction();
		pEaseAction->initWithAction(pAction);
		pEaseAction->autorelease();

		return pEaseAction;
	}

	CCEaseAction* CCEaseAction::initWithAction(cocos2d::CCIntervalAction *pAction)
	{
		assert(pAction != NULL);

		if (__super::initWithDuration(pAction->getDuration()))
		{
			m_pOther = pAction;
			pAction->retain();

			return this;
		}

		return NULL;
	}

	NSObject* CCEaseAction::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseAction* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseAction*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseAction();
			pZone = pNewZone = new NSZone(pCopy);
		}

		__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction *>(m_pOther->copy()->autorelease()));
		
		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	CCEaseAction::~CCEaseAction(void)
	{
		m_pOther->release();
	}

	void CCEaseAction::startWithTarget(cocos2d::NSObject *pTarget)
	{
		__super::startWithTarget(pTarget);
		m_pOther->startWithTarget(pTarget);
	}

	void CCEaseAction::stop(void)
	{
		m_pOther->stop();
		__super::stop();
	}

	void CCEaseAction::update(cocos2d::ccTime time)
	{
		m_pOther->update(time);
	}

	CCIntervalAction* CCEaseAction::reverse(void)
	{
		return CCEaseAction::actionWithAction(m_pOther->reverse());
	}

	//
	// EaseRateAction
	//
	CCEaseRateAction* CCEaseRateAction::actionWithAction(cocos2d::CCIntervalAction *pAction, float fRate)
	{
		CCEaseRateAction *pEaseRateAction = new CCEaseRateAction();
		pEaseRateAction->initWithAction(pAction, fRate);
		pEaseRateAction->autorelease();

		return pEaseRateAction;
	}

	CCEaseRateAction* CCEaseRateAction::initWithAction(cocos2d::CCIntervalAction *pAction, float fRate)
	{
		if (__super::initWithAction(pAction))
		{
			m_fRate = fRate;
			return this;
		}

		return NULL;
	}

	NSObject* CCEaseRateAction::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseRateAction* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseRateAction*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseRateAction();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);


		pCopy->initWithAction(dynamic_cast<CCIntervalAction*>(m_pOther->copy()->autorelease()), m_fRate);

		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	CCEaseRateAction::~CCEaseRateAction(void)
	{
	}

	CCIntervalAction* CCEaseRateAction::reverse(void)
	{
		return CCEaseRateAction::actionWithAction(m_pOther->reverse(), 1 / m_fRate);
	}

	//
	// EeseIn
	//
	NSObject* CCEaseIn::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseIn* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseIn*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseIn();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);


		pCopy->initWithAction(dynamic_cast<CCIntervalAction*>(m_pOther->copy()->autorelease()), m_fRate);

		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseIn::update(cocos2d::ccTime time)
	{
		m_pOther->update(powf(time, m_fRate));
	}

	//
	// EaseOut
	//
	NSObject* CCEaseOut::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseOut* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseOut*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseOut();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);


		pCopy->initWithAction(dynamic_cast<CCIntervalAction*>(m_pOther->copy()->autorelease()), m_fRate);

		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseOut::update(cocos2d::ccTime time)
	{
		m_pOther->update(powf(time, 1 / m_fRate));
	}

	//
	// EaseInOut
	//
	NSObject* CCEaseInOut::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseInOut* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseInOut*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseInOut();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction*>(m_pOther->copy()->autorelease()), m_fRate);

		CCX_SAFE_DELETE(pNewZone);
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
	CCIntervalAction* CCEaseInOut::reverse(void)
	{
		return CCEaseInOut::actionWithAction(m_pOther->reverse(), m_fRate);
	}

	//
	// EaseExponentialIn
	//
	NSObject* CCEaseExponentialIn::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseExponentialIn* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseExponentialIn*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseExponentialIn();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction *>(m_pOther->copy()->autorelease()));
		
		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseExponentialIn::update(cocos2d::ccTime time)
	{
		m_pOther->update(time == 0 ? 0 : powf(2, 10 * (time/1 - 1)) - 1 * 0.001f);
	}

	CCIntervalAction* CCEaseExponentialIn::reverse(void)
	{
		return CCEaseExponentialOut::actionWithAction(m_pOther->reverse());
	}

	//
	// EaseExponentialOut
	//
	NSObject* CCEaseExponentialOut::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseExponentialOut* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseExponentialOut*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseExponentialOut();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction *>(m_pOther->copy()->autorelease()));
		
		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseExponentialOut::update(cocos2d::ccTime time)
	{
		m_pOther->update(time == 1 ? 1 : (-powf(2, -10 * time / 1) + 1));
	}

	CCIntervalAction* CCEaseExponentialOut::reverse(void)
	{
		return CCEaseExponentialIn::actionWithAction(m_pOther->reverse());
	}

	//
	// EaseExponentialInOut
	//
	NSObject* CCEaseExponentialInOut::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseExponentialInOut* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseExponentialInOut*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseExponentialInOut();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction *>(m_pOther->copy()->autorelease()));
		
		CCX_SAFE_DELETE(pNewZone);
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
	NSObject* CCEaseSineIn::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseSineIn* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject)
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseSineIn*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseSineIn();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction *>(m_pOther->copy()->autorelease()));
		
		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseSineIn::update(cocos2d::ccTime time)
	{
		m_pOther->update(-1 * cosf(time * (float)M_PI_2) + 1);
	}

	CCIntervalAction* CCEaseSineIn::reverse(void)
	{
		return CCEaseSineOut::actionWithAction(m_pOther->reverse());
	}

	//
	// EaseSineOut
	//
	NSObject* CCEaseSineOut::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseSineOut* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseSineOut*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseSineOut();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction *>(m_pOther->copy()->autorelease()));
		
		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseSineOut::update(cocos2d::ccTime time)
	{
		m_pOther->update(sinf(time * (float)M_PI_2));
	}

	CCIntervalAction* CCEaseSineOut::reverse(void)
	{
		return CCEaseSineIn::actionWithAction(m_pOther->reverse());
	}

	//
	// EaseSineInOut
	//
	NSObject* CCEaseSineInOut::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseSineInOut* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseSineInOut*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseSineInOut();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction *>(m_pOther->copy()->autorelease()));
		
		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseSineInOut::update(cocos2d::ccTime time)
	{
		m_pOther->update(-0.5f * (cosf((float)M_PI * time) - 1));
	}

	//
	// EaseElastic
	//
	CCEaseElastic* CCEaseElastic::actionWithAction(cocos2d::CCIntervalAction *pAction)
	{
		CCEaseElastic *pEaseElastic = new CCEaseElastic();
		pEaseElastic->initWithAction(pAction, 0.3f);
		pEaseElastic->autorelease();

		return pEaseElastic;
	}

	CCEaseElastic* CCEaseElastic::actionWithAction(cocos2d::CCIntervalAction *pAction, float fPeriod)
	{
		CCEaseElastic *pEaseElastic = new CCEaseElastic();
		pEaseElastic->initWithAction(pAction, fPeriod);
		pEaseElastic->autorelease();

		return pEaseElastic;
	}

	CCEaseElastic* CCEaseElastic::initWithAction(cocos2d::CCIntervalAction *pAction)
	{
		return initWithAction(pAction, 0.3f);
	}

	CCEaseElastic* CCEaseElastic::initWithAction(cocos2d::CCIntervalAction *pAction, float fPeriod)
	{
		if (__super::initWithAction(pAction))
		{
			m_fPeriod = fPeriod;
			return this;
		}

		return NULL;
	}

	NSObject* CCEaseElastic::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseElastic* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseElastic*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseElastic();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction *>(m_pOther->copy()->autorelease()), m_fPeriod);

		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	CCIntervalAction* CCEaseElastic::reverse(void)
	{
		assert(0);

		return NULL;
	}

    //
	// EaseElasticIn
	//
	NSObject* CCEaseElasticIn::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseElasticIn* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseElasticIn*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseElasticIn();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction *>(m_pOther->copy()->autorelease()), m_fPeriod);

		CCX_SAFE_DELETE(pNewZone);
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

	CCIntervalAction* CCEaseElasticIn::reverse(void)
	{
		return CCEaseElasticOut::actionWithAction(m_pOther->reverse(), m_fPeriod);
	}

	//
	// EaseElasticOut
	//
	NSObject *CCEaseElasticOut::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseElasticOut* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseElasticOut*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseElasticOut();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction *>(m_pOther->copy()->autorelease()), m_fPeriod);

		CCX_SAFE_DELETE(pNewZone);
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

	CCIntervalAction* CCEaseElasticOut::reverse(void)
	{
		return CCEaseElasticIn::actionWithAction(m_pOther->reverse(), m_fPeriod);
	}

	//
	// EaseElasticInOut
	//
	NSObject* CCEaseElasticInOut::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseElasticInOut* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseElasticInOut*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseElasticInOut();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction *>(m_pOther->copy()->autorelease()), m_fPeriod);

		CCX_SAFE_DELETE(pNewZone);
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

	CCIntervalAction* CCEaseElasticInOut::reverse(void)
	{
		return CCEaseInOut::actionWithAction(m_pOther->reverse(), m_fPeriod);
	}

	//
	// EaseBounce
	//
	NSObject* CCEaseBounce::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseBounce* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseBounce*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseBounce();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction *>(m_pOther->copy()->autorelease()));
		
		CCX_SAFE_DELETE(pNewZone);
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
	NSObject* CCEaseBounceIn::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseBounceIn* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseBounceIn*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseBounceIn();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction *>(m_pOther->copy()->autorelease()));
		
		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseBounceIn::update(cocos2d::ccTime time)
	{
		ccTime newT = 1 - bounceTime(1 - time);
		m_pOther->update(newT);
	}

	CCIntervalAction* CCEaseBounceIn::reverse(void)
	{
		return CCEaseBounceOut::actionWithAction(m_pOther->reverse());
	}

	//
	// EaseBounceOut
	//
	NSObject* CCEaseBounceOut::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseBounceOut* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject)
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseBounceOut*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseBounceOut();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction *>(m_pOther->copy()->autorelease()));
		
		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseBounceOut::update(cocos2d::ccTime time)
	{
		ccTime newT = bounceTime(time);
		m_pOther->update(newT);
	}

	CCIntervalAction* CCEaseBounceOut::reverse(void)
	{
		return CCEaseBounceIn::actionWithAction(m_pOther->reverse());
	}

	//
	// EaseBounceInOut
	//
	NSObject* CCEaseBounceInOut::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseBounceInOut* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseBounceInOut*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseBounceInOut();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction *>(m_pOther->copy()->autorelease()));
		
		CCX_SAFE_DELETE(pNewZone);
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
	NSObject* CCEaseBackIn::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseBackIn* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseBackIn*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseBackIn();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction *>(m_pOther->copy()->autorelease()));
		
		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseBackIn::update(cocos2d::ccTime time)
	{
		ccTime overshoot = 1.70158f;
		m_pOther->update(time * time * ((overshoot + 1) * time - overshoot));
	}

	CCIntervalAction* CCEaseBackIn::reverse(void)
	{
		return CCEaseBackOut::actionWithAction(m_pOther->reverse());
	}

	//
	// EaseBackOut
	//
	NSObject* CCEaseBackOut::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseBackOut* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseBackOut*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseBackOut();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction *>(m_pOther->copy()->autorelease()));
		
		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCEaseBackOut::update(cocos2d::ccTime time)
	{
		ccTime overshoot = 1.70158f;

		time = time - 1;
		m_pOther->update(time * time * ((overshoot + 1) * time + overshoot) + 1);
	}

	CCIntervalAction* CCEaseBackOut::reverse(void)
	{
		return CCEaseBackIn::actionWithAction(m_pOther->reverse());
	}

	//
	// EaseBackInOut
	//
	NSObject* CCEaseBackInOut::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCEaseBackInOut* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCEaseBackInOut*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCEaseBackInOut();
			pZone = pNewZone = new NSZone(pCopy);
		}

		
		//__super::copyWithZone(pZone);

		pCopy->initWithAction(dynamic_cast<CCIntervalAction *>(m_pOther->copy()->autorelease()));
		
		CCX_SAFE_DELETE(pNewZone);
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
