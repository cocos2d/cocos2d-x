#include "KeyboardTest.h"

KeyboardTest::KeyboardTest()
{
    auto s = Director::getInstance()->getWinSize();
    auto label = Label::createWithTTF("Keyboard Test", "fonts/arial.ttf", 28);
    addChild(label, 0);
    label->setPosition( Point(s.width/2, s.height-50) );

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(KeyboardTest::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(KeyboardTest::onKeyReleased, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // create a label to display the tip string
    _label = Label::createWithTTF("Please press any key and see console log...", "fonts/arial.ttf", 22);
    _label->setPosition(Point(s.width / 2, s.height / 2));
    addChild(_label, 0);
    
    _label->retain();
}

KeyboardTest::~KeyboardTest()
{
    _label->release();
}

void KeyboardTest::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d pressed", keyCode);
}

void KeyboardTest::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d released", keyCode);
}

void KeyboardTestScene::runThisTest()
{
    auto layer = new KeyboardTest();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
    layer->release();
}

