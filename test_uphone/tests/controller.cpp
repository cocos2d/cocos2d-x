#include "tests.h"
#include "controller.h"
#include "CCMenu.h"
#include "CCBitmapFontAtlas.h"
#include "touch_dispatcher/CCTouchDispatcher.h"

TestController::TestController()
{
    /**
    @todo add menu items for all tests
    */
    CCBitmapFontAtlas* label = CCBitmapFontAtlas::bitmapFontAtlasWithString("ActionsTest", "/NEWPLUS/TDA_DATA/Data/cocos2d_tests/Images/bitmapFontTest3.fnt");
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
