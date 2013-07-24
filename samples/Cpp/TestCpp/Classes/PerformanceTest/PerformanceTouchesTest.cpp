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
        Scene* scene = Scene::create();
        scene->addChild(layer);
        layer->release();

        Director::getInstance()->replaceScene(scene);
    }
}

void TouchesMainScene::onEnter()
{
    PerformBasicLayer::onEnter();

    Size s = Director::getInstance()->getWinSize();

    // add title
    LabelTTF *label = LabelTTF::create(title().c_str(), "Arial", 32);
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
}

std::string TouchesPerformTest1::title()
{
    return "Targeted touches";
}

void TouchesPerformTest1::registerWithTouchDispatcher()
{
    Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool TouchesPerformTest1::ccTouchBegan(Touch* touch, Event* event)
{
    numberOfTouchesB++;
    return true;
}

void TouchesPerformTest1::ccTouchMoved(Touch* touch, Event* event)
{
    numberOfTouchesM++;
}

void TouchesPerformTest1::ccTouchEnded(Touch* touch, Event* event)
{
    numberOfTouchesE++;
}

void TouchesPerformTest1::ccTouchCancelled(Touch* touch, Event* event)
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

void TouchesPerformTest2::registerWithTouchDispatcher()
{
    Director* director = Director::getInstance();
    director->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void TouchesPerformTest2::ccTouchesBegan(Set* touches, Event* event)
{
    numberOfTouchesB += touches->count();
}

void TouchesPerformTest2::ccTouchesMoved(Set* touches, Event* event)
{
    numberOfTouchesM += touches->count();
}
void TouchesPerformTest2::ccTouchesEnded(Set* touches, Event* event)
{
    numberOfTouchesE += touches->count();
}

void TouchesPerformTest2::ccTouchesCancelled(Set* touches, Event* event)
{
    numberOfTouchesC += touches->count();
}

void runTouchesTest()
{
    s_nTouchCurCase = 0;
    Scene* scene = Scene::create();
    Layer* layer = new TouchesPerformTest1(true, TEST_COUNT, s_nTouchCurCase);

    scene->addChild(layer);
    layer->release();

    Director::getInstance()->replaceScene(scene);
}
