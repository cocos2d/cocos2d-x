#include "CocosGUIScene.h"
#include "CocosGUISlotScene.h"
//#include "CCScale9Sprite.h"


CocosGUITestScene::CocosGUITestScene(bool bPortrait)
{
	TestScene::init();
    
	CCSprite *bg = CCSprite::create("armature/bg.jpg");
	bg->setPosition(VisibleRect::center());
    
	float scaleX = VisibleRect::getVisibleRect().size.width / bg->getContentSize().width;
	float scaleY = VisibleRect::getVisibleRect().size.height / bg->getContentSize().height;
    
	bg->setScaleX(scaleX);
	bg->setScaleY(scaleY);
    
	addChild(bg);
}
void CocosGUITestScene::runThisTest()
{
    
	CCDirector::sharedDirector()->replaceScene(this);
    
    ul = UILayer::create();
    ul->scheduleUpdate();
    this->addChild(ul);
    
    /*
    CCSprite* spP = CCSprite::create("army_1.png");
    CCSprite* spS = CCSprite::create("army_1.png");
    spS->setPosition(ccp(0, 0));
    
    spP->addChild(spS);
    
    spP->setPosition(ccp(100, 100));
    
    ul->addChild(spP);
    
    CocoImageView* ivP = CocoImageView::create();
    ivP->setTexture("army_1.png");
    CocoImageView* ivS = CocoImageView::create();
    ivS->setTexture("army_1.png");
    ivS->setPosition(ccp(0+(-(ivP->getRelativeRect().size.width/2.0f)), 0+(-(ivP->getRelativeRect().size.height/2.0f))));
    
    ivP->addChild(ivS);
    
    ul->addWidget(ivP);
    ivP->setPosition(ccp(300, 100));
     */
    
    
    /*
    CCScale9Sprite* sp9 = CCScale9Sprite::create("army_1.png");
    
    ul->addChild(sp9);
    
    
    CocoImageView* iv9 = CocoImageView::create();
    iv9->setTexture("army_1.png");
    
    iv9->setScale9Enable(true);
    
    ul->addWidget(iv9);
    iv9->setPosition(ccp(300, 100));
    sp9->setPosition(ccp(100, 100));
    
    
    iv9->setAnchorPoint(ccp(0, 0));
    sp9->setAnchorPoint(ccp(0, 0));
     */
    

//    ul->addWidget(CCUIHELPER->createWidgetFromFile_ccb("ccb_parse/Tests/TestSprites.ccb"));
//    ul->addWidget(CCUIHELPER->createWidgetFromFile_ccb("ccb_parse/HelloCocosBuilder.ccb"));

//    /*
    ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("cocosgui/CocoGUISample.json"));
    UIScrollView* sc = (UIScrollView*)(ul->getWidgetByName("scrollview"));
    sc->setUpdateEnable(true);
    sc->setMoveMode(SCROLLVIEW_MOVE_MODE_NORMAL);
//
//    UIImageView* image = dynamic_cast<UIImageView*>(ul->getWidgetByName("imageview"));
//    image->setBeTouchEnable(true);
////    image->addReleaseEvent(this, coco_releaseselector(CocosGUITestScene::MainMenuCallback));
//    
    UIButton* exitBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("exitbutton"));
    exitBtn->addReleaseEvent(this, coco_releaseselector(CocosGUITestScene::toCocosGUISlotScene));
////     */
//    
//    UICheckBox* cb = dynamic_cast<UICheckBox*>(ul->getWidgetByName("checkbox"));
//    cb->addSelectEvent(this, coco_releaseselector(CocosGUITestScene::MainMenuCallback));
//    
//    UIPanel* pn = UIPanel::create();
//    ul->addWidget(pn);
//    pn->setBackGroundColorEnable(true);
//    pn->setColor(ccc3(0, 255, 0));
//    pn->setOpacity(255);
//    pn->setSize(CCSizeMake(100, 100));
//    pn->setPosition(ccp(100, 100));
//    
//    UIButton* btn = UIButton::create();
//    btn->setTextures("slot/2.png", NULL, NULL);
//    pn->addChild(btn);
    
//    ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("cocosgui/test/NewProject_1_1.json"));
////    UIWidget* pv = UIPageView::create();
//    UIPageView* pv = UIPageView::create();
//    pv->addPage(NULL);
//    pv->addWidgetToPage(NULL, 0, false);
}
void CocosGUITestScene::MainMenuCallback(CCObject* pSender)
{
	TestScene::MainMenuCallback(pSender);
//    UIActionManager::shareManager()->PlayActionByName("Animation1");
}

void CocosGUITestScene::toCocosGUISlotScene(CCObject* pSender)
{    
    CocosGUISlotScene *pScene = new CocosGUISlotScene();
    if (pScene)
    {
        ul->clear();
        
        pScene->runThisTest();
        pScene->release();
    }
}