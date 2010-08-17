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

    CCMenu* pMenu =CCMenu::menuWithItems(pMenuItem, NULL);
    CGSize s = CCDirector::getSharedDirector()->getWinSize();
    pMenu->setPosition( CGPointZero );
    pMenuItem->setPosition( CGPointMake( s.width / 2, s.height / 2) );

    addChild(pMenu, 1);
}

void TestController::menuCallback(NSObject * pSender)
{
    TestScene* pScene = new ActionsTestScene();

    pScene->runThisTest();
}
