
#include "HelloWorld.h"
#include "FirstLayer.h"
using namespace cocos2d;

CCScene* HelloWorld::scene()
{
	bool bRet = false;

	// 'pScene' is an autorelease object
	CCScene *pScene = CCScene::node();
	
	// 'pLayer' is an autorelease object
	FirstLayer *pLayer = new FirstLayer;
	pLayer->init();

	// add layer as a child to scene
	pScene->addChild(pLayer);

	// release layer, it's "new" by us.
	pLayer->release();

	// return the scene
	return pScene;
}