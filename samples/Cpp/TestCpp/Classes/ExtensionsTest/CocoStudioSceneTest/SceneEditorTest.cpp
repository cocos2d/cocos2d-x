
#include "extensions/cocos-ext.h"
#include "../ExtensionsTest.h"
#include "SceneEditorTest.h"
#include "cocostudio/CocoStudio.h"
#include "gui/CocosGUI.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace gui;

SceneEditorTestLayer::~SceneEditorTestLayer()
{
    ArmatureDataManager::getInstance()->destoryInstance();
	SceneReader::getInstance()->purgeSceneReader();
	ActionManagerEx::shareManager()->purgeActionManager();
}

SceneEditorTestLayer::SceneEditorTestLayer()
{
	_curNode = nullptr;
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
        CC_BREAK_IF(! LayerColor::initWithColor(Color4B(0,0,0,255)));
        
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);

		bRet = true;
	} while (0);

	return bRet;
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
    
    //ui action
	actionObject = ActionManagerEx::shareManager()->playActionByName("startMenu_1.json","Animation1");
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
