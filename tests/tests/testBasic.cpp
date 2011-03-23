#include "testBasic.h"
#include "controller.h"

BackToMainMenuLayer::BackToMainMenuLayer()
{
    //add the menu item for back to main menu
#if (CC_TARGET_PLATFORM == CC_PLATFORM_AIRPLAY)
	CCLabelBMFont* label = CCLabelBMFont::bitmapFontAtlasWithString("MainMenu",  "fonts/arial16.fnt");
#else
    CCLabelTTF* label = CCLabelTTF::labelWithString("MainMenu", "Arial", 20);
#endif
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::itemWithLabel(label, this, menu_selector(BackToMainMenuLayer::MainMenuCallback));

    CCMenu* pMenu =CCMenu::menuWithItems(pMenuItem, NULL);
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    pMenu->setPosition( CCPointZero );
    pMenuItem->setPosition( CCPointMake( s.width - 50, 25) );

    addChild(pMenu, 1);
}

void BackToMainMenuLayer::MainMenuCallback(CCObject* pSender)
{
    CCScene* pScene = CCScene::node();
    CCLayer* pLayer = new TestController();
    pLayer->autorelease();

    pScene->addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

TestScene::TestScene()
{
    CCScene::init();
    CCLayer* pLayer = new BackToMainMenuLayer();
    pLayer->autorelease();

    // 54321 is the tag of BackToMainMenuLayer
    addChild(pLayer, 1000, 54321);
}
