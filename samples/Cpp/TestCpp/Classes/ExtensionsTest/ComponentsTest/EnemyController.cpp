#include "EnemyController.h"
#include "SceneController.h"

using namespace cocos2d;

EnemyController::EnemyController(void)
{
    _name = "EnemyController";
}

EnemyController::~EnemyController(void)
{
}

bool EnemyController::init()
{
    return true;
}

void EnemyController::onEnter()
{
   // Determine where to spawn the target along the Y axis
	Size winSize = Director::getInstance()->getVisibleSize();
	float minY = getOwner()->getContentSize().height/2;
	float maxY = winSize.height -  getOwner()->getContentSize().height/2;
	int rangeY = (int)(maxY - minY);
	// srand( TimGetTicks() );
	int actualY = ( rand() % rangeY ) + (int)minY;

	// Create the target slightly off-screen along the right edge,
	// and along a random position along the Y axis as calculated
	_owner->setPosition(
		Point(winSize.width + (getOwner()->getContentSize().width/2), 
            Director::getInstance()->getVisibleOrigin().y + actualY) );
	

	// Determine speed of the target
	int minDuration = (int)2.0;
	int maxDuration = (int)4.0;
	int rangeDuration = maxDuration - minDuration;
	// srand( TimGetTicks() );
	int actualDuration = ( rand() % rangeDuration ) + minDuration;

	// Create the actions
	FiniteTimeAction* actionMove = MoveTo::create( (float)actualDuration,
                                            Point(0 - getOwner()->getContentSize().width/2, actualY) );
	FiniteTimeAction* actionMoveDone = CallFuncN::create(getOwner()->getParent()->getComponent("SceneController"),
                                            callfuncN_selector(SceneController::spriteMoveFinished));
	_owner->runAction( Sequence::create(actionMove, actionMoveDone, NULL) );
}

void EnemyController::onExit()
{
}

void EnemyController::update(float delta)
{

}

EnemyController* EnemyController::create(void)
{
    EnemyController * pRet = new EnemyController();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void EnemyController::die()
{
    Component *com = _owner->getParent()->getComponent("SceneController");
    cocos2d::Array *_targets = ((SceneController*)com)->getTargets();
    _targets->removeObject(_owner);
    _owner->removeFromParentAndCleanup(true);
    ((SceneController*)com)->increaseKillCount();
}

