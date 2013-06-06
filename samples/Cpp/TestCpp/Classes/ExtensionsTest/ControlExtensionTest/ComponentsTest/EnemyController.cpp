/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "EnemyController.h"
#include "SceneController.h"

using namespace cocos2d;

EnemyController::EnemyController(void)
{
    m_strName = "EnemyController";
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
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	float minY = getOwner()->getContentSize().height/2;
	float maxY = winSize.height -  getOwner()->getContentSize().height/2;
	int rangeY = (int)(maxY - minY);
	// srand( TimGetTicks() );
	int actualY = ( rand() % rangeY ) + (int)minY;

	// Create the target slightly off-screen along the right edge,
	// and along a random position along the Y axis as calculated
	m_pOwner->setPosition(
		ccp(winSize.width + (getOwner()->getContentSize().width/2), 
            CCDirector::sharedDirector()->getVisibleOrigin().y + actualY) );
	

	// Determine speed of the target
	int minDuration = (int)2.0;
	int maxDuration = (int)4.0;
	int rangeDuration = maxDuration - minDuration;
	// srand( TimGetTicks() );
	int actualDuration = ( rand() % rangeDuration ) + minDuration;

	// Create the actions
	CCFiniteTimeAction* actionMove = CCMoveTo::create( (float)actualDuration,
                                            ccp(0 - getOwner()->getContentSize().width/2, actualY) );
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(getOwner()->getParent()->getComponent("SceneController"),
                                            callfuncN_selector(SceneController::spriteMoveFinished));
	m_pOwner->runAction( CCSequence::create(actionMove, actionMoveDone, NULL) );
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
    CCComponent *com = m_pOwner->getParent()->getComponent("SceneController");
    cocos2d::CCArray *_targets = ((SceneController*)com)->getTargets();
    _targets->removeObject(m_pOwner);
    m_pOwner->removeFromParentAndCleanup(true);
    ((SceneController*)com)->increaseKillCount();
}

