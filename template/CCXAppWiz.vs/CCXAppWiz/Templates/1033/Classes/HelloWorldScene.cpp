
#include "HelloWorldScene.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	/////////////////////////////
	// 2. add your codes below...
	
	// add a label shows "Hello World"
	// create and initialize a label
	CCLabel* pLabel = CCLabel::labelWithString("HelloWorld", "Thonburi", 64);

	// ask director the window size
	CGSize size = CCDirector::sharedDirector()->getWinSize();

	// position the label on the center of the screen
	pLabel->setPosition( ccp(size.width / 2, size.height / 2) );

	// add the label as a child to this layer
	this->addChild(pLabel);
	
	return true;
}

void HelloWorld::menuCloseCallback(NSObject* pSender)
{
	CCDirector::sharedDirector()->end();
}