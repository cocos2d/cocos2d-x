/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2009 Lam Pham
Copyright (c) 2012 Ricardo Quesada

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


#include "CCTransitionProgress.h"
#include "CCDirector.h"
#include "CCRenderTexture.h"
#include "CCLayer.h"
#include "CCActionInstant.h"
#include "CCProgressTimer.h"
#include "CCActionProgressTimer.h"
#include "CCPointExtension.h"

NS_CC_BEGIN

enum {
	kCCSceneRadial = 0xc001,
};

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionProgress)

CCTransitionProgress::CCTransitionProgress()
: to_(0.0f)
, from_(0.0f)
, sceneToBeModified_(NULL)
{

}

// CCTransitionProgress
void CCTransitionProgress::onEnter()
{
    CCTransitionScene::onEnter();

	setupTransition();
	
	// create a transparent color layer
	// in which we are going to add our rendertextures
    CCSize size = CCDirector::sharedDirector()->getWinSize();

	// create the second render texture for outScene
    CCRenderTexture *texture = CCRenderTexture::renderTextureWithWidthAndHeight(size.width, size.height);
	texture->getSprite()->setAnchorPoint(ccp(0.5f,0.5f));
	texture->setPosition(ccp(size.width/2, size.height/2));
	texture->setAnchorPoint(ccp(0.5f,0.5f));

	// render outScene to its texturebuffer
	texture->clear(0, 0, 0, 1);
	texture->begin();
	sceneToBeModified_->visit();
	texture->end();


	//	Since we've passed the outScene to the texture we don't need it.
	if( sceneToBeModified_ == m_pOutScene )
    {
		hideOutShowIn();
    }
	//	We need the texture in RenderTexture.
	CCProgressTimer *pNode = progressTimerNodeWithRenderTexture(texture);

	// create the blend action
    CCActionInterval* layerAction = (CCActionInterval*)CCSequence::actions(
        CCProgressFromTo::actionWithDuration(m_fDuration, from_, to_),
        CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionProgress::finish)), 
        NULL);
	// run the blend action
	pNode->runAction(layerAction);

	// add the layer (which contains our two rendertextures) to the scene
	addChild(pNode, 2, kCCSceneRadial);
}

// clean up on exit
void CCTransitionProgress::onExit()
{
	// remove our layer and release all containing objects
	removeChildByTag(kCCSceneRadial, false);
    CCTransitionScene::onExit();
}

void CCTransitionProgress::sceneOrder()
{
	m_bIsInSceneOnTop = false;
}

void CCTransitionProgress::setupTransition()
{
	sceneToBeModified_ = m_pOutScene;
	from_ = 100;
	to_ = 0;
}

CCProgressTimer* CCTransitionProgress::progressTimerNodeWithRenderTexture(CCRenderTexture* texture)
{
	CCAssert(false, "override me - abstract class");
	return NULL;
}


// CCTransitionProgressRadialCCW
IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionProgressRadialCCW)

CCProgressTimer* CCTransitionProgressRadialCCW::progressTimerNodeWithRenderTexture(CCRenderTexture* texture)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCProgressTimer* pNode = CCProgressTimer::progressWithSprite(texture->getSprite());

	// but it is flipped upside down so we flip the sprite
	pNode->getSprite()->setFlipY(true);
	pNode->setType(kCCProgressTimerTypeRadial);

	//	Return the radial type that we want to use
	pNode->setIsReverseDirection(false);
	pNode->setPercentage(100);
	pNode->setPosition(ccp(size.width/2, size.height/2));
	pNode->setAnchorPoint(ccp(0.5f,0.5f));
	
	return pNode;
}

// CCTransitionProgressRadialCW

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionProgressRadialCW)

CCProgressTimer* CCTransitionProgressRadialCW::progressTimerNodeWithRenderTexture(CCRenderTexture* texture)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	
	CCProgressTimer* pNode = CCProgressTimer::progressWithSprite(texture->getSprite());
	
	// but it is flipped upside down so we flip the sprite
	pNode->getSprite()->setFlipY(true);
	pNode->setType( kCCProgressTimerTypeRadial );
	
	//	Return the radial type that we want to use
	pNode->setIsReverseDirection(true);
	pNode->setPercentage(100);
	pNode->setPosition(ccp(size.width/2, size.height/2));
	pNode->setAnchorPoint(ccp(0.5f,0.5f));
	
	return pNode;
}

// CCTransitionProgressHorizontal

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionProgressHorizontal)

CCProgressTimer* CCTransitionProgressHorizontal::progressTimerNodeWithRenderTexture(CCRenderTexture* texture)
{	
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCProgressTimer* pNode = CCProgressTimer::progressWithSprite(texture->getSprite());
	
	// but it is flipped upside down so we flip the sprite
	pNode->getSprite()->setFlipY(true);
	pNode->setType( kCCProgressTimerTypeBar);
	
	pNode->setMidpoint(ccp(1, 0));
	pNode->setBarChangeRate(ccp(1,0));
	
	pNode->setPercentage(100);
	pNode->setPosition(ccp(size.width/2, size.height/2));
	pNode->setAnchorPoint(ccp(0.5f,0.5f));

	return pNode;
}

// CCTransitionProgressVertical

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionProgressVertical)

CCProgressTimer* CCTransitionProgressVertical::progressTimerNodeWithRenderTexture(CCRenderTexture* texture)
{	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	
	CCProgressTimer* pNode = CCProgressTimer::progressWithSprite(texture->getSprite());
	
	// but it is flipped upside down so we flip the sprite
	pNode->getSprite()->setFlipY(true);
	pNode->setType(kCCProgressTimerTypeBar);
	
	pNode->setMidpoint(ccp(0, 0));
	pNode->setBarChangeRate(ccp(0,1));
	
	pNode->setPercentage(100);
	pNode->setPosition(ccp(size.width/2, size.height/2));
	pNode->setAnchorPoint(ccp(0.5f,0.5f));
	
	return pNode;
}


// CCTransitionProgressInOut

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionProgressInOut)

void CCTransitionProgressInOut::sceneOrder()
{
    m_bIsInSceneOnTop = false;
}

void CCTransitionProgressInOut::setupTransition()
{
	sceneToBeModified_ = m_pInScene;
	from_ = 0;
	to_ = 100;	
}

CCProgressTimer* CCTransitionProgressInOut::progressTimerNodeWithRenderTexture(CCRenderTexture* texture)
{	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	
	CCProgressTimer* pNode = CCProgressTimer::progressWithSprite(texture->getSprite());
	
	// but it is flipped upside down so we flip the sprite
	pNode->getSprite()->setFlipY(true);
	pNode->setType( kCCProgressTimerTypeBar);
	
	pNode->setMidpoint(ccp(0.5f, 0.5f));
	pNode->setBarChangeRate(ccp(1, 1));
	
	pNode->setPercentage(0);
	pNode->setPosition(ccp(size.width/2, size.height/2));
	pNode->setAnchorPoint(ccp(0.5f,0.5f));
	
	return pNode;
}


// CCTransitionProgressOutIn

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionProgressOutIn)

CCProgressTimer* CCTransitionProgressOutIn::progressTimerNodeWithRenderTexture(CCRenderTexture* texture)
{	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	
	CCProgressTimer* pNode = CCProgressTimer::progressWithSprite(texture->getSprite());
	
	// but it is flipped upside down so we flip the sprite
	pNode->getSprite()->setFlipY(true);
	pNode->setType( kCCProgressTimerTypeBar );
	
	pNode->setMidpoint(ccp(0.5f, 0.5f));
	pNode->setBarChangeRate(ccp(1, 1));
	
	pNode->setPercentage(100);
	pNode->setPosition(ccp(size.width/2, size.height/2));
	pNode->setAnchorPoint(ccp(0.5f,0.5f));
	
	return pNode;
}

NS_CC_END

