#include "ExtensionsTest.h"
#include "../testResource.h"
#include "NotificationCenterTest/NotificationCenterTest.h"
#include "ControlExtensionTest/CCControlSceneManager.h"
#include "CocosBuilderTest/CocosBuilderTest.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_EMSCRIPTEN)
#include "NetworkTest/HttpClientTest.h"
#endif
#include "TableViewTest/TableViewTestScene.h"
#include "ArmatureTest/ArmatureScene.h"
#include "ComponentsTest/ComponentsTestScene.h"
#include "SceneEditorTest/SceneEditorTestScene.h"
#include "CocosGUITest/CocosGUIScene.h"
#include "CocosGUITest/UISceneManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "NetworkTest/WebSocketTest.h"
#endif
 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN)
#include "EditBoxTest/EditBoxTest.h"
#endif

enum
{
    LINE_SPACE = 40,
    kItemTagBasic = 1000,
};

enum
{
    TEST_NOTIFICATIONCENTER = 0,
    TEST_CCCONTROLBUTTON,
    TEST_COCOSBUILDER,
    TEST_HTTPCLIENT,
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    TEST_WEBSOCKET,
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN)
    TEST_EDITBOX,
#endif
	TEST_TABLEVIEW,
	TEST_COMPONENTS,
	TEST_ARMATURE,
    TEST_SCENEEDITOR,
    TEST_COCOSGUI,
    TEST_MAX_COUNT,
};

static const std::string testsName[TEST_MAX_COUNT] = 
{
    "NotificationCenterTest",
    "CCControlButtonTest",
    "CocosBuilderTest",
#if (CC_TARGET_PLATFORM != CC_PLATFORM_EMSCRIPTEN)
    "HttpClientTest",
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    "WebSocketTest",
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN)
    "EditBoxTest",
#endif
	"TableViewTest",
    "ComponentsTest",
	"ArmatureTest",
    "SceneJsonTest",
    "CocosGUIScene"
};

////////////////////////////////////////////////////////
//
// ExtensionsMainLayer
//
////////////////////////////////////////////////////////

static CCPoint s_tCurPos = CCPointZero;

void ExtensionsMainLayer::onEnter()
{
    CCLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    m_pItemMenu = CCMenu::create();
    m_pItemMenu->setPosition( CCPointZero );
    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(24);
    for (int i = 0; i < TEST_MAX_COUNT; ++i)
    {
        CCMenuItemFont* pItem = CCMenuItemFont::create(testsName[i].c_str(), this,
                                                    menu_selector(ExtensionsMainLayer::menuCallback));
        pItem->setPosition(ccp(s.width / 2, s.height - (i + 1) * LINE_SPACE));
        m_pItemMenu->addChild(pItem, kItemTagBasic + i);
    }
    setTouchEnabled(true);
    addChild(m_pItemMenu);
}

void ExtensionsMainLayer::menuCallback(CCObject* pSender)
{
    CCMenuItemFont* pItem = (CCMenuItemFont*)pSender;
    int nIndex = pItem->getZOrder() - kItemTagBasic;

    switch (nIndex)
    {
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)	// MARMALADE CHANGE: Not yet avaiable on Marmalade
    case TEST_NOTIFICATIONCENTER:
        {
            runNotificationCenterTest();
        }
        break;
#endif
    case TEST_CCCONTROLBUTTON:
        {
            CCControlSceneManager* pManager = CCControlSceneManager::sharedControlSceneManager();
            CCScene* pScene = pManager->currentControlScene();
            CCDirector::sharedDirector()->replaceScene(pScene);
        }
        break;
    case TEST_COCOSBUILDER:
        {
            TestScene* pScene = new CocosBuilderTestScene();
            if (pScene)
            {
                pScene->runThisTest();
                pScene->release();
            }
        }
        break;
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE && CC_TARGET_PLATFORM != CC_PLATFORM_NACL && CC_TARGET_PLATFORM != CC_PLATFORM_EMSCRIPTEN)
    case TEST_HTTPCLIENT:
        {
            runHttpClientTest();
        }
        break;
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        case TEST_WEBSOCKET:
        {
            runWebSocketTest();
        }
        break;
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN)
    case TEST_EDITBOX:
        {
            runEditBoxTest();
        }
        break;
#endif
	case TEST_TABLEVIEW:
		{
			runTableViewTest();
		}
		break;
    case TEST_COMPONENTS:
        {
            runComponentsTestLayerTest();
        }
        break;
	case TEST_ARMATURE:
		{
			ArmatureTestScene *pScene = new ArmatureTestScene();
			if (pScene)
			{
				pScene->runThisTest();
				pScene->release();
			}
		}
		break;
    case TEST_SCENEEDITOR:
       {
            runSceneEditorTestLayer();
       }
            break;
        case TEST_COCOSGUI:
        {
			/*UISceneManager* pManager = UISceneManager::sharedUISceneManager();
			CCScene* pScene = pManager->currentUIScene();
			CCDirector::sharedDirector()->replaceScene(pScene);*/ 

			CocosGUITestScene *pScene = new CocosGUITestScene();
			pScene->runThisTest();
			pScene->release();
		}
            break;
    default:
        break;
    }
}


void ExtensionsMainLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);

    m_tBeginPos = touch->getLocation();    
}

void ExtensionsMainLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
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
// ExtensionsTestScene
//
////////////////////////////////////////////////////////

void ExtensionsTestScene::runThisTest()
{
    CCLayer* pLayer = new ExtensionsMainLayer();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}
