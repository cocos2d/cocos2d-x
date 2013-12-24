
#include "cocos-ext.h"
#include "../ExtensionsTest.h"
#include "SceneEditorTest.h"
#include "TriggerCode/EventDef.h"

using namespace cocos2d;
using namespace cocos2d::extension;

SceneEditorTestLayer::~SceneEditorTestLayer()
{
	CCArmatureDataManager::purge();
	SceneReader::sharedSceneReader()->purgeSceneReader();
	cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
}

SceneEditorTestLayer::SceneEditorTestLayer()
{
	m_pCurNode = NULL;
}

CCScene* SceneEditorTestLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		SceneEditorTestLayer *layer = SceneEditorTestLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SceneEditorTestLayer::init()
{
	bool bRet = false;
	do 
	{
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
        sendEvent(TRIGGEREVENT_INITSCENE);
	    this->schedule(schedule_selector(SceneEditorTestLayer::gameLogic));
	    this->setTouchEnabled(true);
	    this->setTouchMode(kCCTouchesOneByOne);
		bRet = true;
	} while (0);

	return bRet;
}

void SceneEditorTestLayer::onEnter()
{
	CCLayer::onEnter();
	sendEvent(TRIGGEREVENT_ENTERSCENE);
}

void SceneEditorTestLayer::onExit()
{
	CCLayer::onExit();
	sendEvent(TRIGGEREVENT_LEAVESCENE);
}

bool SceneEditorTestLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	sendEvent(TRIGGEREVENT_TOUCHBEGAN);
	return true;
}

void SceneEditorTestLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	sendEvent(TRIGGEREVENT_TOUCHMOVED);
}

void SceneEditorTestLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	sendEvent(TRIGGEREVENT_TOUCHENDED);
}

void SceneEditorTestLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	sendEvent(TRIGGEREVENT_TOUCHCANCELLED);
}

void SceneEditorTestLayer::gameLogic(float dt)
{
    sendEvent(TRIGGEREVENT_UPDATESCENE);
}

static ActionObject* actionObject = NULL;

cocos2d::CCNode* SceneEditorTestLayer::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/FishJoy2.json");
	if (pNode == NULL)
	{
		return NULL;
	}
	m_pCurNode = pNode;

    CCMenuItemFont *itemBack = CCMenuItemFont::create("Back", this, menu_selector(SceneEditorTestLayer::toExtensionsMainLayer));
        itemBack->setColor(ccc3(255, 255, 255));
        itemBack->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
        CCMenu *menuBack = CCMenu::create(itemBack, NULL);
        menuBack->setPosition(CCPointZero);
		menuBack->setZOrder(4);

    pNode->addChild(menuBack);
    
	//ui action
	actionObject = cocos2d::extension::ActionManager::shareManager()->playActionByName("startMenu_1.json","Animation1");

    return pNode;
}

void SceneEditorTestLayer::toExtensionsMainLayer(cocos2d::CCObject *sender)
{
	if (actionObject)
	{
		actionObject->stop();
	}
	this->setTouchEnabled(false);
	ExtensionsTestScene *pScene = new ExtensionsTestScene();
	pScene->runThisTest();
	pScene->release();
}


void runSceneEditorTestLayer()
{
    CCScene *pScene = SceneEditorTestLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

CCArmature* SceneEditorTestLayer::getFish(int nTag, const char *pszName)
{
	if (m_pCurNode == NULL)
	{
		return NULL;
	}
	CCComRender *pFishRender = (CCComRender*)(m_pCurNode->getChildByTag(nTag)->getComponent(pszName));
	return (CCArmature *)(pFishRender->getNode());
}
