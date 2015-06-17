#include "EnemyController.h"
#include "SceneController.h"

using namespace cocos2d;
using namespace cocostudio;

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

void EnemyController::onAdd()
{
    ComController::onAdd();
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
		Vec2(winSize.width + (getOwner()->getContentSize().width/2), 
            Director::getInstance()->getVisibleOrigin().y + actualY) );
	

	// Determine speed of the target
	int minDuration = 2;
	int maxDuration = 4;
	int rangeDuration = maxDuration - minDuration;
	// srand( TimGetTicks() );
	int actualDuration = ( rand() % rangeDuration ) + minDuration;

	// Create the actions
	FiniteTimeAction* actionMove = MoveTo::create( actualDuration,
                                            Vec2(0 - getOwner()->getContentSize().width/2, actualY) );
	FiniteTimeAction* actionMoveDone = CallFuncN::create(
                                         CC_CALLBACK_1(SceneController::spriteMoveFinished, static_cast<SceneController*>( getOwner()->getParent()->getComponent("SceneController") )));

	_owner->runAction( Sequence::create(actionMove, actionMoveDone, nullptr) );
}

void EnemyController::onRemove()
{
}

void EnemyController::update(float delta)
{

}

EnemyController* EnemyController::create(void)
{
    EnemyController * pRet = new (std::nothrow) EnemyController();
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
    auto com = _owner->getParent()->getComponent("SceneController");
    auto& targets = static_cast<SceneController*>(com)->getTargets();
    targets.eraseObject(_owner);
    _owner->removeFromParentAndCleanup(true);
    static_cast<SceneController*>(com)->increaseKillCount();
}

