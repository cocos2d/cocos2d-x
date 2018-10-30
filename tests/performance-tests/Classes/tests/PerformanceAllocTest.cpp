/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

/*
 *
 */
#include "PerformanceAllocTest.h"
#include "Profile.h"

#include <algorithm>

USING_NS_CC;
using namespace cocos2d::ui;

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

PerformceAllocTests::PerformceAllocTests()
{
    ADD_TEST_CASE(NodeCreateTest);
    ADD_TEST_CASE(NodeDeallocTest);
    ADD_TEST_CASE(SpriteCreateEmptyTest);
    ADD_TEST_CASE(SpriteCreateTest);
    ADD_TEST_CASE(SpriteDeallocTest);
}

enum {
    kTagInfoLayer = 1,
};

enum {
    kMaxNodes = 15000,
    kNodesIncrease = 500,
};

int PerformceAllocScene::quantityOfNodes = kNodesIncrease;

static int autoTestNodesNums[] = {
    1000, 2000, 3000
};

////////////////////////////////////////////////////////
//
// PerformceAllocScene
//
////////////////////////////////////////////////////////
PerformceAllocScene::PerformceAllocScene()
: autoTestIndex(0)
{
}

bool PerformceAllocScene::init()
{
    if (TestCase::init())
    {
        initWithQuantityOfNodes(quantityOfNodes);
        return true;
    }

    return false;
}

void PerformceAllocScene::initWithQuantityOfNodes(unsigned int nNodes)
{
    //std::srand(time());
    auto s = Director::getInstance()->getWinSize();

    lastRenderedCount = 0;
    currentQuantityOfNodes = 0;
    quantityOfNodes = nNodes;

    MenuItemFont::setFontSize(65);
    auto decrease = MenuItemFont::create(" - ", [&](Ref *sender) {
		quantityOfNodes -= kNodesIncrease;
		if( quantityOfNodes < 0 )
			quantityOfNodes = 0;

		updateQuantityLabel();
		updateQuantityOfNodes();
        updateProfilerName();
        CC_PROFILER_PURGE_ALL();
        std::srand(0);
	});
    decrease->setColor(Color3B(0,200,20));
    auto increase = MenuItemFont::create(" + ", [&](Ref *sender) {
		quantityOfNodes += kNodesIncrease;
		if( quantityOfNodes > kMaxNodes )
			quantityOfNodes = kMaxNodes;

		updateQuantityLabel();
		updateQuantityOfNodes();
        updateProfilerName();
        CC_PROFILER_PURGE_ALL();
        std::srand(0);
	});
    increase->setColor(Color3B(0,200,20));

    auto menu = Menu::create(decrease, increase, nullptr);
    menu->alignItemsHorizontally();
    menu->setPosition(Vec2(s.width/2, s.height/2+15));
    addChild(menu, 1);

    auto infoLabel = Label::createWithTTF("0 nodes", "fonts/Marker Felt.ttf", 30);
    infoLabel->setColor(Color3B(0,200,20));
    infoLabel->setPosition(Vec2(s.width/2, s.height/2-15));
    addChild(infoLabel, 1, kTagInfoLayer);

    updateQuantityLabel();
    updateQuantityOfNodes();
    updateProfilerName();
    std::srand(0);
}

std::string PerformceAllocScene::title() const
{
    return "No title";
}

std::string PerformceAllocScene::subtitle() const
{
    return "";
}

void PerformceAllocScene::updateQuantityLabel()
{
    if( quantityOfNodes != lastRenderedCount )
    {
        auto infoLabel = static_cast<Label*>( getChildByTag(kTagInfoLayer) );
        char str[20] = {0};
        sprintf(str, "%u nodes", quantityOfNodes);
        infoLabel->setString(str);

        lastRenderedCount = quantityOfNodes;
    }
}

const char * PerformceAllocScene::profilerName()
{
    return _profilerName;
}

void PerformceAllocScene::updateProfilerName()
{
    snprintf(_profilerName, sizeof(_profilerName)-1, "%s(%d)", testName(), quantityOfNodes);
}

void PerformceAllocScene::onExitTransitionDidStart()
{
    Scene::onExitTransitionDidStart();
    
    auto director = Director::getInstance();
    auto sched = director->getScheduler();

    sched->unschedule(CC_SCHEDULE_SELECTOR(PerformceAllocScene::dumpProfilerInfo), this);
}

void PerformceAllocScene::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();

    auto director = Director::getInstance();
    auto sched = director->getScheduler();

    if (this->isAutoTesting()) {
        // Update the quantity of nodes if is auto testing.
        quantityOfNodes = autoTestNodesNums[autoTestIndex];
        updateQuantityLabel();
        updateQuantityOfNodes();
        updateProfilerName();
        
        Profile::getInstance()->testCaseBegin("AllocTest",
                                              genStrVector("Type", "NodeCount", nullptr),
                                              genStrVector("Avg", "Min", "Max", nullptr));
    }
    
    CC_PROFILER_PURGE_ALL();
    sched->schedule(CC_SCHEDULE_SELECTOR(PerformceAllocScene::dumpProfilerInfo), this, 2, false);
}

void PerformceAllocScene::dumpProfilerInfo(float dt)
{
	CC_PROFILER_DISPLAY_TIMERS();

    if (this->isAutoTesting()) {
        // record the test result to class Profile
        auto timer = Profiler::getInstance()->_activeTimers.at(_profilerName);
        auto numStr = genStr("%d", quantityOfNodes);
        auto avgStr = genStr("%ldµ", timer->_averageTime2);
        auto minStr = genStr("%ldµ", timer->minTime);
        auto maxStr = genStr("%ldµ", timer->maxTime);
        Profile::getInstance()->addTestResult(genStrVector(getTestCaseName().c_str(), numStr.c_str(), nullptr),
                                              genStrVector(avgStr.c_str(), minStr.c_str(), maxStr.c_str(), nullptr));
        
        auto testsSize = sizeof(autoTestNodesNums)/sizeof(int);
        if (autoTestIndex >= (testsSize - 1)) {
            // if it's the last one of auto test. End the auto test.
            this->setAutoTesting(false);
            Profile::getInstance()->testCaseEnd();
        }
        else
        {
            // update the auto test index
            autoTestIndex++;
            quantityOfNodes = autoTestNodesNums[autoTestIndex];
            updateQuantityLabel();
            updateQuantityOfNodes();
            updateProfilerName();
            CC_PROFILER_PURGE_ALL();
        }
    }
}

////////////////////////////////////////////////////////
//
// NodeCreateTest
//
////////////////////////////////////////////////////////
void NodeCreateTest::updateQuantityOfNodes()
{
    currentQuantityOfNodes = quantityOfNodes;
}

void NodeCreateTest::initWithQuantityOfNodes(unsigned int nNodes)
{
    PerformceAllocScene::initWithQuantityOfNodes(nNodes);

    log("Size of Node: %lu\n", sizeof(Node));

    scheduleUpdate();
}

void NodeCreateTest::update(float dt)
{
    // iterate using fast enumeration protocol

    Node **nodes = new (std::nothrow) Node*[quantityOfNodes];

    CC_PROFILER_START(this->profilerName());
    for( int i=0; i<quantityOfNodes; ++i)
        nodes[i] = Node::create();
    CC_PROFILER_STOP(this->profilerName());

    delete [] nodes;
}

std::string NodeCreateTest::title() const
{
    return "Node Create Perf test.";
}

std::string NodeCreateTest::subtitle() const
{
    return "Node Create Perf test. See console";
}

const char*  NodeCreateTest::testName()
{
    return "Node::create()";
}

////////////////////////////////////////////////////////
//
// NodeDeallocTest
//
////////////////////////////////////////////////////////
void NodeDeallocTest::updateQuantityOfNodes()
{
    currentQuantityOfNodes = quantityOfNodes;
}

void NodeDeallocTest::initWithQuantityOfNodes(unsigned int nNodes)
{
    PerformceAllocScene::initWithQuantityOfNodes(nNodes);

    log("Size of Node: %lu\n", sizeof(Node));

    scheduleUpdate();
}

void NodeDeallocTest::update(float dt)
{
    // iterate using fast enumeration protocol

    Node **nodes = new (std::nothrow) Node*[quantityOfNodes];

    for( int i=0; i<quantityOfNodes; ++i) {
        nodes[i] = Node::create();
        nodes[i]->retain();
    }

    CC_PROFILER_START(this->profilerName());
    for( int i=0; i<quantityOfNodes; ++i)
        nodes[i]->release();
    CC_PROFILER_STOP(this->profilerName());

    delete [] nodes;
}

std::string NodeDeallocTest::title() const
{
    return "Node Dealloc Perf test.";
}

std::string NodeDeallocTest::subtitle() const
{
    return "Node Dealloc Perf test. See console";
}

const char*  NodeDeallocTest::testName()
{
    return "Node::~Node()";
}

////////////////////////////////////////////////////////
//
// SpriteCreateEmptyTest
//
////////////////////////////////////////////////////////
void SpriteCreateEmptyTest::updateQuantityOfNodes()
{
    currentQuantityOfNodes = quantityOfNodes;
}

void SpriteCreateEmptyTest::initWithQuantityOfNodes(unsigned int nNodes)
{
    PerformceAllocScene::initWithQuantityOfNodes(nNodes);

    log("Size of Sprite: %lu\n", sizeof(Sprite));

    scheduleUpdate();
}

void SpriteCreateEmptyTest::update(float dt)
{
    // iterate using fast enumeration protocol

    Sprite **sprites = new (std::nothrow) Sprite*[quantityOfNodes];

    Sprite::create("Images/grossini.png");

    CC_PROFILER_START(this->profilerName());
    for( int i=0; i<quantityOfNodes; ++i)
        sprites[i] = Sprite::create();
    CC_PROFILER_STOP(this->profilerName());

    delete [] sprites;
}

std::string SpriteCreateEmptyTest::title() const
{
    return "Create Empty Sprite";
}

std::string SpriteCreateEmptyTest::subtitle() const
{
    return "Create Empty Sprite Perf test. See console";
}

const char*  SpriteCreateEmptyTest::testName()
{
    return "Sprite::create(void)";
}

////////////////////////////////////////////////////////
//
// SpriteCreateTest
//
////////////////////////////////////////////////////////
void SpriteCreateTest::updateQuantityOfNodes()
{
    currentQuantityOfNodes = quantityOfNodes;
}

void SpriteCreateTest::initWithQuantityOfNodes(unsigned int nNodes)
{
    PerformceAllocScene::initWithQuantityOfNodes(nNodes);

    log("Size of Sprite: %lu\n", sizeof(Sprite));

    scheduleUpdate();
}

void SpriteCreateTest::update(float dt)
{
    // iterate using fast enumeration protocol

    Sprite **sprites = new (std::nothrow) Sprite*[quantityOfNodes];

    Sprite::create("Images/grossini.png");
    
    CC_PROFILER_START(this->profilerName());
    for( int i=0; i<quantityOfNodes; ++i)
        sprites[i] = Sprite::create("Images/grossini.png");
    CC_PROFILER_STOP(this->profilerName());

    delete [] sprites;
}

std::string SpriteCreateTest::title() const
{
    return "Create Sprite";
}

std::string SpriteCreateTest::subtitle() const
{
    return "Create Empty Sprite. See console";
}

const char*  SpriteCreateTest::testName()
{
    return "Sprite::create(\"image\")";
}

////////////////////////////////////////////////////////
//
// SpriteDeallocTest
//
////////////////////////////////////////////////////////
void SpriteDeallocTest::updateQuantityOfNodes()
{
    currentQuantityOfNodes = quantityOfNodes;
}

void SpriteDeallocTest::initWithQuantityOfNodes(unsigned int nNodes)
{
    PerformceAllocScene::initWithQuantityOfNodes(nNodes);

    log("Size of sprite: %lu\n", sizeof(Sprite));

    scheduleUpdate();
}

void SpriteDeallocTest::update(float dt)
{
    // iterate using fast enumeration protocol

    Sprite **sprites = new (std::nothrow) Sprite*[quantityOfNodes];

    for( int i=0; i<quantityOfNodes; ++i) {
        sprites[i] = Sprite::create();
        sprites[i]->retain();
    }

    CC_PROFILER_START(this->profilerName());
    for( int i=0; i<quantityOfNodes; ++i)
        sprites[i]->release();
    CC_PROFILER_STOP(this->profilerName());

    delete [] sprites;
}

std::string SpriteDeallocTest::title() const
{
    return "Sprite Dealloc Perf test.";
}

std::string SpriteDeallocTest::subtitle() const
{
    return "Sprite Dealloc Perf test. See console";
}

const char*  SpriteDeallocTest::testName()
{
    return "Sprite::~Sprite()";
}
