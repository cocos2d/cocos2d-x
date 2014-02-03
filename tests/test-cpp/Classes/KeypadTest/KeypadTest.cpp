#include "KeypadTest.h"

KeypadTest::KeypadTest()
{
    auto s = Director::getInstance()->getWinSize();
    auto label = LabelTTF::create("Keypad Test", "Arial", 28);
    addChild(label, 0);
    label->setPosition( Point(s.width/2, s.height-50) );

    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(KeypadTest::onKeyReleased, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // create a label to display the tip string
    _label = LabelTTF::create("Please press any key...", "Arial", 22);
    _label->setPosition(Point(s.width / 2, s.height / 2));
    addChild(_label, 0);
    
    _label->retain();
}

KeypadTest::~KeypadTest()
{
    _label->release();
}

void KeypadTest::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    if (keycode == EventKeyboard::KeyCode::KEY_BACKSPACE)
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
