#include "CocosGUIScene.h"
#include "CocosGUIExamplesScene.h"


CocosGUITestScene::CocosGUITestScene(bool bPortrait)
{
	TestScene::init();
}

CocosGUITestScene::~CocosGUITestScene()
{
	cocos2d::extension::CCJsonReader::purgeJsonReader();
	cocos2d::extension::UIActionManager::purgeUIActionManager();
	cocos2d::extension::UIHelper::purgeUIHelper();
}

void CocosGUITestScene::runThisTest()
{
    
	CCDirector::sharedDirector()->replaceScene(this);
    
    ul = UILayer::create();
    ul->scheduleUpdate();
    this->addChild(ul);
    
    UIPanel * p = (UIPanel*)CCUIHELPER->createWidgetFromJsonFile("cocosgui/1_2/1_2.json");
    ul->addWidget(p);
    
//    UIPanel * p = (UIPanel*)CCUIHELPER->createWidgetFromJsonFile("cocosgui/CocoGUISample.json");
//    ((UIScrollView*)p->getChildByName("scrollview"))->setInnerContainerSize(CCSizeMake(300, 275));
//    ((UIScrollView*)p->getChildByName("scrollview"))->addScrollToBottomEvent(this, coco_ScrollToBottomSelector(CocosGUITestScene::toCocosGUIExampleScene));
//    ul->addWidget(p);
}
void CocosGUITestScene::MainMenuCallback(CCObject* pSender)
{
    ul->removeFromParent();
    TestScene::MainMenuCallback(pSender);
}

void CocosGUITestScene::toCocosGUIExampleScene(CCObject* pSender)
{
    ((UIScrollView*)pSender)->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
    ((UIScrollView*)pSender)->getChildByName("backtotopbutton")->disable();
    CCLOG("p2 click");
    ul->removeFromParent();
    
    CocosGUIExamplesScene* pScene = new CocosGUIExamplesScene();
    if (pScene)
    {
        pScene->runThisTest();
        pScene->release();
    }
}
