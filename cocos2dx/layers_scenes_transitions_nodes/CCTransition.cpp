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

#include "CCTransition.h"
#include "CCCamera.h"
#include "cgpointextension.h"
#include "CCDirector.h"
#include "CCTouchDispatcher.h"
#include "CCIntervalAction.h"
#include "CCInstantAction.h"
#include "CCEaseAction.h"
#include "CCCameraAction.h"
#include "CCLayer.h"
#include "CCGridAction.h"
namespace   cocos2d {

enum {
	kSceneFade = 0xFADEFADE,
};

#define IMPLEMENT_TRANSITIONWITHDURATION(_Type)\
    _Type* _Type::transitionWithDuration(ccTime t, CCScene* scene)\
{\
    _Type* pScene = new _Type();\
    pScene->initWithDuration(t, scene);\
    pScene->autorelease();\
    return pScene;\
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
	pScene->initWithDuration(t,scene);
	pScene->autorelease();
	return pScene;
}

CCTransitionScene * CCTransitionScene::initWithDuration(ccTime t, CCScene *scene)
{
	NSAssert( scene != NULL, "Argument scene must be non-nil");

	if (__super::init())
	{
		m_fDuration = t;

		// retain
		m_pInScene = scene;
		m_pInScene->retain();
		m_pOutScene = CCDirector::getSharedDirector()->getRunningScene();
		m_pOutScene->retain();

		NSAssert( m_pInScene != m_pOutScene, "Incoming scene must be different from the outgoing scene" );

		// disable events while transitions
		CCTouchDispatcher::getSharedDispatcher()->setDispatchEvents(false);
		this->sceneOrder();

		return this;
	}
	else
	{
		return NULL;
	}
}

void CCTransitionScene::sceneOrder()
{
	m_bIsInSceneOnTop = true;
}

void CCTransitionScene::draw()
{
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
	// [self unschedule:_cmd]; 
	// "_cmd" is a local variable automatically defined in a method 
	// that contains the selector for the method
	this->unschedule(schedule_selector(CCTransitionScene::setNewScene));
	CCDirector *director = CCDirector::getSharedDirector();
	// Before replacing, save the "send cleanup to scene"
	m_bIsSendCleanupToScene = director->isSendCleanupToScene();
	director->replaceScene(m_pInScene);
	// enable events while transitions
	CCTouchDispatcher::getSharedDispatcher()->setDispatchEvents(true);
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
	__super::onEnter();
	m_pInScene->onEnter();
	// outScene should not receive the onEnter callback
}

// custom onExit
void CCTransitionScene::onExit()
{
	__super::onExit();
	m_pOutScene->onExit();

	// inScene should not receive the onExit callback
	// only the onEnterTransitionDidFinish
	m_pInScene->onEnterTransitionDidFinish();
}

// custom cleanup
void CCTransitionScene::cleanup()
{
	__super::cleanup();

	if( m_bIsSendCleanupToScene )
		m_pOutScene->cleanup();
}

//
// Oriented Transition
//
CCOrientedTransitionScene::CCOrientedTransitionScene()
{
}
CCOrientedTransitionScene::~CCOrientedTransitionScene()
{
}

CCOrientedTransitionScene * CCOrientedTransitionScene::transitionWithDuration(ccTime t, CCScene *scene, tOrientation orientation)
{
	CCOrientedTransitionScene * pScene = new CCOrientedTransitionScene();
	pScene->initWithDuration(t,scene,orientation);
	pScene->autorelease();
	return pScene;
}

CCOrientedTransitionScene * CCOrientedTransitionScene::initWithDuration(ccTime t, CCScene *scene, tOrientation orientation)
{
	if ( __super::initWithDuration(t, scene) )
	{
		m_eOrientation = orientation;
	}
	return this;
}

//
// RotoZoom
//
CCRotoZoomTransition::CCRotoZoomTransition()
{
}
CCRotoZoomTransition::~CCRotoZoomTransition()
{
}

void CCRotoZoomTransition:: onEnter()
{
	__super::onEnter();

	m_pInScene->setScale(0.001f);
	m_pOutScene->setScale(1.0f);

	m_pInScene->setAnchorPoint(ccp(0.5f, 0.5f));
	m_pOutScene->setAnchorPoint(ccp(0.5f, 0.5f));

	CCIntervalAction *rotozoom = static_cast<CCIntervalAction*>(CCSequence::actions
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

IMPLEMENT_TRANSITIONWITHDURATION(CCRotoZoomTransition)


//
// JumpZoom
//
CCJumpZoomTransition::CCJumpZoomTransition()
{
}
CCJumpZoomTransition::~CCJumpZoomTransition()
{
}

void CCJumpZoomTransition::onEnter()
{
	__super::onEnter();
	CGSize s = CCDirector::getSharedDirector()->getWinSize();

	m_pInScene->setScale(0.5f);
	m_pInScene->setPosition(ccp(s.width, 0));
	m_pInScene->setAnchorPoint(ccp(0.5f, 0.5f));
	m_pOutScene->setAnchorPoint(ccp(0.5f, 0.5f));

	CCIntervalAction *jump = CCJumpBy::actionWithDuration(m_fDuration/4, ccp(-s.width,0), s.width/4, 2);
	CCIntervalAction *scaleIn = CCScaleTo::actionWithDuration(m_fDuration/4, 1.0f);
	CCIntervalAction *scaleOut = CCScaleTo::actionWithDuration(m_fDuration/4, 0.5f);

	CCIntervalAction *jumpZoomOut = dynamic_cast<CCIntervalAction*>(CCSequence::actions(scaleOut, jump, NULL));
	CCIntervalAction *jumpZoomIn = dynamic_cast<CCIntervalAction*>(CCSequence::actions(jump, scaleIn, NULL));

	CCIntervalAction *delay = CCDelayTime::actionWithDuration(m_fDuration/2);

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

IMPLEMENT_TRANSITIONWITHDURATION(CCJumpZoomTransition)

//
// MoveInL
//
CCMoveInLTransition::CCMoveInLTransition()
{
}
CCMoveInLTransition::~CCMoveInLTransition()
{
}

void CCMoveInLTransition::onEnter()
{
	__super::onEnter();
	this->initScenes();

	CCIntervalAction *a = this->action();

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
 
CCIntervalAction* CCMoveInLTransition::action()
{
	return CCMoveTo::actionWithDuration(m_fDuration, ccp(0,0));
}

CCIntervalAction* CCMoveInLTransition::easeActionWithAction(CCIntervalAction* action)
{
	return CCEaseOut::actionWithAction(action, 2.0f);
//	return [EaseElasticOut actionWithAction:action period:0.4f];
}

void CCMoveInLTransition::initScenes()
{
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	m_pInScene->setPosition( ccp(-s.width,0) );
}

IMPLEMENT_TRANSITIONWITHDURATION(CCMoveInLTransition)

//
// MoveInR
//
CCMoveInRTransition::CCMoveInRTransition()
{
}
CCMoveInRTransition::~CCMoveInRTransition()
{
}

void CCMoveInRTransition::initScenes()
{
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	m_pInScene->setPosition( ccp(s.width,0) );
}

IMPLEMENT_TRANSITIONWITHDURATION(CCMoveInRTransition)

//
// MoveInT
//
CCMoveInTTransition::CCMoveInTTransition()
{
}
CCMoveInTTransition::~CCMoveInTTransition()
{
}

void CCMoveInTTransition::initScenes()
{
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	m_pInScene->setPosition( ccp(0,s.height) );
}

IMPLEMENT_TRANSITIONWITHDURATION(CCMoveInTTransition)

//
// MoveInB
//
CCMoveInBTransition::CCMoveInBTransition()
{
}
CCMoveInBTransition::~CCMoveInBTransition()
{
}

void CCMoveInBTransition::initScenes()
{
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	m_pInScene->setPosition( ccp(0,-s.height) );
}

IMPLEMENT_TRANSITIONWITHDURATION(CCMoveInBTransition)


//
// SlideInL
//

// The adjust factor is needed to prevent issue #442
// One solution is to use DONT_RENDER_IN_SUBPIXELS images, but NO
// The other issue is that in some transitions (and I don't know why)
// the order should be reversed (In in top of Out or vice-versa).
#define ADJUST_FACTOR 0.5f
CCSlideInLTransition::CCSlideInLTransition()
{
}
CCSlideInLTransition::~CCSlideInLTransition()
{
}

void CCSlideInLTransition::onEnter()
{
	__super::onEnter();
	this->initScenes();

	CCIntervalAction *in = this->action();
	CCIntervalAction *out = this->action();

	CCIntervalAction* inAction = easeActionWithAction(in);
	CCIntervalAction* outAction = (CCIntervalAction*)CCSequence::actions
	(
		easeActionWithAction(out),
		CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)), 
		NULL
	);
	m_pInScene->runAction(inAction);
	m_pOutScene->runAction(outAction);
}

void CCSlideInLTransition::sceneOrder()
{
	m_bIsInSceneOnTop = false;
}

void CCSlideInLTransition:: initScenes()
{
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	m_pInScene->setPosition( ccp(-(s.width-ADJUST_FACTOR),0) );
}

CCIntervalAction* CCSlideInLTransition::action()
{
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	return CCMoveBy::actionWithDuration(m_fDuration, ccp(s.width-ADJUST_FACTOR,0));
}

CCIntervalAction* CCSlideInLTransition::easeActionWithAction(CCIntervalAction* action)
{
	return CCEaseOut::actionWithAction(action, 2.0f);
//	return [EaseElasticOut actionWithAction:action period:0.4f];
}

IMPLEMENT_TRANSITIONWITHDURATION(CCSlideInLTransition)


//
// SlideInR
//
CCSlideInRTransition::CCSlideInRTransition()
{
}
CCSlideInRTransition::~CCSlideInRTransition()
{
}

void CCSlideInRTransition::sceneOrder()
{
	m_bIsInSceneOnTop = true;
}

void CCSlideInRTransition::initScenes()
{
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	m_pInScene->setPosition( ccp(s.width-ADJUST_FACTOR,0) );
}


CCIntervalAction* CCSlideInRTransition:: action()
{
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	return CCMoveBy::actionWithDuration(m_fDuration, ccp(-(s.width-ADJUST_FACTOR),0));
}

IMPLEMENT_TRANSITIONWITHDURATION(CCSlideInRTransition)


//
// SlideInT
//
CCSlideInTTransition::CCSlideInTTransition()
{
}
CCSlideInTTransition::~CCSlideInTTransition()
{
}

void CCSlideInTTransition::sceneOrder()
{
	m_bIsInSceneOnTop = false;
}

void CCSlideInTTransition::initScenes()
{
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	m_pInScene->setPosition( ccp(0,s.height-ADJUST_FACTOR) );
}


CCIntervalAction* CCSlideInTTransition::action()
{
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	return CCMoveBy::actionWithDuration(m_fDuration, ccp(0,-(s.height-ADJUST_FACTOR)));
}

IMPLEMENT_TRANSITIONWITHDURATION(CCSlideInTTransition)

//
// SlideInB
//
CCSlideInBTransition::CCSlideInBTransition()
{
}
CCSlideInBTransition::~CCSlideInBTransition()
{
}

void CCSlideInBTransition::sceneOrder()
{
	m_bIsInSceneOnTop = true;
}

void CCSlideInBTransition:: initScenes()
{
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	m_pInScene->setPosition( ccp(0,-(s.height-ADJUST_FACTOR)) );
}


CCIntervalAction* CCSlideInBTransition:: action()
{
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	return CCMoveBy::actionWithDuration(m_fDuration, ccp(0,s.height-ADJUST_FACTOR));
}

IMPLEMENT_TRANSITIONWITHDURATION(CCSlideInBTransition)

//
// ShrinkGrow Transition
//
CCShrinkGrowTransition::CCShrinkGrowTransition()
{
}
CCShrinkGrowTransition::~CCShrinkGrowTransition()
{
}

void CCShrinkGrowTransition::onEnter()
{
	__super::onEnter();

	m_pInScene->setScale(0.001f);
	m_pOutScene->setScale(1.0f);

	m_pInScene->setAnchorPoint(ccp(2/3.0f,0.5f));
	m_pOutScene->setAnchorPoint(ccp(1/3.0f,0.5f));	

	CCIntervalAction* scaleOut = CCScaleTo::actionWithDuration(m_fDuration, 0.01f);
	CCIntervalAction* scaleIn = CCScaleTo::actionWithDuration(m_fDuration, 1.0f);

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
CCIntervalAction* CCShrinkGrowTransition:: easeActionWithAction(CCIntervalAction* action)
{
	return CCEaseOut::actionWithAction(action, 2.0f);
//	return [EaseElasticOut actionWithAction:action period:0.3f];
}

IMPLEMENT_TRANSITIONWITHDURATION(CCShrinkGrowTransition)

//
// FlipX Transition
//
CCFlipXTransition::CCFlipXTransition()
{
}
CCFlipXTransition::~CCFlipXTransition()
{
}

void CCFlipXTransition::onEnter()
{
	__super::onEnter();

	CCIntervalAction *inA, *outA;
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

	inA = (CCIntervalAction*)CCSequence::actions
		(
			CCDelayTime::actionWithDuration(m_fDuration/2),
			CCShow::action(),
			CCOrbitCamera::actionWithDuration(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, 0, 0),
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)), 
			NULL
		);

	outA = (CCIntervalAction *)CCSequence::actions
		(
			CCOrbitCamera::actionWithDuration(m_fDuration/2, 1, 0, outAngleZ, outDeltaZ, 0, 0),
			CCHide::action(),
			CCDelayTime::actionWithDuration(m_fDuration/2),							
			NULL 
		);

	m_pInScene->runAction(inA);
	m_pOutScene->runAction(outA);
}

CCFlipXTransition* CCFlipXTransition::transitionWithDuration(ccTime t, CCScene* s, tOrientation o)
{
    CCFlipXTransition* pScene = new CCFlipXTransition();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

//
// FlipY Transition
//
CCFlipYTransition::CCFlipYTransition()
{
}
CCFlipYTransition::~CCFlipYTransition()
{
}

void CCFlipYTransition::onEnter()
{
	__super::onEnter();

	CCIntervalAction *inA, *outA;
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

	inA = (CCIntervalAction*)CCSequence::actions
		(
			CCDelayTime::actionWithDuration(m_fDuration/2),
			CCShow::action(),
			CCOrbitCamera::actionWithDuration(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, 90, 0),
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)), 
			NULL
		);
	outA = (CCIntervalAction*)CCSequence::actions
		(
			CCOrbitCamera::actionWithDuration(m_fDuration/2, 1, 0, outAngleZ, outDeltaZ, 90, 0),
			CCHide::action(),
			CCDelayTime::actionWithDuration(m_fDuration/2),							
			NULL
		);

	m_pInScene->runAction(inA);
	m_pOutScene->runAction(outA);

}

CCFlipYTransition* CCFlipYTransition::transitionWithDuration(ccTime t, CCScene* s, tOrientation o)
{
    CCFlipYTransition* pScene = new CCFlipYTransition();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

//
// FlipAngular Transition
//
CCFlipAngularTransition::CCFlipAngularTransition()
{
}
CCFlipAngularTransition::~CCFlipAngularTransition()
{
}

void CCFlipAngularTransition::onEnter()
{
	__super::onEnter();

	CCIntervalAction *inA, *outA;
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

	inA = (CCIntervalAction *)CCSequence::actions
		(
			CCDelayTime::actionWithDuration(m_fDuration/2),
			CCShow::action(),
			CCOrbitCamera::actionWithDuration(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, -45, 0),
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)), 
			NULL
		);
	outA = (CCIntervalAction *)CCSequence::actions
		(
			CCOrbitCamera::actionWithDuration(m_fDuration/2, 1, 0, outAngleZ, outDeltaZ, 45, 0),
			CCHide::action(),
			CCDelayTime::actionWithDuration(m_fDuration/2),							
			NULL
		);

	m_pInScene->runAction(inA);
	m_pOutScene->runAction(outA);
}

CCFlipAngularTransition* CCFlipAngularTransition::transitionWithDuration(ccTime t, CCScene* s, tOrientation o)
{
    CCFlipAngularTransition* pScene = new CCFlipAngularTransition();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

//
// ZoomFlipX Transition
//
CCZoomFlipXTransition::CCZoomFlipXTransition()
{
}
CCZoomFlipXTransition::~CCZoomFlipXTransition()
{
}

void CCZoomFlipXTransition::onEnter()
{
	__super::onEnter();

	CCIntervalAction *inA, *outA;
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
	inA = (CCIntervalAction *)CCSequence::actions
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
	outA = (CCIntervalAction *)CCSequence::actions
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

CCZoomFlipXTransition* CCZoomFlipXTransition::transitionWithDuration(ccTime t, CCScene* s, tOrientation o)
{
    CCZoomFlipXTransition* pScene = new CCZoomFlipXTransition();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

//
// ZoomFlipY Transition
//
CCZoomFlipYTransition::CCZoomFlipYTransition()
{
}
CCZoomFlipYTransition::~CCZoomFlipYTransition()
{
}

void CCZoomFlipYTransition::onEnter()
{
	__super::onEnter();

	CCIntervalAction *inA, *outA;
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

	inA = (CCIntervalAction *)CCSequence::actions
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

	outA = (CCIntervalAction *)CCSequence::actions
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

CCZoomFlipYTransition* CCZoomFlipYTransition::transitionWithDuration(ccTime t, CCScene* s, tOrientation o)
{
    CCZoomFlipYTransition* pScene = new CCZoomFlipYTransition();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

//
// ZoomFlipAngular Transition
//
CCZoomFlipAngularTransition::CCZoomFlipAngularTransition()
{
}
CCZoomFlipAngularTransition::~CCZoomFlipAngularTransition()
{
}


void CCZoomFlipAngularTransition::onEnter()
{
	__super::onEnter();

	CCIntervalAction *inA, *outA;
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

	inA = (CCIntervalAction *)CCSequence::actions
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
	outA = (CCIntervalAction *)CCSequence::actions
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

CCZoomFlipAngularTransition* CCZoomFlipAngularTransition::transitionWithDuration(ccTime t, CCScene* s, tOrientation o)
{
    CCZoomFlipAngularTransition* pScene = new CCZoomFlipAngularTransition();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

//
// Fade Transition
//
CCFadeTransition::CCFadeTransition()
{
}
CCFadeTransition::~CCFadeTransition()
{
}


CCFadeTransition * CCFadeTransition::transitionWithDuration(ccTime duration, CCScene *scene, ccColor3B color)
{
	CCFadeTransition * pTransition = new CCFadeTransition();
	pTransition->initWithDuration(duration, scene, color);
	pTransition->autorelease();
	return pTransition;
}

CCFadeTransition * CCFadeTransition::initWithDuration(ccTime duration, CCScene *scene, ccColor3B color)
{
	if (__super::initWithDuration(duration, scene))
	{
		m_tColor.r = color.r;
		m_tColor.g = color.g;
		m_tColor.b = color.b;
	}
	return this;
}

CCFadeTransition * CCFadeTransition::initWithDuration(ccTime t, CCScene *scene)
{
	this->initWithDuration(t, scene, ccBLACK);
	return this;
}

void CCFadeTransition :: onEnter()
{
	__super::onEnter();

	CCColorLayer* l = CCColorLayer::layerWithColor(m_tColor);
	m_pInScene->setIsVisible(false);

	addChild(l, 2, kSceneFade);
	CCNode* f = getChildByTag(kSceneFade);

	CCIntervalAction* a = (CCIntervalAction *)CCSequence::actions
		(
			CCFadeIn::actionWithDuration(m_fDuration/2),
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::hideOutShowIn)),//CCCallFunc::actionWithTarget:self selector:@selector(hideOutShowIn)],
			CCFadeOut::actionWithDuration(m_fDuration/2),
			CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)), //:self selector:@selector(finish)],
			NULL
		);
	f->runAction(a);
}

void CCFadeTransition::onExit()
{
	__super::onExit();
	this->removeChildByTag(kSceneFade, false);
}

//
// Cross Fade Transition
//
CCCrossFadeTransition::CCCrossFadeTransition()
{
}
CCCrossFadeTransition::~CCCrossFadeTransition()
{
}


void CCCrossFadeTransition:: draw()
{
	// override draw since both scenes (textures) are rendered in 1 scene
}

void CCCrossFadeTransition::onEnter()
{
	/** @todo ccrendertexture
	__super::onEnter();

	// create a transparent color layer
	// in which we are going to add our rendertextures
	ccColor4B  color = {0,0,0,0};
	CGSize size = CCDirector::getSharedDirector()->getWinSize();
	CCColorLayer* layer = CCColorLayer::layerWithColor(color);

	// create the first render texture for inScene
	CCRenderTexture* inTexture = CCRenderTexture::renderTextureWithWidth((int)size.width, (int)size.height);
	inTexture->getSprite()->setAnchorPoint( ccp(0.5f,0.5f) );
	inTexture->setPosition( ccp(size.width/2, size.height/2) );
	inTexture->setAnchorPoint( ccp(0.5f,0.5f) );

	// render inScene to its texturebuffer
	inTexture->begin();
	m_pInScene->visit();
	inTexture->end();

	// create the second render texture for outScene
	CCRenderTexture* outTexture = CCRenderTexture::renderTextureWithWidth((int)size.width, (int)size.height);
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
	addChild(layer, 2, kSceneFade);*/
}

// clean up on exit
void CCCrossFadeTransition::onExit()
{
	// remove our layer and release all containing objects 
	this->removeChildByTag(kSceneFade, false);
	__super::onExit();
}

CCCrossFadeTransition* CCCrossFadeTransition::transitionWithDuration(ccTime d, CCScene* s)
{
    CCCrossFadeTransition* Transition = new CCCrossFadeTransition();
    Transition->initWithDuration(d, s);
    Transition->autorelease();

    return Transition;
}

//
// TurnOffTilesTransition
//
CCTurnOffTilesTransition::CCTurnOffTilesTransition()
{
}
CCTurnOffTilesTransition::~CCTurnOffTilesTransition()
{
}


// override addScenes, and change the order
void CCTurnOffTilesTransition::sceneOrder()
{
	m_bIsInSceneOnTop = false;
}

void CCTurnOffTilesTransition::onEnter()
{
	/** @todo ccturnofftiles
	__super::onEnter();
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	float aspect = s.width / s.height;
	int x = (int)(12 * aspect);
	int y = 12;

	CCTurnOffTiles* toff = CCTurnOffTiles::actionWithSize( ccg(x,y), m_duration);
	CCIntervalAction* action = easeActionWithAction(toff);
	m_outScene->runAction(
		CCSequence::actions(
		action,
		CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)), 
		CCStopGrid::action(),
		NULL)
		);*/
	/** @todo
	[super onEnter];
	CGSize s = [[CCDirector sharedDirector] winSize];
	float aspect = s.width / s.height;
	int x = 12 * aspect;
	int y = 12;

	id toff = [CCTurnOffTiles actionWithSize: ccg(x,y) duration:duration];
	id action = [self easeActionWithAction:toff];
	[outScene runAction: [CCSequence actions: action,
		[CCCallFunc actionWithTarget:self selector:@selector(finish)],
		[CCStopGrid action],
		nil]
	];*/

}


CCIntervalAction* CCTurnOffTilesTransition:: easeActionWithAction(CCIntervalAction* action)
{
	return action;
}

IMPLEMENT_TRANSITIONWITHDURATION(CCTurnOffTilesTransition)

//
// SplitCols Transition
//
CCSplitColsTransition::CCSplitColsTransition()
{
}
CCSplitColsTransition::~CCSplitColsTransition()
{
}


void CCSplitColsTransition::onEnter()
{
	__super::onEnter();
	m_pInScene->setIsVisible(false);

	CCIntervalAction* split = action();
	CCIntervalAction* seq = (CCIntervalAction*)CCSequence::actions
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


CCIntervalAction* CCSplitColsTransition:: action()
{
	return NULL;
	/// @todo return [CCSplitCols actionWithCols:3 duration:duration/2.0f];
}


CCIntervalAction* CCSplitColsTransition::easeActionWithAction(CCIntervalAction * action)
{
	return CCEaseInOut::actionWithAction(action, 3.0f);
}

IMPLEMENT_TRANSITIONWITHDURATION(CCSplitColsTransition)


//
// SplitRows Transition
//
CCSplitRowsTransition::CCSplitRowsTransition()
{
}
CCSplitRowsTransition::~CCSplitRowsTransition()
{
}


CCIntervalAction* CCSplitRowsTransition::action()
{
	return NULL;
	/// @todo return [CCSplitRows actionWithRows:3 duration:duration/2.0f];
}

IMPLEMENT_TRANSITIONWITHDURATION(CCSplitRowsTransition)

//
// FadeTR Transition
//
CCFadeTRTransition::CCFadeTRTransition()
{
}
CCFadeTRTransition::~CCFadeTRTransition()
{
}


void CCFadeTRTransition::sceneOrder()
{
	m_bIsInSceneOnTop = false;
}

void CCFadeTRTransition::onEnter()
{
	__super::onEnter();

	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	float aspect = s.width / s.height;
	int x = (int)(12 * aspect);
	int y = 12;

	CCIntervalAction* action  = actionWithSize(ccg(x,y));

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


CCIntervalAction*  CCFadeTRTransition::actionWithSize(ccGridSize size)
{
	return NULL;
	/// @todo return [CCFadeOutTRTiles actionWithSize:v duration:duration];
}

CCIntervalAction* CCFadeTRTransition:: easeActionWithAction(CCIntervalAction* action)
{
	return action;
}

IMPLEMENT_TRANSITIONWITHDURATION(CCFadeTRTransition)


//
// FadeBL Transition
//

CCFadeBLTransition::CCFadeBLTransition()
{
}
CCFadeBLTransition::~CCFadeBLTransition()
{
}

CCIntervalAction*  CCFadeBLTransition::actionWithSize(ccGridSize size)
{
	return NULL;
	/// @todo return [CCFadeOutBLTiles actionWithSize:v duration:duration];
}

IMPLEMENT_TRANSITIONWITHDURATION(CCFadeBLTransition)

//
// FadeUp Transition
//
CCFadeUpTransition::CCFadeUpTransition()
{
}
CCFadeUpTransition::~CCFadeUpTransition()
{
}

CCIntervalAction* CCFadeUpTransition::actionWithSize(ccGridSize size)
{
	return NULL;
	/// @todo return [CCFadeOutUpTiles actionWithSize:v duration:duration];
}

IMPLEMENT_TRANSITIONWITHDURATION(CCFadeUpTransition)

//
// FadeDown Transition
//
CCFadeDownTransition::CCFadeDownTransition()
{
}
CCFadeDownTransition::~CCFadeDownTransition()
{
}

CCIntervalAction* CCFadeDownTransition::actionWithSize(ccGridSize size)
{
	return NULL;
	/// @todo return [CCFadeOutDownTiles actionWithSize:v duration:duration];
}

IMPLEMENT_TRANSITIONWITHDURATION(CCFadeDownTransition)

}//namespace   cocos2d 
