//
//  PerformanceEventDispatcherTest.cpp
//

#include "PerformanceEventDispatcherTest.h"

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

static std::function<PerformanceEventDispatcherScene*()> createFunctions[] =
{
    CL(TouchEventDispatchingPerfTest),
    CL(KeyboardEventDispatchingPerfTest),
    CL(CustomEventDispatchingPerfTest),
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

enum {
    kTagInfoLayer = 1,
    
    kTagBase = 20000,
};

enum {
    kMaxNodes = 15000,
    kNodesIncrease = 500,
};

static int g_curCase = 0;

////////////////////////////////////////////////////////
//
// EventDispatcherBasicLayer
//
////////////////////////////////////////////////////////

EventDispatcherBasicLayer::EventDispatcherBasicLayer(bool bControlMenuVisible, int nMaxCases, int nCurCase)
: PerformBasicLayer(bControlMenuVisible, nMaxCases, nCurCase)
{
}

void EventDispatcherBasicLayer::showCurrentTest()
{
    int nodes = ((PerformanceEventDispatcherScene*)getParent())->getQuantityOfNodes();
    
    auto scene = createFunctions[_curCase]();
    
    g_curCase = _curCase;
    
    if (scene)
    {
        scene->initWithQuantityOfNodes(nodes);
        
        Director::getInstance()->replaceScene(scene);
    }
}

////////////////////////////////////////////////////////
//
// PerformanceEventDispatcherScene
//
////////////////////////////////////////////////////////
void PerformanceEventDispatcherScene::initWithQuantityOfNodes(unsigned int nNodes)
{
    _type = 0;
    srand(time(nullptr));
    auto s = Director::getInstance()->getWinSize();
    
    // Title
    auto label = LabelTTF::create(title().c_str(), "Arial", 40);
    addChild(label, 1, TAG_TITLE);
    label->setPosition(Point(s.width/2, s.height-32));
    label->setColor(Color3B(255,255,40));
    
    // Subtitle
    std::string strSubTitle = subtitle();
    if(strSubTitle.length())
    {
        auto l = LabelTTF::create(strSubTitle.c_str(), "Thonburi", 16);
        addChild(l, 1, TAG_SUBTITLE);
        l->setPosition(Point(s.width/2, s.height-80));
    }
    
    _lastRenderedCount = 0;
    _currentQuantityOfNodes = 0;
    _quantityOfNodes = nNodes;
    
    MenuItemFont::setFontSize(65);
    auto decrease = MenuItemFont::create(" - ", [&](Object *sender) {
		_quantityOfNodes -= kNodesIncrease;
		if( _quantityOfNodes < 0 )
			_quantityOfNodes = 0;
        
		updateQuantityLabel();
		updateQuantityOfNodes();
        updateProfilerName();
        CC_PROFILER_PURGE_ALL();
        srand(0);
	});
    decrease->setColor(Color3B(0,200,20));
    _decrease = decrease;
    
    auto increase = MenuItemFont::create(" + ", [&](Object *sender) {
		_quantityOfNodes += kNodesIncrease;
		if( _quantityOfNodes > kMaxNodes )
			_quantityOfNodes = kMaxNodes;
        
		updateQuantityLabel();
		updateQuantityOfNodes();
        updateProfilerName();
        CC_PROFILER_PURGE_ALL();
        srand(0);
	});
    increase->setColor(Color3B(0,200,20));
    _increase = increase;
    
    auto menu = Menu::create(decrease, increase, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(Point(s.width/2, s.height/2+15));
    addChild(menu, 1);
    
    auto infoLabel = LabelTTF::create("0 listeners", "Marker Felt", 30);
    infoLabel->setColor(Color3B(0,200,20));
    infoLabel->setPosition(Point(s.width/2, s.height/2-15));
    addChild(infoLabel, 1, kTagInfoLayer);
    
    auto menuLayer = new EventDispatcherBasicLayer(true, MAX_LAYER, g_curCase);
    addChild(menuLayer);
    menuLayer->release();
    
    printf("Size of Node: %lu\n", sizeof(Node));
    
    int oldFontSize = MenuItemFont::getFontSize();
    MenuItemFont::setFontSize(24);
    
    Vector<cocos2d::MenuItem *> toggleItems;
    
    generateTestFunctions();
    
    CCASSERT(!_testFunctions.empty(), "Should not be empty after generate test functions");
    
    
    for (const auto& f : _testFunctions)
    {
        toggleItems.pushBack(MenuItemFont::create(f.name));
    }
    
    auto reset = [this](){
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
    };
    
    auto toggle = MenuItemToggle::createWithCallback([=](Object* sender){
        auto toggle = static_cast<MenuItemToggle*>(sender);
        this->_type = toggle->getSelectedIndex();
        auto label = static_cast<LabelTTF*>(this->getChildByTag(TAG_SUBTITLE));
        label->setString(StringUtils::format("Test '%s', See console", this->_testFunctions[this->_type].name));
        this->updateProfilerName();
        reset();
    }, toggleItems);
    
    toggle->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    toggle->setPosition(VisibleRect::left());
    _toggle = toggle;
    
    auto start = MenuItemFont::create("start", [this](Object* sender){
        auto director = Director::getInstance();
        auto sched = director->getScheduler();
        
        CC_PROFILER_PURGE_ALL();
        sched->scheduleSelector(schedule_selector(PerformanceEventDispatcherScene::dumpProfilerInfo), this, 2, false);
        
        this->unscheduleUpdate();
        this->scheduleUpdate();
        this->_startItem->setEnabled(false);
        this->_stopItem->setEnabled(true);
        this->_toggle->setEnabled(false);
        this->_increase->setEnabled(false);
        this->_decrease->setEnabled(false);
    });
    start->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    start->setPosition(VisibleRect::right() + Point(0, 40));
    _startItem = start;
    
    auto stop = MenuItemFont::create("stop", [=](Object* sender){
        auto director = Director::getInstance();
        auto sched = director->getScheduler();
        
        sched->unscheduleSelector(schedule_selector(PerformanceEventDispatcherScene::dumpProfilerInfo), this);
        
        this->unscheduleUpdate();
        this->_startItem->setEnabled(true);
        this->_stopItem->setEnabled(false);
        this->_toggle->setEnabled(true);
        this->_increase->setEnabled(true);
        this->_decrease->setEnabled(true);
        
        reset();
    });
    
    stop->setEnabled(false);
    stop->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    stop->setPosition(VisibleRect::right() + Point(0, -40));
    _stopItem = stop;
    
    auto menu2 = Menu::create(toggle, start, stop, NULL);
    menu2->setPosition(Point::ZERO);
    addChild(menu2);
    
    MenuItemFont::setFontSize(oldFontSize);
    
    updateQuantityLabel();
    updateQuantityOfNodes();
    updateProfilerName();
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
    if( _quantityOfNodes != _lastRenderedCount )
    {
        auto infoLabel = static_cast<LabelTTF*>( getChildByTag(kTagInfoLayer) );
        char str[20] = {0};
        sprintf(str, "%u listeners", _quantityOfNodes);
        infoLabel->setString(str);
    }
}

const char * PerformanceEventDispatcherScene::profilerName()
{
    return _profilerName;
}

void PerformanceEventDispatcherScene::updateProfilerName()
{
    snprintf(_profilerName, sizeof(_profilerName)-1, "%s(%d)", testName(), _quantityOfNodes);
}

void PerformanceEventDispatcherScene::dumpProfilerInfo(float dt)
{
	CC_PROFILER_DISPLAY_TIMERS();
}

void PerformanceEventDispatcherScene::update(float dt)
{
    _testFunctions[_type].func();
}

void PerformanceEventDispatcherScene::updateQuantityOfNodes()
{
    _currentQuantityOfNodes = _quantityOfNodes;
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
            if (_quantityOfNodes != _lastRenderedCount)
            {
                auto listener = EventListenerTouchOneByOne::create();
                listener->onTouchBegan = [](Touch* touch, Event* event){
                    return false;
                };
                
                listener->onTouchMoved = [](Touch* touch, Event* event){};
                listener->onTouchEnded = [](Touch* touch, Event* event){};

                // Create new touchable nodes
                for (int i = 0; i < this->_quantityOfNodes; ++i)
                {
                    auto node = Node::create();
                    node->setTag(1000 + i);
                    this->addChild(node);
                    this->_nodes.push_back(node);
                    dispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), node);
                }
                
                _lastRenderedCount = _quantityOfNodes;
            }
            
            Size size = Director::getInstance()->getWinSize();
            EventTouch touchEvent;
            touchEvent.setEventCode(EventTouch::EventCode::BEGAN);
            std::vector<Touch*> touches;

            for (int i = 0; i < 4; ++i)
            {
                Touch* touch = new Touch();
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
            if (_quantityOfNodes != _lastRenderedCount)
            {
                auto listener = EventListenerTouchOneByOne::create();
                listener->onTouchBegan = [](Touch* touch, Event* event){
                    return false;
                };
                
                listener->onTouchMoved = [](Touch* touch, Event* event){};
                listener->onTouchEnded = [](Touch* touch, Event* event){};
                
                for (int i = 0; i < this->_quantityOfNodes; ++i)
                {
                    auto l = listener->clone();
                    this->_fixedPriorityListeners.push_back(l);
                    dispatcher->addEventListenerWithFixedPriority(l, i+1);
                }
                
                _lastRenderedCount = _quantityOfNodes;
            }
            
            Size size = Director::getInstance()->getWinSize();
            EventTouch touchEvent;
            touchEvent.setEventCode(EventTouch::EventCode::BEGAN);
            std::vector<Touch*> touches;
            
            for (int i = 0; i < 4; ++i)
            {
                Touch* touch = new Touch();
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
            if (_quantityOfNodes != _lastRenderedCount)
            {
                auto listener = EventListenerTouchAllAtOnce::create();
                listener->onTouchesBegan = [](const std::vector<Touch*> touches, Event* event){};
                listener->onTouchesMoved = [](const std::vector<Touch*> touches, Event* event){};
                listener->onTouchesEnded = [](const std::vector<Touch*> touches, Event* event){};
                
                // Create new touchable nodes
                for (int i = 0; i < this->_quantityOfNodes; ++i)
                {
                    auto node = Node::create();
                    node->setTag(1000 + i);
                    this->addChild(node);
                    this->_nodes.push_back(node);
                    dispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), node);
                }
                
                _lastRenderedCount = _quantityOfNodes;
            }
            
            Size size = Director::getInstance()->getWinSize();
            EventTouch touchEvent;
            touchEvent.setEventCode(EventTouch::EventCode::BEGAN);
            std::vector<Touch*> touches;
            
            for (int i = 0; i < 4; ++i)
            {
                Touch* touch = new Touch();
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
            if (_quantityOfNodes != _lastRenderedCount)
            {
                auto listener = EventListenerTouchAllAtOnce::create();
                listener->onTouchesBegan = [](const std::vector<Touch*> touches, Event* event){};
                listener->onTouchesMoved = [](const std::vector<Touch*> touches, Event* event){};
                listener->onTouchesEnded = [](const std::vector<Touch*> touches, Event* event){};
                
                for (int i = 0; i < this->_quantityOfNodes; ++i)
                {
                    auto l = listener->clone();
                    this->_fixedPriorityListeners.push_back(l);
                    dispatcher->addEventListenerWithFixedPriority(l, i+1);
                }
                
                _lastRenderedCount = _quantityOfNodes;
            }
            
            Size size = Director::getInstance()->getWinSize();
            EventTouch touchEvent;
            touchEvent.setEventCode(EventTouch::EventCode::BEGAN);
            std::vector<Touch*> touches;
            
            for (int i = 0; i < 4; ++i)
            {
                Touch* touch = new Touch();
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
            if (_quantityOfNodes != _lastRenderedCount)
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
                for (; i < this->_quantityOfNodes/2; ++i)
                {
                    auto node = Node::create();
                    node->setTag(1000 + i);
                    this->addChild(node);
                    this->_nodes.push_back(node);
                    dispatcher->addEventListenerWithSceneGraphPriority(listenerOneByOne->clone(), node);
                }
                
                for (; i < this->_quantityOfNodes; ++i)
                {
                    auto node = Node::create();
                    node->setTag(1000 + i);
                    this->addChild(node);
                    this->_nodes.push_back(node);
                    dispatcher->addEventListenerWithSceneGraphPriority(listenerAllAtOnce->clone(), node);
                }
                
                _lastRenderedCount = _quantityOfNodes;
            }
            
            Size size = Director::getInstance()->getWinSize();
            EventTouch touchEvent;
            touchEvent.setEventCode(EventTouch::EventCode::BEGAN);
            std::vector<Touch*> touches;
            
            for (int i = 0; i < 4; ++i)
            {
                Touch* touch = new Touch();
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
            if (_quantityOfNodes != _lastRenderedCount)
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

                for (; i < this->_quantityOfNodes/2; ++i)
                {
                    auto l = listenerOneByOne->clone();
                    this->_fixedPriorityListeners.push_back(l);
                    dispatcher->addEventListenerWithFixedPriority(l, i+1);
                }
                
                for (; i < this->_quantityOfNodes; ++i)
                {
                    auto l = listenerAllAtOnce->clone();
                    this->_fixedPriorityListeners.push_back(l);
                    dispatcher->addEventListenerWithFixedPriority(l, i+1);
                }
                
                _lastRenderedCount = _quantityOfNodes;
            }
            
            Size size = Director::getInstance()->getWinSize();
            EventTouch touchEvent;
            touchEvent.setEventCode(EventTouch::EventCode::BEGAN);
            std::vector<Touch*> touches;
            
            for (int i = 0; i < 4; ++i)
            {
                Touch* touch = new Touch();
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
            if (_quantityOfNodes != _lastRenderedCount)
            {
                auto listener = EventListenerKeyboard::create();
                listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event){};
                listener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event){};
                
                // Create new nodes listen to keyboard event
                for (int i = 0; i < this->_quantityOfNodes; ++i)
                {
                    auto node = Node::create();
                    node->setTag(1000 + i);
                    this->addChild(node);
                    this->_nodes.push_back(node);
                    dispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), node);
                }
                
                _lastRenderedCount = _quantityOfNodes;
            }
            
            EventKeyboard event(EventKeyboard::KeyCode::KEY_RETURN, true);
            
            CC_PROFILER_START(this->profilerName());
            dispatcher->dispatchEvent(&event);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "keyboard-fixed",    [=](){
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            if (_quantityOfNodes != _lastRenderedCount)
            {
                auto listener = EventListenerKeyboard::create();
                listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event){};
                listener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event){};
                
                for (int i = 0; i < this->_quantityOfNodes; ++i)
                {
                    auto l = listener->clone();
                    this->_fixedPriorityListeners.push_back(l);
                    dispatcher->addEventListenerWithFixedPriority(l, i+1);
                }
                
                _lastRenderedCount = _quantityOfNodes;
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
            if (_quantityOfNodes != _lastRenderedCount)
            {
                auto listener = EventListenerCustom::create("custom_event_test_scenegraph", [](EventCustom* event){});
                
                // Create new nodes listen to custom event
                for (int i = 0; i < this->_quantityOfNodes; ++i)
                {
                    auto node = Node::create();
                    node->setTag(1000 + i);
                    this->addChild(node);
                    this->_nodes.push_back(node);
                    dispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), node);
                }
                
                _lastRenderedCount = _quantityOfNodes;
            }
            
            EventCustom event("custom_event_test_scenegraph");
            
            CC_PROFILER_START(this->profilerName());
            dispatcher->dispatchEvent(&event);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        { "custom-fixed",    [=](){
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            if (_quantityOfNodes != _lastRenderedCount)
            {
                auto listener = EventListenerCustom::create("custom_event_test_fixed", [](EventCustom* event){});
                
                for (int i = 0; i < this->_quantityOfNodes; ++i)
                {
                    auto l = listener->clone();
                    this->_fixedPriorityListeners.push_back(l);
                    dispatcher->addEventListenerWithFixedPriority(l, i+1);
                }
                
                _lastRenderedCount = _quantityOfNodes;
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

///----------------------------------------
void runEventDispatcherPerformanceTest()
{
    auto scene = createFunctions[g_curCase]();
    scene->initWithQuantityOfNodes(kNodesIncrease);
    
    Director::getInstance()->replaceScene(scene);
}

