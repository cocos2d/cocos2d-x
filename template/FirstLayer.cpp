
#include "FirstLayer.h"
using namespace cocos2d;

#define PATH_CLOSE_NORMAL		"/NEWPLUS/TDA_DATA/UserData/CloseNormal.png"
#define PATH_CLOSE_SELECTED		"/NEWPLUS/TDA_DATA/UserData/CloseSelected.png"


// on "init" you need to initialize your instance
bool FirstLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	/////////////////////////////
	// 2. add a label shows "Hello World"

	// create and initialize a label
	CCLabel* pLabel = CCLabel::labelWithString("HelloWorld", "Thonburi", 64);

	// ask director the window size
	CGSize size = CCDirector::getSharedDirector()->getWinSize();

	// position the label on the center of the screen
	pLabel->setPosition( ccp(size.width / 2, size.height / 2) );

	// add the label as a child to this layer
	this->addChild(pLabel);

	/////////////////////////////
	// 3. add a menu item with "X" image, which is clicked to quit the program

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
										PATH_CLOSE_NORMAL, 
										PATH_CLOSE_SELECTED, 
										this,
										menu_selector(FirstLayer::menuCloseCallback) );
	pCloseItem->setPosition( ccp(size.width - 20, 20) );

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
	pMenu->setPosition( CGPointZero );
	this->addChild(pMenu);
	

	return true;
}

void FirstLayer::menuCloseCallback(NSObject* pSender)
{
	CCDirector::getSharedDirector()->end();
}