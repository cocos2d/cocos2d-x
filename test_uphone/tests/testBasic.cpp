#include "testBasic.h"
#include "controller.h"

BackToMainMenuLayer::BackToMainMenuLayer()
{
    //add the menu item for back to main menu

//     CCLabelAtlas* labelAtlas = CCLabelAtlas::labelAtlasWithString(L"0123456789", L"fonts/fps_images.png", 16, 24, L'.');
//     CCMenuItemLabel* item = CCMenuItemLabel::itemWithLabel(labelAtlas, this, menu_selector(BackToMainMenuLayer::MainMenuCallback) );
//     item->setDisabledColor( ccc3(32,32,64) );
//     item->setColor( ccc3(200,200,255) );

//     CCMenu *menu = CCMenu::menuWithItems(item, NULL);
//     CGSize s = CCDirector::getSharedDirector()->getWinSize();
//     menu->setPosition( CGPointZero );
//     item->setPosition( CGPointMake( s.width/2 - 100,30) );
// 
//     addChild(menu, 1);
}

// void BackToMainMenuLayer::MainMenuCallback(UxObject* pSender)
// {
//     CCScene* pScene = CCScene::node();
//     CCLayer* pLayer = new TestController();
//     pLayer->autorelease();
// 
//     pScene->addChild(pLayer);
//     CCDirector::getSharedDirector()->replaceScene(pScene);
// }

TestScene::TestScene()
{
    CCLayer* pLayer = new BackToMainMenuLayer();
    pLayer->autorelease();
    pLayer->retain();

    addChild(pLayer);
}
