#include "PerformanceTouchesTest.h"

enum
{
    TEST_COUNT = 2,
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
    
    // Register Touch Event
    auto listener = TouchEventListener::create(Touch::DispatchMode::ONE_BY_ONE);
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(TouchesPerformTest1::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(TouchesPerformTest1::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(TouchesPerformTest1::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(TouchesPerformTest1::onTouchCancelled, this);
    
    EventDispatcher::getInstance()->registerEventListenerWithSceneGraphPriority(listener, this);
}

std::string TouchesPerformTest1::title()
{
    return "Targeted touches";
}

//void TouchesPerformTest1::registerWithTouchDispatcher()
//{
//    auto director = Director::getInstance();
//    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
//}

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
    
    // Register Touch Event
//    auto listener = TouchEventListener::create(Touch::DispatchMode::ALL_AT_ONCE);
//    
//    listener->onTouchesBegan = CC_CALLBACK_2(TouchesPerformTest2::onTouchesBegan, this);
//    listener->onTouchesMoved = CC_CALLBACK_2(TouchesPerformTest2::onTouchesMoved, this);
//    listener->onTouchesEnded = CC_CALLBACK_2(TouchesPerformTest2::onTouchesEnded, this);
//    listener->onTouchesCancelled = CC_CALLBACK_2(TouchesPerformTest2::onTouchesCancelled, this);
//    
//    EventDispatcher::getInstance()->registerEventListenerWithSceneGraphPriority(listener, this);
}

std::string TouchesPerformTest2::title()
{
    return "Standard touches";
}

//void TouchesPerformTest2::registerWithTouchDispatcher()
//{
//    auto director = Director::getInstance();
//    director->getTouchDispatcher()->addStandardDelegate(this, 0);
//}

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

void runTouchesTest()
{
    s_nTouchCurCase = 0;
    auto scene = Scene::create();
    auto layer = new TouchesPerformTest1(true, TEST_COUNT, s_nTouchCurCase);

    scene->addChild(layer);
    layer->release();

    Director::getInstance()->replaceScene(scene);
}
