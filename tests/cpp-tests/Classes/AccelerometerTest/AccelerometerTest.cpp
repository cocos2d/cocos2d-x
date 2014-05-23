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
AccelerometerTest::AccelerometerTest()
{
}

AccelerometerTest::~AccelerometerTest()
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
    label->setPosition( Vec2(VisibleRect::center().x, VisibleRect::top().y-50) );

    _ball = Sprite::create("Images/ball.png");
    _ball->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
    addChild(_ball);

    _ball->retain();
}

void AccelerometerTest::onAcceleration(Acceleration* acc, Event* event)
{
    /*FIXME: Testing on the Nexus S sometimes _ball is NULL */
    if ( _ball == nullptr ) {
        return;
    }

    auto ballSize  = _ball->getContentSize();

    auto pos  = _ball->getPosition();

    pos.x += acc->x * 9.81f;
    pos.y += acc->y * 9.81f;

    FIX_POS(pos.x, (VisibleRect::left().x+ballSize.width / 2.0), (VisibleRect::right().x - ballSize.width / 2.0));
    FIX_POS(pos.y, (VisibleRect::bottom().y+ballSize.height / 2.0), (VisibleRect::top().y - ballSize.height / 2.0));
    _ball->setPosition(pos);
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
