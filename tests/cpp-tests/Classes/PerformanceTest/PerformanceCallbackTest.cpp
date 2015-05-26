//
//  PerformanceCallbackTest.cpp
//

#include "PerformanceCallbackTest.h"
#include <algorithm>

USING_NS_CC;

// Enable profiles for this file
#undef CC_PROFILER_DISPLAY_TIMERS
#define CC_PROFILER_DISPLAY_TIMERS() Profiler::getInstance()->displayTimers()
#undef CC_PROFILER_PURGE_ALL
#define CC_PROFILER_PURGE_ALL() Profiler::getInstance()->releaseAllTimers()

#undef CC_PROFILER_START
#define CC_PROFILER_START(__name__) ProfilingBeginTimingBlock(__name__)
#undef CC_PROFILER_STOP
#define CC_PROFILER_STOP(__name__) ProfilingEndTimingBlock(__name__)
#undef CC_PROFILER_RESET
#define CC_PROFILER_RESET(__name__) ProfilingResetTimingBlock(__name__)

#undef CC_PROFILER_START_CATEGORY
#define CC_PROFILER_START_CATEGORY(__cat__, __name__) do{ if(__cat__) ProfilingBeginTimingBlock(__name__); } while(0)
#undef CC_PROFILER_STOP_CATEGORY
#define CC_PROFILER_STOP_CATEGORY(__cat__, __name__) do{ if(__cat__) ProfilingEndTimingBlock(__name__); } while(0)
#undef CC_PROFILER_RESET_CATEGORY
#define CC_PROFILER_RESET_CATEGORY(__cat__, __name__) do{ if(__cat__) ProfilingResetTimingBlock(__name__); } while(0)

#undef CC_PROFILER_START_INSTANCE
#define CC_PROFILER_START_INSTANCE(__id__, __name__) do{ ProfilingBeginTimingBlock( String::createWithFormat("%08X - %s", __id__, __name__)->getCString() ); } while(0)
#undef CC_PROFILER_STOP_INSTANCE
#define CC_PROFILER_STOP_INSTANCE(__id__, __name__) do{ ProfilingEndTimingBlock(    String::createWithFormat("%08X - %s", __id__, __name__)->getCString() ); } while(0)
#undef CC_PROFILER_RESET_INSTANCE
#define CC_PROFILER_RESET_INSTANCE(__id__, __name__) do{ ProfilingResetTimingBlock( String::createWithFormat("%08X - %s", __id__, __name__)->getCString() ); } while(0)

PerformceCallbackTests::PerformceCallbackTests()
{
    ADD_TEST_CASE(SimulateNewSchedulerCallbackPerfTest);
    ADD_TEST_CASE(InvokeMemberFunctionPerfTest);
    ADD_TEST_CASE(InvokeStdFunctionPerfTest);
}

////////////////////////////////////////////////////////
//
// PerformanceCallbackScene
//
////////////////////////////////////////////////////////

void PerformanceCallbackScene::onEnter()
{
    Scene::onEnter();

    CC_PROFILER_PURGE_ALL();
    
    getScheduler()->schedule(CC_SCHEDULE_SELECTOR(PerformanceCallbackScene::onUpdate), this, 0.0f, false);
    getScheduler()->schedule(CC_SCHEDULE_SELECTOR(PerformanceCallbackScene::dumpProfilerInfo), this, 2, false);
}

std::string PerformanceCallbackScene::title() const
{
    return "No title";
}

std::string PerformanceCallbackScene::subtitle() const
{
    return "";
}

void PerformanceCallbackScene::dumpProfilerInfo(float dt)
{
	CC_PROFILER_DISPLAY_TIMERS();
}


////////////////////////////////////////////////////////
//
// SimulateNewSchedulerCallbackPerfTest
//
////////////////////////////////////////////////////////

void SimulateNewSchedulerCallbackPerfTest::onEnter()
{
    PerformanceCallbackScene::onEnter();
    _profileName = "SimulateNewScheduler";
    this->simulateScheduleUpdate(this);
}

void SimulateNewSchedulerCallbackPerfTest::onUpdate(float dt)
{
    CC_PROFILER_START(_profileName.c_str());
    for (int i = 0; i < LOOP_COUNT; ++i)
    {
        _callback(dt);
    }
    CC_PROFILER_STOP(_profileName.c_str());
}

std::string SimulateNewSchedulerCallbackPerfTest::title() const
{
    return "Simulate scheduler in 3.0 Perf test";
}

std::string SimulateNewSchedulerCallbackPerfTest::subtitle() const
{
    return "See console";
}

// InvokeMemberFunctionPerfTest

void InvokeMemberFunctionPerfTest::onEnter()
{
    PerformanceCallbackScene::onEnter();
    _profileName = "InvokeMemberFunction";
    _target = this;
    _selector = CC_SCHEDULE_SELECTOR(InvokeMemberFunctionPerfTest::update);
}

std::string InvokeMemberFunctionPerfTest::title() const
{
    return "Invoke Member function pert test";
}

std::string InvokeMemberFunctionPerfTest::subtitle() const
{
    return "See console";
}

void InvokeMemberFunctionPerfTest::onUpdate(float dt)
{
    CC_PROFILER_START(_profileName.c_str());
    for (int i = 0; i < LOOP_COUNT; ++i)
    {
        (_target->*_selector)(dt);
    }
    CC_PROFILER_STOP(_profileName.c_str());
}

void InvokeStdFunctionPerfTest::onEnter()
{
    PerformanceCallbackScene::onEnter();
    _profileName = "InvokeStdFunction";
    _callback = CC_CALLBACK_1(InvokeStdFunctionPerfTest::update, this);
}

std::string InvokeStdFunctionPerfTest::title() const
{
    return "Invoke std function pert test";
}

std::string InvokeStdFunctionPerfTest::subtitle() const
{
    return "See console";
}

void InvokeStdFunctionPerfTest::onUpdate(float dt)
{
    CC_PROFILER_START(_profileName.c_str());
    for (int i = 0; i < LOOP_COUNT; ++i)
    {
        _callback(dt);
    }
    CC_PROFILER_STOP(_profileName.c_str());
}
