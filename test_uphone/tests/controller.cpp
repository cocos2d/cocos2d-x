#include "tests.h"
#include "controller.h"
#include "CCMenu.h"
#include "CCLabel.h"
#include "touch_dispatcher/CCTouchDispatcher.h"

TestController::TestController()
{
    /**
    @todo add menu items for all tests
    */
    CCLabel* label = CCLabel::labelWithString("ActionsTest", "Arial", 22);
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::itemWithLabel(label, this, menu_selector(TestController::menuCallback));

    

    // add close menu
    CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage("/NEWPLUS/TDA_DATA/Data/cocos2d_tests/Images/close.png",
                                                                       "/NEWPLUS/TDA_DATA/Data/cocos2d_tests/Images/close.png",
                                                                       this, menu_selector(TestController::closeCallback) );

    CCMenu* pMenu =CCMenu::menuWithItems(pMenuItem, pCloseItem, NULL);
    CGSize s = CCDirector::getSharedDirector()->getWinSize();
    pMenu->setPosition( CGPointZero );
    pMenuItem->setPosition( CGPointMake( s.width / 2, s.height / 2) );
    pCloseItem->setPosition(CGPointMake( s.width - 30, s.height - 30));

    addChild(pMenu, 1);
}

void TestController::menuCallback(NSObject * pSender)
{
    TestScene* pScene = new ActionsTestScene();

    pScene->runThisTest();
}

void TestController::closeCallback(NSObject * pSender)
{
    TApplication * pApp = TApplication::GetCurrentApplication();

    CCDirector::getSharedDirector()->end();
    pApp->SendStopEvent();
}
