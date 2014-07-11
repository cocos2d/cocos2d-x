#include "PerformanceTouchesTest.h"

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

enum
{
    TEST_COUNT = 3,
};

static int s_nTouchCurCase = 0;

////////////////////////////////////////////////////////
//
// TouchesMainScene
//
////////////////////////////////////////////////////////
void TouchesMainScene::showCurrentTest()
{
    Layer* layer = nullptr;
    switch (_curCase)
    {
    case 0:
        layer = new TouchesPerformTest1(true, TEST_COUNT, _curCase);
        break;
    case 1:
        layer = new TouchesPerformTest2(true, TEST_COUNT, _curCase);
        break;
    case 2:
        layer = new TouchesPerformTest3(true, TEST_COUNT, _curCase);
        break;
    }
    s_nTouchCurCase = _curCase;

    if (layer)
    {
        auto scene = Scene::create();
        scene->addChild(layer);
        layer->release();

        Director::getInstance()->replaceScene(scene);
    }
}

void TouchesMainScene::onEnter()
{
    PerformBasicLayer::onEnter();

    auto s = Director::getInstance()->getWinSize();

    // add title
    auto label = Label::createWithTTF(title().c_str(), "fonts/arial.ttf", 32);
    addChild(label, 1);
    label->setPosition(Vec2(s.width/2, s.height-50));

    scheduleUpdate();

    _plabel = Label::createWithBMFont("fonts/arial16.fnt","00.0");
    _plabel->setPosition(Vec2(s.width/2, s.height/2));
    addChild(_plabel);

    elapsedTime = 0;
    numberOfTouchesB = numberOfTouchesM = numberOfTouchesE = numberOfTouchesC = 0;    
}

void TouchesMainScene::update(float dt)
{
    elapsedTime += dt;

    if ( elapsedTime > 1.0f)
    {
        float frameRateB = numberOfTouchesB / elapsedTime;
        float frameRateM = numberOfTouchesM / elapsedTime;
        float frameRateE = numberOfTouchesE / elapsedTime;
        float frameRateC = numberOfTouchesC / elapsedTime;
        elapsedTime = 0;
        numberOfTouchesB = numberOfTouchesM = numberOfTouchesE = numberOfTouchesC = 0;

        char str[32] = {0};
        sprintf(str, "%.1f %.1f %.1f %.1f", frameRateB, frameRateM, frameRateE, frameRateC);
        _plabel->setString(str);
    }
}

std::string TouchesMainScene::title() const
{
    return "No title";
}

////////////////////////////////////////////////////////
//
// TouchesPerformTest1
//
////////////////////////////////////////////////////////
void TouchesPerformTest1::onEnter()
{
    TouchesMainScene::onEnter();
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(TouchesPerformTest1::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(TouchesPerformTest1::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(TouchesPerformTest1::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(TouchesPerformTest1::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

std::string TouchesPerformTest1::title() const
{
    return "Targeted touches";
}

bool TouchesPerformTest1::onTouchBegan(Touch* touch, Event* event)
{
    numberOfTouchesB++;
    return true;
}

void TouchesPerformTest1::onTouchMoved(Touch* touch, Event* event)
{
    numberOfTouchesM++;
}

void TouchesPerformTest1::onTouchEnded(Touch* touch, Event* event)
{
    numberOfTouchesE++;
}

void TouchesPerformTest1::onTouchCancelled(Touch* touch, Event* event)
{
    numberOfTouchesC++;
}

////////////////////////////////////////////////////////
//
// TouchesPerformTest2
//
////////////////////////////////////////////////////////
void TouchesPerformTest2::onEnter()
{
    TouchesMainScene::onEnter();
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(TouchesPerformTest2::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(TouchesPerformTest2::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(TouchesPerformTest2::onTouchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(TouchesPerformTest2::onTouchesCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

std::string TouchesPerformTest2::title() const
{
    return "Standard touches";
}

void TouchesPerformTest2::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
    numberOfTouchesB += touches.size();
}

void TouchesPerformTest2::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    numberOfTouchesM += touches.size();
}
void TouchesPerformTest2::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    numberOfTouchesE += touches.size();
}

void TouchesPerformTest2::onTouchesCancelled(const std::vector<Touch*>& touches, Event* event)
{
    numberOfTouchesC += touches.size();
}

////////////////////////////////////////////////////////
//
// TouchesPerformTest3
//
////////////////////////////////////////////////////////

class TouchableLayer : public Layer
{
public:
    bool onTouchBegan(Touch *touch, Event *event)
    {
        return false;
    }
    void onTouchMoved(Touch *touch, Event *event) {}
    void onTouchEnded(Touch *touch, Event *event) {}
    void onTouchCancelled(Touch *touch, Event *event) {}
};



void TouchesPerformTest3::onEnter()
{
    PerformBasicLayer::onEnter();
    
    
    auto s = Director::getInstance()->getWinSize();
    
    // add title
    auto label = Label::createWithTTF(title().c_str(), "fonts/arial.ttf", 32);
    addChild(label, 1);
    label->setPosition(Vec2(s.width/2, s.height-50));
    
#define TOUCH_PROFILER_NAME  "TouchProfileName"
#define TOUCHABLE_NODE_NUM 1000
    
    srand((unsigned)time(nullptr));
    
    for (int i = 0; i < TOUCHABLE_NODE_NUM; ++i)
    {
        int zorder = rand() % TOUCHABLE_NODE_NUM;
        auto layer = new TouchableLayer();
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(TouchableLayer::onTouchBegan, layer);
        listener->onTouchMoved = CC_CALLBACK_2(TouchableLayer::onTouchMoved, layer);
        listener->onTouchEnded = CC_CALLBACK_2(TouchableLayer::onTouchEnded, layer);
        listener->onTouchCancelled = CC_CALLBACK_2(TouchableLayer::onTouchCancelled, layer);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, layer);
        
        addChild(layer, zorder);
        layer->release();
    }
    
    auto emitEventlabel = Label::createWithSystemFont("Emit Touch Event", "", 24);
    auto menuItem = MenuItemLabel::create(emitEventlabel, [this](Ref* sender){
        
        CC_PROFILER_PURGE_ALL();
        
        std::vector<Touch*> touches;
        for (int i = 0; i < EventTouch::MAX_TOUCHES; ++i)
        {
            Touch* touch = new Touch();
            touch->setTouchInfo(i, 10, (i+1) * 10);
            touches.push_back(touch);
        }
        
        EventTouch event;
        event.setEventCode(EventTouch::EventCode::BEGAN);
        event.setTouches(touches);
        
        for (int i = 0; i < 100; ++i)
        {
            CC_PROFILER_START(TOUCH_PROFILER_NAME);
            
            _eventDispatcher->dispatchEvent(&event);
            
            CC_PROFILER_STOP(TOUCH_PROFILER_NAME);
        }
        
        CC_PROFILER_DISPLAY_TIMERS();
        
        for (auto& touch : touches)
        {
            touch->release();
        }
    });
    
    menuItem->setPosition(Vec2(0, -20));
    auto menu = Menu::create(menuItem, nullptr);
    addChild(menu);
}

std::string TouchesPerformTest3::title() const
{
    return "Touch Event Perf Test";
}

void TouchesPerformTest3::showCurrentTest()
{
    Layer* layer = nullptr;
    switch (_curCase)
    {
        case 0:
            layer = new TouchesPerformTest1(true, TEST_COUNT, _curCase);
            break;
        case 1:
            layer = new TouchesPerformTest2(true, TEST_COUNT, _curCase);
            break;
        case 2:
            layer = new TouchesPerformTest3(true, TEST_COUNT, _curCase);
            break;
    }
    s_nTouchCurCase = _curCase;
    
    if (layer)
    {
        auto scene = Scene::create();
        scene->addChild(layer);
        layer->release();
        
        Director::getInstance()->replaceScene(scene);
    }
}

void runTouchesTest()
{
    s_nTouchCurCase = 0;
    auto scene = Scene::create();
    auto layer = new TouchesPerformTest1(true, TEST_COUNT, s_nTouchCurCase);

    scene->addChild(layer);
    layer->release();

    Director::getInstance()->replaceScene(scene);
}
