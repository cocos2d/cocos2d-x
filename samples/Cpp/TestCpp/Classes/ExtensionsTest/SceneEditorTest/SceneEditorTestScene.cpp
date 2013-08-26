#include "SceneEditorTestScene.h"
#include "../ExtensionsTest.h"
#include "CocostudioReader/CCSSceneReader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

SceneEditorTestLayer::~SceneEditorTestLayer()
{
	CCArmatureDataManager::purge();
	CCSSceneReader::sharedSceneReader()->purgeSceneReader();
	cocos2d::extension::UIActionManager::shareManager()->purgeUIActionManager();
	cocos2d::extension::UIHelper::instance()->purgeUIHelper();
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
        CC_BREAK_IF(! CCLayerColor::initWithColor( ccc4(0,0,0,255) ) );
        
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);

		bRet = true;
	} while (0);

	return bRet;
}

cocos2d::CCNode* SceneEditorTestLayer::createGameScene()
{
    CCNode *pNode = CCSSceneReader::sharedSceneReader()->createNodeWithSceneFile("FishJoy2.json");
	if (pNode == NULL)
	{
		return NULL;
	}
	m_pCurNode = pNode;

	//play back music
    CCComAudio *pAudio = (CCComAudio*)(pNode->getComponent("Audio"));
	pAudio->playBackgroundMusic(pAudio->getFile(), pAudio->isLoop());

	//fishes
	CCArmature *pBlowFish = getFish(5, "blowFish");
	CCArmature *pButterFlyFish = getFish(6, "butterFlyFish");
	pBlowFish->getAnimation()->playByIndex(0);
	pButterFlyFish->getAnimation()->playByIndex(0);

    CCMenuItemFont *itemBack = CCMenuItemFont::create("Back", this, menu_selector(SceneEditorTestLayer::toExtensionsMainLayer));
        itemBack->setColor(ccc3(255, 255, 255));
        itemBack->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
        CCMenu *menuBack = CCMenu::create(itemBack, NULL);
        menuBack->setPosition(CCPointZero);
		menuBack->setZOrder(4);

    pNode->addChild(menuBack);
    
	//ui action
	cocos2d::extension::UIActionManager::shareManager()->PlayActionByName("startMenu_1.json","Animation1");

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

CCArmature* SceneEditorTestLayer::getFish(int nTag, const char *pszName)
{
	if (m_pCurNode == NULL)
	{
		return NULL;
	}
	CCComRender *pFishRender = (CCComRender*)(m_pCurNode->getChildByTag(nTag)->getComponent(pszName));
	return (CCArmature *)(pFishRender->getRender());
}
