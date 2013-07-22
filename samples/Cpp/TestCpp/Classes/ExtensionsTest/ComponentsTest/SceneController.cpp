#include "SceneController.h"
#include "ComponentsTestScene.h"
#include "PlayerController.h"
#include "GameOverScene.h"
#include "EnemyController.h"

using namespace cocos2d;
using namespace cocos2d::extension;

SceneController::SceneController(void)
: _fAddTargetTime(0.0f)
, _fElapsedTime(0.0f)
, _targets(NULL)
, _projectiles(NULL)
{
    _name = "SceneController";
}

SceneController::~SceneController(void)
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

bool SceneController::init()
{
    return true;
}

void SceneController::onEnter()
{
    _fAddTargetTime = 1.0f;
    
    _targets = new Array;
    _projectiles = new Array;
   
    ((ComAudio*)(_owner->getComponent("Audio")))->playBackgroundMusic("background-music-aac.wav", true);
    ((ComAttribute*)(_owner->getComponent("ComAttribute")))->setInt("KillCount", 0);
}

void SceneController::onExit()
{


}

void SceneController::update(float delta)
{
//    return;
    _fElapsedTime += delta;
    if (_fElapsedTime > _fAddTargetTime)
    {
        addTarget();
        _fElapsedTime = 0.0f;
    }
}

SceneController* SceneController::create(void)
{
    SceneController * pRet = new SceneController();
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

void SceneController::addTarget()
{
	Sprite *target = Sprite::create("components/Target.png", Rect(0,0,27,40));
    _owner->addChild(target, 1, 2);
    
    target->addComponent(EnemyController::create());
	target->setTag(2);
    _targets->addObject(target);
}

void SceneController::spriteMoveFinished(Node* sender)
{
	Sprite *sprite = (Sprite *)sender;
	_owner->removeChild(sprite, true);
    
	if (sprite->getTag() == 2)  // target
	{
        _targets->removeObject(sprite);
		GameOverScene *gameOverScene = GameOverScene::create();
		gameOverScene->getLayer()->getLabel()->setString("You Lose :[");
		Director::getInstance()->replaceScene(gameOverScene);
	}
	else if (sprite->getTag() == 3) 
	{
        _projectiles->removeObject(sprite);
	}
    
}

void SceneController::increaseKillCount()
{
    int nProjectilesDestroyed = ((ComAttribute*)(_owner->getComponent("ComAttribute")))->getInt("KillCount");
    
    ComAttribute *p = (ComAttribute*)(_owner->getComponent("ComAttribute"));
    p->setInt("KillCount", ++nProjectilesDestroyed);

    if (nProjectilesDestroyed >= 5)
    {
            GameOverScene *gameOverScene = GameOverScene::create();
            gameOverScene->getLayer()->getLabel()->setString("You Win!");
            Director::getInstance()->replaceScene(gameOverScene);
    }
}
