

#include "GUIEditorTest.h"
#include "CocoStudioGUITest.h"
#include "UISceneManager_Editor.h"


enum
{
    LINE_SPACE = 40,
    kItemTagBasic = 1000,
};

enum
{
    TEST_BUTTON_EDITOR = 0,
    TEST_CHECKBOX_EDITOR,
    TEST_SLIDER_EDITOR,
    //
//     TEST_POTENTIOMETER,
//     TEST_SWITCH,
     //
    TEST_IMAGEVIEW_EDITOR,
    TEST_LOADINGBAR_EDITOR,
    //
//     TEST_PROGRESSTIMER,
     //
    TEST_LABELATLAS_EDITOR,
    TEST_LABEL_EDITOR,
    TEST_LABELBMFONT_EDITOR,
    TEST_TEXTFIELD_EDITOR,
    TEST_LAYOUT_EDITOR,
    TEST_SCROLLVIEW_EDITOR,
    TEST_PAGEVIEW_EDITOR,
    TEST_LISTVIEW_EDITOR,
    //
//     TEST_GRIDVIEW,
//     TEST_PICKERVIEW,
     //
    TEST_WIDGETADDNODE_EDITOR,
    TEST_MAX_COUNT,
};

static const std::string testsName[TEST_MAX_COUNT] =
{
    "gui Editor ButtonTest",
    "gui Editor CheckBoxTest",
    "gui Editor SliderTest",
    //
//     "gui Editor PotentiometerTest",
//     "gui Editor SwitchTest",
     //
    "gui Editor ImageViewTest",
    "gui Editor LoadingBarTest",
    //
//     "gui Editor ProgressTimerTest",
     //
    "gui Editor LabelAtalsTest",
    "gui Editor LabelTest",
    "gui Editor LabelBMFontTest",
    "gui Editor TextFieldTest",
    "gui Editor LayoutTest",
    "gui Editor ScrollViewTest",
    "gui Editor PageViewTest",
    "gui Editor ListViewTest",
    //
//     "gui Editor GridViewTest",
//     "gui Editor PickerViewTest",
     //
    "gui Editor WidgetAddNodeTest",
};

////////////////////////////////////////////////////////
//
// GUIEditorMainLayer
//
////////////////////////////////////////////////////////

static CCPoint _curPos = CCPointZero;

void GUIEditorMainLayer::onEnter()
{
    CCLayer::onEnter();
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    _itemMenu = CCMenu::create();
    _itemMenu->setPosition( _curPos );
    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(24);
    for (int i = 0; i < TEST_MAX_COUNT; ++i)
    {
        CCMenuItemFont* pItem = CCMenuItemFont::create(testsName[i].c_str(), this,
                                                       menu_selector(GUIEditorMainLayer::menuCallback));
        pItem->setPosition(ccp(s.width / 2, s.height - (i + 1) * LINE_SPACE));
        _itemMenu->addChild(pItem, kItemTagBasic + i);
    }
    setTouchEnabled(true);
    addChild(_itemMenu);
}

void GUIEditorMainLayer::menuCallback(CCObject* pSender)
{
    UISceneManager_Editor* pManager = UISceneManager_Editor::sharedUISceneManager_Editor();
    CCMenuItemFont* pItem = (CCMenuItemFont*)pSender;
    int nIndex = pItem->getZOrder() - kItemTagBasic;
    
    switch (nIndex)
    {
        case TEST_BUTTON_EDITOR:
            pManager->setCurrentUISceneId(kUIButtonTest_Editor);
            pManager->setMinUISceneId(kUIButtonTest_Editor);
            pManager->setMaxUISceneId(kUIButtonTest_Editor);
            break;
            
            
        case TEST_CHECKBOX_EDITOR:
        {
            pManager->setCurrentUISceneId(kUICheckBoxTest_Editor);
            pManager->setMinUISceneId(kUICheckBoxTest_Editor);
            pManager->setMaxUISceneId(kUICheckBoxTest_Editor);
        }
            break;
            
        case TEST_SLIDER_EDITOR:
        {
            pManager->setCurrentUISceneId(kUISliderTest_Editor);
            pManager->setMinUISceneId(kUISliderTest_Editor);
            pManager->setMaxUISceneId(kUISliderTest_Editor);
        }
            break;
            
            /*
            //
//             case TEST_POTENTIOMETER:
//             {
//             pManager->setCurrentUISceneId(kUIPotentiometerTest);
//             pManager->setMinUISceneId(kUIPotentiometerTest);
//             pManager->setMaxUISceneId(kUIPotentiometerTest);
//             }
//             break;
//             
//             case TEST_SWITCH:
//             {
//             pManager->setCurrentUISceneId(kUISwitchTest_Horizontal);
//             pManager->setMinUISceneId(kUISwitchTest_Horizontal);
//             pManager->setMaxUISceneId(kUISwitchTest_VerticalAndTitleVertical);
//             }
//             break;
             //
             */
            
        case TEST_IMAGEVIEW_EDITOR:
        {
            pManager->setCurrentUISceneId(kUIImageViewTest_Editor);
            pManager->setMinUISceneId(kUIImageViewTest_Editor);
            pManager->setMaxUISceneId(kUIImageViewTest_Editor);
        }
            break;
            
        case TEST_LOADINGBAR_EDITOR:
        {
            pManager->setCurrentUISceneId(kUILoadingBarTest_Editor);
            pManager->setMinUISceneId(kUILoadingBarTest_Editor);
            pManager->setMaxUISceneId(kUILoadingBarTest_Editor);
        }
            break;
            
            
            //
//             case TEST_PROGRESSTIMER:
//             {
//             pManager->setCurrentUISceneId(kUIProgressTimerTest_Radial);
//             pManager->setMinUISceneId(kUIProgressTimerTest_Radial);
//             pManager->setMaxUISceneId(kUIProgressTimerTest_WithSpriteFrame);
//             }
//             break;
             //
            
        case TEST_LABELATLAS_EDITOR:
        {
            pManager->setCurrentUISceneId(kUILabelAtlasTest_Editor);
            pManager->setMinUISceneId(kUILabelAtlasTest_Editor);
            pManager->setMaxUISceneId(kUILabelAtlasTest_Editor);
        }
            break;
            
            
        case TEST_LABEL_EDITOR:
        {
            pManager->setCurrentUISceneId(kUILabelTest_Editor);
            pManager->setMinUISceneId(kUILabelTest_Editor);
            pManager->setMaxUISceneId(kUILabelTest_Editor);
        }
            break;
            
        case TEST_LABELBMFONT_EDITOR:
        {
            pManager->setCurrentUISceneId(kUILabelBMFontTest_Editor);
            pManager->setMinUISceneId(kUILabelBMFontTest_Editor);
            pManager->setMaxUISceneId(kUILabelBMFontTest_Editor);
        }
            break;
            
        case TEST_TEXTFIELD_EDITOR:
        {
            pManager->setCurrentUISceneId(kUITextFieldTest_Editor);
            pManager->setMinUISceneId(kUITextFieldTest_Editor);
            pManager->setMaxUISceneId(kUITextFieldTest_Editor);
        }
            break;
            
        case TEST_LAYOUT_EDITOR:
		{
			pManager->setCurrentUISceneId(kUILayoutTest_Editor);
            pManager->setMinUISceneId(kUILayoutTest_Editor);
            pManager->setMaxUISceneId(kUILayoutTest_Layout_Relative_Location_Editor);
		}
            break;
            
        case TEST_SCROLLVIEW_EDITOR:
        {
            pManager->setCurrentUISceneId(kUIScrollViewTest_Vertical_Editor);
            pManager->setMinUISceneId(kUIScrollViewTest_Vertical_Editor);
            pManager->setMaxUISceneId(kUIScrollViewTest_Both_Editor);
        }
            break;
            
        case TEST_PAGEVIEW_EDITOR:
        {
			pManager->setCurrentUISceneId(kUIPageViewTest_Editor);
            pManager->setMinUISceneId(kUIPageViewTest_Editor);
            pManager->setMaxUISceneId(kUIPageViewTest_Editor);
		}
            break;
            
        case TEST_LISTVIEW_EDITOR:
		{
			pManager->setCurrentUISceneId(kUIListViewTest_Vertical_Editor);
            pManager->setMinUISceneId(kUIListViewTest_Vertical_Editor);
            pManager->setMaxUISceneId(kUIListViewTest_Horizontal_Editor);
		}
            break;
            
            //
//             case TEST_GRIDVIEW:
//             {
//             pManager->setCurrentUISceneId(kUIGridViewTest_Mode_Column);
//             pManager->setMinUISceneId(kUIGridViewTest_Mode_Column);
//             pManager->setMaxUISceneId(kUIGridViewTest_Mode_Row);
//             }
//             break;
//             
//             case TEST_PICKERVIEW:
//             {
//             pManager->setCurrentUISceneId(kUIPickerViewTest_Vertical);
//             pManager->setMinUISceneId(kUIPickerViewTest_Vertical);
//             pManager->setMaxUISceneId(kUIPickerViewTest_Horizontal);
//             }
//             break;
             //
            
        case TEST_WIDGETADDNODE_EDITOR:
        {
            pManager->setCurrentUISceneId(kUIWidgetAddNodeTest_Editor);
            pManager->setMinUISceneId(kUIWidgetAddNodeTest_Editor);
            pManager->setMaxUISceneId(kUIWidgetAddNodeTest_Editor);
        }
            break;
            
        default:
            break;
    }
    
    CCScene* pScene = pManager->currentUIScene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void GUIEditorMainLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    _beginPos = touch->getLocation();
}

void GUIEditorMainLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    CCPoint touchLocation = touch->getLocation();
    float nMoveY = touchLocation.y - _beginPos.y;
    
    CCPoint curPos  = _itemMenu->getPosition();
    CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);
    
    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(CCPointZero);
        return;
    }
    
    if (nextPos.y > ((TEST_MAX_COUNT + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        _itemMenu->setPosition(ccp(0, ((TEST_MAX_COUNT + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
        return;
    }
    
    _itemMenu->setPosition(nextPos);
    _beginPos = touchLocation;
    _curPos   = nextPos;
}

////////////////////////////////////////////////////////
//
// GUIEditorTestScene
//
////////////////////////////////////////////////////////

void GUIEditorTestScene::onEnter()
{
    CCScene::onEnter();
    
    CCLabelTTF* label = CCLabelTTF::create("Back", "Arial", 20);
    //#endif
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(GUIEditorTestScene::BackCallback));
    
    CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);
    
    pMenu->setPosition( CCPointZero );
    pMenuItem->setPosition( ccp( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );
    
    addChild(pMenu, 1);
}

void GUIEditorTestScene::runThisTest()
{
    CCLayer* pLayer = new GUIEditorMainLayer();
    addChild(pLayer);
    pLayer->release();
    
    CCDirector::sharedDirector()->replaceScene(this);
}

void GUIEditorTestScene::BackCallback(CCObject* pSender)
{
    CocoStudioGUITestScene* pScene = new CocoStudioGUITestScene();
    pScene->runThisTest();
    pScene->release();
}
