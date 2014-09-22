#include "UITest.h"
#include "CocoStudioGUITest/CocoStudioGUITest.h"

void UITestScene::runThisTest()
{
    CocoStudioGUITestScene* pScene = new (std::nothrow) CocoStudioGUITestScene();
    pScene->runThisTest();
}
