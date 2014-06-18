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
    m_strName = "SceneController";
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
    CCComController::onEnter();
    _fAddTargetTime = 1.0f;
    
    _targets = new CCArray;
    _projectiles = new CCArray;
   
    ((CCComAttribute*)(m_pOwner->getComponent("CCComAttribute")))->setInt("KillCount", 0);
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
	CCSprite *target = CCSprite::create("components/Target.png", CCRectMake(0,0,27,40));
    m_pOwner->addChild(target, 1, 2);
    
    target->addComponent(EnemyController::create());
	target->setTag(2);
    _targets->addObject(target);
}

void SceneController::spriteMoveFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
	m_pOwner->removeChild(sprite, true);
    
	if (sprite->getTag() == 2)  // target
	{
        _targets->removeObject(sprite);
		GameOverScene *gameOverScene = GameOverScene::create();
		gameOverScene->getLayer()->getLabel()->setString("You Lose :[");
		CCDirector::sharedDirector()->replaceScene(gameOverScene);
	}
	else if (sprite->getTag() == 3) 
	{
        _projectiles->removeObject(sprite);
	}
    
}

void SceneController::increaseKillCount()
{
    int nProjectilesDestroyed = ((CCComAttribute*)(m_pOwner->getComponent("CCComAttribute")))->getInt("KillCount");
    
    CCComAttribute *p = (CCComAttribute*)(m_pOwner->getComponent("CCComAttribute"));
    p->setInt("KillCount", ++nProjectilesDestroyed);

    if (nProjectilesDestroyed >= 5)
    {
            GameOverScene *gameOverScene = GameOverScene::create();
            gameOverScene->getLayer()->getLabel()->setString("You Win!");
            CCDirector::sharedDirector()->replaceScene(gameOverScene);
    }
}
