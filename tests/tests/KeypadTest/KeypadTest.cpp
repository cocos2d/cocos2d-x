#include "KeypadTest.h"

KeypadTest::KeypadTest()
: m_bShow(true)
{
	CGSize s = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* label = CCLabelTTF::labelWithString("Keypad Test", "Arial", 28);
	addChild(label, 0);
	label->setPosition( ccp(s.width/2, s.height-50) );

    CCLabelTTF* subtitle = CCLabelTTF::labelWithString("only goes well in cocos2d-uphone now!", "Arial", 18);
    addChild(subtitle, 0);
    subtitle->setPosition( ccp(s.width/2, s.height-100) );

    setIsKeypadEnabled(true);

    // create a label to display the tip string
    m_pLabel = CCLabelTTF::labelWithString("Key Back Clicked!", "Arial", 22);
    m_pLabel->setPosition(ccp(s.width / 2, s.height / 2));
	addChild(m_pLabel, 0);
    m_pLabel->setIsVisible(false);
    m_pLabel->retain();
}

KeypadTest::~KeypadTest()
{
	m_pLabel->release();
}

void KeypadTest::keyBackClicked()
{
    m_pLabel->setIsVisible(m_bShow);
    m_bShow = !m_bShow;
}

void KeypadTestScene::runThisTest()
{
    CCLayer* pLayer = new KeypadTest();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}
