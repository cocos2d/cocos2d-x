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
#include "../support/cgpointextension.h"


enum {
	kSceneFade = 0xFADEFADE,
};

CCTransitionScene::CCTransitionScene()
{
	/// @todo
}
CCTransitionScene::~CCTransitionScene()
{
	m_pInScene->release();
	m_pOutScene->release();
}

CCTransitionScene * CCTransitionScene::transitionWithDurationAndScene(ccTime t, CCScene *scene)
{
/// @todo	return [[[self alloc] initWithDuration:t scene:s] autorelease];
	CCTransitionScene * pScene = new CCTransitionScene();
	pScene->initWithDurationAndScene(t,scene);
	pScene->autorelease();
	return pScene;
}

CCTransitionScene * CCTransitionScene::initWithDurationAndScene(ccTime t, CCScene *scene)
{
	/** @todo
	NSAssert( s != nil, @"Argument scene must be non-nil");

	if( (self=[super init]) ) {

		duration = t;

		// retain
		inScene = [s retain];
		outScene = [[CCDirector sharedDirector] runningScene];
		[outScene retain];

		NSAssert( inScene != outScene, @"Incoming scene must be different from the outgoing scene" );

		// disable events while transitions
		[[CCTouchDispatcher sharedDispatcher] setDispatchEvents: NO];

		[self sceneOrder];
	}
	return self;*/
	return NULL;
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
	/** @todo
	// clean up 	
// 	m_pInScene->setIsVisible(true);
// 	m_pInScene->setPosition(ccp(0,0));
// 	m_pInScene->setScale(1.0f);
// 	m_pInScene->setRotation(0.0f);
// 	m_pInScene->getCamera()->restore();
// 
// 	m_pOutScene->setIsVisible(false);
// 	m_pOutScene->setPosition(ccp(0,0));
// 	m_pOutScene->setScale(1.0f);
// 	m_pOutScene->setRotation(0.0f);
// 	m_pOutScene->getCamera()->restore();

	this->schedule(&CCTransitionScene::setNewScene, 0);
//	[self schedule:@selector(setNewScene:) interval:0];*/

}

void CCTransitionScene::setNewScene(ccTime dt)
{	
	/** @todo
	[self unschedule:_cmd];

	CCDirector *director = [CCDirector sharedDirector];

	// Before replacing, save the "send cleanup to scene"
	sendCleanupToScene = [director sendCleanupToScene];

	[director replaceScene: inScene];

	// enable events while transitions
	[[CCTouchDispatcher sharedDispatcher] setDispatchEvents: YES];

	// issue #267
	[outScene setVisible:YES];	*/
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
/// @todo
}
CCOrientedTransitionScene::~CCOrientedTransitionScene()
{
/// @todo
}

CCOrientedTransitionScene * CCOrientedTransitionScene::transitionWithDurationAndScene(ccTime t, CCScene *scene, tOrientation orientation)
{
/// @todo	return [[[self alloc] initWithDuration:t scene:s orientation:o] autorelease];
	CCOrientedTransitionScene * pScene = new CCOrientedTransitionScene();
	pScene->initWithDurationAndScene(t,scene,orientation);
	pScene->autorelease();
	return pScene;
}

CCOrientedTransitionScene * CCOrientedTransitionScene::initWithDurationAndScene(ccTime t, CCScene *scene, tOrientation orientation)
{
	if ( __super::initWithDurationAndScene(t, scene) )
	{
		m_tOrientation = orientation;
	}
	return this;
}

//
// RotoZoom
//
CCRotoZoomTransition::CCRotoZoomTransition()
{
	/// @todo
}
CCRotoZoomTransition::~CCRotoZoomTransition()
{
	/// @todo
}

void CCRotoZoomTransition:: onEnter()
{
	/** @todo
	[super onEnter];

	[inScene setScale:0.001f];
	[outScene setScale:1.0f];

	[inScene setAnchorPoint:ccp(0.5f, 0.5f)];
	[outScene setAnchorPoint:ccp(0.5f, 0.5f)];

	CCIntervalAction *rotozoom = [CCSequence actions: [CCSpawn actions:
	[CCScaleBy actionWithDuration:duration/2 scale:0.001f],
		[CCRotateBy actionWithDuration:duration/2 angle:360 *2],
		nil],
		[CCDelayTime actionWithDuration:duration/2],
		nil];


	[outScene runAction: rotozoom];
	[inScene runAction: [CCSequence actions:
	[rotozoom reverse],
		[CCCallFunc actionWithTarget:self selector:@selector(finish)],
		nil]];*/
}


//
// JumpZoom
//
CCJumpZoomTransition::CCJumpZoomTransition()
{
	/// @todo
}
CCJumpZoomTransition::~CCJumpZoomTransition()
{
	/// @todo
}

void CCJumpZoomTransition::onEnter()
{
	/** @todo
	[super onEnter];
	CGSize s = [[CCDirector sharedDirector] winSize];

	[inScene setScale:0.5f];
	[inScene setPosition:ccp( s.width,0 )];

	[inScene setAnchorPoint:ccp(0.5f, 0.5f)];
	[outScene setAnchorPoint:ccp(0.5f, 0.5f)];

	CCIntervalAction *jump = [CCJumpBy actionWithDuration:duration/4 position:ccp(-s.width,0) height:s.width/4 jumps:2];
	CCIntervalAction *scaleIn = [CCScaleTo actionWithDuration:duration/4 scale:1.0f];
	CCIntervalAction *scaleOut = [CCScaleTo actionWithDuration:duration/4 scale:0.5f];

	CCIntervalAction *jumpZoomOut = [CCSequence actions: scaleOut, jump, nil];
	CCIntervalAction *jumpZoomIn = [CCSequence actions: jump, scaleIn, nil];

	CCIntervalAction *delay = [CCDelayTime actionWithDuration:duration/2];

	[outScene runAction: jumpZoomOut];
	[inScene runAction: [CCSequence actions: delay,
		jumpZoomIn,
		[CCCallFunc actionWithTarget:self selector:@selector(finish)],
		nil] ];*/
}


//
// MoveInL
//
CCMoveInLTransition::CCMoveInLTransition()
{
	/// @todo
}
CCMoveInLTransition::~CCMoveInLTransition()
{
	/// @todo
}

void CCMoveInLTransition::onEnter()
{
	/** @todo
	[super onEnter];

	[self initScenes];

	CCIntervalAction *a = [self action];

	[inScene runAction: [CCSequence actions:
	[self easeActionWithAction:a],
		[CCCallFunc actionWithTarget:self selector:@selector(finish)],
		nil]
	];*/

}
 
CCIntervalAction* CCMoveInLTransition::action()
{
	return NULL;
	/// @todo return [CCMoveTo actionWithDuration:duration position:ccp(0,0)];
}

CCIntervalAction* CCMoveInLTransition::easeActionWithAction(CCIntervalAction* action)
{
	return NULL;
	/// @todo return [CCEaseOut actionWithAction:action rate:2.0f];
	//	return [EaseElasticOut actionWithAction:action period:0.4f];
}

void CCMoveInLTransition::initScenes()
{
	/** @todo
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	m_pInScene->setPosition: ccp( -s.width,0);*/
}



//
// MoveInR
//
CCMoveInRTransition::CCMoveInRTransition()
{
	/// @todo
}
CCMoveInRTransition::~CCMoveInRTransition()
{
	/// @todo
}

void CCMoveInRTransition::initScenes()
{
	/** @todo
	CGSize s = [[CCDirector sharedDirector] winSize];
	[inScene setPosition: ccp( s.width,0) ];*/
}

//
// MoveInT
//
CCMoveInTTransition::CCMoveInTTransition()
{
	/// @todo
}
CCMoveInTTransition::~CCMoveInTTransition()
{
	/// @todo
}

void CCMoveInTTransition::initScenes()
{
	/** @todo
	CGSize s = [[CCDirector sharedDirector] winSize];
	[inScene setPosition: ccp( 0, s.height) ];*/
}


//
// MoveInB
//
CCMoveInBTransition::CCMoveInBTransition()
{
	/// @todo
}
CCMoveInBTransition::~CCMoveInBTransition()
{
	/// @todo
}

void CCMoveInBTransition::initScenes()
{
	/** @todo
	CGSize s = [[CCDirector sharedDirector] winSize];
	[inScene setPosition: ccp( 0, -s.height) ];*/
}


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
	/// @todo
}
CCSlideInLTransition::~CCSlideInLTransition()
{
	/// @todo
}

void CCSlideInLTransition::onEnter()
{
	/** @todo
	[super onEnter];

	[self initScenes];

	CCIntervalAction *in = [self action];
	CCIntervalAction *out = [self action];

	id inAction = [self easeActionWithAction:in];
	id outAction = [CCSequence actions:
	[self easeActionWithAction:out],
		[CCCallFunc actionWithTarget:self selector:@selector(finish)],
		nil];

	[inScene runAction: inAction];
	[outScene runAction: outAction];*/
}

void CCSlideInLTransition::sceneOrder()
{
	m_bIsInSceneOnTop = false;
}

void CCSlideInLTransition:: initScenes()
{
	/** @todo
	CGSize s = [[CCDirector sharedDirector] winSize];
	[inScene setPosition: ccp( -(s.width-ADJUST_FACTOR),0) ];*/
}

CCIntervalAction* CCSlideInLTransition::action()
{
	/** @todo
	CGSize s = [[CCDirector sharedDirector] winSize];
	return [CCMoveBy actionWithDuration:duration position:ccp(s.width-ADJUST_FACTOR,0)];*/
	return NULL;
}

CCIntervalAction* CCSlideInLTransition::easeActionWithAction(CCIntervalAction* action)
{
	/** @todo
	return [CCEaseOut actionWithAction:action rate:2.0f];*/
	return NULL;
	//	return [EaseElasticOut actionWithAction:action period:0.4f];
}


//
// SlideInR
//
CCSlideInRTransition::CCSlideInRTransition()
{
	/// @todo
}
CCSlideInRTransition::~CCSlideInRTransition()
{
	/// @todo
}

void CCSlideInRTransition::sceneOrder()
{
	m_bIsInSceneOnTop = true;
}

void CCSlideInRTransition::initScenes()
{
	/** @todo
	CGSize s = [[CCDirector sharedDirector] winSize];
	[inScene setPosition: ccp( s.width-ADJUST_FACTOR,0) ];*/
}


CCIntervalAction* CCSlideInRTransition:: action()
{
	/** @todo
	CGSize s = [[CCDirector sharedDirector] winSize];
	return [CCMoveBy actionWithDuration:duration position:ccp(-(s.width-ADJUST_FACTOR),0)];*/
	return NULL;
}


//
// SlideInT
//
CCSlideInTTransition::CCSlideInTTransition()
{
	/// @todo
}
CCSlideInTTransition::~CCSlideInTTransition()
{
	/// @todo
}

void CCSlideInTTransition::sceneOrder()
{
	m_bIsInSceneOnTop = false;
}

void CCSlideInTTransition::initScenes()
{
	/** @todo
	CGSize s = [[CCDirector sharedDirector] winSize];
	[inScene setPosition: ccp(0,s.height-ADJUST_FACTOR) ];*/
}


CCIntervalAction* CCSlideInTTransition::action()
{
	/** @todo
	CGSize s = [[CCDirector sharedDirector] winSize];
	return [CCMoveBy actionWithDuration:duration position:ccp(0,-(s.height-ADJUST_FACTOR))];*/
	return NULL;
}


//
// SlideInB
//
CCSlideInBTransition::CCSlideInBTransition()
{
	/// @todo
}
CCSlideInBTransition::~CCSlideInBTransition()
{
	/// @todo
}

void CCSlideInBTransition::sceneOrder()
{
	m_bIsInSceneOnTop = true;
}

void CCSlideInBTransition:: initScenes()
{
	/** @todo
	CGSize s = [[CCDirector sharedDirector] winSize];
	[inScene setPosition: ccp(0,-(s.height-ADJUST_FACTOR)) ];*/
}


CCIntervalAction* CCSlideInBTransition:: action()
{
	/** @todo
	CGSize s = [[CCDirector sharedDirector] winSize];
	return [CCMoveBy actionWithDuration:duration position:ccp(0,s.height-ADJUST_FACTOR)];*/
	return NULL;
}



//
// ShrinkGrow Transition
//
CCShrinkGrowTransition::CCShrinkGrowTransition()
{
	/// @todo
}
CCShrinkGrowTransition::~CCShrinkGrowTransition()
{
	/// @todo
}

void CCShrinkGrowTransition::onEnter()
{
	/** @todo
	[super onEnter];

	[inScene setScale:0.001f];
	[outScene setScale:1.0f];

	[inScene setAnchorPoint:ccp(2/3.0f,0.5f)];
	[outScene setAnchorPoint:ccp(1/3.0f,0.5f)];	

	CCIntervalAction *scaleOut = [CCScaleTo actionWithDuration:duration scale:0.01f];
	CCIntervalAction *scaleIn = [CCScaleTo actionWithDuration:duration scale:1.0f];

	[inScene runAction: [self easeActionWithAction:scaleIn]];
	[outScene runAction: [CCSequence actions:
	[self easeActionWithAction:scaleOut],
		[CCCallFunc actionWithTarget:self selector:@selector(finish)],
		nil] ];*/
}
CCIntervalAction* CCShrinkGrowTransition:: easeActionWithAction(CCIntervalAction* action)
{
	return NULL;
	/// @todo return [CCEaseOut actionWithAction:action rate:2.0f];
	//	return [EaseElasticOut actionWithAction:action period:0.3f];
}



//
// FlipX Transition
//
CCFlipXTransition::CCFlipXTransition()
{
	/// @todo
}
CCFlipXTransition::~CCFlipXTransition()
{
	/// @todo
}

void CCFlipXTransition::onEnter()
{
	/** @todo
	[super onEnter];

	CCIntervalAction *inA, *outA;
	[inScene setVisible: NO];

	float inDeltaZ, inAngleZ;
	float outDeltaZ, outAngleZ;

	if( orientation == kOrientationRightOver ) {
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

	inA = [CCSequence actions:
	[CCDelayTime actionWithDuration:duration/2],
		[CCShow action],
		[CCOrbitCamera actionWithDuration: duration/2 radius: 1 deltaRadius:0 angleZ:inAngleZ deltaAngleZ:inDeltaZ angleX:0 deltaAngleX:0],
		[CCCallFunc actionWithTarget:self selector:@selector(finish)],
		nil ];
	outA = [CCSequence actions:
	[CCOrbitCamera actionWithDuration: duration/2 radius: 1 deltaRadius:0 angleZ:outAngleZ deltaAngleZ:outDeltaZ angleX:0 deltaAngleX:0],
		[CCHide action],
		[CCDelayTime actionWithDuration:duration/2],							
		nil ];

	[inScene runAction: inA];
	[outScene runAction: outA];
*/
}


//
// FlipY Transition
//
CCFlipYTransition::CCFlipYTransition()
{
	/// @todo
}
CCFlipYTransition::~CCFlipYTransition()
{
	/// @todo
}

void CCFlipYTransition::onEnter()
{
	/** @todo
	[super onEnter];

	CCIntervalAction *inA, *outA;
	[inScene setVisible: NO];

	float inDeltaZ, inAngleZ;
	float outDeltaZ, outAngleZ;

	if( orientation == kOrientationUpOver ) {
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
	inA = [CCSequence actions:
	[CCDelayTime actionWithDuration:duration/2],
		[CCShow action],
		[CCOrbitCamera actionWithDuration: duration/2 radius: 1 deltaRadius:0 angleZ:inAngleZ deltaAngleZ:inDeltaZ angleX:90 deltaAngleX:0],
		[CCCallFunc actionWithTarget:self selector:@selector(finish)],
		nil ];
	outA = [CCSequence actions:
	[CCOrbitCamera actionWithDuration: duration/2 radius: 1 deltaRadius:0 angleZ:outAngleZ deltaAngleZ:outDeltaZ angleX:90 deltaAngleX:0],
		[CCHide action],
		[CCDelayTime actionWithDuration:duration/2],							
		nil ];

	[inScene runAction: inA];
	[outScene runAction: outA];
*/
}



//
// FlipAngular Transition
//
CCFlipAngularTransition::CCFlipAngularTransition()
{
	/// @todo
}
CCFlipAngularTransition::~CCFlipAngularTransition()
{
	/// @todo
}

void CCFlipAngularTransition::onEnter()
{
	/** @todo
	[super onEnter];

	CCIntervalAction *inA, *outA;
	[inScene setVisible: NO];

	float inDeltaZ, inAngleZ;
	float outDeltaZ, outAngleZ;

	if( orientation == kOrientationRightOver ) {
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
	inA = [CCSequence actions:
	[CCDelayTime actionWithDuration:duration/2],
		[CCShow action],
		[CCOrbitCamera actionWithDuration: duration/2 radius: 1 deltaRadius:0 angleZ:inAngleZ deltaAngleZ:inDeltaZ angleX:-45 deltaAngleX:0],
		[CCCallFunc actionWithTarget:self selector:@selector(finish)],
		nil ];
	outA = [CCSequence actions:
	[CCOrbitCamera actionWithDuration: duration/2 radius: 1 deltaRadius:0 angleZ:outAngleZ deltaAngleZ:outDeltaZ angleX:45 deltaAngleX:0],
		[CCHide action],
		[CCDelayTime actionWithDuration:duration/2],							
		nil ];

	[inScene runAction: inA];
	[outScene runAction: outA];*/
}


//
// ZoomFlipX Transition
//
CCZoomFlipXTransition::CCZoomFlipXTransition()
{
	/// @todo
}
CCZoomFlipXTransition::~CCZoomFlipXTransition()
{
	/// @todo
}

void CCZoomFlipXTransition::onEnter()
{
	/** @todo
	[super onEnter];

	CCIntervalAction *inA, *outA;
	[inScene setVisible: NO];

	float inDeltaZ, inAngleZ;
	float outDeltaZ, outAngleZ;

	if( orientation == kOrientationRightOver ) {
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
	inA = [CCSequence actions:
	[CCDelayTime actionWithDuration:duration/2],
		[CCSpawn actions:
	[CCOrbitCamera actionWithDuration: duration/2 radius: 1 deltaRadius:0 angleZ:inAngleZ deltaAngleZ:inDeltaZ angleX:0 deltaAngleX:0],
		[CCScaleTo actionWithDuration:duration/2 scale:1],
		[CCShow action],
		nil],
		[CCCallFunc actionWithTarget:self selector:@selector(finish)],
		nil ];
	outA = [CCSequence actions:
	[CCSpawn actions:
	[CCOrbitCamera actionWithDuration: duration/2 radius: 1 deltaRadius:0 angleZ:outAngleZ deltaAngleZ:outDeltaZ angleX:0 deltaAngleX:0],
		[CCScaleTo actionWithDuration:duration/2 scale:0.5f],
		nil],
		[CCHide action],
		[CCDelayTime actionWithDuration:duration/2],							
		nil ];

	inScene.scale = 0.5f;
	[inScene runAction: inA];
	[outScene runAction: outA];*/
}



//
// ZoomFlipY Transition
//
CCZoomFlipYTransition::CCZoomFlipYTransition()
{
	/// @todo
}
CCZoomFlipYTransition::~CCZoomFlipYTransition()
{
	/// @todo
}

void CCZoomFlipYTransition::onEnter()
{
	/** @todo
	[super onEnter];

	CCIntervalAction *inA, *outA;
	[inScene setVisible: NO];

	float inDeltaZ, inAngleZ;
	float outDeltaZ, outAngleZ;

	if( orientation == kOrientationUpOver ) {
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

	inA = [CCSequence actions:
	[CCDelayTime actionWithDuration:duration/2],
		[CCSpawn actions:
	[CCOrbitCamera actionWithDuration: duration/2 radius: 1 deltaRadius:0 angleZ:inAngleZ deltaAngleZ:inDeltaZ angleX:90 deltaAngleX:0],
		[CCScaleTo actionWithDuration:duration/2 scale:1],
		[CCShow action],
		nil],
		[CCCallFunc actionWithTarget:self selector:@selector(finish)],
		nil ];
	outA = [CCSequence actions:
	[CCSpawn actions:
	[CCOrbitCamera actionWithDuration: duration/2 radius: 1 deltaRadius:0 angleZ:outAngleZ deltaAngleZ:outDeltaZ angleX:90 deltaAngleX:0],
		[CCScaleTo actionWithDuration:duration/2 scale:0.5f],
		nil],							
		[CCHide action],
		[CCDelayTime actionWithDuration:duration/2],							
		nil ];

	inScene.scale = 0.5f;
	[inScene runAction: inA];
	[outScene runAction: outA];*/
}



//
// ZoomFlipAngular Transition
//
CCZoomFlipAngularTransition::CCZoomFlipAngularTransition()
{
	/// @todo
}
CCZoomFlipAngularTransition::~CCZoomFlipAngularTransition()
{
	/// @todo
}


void CCZoomFlipAngularTransition::onEnter()
{
	/** @todo
	[super onEnter];

	CCIntervalAction *inA, *outA;
	[inScene setVisible: NO];

	float inDeltaZ, inAngleZ;
	float outDeltaZ, outAngleZ;

	if( orientation == kOrientationRightOver ) {
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

	inA = [CCSequence actions:
	[CCDelayTime actionWithDuration:duration/2],
		[CCSpawn actions:
	[CCOrbitCamera actionWithDuration: duration/2 radius: 1 deltaRadius:0 angleZ:inAngleZ deltaAngleZ:inDeltaZ angleX:-45 deltaAngleX:0],
		[CCScaleTo actionWithDuration:duration/2 scale:1],
		[CCShow action],
		nil],						   
		[CCShow action],
		[CCCallFunc actionWithTarget:self selector:@selector(finish)],
		nil ];
	outA = [CCSequence actions:
	[CCSpawn actions:
	[CCOrbitCamera actionWithDuration: duration/2 radius: 1 deltaRadius:0 angleZ:outAngleZ deltaAngleZ:outDeltaZ angleX:45 deltaAngleX:0],
		[CCScaleTo actionWithDuration:duration/2 scale:0.5f],
		nil],							
		[CCHide action],
		[CCDelayTime actionWithDuration:duration/2],							
		nil ];

	inScene.scale = 0.5f;
	[inScene runAction: inA];
	[outScene runAction: outA];*/
}


//
// Fade Transition
//
CCFadeTransition::CCFadeTransition()
{
	/// @todo
}
CCFadeTransition::~CCFadeTransition()
{
	/// @todo
}


CCFadeTransition * CCFadeTransition::transitionWithDurationAndColor(ccTime duration, CCScene *scene, ccColor3B color)
{
	CCFadeTransition * pTransition = new CCFadeTransition();
	pTransition->initWithDurationAndColor(duration, scene, color);
	pTransition->autorelease();
	return pTransition;
}

CCFadeTransition * CCFadeTransition::initWithDurationAndColor(ccTime duration, CCScene *scene, ccColor3B color)
{
	if (__super::initWithDurationAndScene(duration, scene))
	{
		m_tColor.r = color.r;
		m_tColor.g = color.g;
		m_tColor.b = color.b;
	}
	return this;
}

CCFadeTransition * CCFadeTransition::initWithDurationAndScene(ccTime t, CCScene *scene)
{
	__super::initWithDurationAndScene(t, scene);
	return this;
}

void CCFadeTransition :: onEnter()
{
	/** @todo
	[super onEnter];

	CCColorLayer *l = [CCColorLayer layerWithColor:color];
	[inScene setVisible: NO];

	[self addChild: l z:2 tag:kSceneFade];


	CCNode *f = [self getChildByTag:kSceneFade];

	CCIntervalAction *a = [CCSequence actions:
	[CCFadeIn actionWithDuration:duration/2],
		[CCCallFunc actionWithTarget:self selector:@selector(hideOutShowIn)],
		[CCFadeOut actionWithDuration:duration/2],
		[CCCallFunc actionWithTarget:self selector:@selector(finish)],
		nil ];
	[f runAction: a];*/
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
	/// @todo
}
CCCrossFadeTransition::~CCCrossFadeTransition()
{
	/// @todo
}


void CCCrossFadeTransition:: draw()
{
	/// @todo override draw since both scenes (textures) are rendered in 1 scene
}

void CCCrossFadeTransition::onEnter()
{
	/** @todo
	[super onEnter];

	// create a transparent color layer
	// in which we are going to add our rendertextures
	ccColor4B  color = {0,0,0,0};
	CGSize size = [[CCDirector sharedDirector] winSize];
	CCColorLayer * layer = [CCColorLayer layerWithColor:color];

	// create the first render texture for inScene
	CCRenderTexture *inTexture = [CCRenderTexture renderTextureWithWidth:size.width height:size.height];
	inTexture.sprite.anchorPoint= ccp(0.5f,0.5f);
	inTexture.position = ccp(size.width/2, size.height/2);
	inTexture.anchorPoint = ccp(0.5f,0.5f);

	// render inScene to its texturebuffer
	[inTexture begin];
	[inScene visit];
	[inTexture end];

	// create the second render texture for outScene
	CCRenderTexture *outTexture = [CCRenderTexture renderTextureWithWidth:size.width height:size.height];
	outTexture.sprite.anchorPoint= ccp(0.5f,0.5f);
	outTexture.position = ccp(size.width/2, size.height/2);
	outTexture.anchorPoint = ccp(0.5f,0.5f);

	// render outScene to its texturebuffer
	[outTexture begin];
	[outScene visit];
	[outTexture end];

	// create blend functions

	ccBlendFunc blend1 = {GL_ONE, GL_ONE}; // inScene will lay on background and will not be used with alpha
	ccBlendFunc blend2 = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}; // we are going to blend outScene via alpha 

	// set blendfunctions
	[inTexture.sprite setBlendFunc:blend1];
	[outTexture.sprite setBlendFunc:blend2];	

	// add render textures to the layer
	[layer addChild:inTexture];
	[layer addChild:outTexture];

	// initial opacity:
	[inTexture.sprite setOpacity:255];
	[outTexture.sprite setOpacity:255];

	// create the blend action
	CCIntervalAction * layerAction = [CCSequence actions:
	[CCFadeTo actionWithDuration:duration opacity:0],
		[CCCallFunc actionWithTarget:self selector:@selector(hideOutShowIn)],
		[CCCallFunc actionWithTarget:self selector:@selector(finish)],
		nil ];


	// run the blend action
	[outTexture.sprite runAction: layerAction];

	// add the layer (which contains our two rendertextures) to the scene
	[self addChild: layer z:2 tag:kSceneFade];*/
}

// clean up on exit
void CCCrossFadeTransition::onExit()
{
	// remove our layer and release all containing objects 
	this->removeChildByTag(kSceneFade, false);
	__super::onExit();
}



//
// TurnOffTilesTransition
//
CCTurnOffTilesTransition::CCTurnOffTilesTransition()
{
	/// @todo
}
CCTurnOffTilesTransition::~CCTurnOffTilesTransition()
{
	/// @todo
}


// override addScenes, and change the order
void CCTurnOffTilesTransition::sceneOrder()
{
	m_bIsInSceneOnTop = false;
}

void CCTurnOffTilesTransition::onEnter()
{
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




//
// SplitCols Transition
//
CCSplitColsTransition::CCSplitColsTransition()
{
	/// @todo
}
CCSplitColsTransition::~CCSplitColsTransition()
{
	/// @todo
}


void CCSplitColsTransition::onEnter()
{
	/** @todo
	[super onEnter];

	inScene.visible = NO;

	id split = [self action];
	id seq = [CCSequence actions:
	split,
		[CCCallFunc actionWithTarget:self selector:@selector(hideOutShowIn)],
		[split reverse],
		nil
	];
	[self runAction: [CCSequence actions:
	[self easeActionWithAction:seq],
		[CCCallFunc actionWithTarget:self selector:@selector(finish)],
		[CCStopGrid action],
		nil]
	];*/
}


CCIntervalAction* CCSplitColsTransition:: action()
{
	return NULL;
	/// @todo return [CCSplitCols actionWithCols:3 duration:duration/2.0f];
}


CCIntervalAction* easeActionWithAction(CCIntervalAction * action)
{
	return NULL;
	/// @todo return [CCEaseInOut actionWithAction:action rate:3.0f];
}


//
// SplitRows Transition
//
CCSplitRowsTransition::CCSplitRowsTransition()
{
	/// @todo
}
CCSplitRowsTransition::~CCSplitRowsTransition()
{
	/// @todo
}


CCIntervalAction* CCSplitRowsTransition::action()
{
	return NULL;
	/// @todo return [CCSplitRows actionWithRows:3 duration:duration/2.0f];
}



//
// FadeTR Transition
//
CCFadeTRTransition::CCFadeTRTransition()
{
	/// @todo
}
CCFadeTRTransition::~CCFadeTRTransition()
{
	/// @todo
}


void CCFadeTRTransition::sceneOrder()
{
	m_bIsInSceneOnTop = false;
}

void CCFadeTRTransition::onEnter()
{
	/** @todo
	[super onEnter];

	CGSize s = [[CCDirector sharedDirector] winSize];
	float aspect = s.width / s.height;
	int x = 12 * aspect;
	int y = 12;

	id action  = [self actionWithSize:ccg(x,y)];

	[outScene runAction: [CCSequence actions:
	[self easeActionWithAction:action],
		[CCCallFunc actionWithTarget:self selector:@selector(finish)],
		[CCStopGrid action],
		nil]
	];*/
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


//
// FadeBL Transition
//

CCFadeBLTransition::CCFadeBLTransition()
{
	/// @todo
}
CCFadeBLTransition::~CCFadeBLTransition()
{
	/// @todo
}

CCIntervalAction*  CCFadeBLTransition::actionWithSize(ccGridSize size)
{
	return NULL;
	/// @todo return [CCFadeOutBLTiles actionWithSize:v duration:duration];
}



//
// FadeUp Transition
//
CCFadeUpTransition::CCFadeUpTransition()
{
	/// @todo
}
CCFadeUpTransition::~CCFadeUpTransition()
{
	/// @todo
}


CCIntervalAction* CCFadeUpTransition::actionWithSize(ccGridSize size)
{
	return NULL;
	/// @todo return [CCFadeOutUpTiles actionWithSize:v duration:duration];
}


//
// FadeDown Transition
//
CCFadeDownTransition::CCFadeDownTransition()
{
	/// @todo
}
CCFadeDownTransition::~CCFadeDownTransition()
{
	/// @todo
}

CCIntervalAction* CCFadeDownTransition::actionWithSize(ccGridSize size)
{
	return NULL;
	/// @todo return [CCFadeOutDownTiles actionWithSize:v duration:duration];
}
