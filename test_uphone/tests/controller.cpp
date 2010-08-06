#include "tests.h"
#include "controller.h"
#include "testBasic.h"
#include "touch_dispatcher/CCTouchDispatcher.h"

TestController::TestController()
{
    /**
    @todo 添加菜单点击后开始运行测试
    */
    
}

void TestController::onEnter()
{
    __super::onEnter();

    setIsTouchEnabled(true);
}

void TestController::registerWithTouchDispatcher()
{
    CCTouchDispatcher::getSharedDispatcher()->addTargetedDelegate(dynamic_cast<CCLayer*>(this), 0, true);
}

bool TestController::ccTouchBegan(CCTouch *pTouch, UIEvent *pEvent)
{
    // 运行ActionsTest
    TestScene* pScene = new ActionsTestScene();

    pScene->runThisTest();
    return true;
}

// CCScene* NextTest()
// {
// 
// }
// 
// CCScene* PreTest()
// {
// 
// }
// 
// CCScene* CurrentTest()
// {
// 
// }
