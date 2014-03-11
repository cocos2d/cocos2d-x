

#include "CocoStudioGUITest.h"
#include "../../ExtensionsTest/ExtensionsTest.h"
#include "CocosGUIScene.h"
#include "GUIEditorTest.h"
#include "CustomGUIScene.h"


enum
{
    LINE_SPACE = 40,
    kItemTagBasic = 1000,
};

enum
{
    TEST_GUI_WIDGET_DYNAMIC_CREATE,
    TEST_GUI_WIDGET_CREATE_FROM_EDITOR,
    TEST_CUSTOM_GUI,
    TEST_MAX_COUNT,
};

static const std::string testsName[TEST_MAX_COUNT] =
{
    "GUI Dynamic Create Test",
    "GUI Editor Test",
    "Custom GUI Test",
};

////////////////////////////////////////////////////////
//
// CocoStudioGUIMainLayer
//
////////////////////////////////////////////////////////

static CCPoint _curPos = CCPointZero;

void CocoStudioGUIMainLayer::onEnter()
{
    CCLayer::onEnter();
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    _itemMenu = CCMenu::create();
    _itemMenu->setPosition(CCPointZero);
    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(24);
    for (int i = 0; i < TEST_MAX_COUNT; ++i)
    {
        CCMenuItemFont* pItem = CCMenuItemFont::create(testsName[i].c_str(), this, menu_selector(CocoStudioGUIMainLayer::menuCallback));
        pItem->setPosition(ccp(s.width / 2, s.height / 4 * 3 - (i + 1) * LINE_SPACE));
        _itemMenu->addChild(pItem, kItemTagBasic + i);
    }
    addChild(_itemMenu);
}

void CocoStudioGUIMainLayer::menuCallback(CCObject *pSender)
{
    CCMenuItemFont* pItem = static_cast<CCMenuItemFont*>(pSender);
    int nIndex = pItem->getZOrder() - kItemTagBasic;
    
    switch (nIndex)
    {
        case TEST_GUI_WIDGET_DYNAMIC_CREATE:
        {
            CocosGUITestScene *pScene = new CocosGUITestScene();
			pScene->runThisTest();
			pScene->release();
        }
            break;
            
        case TEST_CUSTOM_GUI:
        {
            CustomGUITestScene* pScene = new CustomGUITestScene();
            pScene->runThisTest();
            pScene->release();
        }
            break;
         
//            /*
        case TEST_GUI_WIDGET_CREATE_FROM_EDITOR:
        {
            GUIEditorTestScene* pScene = new GUIEditorTestScene();
            pScene->runThisTest();
            pScene->release();
        }
            break;
//             */
            
        default:
            break;
    }
}

void CocoStudioGUIMainLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    _beginPos = touch->getLocation();
}

void CocoStudioGUIMainLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    CCPoint touchLocation = touch->getLocation();
    float nMoveY = touchLocation.y - _beginPos.y;
    
    CCPoint curPos = _itemMenu->getPosition();
    CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);
    
    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(CCPointZero);
        return;
    }
    
    if (nextPos.y > ((TEST_MAX_COUNT + 1) * LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        _itemMenu->setPosition(ccp(0, ((TEST_MAX_COUNT + 1) * LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
        return;
    }
    
    _itemMenu->setPosition(nextPos);
    _beginPos = touchLocation;
    _curPos = nextPos;
}

////////////////////////////////////////////////////////
//
// CocoStudioGUITestScene
//
////////////////////////////////////////////////////////

void CocoStudioGUITestScene::onEnter()
{
    CCScene::onEnter();

    CCLabelTTF* label = CCLabelTTF::create("Back", "Arial", 20);
    //#endif
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(CocoStudioGUITestScene::BackCallback));
    
    CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);
    
    pMenu->setPosition( CCPointZero );
    pMenuItem->setPosition( ccp( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );
    
    addChild(pMenu, 1);
}

void CocoStudioGUITestScene::runThisTest()
{
    CCLayer* pLayer = new CocoStudioGUIMainLayer();
    addChild(pLayer);
    pLayer->release();
    
    CCDirector::sharedDirector()->replaceScene(this);
}

void CocoStudioGUITestScene::BackCallback(CCObject* pSender)
{
    ExtensionsTestScene* pScene = new ExtensionsTestScene();
    pScene->runThisTest();
    pScene->release();
}
