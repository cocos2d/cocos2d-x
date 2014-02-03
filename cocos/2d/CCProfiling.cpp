/****************************************************************************
Copyright (c) 2010      Stuart Carnie
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include <chrono>

using namespace std;

NS_CC_BEGIN

//#pragma mark - Profiling Categories
/* set to false the categories that you don't want to profile */
bool kProfilerCategorySprite = false;
bool kProfilerCategoryBatchSprite = false;
bool kProfilerCategoryParticles = false;


static Profiler* g_sSharedProfiler = nullptr;

Profiler* Profiler::getInstance()
{
    if (! g_sSharedProfiler)
    {
        g_sSharedProfiler = new Profiler();
        g_sSharedProfiler->init();
    }

    return g_sSharedProfiler;
}

// XXX: deprecated
Profiler* Profiler::sharedProfiler(void)
{
    return Profiler::getInstance();
}

ProfilingTimer* Profiler::createAndAddTimerWithName(const char* timerName)
{
    ProfilingTimer *t = new ProfilingTimer();
    t->initWithName(timerName);
    _activeTimers.insert(timerName, t);
    t->release();

    return t;
}

void Profiler::releaseTimer(const char* timerName)
{
    _activeTimers.erase(timerName);
}

void Profiler::releaseAllTimers()
{
    _activeTimers.clear();
}

bool Profiler::init()
{
    return true;
}

Profiler::~Profiler(void)
{
}

void Profiler::displayTimers()
{
    for (auto iter = _activeTimers.begin(); iter != _activeTimers.end(); ++iter)
    {
        ProfilingTimer* timer = iter->second;
        log("%s", timer->getDescription().c_str());
    }
}

// implementation of ProfilingTimer

ProfilingTimer::ProfilingTimer()
: _averageTime1(0)
, _averageTime2(0)
, minTime(100000000)
, maxTime(0)
, totalTime(0)
, numberOfCalls(0)
{
}

bool ProfilingTimer::initWithName(const char* timerName)
{
    _nameStr = timerName;
    return true;
}

ProfilingTimer::~ProfilingTimer(void)
{
    
}

std::string ProfilingTimer::getDescription() const
{
    static char s_desciption[512] = {0};

    sprintf(s_desciption, "%s ::\tavg1: %ldµ,\tavg2: %ldµ,\tmin: %ldµ,\tmax: %ldµ,\ttotal: %.2fs,\tnr calls: %ld", _nameStr.c_str(), _averageTime1, _averageTime2, minTime, maxTime, totalTime/1000000., numberOfCalls);
    return s_desciption;
}

void ProfilingTimer::reset()
{
    numberOfCalls = 0;
    _averageTime1 = 0;
    _averageTime2 = 0;
    totalTime = 0;
    minTime = 100000000;
    maxTime = 0;
    _startTime = chrono::high_resolution_clock::now();
}

void ProfilingBeginTimingBlock(const char *timerName)
{
    Profiler* p = Profiler::getInstance();
    ProfilingTimer* timer = p->_activeTimers.at(timerName);
    if( ! timer )
    {
        timer = p->createAndAddTimerWithName(timerName);
    }

    timer->numberOfCalls++;

    // should be the last instruction in order to be more reliable
    timer->_startTime = chrono::high_resolution_clock::now();
}

void ProfilingEndTimingBlock(const char *timerName)
{
    // should be the 1st instruction in order to be more reliable
    auto now = chrono::high_resolution_clock::now();

    Profiler* p = Profiler::getInstance();
    ProfilingTimer* timer = p->_activeTimers.at(timerName);

    CCASSERT(timer, "CCProfilingTimer  not found");


    long duration = static_cast<long>(chrono::duration_cast<chrono::microseconds>(now - timer->_startTime).count());

    timer->totalTime += duration;
    timer->_averageTime1 = (timer->_averageTime1 + duration) / 2.0f;
    timer->_averageTime2 = timer->totalTime / timer->numberOfCalls;
    timer->maxTime = MAX( timer->maxTime, duration);
    timer->minTime = MIN( timer->minTime, duration);
}

void ProfilingResetTimingBlock(const char *timerName)
{
    Profiler* p = Profiler::getInstance();
    ProfilingTimer *timer = p->_activeTimers.at(timerName);

    CCASSERT(timer, "CCProfilingTimer not found");

    timer->reset();
}

NS_CC_END

