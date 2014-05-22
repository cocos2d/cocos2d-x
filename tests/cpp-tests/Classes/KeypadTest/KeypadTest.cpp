#include "KeypadTest.h"

KeypadTest::KeypadTest()
{
    auto s = Director::getInstance()->getWinSize();
    auto label = Label::createWithTTF("Keypad Test", "fonts/arial.ttf", 28);
    addChild(label, 0);
    label->setPosition( Vec2(s.width/2, s.height-50) );

    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(KeypadTest::onKeyReleased, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // create a label to display the tip string
    _label = Label::createWithTTF("Please press any key...", "fonts/arial.ttf", 22);
    _label->setPosition(Vec2(s.width / 2, s.height / 2));
    addChild(_label, 0);
    
    _label->retain();
}

KeypadTest::~KeypadTest()
{
    _label->release();
}

void KeypadTest::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        _label->setString("BACK clicked!");
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_MENU)
    {
        _label->setString("MENU clicked!");
    }
}

void KeypadTestScene::runThisTest()
{
    auto layer = new KeypadTest();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
    layer->release();
}
