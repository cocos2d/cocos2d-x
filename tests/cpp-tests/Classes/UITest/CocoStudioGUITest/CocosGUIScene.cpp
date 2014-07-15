#include "CocosGUIScene.h"
#include "CocoStudioGUITest.h"
#include "UISceneManager.h"
#include "cocostudio/CocoStudio.h"

enum
{
    LINE_SPACE = 40,
    kItemTagBasic = 1000,
};

static struct
{
	const char *name;
	std::function<void(Ref* sender)> callback;
}
g_guisTests[] =
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    {
        "VideoPlayerTest",
        [](Ref* sender)
        {
            UISceneManager* sceneManager = UISceneManager::sharedUISceneManager();
            sceneManager->setCurrentUISceneId(kUIVideoPlayerTest);
            sceneManager->setMinUISceneId(kUIVideoPlayerTest);
            sceneManager->setMaxUISceneId(kUIVideoPlayerTest);
            Scene* scene = sceneManager->currentUIScene();
            Director::getInstance()->replaceScene(scene);
        }
    },
#endif
    {
        "focus test",
        [](Ref* sender)
        {
            UISceneManager* sceneManager = UISceneManager::sharedUISceneManager();
            sceneManager->setCurrentUISceneId(KUIFocusTest_HBox);
            sceneManager->setMinUISceneId(KUIFocusTest_HBox);
            //TODO: improve ListView focus
            sceneManager->setMaxUISceneId(KUIFocusTest_NestedLayout3);
            Scene* scene = sceneManager->currentUIScene();
            Director::getInstance()->replaceScene(scene);
        }
    },
	{
        
        "ButtonTest",
        [](Ref* sender)
        {
            UISceneManager* sceneManager = UISceneManager::sharedUISceneManager();
            sceneManager->setCurrentUISceneId(kUIButtonTest);
            sceneManager->setMinUISceneId(kUIButtonTest);
            sceneManager->setMaxUISceneId(kUIButtonTest_Title);
            Scene* scene = sceneManager->currentUIScene();
            Director::getInstance()->replaceScene(scene);
        }
	},
    {
        "CheckBoxTest",
        [](Ref* sender)
        {
            UISceneManager* sceneManager = UISceneManager::sharedUISceneManager();
            sceneManager->setCurrentUISceneId(kUICheckBoxTest);
            sceneManager->setMinUISceneId(kUICheckBoxTest);
            sceneManager->setMaxUISceneId(kUICheckBoxTest);
            Scene* scene = sceneManager->currentUIScene();
            Director::getInstance()->replaceScene(scene);
        }
	},
	{
        "SliderTest",
        [](Ref* sender)
        {
            UISceneManager* sceneManager = UISceneManager::sharedUISceneManager();
            sceneManager->setCurrentUISceneId(kUISliderTest);
            sceneManager->setMinUISceneId(kUISliderTest);
            sceneManager->setMaxUISceneId(kUISliderTest_Scale9);
            Scene* scene = sceneManager->currentUIScene();
            Director::getInstance()->replaceScene(scene);
        }
	},
    {
        "ImageViewTest",
        [](Ref* sender)
        {
            UISceneManager* sceneManager = UISceneManager::sharedUISceneManager();
            sceneManager->setCurrentUISceneId(kUIImageViewTest);
            sceneManager->setMinUISceneId(kUIImageViewTest);
            sceneManager->setMaxUISceneId(kUIImageViewTest_Scale9);
            Scene* scene = sceneManager->currentUIScene();
            Director::getInstance()->replaceScene(scene);
        }
	},
    {
        "LoadingBarTest",
        [](Ref* sender)
        {
            UISceneManager* sceneManager = UISceneManager::sharedUISceneManager();
            sceneManager->setCurrentUISceneId(kUILoadingBarTest_Left);
            sceneManager->setMinUISceneId(kUILoadingBarTest_Left);
            sceneManager->setMaxUISceneId(kUILoadingBarTest_Right_Scale9);
            Scene* scene = sceneManager->currentUIScene();
            Director::getInstance()->replaceScene(scene);
        }
	},
    {
        "TextAtalsTest",
        [](Ref* sender)
        {
            UISceneManager* sceneManager = UISceneManager::sharedUISceneManager();
            sceneManager->setCurrentUISceneId(kUITextAtlasTest);
            sceneManager->setMinUISceneId(kUITextAtlasTest);
            sceneManager->setMaxUISceneId(kUITextAtlasTest);
            Scene* scene = sceneManager->currentUIScene();
            Director::getInstance()->replaceScene(scene);
        }
	},
    {
        "TextTest",
        [](Ref* sender)
        {
            UISceneManager* sceneManager = UISceneManager::sharedUISceneManager();
            sceneManager->setCurrentUISceneId(kUITextTest);
            sceneManager->setMinUISceneId(kUITextTest);
            sceneManager->setMaxUISceneId(kUITextTest_TTF);
            Scene* scene = sceneManager->currentUIScene();
            Director::getInstance()->replaceScene(scene);
        }
	},
    {
        "TextBMFontTest",
        [](Ref* sender)
        {
            UISceneManager* sceneManager = UISceneManager::sharedUISceneManager();
            sceneManager->setCurrentUISceneId(kUITextBMFontTest);
            sceneManager->setMinUISceneId(kUITextBMFontTest);
            sceneManager->setMaxUISceneId(kUITextBMFontTest);
            Scene* scene = sceneManager->currentUIScene();
            Director::getInstance()->replaceScene(scene);
        }
	},
    {
        "TextFieldTest",
        [](Ref* sender)
        {
            UISceneManager* sceneManager = UISceneManager::sharedUISceneManager();
            sceneManager->setCurrentUISceneId(kUITextFieldTest);
            sceneManager->setMinUISceneId(kUITextFieldTest);
            sceneManager->setMaxUISceneId(kUITextFieldTest_TrueTypeFont);
            Scene* scene = sceneManager->currentUIScene();
            Director::getInstance()->replaceScene(scene);
        }
	},
    {
        "LayoutTest",
        [](Ref* sender)
        {
            UISceneManager* sceneManager = UISceneManager::sharedUISceneManager();
            sceneManager->setCurrentUISceneId(kUILayoutTest);
            sceneManager->setMinUISceneId(kUILayoutTest);
            sceneManager->setMaxUISceneId(kUILayoutTest_Layout_Relative_Location);
            Scene* scene = sceneManager->currentUIScene();
            Director::getInstance()->replaceScene(scene);
        }
	},
    {
        "ScrollViewTest",
        [](Ref* sender)
        {
            UISceneManager* sceneManager = UISceneManager::sharedUISceneManager();
            sceneManager->setCurrentUISceneId(kUIScrollViewTest_Vertical);
            sceneManager->setMinUISceneId(kUIScrollViewTest_Vertical);
            sceneManager->setMaxUISceneId(kUIScrollViewTest_ScrollToPercentBothDirection_Bounce);
            Scene* scene = sceneManager->currentUIScene();
            Director::getInstance()->replaceScene(scene);
        }
	},
    {
        "PageViewTest",
        [](Ref* sender)
        {
            UISceneManager* sceneManager = UISceneManager::sharedUISceneManager();
            sceneManager->setCurrentUISceneId(kUIPageViewTest);
            sceneManager->setMinUISceneId(kUIPageViewTest);
            sceneManager->setMaxUISceneId(kUIPageViewButtonTest);
            Scene* scene = sceneManager->currentUIScene();
            Director::getInstance()->replaceScene(scene);
        }
	},
    {
        "ListViewTest",
        [](Ref* sender)
        {
            UISceneManager* sceneManager = UISceneManager::sharedUISceneManager();
            sceneManager->setCurrentUISceneId(kUIListViewTest_Vertical);
            sceneManager->setMinUISceneId(kUIListViewTest_Vertical);
            sceneManager->setMaxUISceneId(kUIListViewTest_Horizontal);
            Scene* scene = sceneManager->currentUIScene();
            Director::getInstance()->replaceScene(scene);
        }
	},
    {
        "WidgetAddNodeTest",
        [](Ref* sender)
        {
            UISceneManager* sceneManager = UISceneManager::sharedUISceneManager();
            sceneManager->setCurrentUISceneId(kUIWidgetAddNodeTest);
            sceneManager->setMinUISceneId(kUIWidgetAddNodeTest);
            sceneManager->setMaxUISceneId(kUIWidgetAddNodeTest);
            Scene* scene = sceneManager->currentUIScene();
            Director::getInstance()->replaceScene(scene);
        }
	},
    {
        "RichTextTest",
        [](Ref* sender)
        {
            UISceneManager* sceneManager = UISceneManager::sharedUISceneManager();
            sceneManager->setCurrentUISceneId(kUIRichTextTest);
            sceneManager->setMinUISceneId(kUIRichTextTest);
            sceneManager->setMaxUISceneId(kUIRichTextTest);
            Scene* scene = sceneManager->currentUIScene();
            Director::getInstance()->replaceScene(scene);
        }
	},

};

static const int g_maxTests = sizeof(g_guisTests) / sizeof(g_guisTests[0]);

static Vec2 s_tCurPos = Vec2::ZERO;

////////////////////////////////////////////////////////
//
// CocosGUITestMainLayer
//
////////////////////////////////////////////////////////
void CocosGUITestMainLayer::onEnter()
{
    Layer::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    
    _itemMenu = Menu::create();
    _itemMenu->setPosition( s_tCurPos );
    MenuItemFont::setFontName("fonts/arial.ttf");
    MenuItemFont::setFontSize(24);
    for (int i = 0; i < g_maxTests; ++i)
    {
        auto pItem = MenuItemFont::create(g_guisTests[i].name, g_guisTests[i].callback);
        pItem->setPosition(Vec2(s.width / 2, s.height - (i + 1) * LINE_SPACE));
        _itemMenu->addChild(pItem, kItemTagBasic + i);
    }
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(CocosGUITestMainLayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(CocosGUITestMainLayer::onTouchesMoved, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    addChild(_itemMenu);
}

void CocosGUITestMainLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
    auto touch = static_cast<Touch*>(touches[0]);
    
    _beginPos = touch->getLocation();
}

void CocosGUITestMainLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    auto touch = static_cast<Touch*>(touches[0]);
    
    auto touchLocation = touch->getLocation();
    float nMoveY = touchLocation.y - _beginPos.y;
    
    auto curPos  = _itemMenu->getPosition();
    auto nextPos = Vec2(curPos.x, curPos.y + nMoveY);
    
    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(Vec2::ZERO);
        return;
    }
    
    if (nextPos.y > ((g_maxTests + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        _itemMenu->setPosition(Vec2(0, ((g_maxTests + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
        return;
    }
    
    _itemMenu->setPosition(nextPos);
    _beginPos = touchLocation;
    s_tCurPos   = nextPos;
}

////////////////////////////////////////////////////////
//
// CocosGUITestScene
//
////////////////////////////////////////////////////////

void CocosGUITestScene::onEnter()
{
    Scene::onEnter();
    
    auto label = Label::createWithTTF("Back", "fonts/arial.ttf", 20);
    //#endif
    auto pMenuItem = MenuItemLabel::create(label, CC_CALLBACK_1(CocosGUITestScene::BackCallback, this));
    
    Menu* pMenu =Menu::create(pMenuItem, nullptr);
    
    pMenu->setPosition( Vec2::ZERO );
    pMenuItem->setPosition( Vec2( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );
    
    addChild(pMenu, 1);
}

void CocosGUITestScene::runThisTest()
{
    auto layer = new CocosGUITestMainLayer();
    addChild(layer);
    layer->release();
    
    Director::getInstance()->replaceScene(this);
}

void CocosGUITestScene::BackCallback(Ref* pSender)
{
    CocoStudioGUITestScene* pScene = new CocoStudioGUITestScene();
    pScene->runThisTest();
    pScene->release();
}
