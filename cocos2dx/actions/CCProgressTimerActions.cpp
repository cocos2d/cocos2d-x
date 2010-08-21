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
#include "CCProgressTimerActions.h"
#include "CCProgressTimer.h"

namespace cocos2d
{
	#define kProgressTimerCast CCProgressTimer*

    // implementation of CCProgressTo

	CCProgressTo* CCProgressTo::actionWithDuration(cocos2d::ccTime duration, float fPercent)
	{
		CCProgressTo *pProgressTo = new CCProgressTo();
		pProgressTo->initWithDuration(duration, fPercent);
		pProgressTo->autorelease();

		return pProgressTo;
	}
 
	bool CCProgressTo::initWithDuration(cocos2d::ccTime duration, float fPercent)
	{
		if (__super::initWithDuration(duration))
		{
			m_fTo = fPercent;

			return true;
		}

		return false;
	}

	NSObject* CCProgressTo::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCProgressTo* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCProgressTo*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCProgressTo();
			pZone = pNewZone = new NSZone(pCopy);
		}

		__super::copyWithZone(pZone);

		pCopy->initWithDuration(m_fDuration, m_fTo);

		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCProgressTo::startWithTarget(cocos2d::NSObject *pTarget)
	{
		__super::startWithTarget(pTarget);
		m_fFrom = dynamic_cast<kProgressTimerCast>(pTarget)->getPercentage();

		// XXX: Is this correct ?
		// Adding it to support CCRepeat
		if (m_fFrom == 100)
		{
			m_fFrom = 0;
		}
	}

	void CCProgressTo::update(cocos2d::ccTime time)
	{
		dynamic_cast<kProgressTimerCast>(m_pTarget)->setPercentage(m_fFrom + (m_fTo - m_fFrom) * time);
	}

	// implementation of CCProgressFromTo
 
	CCProgressFromTo* CCProgressFromTo::actionWithDuration(cocos2d::ccTime duration, float fFromPercentage, float fToPercentage)
	{
		CCProgressFromTo *pProgressFromTo = new CCProgressFromTo();
		pProgressFromTo->initWithDuration(duration, fFromPercentage, fToPercentage);
		pProgressFromTo->autorelease();

		return pProgressFromTo;
	}

	bool CCProgressFromTo::initWithDuration(cocos2d::ccTime duration, float fFromPercentage, float fToPercentage)
	{
		if (__super::initWithDuration(duration))
		{
			m_fTo = fToPercentage;
			m_fFrom = fFromPercentage;

			return true;
		}

		return false;
	}

	NSObject* CCProgressFromTo::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCProgressFromTo* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCProgressFromTo*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCProgressFromTo();
			pZone = pNewZone = new NSZone(pCopy);
		}

		__super::copyWithZone(pZone);

		pCopy->initWithDuration(m_fDuration, m_fFrom, m_fTo);

		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	CCIntervalAction* CCProgressFromTo::reverse(void)
	{
		return CCProgressFromTo::actionWithDuration(m_fDuration, m_fTo, m_fFrom);
	}

	void CCProgressFromTo::startWithTarget(cocos2d::NSObject *pTarget)
	{
		__super::startWithTarget(pTarget);
	}

	void CCProgressFromTo::update(cocos2d::ccTime time)
	{
		dynamic_cast<kProgressTimerCast>(m_pTarget)->setPercentage(m_fFrom + (m_fTo - m_fFrom) * time);
	}

}// end of namespace cocos2d
