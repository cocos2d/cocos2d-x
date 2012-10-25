#include "testBasic.h"
#include "controller.h"

TestScene::TestScene(bool bPortrait)
{
    
    CCScene::init();
}

void TestScene::onEnter()
{
    CCScene::onEnter();

    //add the menu item for back to main menu
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
//    CCLabelBMFont* label = CCLabelBMFont::create("MainMenu",  "fonts/arial16.fnt");
//#else
    CCLabelTTF* label = CCLabelTTF::create("MainMenu", "Arial", 20);
//#endif
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(TestScene::MainMenuCallback));

    CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);

    pMenu->setPosition( CCPointZero );
    pMenuItem->setPosition( ccp( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );

    addChild(pMenu, 1);
}

void TestScene::MainMenuCallback(CCObject* pSender)
{
    CCScene* pScene = CCScene::create();
    CCLayer* pLayer = new TestController();
    pLayer->autorelease();

    pScene->addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(pScene);
}
