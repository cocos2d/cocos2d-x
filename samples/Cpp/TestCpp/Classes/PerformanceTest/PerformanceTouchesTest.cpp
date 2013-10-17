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
    Layer* layer = NULL;
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
    auto label = LabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label, 1);
    label->setPosition(Point(s.width/2, s.height-50));

    scheduleUpdate();

    _plabel = LabelBMFont::create("00.0", "fonts/arial16.fnt");
    _plabel->setPosition(Point(s.width/2, s.height/2));
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

std::string TouchesMainScene::title()
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
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    setSwallowsTouches(true);
}

std::string TouchesPerformTest1::title()
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
    setTouchEnabled(true);
}

std::string TouchesPerformTest2::title()
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
    virtual bool onTouchBegan(Touch *touch, Event *event)
    {
        return false;
    }
    virtual void onTouchMoved(Touch *touch, Event *event) {}
    virtual void onTouchEnded(Touch *touch, Event *event) {}
    virtual void onTouchCancelled(Touch *touch, Event *event) {}
    
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *event) {}
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *event) {}
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *event) {}
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *event) {}
};



void TouchesPerformTest3::onEnter()
{
    PerformBasicLayer::onEnter();
    
    
    auto s = Director::getInstance()->getWinSize();
    
    // add title
    auto label = LabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label, 1);
    label->setPosition(Point(s.width/2, s.height-50));
    
#define TOUCH_PROFILER_NAME  "TouchProfileName"
#define TOUCHABLE_NODE_NUM 1000
    
    srand(time(nullptr));
    
    for (int i = 0; i < TOUCHABLE_NODE_NUM; ++i)
    {
        int zorder = rand() % TOUCHABLE_NODE_NUM;
        auto layer = new TouchableLayer();
        layer->setTouchEnabled(true);
        layer->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
        addChild(layer, zorder);
        layer->release();
    }
    
    auto emitEventlabel = LabelTTF::create("Emit Touch Event", "", 24);
    auto menuItem = MenuItemLabel::create(emitEventlabel, [](Object* sender){
        
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
        
        auto dispatcher = EventDispatcher::getInstance();
        
        for (int i = 0; i < 100; ++i)
        {
            CC_PROFILER_START(TOUCH_PROFILER_NAME);
            
            dispatcher->dispatchEvent(&event, false);
            
            CC_PROFILER_STOP(TOUCH_PROFILER_NAME);
        }
        
        CC_PROFILER_DISPLAY_TIMERS();
        
        for (auto& touch : touches)
        {
            touch->release();
        }
    });
    
    menuItem->setPosition(Point(0, -20));
    auto menu = Menu::create(menuItem, NULL);
    addChild(menu);
}

std::string TouchesPerformTest3::title()
{
    return "Touch Event Perf Test";
}

void TouchesPerformTest3::showCurrentTest()
{
    Layer* layer = NULL;
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
