#include "testBasic.h"
#include "controller.h"

TestScene::TestScene(bool bPortrait)
:m_bPortrait(bPortrait)
{
    if (m_bPortrait)
    {
        CCDirector::sharedDirector()->setDeviceOrientation(CCDeviceOrientationLandscapeRight);
    }
    
    CCScene::init();
}

void TestScene::onEnter()
{
    CCScene::onEnter();

    //add the menu item for back to main menu
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
//    CCLabelBMFont* label = CCLabelBMFont::labelWithString("MainMenu",  "fonts/arial16.fnt");
//#else
    CCLabelTTF* label = CCLabelTTF::labelWithString("MainMenu", "Arial", 20);
//#endif
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::itemWithLabel(label, this, menu_selector(TestScene::MainMenuCallback));

    CCMenu* pMenu =CCMenu::menuWithItems(pMenuItem, NULL);
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    pMenu->setPosition( CCPointZero );
    pMenuItem->setPosition( CCPointMake( s.width - 50, 25) );

    addChild(pMenu, 1);
}

void TestScene::MainMenuCallback(CCObject* pSender)
{
    CCScene* pScene = CCScene::node();
    CCLayer* pLayer = new TestController();
    pLayer->autorelease();

    pScene->addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(pScene);
}
