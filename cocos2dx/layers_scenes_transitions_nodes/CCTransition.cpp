/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

#include "CCTransition.h"
#include "CCCamera.h"
#include "CCPointExtension.h"
#include "CCDirector.h"
#include "CCTouchDispatcher.h"
#include "CCActionInterval.h"
#include "CCActionInstant.h"
#include "CCActionEase.h"
#include "CCActionCamera.h"
#include "CCLayer.h"
#include "CCActionGrid.h"
#include "CCRenderTexture.h"
#include "CCActionTiledGrid.h"
namespace   cocos2d {

const unsigned int kSceneFade = 0xFADEFADE;

#define IMPLEMENT_TRANSITIONWITHDURATION(_Type)\
    _Type* _Type::transitionWithDuration(ccTime t, CCScene* scene)\
{\
    _Type* pScene = new _Type();\
	if(pScene && pScene->initWithDuration(t, scene)){\
    pScene->autorelease();\
	return pScene;}\
	CC_SAFE_DELETE(pScene);\
	return NULL;\
}



CCTransitionScene::CCTransitionScene()
{
}
CCTransitionScene::~CCTransitionScene()
{
	m_pInScene->release();
	m_pOutScene->release();
}

CCTransitionScene * CCTransitionScene::transitionWithDuration(ccTime t, CCScene *scene)
{
	CCTransitionScene * pScene = new CCTransitionScene();
	if(pScene && pScene->initWithDuration(t,scene))
	{
		pScene->autorelease();
		return pScene;
	}
	CC_SAFE_DELETE(pScene);
	return NULL;
}

bool CCTransitionScene::initWithDuration(ccTime t, CCScene *scene)
{
	CCAssert( scene != NULL, "Argument scene must be non-nil");

	if (CCScene::init())
	{
		m_fDuration = t;

		// retain
		m_pInScene = scene;
		m_pInScene->retain();
		m_pOutScene = CCDirector::sharedDirector()->getRunningScene();
		m_pOutScene->retain();

		CCAssert( m_pInScene != m_pOutScene, "Incoming scene must be different from the outgoing scene" );

		// disable events while transitions
		CCTouchDispatcher::sharedDispatcher()->setDispatchEvents(false);
		this->sceneOrder();

		return true;
	}
	else
	{
		return false;
	}
}

void CCTransitionScene::sceneOrder()
{
	m_bIsInSceneOnTop = true;
}

void CCTransitionScene::draw()
{
	CCScene::draw();

	if( m_bIsInSceneOnTop ) {
		m_pOutScene->visit();
		m_pInScene->visit();
	} else {
		m_pInScene->visit();
		m_pOutScene->visit();
	}
}

void CCTransitionScene::finish()
{
	// clean up 	
 	m_pInScene->setIsVisible(true);
 	m_pInScene->setPosition(ccp(0,0));
 	m_pInScene->setScale(1.0f);
 	m_pInScene->setRotation(0.0f);
 	m_pInScene->getCamera()->restore();
 
 	m_pOutScene->setIsVisible(false);
 	m_pOutScene->setPosition(ccp(0,0));
 	m_pOutScene->setScale(1.0f);
 	m_pOutScene->setRotation(0.0f);
 	m_pOutScene->getCamera()->restore();

	//[self schedule:@selector(setNewScene:) interval:0];
	this->schedule(schedule_selector(CCTransitionScene::setNewScene), 0);

}

void CCTransitionScene::setNewScene(ccTime dt)
{	
    CC_UNUSED_PARAM(dt);
	// [self unschedule:_cmd]; 
	// "_cmd" is a local variable automatically defined in a method 
	// that contains the selector for the method
	this->unschedule(schedule_selector(CCTransitionScene::setNewScene));
	CCDirector *director = CCDirector::sharedDirector();
	// Before replacing, save the "send cleanup to scene"
	m_bIsSendCleanupToScene = director->isSendCleanupToScene();
	director->replaceScene(m_pInScene);
	// enable events while transitions
	CCTouchDispatcher::sharedDispatcher()->setDispatchEvents(true);
	// issue #267
	m_pOutScene->setIsVisible(true);
}

void CCTransitionScene::hideOutShowIn()
{
	m_pInScene->setIsVisible(true);
	m_pOutScene->setIsVisible(false);
}


// custom onEnter
void CCTransitionScene::onEnter()
{
	CCScene::onEnter();
	m_pInScene->onEnter();
	// outScene should not receive the onEnter callback
}

// custom onExit
void CCTransitionScene::onExit()
{
	CCScene::onExit();
	m_pOutScene->onExit();

	// inScene should not receive the onExit callback
	// only the onEnterTransitionDidFinish
	m_pInScene->onEnterTransitionDidFinish();
}

// custom cleanup
void CCTransitionScene::cleanup()
{
	CCScene::cleanup();

	if( m_bIsSendCleanupToScene )
		m_pOutScene->cleanup();
}

//
// Oriented Transition
//
CCTransitionSceneOriented::CCTransitionSceneOriented()
{
}
CCTransitionSceneOriented::~CCTransitionSceneOriented()
{
}

CCTransitionSceneOriented * CCTransitionSceneOriented::transitionWithDuration(ccTime t, CCScene *scene, tOrientation orientation)
{
	CCTransitionSceneOriented * pScene = new CCTransitionSceneOriented();
	pScene->initWithDuration(t,scene,orientation);
	pScene->autorelease();
	return pScene;
}

bool CCTransitionSceneOriented::initWithDuration(ccTime t, CCScene *scene, tOrientation orientation)
{
	if ( CCTransitionScene::initWithDuration(t, scene) )
	{
		m_eOrientation = orientation;
	}
	return true;
}

//
// RotoZoom
//
CCTransitionRotoZoom::CCTransitionRotoZoom()
{
}
CCTransitionRotoZoom::~CCTransitionRotoZoom()
{
}

void CCTransitionRotoZoom:: onEnter()
{
	CCTransitionScene::onEnter();

	m_pInScene->setScale(0.001f);
	m_pOutScene->setScale(1.0f);

	m_pInScene->setAnchorPoint(ccp(0.5f, 0.5f));
	m_pOutScene->setAnchorPoint(ccp(0.5f, 0.5f));

	CCActionInterval *rotozoom = (CCActionInterval*)(CCSequence::actions
	(
		CCSpawn::actions
		(
			CCScaleBy::actionWithDuration(m_fDuration/2, 0.001f),
			CCRotateBy::actionWithDuration(m_fDuration/2, 360 * 2),
			NULL
		),
		CCDelayTime::actionWithDuration(m_fDuration/2),
		NULL
	));

	m_pOutScene->runAction(rotozoom);
	m_pInScene->runAction
	(
		CCSequence::actions
		(
			rotozoom->reverse(),
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)),
			NULL
		)
	);
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionRotoZoom)


//
// JumpZoom
//
CCTransitionJumpZoom::CCTransitionJumpZoom()
{
}
CCTransitionJumpZoom::~CCTransitionJumpZoom()
{
}

void CCTransitionJumpZoom::onEnter()
{
	CCTransitionScene::onEnter();
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	m_pInScene->setScale(0.5f);
	m_pInScene->setPosition(ccp(s.width, 0));
	m_pInScene->setAnchorPoint(ccp(0.5f, 0.5f));
	m_pOutScene->setAnchorPoint(ccp(0.5f, 0.5f));

	CCActionInterval *jump = CCJumpBy::actionWithDuration(m_fDuration/4, ccp(-s.width,0), s.width/4, 2);
	CCActionInterval *scaleIn = CCScaleTo::actionWithDuration(m_fDuration/4, 1.0f);
	CCActionInterval *scaleOut = CCScaleTo::actionWithDuration(m_fDuration/4, 0.5f);

	CCActionInterval *jumpZoomOut = (CCActionInterval*)(CCSequence::actions(scaleOut, jump, NULL));
	CCActionInterval *jumpZoomIn = (CCActionInterval*)(CCSequence::actions(jump, scaleIn, NULL));

	CCActionInterval *delay = CCDelayTime::actionWithDuration(m_fDuration/2);

	m_pOutScene->runAction(jumpZoomOut);
	m_pInScene->runAction
	(
		CCSequence::actions
		(
			delay,
			jumpZoomIn,
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)),
			NULL
		)
	);
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionJumpZoom)

//
// MoveInL
//
CCTransitionMoveInL::CCTransitionMoveInL()
{
}
CCTransitionMoveInL::~CCTransitionMoveInL()
{
}

void CCTransitionMoveInL::onEnter()
{
	CCTransitionScene::onEnter();
	this->initScenes();

	CCActionInterval *a = this->action();

	m_pInScene->runAction
	(
		CCSequence::actions
		(
			this->easeActionWithAction(a),
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)),
			NULL
		)
	);
}
 
CCActionInterval* CCTransitionMoveInL::action()
{
	return CCMoveTo::actionWithDuration(m_fDuration, ccp(0,0));
}

CCActionInterval* CCTransitionMoveInL::easeActionWithAction(CCActionInterval* action)
{
	return CCEaseOut::actionWithAction(action, 2.0f);
//	return [EaseElasticOut actionWithAction:action period:0.4f];
}

void CCTransitionMoveInL::initScenes()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pInScene->setPosition( ccp(-s.width,0) );
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionMoveInL)

//
// MoveInR
//
CCTransitionMoveInR::CCTransitionMoveInR()
{
}
CCTransitionMoveInR::~CCTransitionMoveInR()
{
}

void CCTransitionMoveInR::initScenes()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pInScene->setPosition( ccp(s.width,0) );
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionMoveInR)

//
// MoveInT
//
CCTransitionMoveInT::CCTransitionMoveInT()
{
}
CCTransitionMoveInT::~CCTransitionMoveInT()
{
}

void CCTransitionMoveInT::initScenes()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pInScene->setPosition( ccp(0,s.height) );
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionMoveInT)

//
// MoveInB
//
CCTransitionMoveInB::CCTransitionMoveInB()
{
}
CCTransitionMoveInB::~CCTransitionMoveInB()
{
}

void CCTransitionMoveInB::initScenes()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pInScene->setPosition( ccp(0,-s.height) );
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionMoveInB)


//
// SlideInL
//

// The adjust factor is needed to prevent issue #442
// One solution is to use DONT_RENDER_IN_SUBPIXELS images, but NO
// The other issue is that in some transitions (and I don't know why)
// the order should be reversed (In in top of Out or vice-versa).
#define ADJUST_FACTOR 0.5f
CCTransitionSlideInL::CCTransitionSlideInL()
{
}
CCTransitionSlideInL::~CCTransitionSlideInL()
{
}

void CCTransitionSlideInL::onEnter()
{
	CCTransitionScene::onEnter();
	this->initScenes();

	CCActionInterval *in = this->action();
	CCActionInterval *out = this->action();

	CCActionInterval* inAction = easeActionWithAction(in);
	CCActionInterval* outAction = (CCActionInterval*)CCSequence::actions
	(
		easeActionWithAction(out),
		CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)), 
		NULL
	);
	m_pInScene->runAction(inAction);
	m_pOutScene->runAction(outAction);
}

void CCTransitionSlideInL::sceneOrder()
{
	m_bIsInSceneOnTop = false;
}

void CCTransitionSlideInL:: initScenes()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pInScene->setPosition( ccp(-(s.width-ADJUST_FACTOR),0) );
}

CCActionInterval* CCTransitionSlideInL::action()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	return CCMoveBy::actionWithDuration(m_fDuration, ccp(s.width-ADJUST_FACTOR,0));
}

CCActionInterval* CCTransitionSlideInL::easeActionWithAction(CCActionInterval* action)
{
	return CCEaseOut::actionWithAction(action, 2.0f);
//	return [EaseElasticOut actionWithAction:action period:0.4f];
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionSlideInL)


//
// SlideInR
//
CCTransitionSlideInR::CCTransitionSlideInR()
{
}
CCTransitionSlideInR::~CCTransitionSlideInR()
{
}

void CCTransitionSlideInR::sceneOrder()
{
	m_bIsInSceneOnTop = true;
}

void CCTransitionSlideInR::initScenes()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pInScene->setPosition( ccp(s.width-ADJUST_FACTOR,0) );
}


CCActionInterval* CCTransitionSlideInR:: action()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	return CCMoveBy::actionWithDuration(m_fDuration, ccp(-(s.width-ADJUST_FACTOR),0));
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionSlideInR)


//
// SlideInT
//
CCTransitionSlideInT::CCTransitionSlideInT()
{
}
CCTransitionSlideInT::~CCTransitionSlideInT()
{
}

void CCTransitionSlideInT::sceneOrder()
{
	m_bIsInSceneOnTop = false;
}

void CCTransitionSlideInT::initScenes()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pInScene->setPosition( ccp(0,s.height-ADJUST_FACTOR) );
}


CCActionInterval* CCTransitionSlideInT::action()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	return CCMoveBy::actionWithDuration(m_fDuration, ccp(0,-(s.height-ADJUST_FACTOR)));
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionSlideInT)

//
// SlideInB
//
CCTransitionSlideInB::CCTransitionSlideInB()
{
}
CCTransitionSlideInB::~CCTransitionSlideInB()
{
}

void CCTransitionSlideInB::sceneOrder()
{
	m_bIsInSceneOnTop = true;
}

void CCTransitionSlideInB:: initScenes()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pInScene->setPosition( ccp(0,-(s.height-ADJUST_FACTOR)) );
}


CCActionInterval* CCTransitionSlideInB:: action()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	return CCMoveBy::actionWithDuration(m_fDuration, ccp(0,s.height-ADJUST_FACTOR));
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionSlideInB)

//
// ShrinkGrow Transition
//
CCTransitionShrinkGrow::CCTransitionShrinkGrow()
{
}
CCTransitionShrinkGrow::~CCTransitionShrinkGrow()
{
}

void CCTransitionShrinkGrow::onEnter()
{
	CCTransitionScene::onEnter();

	m_pInScene->setScale(0.001f);
	m_pOutScene->setScale(1.0f);

	m_pInScene->setAnchorPoint(ccp(2/3.0f,0.5f));
	m_pOutScene->setAnchorPoint(ccp(1/3.0f,0.5f));	

	CCActionInterval* scaleOut = CCScaleTo::actionWithDuration(m_fDuration, 0.01f);
	CCActionInterval* scaleIn = CCScaleTo::actionWithDuration(m_fDuration, 1.0f);

	m_pInScene->runAction(this->easeActionWithAction(scaleIn));
	m_pOutScene->runAction
	(
		CCSequence::actions
		(
			this->easeActionWithAction(scaleOut),
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)), 
			NULL
		)
	);
}
CCActionInterval* CCTransitionShrinkGrow:: easeActionWithAction(CCActionInterval* action)
{
	return CCEaseOut::actionWithAction(action, 2.0f);
//	return [EaseElasticOut actionWithAction:action period:0.3f];
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionShrinkGrow)

//
// FlipX Transition
//
CCTransitionFlipX::CCTransitionFlipX()
{
}
CCTransitionFlipX::~CCTransitionFlipX()
{
}

void CCTransitionFlipX::onEnter()
{
	CCTransitionSceneOriented::onEnter();

	CCActionInterval *inA, *outA;
	m_pInScene->setIsVisible(false);

	float inDeltaZ, inAngleZ;
	float outDeltaZ, outAngleZ;

	if( m_eOrientation == kOrientationRightOver )
	{
		inDeltaZ = 90;
		inAngleZ = 270;
		outDeltaZ = 90;
		outAngleZ = 0;
	}
	else
	{
		inDeltaZ = -90;
		inAngleZ = 90;
		outDeltaZ = -90;
		outAngleZ = 0;
	}

	inA = (CCActionInterval*)CCSequence::actions
		(
			CCDelayTime::actionWithDuration(m_fDuration/2),
			CCShow::action(),
			CCOrbitCamera::actionWithDuration(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, 0, 0),
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)), 
			NULL
		);

	outA = (CCActionInterval *)CCSequence::actions
		(
			CCOrbitCamera::actionWithDuration(m_fDuration/2, 1, 0, outAngleZ, outDeltaZ, 0, 0),
			CCHide::action(),
			CCDelayTime::actionWithDuration(m_fDuration/2),							
			NULL 
		);

	m_pInScene->runAction(inA);
	m_pOutScene->runAction(outA);
}

CCTransitionFlipX* CCTransitionFlipX::transitionWithDuration(ccTime t, CCScene* s, tOrientation o)
{
    CCTransitionFlipX* pScene = new CCTransitionFlipX();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

//
// FlipY Transition
//
CCTransitionFlipY::CCTransitionFlipY()
{
}
CCTransitionFlipY::~CCTransitionFlipY()
{
}

void CCTransitionFlipY::onEnter()
{
	CCTransitionSceneOriented::onEnter();

	CCActionInterval *inA, *outA;
	m_pInScene->setIsVisible(false);

	float inDeltaZ, inAngleZ;
	float outDeltaZ, outAngleZ;

	if( m_eOrientation == kOrientationUpOver ) 
	{
		inDeltaZ = 90;
		inAngleZ = 270;
		outDeltaZ = 90;
		outAngleZ = 0;
	} 
	else 
	{
		inDeltaZ = -90;
		inAngleZ = 90;
		outDeltaZ = -90;
		outAngleZ = 0;
	}

	inA = (CCActionInterval*)CCSequence::actions
		(
			CCDelayTime::actionWithDuration(m_fDuration/2),
			CCShow::action(),
			CCOrbitCamera::actionWithDuration(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, 90, 0),
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)), 
			NULL
		);
	outA = (CCActionInterval*)CCSequence::actions
		(
			CCOrbitCamera::actionWithDuration(m_fDuration/2, 1, 0, outAngleZ, outDeltaZ, 90, 0),
			CCHide::action(),
			CCDelayTime::actionWithDuration(m_fDuration/2),							
			NULL
		);

	m_pInScene->runAction(inA);
	m_pOutScene->runAction(outA);

}

CCTransitionFlipY* CCTransitionFlipY::transitionWithDuration(ccTime t, CCScene* s, tOrientation o)
{
    CCTransitionFlipY* pScene = new CCTransitionFlipY();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

//
// FlipAngular Transition
//
CCTransitionFlipAngular::CCTransitionFlipAngular()
{
}
CCTransitionFlipAngular::~CCTransitionFlipAngular()
{
}

void CCTransitionFlipAngular::onEnter()
{
	CCTransitionSceneOriented::onEnter();

	CCActionInterval *inA, *outA;
	m_pInScene->setIsVisible(false);

	float inDeltaZ, inAngleZ;
	float outDeltaZ, outAngleZ;

	if( m_eOrientation == kOrientationRightOver ) 
	{
		inDeltaZ = 90;
		inAngleZ = 270;
		outDeltaZ = 90;
		outAngleZ = 0;
	} 
	else 
	{
		inDeltaZ = -90;
		inAngleZ = 90;
		outDeltaZ = -90;
		outAngleZ = 0;
	}

	inA = (CCActionInterval *)CCSequence::actions
		(
			CCDelayTime::actionWithDuration(m_fDuration/2),
			CCShow::action(),
			CCOrbitCamera::actionWithDuration(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, -45, 0),
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)), 
			NULL
		);
	outA = (CCActionInterval *)CCSequence::actions
		(
			CCOrbitCamera::actionWithDuration(m_fDuration/2, 1, 0, outAngleZ, outDeltaZ, 45, 0),
			CCHide::action(),
			CCDelayTime::actionWithDuration(m_fDuration/2),							
			NULL
		);

	m_pInScene->runAction(inA);
	m_pOutScene->runAction(outA);
}

CCTransitionFlipAngular* CCTransitionFlipAngular::transitionWithDuration(ccTime t, CCScene* s, tOrientation o)
{
    CCTransitionFlipAngular* pScene = new CCTransitionFlipAngular();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

//
// ZoomFlipX Transition
//
CCTransitionZoomFlipX::CCTransitionZoomFlipX()
{
}
CCTransitionZoomFlipX::~CCTransitionZoomFlipX()
{
}

void CCTransitionZoomFlipX::onEnter()
{
	CCTransitionSceneOriented::onEnter();

	CCActionInterval *inA, *outA;
	m_pInScene->setIsVisible(false);

	float inDeltaZ, inAngleZ;
	float outDeltaZ, outAngleZ;

	if( m_eOrientation == kOrientationRightOver ) {
		inDeltaZ = 90;
		inAngleZ = 270;
		outDeltaZ = 90;
		outAngleZ = 0;
	} 
	else 
	{
		inDeltaZ = -90;
		inAngleZ = 90;
		outDeltaZ = -90;
		outAngleZ = 0;
	}
	inA = (CCActionInterval *)CCSequence::actions
		(
			CCDelayTime::actionWithDuration(m_fDuration/2),
			CCSpawn::actions
			(
				CCOrbitCamera::actionWithDuration(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, 0, 0),
				CCScaleTo::actionWithDuration(m_fDuration/2, 1),
				CCShow::action(),
				NULL
			),
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)),
			NULL
		);
	outA = (CCActionInterval *)CCSequence::actions
		(
			CCSpawn::actions
			(
				CCOrbitCamera::actionWithDuration(m_fDuration/2, 1, 0, outAngleZ, outDeltaZ, 0, 0),
				CCScaleTo::actionWithDuration(m_fDuration/2, 0.5f),
				NULL
			),
			CCHide::action(),
			CCDelayTime::actionWithDuration(m_fDuration/2),							
			NULL
		);

	m_pInScene->setScale(0.5f);
	m_pInScene->runAction(inA);
	m_pOutScene->runAction(outA);
}

CCTransitionZoomFlipX* CCTransitionZoomFlipX::transitionWithDuration(ccTime t, CCScene* s, tOrientation o)
{
    CCTransitionZoomFlipX* pScene = new CCTransitionZoomFlipX();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

//
// ZoomFlipY Transition
//
CCTransitionZoomFlipY::CCTransitionZoomFlipY()
{
}
CCTransitionZoomFlipY::~CCTransitionZoomFlipY()
{
}

void CCTransitionZoomFlipY::onEnter()
{
	CCTransitionSceneOriented::onEnter();

	CCActionInterval *inA, *outA;
	m_pInScene->setIsVisible(false);

	float inDeltaZ, inAngleZ;
	float outDeltaZ, outAngleZ;

	if( m_eOrientation== kOrientationUpOver ) {
		inDeltaZ = 90;
		inAngleZ = 270;
		outDeltaZ = 90;
		outAngleZ = 0;
	} else {
		inDeltaZ = -90;
		inAngleZ = 90;
		outDeltaZ = -90;
		outAngleZ = 0;
	}

	inA = (CCActionInterval *)CCSequence::actions
		(
			CCDelayTime::actionWithDuration(m_fDuration/2),
			CCSpawn::actions
			(
				CCOrbitCamera::actionWithDuration(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, 90, 0),
				CCScaleTo::actionWithDuration(m_fDuration/2, 1),
				CCShow::action(),
				NULL
			),
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)),
			NULL
		);

	outA = (CCActionInterval *)CCSequence::actions
		(
			CCSpawn::actions
			(
				CCOrbitCamera::actionWithDuration(m_fDuration/2, 1, 0, outAngleZ, outDeltaZ, 90, 0),
				CCScaleTo::actionWithDuration(m_fDuration/2, 0.5f),
				NULL
			),							
			CCHide::action(),
			CCDelayTime::actionWithDuration(m_fDuration/2),
			NULL
		);

	m_pInScene->setScale(0.5f);
	m_pInScene->runAction(inA);
	m_pOutScene->runAction(outA);
}

CCTransitionZoomFlipY* CCTransitionZoomFlipY::transitionWithDuration(ccTime t, CCScene* s, tOrientation o)
{
    CCTransitionZoomFlipY* pScene = new CCTransitionZoomFlipY();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

//
// ZoomFlipAngular Transition
//
CCTransitionZoomFlipAngular::CCTransitionZoomFlipAngular()
{
}
CCTransitionZoomFlipAngular::~CCTransitionZoomFlipAngular()
{
}


void CCTransitionZoomFlipAngular::onEnter()
{
	CCTransitionSceneOriented::onEnter();

	CCActionInterval *inA, *outA;
	m_pInScene->setIsVisible(false);

	float inDeltaZ, inAngleZ;
	float outDeltaZ, outAngleZ;

	if( m_eOrientation == kOrientationRightOver ) {
		inDeltaZ = 90;
		inAngleZ = 270;
		outDeltaZ = 90;
		outAngleZ = 0;
	} 
	else 
	{
		inDeltaZ = -90;
		inAngleZ = 90;
		outDeltaZ = -90;
		outAngleZ = 0;
	}

	inA = (CCActionInterval *)CCSequence::actions
		(
			CCDelayTime::actionWithDuration(m_fDuration/2),
			CCSpawn::actions
			(
				CCOrbitCamera::actionWithDuration(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, -45, 0),
				CCScaleTo::actionWithDuration(m_fDuration/2, 1),
				CCShow::action(),
				NULL
			),
			CCShow::action(),
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)),
			NULL
		);
	outA = (CCActionInterval *)CCSequence::actions
		(
			CCSpawn::actions
			(
				CCOrbitCamera::actionWithDuration(m_fDuration/2, 1, 0 , outAngleZ, outDeltaZ, 45, 0),
				CCScaleTo::actionWithDuration(m_fDuration/2, 0.5f),
				NULL
			),							
			CCHide::action(),
			CCDelayTime::actionWithDuration(m_fDuration/2),							
			NULL
		);

	m_pInScene->setScale(0.5f);
	m_pInScene->runAction(inA);
	m_pOutScene->runAction(outA);
}

CCTransitionZoomFlipAngular* CCTransitionZoomFlipAngular::transitionWithDuration(ccTime t, CCScene* s, tOrientation o)
{
    CCTransitionZoomFlipAngular* pScene = new CCTransitionZoomFlipAngular();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

//
// Fade Transition
//
CCTransitionFade::CCTransitionFade()
{
}
CCTransitionFade::~CCTransitionFade()
{
}


CCTransitionFade * CCTransitionFade::transitionWithDuration(ccTime duration, CCScene *scene, const ccColor3B& color)
{
	CCTransitionFade * pTransition = new CCTransitionFade();
	pTransition->initWithDuration(duration, scene, color);
	pTransition->autorelease();
	return pTransition;
}

bool CCTransitionFade::initWithDuration(ccTime duration, CCScene *scene, const ccColor3B& color)
{
	if (CCTransitionScene::initWithDuration(duration, scene))
	{
		m_tColor.r = color.r;
		m_tColor.g = color.g;
		m_tColor.b = color.b;
		m_tColor.a = 0;
	}
	return true;
}

bool CCTransitionFade::initWithDuration(ccTime t, CCScene *scene)
{
	this->initWithDuration(t, scene, ccBLACK);
	return true;
}

void CCTransitionFade :: onEnter()
{
	CCTransitionScene::onEnter();

	CCLayerColor* l = CCLayerColor::layerWithColor(m_tColor);
	m_pInScene->setIsVisible(false);

	addChild(l, 2, kSceneFade);
	CCNode* f = getChildByTag(kSceneFade);

	CCActionInterval* a = (CCActionInterval *)CCSequence::actions
		(
			CCFadeIn::actionWithDuration(m_fDuration/2),
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::hideOutShowIn)),//CCCallFunc::actionWithTarget:self selector:@selector(hideOutShowIn)],
			CCFadeOut::actionWithDuration(m_fDuration/2),
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)), //:self selector:@selector(finish)],
			NULL
		);
	f->runAction(a);
}

void CCTransitionFade::onExit()
{
	CCTransitionScene::onExit();
	this->removeChildByTag(kSceneFade, false);
}

//
// Cross Fade Transition
//
CCTransitionCrossFade::CCTransitionCrossFade()
{
}
CCTransitionCrossFade::~CCTransitionCrossFade()
{
}


void CCTransitionCrossFade:: draw()
{
	// override draw since both scenes (textures) are rendered in 1 scene
}

void CCTransitionCrossFade::onEnter()
{
	CCTransitionScene::onEnter();

	// create a transparent color layer
	// in which we are going to add our rendertextures
	ccColor4B  color = {0,0,0,0};
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCLayerColor* layer = CCLayerColor::layerWithColor(color);

	// create the first render texture for inScene
	CCRenderTexture* inTexture = CCRenderTexture::renderTextureWithWidthAndHeight((int)size.width, (int)size.height);

	if (NULL == inTexture)
	{
		return;
	}

	inTexture->getSprite()->setAnchorPoint( ccp(0.5f,0.5f) );
	inTexture->setPosition( ccp(size.width/2, size.height/2) );
	inTexture->setAnchorPoint( ccp(0.5f,0.5f) );

	// render inScene to its texturebuffer
	inTexture->begin();
	m_pInScene->visit();
	inTexture->end();

	// create the second render texture for outScene
	CCRenderTexture* outTexture = CCRenderTexture::renderTextureWithWidthAndHeight((int)size.width, (int)size.height);
	outTexture->getSprite()->setAnchorPoint( ccp(0.5f,0.5f) );
	outTexture->setPosition( ccp(size.width/2, size.height/2) );
	outTexture->setAnchorPoint( ccp(0.5f,0.5f) );

	// render outScene to its texturebuffer
	outTexture->begin();
	m_pOutScene->visit();
	outTexture->end();

	// create blend functions

	ccBlendFunc blend1 = {GL_ONE, GL_ONE}; // inScene will lay on background and will not be used with alpha
	ccBlendFunc blend2 = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}; // we are going to blend outScene via alpha 

	// set blendfunctions
	inTexture->getSprite()->setBlendFunc(blend1);
	outTexture->getSprite()->setBlendFunc(blend2);	

	// add render textures to the layer
	layer->addChild(inTexture);
	layer->addChild(outTexture);

	// initial opacity:
	inTexture->getSprite()->setOpacity(255);
	outTexture->getSprite()->setOpacity(255);

	// create the blend action
	CCAction* layerAction = CCSequence::actions
	(
		CCFadeTo::actionWithDuration(m_fDuration, 0),
		CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::hideOutShowIn)),
		CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)),
		NULL
	);


	// run the blend action
	outTexture->getSprite()->runAction( layerAction );

	// add the layer (which contains our two rendertextures) to the scene
	addChild(layer, 2, kSceneFade);
}

// clean up on exit
void CCTransitionCrossFade::onExit()
{
	// remove our layer and release all containing objects 
	this->removeChildByTag(kSceneFade, false);
	CCTransitionScene::onExit();
}

CCTransitionCrossFade* CCTransitionCrossFade::transitionWithDuration(ccTime d, CCScene* s)
{
    CCTransitionCrossFade* Transition = new CCTransitionCrossFade();
    Transition->initWithDuration(d, s);
    Transition->autorelease();

    return Transition;
}

//
// TurnOffTilesTransition
//
CCTransitionTurnOffTiles::CCTransitionTurnOffTiles()
{
}
CCTransitionTurnOffTiles::~CCTransitionTurnOffTiles()
{
}


// override addScenes, and change the order
void CCTransitionTurnOffTiles::sceneOrder()
{
	m_bIsInSceneOnTop = false;
}

void CCTransitionTurnOffTiles::onEnter()
{
	CCTransitionScene::onEnter();
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	float aspect = s.width / s.height;
	int x = (int)(12 * aspect);
	int y = 12;

	CCTurnOffTiles* toff = CCTurnOffTiles::actionWithSize( ccg(x,y), m_fDuration);
	CCActionInterval* action = easeActionWithAction(toff);
	m_pOutScene->runAction
	(
		CCSequence::actions
		(
			action,
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)), 
			CCStopGrid::action(),
			NULL
		)
	);
}


CCActionInterval* CCTransitionTurnOffTiles:: easeActionWithAction(CCActionInterval* action)
{
	return action;
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionTurnOffTiles)

//
// SplitCols Transition
//
CCTransitionSplitCols::CCTransitionSplitCols()
{
}
CCTransitionSplitCols::~CCTransitionSplitCols()
{
}


void CCTransitionSplitCols::onEnter()
{
	CCTransitionScene::onEnter();
	m_pInScene->setIsVisible(false);

	CCActionInterval* split = action();
	CCActionInterval* seq = (CCActionInterval*)CCSequence::actions
	(
		split,
		CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::hideOutShowIn)),
		split->reverse(),
		NULL
	);

	this->runAction
	( 
		CCSequence::actions
		(
			easeActionWithAction(seq),
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)),
			CCStopGrid::action(),
			NULL
		)
	);
}


CCActionInterval* CCTransitionSplitCols:: action()
{
	return CCSplitCols::actionWithCols(3, m_fDuration/2.0f);
}


CCActionInterval* CCTransitionSplitCols::easeActionWithAction(CCActionInterval * action)
{
	return CCEaseInOut::actionWithAction(action, 3.0f);
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionSplitCols)


//
// SplitRows Transition
//
CCTransitionSplitRows::CCTransitionSplitRows()
{
}
CCTransitionSplitRows::~CCTransitionSplitRows()
{
}


CCActionInterval* CCTransitionSplitRows::action()
{
	return CCSplitRows::actionWithRows(3, m_fDuration/2.0f);
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionSplitRows)

//
// FadeTR Transition
//
CCTransitionFadeTR::CCTransitionFadeTR()
{
}
CCTransitionFadeTR::~CCTransitionFadeTR()
{
}


void CCTransitionFadeTR::sceneOrder()
{
	m_bIsInSceneOnTop = false;
}

void CCTransitionFadeTR::onEnter()
{
	CCTransitionScene::onEnter();

	CCSize s = CCDirector::sharedDirector()->getWinSize();
	float aspect = s.width / s.height;
	int x = (int)(12 * aspect);
	int y = 12;

	CCActionInterval* action  = actionWithSize(ccg(x,y));

	m_pOutScene->runAction
	(
		CCSequence::actions
		(
			easeActionWithAction(action),
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)), 
			CCStopGrid::action(),
			NULL
		)
	);
}


CCActionInterval*  CCTransitionFadeTR::actionWithSize(const ccGridSize& size)
{
	return CCFadeOutTRTiles::actionWithSize(size, m_fDuration);
}

CCActionInterval* CCTransitionFadeTR:: easeActionWithAction(CCActionInterval* action)
{
	return action;
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionFadeTR)


//
// FadeBL Transition
//

CCTransitionFadeBL::CCTransitionFadeBL()
{
}
CCTransitionFadeBL::~CCTransitionFadeBL()
{
}

CCActionInterval*  CCTransitionFadeBL::actionWithSize(const ccGridSize& size)
{
	return CCFadeOutBLTiles::actionWithSize(size, m_fDuration);
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionFadeBL)

//
// FadeUp Transition
//
CCTransitionFadeUp::CCTransitionFadeUp()
{
}
CCTransitionFadeUp::~CCTransitionFadeUp()
{
}

CCActionInterval* CCTransitionFadeUp::actionWithSize(const ccGridSize& size)
{
	return CCFadeOutUpTiles::actionWithSize(size, m_fDuration);
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionFadeUp)

//
// FadeDown Transition
//
CCTransitionFadeDown::CCTransitionFadeDown()
{
}
CCTransitionFadeDown::~CCTransitionFadeDown()
{
}

CCActionInterval* CCTransitionFadeDown::actionWithSize(const ccGridSize& size)
{
	return CCFadeOutDownTiles::actionWithSize(size, m_fDuration);
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTransitionFadeDown)

}//namespace   cocos2d 
