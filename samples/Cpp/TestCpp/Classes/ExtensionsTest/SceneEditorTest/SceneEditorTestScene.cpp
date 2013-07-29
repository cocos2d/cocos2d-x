#include "SceneEditorTestScene.h"
#include "../ExtensionsTest.h"
#include "CocostudioReader/CCJsonReader.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::extension::armature;

SceneEditorTestLayer::~SceneEditorTestLayer()
{
}

SceneEditorTestLayer::SceneEditorTestLayer()
{
	m_pCurNode = NULL;
}

Scene* SceneEditorTestLayer::scene()
{
	Scene * scene = NULL;
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
        CC_BREAK_IF(! CCLayerColor::initWithColor( Color4B(0,0,0,255) ) );
        
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);

		bRet = true;
	} while (0);

	return bRet;
}

cocos2d::Node* SceneEditorTestLayer::createGameScene()
{
    Node *pNode = CCJsonReader::sharedJsonReader()->createNodeWithJsonFile("FishJoy2.json");
	if (pNode == NULL)
	{
		return NULL;
	}
	m_pCurNode = pNode;

	//play back music
    ComAudio *pAudio = (ComAudio*)(pNode->getComponent("Audio"));
	pAudio->playBackgroundMusic(pAudio->getFile(), pAudio->getIsLoop());

	//fishes
	Armature *pBlowFish = getFish(5, "blowFish");
	Armature *pButterFlyFish = getFish(6, "butterFlyFish");
	pBlowFish->getAnimation()->playByIndex(0);
	pButterFlyFish->getAnimation()->playByIndex(0);

    MenuItemFont *itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(SceneEditorTestLayer::toExtensionsMainLayer, this));//this, menu_selector(SceneEditorTestLayer::toExtensionsMainLayer));
        itemBack->setColor(Color3B(255, 255, 255));
        itemBack->setPosition(Point(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
        Menu *menuBack = Menu::create(itemBack, NULL);
    menuBack->setPosition(Point::ZERO);
		menuBack->setZOrder(4);

    pNode->addChild(menuBack);
    
	//ui action
	cocos2d::extension::UIActionManager::shareManager()->PlayActionByName("Animation1");

    return pNode;
}

void SceneEditorTestLayer::toExtensionsMainLayer(cocos2d::Object *sender)
{

	ExtensionsTestScene *pScene = new ExtensionsTestScene();
	pScene->runThisTest();
	pScene->release();
}


void runSceneEditorTestLayer()
{
    Scene *pScene = SceneEditorTestLayer::scene();
    Director::getInstance()->replaceScene(pScene);
}

Armature* SceneEditorTestLayer::getFish(int nTag, const char *pszName)
{
	if (m_pCurNode == NULL)
	{
		return NULL;
	}
	CCComRender *pFishRender = (CCComRender*)(m_pCurNode->getChildByTag(nTag)->getComponent(pszName));
	return (Armature *)(pFishRender->getRender());
}
