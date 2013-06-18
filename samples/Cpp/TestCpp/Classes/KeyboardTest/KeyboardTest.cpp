#include "KeyboardTest.h"

#ifdef KEYBOARD_SUPPORT

KeyboardTest::KeyboardTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF* label = CCLabelTTF::create("Keyboard Test", "Arial", 28);
    addChild(label, 0);
    label->setPosition( ccp(s.width/2, s.height-50) );

    setKeyboardEnabled(true);

    // create a label to display the tip string
    _label = CCLabelTTF::create("Please press any key and see console log...", "Arial", 22);
    _label->setPosition(ccp(s.width / 2, s.height / 2));
    addChild(_label, 0);
    
    _label->retain();
}

KeyboardTest::~KeyboardTest()
{
    _label->release();
}

void KeyboardTest::keyPressed(int keyCode)
{
    CCLog("Key with keycode %d pressed", keyCode);
}

void KeyboardTest::keyReleased(int keyCode)
{
    CCLog("Key with keycode %d released", keyCode);
}

void KeyboardTestScene::runThisTest()
{
    CCLayer* pLayer = new KeyboardTest();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}

#endif
