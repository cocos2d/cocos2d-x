#include "KeypadTest.h"

KeypadTest::KeypadTest()
{
    Size s = Director::getInstance()->getWinSize();
    LabelTTF* label = LabelTTF::create("Keypad Test", "Arial", 28);
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

void KeypadTest::keyBackClicked()
{
    _label->setString("BACK clicked!");
}

void KeypadTest::keyMenuClicked()
{
    _label->setString("MENU clicked!");
}

void KeypadTestScene::runThisTest()
{
    Layer* layer = new KeypadTest();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
    layer->release();
}
