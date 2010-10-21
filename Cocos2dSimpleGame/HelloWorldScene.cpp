
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include <math.h>
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

void HelloWorld::spriteMoveFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
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

	CCSprite *target = CCSprite::spriteWithFile(ResInfo[4].ResName.c_str());

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
										ResInfo[0].ResName.c_str(), 
										ResInfo[1].ResName.c_str(), 
										this,
										menu_selector(HelloWorld::menuCloseCallback) );
	pCloseItem->setPosition( ccp( CCDirector::getSharedDirector()->getWinSize().width - 30, 30) );
	CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL); 	// create menu, it's an autorelease object
	pMenu->setPosition( CGPointZero );
	this->addChild(pMenu);


	/////////////////////////////
	// add your code below

	// Enable touch events
	this->setIsTouchEnabled(true);

	// Initialize arrays
	_targets = new NSMutableArray<CCSprite*>;
	_projectiles = new NSMutableArray<CCSprite*>;

	// Get the dimensions of the window for calculation purposes
	CGSize winSize = CCDirector::getSharedDirector()->getWinSize();

	// Add the player to the middle of the screen along the y-axis, 
	// and as close to the left side edge as we can get
	// Remember that position is based on the anchor point, and by default the anchor
	// point is the middle of the object.
	CCSprite *player = CCSprite::spriteWithFile(ResInfo[2].ResName.c_str());
	player->setPosition( ccp(player->getContentSize().width / 2, winSize.height/2) );
	this->addChild(player);

	// Call game logic about every second
	this->schedule( schedule_selector(HelloWorld::gameLogic), 1.0 );
	this->schedule( schedule_selector(HelloWorld::update) );

	// Start up the background music
    SimpleAudioEngine::getSharedEngine()->SetBackgroundMusicVolume(40);
	SimpleAudioEngine::getSharedEngine()->playBackgroundMusic(SoundResInfo[0].FileName, true);

 	return true;
}

void HelloWorld::update(ccTime dt)
{
	NSMutableArray<CCSprite*> *projectilesToDelete = new NSMutableArray<CCSprite*>;
	NSMutableArray<CCSprite*>::NSMutableArrayIterator it, jt;

	for (it = _projectiles->begin(); it != _projectiles->end(); it++)
	{
		CCSprite *projectile = *it;

		CGRect projectileRect = CGRectMake(projectile->getPosition().x - (projectile->getContentSize().width/2),
						projectile->getPosition().y - (projectile->getContentSize().height/2),
						projectile->getContentSize().width,
						projectile->getContentSize().height);

		NSMutableArray<CCSprite*> *targetsToDelete = new NSMutableArray<CCSprite*>;

		for (jt = _targets->begin(); jt != _targets->end(); jt++)
		{
			CCSprite *target = *jt;

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
			CCSprite *target = *jt;

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
		CCSprite* projectile = *it;

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
	CCSprite *projectile = CCSprite::spriteWithFile(ResInfo[3].ResName.c_str());
	projectile->setPosition( ccp(20, winSize.height/2) );

	// Determinie offset of location to projectile
	float offX = location.x - projectile->getPosition().x;
	float offY = location.y - projectile->getPosition().y;

	// Bail out if we are shooting down or backwards
	if (offX <= 0) return;

	// Ok to add now - we've double checked position
	this->addChild(projectile);

	// Play a sound!
    // SimpleAudioEngine::getSharedEngine()->SetEffectsVolume(30);
    // SimpleAudioEngine::getSharedEngine()->playEffect(SoundResInfo[1].FileName);

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
,_projectilesDestroyed(0)
{
    SimpleAudioEngine::getSharedEngine()->preloadEffect(SoundResInfo[1].FileName);
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
