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
#include "cocoa/CCDictionary.h"
#include <string>

NS_CC_BEGIN

/**
 * @addtogroup global
 * @{
 */

class ProfilingTimer;

/** Profiler
 cocos2d builtin profiler.

 To use it, enable set the CC_ENABLE_PROFILERS=1 in the ccConfig.h file
 */

class CC_DLL Profiler : public Object
{
public:
    ~Profiler(void);
    /** display the timers */
    void displayTimers(void);
    bool init(void);

public:
    /** returns the singleton */
    static Profiler* getInstance(void);

    CC_DEPRECATED_ATTRIBUTE static Profiler* sharedProfiler(void);

    /** Creates and adds a new timer */
    ProfilingTimer* createAndAddTimerWithName(const char* timerName);
    /** releases a timer */
    void releaseTimer(const char* timerName);
    /** releases all timers */
    void releaseAllTimers();

    Dictionary* _activeTimers;
};

class ProfilingTimer : public Object
{
public:
    bool initWithName(const char* timerName);
    ~ProfilingTimer(void);
    const char* description(void) const;
    inline struct timeval * getStartTime(void) { return &_startTime; };
    inline void setAverageTime(double value) { _averageTime = value; }
    inline double getAverageTime(void) { return _averageTime; }
    /** resets the timer properties */
    void reset();

    std::string _nameStr;
    struct timeval _startTime;
    double _averageTime;
    double            minTime;
    double            maxTime;
    double            totalTime;
    unsigned int    numberOfCalls;
};

extern void ProfilingBeginTimingBlock(const char *timerName);
extern void ProfilingEndTimingBlock(const char *timerName);
extern void ProfilingResetTimingBlock(const char *timerName);

/*
 * cocos2d profiling categories
 * used to enable / disable profilers with granularity
 */

extern bool kProfilerCategorySprite;
extern bool kProfilerCategoryBatchSprite;
extern bool kProfilerCategoryParticles;

// end of global group
/// @}

NS_CC_END

#endif // __SUPPORT_CCPROFILING_H__
