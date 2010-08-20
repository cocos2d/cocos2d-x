#include "testBasic.h"
#include "controller.h"
#include "CCMenu.h"
#include "CCLabel.h"
#include "CCDirector.h"

BackToMainMenuLayer::BackToMainMenuLayer()
{
    //add the menu item for back to main menu
    CCLabel* label = CCLabel::labelWithString("MainMenu", "Arial", 20);
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::itemWithLabel(label, this, menu_selector(BackToMainMenuLayer::MainMenuCallback));

    CCMenu* pMenu =CCMenu::menuWithItems(pMenuItem, NULL);
    CGSize s = CCDirector::getSharedDirector()->getWinSize();
    pMenu->setPosition( CGPointZero );
    pMenuItem->setPosition( CGPointMake( s.width - 50, 25) );

    addChild(pMenu, 1);
}

void BackToMainMenuLayer::MainMenuCallback(NSObject* pSender)
{
    CCScene* pScene = CCScene::node();
    CCLayer* pLayer = new TestController();
    pLayer->autorelease();

    pScene->addChild(pLayer);
    CCDirector::getSharedDirector()->replaceScene(pScene);
}

TestScene::TestScene()
{
    __super::init();
    CCLayer* pLayer = new BackToMainMenuLayer();
    pLayer->autorelease();

    addChild(pLayer);
}
