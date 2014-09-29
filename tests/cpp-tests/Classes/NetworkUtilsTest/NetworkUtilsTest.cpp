#include "NetworkUtilsTest.h"

NetworkUtilsTest::NetworkUtilsTest()
{
    auto label = Label::createWithTTF("NetworkUtils Test", "fonts/arial.ttf", 28);
    addChild(label, 0);
    label->setPosition(VisibleRect::center().x, VisibleRect::top().y - 50);
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(NetworkUtilsTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // create a label to display the tip string
    _label = Label::createWithTTF("Touch the screen to check network status", "fonts/arial.ttf", 22);
    _label->setPosition(VisibleRect::center());
    addChild(_label, 0);
}

void NetworkUtilsTest::onTouchesEnded(const std::vector<Touch*>& touches, Event  *event)
{
    if (NetworkUtils::isNetworkConnected()) {
        _label->setString("Connected");
    } else {
        _label->setString("Disconnected");
    }
}

NetworkUtilsTest::~NetworkUtilsTest()
{
}

void NetworkUtilsTestScene::runThisTest()
{
    auto layer = new (std::nothrow) NetworkUtilsTest();
    addChild(layer);
    
    Director::getInstance()->replaceScene(this);
    layer->release();
}
