

#include "GUIEditorTest.h"
#include "CocoStudioGUITest.h"
#include "UISceneManager_Editor.h"


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
	{
        "gui Button Editor Test",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUIButtonTest_Editor);
            pManager->setMinUISceneId(kUIButtonTest_Editor);
            pManager->setMaxUISceneId(kUIButtonTest_Editor);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
    {
        "gui CheckBox Editor Test",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUICheckBoxTest_Editor);
            pManager->setMinUISceneId(kUICheckBoxTest_Editor);
            pManager->setMaxUISceneId(kUICheckBoxTest_Editor);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
	{
        "gui Slider Editor Test",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUISliderTest_Editor);
            pManager->setMinUISceneId(kUISliderTest_Editor);
            pManager->setMaxUISceneId(kUISliderTest_Editor);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
    /*
	{
        "gui PotentiometerTest",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUIPotentiometerTest);
            pManager->setMinUISceneId(kUIPotentiometerTest);
            pManager->setMaxUISceneId(kUIPotentiometerTest);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
    {
        "gui SwitchTest",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUISwitchTest_Horizontal);
            pManager->setMinUISceneId(kUISwitchTest_Horizontal);
            pManager->setMaxUISceneId(kUISwitchTest_VerticalAndTitleVertical);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
     */
    {
        "gui ImageView Editor Test",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUIImageViewTest_Editor);
            pManager->setMinUISceneId(kUIImageViewTest_Editor);
            pManager->setMaxUISceneId(kUIImageViewTest_Editor);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
    {
        "gui LoadingBar Editor Test",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUILoadingBarTest_Editor);
            pManager->setMinUISceneId(kUILoadingBarTest_Editor);
            pManager->setMaxUISceneId(kUILoadingBarTest_Editor);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
    /*
    {
        "gui ProgressTimerTest",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUIProgressTimerTest_Radial);
            pManager->setMinUISceneId(kUIProgressTimerTest_Radial);
            pManager->setMaxUISceneId(kUIProgressTimerTest_WithSpriteFrame);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
     */
    {
        "gui TextAtals Editor Test",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUITextAtlasTest_Editor);
            pManager->setMinUISceneId(kUITextAtlasTest_Editor);
            pManager->setMaxUISceneId(kUITextAtlasTest_Editor);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
    {
        "gui Text Editor Test",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUITextTest_Editor);
            pManager->setMinUISceneId(kUITextTest_Editor);
            pManager->setMaxUISceneId(kUITextTest_Editor);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
    {
        "gui TextBMFont Editor Test",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUITextBMFontTest_Editor);
            pManager->setMinUISceneId(kUITextBMFontTest_Editor);
            pManager->setMaxUISceneId(kUITextBMFontTest_Editor);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
    {
        "gui TextField Editor Test",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUITextFieldTest_Editor);
            pManager->setMinUISceneId(kUITextFieldTest_Editor);
            pManager->setMaxUISceneId(kUITextFieldTest_Editor);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
    {
        "gui Layout Editor Test",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUILayoutTest_Editor);
            pManager->setMinUISceneId(kUILayoutTest_Editor);
            pManager->setMaxUISceneId(kUILayoutTest_Layout_Relative_Location_Editor);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
    {
        "gui ScrollView Editor Test",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUIScrollViewTest_Vertical_Editor);
            pManager->setMinUISceneId(kUIScrollViewTest_Vertical_Editor);
            pManager->setMaxUISceneId(kUIScrollViewTest_Both_Editor);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
    {
        "gui PageView Editor Test",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUIPageViewTest_Editor);
            pManager->setMinUISceneId(kUIPageViewTest_Editor);
            pManager->setMaxUISceneId(kUIPageViewTest_Editor);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
    {
        "gui ListView Editor Test",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUIListViewTest_Vertical_Editor);
            pManager->setMinUISceneId(kUIListViewTest_Vertical_Editor);
            pManager->setMaxUISceneId(kUIListViewTest_Horizontal_Editor);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
    /*
    {
        "gui GridViewTest",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUIGridViewTest_Mode_Column);
            pManager->setMinUISceneId(kUIGridViewTest_Mode_Column);
            pManager->setMaxUISceneId(kUIGridViewTest_Mode_Row);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
    {
        "gui PickerViewTest",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUIPickerViewTest_Vertical);
            pManager->setMinUISceneId(kUIPickerViewTest_Vertical);
            pManager->setMaxUISceneId(kUIPickerViewTest_Horizontal);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
     */
    {
        "gui WidgetAddNode Editor Test",
        [](Ref* sender)
        {
            UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
            pManager->setCurrentUISceneId(kUIWidgetAddNodeTest_Editor);
            pManager->setMinUISceneId(kUIWidgetAddNodeTest_Editor);
            pManager->setMaxUISceneId(kUIWidgetAddNodeTest_Editor);
            Scene* pScene = pManager->currentUIScene();
            Director::getInstance()->replaceScene(pScene);
        }
	},
};

static const int g_maxTests = sizeof(g_guisTests) / sizeof(g_guisTests[0]);

static Vector2 s_tCurPos = Vector2::ZERO;

////////////////////////////////////////////////////////
//
// GUIEditorMainLayer
//
////////////////////////////////////////////////////////
void GUIEditorMainLayer::onEnter()
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
        pItem->setPosition(Vector2(s.width / 2, s.height - (i + 1) * LINE_SPACE));
        _itemMenu->addChild(pItem, kItemTagBasic + i);
    }
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(GUIEditorMainLayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GUIEditorMainLayer::onTouchesMoved, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    addChild(_itemMenu);
}

void GUIEditorMainLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
    auto touch = static_cast<Touch*>(touches[0]);
    
    _beginPos = touch->getLocation();
}

void GUIEditorMainLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    auto touch = static_cast<Touch*>(touches[0]);
    
    auto touchLocation = touch->getLocation();
    float nMoveY = touchLocation.y - _beginPos.y;
    
    auto curPos  = _itemMenu->getPosition();
    auto nextPos = Vector2(curPos.x, curPos.y + nMoveY);
    
    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(Vector2::ZERO);
        return;
    }
    
    if (nextPos.y > ((g_maxTests + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        _itemMenu->setPosition(Vector2(0, ((g_maxTests + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
        return;
    }
    
    _itemMenu->setPosition(nextPos);
    _beginPos = touchLocation;
    s_tCurPos   = nextPos;
}

////////////////////////////////////////////////////////
//
// GUIEditorTestScene
//
////////////////////////////////////////////////////////

void GUIEditorTestScene::onEnter()
{
    Scene::onEnter();
    
    auto label = Label::createWithTTF("Back", "fonts/arial.ttf", 20);
    
    auto pMenuItem = MenuItemLabel::create(label, CC_CALLBACK_1(GUIEditorTestScene::BackCallback, this));
    
    Menu* pMenu =CCMenu::create(pMenuItem, nullptr);

    pMenu->setPosition( Vector2::ZERO );
    pMenuItem->setPosition( Vector2( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );
    
    addChild(pMenu, 1);
}

void GUIEditorTestScene::runThisTest()
{
    auto layer = new GUIEditorMainLayer();
    addChild(layer);
    layer->release();
    
    Director::getInstance()->replaceScene(this);
}

void GUIEditorTestScene::BackCallback(Ref* pSender)
{
    CocoStudioGUITestScene* pScene = new CocoStudioGUITestScene();
    pScene->runThisTest();
    pScene->release();
}
