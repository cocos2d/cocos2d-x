//
//  PerformanceCallbackTest.cpp
//

#include "PerformanceCallbackTest.h"

#include <algorithm>

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

static std::function<PerformanceCallbackScene*()> createFunctions[] =
{
    CL(SimulateNewSchedulerCallbackPerfTest),
    CL(InvokeMemberFunctionPerfTest),
    CL(InvokeStdFunctionPerfTest),
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))


static int g_curCase = 0;

////////////////////////////////////////////////////////
//
// CallbackBasicLayer
//
////////////////////////////////////////////////////////

CallbackBasicLayer::CallbackBasicLayer(bool bControlMenuVisible, int nMaxCases, int nCurCase)
: PerformBasicLayer(bControlMenuVisible, nMaxCases, nCurCase)
{
}

void CallbackBasicLayer::showCurrentTest()
{
    auto scene = createFunctions[_curCase]();
    
    g_curCase = _curCase;
    
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
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
    
    auto s = Director::getInstance()->getWinSize();
    
    auto menuLayer = new CallbackBasicLayer(true, MAX_LAYER, g_curCase);
    addChild(menuLayer);
    menuLayer->release();
    
    // Title
    auto label = Label::createWithTTF(title().c_str(), "fonts/arial.ttf", 32);
    addChild(label, 1);
    label->setPosition(Point(s.width/2, s.height-50));
    
    // Subtitle
    std::string strSubTitle = subtitle();
    if(strSubTitle.length())
    {
        auto l = Label::createWithTTF(strSubTitle.c_str(), "fonts/Thonburi.ttf", 16);
        addChild(l, 1);
        l->setPosition(Point(s.width/2, s.height-80));
    }
    
    getScheduler()->schedule(schedule_selector(PerformanceCallbackScene::onUpdate), this, 0.0f, false);
    getScheduler()->schedule(schedule_selector(PerformanceCallbackScene::dumpProfilerInfo), this, 2, false);
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
    _selector = schedule_selector(InvokeMemberFunctionPerfTest::update);
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

void runCallbackPerformanceTest()
{
    auto scene = createFunctions[g_curCase]();
    
    Director::getInstance()->replaceScene(scene);
}
