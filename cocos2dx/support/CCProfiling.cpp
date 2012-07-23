/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2010      Stuart Carnie

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
#include "CCProfiling.h"

#if CC_ENABLE_PROFILERS

namespace cocos2d
{
	using namespace std;
	static CCProfiler *g_sSharedProfiler;

	CCProfiler* CCProfiler::sharedProfiler(void)
	{
        if (! g_sSharedProfiler)
		{
			g_sSharedProfiler = new CCProfiler();
			g_sSharedProfiler->init();
		}

		return g_sSharedProfiler;
	}

	CCProfilingTimer* CCProfiler::timerWithName(const char *pszTimerName, CCObject *pInstance)
	{
		CCProfiler *p = CCProfiler::sharedProfiler();
		CCProfilingTimer *t = new CCProfilingTimer();
		t->initWithName(pszTimerName, pInstance);
		p->m_pActiveTimers->addObject(t);
		t->release();

		return t;
	}

	void CCProfiler::releaseTimer(CCProfilingTimer *pTimer)
	{
		CCProfiler *p = CCProfiler::sharedProfiler();
		p->m_pActiveTimers->removeObject(pTimer);

        if (0 == (p->m_pActiveTimers->count()))
        {
            CC_SAFE_DELETE(g_sSharedProfiler);
        }
	}

	bool CCProfiler::init()
	{
        m_pActiveTimers = CCArray::array();
        m_pActiveTimers->retain();

		return true;
	}

	CCProfiler::~CCProfiler(void)
	{
		CC_SAFE_RELEASE(m_pActiveTimers);
	}

	void CCProfiler::displayTimers()
	{
        CCObject* pObject = NULL;
        CCProfilingTimer* pTimer = NULL;
        CCARRAY_FOREACH(m_pActiveTimers, pObject)
		{
            pTimer = (CCProfilingTimer*) pObject;
			char *pszDescription = pTimer->description();
			CCLog(pszDescription);
			delete pszDescription;
		}
	}

	// implementation of CCProfilingTimer

	bool CCProfilingTimer::initWithName(const char* pszTimerName, CCObject *pInstance)
	{
		char tmp[160];
		sprintf(tmp, "%s (0x%.8x)", pszTimerName, (unsigned int)pInstance);
		m_NameStr = string(tmp);
        m_dAverageTime = 0.0;

		return true;
	}

	CCProfilingTimer::~CCProfilingTimer(void)
	{
		
	}

	char* CCProfilingTimer::description()
	{
        char *pszDes = new char[m_NameStr.length() + sizeof(double) + 32];
		sprintf(pszDes, "%s: avg time, %fms", m_NameStr.c_str(), m_dAverageTime);
		return pszDes;
	}

	void CCProfilingBeginTimingBlock(CCProfilingTimer *pTimer)
	{
		CCTime::gettimeofdayCocos2d(pTimer->getStartTime(), NULL);
	}

	void CCProfilingEndTimingBlock(CCProfilingTimer *pTimer)
	{
        struct cc_timeval currentTime;
		CCTime::gettimeofdayCocos2d(&currentTime, NULL);
		CCTime::timersubCocos2d(&currentTime, pTimer->getStartTime(), &currentTime);
		double duration = currentTime.tv_sec * 1000.0 + currentTime.tv_usec / 1000.0;

		// return in milliseconds
		pTimer->setAverageTime((pTimer->getAverageTime() + duration) / 2.0f);
	}

} // end of namespace cocos2d

#endif // CC_ENABLE_PROFILERS
