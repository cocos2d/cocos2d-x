#include "MouseTest.h"

MouseTest::MouseTest()
{
    auto s = Director::getInstance()->getWinSize();
    auto title = Label::createWithTTF("Mouse Test", "fonts/arial.ttf", 28);
    addChild(title, 0);
    title->setPosition( Point(s.width/2, s.height-50) );

    //Create a label to display the mouse action
    _labelAction = Label::createWithTTF("Click mouse button and see this change", "fonts/arial.ttf", 22);
    _labelAction->setPosition(Point(s.width/2, s.height*2/3));
    addChild(_labelAction, 0);

    //Create a label to display the mouse position
    _labelPosition = Label::createWithTTF("Mouse not supported on this device", "fonts/arial.ttf", 22);
    _labelPosition->setPosition(Point(s.width/2, s.height/3));
    addChild(_labelPosition);


    _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseMove = CC_CALLBACK_1(MouseTest::onMouseMove, this);
    _mouseListener->onMouseUp = CC_CALLBACK_1(MouseTest::onMouseUp, this);
    _mouseListener->onMouseDown = CC_CALLBACK_1(MouseTest::onMouseDown, this);
    _mouseListener->onMouseScroll = CC_CALLBACK_1(MouseTest::onMouseScroll, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

    _labelAction->retain();
    _labelPosition->retain();
}

MouseTest::~MouseTest()
{
    _eventDispatcher->removeEventListener(_mouseListener);

    _labelAction->release();
    _labelPosition->release();
}

template <typename T> std::string tostr(const T& t) { std::ostringstream os; os<<t; return os.str(); }

void MouseTest::onMouseDown(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Down detected, Key: ";
    str += tostr(e->getMouseButton());
    _labelAction->setString(str.c_str());
}

void MouseTest::onMouseUp(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Up detected, Key: ";
    str += tostr(e->getMouseButton());
    _labelAction->setString(str.c_str());
}

void MouseTest::onMouseMove(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "MousePosition X:";
    str = str + tostr(e->getCursorX()) + " Y:" + tostr(e->getCursorY());
    _labelPosition->setString(str.c_str());
}

void MouseTest::onMouseScroll(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Scroll detected, X: ";
    str = str + tostr(e->getScrollX()) + " Y: " + tostr(e->getScrollY());
    _labelAction->setString(str.c_str());
}

void MouseTestScene::runThisTest()
{
    auto layer = new MouseTest();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
    layer->release();
}