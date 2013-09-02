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
	cocos2d::extension::CCSSceneReader::purgeSceneReader();
	cocos2d::extension::UIActionManager::purgeUIActionManager();
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
    for (int i = 0; i < 2; ++i)
    {
        CCMenuItemFont* pItem = CCMenuItemFont::create(gui_scene_names[i], this,
                                                       menu_selector(CocosGUITestScene::menuCallback));
        pItem->setPosition(ccp(s.width / 2, s.height - s.height / 4 - (i + 1) * 40));
        pItem->setTag(i);
        m_pItemMenu->addChild(pItem);
    }
    addChild(m_pItemMenu);
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
    
    UIWidget* widget = dynamic_cast<UIWidget*>(pSender);
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
