//
//  PerformanceEventDispatcherTest.cpp
//

#include "PerformanceEventDispatcherTest.h"
#include <algorithm>
#include "Profile.h"

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

PerformceEventDispatcherTests::PerformceEventDispatcherTests()
{
    ADD_TEST_CASE(TouchEventDispatchingPerfTest);
    ADD_TEST_CASE(KeyboardEventDispatchingPerfTest);
    ADD_TEST_CASE(CustomEventDispatchingPerfTest);
}

enum {
    kTagInfoLayer = 1,
    
    kTagBase = 20000,
};

enum {
    kMaxNodes = 15000,
    kNodesIncrease = 500,
};

static int autoTestNodesNums[] = {
    1000, 2000, 3000
};

int PerformanceEventDispatcherScene::quantityOfNodes = kNodesIncrease;

////////////////////////////////////////////////////////
//
// PerformanceEventDispatcherScene
//
////////////////////////////////////////////////////////
bool PerformanceEventDispatcherScene::init()
{
    if (TestCase::init())
    {
        initWithQuantityOfNodes(quantityOfNodes);
        return true;
    }

    return false;
}

void PerformanceEventDispatcherScene::initWithQuantityOfNodes(unsigned int nNodes)
{
    _type = 0;
    std::srand((unsigned)time(nullptr));
    auto s = Director::getInstance()->getWinSize();
    
    _lastRenderedCount = 0;
    _currentQuantityOfNodes = 0;
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
    _decrease = decrease;
    
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
    _increase = increase;
    
    auto menu = Menu::create(decrease, increase, nullptr);
    menu->alignItemsHorizontally();
    menu->setPosition(Vec2(s.width/2, s.height/2+15));
    addChild(menu, 1);
    
    auto infoLabel = Label::createWithTTF("0 listeners", "fonts/Marker Felt.ttf", 30);
    infoLabel->setColor(Color3B(0,200,20));
    infoLabel->setPosition(Vec2(s.width/2, s.height/2-15));
    addChild(infoLabel, 1, kTagInfoLayer);
    
    int oldFontSize = MenuItemFont::getFontSize();
    MenuItemFont::setFontSize(24);
    
    Vector<cocos2d::MenuItem *> toggleItems;
    
    generateTestFunctions();
    
    CCASSERT(!_testFunctions.empty(), "Should not be empty after generate test functions");
    
    
    for (const auto& f : _testFunctions)
    {
        toggleItems.pushBack(MenuItemFont::create(f.name));
    }

    auto toggle = MenuItemToggle::createWithCallback([=](Ref* sender){
        auto toggle = static_cast<MenuItemToggle*>(sender);
        switchTestType(toggle->getSelectedIndex());
    }, toggleItems);
    
    toggle->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    toggle->setPosition(VisibleRect::left());
    _toggle = toggle;
    
    auto start = MenuItemFont::create("start", [this](Ref* sender){
        auto director = Director::getInstance();
        auto sched = director->getScheduler();
        
        CC_PROFILER_PURGE_ALL();
        sched->schedule(CC_SCHEDULE_SELECTOR(PerformanceEventDispatcherScene::dumpProfilerInfo), this, 2, false);
        
        this->unscheduleUpdate();
        this->scheduleUpdate();
        this->_startItem->setEnabled(false);
        this->_stopItem->setEnabled(true);
        this->_toggle->setEnabled(false);
        this->_increase->setEnabled(false);
        this->_decrease->setEnabled(false);
    });
    start->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    start->setPosition(VisibleRect::right() + Vec2(0, 40));
    _startItem = start;
    
    auto stop = MenuItemFont::create("stop", [=](Ref* sender){
        auto director = Director::getInstance();
        auto sched = director->getScheduler();
        
        sched->unschedule(CC_SCHEDULE_SELECTOR(PerformanceEventDispatcherScene::dumpProfilerInfo), this);
        
        this->unscheduleUpdate();
        this->_startItem->setEnabled(true);
        this->_stopItem->setEnabled(false);
        this->_toggle->setEnabled(true);
        this->_increase->setEnabled(true);
        this->_decrease->setEnabled(true);
        
        reset();
    });
    
    stop->setEnabled(false);
    stop->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    stop->setPosition(VisibleRect::right() + Vec2(0, -40));
    _stopItem = stop;
    
    auto menu2 = Menu::create(toggle, start, stop, nullptr);
    menu2->setPosition(Vec2::ZERO);
    addChild(menu2);
    
    MenuItemFont::setFontSize(oldFontSize);
    
    updateQuantityLabel();
    updateQuantityOfNodes();
    updateProfilerName();
}

void PerformanceEventDispatcherScene::onEnter()
{
    TestCase::onEnter();
    if (isAutoTesting()) {
        this->_startItem->setEnabled(false);
        this->_stopItem->setEnabled(false);
        this->_toggle->setEnabled(false);
        this->_increase->setEnabled(false);
        this->_decrease->setEnabled(false);

        autoTestCountIndex = 0;
        _type = 0;
        updateStatus();

        Profile::getInstance()->testCaseBegin("EventDispatcherTest",
                                              genStrVector("Type", "ListenerCount", nullptr),
                                              genStrVector("Avg", "Min", "Max", nullptr));

        auto director = Director::getInstance();
        auto sched = director->getScheduler();
        sched->schedule(CC_SCHEDULE_SELECTOR(PerformanceEventDispatcherScene::dumpProfilerInfo), this, 2, false);
        this->unscheduleUpdate();
        this->scheduleUpdate();
    }
}

void PerformanceEventDispatcherScene::onExit()
{
    TestCase::onExit();
    auto director = Director::getInstance();
    auto sched = director->getScheduler();
    sched->unscheduleAllForTarget(this);
}

void PerformanceEventDispatcherScene::updateStatus()
{
    quantityOfNodes = autoTestNodesNums[autoTestCountIndex];
    _toggle->setSelectedIndex(_type);
    switchTestType(_type);

    updateQuantityLabel();
    updateQuantityOfNodes();
    CC_PROFILER_PURGE_ALL();
}

void PerformanceEventDispatcherScene::reset()
{
    // Removes all nodes
    for (auto& node : _nodes)
    {
        node->removeFromParent();
    }
    
    _nodes.clear();
    
    // Removes all fixed listeners
    for (auto& listener : _fixedPriorityListeners)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
    }
    
    this->_lastRenderedCount = 0;
}

void PerformanceEventDispatcherScene::switchTestType(unsigned int index)
{
    this->_type = index;
    _subtitleLabel->setString(StringUtils::format("Test '%s', See console", this->_testFunctions[this->_type].name));
    this->updateProfilerName();
    reset();
}

std::string PerformanceEventDispatcherScene::title() const
{
    return "No title";
}

std::string PerformanceEventDispatcherScene::subtitle() const
{
    return "";
}

void PerformanceEventDispatcherScene::updateQuantityLabel()
{
    if( quantityOfNodes != _lastRenderedCount )
    {
        auto infoLabel = static_cast<Label*>( getChildByTag(kTagInfoLayer) );
        char str[20] = {0};
        sprintf(str, "%u listeners", quantityOfNodes);
        infoLabel->setString(str);
    }
}

const char * PerformanceEventDispatcherScene::profilerName()
{
    return _profilerName;
}

void PerformanceEventDispatcherScene::updateProfilerName()
{
    snprintf(_profilerName, sizeof(_profilerName)-1, "%s(%d)", testName(), quantityOfNodes);
}

void PerformanceEventDispatcherScene::dumpProfilerInfo(float dt)
{
	CC_PROFILER_DISPLAY_TIMERS();
    
    if (this->isAutoTesting()) {
        // record the test result to class Profile
        auto timer = Profiler::getInstance()->_activeTimers.at(_profilerName);
        auto numStr = genStr("%d", quantityOfNodes);
        auto avgStr = genStr("%ldµ", timer->_averageTime2);
        auto minStr = genStr("%ldµ", timer->minTime);
        auto maxStr = genStr("%ldµ", timer->maxTime);
        Profile::getInstance()->addTestResult(genStrVector(_testFunctions[_type].name, numStr.c_str(), nullptr),
                                              genStrVector(avgStr.c_str(), minStr.c_str(), maxStr.c_str(), nullptr));

        auto testsSize = sizeof(autoTestNodesNums)/sizeof(int);
        auto typeSize = _testFunctions.size();
        if (autoTestCountIndex >= (testsSize - 1) &&
            _type >= (typeSize - 1)) {
            // if it's the last one of auto test. End the auto test.
            this->setAutoTesting(false);
            Profile::getInstance()->testCaseEnd();
            return;
        }

        if (autoTestCountIndex >= (testsSize - 1)) {
            autoTestCountIndex = 0;
            _type++;
        }
        else
        {
            autoTestCountIndex++;
        }
        updateStatus();
    }
}

void PerformanceEventDispatcherScene::update(float dt)
{
    _testFunctions[_type].func();
}

void PerformanceEventDispatcherScene::updateQuantityOfNodes()
{
    _currentQuantityOfNodes = quantityOfNodes;
}

const char*  PerformanceEventDispatcherScene::testName()
{
    return _testFunctions[_type].name;
}


////////////////////////////////////////////////////////
//
// TouchEventDispatchingPerfTest
//
////////////////////////////////////////////////////////

void TouchEventDispatchingPerfTest::generateTestFunctions()
{
    TestFunction testFunctions[] = {
        { "OneByOne-scenegraph",    [=](){
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            if (quantityOfNodes != _lastRenderedCount)
            {
                auto listener = EventListenerTouchOneByOne::create();
                listener->onTouchBegan = [](Touch* touch, Event* event){
                    return false;
                };
                
                listener->onTouchMoved = [](Touch* touch, Event* event){};
                listener->onTouchEnded = [](Touch* touch, Event* event){};

                // Create new touchable nodes
                for (int i = 0; i < this->quantityOfNodes; ++i)
                {
                    auto node = Node::create();
                    node->setTag(1000 + i);
                    this->addChild(node);
                    this->_nodes.push_back(node);
                    dispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), node);
                }
                
                _lastRenderedCount = quantityOfNodes;
            }
            
            Size size = Director::getInstance()->getWinSize();
            EventTouch touchEvent;
            touchEvent.setEventCode(EventTouch::EventCode::BEGAN);
            std::vector<Touch*> touches;

            for (int i = 0; i < 4; ++i)
            {
                Touch* touch = new (std::nothrow) Touch();
                touch->autorelease();
                touch->setTouchInfo(i, rand() % 200, rand() % 200);
                touches.push_back(touch);
            }
            touchEvent.setTouches(touches);

            CC_PROFILER_START(this->profilerName());
            dispatcher->dispatchEvent(&touchEvent);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "OneByOne-fixed",    [=](){
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            if (quantityOfNodes != _lastRenderedCount)
            {
                auto listener = EventListenerTouchOneByOne::create();
                listener->onTouchBegan = [](Touch* touch, Event* event){
                    return false;
                };
                
                listener->onTouchMoved = [](Touch* touch, Event* event){};
                listener->onTouchEnded = [](Touch* touch, Event* event){};
                
                for (int i = 0; i < this->quantityOfNodes; ++i)
                {
                    auto l = listener->clone();
                    this->_fixedPriorityListeners.push_back(l);
                    dispatcher->addEventListenerWithFixedPriority(l, i+1);
                }
                
                _lastRenderedCount = quantityOfNodes;
            }
            
            Size size = Director::getInstance()->getWinSize();
            EventTouch touchEvent;
            touchEvent.setEventCode(EventTouch::EventCode::BEGAN);
            std::vector<Touch*> touches;
            
            for (int i = 0; i < 4; ++i)
            {
                Touch* touch = new (std::nothrow) Touch();
                touch->autorelease();
                touch->setTouchInfo(i, rand() % 200, rand() % 200);
                touches.push_back(touch);
            }
            touchEvent.setTouches(touches);
            
            CC_PROFILER_START(this->profilerName());
            dispatcher->dispatchEvent(&touchEvent);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "AllAtOnce-scenegraph",    [=](){
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            if (quantityOfNodes != _lastRenderedCount)
            {
                auto listener = EventListenerTouchAllAtOnce::create();
                listener->onTouchesBegan = [](const std::vector<Touch*> touches, Event* event){};
                listener->onTouchesMoved = [](const std::vector<Touch*> touches, Event* event){};
                listener->onTouchesEnded = [](const std::vector<Touch*> touches, Event* event){};
                
                // Create new touchable nodes
                for (int i = 0; i < this->quantityOfNodes; ++i)
                {
                    auto node = Node::create();
                    node->setTag(1000 + i);
                    this->addChild(node);
                    this->_nodes.push_back(node);
                    dispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), node);
                }
                
                _lastRenderedCount = quantityOfNodes;
            }
            
            Size size = Director::getInstance()->getWinSize();
            EventTouch touchEvent;
            touchEvent.setEventCode(EventTouch::EventCode::BEGAN);
            std::vector<Touch*> touches;
            
            for (int i = 0; i < 4; ++i)
            {
                Touch* touch = new (std::nothrow) Touch();
                touch->autorelease();
                touch->setTouchInfo(i, rand() % 200, rand() % 200);
                touches.push_back(touch);
            }
            touchEvent.setTouches(touches);
            
            CC_PROFILER_START(this->profilerName());
            dispatcher->dispatchEvent(&touchEvent);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "AllAtOnce-fixed",    [=](){
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            if (quantityOfNodes != _lastRenderedCount)
            {
                auto listener = EventListenerTouchAllAtOnce::create();
                listener->onTouchesBegan = [](const std::vector<Touch*> touches, Event* event){};
                listener->onTouchesMoved = [](const std::vector<Touch*> touches, Event* event){};
                listener->onTouchesEnded = [](const std::vector<Touch*> touches, Event* event){};
                
                for (int i = 0; i < this->quantityOfNodes; ++i)
                {
                    auto l = listener->clone();
                    this->_fixedPriorityListeners.push_back(l);
                    dispatcher->addEventListenerWithFixedPriority(l, i+1);
                }
                
                _lastRenderedCount = quantityOfNodes;
            }
            
            Size size = Director::getInstance()->getWinSize();
            EventTouch touchEvent;
            touchEvent.setEventCode(EventTouch::EventCode::BEGAN);
            std::vector<Touch*> touches;
            
            for (int i = 0; i < 4; ++i)
            {
                Touch* touch = new (std::nothrow) Touch();
                touch->autorelease();
                touch->setTouchInfo(i, rand() % 200, rand() % 200);
                touches.push_back(touch);
            }
            touchEvent.setTouches(touches);
            
            CC_PROFILER_START(this->profilerName());
            dispatcher->dispatchEvent(&touchEvent);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "TouchModeMix-scenegraph",    [=](){
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            if (quantityOfNodes != _lastRenderedCount)
            {
                auto listenerOneByOne = EventListenerTouchOneByOne::create();
                listenerOneByOne->onTouchBegan = [](Touch* touch, Event* event){
                    return false;
                };
                
                listenerOneByOne->onTouchMoved = [](Touch* touch, Event* event){};
                listenerOneByOne->onTouchEnded = [](Touch* touch, Event* event){};
                
                auto listenerAllAtOnce = EventListenerTouchAllAtOnce::create();
                listenerAllAtOnce->onTouchesBegan = [](const std::vector<Touch*> touches, Event* event){};
                listenerAllAtOnce->onTouchesMoved = [](const std::vector<Touch*> touches, Event* event){};
                listenerAllAtOnce->onTouchesEnded = [](const std::vector<Touch*> touches, Event* event){};
                
                int i = 0;
                // Create new touchable nodes
                for (; i < this->quantityOfNodes/2; ++i)
                {
                    auto node = Node::create();
                    node->setTag(1000 + i);
                    this->addChild(node);
                    this->_nodes.push_back(node);
                    dispatcher->addEventListenerWithSceneGraphPriority(listenerOneByOne->clone(), node);
                }
                
                for (; i < this->quantityOfNodes; ++i)
                {
                    auto node = Node::create();
                    node->setTag(1000 + i);
                    this->addChild(node);
                    this->_nodes.push_back(node);
                    dispatcher->addEventListenerWithSceneGraphPriority(listenerAllAtOnce->clone(), node);
                }
                
                _lastRenderedCount = quantityOfNodes;
            }
            
            Size size = Director::getInstance()->getWinSize();
            EventTouch touchEvent;
            touchEvent.setEventCode(EventTouch::EventCode::BEGAN);
            std::vector<Touch*> touches;
            
            for (int i = 0; i < 4; ++i)
            {
                Touch* touch = new (std::nothrow) Touch();
                touch->autorelease();
                touch->setTouchInfo(i, rand() % 200, rand() % 200);
                touches.push_back(touch);
            }
            touchEvent.setTouches(touches);
            
            CC_PROFILER_START(this->profilerName());
            dispatcher->dispatchEvent(&touchEvent);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "TouchModeMix-fixed",    [=](){
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            if (quantityOfNodes != _lastRenderedCount)
            {
                auto listenerOneByOne = EventListenerTouchOneByOne::create();
                listenerOneByOne->onTouchBegan = [](Touch* touch, Event* event){
                    return false;
                };
                
                listenerOneByOne->onTouchMoved = [](Touch* touch, Event* event){};
                listenerOneByOne->onTouchEnded = [](Touch* touch, Event* event){};
                
                auto listenerAllAtOnce = EventListenerTouchAllAtOnce::create();
                listenerAllAtOnce->onTouchesBegan = [](const std::vector<Touch*> touches, Event* event){};
                listenerAllAtOnce->onTouchesMoved = [](const std::vector<Touch*> touches, Event* event){};
                listenerAllAtOnce->onTouchesEnded = [](const std::vector<Touch*> touches, Event* event){};
                
                int i = 0;

                for (; i < this->quantityOfNodes/2; ++i)
                {
                    auto l = listenerOneByOne->clone();
                    this->_fixedPriorityListeners.push_back(l);
                    dispatcher->addEventListenerWithFixedPriority(l, i+1);
                }
                
                for (; i < this->quantityOfNodes; ++i)
                {
                    auto l = listenerAllAtOnce->clone();
                    this->_fixedPriorityListeners.push_back(l);
                    dispatcher->addEventListenerWithFixedPriority(l, i+1);
                }
                
                _lastRenderedCount = quantityOfNodes;
            }
            
            Size size = Director::getInstance()->getWinSize();
            EventTouch touchEvent;
            touchEvent.setEventCode(EventTouch::EventCode::BEGAN);
            std::vector<Touch*> touches;
            
            for (int i = 0; i < 4; ++i)
            {
                Touch* touch = new (std::nothrow) Touch();
                touch->autorelease();
                touch->setTouchInfo(i, rand() % 200, rand() % 200);
                touches.push_back(touch);
            }
            touchEvent.setTouches(touches);
            
            CC_PROFILER_START(this->profilerName());
            dispatcher->dispatchEvent(&touchEvent);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
    };
    
    for (const auto& func : testFunctions)
    {
        _testFunctions.push_back(func);
    }
}

std::string TouchEventDispatchingPerfTest::title() const
{
    return "Touch Event Dispatching Perf test";
}

std::string TouchEventDispatchingPerfTest::subtitle() const
{
    return "Test 'OneByOne-scenegraph', See console";
}

////////////////////////////////////////////////////////
//
// KeyboardEventDispatchingPerfTest
//
////////////////////////////////////////////////////////

void KeyboardEventDispatchingPerfTest::generateTestFunctions()
{
    TestFunction testFunctions[] = {
        { "keyboard-scenegraph",    [=](){
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            if (quantityOfNodes != _lastRenderedCount)
            {
                auto listener = EventListenerKeyboard::create();
                listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event){};
                listener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event){};
                
                // Create new nodes listen to keyboard event
                for (int i = 0; i < this->quantityOfNodes; ++i)
                {
                    auto node = Node::create();
                    node->setTag(1000 + i);
                    this->addChild(node);
                    this->_nodes.push_back(node);
                    dispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), node);
                }
                
                _lastRenderedCount = quantityOfNodes;
            }
            
            EventKeyboard event(EventKeyboard::KeyCode::KEY_RETURN, true);
            
            CC_PROFILER_START(this->profilerName());
            dispatcher->dispatchEvent(&event);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "keyboard-fixed",    [=](){
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            if (quantityOfNodes != _lastRenderedCount)
            {
                auto listener = EventListenerKeyboard::create();
                listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event){};
                listener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event){};
                
                for (int i = 0; i < this->quantityOfNodes; ++i)
                {
                    auto l = listener->clone();
                    this->_fixedPriorityListeners.push_back(l);
                    dispatcher->addEventListenerWithFixedPriority(l, i+1);
                }
                
                _lastRenderedCount = quantityOfNodes;
            }
            
            EventKeyboard event(EventKeyboard::KeyCode::KEY_RETURN, true);
            
            CC_PROFILER_START(this->profilerName());
            dispatcher->dispatchEvent(&event);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
    };
    
    for (const auto& func : testFunctions)
    {
        _testFunctions.push_back(func);
    }
}

std::string KeyboardEventDispatchingPerfTest::title() const
{
    return "Keyboard Event Dispatching Perf test";
}

std::string KeyboardEventDispatchingPerfTest::subtitle() const
{
    return "Test 'keyboard-scenegraph', See console";
}

////////////////////////////////////////////////////////
//
// CustomEventDispatchingPerfTest
//
////////////////////////////////////////////////////////

void CustomEventDispatchingPerfTest::onEnter()
{
    PerformanceEventDispatcherScene::onEnter();
    
    for (int i = 0; i < 2000; i++)
    {
        auto listener = EventListenerCustom::create(StringUtils::format("custom_event_%d", i), [](EventCustom* event){});
        _eventDispatcher->addEventListenerWithFixedPriority(listener, i + 1);
        _customListeners.push_back(listener);
    }
}

void CustomEventDispatchingPerfTest::onExit()
{
    for (auto& l : _customListeners)
    {
        _eventDispatcher->removeEventListener(l);
    }
    PerformanceEventDispatcherScene::onExit();
}

void CustomEventDispatchingPerfTest::generateTestFunctions()
{
    TestFunction testFunctions[] = {
        { "custom-scenegraph",    [=](){
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            if (quantityOfNodes != _lastRenderedCount)
            {
                auto listener = EventListenerCustom::create("custom_event_test_scenegraph", [](EventCustom* event){});
                
                // Create new nodes listen to custom event
                for (int i = 0; i < this->quantityOfNodes; ++i)
                {
                    auto node = Node::create();
                    node->setTag(1000 + i);
                    this->addChild(node);
                    this->_nodes.push_back(node);
                    dispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), node);
                }
                
                _lastRenderedCount = quantityOfNodes;
            }
            
            EventCustom event("custom_event_test_scenegraph");
            
            CC_PROFILER_START(this->profilerName());
            dispatcher->dispatchEvent(&event);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        { "custom-fixed",    [=](){
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            if (quantityOfNodes != _lastRenderedCount)
            {
                auto listener = EventListenerCustom::create("custom_event_test_fixed", [](EventCustom* event){});
                
                for (int i = 0; i < this->quantityOfNodes; ++i)
                {
                    auto l = listener->clone();
                    this->_fixedPriorityListeners.push_back(l);
                    dispatcher->addEventListenerWithFixedPriority(l, i+1);
                }
                
                _lastRenderedCount = quantityOfNodes;
            }
            
            EventCustom event("custom_event_test_fixed");
            
            CC_PROFILER_START(this->profilerName());
            dispatcher->dispatchEvent(&event);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
    };
    
    for (const auto& func : testFunctions)
    {
        _testFunctions.push_back(func);
    }
}

std::string CustomEventDispatchingPerfTest::title() const
{
    return "Custom Event Dispatching Perf test";
}

std::string CustomEventDispatchingPerfTest::subtitle() const
{
    return "Test 'custom-scenegraph', See console";
}
