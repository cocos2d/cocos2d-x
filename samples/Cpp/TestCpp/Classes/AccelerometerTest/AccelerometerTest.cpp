#include "AccelerometerTest.h"
#include "../testResource.h"
#include "cocos2d.h"

#define FIX_POS(_pos, _min, _max) \
    if (_pos < _min)        \
    _pos = _min;        \
else if (_pos > _max)   \
    _pos = _max;        \

//------------------------------------------------------------------
//
// AccelerometerTest
//
//------------------------------------------------------------------
AccelerometerTest::AccelerometerTest(void)
: _lastTime(0.0)
{
}

AccelerometerTest::~AccelerometerTest(void)
{
    _ball->release();
}

std::string AccelerometerTest::title()
{
    return "AccelerometerTest";
}

void AccelerometerTest::onEnter()
{
    Layer::onEnter();

    setAccelerometerEnabled(true);


    LabelTTF* label = LabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label, 1);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-50) );

    _ball = Sprite::create("Images/ball.png");
    _ball->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y));
    addChild(_ball);

    _ball->retain();
}

void AccelerometerTest::didAccelerate(Acceleration* pAccelerationValue)
{
//     double fNow = pAccelerationValue->timestamp;
// 
//     if (_lastTime > 0.0)
//     {
//         Point ptNow = convertToUI
//     }
// 
//     _lastTime = fNow;

    Director* pDir = Director::sharedDirector();

    /*FIXME: Testing on the Nexus S sometimes _ball is NULL */
    if ( _ball == NULL ) {
        return;
    }

    Size ballSize  = _ball->getContentSize();

    Point ptNow  = _ball->getPosition();
    Point ptTemp = pDir->convertToUI(ptNow);

    ptTemp.x += pAccelerationValue->x * 9.81f;
    ptTemp.y -= pAccelerationValue->y * 9.81f;

    Point ptNext = pDir->convertToGL(ptTemp);
    FIX_POS(ptNext.x, (VisibleRect::left().x+ballSize.width / 2.0), (VisibleRect::right().x - ballSize.width / 2.0));
    FIX_POS(ptNext.y, (VisibleRect::bottom().y+ballSize.height / 2.0), (VisibleRect::top().y - ballSize.height / 2.0));
    _ball->setPosition(ptNext);
}

//------------------------------------------------------------------
//
// AccelerometerTestScene
//
//------------------------------------------------------------------
void AccelerometerTestScene::runThisTest()
{
    Layer* pLayer = new AccelerometerTest();
    addChild(pLayer);
    pLayer->release();

    Director::sharedDirector()->replaceScene(this);
}
