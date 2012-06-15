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
    CCLayer* pLayer = NULL;
    switch (m_nCurCase)
    {
    case 0:
        pLayer = new TouchesPerformTest1(true, TEST_COUNT, m_nCurCase);
        break;
    case 1:
        pLayer = new TouchesPerformTest2(true, TEST_COUNT, m_nCurCase);
        break;
    }
    s_nTouchCurCase = m_nCurCase;

    if (pLayer)
    {
        CCScene* pScene = CCScene::create();
        pScene->addChild(pLayer);
        pLayer->release();

        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

void TouchesMainScene::onEnter()
{
    PerformBasicLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // add title
    CCLabelTTF *label = CCLabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label, 1);
    label->setPosition(ccp(s.width/2, s.height-50));

    scheduleUpdate();

    m_plabel = CCLabelBMFont::create("00.0", "fonts/arial16.fnt");
    m_plabel->setPosition(ccp(s.width/2, s.height/2));
    addChild(m_plabel);

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
        m_plabel->setString(str);
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
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool TouchesPerformTest1::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    numberOfTouchesB++;
    return true;
}

void TouchesPerformTest1::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    numberOfTouchesM++;
}

void TouchesPerformTest1::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    numberOfTouchesE++;
}

void TouchesPerformTest1::ccTouchCancelled(CCTouch* touch, CCEvent* event)
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
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void TouchesPerformTest2::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    numberOfTouchesB += touches->count();
}

void TouchesPerformTest2::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    numberOfTouchesM += touches->count();
}
void TouchesPerformTest2::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    numberOfTouchesE += touches->count();
}

void TouchesPerformTest2::ccTouchesCancelled(CCSet* touches, CCEvent* event)
{
    numberOfTouchesC += touches->count();
}

void runTouchesTest()
{
    s_nTouchCurCase = 0;
    CCScene* pScene = CCScene::create();
    CCLayer* pLayer = new TouchesPerformTest1(true, TEST_COUNT, s_nTouchCurCase);

    pScene->addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(pScene);
}
