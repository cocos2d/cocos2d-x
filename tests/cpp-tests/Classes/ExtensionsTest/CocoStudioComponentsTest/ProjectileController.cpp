#include "ProjectileController.h"
#include "SceneController.h"
#include "EnemyController.h"

using namespace cocos2d;
using namespace cocostudio;

ProjectileController::ProjectileController(void)
{
    _name = "ProjectileController";
}

ProjectileController::~ProjectileController(void)
{
}

bool ProjectileController::init()
{
    return true;
}

void ProjectileController::onEnter()
{
    ComController::onEnter();
    auto winSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    _owner->setPosition( Point(origin.x+20, origin.y+winSize.height/2) );
	_owner->setTag(3);
    auto com = _owner->getParent()->getComponent("SceneController");
    static_cast<SceneController*>(com)->getProjectiles().pushBack(_owner);
}

void ProjectileController::onExit()
{

}

void ProjectileController::update(float delta)
{
    auto com = _owner->getParent()->getComponent("SceneController");
    auto _targets = ((SceneController*)com)->getTargets();
    
    auto projectile = dynamic_cast<Sprite*>(_owner);
    auto projectileRect = Rect(
			projectile->getPosition().x - (projectile->getContentSize().width/2),
			projectile->getPosition().y - (projectile->getContentSize().height/2),
			projectile->getContentSize().width,
			projectile->getContentSize().height);

    std::vector<Node*> targetsToDelete;
    targetsToDelete.reserve(20);
    
    for (const auto& target : _targets)
    {
        Rect targetRect = Rect(
            target->getPosition().x - (target->getContentSize().width/2),
            target->getPosition().y - (target->getContentSize().height/2),
            target->getContentSize().width,
            target->getContentSize().height);

        // if (Rect::RectIntersectsRect(projectileRect, targetRect))
        if (projectileRect.intersectsRect(targetRect))
        {
            targetsToDelete.push_back(target);
        }
    }
    
    for (const auto& t : targetsToDelete)
    {
        static_cast<EnemyController*>(t->getComponent("EnemyController"))->die();
    }
    
    if (!targetsToDelete.empty())
    {
        die();
    }
}

ProjectileController* ProjectileController::create(void)
{
    ProjectileController * pRet = new ProjectileController();
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

void freeFunction( Node *ignore )
{
    log("hello");
}

void ProjectileController::move(float flocationX, float flocationY)
{
    auto winSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    // Determinie offset of location to projectile
	float offX = flocationX - _owner->getPosition().x;
	float offY = flocationY - _owner->getPosition().y;

	// Bail out if we are shooting down or backwards
	if (offX <= 0) return;

	// Ok to add now - we've double checked position
	

	// Determine where we wish to shoot the projectile to
	float realX = origin.x + winSize.width + (_owner->getContentSize().width/2);
	float ratio = offY / offX;
	float realY = (realX * ratio) + _owner->getPosition().y;
	Point realDest = Point(realX, realY);

	// Determine the length of how far we're shooting
	float offRealX = realX - _owner->getPosition().x;
	float offRealY = realY - _owner->getPosition().y;
	float length = sqrtf((offRealX * offRealX) + (offRealY*offRealY));
	float velocity = 480/1; // 480pixels/1sec
	float realMoveDuration = length/velocity;

    auto callfunc = CallFuncN::create(
          CC_CALLBACK_1(
                SceneController::spriteMoveFinished,
                static_cast<SceneController*>( getOwner()->getParent()->getComponent("SceneController")
      ) ) );

	// Move projectile to actual endpoint
	_owner->runAction(
          Sequence::create(
               MoveTo::create(realMoveDuration, realDest),
               callfunc,
               NULL)
          );
}

void ProjectileController::die()
{
    auto com = _owner->getParent()->getComponent("SceneController");
    auto& _projectiles = static_cast<SceneController*>(com)->getProjectiles();
    _projectiles.eraseObject(_owner);
    _owner->removeFromParentAndCleanup(true);
}
