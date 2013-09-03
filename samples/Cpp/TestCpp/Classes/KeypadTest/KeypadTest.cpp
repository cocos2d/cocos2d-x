#include "KeypadTest.h"

KeypadTest::KeypadTest()
{
    auto s = Director::getInstance()->getWinSize();
    auto label = LabelTTF::create("Keypad Test", "Arial", 28);
    addChild(label, 0);
    label->setPosition( Point(s.width/2, s.height-50) );

    setKeypadEnabled(true);

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

void KeypadTest::onKeyReleased(KeyboardEvent::KeyCode keycode, Event* event)
{
    if (keycode == KeyboardEvent::KeyCode::KEY_BACKSPACE)
    {
        _label->setString("BACK clicked!");
    }
    else if (keycode == KeyboardEvent::KeyCode::KEY_MENU)
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
