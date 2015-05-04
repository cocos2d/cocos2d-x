#include "OpenURLTest.h"

USING_NS_CC;

OpenURLTests::OpenURLTests()
{
    ADD_TEST_CASE(OpenURLTest);
}

OpenURLTest::OpenURLTest()
{
    auto label = Label::createWithTTF("Open URL Test", "fonts/arial.ttf", 28);
    addChild(label, 0);
    label->setPosition(VisibleRect::center().x, VisibleRect::top().y - 50);

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(OpenURLTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // create a label to display the tip string
    _label = Label::createWithTTF("Touch the screen to open\nthe cocos2d-x home page", "fonts/arial.ttf", 22);
    _label->setPosition(VisibleRect::center());
    addChild(_label, 0);

    _label->retain();
}

void OpenURLTest::onTouchesEnded(const std::vector<Touch*>& touches, Event  *event)
{
    Application::getInstance()->openURL("http://www.cocos2d-x.org/");
}

OpenURLTest::~OpenURLTest()
{
    _label->release();
}
