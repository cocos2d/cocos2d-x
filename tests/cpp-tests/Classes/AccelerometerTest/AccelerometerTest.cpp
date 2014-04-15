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
    Device::setAccelerometerEnabled(false);
}

std::string AccelerometerTest::title() const
{
    return "AccelerometerTest";
}

void AccelerometerTest::onEnter()
{
    Layer::onEnter();

    Device::setAccelerometerEnabled(true);
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(AccelerometerTest::onAcceleration, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto label = Label::createWithTTF(title().c_str(), "fonts/arial.ttf", 32.0f);
    addChild(label, 1);
    label->setPosition( Vector2(VisibleRect::center().x, VisibleRect::top().y-50) );

    _ball = Sprite::create("Images/ball.png");
    _ball->setPosition(Vector2(VisibleRect::center().x, VisibleRect::center().y));
    addChild(_ball);

    _ball->retain();
}

void AccelerometerTest::onAcceleration(Acceleration* acc, Event* event)
{
//     double fNow = pAccelerationValue->timestamp;
// 
//     if (_lastTime > 0.0)
//     {
//         auto ptNow = convertToUI
//     }
// 
//     _lastTime = fNow;

    auto pDir = Director::getInstance();

    /*FIXME: Testing on the Nexus S sometimes _ball is NULL */
    if ( _ball == NULL ) {
        return;
    }

    auto ballSize  = _ball->getContentSize();

    auto ptNow  = _ball->getPosition();
    auto ptTemp = pDir->convertToUI(ptNow);

    ptTemp.x += acc->x * 9.81f;
    ptTemp.y -= acc->y * 9.81f;

    auto ptNext = pDir->convertToGL(ptTemp);
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
    auto layer = new AccelerometerTest();
    addChild(layer);
    layer->release();

    Director::getInstance()->replaceScene(this);
}
