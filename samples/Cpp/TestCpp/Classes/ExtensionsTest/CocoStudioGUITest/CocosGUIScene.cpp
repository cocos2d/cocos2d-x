#include "CocosGUIScene.h"
#include "CocoStudioGUITest.h"
#include "UISceneManager.h"

enum
{
    LINE_SPACE = 40,
    kItemTagBasic = 1000,
};

enum
{
    TEST_BUTTON = 0,
    TEST_CHECKBOX,
    TEST_SLIDER,
    /*
    TEST_POTENTIOMETER,
    TEST_SWITCH,
     */
    TEST_IMAGEVIEW,
    TEST_LOADINGBAR,
    /*
    TEST_PROGRESSTIMER,
     */
    TEST_LABELATLAS,
    TEST_LABEL,
    TEST_LABELBMFONT,
    TEST_TEXTFIELD,
    TEST_LAYOUT,
    TEST_SCROLLVIEW,
    TEST_PAGEVIEW,
    TEST_LISTVIEW,
    /*
    TEST_GRIDVIEW,
    TEST_PICKERVIEW,
     */
    TEST_WIDGETADDNODE,
    TEST_RICHTEXT,
    TEST_MAX_COUNT,
};

static const std::string testsName[TEST_MAX_COUNT] =
{
    "gui ButtonTest",
    "gui CheckBoxTest",
    "gui SliderTest",
    /*
    "gui PotentiometerTest",
    "gui SwitchTest",
     */
    "gui ImageViewTest",
    "gui LoadingBarTest",
    /*
    "gui ProgressTimerTest",
     */
    "gui LabelAtalsTest",
    "gui LabelTest",
    "gui LabelBMFontTest",
    "gui TextFieldTest",
    "gui LayoutTest",
    "gui ScrollViewTest",
    "gui PageViewTest",
    "gui ListViewTest",
    /*
    "gui GridViewTest",
    "gui PickerViewTest",
     */
    "gui WidgetAddNodeTest",
    "gui RichTextTest",
};

////////////////////////////////////////////////////////
//
// CocosGUITestMainLayer
//
////////////////////////////////////////////////////////

static CCPoint s_tCurPos = CCPointZero;

void CocosGUITestMainLayer::onEnter()
{
    CCLayer::onEnter();
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
//    /*
    m_pItemMenu = CCMenu::create();
    m_pItemMenu->setPosition( s_tCurPos );
    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(24);
    for (int i = 0; i < TEST_MAX_COUNT; ++i)
    {
        CCMenuItemFont* pItem = CCMenuItemFont::create(testsName[i].c_str(), this,
                                                       menu_selector(CocosGUITestMainLayer::menuCallback));
        pItem->setPosition(ccp(s.width / 2, s.height - (i + 1) * LINE_SPACE));
        m_pItemMenu->addChild(pItem, kItemTagBasic + i);
    }
    setTouchEnabled(true);
    addChild(m_pItemMenu);
//     */
}


void CocosGUITestMainLayer::touchEvent(cocos2d::CCObject *pSender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_ENDED:
            CCLOG("button touch ended");
            break;
            
        default:
            break;
    }
}

void CocosGUITestMainLayer::menuCallback(CCObject* pSender)
{
    UISceneManager* pManager = UISceneManager::sharedUISceneManager();
    CCMenuItemFont* pItem = (CCMenuItemFont*)pSender;
    int nIndex = pItem->getZOrder() - kItemTagBasic;
    
    switch (nIndex)
    {
        case TEST_BUTTON:
            pManager->setCurrentUISceneId(kUIButtonTest);
            pManager->setMinUISceneId(kUIButtonTest);
            pManager->setMaxUISceneId(kUIButtonTest_Title);
            break;
            
        case TEST_CHECKBOX:
        {
            pManager->setCurrentUISceneId(kUICheckBoxTest);
            pManager->setMinUISceneId(kUICheckBoxTest);
            pManager->setMaxUISceneId(kUICheckBoxTest);
        }
            break;
            
        case TEST_SLIDER:
        {
            pManager->setCurrentUISceneId(kUISliderTest);
            pManager->setMinUISceneId(kUISliderTest);
            pManager->setMaxUISceneId(kUISliderTest_Scale9);
        }
            break;
            
            /*
        case TEST_POTENTIOMETER:
        {
            pManager->setCurrentUISceneId(kUIPotentiometerTest);
            pManager->setMinUISceneId(kUIPotentiometerTest);
            pManager->setMaxUISceneId(kUIPotentiometerTest);
        }
            break;
            
        case TEST_SWITCH:
        {
            pManager->setCurrentUISceneId(kUISwitchTest_Horizontal);
            pManager->setMinUISceneId(kUISwitchTest_Horizontal);
            pManager->setMaxUISceneId(kUISwitchTest_VerticalAndTitleVertical);
        }
            break;
             */
            
        case TEST_IMAGEVIEW:
        {
            pManager->setCurrentUISceneId(kUIImageViewTest);
            pManager->setMinUISceneId(kUIImageViewTest);
            pManager->setMaxUISceneId(kUIImageViewTest_Scale9);
        }
            break;
            
        case TEST_LOADINGBAR:
        {
            pManager->setCurrentUISceneId(kUILoadingBarTest_Left);
            pManager->setMinUISceneId(kUILoadingBarTest_Left);
            pManager->setMaxUISceneId(kUILoadingBarTest_Right_Scale9);
        }
            break;
            
            /*
        case TEST_PROGRESSTIMER:
        {
            pManager->setCurrentUISceneId(kUIProgressTimerTest_Radial);
            pManager->setMinUISceneId(kUIProgressTimerTest_Radial);
            pManager->setMaxUISceneId(kUIProgressTimerTest_WithSpriteFrame);
        }
            break;
             */
            
        case TEST_LABELATLAS:
        {
            pManager->setCurrentUISceneId(kUILabelAtlasTest);
            pManager->setMinUISceneId(kUILabelAtlasTest);
            pManager->setMaxUISceneId(kUILabelAtlasTest);
        }
            break;
            
        case TEST_LABEL:
        {
            pManager->setCurrentUISceneId(kUILabelTest);
            pManager->setMinUISceneId(kUILabelTest);
            pManager->setMaxUISceneId(kUILabelTest_TTF);
        }
            break;
            
        case TEST_LABELBMFONT:
        {
            pManager->setCurrentUISceneId(kUILabelBMFontTest);
            pManager->setMinUISceneId(kUILabelBMFontTest);
            pManager->setMaxUISceneId(kUILabelBMFontTest);
        }
            break;
            
        case TEST_TEXTFIELD:
        {
            pManager->setCurrentUISceneId(kUITextFieldTest);
            pManager->setMinUISceneId(kUITextFieldTest);
            pManager->setMaxUISceneId(kUITextFieldTest_LineWrap);
        }
            break;
            
        case TEST_LAYOUT:
		{
			pManager->setCurrentUISceneId(kUILayoutTest);
            pManager->setMinUISceneId(kUILayoutTest);
            pManager->setMaxUISceneId(kUILayoutTest_Layout_Relative_Location);
		}
            break;
            
        case TEST_SCROLLVIEW:
        {
            pManager->setCurrentUISceneId(kUIScrollViewTest_Vertical);
            pManager->setMinUISceneId(kUIScrollViewTest_Vertical);
            pManager->setMaxUISceneId(kUIScrollViewTest_ScrollToPercentBothDirection_Bounce);
        }
            break;
            
        case TEST_PAGEVIEW:
        {
			pManager->setCurrentUISceneId(kUIPageViewTest);
            pManager->setMinUISceneId(kUIPageViewTest);
            pManager->setMaxUISceneId(kUIPageViewTest);
		}
            break;
            
        case TEST_LISTVIEW:
		{
			pManager->setCurrentUISceneId(kUIListViewTest_Vertical);
            pManager->setMinUISceneId(kUIListViewTest_Vertical);
            pManager->setMaxUISceneId(kUIListViewTest_Horizontal);
		}
            break;
            
            /*
        case TEST_GRIDVIEW:
        {
            pManager->setCurrentUISceneId(kUIGridViewTest_Mode_Column);
            pManager->setMinUISceneId(kUIGridViewTest_Mode_Column);
            pManager->setMaxUISceneId(kUIGridViewTest_Mode_Row);
        }
            break;
            
        case TEST_PICKERVIEW:
        {
            pManager->setCurrentUISceneId(kUIPickerViewTest_Vertical);
            pManager->setMinUISceneId(kUIPickerViewTest_Vertical);
            pManager->setMaxUISceneId(kUIPickerViewTest_Horizontal);
        }
            break;
             */
            
        case TEST_WIDGETADDNODE:
        {
            pManager->setCurrentUISceneId(kUIWidgetAddNodeTest);
            pManager->setMinUISceneId(kUIWidgetAddNodeTest);
            pManager->setMaxUISceneId(kUIWidgetAddNodeTest);
        }
            break;
            
        case TEST_RICHTEXT:
        {
            pManager->setCurrentUISceneId(kUIRichTextTest);
            pManager->setMinUISceneId(kUIRichTextTest);
            pManager->setMaxUISceneId(kUIRichTextTest);
        }
            break;
            
        default:
            break;
    }
    
    CCScene* pScene = pManager->currentUIScene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void CocosGUITestMainLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    m_tBeginPos = touch->getLocation();
}

void CocosGUITestMainLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    CCPoint touchLocation = touch->getLocation();
    float nMoveY = touchLocation.y - m_tBeginPos.y;
    
    CCPoint curPos  = m_pItemMenu->getPosition();
    CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);
    
    if (nextPos.y < 0.0f)
    {
        m_pItemMenu->setPosition(CCPointZero);
        return;
    }
    
    if (nextPos.y > ((TEST_MAX_COUNT + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        m_pItemMenu->setPosition(ccp(0, ((TEST_MAX_COUNT + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
        return;
    }
    
    m_pItemMenu->setPosition(nextPos);
    m_tBeginPos = touchLocation;
    s_tCurPos   = nextPos;
}

////////////////////////////////////////////////////////
//
// CocosGUITestScene
//
////////////////////////////////////////////////////////

void CocosGUITestScene::onEnter()
{
    CCScene::onEnter();
    
    CCLabelTTF* label = CCLabelTTF::create("Back", "Arial", 20);
    //#endif
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(CocosGUITestScene::BackCallback));
    
    CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);
    
    pMenu->setPosition( CCPointZero );
    pMenuItem->setPosition( ccp( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );
    
    addChild(pMenu, 1);
}

void CocosGUITestScene::runThisTest()
{
    CCLayer* pLayer = new CocosGUITestMainLayer();
    addChild(pLayer);
    pLayer->release();
    
    CCDirector::sharedDirector()->replaceScene(this);
}

void CocosGUITestScene::BackCallback(CCObject* pSender)
{
    CocoStudioGUITestScene* pScene = new CocoStudioGUITestScene();
    pScene->runThisTest();
    pScene->release();
}

/*
const char* gui_scene_names[1] =
{
    "CocosGUIWidgetTest",
};

CocosGUITestScene::CocosGUITestScene(bool bPortrait)
: m_pLabel(NULL)
{
	TestScene::init();
}

CocosGUITestScene::~CocosGUITestScene()
{
	cocos2d::extension::SceneReader::sharedSceneReader()->purgeSceneReader();
	cocos2d::extension::ActionManager::purgeActionManager();
}

void CocosGUITestScene::runThisTest()
{
    
	CCDirector::sharedDirector()->replaceScene(this);
        
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    m_pItemMenu = CCMenu::create();
    m_pItemMenu->setPosition( CCPointZero );
    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(24);
    for (int i = 0; i < sizeof(gui_scene_names) / sizeof(gui_scene_names[0]); ++i)
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
    TestScene::MainMenuCallback(pSender);
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
            
        default:
            break;
    }
}
 */
