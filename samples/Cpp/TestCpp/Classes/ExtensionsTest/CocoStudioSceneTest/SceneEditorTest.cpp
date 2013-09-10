
#include "cocos-ext.h"
#include "../ExtensionsTest.h"
#include "SceneEditorTest.h"

using namespace cocos2d;
using namespace cocos2d::extension;

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
        CC_BREAK_IF(! LayerColor::initWithColor( ccc4(0,0,0,255) ) );
        
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);

		bRet = true;
	} while (0);

	return bRet;
}

cocos2d::CCNode* SceneEditorTestLayer::createGameScene()
{
    Node *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/FishJoy2.json");
	if (pNode == NULL)
	{
		return NULL;
	}
	m_pCurNode = pNode;

	//fishes
	/*cocos2d::extension::armature::Armature *pBlowFish = getFish(10008, "blowFish");
	cocos2d::extension::armature::Armature *pButterFlyFish = getFish(10009, "butterFlyFish");
	pBlowFish->getAnimation()->playByIndex(0);
	pButterFlyFish->getAnimation()->playByIndex(0);*/

    CCMenuItemFont *itemBack = CCMenuItemFont::create("Back", this, menu_selector(SceneEditorTestLayer::toExtensionsMainLayer));
        itemBack->setColor(ccc3(255, 255, 255));
        itemBack->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
        CCMenu *menuBack = CCMenu::create(itemBack, NULL);
        menuBack->setPosition(CCPointZero);
		menuBack->setZOrder(4);

    pNode->addChild(menuBack);
    
	//ui action
	//cocos2d::extension::UIActionManager::shareManager()->PlayActionByName("startMenu_1.json","Animation1");

    return pNode;
}

void SceneEditorTestLayer::toExtensionsMainLayer(cocos2d::CCObject *sender)
{

	ExtensionsTestScene *pScene = new ExtensionsTestScene();
	pScene->runThisTest();
	pScene->release();
}


void runSceneEditorTestLayer()
{
    CCScene *pScene = SceneEditorTestLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

cocos2d::extension::armature::Armature* SceneEditorTestLayer::getFish(int nTag, const char *pszName)
{
	if (m_pCurNode == NULL)
	{
		return NULL;
	}
	ComRender *pFishRender = (ComRender*)(m_pCurNode->getChildByTag(nTag)->getComponent(pszName));
	return (cocos2d::extension::armature::Armature *)(pFishRender->getNode());
}
