/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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
#include "cocoa/CCObject.h"
#include "platform/platform.h"
#include "cocoa/CCDictionary.h"
#include <string>

NS_CC_BEGIN

/**
 * @addtogroup global
 * @{
 */

class CCProfilingTimer;

/** CCProfiler
 cocos2d builtin profiler.

 To use it, enable set the CC_ENABLE_PROFILERS=1 in the ccConfig.h file
 */

class CC_DLL CCProfiler : public CCObject
{
public:
    ~CCProfiler(void);
    /** display the timers */
    void displayTimers(void);
    bool init(void);

public:
    static CCProfiler* sharedProfiler(void);
    /** Creates and adds a new timer */
    CCProfilingTimer* createAndAddTimerWithName(const char* timerName);
    /** releases a timer */
    void releaseTimer(const char* timerName);
    /** releases all timers */
    void releaseAllTimers();

    CCDictionary* m_pActiveTimers;
};

class CCProfilingTimer : public CCObject
{
public:
    bool initWithName(const char* timerName);
    ~CCProfilingTimer(void);
    const char* description(void);
    inline struct cc_timeval * getStartTime(void) { return &m_sStartTime; };
    inline void setAverageTime(double value) { m_dAverageTime = value; }
    inline double getAverageTime(void) { return m_dAverageTime; }
    /** resets the timer properties */
    void reset();

    std::string m_NameStr;
    struct cc_timeval m_sStartTime;
    double m_dAverageTime;
    double            minTime;
    double            maxTime;
    double            totalTime;
    unsigned int    numberOfCalls;
};

extern void CCProfilingBeginTimingBlock(const char *timerName);
extern void CCProfilingEndTimingBlock(const char *timerName);
extern void CCProfilingResetTimingBlock(const char *timerName);

/*
 * cocos2d profiling categories
 * used to enable / disable profilers with granularity
 */

extern bool kCCProfilerCategorySprite;
extern bool kCCProfilerCategoryBatchSprite;
extern bool kCCProfilerCategoryParticles;

// end of global group
/// @}

NS_CC_END

#endif // __SUPPORT_CCPROFILING_H__
