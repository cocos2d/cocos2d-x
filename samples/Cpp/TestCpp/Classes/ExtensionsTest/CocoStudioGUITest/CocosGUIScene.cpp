#include "CocosGUIScene.h"
#include "UISceneManager.h"
//#include "CocosGUIExamplesRegisterScene.h"
#include "ExtensionsTest.h"

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
	cocos2d::extension::SceneReader::getInstance()->purgeSceneReader();
	cocos2d::extension::UIActionManager::purgeUIActionManager();
	cocos2d::extension::UIHelper::purgeUIHelper();
}

void CocosGUITestScene::runThisTest()
{
    
	Director::getInstance()->replaceScene(this);
    
    ul = UILayer::create();
    ul->scheduleUpdate();
    this->addChild(ul);
    
    /*
    Layout* layout = static_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("cocosgui/UI/UI01.json"));
    ul->addWidget(layout);
     */
    
//    /*
    Size s = CCDirector::getInstance()->getWinSize();
    
    m_pItemMenu = CCMenu::create();
    m_pItemMenu->setPosition(Point::ZERO);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(24);
    for (int i = 0; i < 1; ++i)
    {
        MenuItemFont* pItem = MenuItemFont::create(gui_scene_names[i], this,
                                                   menu_selector(CocosGUITestScene::menuCallback));
        pItem->setPosition(Point(s.width / 2, s.height - s.height / 4 - (i + 1) * 40));
        pItem->setTag(i);
        m_pItemMenu->addChild(pItem);
    }
    addChild(m_pItemMenu);
//     */
}
void CocosGUITestScene::MainMenuCallback(Object* pSender)
{
    ul->removeFromParent();
    ExtensionsTestScene *pScene = new ExtensionsTestScene();
	pScene->runThisTest();
	pScene->release();    
}

void CocosGUITestScene::toCocosGUIExampleScene(Object* pSender)
{
    ((UIScrollView*)pSender)->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
    ((UIScrollView*)pSender)->getChildByName("backtotopbutton")->setBright(false);
    ((UIScrollView*)pSender)->getChildByName("backtotopbutton")->setTouchEnabled(false);
    CCLOG("p2 click");
    ul->removeFromParent();
    
}

void CocosGUITestScene::load(Object *pSender, int count)
{
    char tmp[10];
    sprintf(tmp,"%d", count);
    m_pLabel->setString(CCString::createWithFormat("%i", count)->getCString());
}

void CocosGUITestScene::menuCallback(Object *pSender)
{
    MenuItemFont* pItem = dynamic_cast<MenuItemFont*>(pSender);
    
    switch (pItem->getTag())
    {
        case 0:
        {
            UISceneManager* pManager = UISceneManager::sharedUISceneManager();
            Scene* pScene = pManager->currentUIScene();
            CCDirector::getInstance()->replaceScene(pScene);
        }
            break;
            
            /*
        case 1:
        {
            CocosGUIExamplesRegisterScene* pScene = new CocosGUIExamplesRegisterScene();
            pScene->runThisTest();
            pScene->release();
        }
             */
            break;
            
        default:
            break;
    }
}
