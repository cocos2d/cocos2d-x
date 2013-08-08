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
    
//    ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("cocosgui/UI_Register/UI_Register.json"));
    
    
    UIPanel * p = (UIPanel*)CCUIHELPER->createWidgetFromJsonFile("cocosgui/CocoGUISample.json");
//        UIPanel * p = (UIPanel*)CCUIHELPER->createWidgetFromJsonFile("cocosgui/test/5_3/5_3.ExportJson");
    ((UIScrollView*)p->getChildByName("scrollview"))->setInnerContainerSize(CCSizeMake(300, 275));
//    ((UIScrollView*)p->getChildByName("scrollview"))->setInnerContainerSize(CCSizeMake(300, 275));
//    ((UIScrollView*)p->getChildByName("scrollview"))->setLayoutType(UI_LAYOUT_LINEAR_VERTICAL);
    ((UIScrollView*)p->getChildByName("scrollview"))->addScrollToBottomEvent(this, coco_ScrollToBottomSelector(CocosGUITestScene::toCocosGUIExampleScene));
//    UILabel* tl = UILabel::create();
//    tl->setText("111");
//    tl->setPosition(ccp(100, 200));
//    ((UIScrollView*)p->getChildByName("scrollview"))->addChild(tl);
//    p->setLayoutType(UI_LAYOUT_LINEAR_HORIZONTAL);
    ul->addWidget(p);
//    UIButton* exitBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("exitbutton"));
//    exitBtn->addReleaseEvent(this, coco_releaseselector(CocosGUITestScene::toCocosGUIExampleScene));
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
    return;
    CCLOG("p2 click");
    ul->removeFromParent();
    
    CocosGUIExamplesScene* pScene = new CocosGUIExamplesScene();
    if (pScene)
    {
        pScene->runThisTest();
        pScene->release();
    }
}
