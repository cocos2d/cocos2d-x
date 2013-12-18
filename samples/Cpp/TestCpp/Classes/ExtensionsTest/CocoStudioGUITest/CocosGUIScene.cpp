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
//    
////    Layout* l = Layout::create();
////    l->setSize(Size(100, 100));
////    l->setBackGroundColor(Color3B::GREEN);
//////    l->setBackGroundColorType(LAYOUT_COLOR_SOLID);
////    l->setLayoutType(LAYOUT_LINEAR_HORIZONTAL);
////    addChild(l);
////    l->setBackGroundImage("cocosgui/animationbuttonnormal.png");
////    l->setBackGroundImageScale9Enabled(true);
////    
////    
////    ImageView* iv = ImageView::create();
////    iv->loadTexture("cocosgui/animationbuttonnormal.png");
////    iv->setPosition(Point(100, 100));
////    iv->setScale9Enabled(true);
////    iv->setSize(Size(80, 80));
//////    l->addChild(iv);
////    addChild(iv);
//    
////    LayerColor* lc = LayerColor::create();
////    lc->setColor(Color3B::GREEN);
////    lc->setOpacity(255);
////    lc->setContentSize(Size(50, 50));
////    addChild(lc);
////
//////    Scale9Sprite* sp9 = Scale9Sprite::create("cocosgui/animationbuttonnormal.png");
//////    sp9->setPreferredSize(Size(100, 100));
//////    addChild(sp9);
//////    sp9->setPosition(Point(50, 50));
////    
////    Sprite* sp = Sprite::create("cocosgui/animationbuttonnormal.png");
////    addChild(sp);
//
//    DrawNode
//    ClippingNode* cn = ClippingNode::create();
    
    
}
void CocosGUITestScene::MainMenuCallback(Object* pSender)
{
    ExtensionsTestScene *pScene = new ExtensionsTestScene();
	pScene->runThisTest();
	pScene->release();    
}

void CocosGUITestScene::toCocosGUIExampleScene(Object* sender)
{
    auto scrollView = static_cast<cocos2d::gui::ScrollView*>(sender);
    scrollView->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
    scrollView->getChildByName("backtotopbutton")->setBright(false);
    scrollView->getChildByName("backtotopbutton")->setTouchEnabled(false);
    CCLOG("p2 click");    
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
