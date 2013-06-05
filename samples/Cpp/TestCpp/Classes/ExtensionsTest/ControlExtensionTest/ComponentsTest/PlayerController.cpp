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

#include "PlayerController.h"
#include "ComponentsTestScene.h"
#include "SceneController.h"
#include "ProjectileController.h"

using namespace cocos2d;
using namespace cocos2d::extension;

PlayerController::PlayerController(void)
{
    m_strName = "PlayerController";
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
    m_pOwner->getParent()->addChild(projectile, 1, 4);
    
    ProjectileController *com = ProjectileController::create();
    projectile->addComponent(com);
    com->move(location.x, location.y);

    ((CCComAudio*)(m_pOwner->getComponent("Audio")))->playEffect("pew-pew-lei.wav");
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

