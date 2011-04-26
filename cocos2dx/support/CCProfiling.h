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
#ifndef __SUPPORT_CCPROFILING_H__
#define __SUPPORT_CCPROFILING_H__

#include "ccConfig.h"

#if CC_ENABLE_PROFILERS

#include <string>

#include "CCObject.h"
#include "platform/platform.h"
#include "CCArray.h"

namespace cocos2d
{
	class CCProfilingTimer;

	class CC_DLL CCProfiler : public CCObject
	{
	public:
		~CCProfiler(void);
		void displayTimers(void);
		bool init(void);

	public:
		static CCProfiler* sharedProfiler(void);
		static CCProfilingTimer* timerWithName(const char *pszTimerName, CCObject *pInstance);
		static void releaseTimer(CCProfilingTimer *pTimer);

	protected:
		CCArray *m_pActiveTimers;
	};

	class CCProfilingTimer : public CCObject
	{
	public:
		bool initWithName(const char* pszTimerName, CCObject *pInstance);
		~CCProfilingTimer(void);
		char* description(void);
		inline struct cc_timeval * getStartTime(void) { return &m_sStartTime; };
		inline void setAverageTime(double value) { m_dAverageTime = value; }
		inline double getAverageTime(void) { return m_dAverageTime; }

	protected:
		std::string m_NameStr;
        struct cc_timeval m_sStartTime;
		double m_dAverageTime;
	};

	void CC_DLL CCProfilingBeginTimingBlock(CCProfilingTimer *pTimer);
	void CC_DLL CCProfilingEndTimingBlock(CCProfilingTimer *pTimer);

} // end of namespace cocos2d

#endif // CC_ENABLE_PROFILERS
#endif // __SUPPORT_CCPROFILING_H__
