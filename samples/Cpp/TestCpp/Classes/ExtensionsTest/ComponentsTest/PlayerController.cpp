#include "PlayerController.h"
#include "ComponentsTestScene.h"
#include "SceneController.h"
#include "ProjectileController.h"

using namespace cocos2d;
using namespace cocos2d::extension;

PlayerController::PlayerController(void)
{
    _name = "PlayerController";
}

PlayerController::~PlayerController(void)
{
}

bool PlayerController::init()
{
    return true;
}

void PlayerController::onEnter()
{
    setTouchEnabled(true);
}

void PlayerController::onExit()
{
    setTouchEnabled(false);
}

void PlayerController::update(float delta)
{

}

void PlayerController::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    // Choose one of the touches to work with
	CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
	CCPoint location = touch->getLocation();
    

	CCSprite *projectile = CCSprite::create("components/Projectile.png", CCRectMake(0, 0, 20, 20));
    _owner->getParent()->addChild(projectile, 1, 4);
    
    ProjectileController *com = ProjectileController::create();
    projectile->addComponent(com);
    com->move(location.x, location.y);

    ((CCComAudio*)(_owner->getComponent("Audio")))->playEffect("pew-pew-lei.wav");
}

PlayerController* PlayerController::create(void)
{
    PlayerController * pRet = new PlayerController();
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

