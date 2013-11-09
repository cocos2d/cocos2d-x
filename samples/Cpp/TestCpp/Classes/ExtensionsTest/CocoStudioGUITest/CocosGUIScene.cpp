#include "CocosGUIScene.h"
#include "UISceneManager.h"
#include "../ExtensionsTest.h"
#include "cocostudio/CocoStudio.h"

const char* gui_scene_names[2] =
{
    "CocosGUIWidgetTest",
    "CocosGUIExampleTest",
};

CocosGUITestScene::CocosGUITestScene(bool bPortrait)
: _label(NULL)
{
	TestScene::init();
}

CocosGUITestScene::~CocosGUITestScene()
{
	cocostudio::SceneReader::getInstance()->purgeSceneReader();
	cocostudio::ActionManagerEx::purgeActionManager();
}

void CocosGUITestScene::runThisTest()
{
    
	Director::getInstance()->replaceScene(this);

    Size s = CCDirector::getInstance()->getWinSize();
    
    _itemMenu = CCMenu::create();
    _itemMenu->setPosition(Point::ZERO);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(24);
    for (int i = 0; i < 1; ++i)
    {
        auto item = MenuItemFont::create(
                                         gui_scene_names[i],
                                         CC_CALLBACK_1( CocosGUITestScene::menuCallback, this));
        item->setPosition(Point(s.width / 2, s.height - s.height / 4 - (i + 1) * 40));
        item->setTag(i);
        _itemMenu->addChild(item);
    }
    addChild(_itemMenu);
//     */
}
void CocosGUITestScene::MainMenuCallback(Object* pSender)
{
    ExtensionsTestScene *pScene = new ExtensionsTestScene();
	pScene->runThisTest();
	pScene->release();    
}

void CocosGUITestScene::toCocosGUIExampleScene(Object* sender)
{
    auto scrollView = static_cast<UIScrollView*>(sender);
    scrollView->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
    scrollView->getChildByName("backtotopbutton")->setBright(false);
    scrollView->getChildByName("backtotopbutton")->setTouchEnabled(false);
    CCLOG("p2 click");
    ul->removeFromParent();
    
}

void CocosGUITestScene::load(Object *pSender, int count)
{
    char tmp[10];
    sprintf(tmp,"%d", count);
    _label->setString(CCString::createWithFormat("%i", count)->getCString());
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
