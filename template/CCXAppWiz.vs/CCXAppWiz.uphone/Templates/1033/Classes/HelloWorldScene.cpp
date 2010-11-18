#include "HelloWorldScene.h"

#include "Resource.h"

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

[! if CCX_USE_UI_RESOURCE]
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
										(ResInfo[0]).ResName,
										(ResInfo[1]).ResName,
										this,
										menu_selector(HelloWorld::menuCloseCallback) );
	pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
	pMenu->setPosition( CGPointZero );
	this->addChild(pMenu);

	/////////////////////////////
	// 3. add your codes below...
[! else]
    /////////////////////////////
    // 2. add your codes below...
[! endif]
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
[! if CCX_USE_UI_RESOURCE]

void HelloWorld::menuCloseCallback(NSObject* pSender)
{
	CCDirector::sharedDirector()->end();
}
[! endif]
