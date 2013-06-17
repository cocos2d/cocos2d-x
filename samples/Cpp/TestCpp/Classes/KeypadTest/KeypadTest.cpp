#include "KeypadTest.h"

KeypadTest::KeypadTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF* label = CCLabelTTF::create("Keypad Test", "Arial", 28);
    addChild(label, 0);
    label->setPosition( ccp(s.width/2, s.height-50) );

    setKeypadEnabled(true);

    // create a label to display the tip string
    _label = CCLabelTTF::create("Please press any key...", "Arial", 22);
    _label->setPosition(ccp(s.width / 2, s.height / 2));
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
    CCLayer* pLayer = new KeypadTest();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}
