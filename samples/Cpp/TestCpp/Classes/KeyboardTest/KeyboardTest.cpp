#include "KeyboardTest.h"

#ifdef CC_KEYBOARD_SUPPORT

KeyboardTest::KeyboardTest()
{
    Size s = Director::getInstance()->getWinSize();
    LabelTTF* label = LabelTTF::create("Keyboard Test", "Arial", 28);
    addChild(label, 0);
    label->setPosition( Point(s.width/2, s.height-50) );

    setKeyboardEnabled(true);

    // create a label to display the tip string
    _label = LabelTTF::create("Please press any key and see console log...", "Arial", 22);
    _label->setPosition(Point(s.width / 2, s.height / 2));
    addChild(_label, 0);
    
    _label->retain();
}

KeyboardTest::~KeyboardTest()
{
    _label->release();
}

void KeyboardTest::keyPressed(int keyCode)
{
    log("Key with keycode %d pressed", keyCode);
}

void KeyboardTest::keyReleased(int keyCode)
{
    log("Key with keycode %d released", keyCode);
}

void KeyboardTestScene::runThisTest()
{
    Layer* layer = new KeyboardTest();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
    layer->release();
}

#endif
