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
#include "CCProfiling.h"

using namespace std;

NS_CC_BEGIN

//#pragma mark - Profiling Categories
/* set to NO the categories that you don't want to profile */
bool kCCProfilerCategorySprite = false;
bool kCCProfilerCategoryBatchSprite = false;
bool kCCProfilerCategoryParticles = false;


static CCProfiler* g_sSharedProfiler = NULL;

CCProfiler* CCProfiler::sharedProfiler(void)
{
    if (! g_sSharedProfiler)
    {
        g_sSharedProfiler = new CCProfiler();
        g_sSharedProfiler->init();
    }

    return g_sSharedProfiler;
}

CCProfilingTimer* CCProfiler::createAndAddTimerWithName(const char* timerName)
{
    CCProfilingTimer *t = new CCProfilingTimer();
    t->initWithName(timerName);
    m_pActiveTimers->setObject(t, timerName);
    t->release();

    return t;
}

void CCProfiler::releaseTimer(const char* timerName)
{
    m_pActiveTimers->removeObjectForKey(timerName);
}

void CCProfiler::releaseAllTimers()
{
    m_pActiveTimers->removeAllObjects();
}

bool CCProfiler::init()
{
    m_pActiveTimers = new CCDictionary();
    return true;
}

CCProfiler::~CCProfiler(void)
{
    CC_SAFE_RELEASE(m_pActiveTimers);
}

void CCProfiler::displayTimers()
{
    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(m_pActiveTimers, pElement)
    {
        CCProfilingTimer* timer = (CCProfilingTimer*)pElement->getObject();
        CCLog("%s", timer->description());
    }
}

// implementation of CCProfilingTimer

bool CCProfilingTimer::initWithName(const char* timerName)
{
    m_NameStr = timerName;
    numberOfCalls = 0;
    m_dAverageTime = 0.0;
    totalTime = 0.0;
    minTime = 10000.0;
    maxTime = 0.0;
    gettimeofday((struct timeval *)&m_sStartTime, NULL);

    return true;
}

CCProfilingTimer::~CCProfilingTimer(void)
{
    
}

const char* CCProfilingTimer::description()
{
    static char s_szDesciption[256] = {0};
    sprintf(s_szDesciption, "%s: avg time, %fms", m_NameStr.c_str(), m_dAverageTime);
    return s_szDesciption;
}

void CCProfilingTimer::reset()
{
    numberOfCalls = 0;
    m_dAverageTime = 0;
    totalTime = 0;
    minTime = 10000;
    maxTime = 0;
    gettimeofday((struct timeval *)&m_sStartTime, NULL);
}

void CCProfilingBeginTimingBlock(const char *timerName)
{
    CCProfiler* p = CCProfiler::sharedProfiler();
    CCProfilingTimer* timer = (CCProfilingTimer*)p->m_pActiveTimers->objectForKey(timerName);
    if( ! timer )
    {
        timer = p->createAndAddTimerWithName(timerName);
    }

    gettimeofday((struct timeval *)&timer->m_sStartTime, NULL);

    timer->numberOfCalls++;
}

void CCProfilingEndTimingBlock(const char *timerName)
{
    CCProfiler* p = CCProfiler::sharedProfiler();
    CCProfilingTimer* timer = (CCProfilingTimer*)p->m_pActiveTimers->objectForKey(timerName);

    CCAssert(timer, "CCProfilingTimer  not found");

    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);

    double duration = CCTime::timersubCocos2d((struct cc_timeval *)&timer->m_sStartTime, (struct cc_timeval *)&currentTime);

    // milliseconds
    timer->m_dAverageTime = (timer->m_dAverageTime + duration) / 2.0f;
    timer->totalTime += duration;
    timer->maxTime = MAX( timer->maxTime, duration);
    timer->minTime = MIN( timer->minTime, duration);

}

void CCProfilingResetTimingBlock(const char *timerName)
{
    CCProfiler* p = CCProfiler::sharedProfiler();
    CCProfilingTimer *timer = (CCProfilingTimer*)p->m_pActiveTimers->objectForKey(timerName);

    CCAssert(timer, "CCProfilingTimer not found");

    timer->reset();
}

NS_CC_END

