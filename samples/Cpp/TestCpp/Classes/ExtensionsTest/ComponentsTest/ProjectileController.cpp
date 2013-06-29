#include "ProjectileController.h"
#include "SceneController.h"
#include "EnemyController.h"

using namespace cocos2d;

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
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    _owner->setPosition( ccp(origin.x+20, origin.y+winSize.height/2) );
	_owner->setTag(3);
    CCComponent *com = _owner->getParent()->getComponent("SceneController");
    ((SceneController*)com)->getProjectiles()->addObject(_owner);
}

void ProjectileController::onExit()
{

}

void ProjectileController::update(float delta)
{
    CCComponent *com = _owner->getParent()->getComponent("SceneController");
    cocos2d::CCArray *_targets = ((SceneController*)com)->getTargets();
    
    CCSprite *projectile = dynamic_cast<CCSprite*>(_owner);
    CCRect projectileRect = CCRectMake(
			projectile->getPosition().x - (projectile->getContentSize().width/2),
			projectile->getPosition().y - (projectile->getContentSize().height/2),
			projectile->getContentSize().width,
			projectile->getContentSize().height);

    CCArray* targetsToDelete =new CCArray;
    CCObject* jt = NULL;
    CCARRAY_FOREACH(_targets, jt)
    {
        CCSprite *target = dynamic_cast<CCSprite*>(jt);
        CCRect targetRect = CCRectMake(
            target->getPosition().x - (target->getContentSize().width/2),
            target->getPosition().y - (target->getContentSize().height/2),
            target->getContentSize().width,
            target->getContentSize().height);

        // if (CCRect::CCRectIntersectsRect(projectileRect, targetRect))
        if (projectileRect.intersectsRect(targetRect))
        {
            targetsToDelete->addObject(target);
        }
    }
    
    CCARRAY_FOREACH(targetsToDelete, jt)
    {
        CCSprite *target = dynamic_cast<CCSprite*>(jt);
        ((EnemyController*)(target->getComponent("EnemyController")))->die();
    }
    
    bool isDied = targetsToDelete->count();
   
    targetsToDelete->release();
    
    if (isDied)
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


void ProjectileController::move(float flocationX, float flocationY)
{
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
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
	CCPoint realDest = ccp(realX, realY);

	// Determine the length of how far we're shooting
	float offRealX = realX - _owner->getPosition().x;
	float offRealY = realY - _owner->getPosition().y;
	float length = sqrtf((offRealX * offRealX) + (offRealY*offRealY));
	float velocity = 480/1; // 480pixels/1sec
	float realMoveDuration = length/velocity;

	// Move projectile to actual endpoint
	_owner->runAction( CCSequence::create(
		CCMoveTo::create(realMoveDuration, realDest),
		CCCallFuncN::create(getOwner()->getParent()->getComponent("SceneController"),
                            callfuncN_selector(SceneController::spriteMoveFinished)),
        NULL) );

}

void ProjectileController::die()
{
    CCComponent *com = _owner->getParent()->getComponent("SceneController");
    cocos2d::CCArray *_projectiles = ((SceneController*)com)->getProjectiles();
    _projectiles->removeObject(_owner);
    _owner->removeFromParentAndCleanup(true);
}
