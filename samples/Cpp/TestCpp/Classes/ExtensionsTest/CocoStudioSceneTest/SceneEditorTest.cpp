
#include "extensions/cocos-ext.h"
#include "../ExtensionsTest.h"
#include "SceneEditorTest.h"
#include "cocostudio/CocoStudio.h"
#include "gui/CocosGUI.h"
#include "TriggerCode/EventDef.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace gui;

SceneEditorTestLayer::~SceneEditorTestLayer()
{
    ArmatureDataManager::destroyInstance();
	SceneReader::destroyInstance();
	ActionManagerEx::destroyInstance();
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->removeEventListener(_touchListener);
}

SceneEditorTestLayer::SceneEditorTestLayer()
{
	_curNode = nullptr;
    _touchListener = nullptr;
}

Scene* SceneEditorTestLayer::scene()
{
	Scene * scene = nullptr;
	do 
	{
		// 'scene' is an autorelease object
		scene = Scene::create();
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
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
        sendEvent(TRIGGEREVENT_INITSCENE);
	    this->schedule(schedule_selector(SceneEditorTestLayer::gameLogic));
	    auto dispatcher = Director::getInstance()->getEventDispatcher();
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = CC_CALLBACK_2(SceneEditorTestLayer::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(SceneEditorTestLayer::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(SceneEditorTestLayer::onTouchEnded, this);
        listener->onTouchCancelled = CC_CALLBACK_2(SceneEditorTestLayer::onTouchCancelled, this);
        dispatcher->addEventListenerWithFixedPriority(listener, 1);
        _touchListener = listener;

		bRet = true;
	} while (0);

	return bRet;
}

void SceneEditorTestLayer::onEnter()
{
	Layer::onEnter();
	sendEvent(TRIGGEREVENT_ENTERSCENE);
}

void SceneEditorTestLayer::onExit()
{
	Layer::onExit();
	sendEvent(TRIGGEREVENT_LEAVESCENE);
}

bool SceneEditorTestLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    sendEvent(TRIGGEREVENT_TOUCHBEGAN);
    return true;
}

void SceneEditorTestLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    sendEvent(TRIGGEREVENT_TOUCHMOVED);
}

void SceneEditorTestLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    sendEvent(TRIGGEREVENT_TOUCHENDED);
}

void SceneEditorTestLayer::onTouchCancelled(Touch *touch, Event *unused_event)
{
    sendEvent(TRIGGEREVENT_TOUCHCANCELLED);
}

void SceneEditorTestLayer::gameLogic(float dt)
{
    sendEvent(TRIGGEREVENT_UPDATESCENE);
}

static ActionObject* actionObject = nullptr;

cocos2d::Node* SceneEditorTestLayer::createGameScene()
{
    Node *pNode = SceneReader::getInstance()->createNodeWithSceneFile("scenetest/FishJoy2.json");
	if (pNode == nullptr)
	{
		return nullptr;
	}
	_curNode = pNode;
   
    MenuItemFont *itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(SceneEditorTestLayer::toExtensionsMainLayer, this));
        itemBack->setColor(Color3B(255, 255, 255));
        itemBack->setPosition(Point(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
        Menu *menuBack = Menu::create(itemBack, nullptr);
        menuBack->setPosition(Point(0.0f, 0.0f));
		menuBack->setZOrder(4);

    pNode->addChild(menuBack);
    
    return pNode;
}

void SceneEditorTestLayer::toExtensionsMainLayer(cocos2d::Object *sender)
{
	if (actionObject)
	{
		actionObject->stop();
	}
    ComAudio *pBackMusic = (ComAudio*)(_curNode->getComponent("CCBackgroundAudio"));
    pBackMusic->stopBackgroundMusic();
	ExtensionsTestScene *pScene = new ExtensionsTestScene();
	pScene->runThisTest();
	pScene->release();
}  


void runSceneEditorTestLayer()
{
    Scene *pScene = SceneEditorTestLayer::scene();
    Director::getInstance()->replaceScene(pScene);
}
