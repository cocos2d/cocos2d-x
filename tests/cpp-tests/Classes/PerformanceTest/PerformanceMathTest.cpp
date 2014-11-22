#include "PerformanceMathTest.h"

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

static const int TEST_COUNT = 2;
static int s_nTouchCurCase = 0;

static const int K_INFO_LOOP_TAG = 1581;

static PerformanceMathLayer* createLayer()
{
    s_nTouchCurCase = s_nTouchCurCase % TEST_COUNT;
    
    PerformanceMathLayer* result = nullptr;
    
    switch (s_nTouchCurCase) {
        case 0:
            result = new PerformanceMathLayer1(true, TEST_COUNT, s_nTouchCurCase);
            break;
        case 1:
            result = new PerformanceMathLayer2(true, TEST_COUNT, s_nTouchCurCase);
            break;
        default:
            result = new PerformanceMathLayer1(true, TEST_COUNT, s_nTouchCurCase);
            break;
    }
    
    if(result)
    {
        result->autorelease();
        return result;
    }
    else
    {
        return nullptr;
    }
}

void PerformanceMathLayer::onEnter()
{
    PerformBasicLayer::onEnter();
    
    CC_PROFILER_PURGE_ALL();
    
    auto s = Director::getInstance()->getWinSize();
    // Title
    auto label = Label::createWithTTF(title().c_str(), "fonts/arial.ttf", 32);
    addChild(label, 1);
    label->setPosition(Vec2(s.width/2, s.height-50));
    
    // Subtitle
    std::string strSubTitle = subtitle();
    if(strSubTitle.length())
    {
        auto l = Label::createWithTTF(strSubTitle.c_str(), "fonts/Thonburi.ttf", 16);
        addChild(l, 1);
        l->setPosition(Vec2(s.width/2, s.height-80));
    }
    
    MenuItemFont::setFontSize(65);
    auto decrease = MenuItemFont::create(" - ", CC_CALLBACK_1(PerformanceMathLayer::subLoopCount, this));
    decrease->setColor(Color3B(0,200,20));
    auto increase = MenuItemFont::create(" + ", CC_CALLBACK_1(PerformanceMathLayer::addLoopCount, this));
    increase->setColor(Color3B(0,200,20));
    
    auto menu = Menu::create(decrease, increase, nullptr);
    menu->alignItemsHorizontally();
    menu->setPosition(Vec2(s.width/2, s.height/2));
    addChild(menu, 1);
    
    auto infoLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 30);
    infoLabel->setColor(Color3B(0,200,20));
    infoLabel->setPosition(Vec2(s.width/2, s.height/2 + 40));
    addChild(infoLabel, 1, K_INFO_LOOP_TAG);
    updateLoopLabel();
    
    getScheduler()->schedule(schedule_selector(PerformanceMathLayer::doPerformanceTest), this, 0.0f, false);
    getScheduler()->schedule(schedule_selector(PerformanceMathLayer::dumpProfilerInfo), this, 2, false);
    
}

void PerformanceMathLayer::addLoopCount(Ref *sender)
{
    _loopCount += _stepCount;
    updateLoopLabel();
}

void PerformanceMathLayer::subLoopCount(Ref *sender)
{
    _loopCount -= _stepCount;
    _loopCount = std::max(_loopCount, 0);
    updateLoopLabel();
}

void PerformanceMathLayer::updateLoopLabel()
{
    auto infoLabel = (Label *) getChildByTag(K_INFO_LOOP_TAG);
    char str[16] = {0};
    sprintf(str, "%u", _loopCount);
    infoLabel->setString(str);
    
}

void PerformanceMathLayer::restartCallback(Ref* sender)
{
    s_nTouchCurCase = 0;
    runMathPerformanceTest();
}

void PerformanceMathLayer::nextCallback(Ref* sender)
{
    ++s_nTouchCurCase;
    s_nTouchCurCase = s_nTouchCurCase % TEST_COUNT;
    runMathPerformanceTest();
}

void PerformanceMathLayer::backCallback(Ref* sender)
{
    s_nTouchCurCase = s_nTouchCurCase + TEST_COUNT -1;
    s_nTouchCurCase = s_nTouchCurCase % TEST_COUNT;
    runMathPerformanceTest();
}

void PerformanceMathLayer::dumpProfilerInfo(float dt)
{
    CC_PROFILER_DISPLAY_TIMERS();
}

void PerformanceMathLayer1::doPerformanceTest(float dt)
{
    Mat4 dst = Mat4::IDENTITY;
    Mat4 src;
    Mat4::createRotation(Vec3(1,1,1), 10, &src);
    CC_PROFILER_START(_profileName.c_str());
    for (int i = 0; i < _loopCount; ++i)
    {
        dst = dst * src;
    }
    CC_PROFILER_STOP(_profileName.c_str());
    
}

void PerformanceMathLayer2::doPerformanceTest(float dt)
{
    Vec4 dst(1,3,4,1);
    Mat4 src;
    Mat4::createRotation(Vec3(1,1,1), 10, &src);
    CC_PROFILER_START(_profileName.c_str());
    for (int i = 0; i < _loopCount; ++i)
    {
        dst = src * dst;
    }
    CC_PROFILER_STOP(_profileName.c_str());
    
}

void runMathPerformanceTest()
{
    auto scene = Scene::create();
    auto layer = createLayer();
    
    scene->addChild(layer);
    
    Director::getInstance()->replaceScene(scene);
}
