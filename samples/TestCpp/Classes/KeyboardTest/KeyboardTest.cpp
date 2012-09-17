#include "KeyboardTest.h"

KeyboardTest::KeyboardTest()
: m_bShow(true)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF* label = CCLabelTTF::create("Keyboard Test", "Arial", 28);
    addChild(label, 0);
    label->setPosition( ccp(s.width/2, s.height-50) );
    
    setKeypadEnabled(true);
    
    // create a label to display the tip string
    m_pLabel = CCLabelTTF::create("Please press any key...", "Arial", 22);
    m_pLabel->setPosition(ccp(s.width / 2, s.height / 2));
    addChild(m_pLabel, 0);
    
    m_pLabel->retain();
}

KeyboardTest::~KeyboardTest()
{
    m_pLabel->release();
}

#pragma mark CCLayer methods
void KeyboardTest::onEnterTransitionDidFinish() {
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCKeyboardDispatcher* dispatcher = pDirector->getKeyboardDispatcher();
    dispatcher->addDelegate(this, INT_MIN + 1);
    
    CCLayer::onEnterTransitionDidFinish();
}

void KeyboardTest::onExit() {
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCKeyboardDispatcher* dispatcher = pDirector->getKeyboardDispatcher();
    dispatcher->removeDelegate(this);
    
    CCLayer::onExit();
}

void KeyboardTest::keyUp(CCKeyboard* pKeyboard) {
    std::string msg = "KeyUp ";
    msg += "\"";
    msg += pKeyboard->getKeySequence();
    msg +=  "\" = ";

    std::ostringstream convert;
    convert << pKeyboard->getKey();
    msg += "[" + convert.str();
    msg += "]";
    
    if (pKeyboard->isAltKeyPressed())
        msg += " [Alt pressed]";
    if (pKeyboard->isCommandKeyPressed())
        msg += " [Cmd pressed]";
    if (pKeyboard->isControlKeyPressed())
        msg += " [Crtl pressed]";
    if (pKeyboard->isShiftKeyPressed())
        msg += " [Shift pressed]";
    
    m_pLabel->setString(msg.c_str());
}

void KeyboardTest::keyDown(CCKeyboard* pKeyboard)
{
    std::string msg = "KeyDown ";
    msg += "\"";
    msg += pKeyboard->getKeySequence();
    msg +=  "\" = ";
    
    std::ostringstream convert;
    convert << pKeyboard->getKey();
    msg += "[" + convert.str();
    msg += "]";
    
    if (pKeyboard->isAltKeyPressed())
        msg += " [Alt pressed]";
    if (pKeyboard->isCommandKeyPressed())
        msg += " [Cmd pressed]";
    if (pKeyboard->isControlKeyPressed())
        msg += " [Crtl pressed]";
    if (pKeyboard->isShiftKeyPressed())
        msg += " [Shift pressed]";
    
    m_pLabel->setString(msg.c_str());
}

void KeyboardTest::flagsChanged(CCKeyboard* pKeyboard)
{
    std::string msg = "";
    if (pKeyboard->isAltKeyPressed())
        msg += "[Alt pressed]";
    if (pKeyboard->isCommandKeyPressed())
        msg += "[Cmd pressed]";
    if (pKeyboard->isControlKeyPressed())
        msg += "[Crtl pressed]";
    if (pKeyboard->isShiftKeyPressed())
        msg += "[Shift pressed]";
    
    m_pLabel->setString(msg.c_str());
}

void KeyboardTestScene::runThisTest()
{
    CCLayer* pLayer = new KeyboardTest();
    addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}
