/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCRadialTransition.h"
#include "CCDirector.h"
#include "CCRenderTexture.h"
#include "CCInstantAction.h"
#include "CCProgressTimerActions.h"
#include "CGPointExtension.h"

namespace   cocos2d {

//#import "CCDirector.h"
//#import "CCRadialTransition.h"
//#import "CCRenderTexture.h"
//#import "CCLayer.h"
//#import "CCInstantAction.h"
//#import "Support/CGPointExtension.h"

enum {
	kSceneRadial = 0xc001,
};

CCRadialCCWTransition::CCRadialCCWTransition()
{
}
CCRadialCCWTransition::~CCRadialCCWTransition()
{
}

void CCRadialCCWTransition::sceneOrder()
{
	m_bIsInSceneOnTop = false;
}

CCProgressTimerType CCRadialCCWTransition::radialType()
{
	return kCCProgressTimerTypeRadialCCW;
}

void CCRadialCCWTransition::onEnter()
{
	__super::onEnter();
	// create a transparent color layer
	// in which we are going to add our rendertextures
	CGSize size = CCDirector::getSharedDirector()->getWinSize();

	// create the second render texture for outScene
	CCRenderTexture *outTexture = CCRenderTexture::renderTextureWithWidthAndHeight((int)size.width, (int)size.height);
	outTexture->getSprite()->setAnchorPoint(ccp(0.5f,0.5f));
	outTexture->setPosition(ccp(size.width/2, size.height/2));
	outTexture->setAnchorPoint(ccp(0.5f,0.5f));

	// render outScene to its texturebuffer
	outTexture->clear(0,0,0,1);
	outTexture->begin();
	m_pOutScene->visit();
	outTexture->end();

	//	Since we've passed the outScene to the texture we don't need it.
	this->hideOutShowIn();

	//	We need the texture in RenderTexture.
	CCProgressTimer *outNode = CCProgressTimer::progressWithTexture(outTexture->getSprite()->getTexture());
	// but it's flipped upside down so we flip the sprite
	outNode->getSprite()->setFlipY(true);
	//	Return the radial type that we want to use
	outNode->setType(radialType());
	outNode->setPercentage(100.f);
	outNode->setPosition(ccp(size.width/2, size.height/2));
	outNode->setAnchorPoint(ccp(0.5f,0.5f));

	// create the blend action
	CCAction * layerAction = CCSequence::actions
	(
		CCProgressFromTo::actionWithDuration(m_fDuration, 100.0f, 0.0f),
		CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)),
		NULL
	);
	// run the blend action
	outNode->runAction(layerAction);

	// add the layer (which contains our two rendertextures) to the scene
	this->addChild(outNode, 2, kSceneRadial);
}


// clean up on exit
void CCRadialCCWTransition::onExit()
{
	// remove our layer and release all containing objects 
	this->removeChildByTag(kSceneRadial, false);
	__super::onExit();
}

CCRadialCCWTransition* CCRadialCCWTransition::transitionWithDuration(ccTime t, CCScene* scene)
{
    CCRadialCCWTransition* pScene = new CCRadialCCWTransition();
    pScene->initWithDuration(t, scene);
    pScene->autorelease();

    return pScene;
}

CCProgressTimerType CCRadialCWTransition::radialType()
{
	return kCCProgressTimerTypeRadialCW;
}

CCRadialCWTransition* CCRadialCWTransition::transitionWithDuration(ccTime t, CCScene* scene)
{
    CCRadialCWTransition* pScene = new CCRadialCWTransition();
    pScene->initWithDuration(t, scene);
    pScene->autorelease();

    return pScene;
}

}//namespace   cocos2d 

