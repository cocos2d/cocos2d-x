
#include "HelloWorldScene.h"
// #include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#include <math.h>
using namespace cocos2d;

#define PATH_CLOSE_NORMAL		"/NEWPLUS/TDA_DATA/UserData/CloseNormal.png"
#define PATH_CLOSE_SELECTED		"/NEWPLUS/TDA_DATA/UserData/CloseSelected.png"
#define IMG_PLAYER				"/NEWPLUS/TDA_DATA/UserData/player.png"
#define IMG_PROJECTILE			"/NEWPLUS/TDA_DATA/UserData/projectile.png"
#define IMG_TARGET				"/NEWPLUS/TDA_DATA/UserData/target.png"

CCScene* HelloWorld::scene()
{
	bool bRet = false;

	// 'pScene' is an autorelease object
	CCScene *pScene = CCScene::node();
	
	// 'pLayer' is an autorelease object
	HelloWorld *pLayer = new HelloWorld;
	pLayer->init();

	// add layer as a child to scene
	pScene->addChild(pLayer);

	// release layer, it's "new" by us.
	pLayer->release();

	// return the scene
	return pScene;
}

void HelloWorld::spriteMoveFinished(CCNode* sender)
{
	TagSprite *sprite = (TagSprite *)sender;
	this->removeChild(sprite, true);

	if (sprite->getTag() == 1)  // target
	{
		_targets->removeObject(sprite);

		GameOverScene *gameOverScene = GameOverScene::node();
		gameOverScene->getLayer()->getLabel()->setString("You Lose :[");
		CCDirector::getSharedDirector()->replaceScene(gameOverScene);
	}
	else if (sprite->getTag() == 2) // projectile
	{
		_projectiles->removeObject(sprite);
	}
}


void HelloWorld::addTarget()
{
	TagSprite *target = (TagSprite*)CCSprite::spriteWithFile(IMG_TARGET, CGRectMake(0,0,27,40));

	// Determine where to spawn the target along the Y axis
	CGSize winSize = CCDirector::getSharedDirector()->getWinSize();
	int minY = (int)( target->getContentSize().height / 2 );
	int maxY = (int)( winSize.height -  target->getContentSize().height / 2 );
	int rangeY = maxY - minY;

	srand( TimGetTicks() );
	int actualY = ( rand() % rangeY ) + minY;

	// Create the target slightly off-screen along the right edge,
	// and along a random position along the Y axis as calculated above
	target->setPosition( ccp(winSize.width + (target->getContentSize().width/2), actualY) );
	this->addChild(target);

	// Determine speed of the target
	int minDuration = (int)2.0;
	int maxDuration = (int)4.0;
	int rangeDuration = maxDuration - minDuration;
	srand( TimGetTicks() );
	int actualDuration = ( rand() % rangeDuration ) + minDuration;

	// Create the actions
	CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration( (ccTime)actualDuration, ccp(0 - target->getContentSize().width/2, actualY) );
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(HelloWorld::spriteMoveFinished));
	target->runAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );

	// Add to targets array
	target->setTag(1);
	_targets->addObject(target);

}

void HelloWorld::gameLogic(ccTime dt)
{
	this->addTarget();
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	// always call "super" init
	if ( !CCColorLayer::initWithColor( ccc4(255,255,255,255) ) )
	{
		return false;
	}

	// cocos2d-uphone: add a menu item with "X" image, which is clicked to quit the program
	// add a "close" icon, it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
										PATH_CLOSE_NORMAL, 
										PATH_CLOSE_SELECTED, 
										this,
										menu_selector(HelloWorld::menuCloseCallback) );
	pCloseItem->setPosition( ccp( CCDirector::getSharedDirector()->getWinSize().width - 20, 20) );
	CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL); 	// create menu, it's an autorelease object
	pMenu->setPosition( CGPointZero );
	this->addChild(pMenu);


	/////////////////////////////
	// add your code below

	// Enable touch events
	this->setIsTouchEnabled(true);

	// Initialize arrays
	_targets = new NSMutableArray<TagSprite*>;
	_projectiles = new NSMutableArray<TagSprite*>;

	// Get the dimensions of the window for calculation purposes
	CGSize winSize = CCDirector::getSharedDirector()->getWinSize();

	// Add the player to the middle of the screen along the y-axis, 
	// and as close to the left side edge as we can get
	// Remember that position is based on the anchor point, and by default the anchor
	// point is the middle of the object.
	CCSprite *player = CCSprite::spriteWithFile(IMG_PLAYER, CGRectMake(0, 0, 27, 40) );
	player->setPosition( ccp(player->getContentSize().width / 2, winSize.height/2) );
	this->addChild(player);

	// Call game logic about every second
	this->schedule( schedule_selector(HelloWorld::gameLogic), 1.0 );
	this->schedule( schedule_selector(HelloWorld::update) );

	// Start up the background music
	// SimpleAudioEngine->getSharedEngine()->playBackgroundMusic("background-music-aac.caf");

	return true;
}


void HelloWorld::update(ccTime dt)
{
	NSMutableArray<TagSprite*> *projectilesToDelete = new NSMutableArray<TagSprite*>;
	NSMutableArray<TagSprite*>::NSMutableArrayIterator it, jt;

	for (it = _projectiles->begin(); it != _projectiles->end(); it++)
	{
		TagSprite *projectile = *it;

		CGRect projectileRect = CGRectMake(projectile->getPosition().x - (projectile->getContentSize().width/2),
						projectile->getPosition().y - (projectile->getContentSize().height/2),
						projectile->getContentSize().width,
						projectile->getContentSize().height);

		NSMutableArray<TagSprite*> *targetsToDelete = new NSMutableArray<TagSprite*>;

		for (jt = _targets->begin(); jt != _targets->end(); jt++)
		{
			TagSprite *target = *jt;

			CGRect targetRect = CGRectMake(target->getPosition().x - (target->getContentSize().width/2),
							target->getPosition().y - (target->getContentSize().height/2),
							target->getContentSize().width,
							target->getContentSize().height);
			
			if (CGRect::CGRectIntersectsRect(projectileRect, targetRect))
			{
				targetsToDelete->addObject(target);
			}
		}


		for (jt = targetsToDelete->begin(); jt != targetsToDelete->end(); jt++)
		{
			TagSprite *target = *jt;

			_targets->removeObject(target);
			this->removeChild(target, true);
			_projectilesDestroyed++;
			
			if (_projectilesDestroyed > 30)
			{
				GameOverScene *gameOverScene = GameOverScene::node();
				gameOverScene->getLayer()->getLabel()->setString("You Win!");
				CCDirector::getSharedDirector()->replaceScene(gameOverScene);
			}
		}

		if (targetsToDelete->count() > 0)
		{
			projectilesToDelete->addObject(projectile);
		}
		targetsToDelete->release();
	}

	for (it = projectilesToDelete->begin(); it != projectilesToDelete->end(); it++)
	{
		TagSprite* projectile = *it;

		_projectiles->removeObject(projectile);
		this->removeChild(projectile, true);
	}
	projectilesToDelete->release();
}


void HelloWorld::ccTouchesEnded(NSSet* touches, UIEvent* event)
{
	// Choose one of the touches to work with
	CCTouch* touch = (CCTouch*)( touches->anyObject() );
	CGPoint location = touch->locationInView(touch->view());
	location = CCDirector::getSharedDirector()->convertToGL(location);

	// Set up initial location of projectile
	CGSize winSize = CCDirector::getSharedDirector()->getWinSize();
	TagSprite *projectile = (TagSprite*)CCSprite::spriteWithFile(IMG_PROJECTILE, CGRectMake(0, 0, 20, 20));
	projectile->setPosition( ccp(20, winSize.height/2) );

	// Determinie offset of location to projectile
	float offX = location.x - projectile->getPosition().x;
	float offY = location.y - projectile->getPosition().y;

	// Bail out if we are shooting down or backwards
	if (offX <= 0) return;

	// Ok to add now - we've double checked position
	this->addChild(projectile);

	// Play a sound!
	// SimpleAudioEngine->getSharedEngine()->playEffect("pew-pew-lei.caf");

	// Determine where we wish to shoot the projectile to
	float realX = winSize.width + (projectile->getContentSize().width / 2);
	float ratio = (float)offY / (float)offX;
	float realY = (realX * ratio) + projectile->getPosition().y;
	CGPoint realDest = ccp(realX, realY);

	// Determine the length of how far we're shooting
	float offRealX = realX - projectile->getPosition().x;
	float offRealY = realY - projectile->getPosition().y;
	float length = sqrtf((offRealX * offRealX) + (offRealY*offRealY));
	float velocity = 480/1; // 480pixels/1sec
	float realMoveDuration = length/velocity;

	// Move projectile to actual endpoint
	projectile->runAction( CCSequence::actions(
		CCMoveTo::actionWithDuration(realMoveDuration, realDest),
		CCCallFuncN::actionWithTarget(this, callfuncN_selector(HelloWorld::spriteMoveFinished)),
		NULL) );

	// Add to projectiles array
	projectile->setTag(2);
	_projectiles->addObject(projectile);
}

HelloWorld::HelloWorld()
:_targets(NULL)
,_projectiles(NULL)
{
}

// on "dealloc" you need to release all your retained objects
// cocos2d-x:  destructor in cpp equals to dealloc in objc
HelloWorld::~HelloWorld()
{
	if (_targets)
	{
		_targets->release();
		_targets = NULL;
	}

	if (_projectiles)
	{
		_projectiles->release();
		_projectiles = NULL;
	}
}

void HelloWorld::menuCloseCallback(NSObject* pSender)
{
	CCDirector::getSharedDirector()->end();
}
