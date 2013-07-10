#include "SceneEditorTestScene.h"
#include "../ExtensionsTest.h"
#include "CocostudioReader/CCJsonReader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

SceneEditorTestLayer::~SceneEditorTestLayer()
{
}

SceneEditorTestLayer::SceneEditorTestLayer()
{
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
    CCNode *pNode = CCJsonReader::sharedJsonReader()->createNodeWithJsonFile("NewProject123.json");
    
    CCMenuItemFont *itemBack = CCMenuItemFont::create("Back", this, menu_selector(SceneEditorTestLayer::toExtensionsMainLayer));
        itemBack->setColor(ccc3(255, 255, 255));
        itemBack->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
        CCMenu *menuBack = CCMenu::create(itemBack, NULL);
        menuBack->setPosition(CCPointZero);
    
    pNode->addChild(menuBack);
    
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
