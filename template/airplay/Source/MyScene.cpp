#include "MyScene.h"

USING_NS_CC;

CCScene* MyScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	MyScene *layer = MyScene::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MyScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	//////////////////////////////
	// 2. add your codes below...


	//////////////////////////////
	return true;
}

void MyScene::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}
