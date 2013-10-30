#include "CocosGUIScene.h"
#include "CocosGUIExamplesScene.h"
#include "UISceneManager.h"
#include "CocosGUIExamplesRegisterScene.h"

const char* gui_scene_names[2] =
{
    "CocosGUIWidgetTest",
    "CocosGUIExampleTest",
};

CocosGUITestScene::CocosGUITestScene(bool bPortrait)
: m_pLabel(NULL)
{
	TestScene::init();
}

CocosGUITestScene::~CocosGUITestScene()
{
	cocos2d::extension::CCSSceneReader::sharedSceneReader()->purgeSceneReader();
	cocos2d::extension::ActionManager::purgeActionManager();
	cocos2d::extension::UIHelper::purgeUIHelper();
}

void CocosGUITestScene::runThisTest()
{
    
	CCDirector::sharedDirector()->replaceScene(this);
    
    ul = UILayer::create();
    ul->scheduleUpdate();
    this->addChild(ul);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    m_pItemMenu = CCMenu::create();
    m_pItemMenu->setPosition( CCPointZero );
    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(24);
    for (int i = 0; i < 1; ++i)
    {
        CCMenuItemFont* pItem = CCMenuItemFont::create(gui_scene_names[i], this,
                                                       menu_selector(CocosGUITestScene::menuCallback));
        pItem->setPosition(ccp(s.width / 2, s.height - s.height / 4 - (i + 1) * 40));
        pItem->setTag(i);
        m_pItemMenu->addChild(pItem);
    }
    addChild(m_pItemMenu);
    
    UIScrollView* sc = UIScrollView::create();
    sc->setBounceEnabled(true);
    sc->setDirection(SCROLLVIEW_DIR_BOTH);
    sc->setSize(CCSizeMake(200, 200));
    ul->addWidget(sc);
    sc->setPosition(ccp((480-200)/2, (320-200)/2));
    sc->setBackGroundColor(ccGREEN);
    sc->setBackGroundColorType(LAYOUT_COLOR_SOLID);
    sc->setInnerContainerSize(CCSizeMake(480, 320));
    
    UIImageView* iv = UIImageView::create();
    iv->loadTexture("Hello.png");
    iv->setTouchEnabled(true);
    sc->addChild(iv);
    iv->setPositionPercent(ccp(0.5, 0.5));
//
//    l = UIListViewEx::create();
////    l->setInertiaScrollEnabled(false);
////    l->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
//    l->setBackGroundColor(ccGREEN);
//    l->setBackGroundColorType(LAYOUT_COLOR_SOLID);
//    l->setItemModel(iv);
//    l->setSize(CCSizeMake(100, 200));
//    l->setPosition(ccp(100, 100));
//    l->setItemsMargin(20);
//    for (int i=0; i<50; i++)
//    {
//        l->pushBackDefaultItem();
//    }
//    for (int i=0; i<50; i++)
//    {
//        char buf[8] = {0};
//        sprintf(buf,"%d", i);
//        ((UIButton*)l->getItemByIndex(i))->setTitleText(buf);
//    }
//    l->setGravity(LISTVIEW_GRAVITY_CENTER_HORIZONTAL);
//    l->setBounceEnabled(true);
//    ul->addWidget(l);
////
//    UIButton* btnT = UIButton::create();
//    btnT->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", NULL);
//    btnT->setPosition(ccp(280, 170));
//    btnT->setTitleText("top");
//    btnT->setTouchEnabled(true);
//    btnT->addTouchEventListener(this, toucheventselector(CocosGUITestScene::toTop));
//    ul->addWidget(btnT);
//    
//    UIButton* btnB = (UIButton*)(btnT->clone());
//    btnB->setTitleText("bottom");
//    btnB->addTouchEventListener(this, toucheventselector(CocosGUITestScene::toBottom));
//    ul->addWidget(btnB);
//    btnB->setPosition(ccp(280, 100));
//    
////    UIImageView* iv = UIImageView::create();
////    iv->loadTexture("Hello.png");
////    iv->setPositionType(POSITION_PERCENT);
////    iv->setPositionPercent(ccp(0.5, 0.5));
////
////    sc = UIScrollView::create();
////    sc->setBounceEnabled(true);
////    sc->setDirection(SCROLLVIEW_DIR_BOTH);
////    sc->setInnerContainerSize(CCSizeMake(480, 320));
////    sc->setPosition(ccp(100, 100));
////    sc->setSize(CCSizeMake(100, 100));
////    sc->setBackGroundColorType(LAYOUT_COLOR_SOLID);
////    sc->setBackGroundColor(ccGREEN);
////    sc->addChild(iv);
////    ul->addWidget(sc);
//    int aaa = l->getItems()->data->num;
//    UIWidget* lc = l->clone();
//    lc->setPosition(ccp(250, 100));
//    ul->addWidget(lc);
}

void CocosGUITestScene::toTop(cocos2d::CCObject *sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        l->scrollToPercentBothDirection(ccp(50, 50), 1, true);
    }
}

void CocosGUITestScene::toBottom(cocos2d::CCObject *sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        l->scrollToPercentVertical(98, 1, false);
    }
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
}

void CocosGUITestScene::load(CCObject *pSender, int count)
{
    char tmp[10];
    sprintf(tmp,"%d", count);
    m_pLabel->setString(CCString::createWithFormat("%i", count)->getCString());
}

void CocosGUITestScene::menuCallback(CCObject *pSender)
{
    CCMenuItemFont* pItem = dynamic_cast<CCMenuItemFont*>(pSender);
    
    switch (pItem->getTag())
    {
        case 0:
        {
            UISceneManager* pManager = UISceneManager::sharedUISceneManager();
            CCScene* pScene = pManager->currentUIScene();
            CCDirector::sharedDirector()->replaceScene(pScene);
        }
            break;
            
        case 1:
        {
            CocosGUIExamplesRegisterScene* pScene = new CocosGUIExamplesRegisterScene();
            pScene->runThisTest();
            pScene->release();
        }
            break;
            
        default:
            break;
    }
}
