/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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
#include "support/CCPointExtension.h"
#include "CCDirector.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "actions/CCActionInterval.h"
#include "actions/CCActionInstant.h"
#include "actions/CCActionEase.h"
#include "actions/CCActionCamera.h"
#include "actions/CCActionTiledGrid.h"
#include "actions/CCActionGrid.h"
#include "CCLayer.h"
#include "misc_nodes/CCRenderTexture.h"


NS_CC_BEGIN

const unsigned int kSceneFade = 0xFADEFADE;

CCTransitionScene::CCTransitionScene()
{
}
CCTransitionScene::~CCTransitionScene()
{
    m_pInScene->release();
    m_pOutScene->release();
}

CCTransitionScene * CCTransitionScene::transitionWithDuration(float t, CCScene *scene)
{
    return CCTransitionScene::create(t,scene);
}

CCTransitionScene * CCTransitionScene::create(float t, CCScene *scene)
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

bool CCTransitionScene::initWithDuration(float t, CCScene *scene)
{
    CCAssert( scene != NULL, "Argument scene must be non-nil");

    if (CCScene::init())
    {
        m_fDuration = t;

        // retain
        m_pInScene = scene;
        m_pInScene->retain();
        m_pOutScene = CCDirector::sharedDirector()->getRunningScene();
        if (m_pOutScene == NULL)
        {
            m_pOutScene = CCScene::create();
            m_pOutScene->init();
        }
        m_pOutScene->retain();

        CCAssert( m_pInScene != m_pOutScene, "Incoming scene must be different from the outgoing scene" );

        // disable events while transitions
        CCDirector* pDirector = CCDirector::sharedDirector();
        pDirector->getTouchDispatcher()->setDispatchEvents(false);
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
     m_pInScene->setVisible(true);
     m_pInScene->setPosition(ccp(0,0));
     m_pInScene->setScale(1.0f);
     m_pInScene->setRotation(0.0f);
     m_pInScene->getCamera()->restore();
 
     m_pOutScene->setVisible(false);
     m_pOutScene->setPosition(ccp(0,0));
     m_pOutScene->setScale(1.0f);
     m_pOutScene->setRotation(0.0f);
     m_pOutScene->getCamera()->restore();

    //[self schedule:@selector(setNewScene:) interval:0];
    this->schedule(schedule_selector(CCTransitionScene::setNewScene), 0);

}

void CCTransitionScene::setNewScene(float dt)
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
    director->getTouchDispatcher()->setDispatchEvents(true);
    // issue #267
    m_pOutScene->setVisible(true);
}

void CCTransitionScene::hideOutShowIn()
{
    m_pInScene->setVisible(true);
    m_pOutScene->setVisible(false);
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

CCTransitionSceneOriented * CCTransitionSceneOriented::transitionWithDuration(float t, CCScene *scene, tOrientation orientation)
{
    return CCTransitionSceneOriented::create(t,scene,orientation);
}

CCTransitionSceneOriented * CCTransitionSceneOriented::create(float t, CCScene *scene, tOrientation orientation)
{
    CCTransitionSceneOriented * pScene = new CCTransitionSceneOriented();
    pScene->initWithDuration(t,scene,orientation);
    pScene->autorelease();
    return pScene;
}

bool CCTransitionSceneOriented::initWithDuration(float t, CCScene *scene, tOrientation orientation)
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

CCTransitionRotoZoom* CCTransitionRotoZoom::create(float t, CCScene* scene)                   
{                                                               
    CCTransitionRotoZoom* pScene = new CCTransitionRotoZoom();                                
    if(pScene && pScene->initWithDuration(t, scene))            
    {                                                           
        pScene->autorelease();                                  
        return pScene;                                          
    }                                                           
    CC_SAFE_DELETE(pScene);                                     
    return NULL;                                                
}


CCTransitionRotoZoom* CCTransitionRotoZoom::transitionWithDuration(float t, CCScene* scene)
{                                                               
    CCTransitionRotoZoom* pScene = new CCTransitionRotoZoom();
    
    if(pScene && pScene->initWithDuration(t, scene))            
    {                                                           
        pScene->autorelease();                                  
        return pScene;                                          
    }                                                           
    CC_SAFE_DELETE(pScene);                                     
    return NULL;                                                
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

    CCActionInterval *rotozoom = (CCActionInterval*)(CCSequence::create
    (
        CCSpawn::create
        (
            CCScaleBy::create(m_fDuration/2, 0.001f),
            CCRotateBy::create(m_fDuration/2, 360 * 2),
            NULL
        ),
        CCDelayTime::create(m_fDuration/2),
        NULL
    ));

    m_pOutScene->runAction(rotozoom);
    m_pInScene->runAction
    (
        CCSequence::create
        (
            rotozoom->reverse(),
            CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)),
            NULL
        )
    );
}

//
// JumpZoom
//
CCTransitionJumpZoom::CCTransitionJumpZoom()
{
}
CCTransitionJumpZoom::~CCTransitionJumpZoom()
{
}

CCTransitionJumpZoom* CCTransitionJumpZoom::create(float t, CCScene* scene)
{
    CCTransitionJumpZoom* pScene = new CCTransitionJumpZoom();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


CCTransitionJumpZoom* CCTransitionJumpZoom::transitionWithDuration(float t, CCScene* scene)
{
    CCTransitionJumpZoom* pScene = new CCTransitionJumpZoom();
    
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCTransitionJumpZoom::onEnter()
{
    CCTransitionScene::onEnter();
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    m_pInScene->setScale(0.5f);
    m_pInScene->setPosition(ccp(s.width, 0));
    m_pInScene->setAnchorPoint(ccp(0.5f, 0.5f));
    m_pOutScene->setAnchorPoint(ccp(0.5f, 0.5f));

    CCActionInterval *jump = CCJumpBy::create(m_fDuration/4, ccp(-s.width,0), s.width/4, 2);
    CCActionInterval *scaleIn = CCScaleTo::create(m_fDuration/4, 1.0f);
    CCActionInterval *scaleOut = CCScaleTo::create(m_fDuration/4, 0.5f);

    CCActionInterval *jumpZoomOut = (CCActionInterval*)(CCSequence::create(scaleOut, jump, NULL));
    CCActionInterval *jumpZoomIn = (CCActionInterval*)(CCSequence::create(jump, scaleIn, NULL));

    CCActionInterval *delay = CCDelayTime::create(m_fDuration/2);

    m_pOutScene->runAction(jumpZoomOut);
    m_pInScene->runAction
    (
        CCSequence::create
        (
            delay,
            jumpZoomIn,
            CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)),
            NULL
        )
    );
}

//
// MoveInL
//
CCTransitionMoveInL::CCTransitionMoveInL()
{
}

CCTransitionMoveInL::~CCTransitionMoveInL()
{
}

CCTransitionMoveInL* CCTransitionMoveInL::create(float t, CCScene* scene)
{
    CCTransitionMoveInL* pScene = new CCTransitionMoveInL();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


CCTransitionMoveInL* CCTransitionMoveInL::transitionWithDuration(float t, CCScene* scene)
{
    CCTransitionMoveInL* pScene = new CCTransitionMoveInL();
    
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCTransitionMoveInL::onEnter()
{
    CCTransitionScene::onEnter();
    this->initScenes();

    CCActionInterval *a = this->action();

    m_pInScene->runAction
    (
        CCSequence::create
        (
            this->easeActionWithAction(a),
            CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)),
            NULL
        )
    );
}
 
CCActionInterval* CCTransitionMoveInL::action()
{
    return CCMoveTo::create(m_fDuration, ccp(0,0));
}

CCActionInterval* CCTransitionMoveInL::easeActionWithAction(CCActionInterval* action)
{
    return CCEaseOut::create(action, 2.0f);
//    return [EaseElasticOut actionWithAction:action period:0.4f];
}

void CCTransitionMoveInL::initScenes()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    m_pInScene->setPosition( ccp(-s.width,0) );
}

//
// MoveInR
//
CCTransitionMoveInR::CCTransitionMoveInR()
{
}
CCTransitionMoveInR::~CCTransitionMoveInR()
{
}

CCTransitionMoveInR* CCTransitionMoveInR::create(float t, CCScene* scene)
{
    CCTransitionMoveInR* pScene = new CCTransitionMoveInR();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


CCTransitionMoveInR* CCTransitionMoveInR::transitionWithDuration(float t, CCScene* scene)
{
    CCTransitionMoveInR* pScene = new CCTransitionMoveInR();
    
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCTransitionMoveInR::initScenes()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    m_pInScene->setPosition( ccp(s.width,0) );
}

//
// MoveInT
//
CCTransitionMoveInT::CCTransitionMoveInT()
{
}
CCTransitionMoveInT::~CCTransitionMoveInT()
{
}

CCTransitionMoveInT* CCTransitionMoveInT::create(float t, CCScene* scene)
{
    CCTransitionMoveInT* pScene = new CCTransitionMoveInT();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


CCTransitionMoveInT* CCTransitionMoveInT::transitionWithDuration(float t, CCScene* scene)
{
    CCTransitionMoveInT* pScene = new CCTransitionMoveInT();
    
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCTransitionMoveInT::initScenes()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    m_pInScene->setPosition( ccp(0,s.height) );
}

//
// MoveInB
//
CCTransitionMoveInB::CCTransitionMoveInB()
{
}
CCTransitionMoveInB::~CCTransitionMoveInB()
{
}

CCTransitionMoveInB* CCTransitionMoveInB::create(float t, CCScene* scene)
{
    CCTransitionMoveInB* pScene = new CCTransitionMoveInB();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


CCTransitionMoveInB* CCTransitionMoveInB::transitionWithDuration(float t, CCScene* scene)
{
    CCTransitionMoveInB* pScene = new CCTransitionMoveInB();
    
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCTransitionMoveInB::initScenes()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    m_pInScene->setPosition( ccp(0,-s.height) );
}


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

CCTransitionSlideInL* CCTransitionSlideInL::create(float t, CCScene* scene)
{
    CCTransitionSlideInL* pScene = new CCTransitionSlideInL();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


CCTransitionSlideInL* CCTransitionSlideInL::transitionWithDuration(float t, CCScene* scene)
{
    CCTransitionSlideInL* pScene = new CCTransitionSlideInL();
    
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCTransitionSlideInL::onEnter()
{
    CCTransitionScene::onEnter();
    this->initScenes();

    CCActionInterval *in = this->action();
    CCActionInterval *out = this->action();

    CCActionInterval* inAction = easeActionWithAction(in);
    CCActionInterval* outAction = (CCActionInterval*)CCSequence::create
    (
        easeActionWithAction(out),
        CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)), 
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
    return CCMoveBy::create(m_fDuration, ccp(s.width-ADJUST_FACTOR,0));
}

CCActionInterval* CCTransitionSlideInL::easeActionWithAction(CCActionInterval* action)
{
    return CCEaseOut::create(action, 2.0f);
//    return [EaseElasticOut actionWithAction:action period:0.4f];
}


//
// SlideInR
//
CCTransitionSlideInR::CCTransitionSlideInR()
{
}
CCTransitionSlideInR::~CCTransitionSlideInR()
{
}

CCTransitionSlideInR* CCTransitionSlideInR::create(float t, CCScene* scene)
{
    CCTransitionSlideInR* pScene = new CCTransitionSlideInR();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


CCTransitionSlideInR* CCTransitionSlideInR::transitionWithDuration(float t, CCScene* scene)
{
    CCTransitionSlideInR* pScene = new CCTransitionSlideInR();
    
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
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
    return CCMoveBy::create(m_fDuration, ccp(-(s.width-ADJUST_FACTOR),0));
}


//
// SlideInT
//
CCTransitionSlideInT::CCTransitionSlideInT()
{
}
CCTransitionSlideInT::~CCTransitionSlideInT()
{
}

CCTransitionSlideInT* CCTransitionSlideInT::create(float t, CCScene* scene)
{
    CCTransitionSlideInT* pScene = new CCTransitionSlideInT();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


CCTransitionSlideInT* CCTransitionSlideInT::transitionWithDuration(float t, CCScene* scene)
{
    CCTransitionSlideInT* pScene = new CCTransitionSlideInT();
    
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
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
    return CCMoveBy::create(m_fDuration, ccp(0,-(s.height-ADJUST_FACTOR)));
}

//
// SlideInB
//
CCTransitionSlideInB::CCTransitionSlideInB()
{
}
CCTransitionSlideInB::~CCTransitionSlideInB()
{
}

CCTransitionSlideInB* CCTransitionSlideInB::create(float t, CCScene* scene)
{
    CCTransitionSlideInB* pScene = new CCTransitionSlideInB();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


CCTransitionSlideInB* CCTransitionSlideInB::transitionWithDuration(float t, CCScene* scene)
{
    CCTransitionSlideInB* pScene = new CCTransitionSlideInB();
    
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
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
    return CCMoveBy::create(m_fDuration, ccp(0,s.height-ADJUST_FACTOR));
}

//
// ShrinkGrow Transition
//
CCTransitionShrinkGrow::CCTransitionShrinkGrow()
{
}
CCTransitionShrinkGrow::~CCTransitionShrinkGrow()
{
}

CCTransitionShrinkGrow* CCTransitionShrinkGrow::create(float t, CCScene* scene)
{
    CCTransitionShrinkGrow* pScene = new CCTransitionShrinkGrow();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


CCTransitionShrinkGrow* CCTransitionShrinkGrow::transitionWithDuration(float t, CCScene* scene)
{
    CCTransitionShrinkGrow* pScene = new CCTransitionShrinkGrow();
    
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCTransitionShrinkGrow::onEnter()
{
    CCTransitionScene::onEnter();

    m_pInScene->setScale(0.001f);
    m_pOutScene->setScale(1.0f);

    m_pInScene->setAnchorPoint(ccp(2/3.0f,0.5f));
    m_pOutScene->setAnchorPoint(ccp(1/3.0f,0.5f));    

    CCActionInterval* scaleOut = CCScaleTo::create(m_fDuration, 0.01f);
    CCActionInterval* scaleIn = CCScaleTo::create(m_fDuration, 1.0f);

    m_pInScene->runAction(this->easeActionWithAction(scaleIn));
    m_pOutScene->runAction
    (
        CCSequence::create
        (
            this->easeActionWithAction(scaleOut),
            CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)), 
            NULL
        )
    );
}
CCActionInterval* CCTransitionShrinkGrow:: easeActionWithAction(CCActionInterval* action)
{
    return CCEaseOut::create(action, 2.0f);
//    return [EaseElasticOut actionWithAction:action period:0.3f];
}

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
    m_pInScene->setVisible(false);

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

    inA = (CCActionInterval*)CCSequence::create
        (
            CCDelayTime::create(m_fDuration/2),
            CCShow::create(),
            CCOrbitCamera::create(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, 0, 0),
            CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)), 
            NULL
        );

    outA = (CCActionInterval *)CCSequence::create
        (
            CCOrbitCamera::create(m_fDuration/2, 1, 0, outAngleZ, outDeltaZ, 0, 0),
            CCHide::create(),
            CCDelayTime::create(m_fDuration/2),                            
            NULL 
        );

    m_pInScene->runAction(inA);
    m_pOutScene->runAction(outA);
}

CCTransitionFlipX* CCTransitionFlipX::transitionWithDuration(float t, CCScene* s, tOrientation o)
{
    return CCTransitionFlipX::create(t, s, o);
}

CCTransitionFlipX* CCTransitionFlipX::create(float t, CCScene* s, tOrientation o)
{
    CCTransitionFlipX* pScene = new CCTransitionFlipX();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

CCTransitionFlipX* CCTransitionFlipX::create(float t, CCScene* s)
{
    return CCTransitionFlipX::create(t, s, kOrientationRightOver);
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
    m_pInScene->setVisible(false);

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

    inA = (CCActionInterval*)CCSequence::create
        (
            CCDelayTime::create(m_fDuration/2),
            CCShow::create(),
            CCOrbitCamera::create(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, 90, 0),
            CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)), 
            NULL
        );
    outA = (CCActionInterval*)CCSequence::create
        (
            CCOrbitCamera::create(m_fDuration/2, 1, 0, outAngleZ, outDeltaZ, 90, 0),
            CCHide::create(),
            CCDelayTime::create(m_fDuration/2),                            
            NULL
        );

    m_pInScene->runAction(inA);
    m_pOutScene->runAction(outA);

}

CCTransitionFlipY* CCTransitionFlipY::transitionWithDuration(float t, CCScene* s, tOrientation o)
{
    return CCTransitionFlipY::create(t, s, o);
}

CCTransitionFlipY* CCTransitionFlipY::create(float t, CCScene* s, tOrientation o)
{
    CCTransitionFlipY* pScene = new CCTransitionFlipY();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

CCTransitionFlipY* CCTransitionFlipY::create(float t, CCScene* s)
{
    return CCTransitionFlipY::create(t, s, kOrientationUpOver);
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
    m_pInScene->setVisible(false);

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

    inA = (CCActionInterval *)CCSequence::create
        (
            CCDelayTime::create(m_fDuration/2),
            CCShow::create(),
            CCOrbitCamera::create(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, -45, 0),
            CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)), 
            NULL
        );
    outA = (CCActionInterval *)CCSequence::create
        (
            CCOrbitCamera::create(m_fDuration/2, 1, 0, outAngleZ, outDeltaZ, 45, 0),
            CCHide::create(),
            CCDelayTime::create(m_fDuration/2),                            
            NULL
        );

    m_pInScene->runAction(inA);
    m_pOutScene->runAction(outA);
}

CCTransitionFlipAngular* CCTransitionFlipAngular::transitionWithDuration(float t, CCScene* s, tOrientation o)
{
    return CCTransitionFlipAngular::create(t, s, o);
}

CCTransitionFlipAngular* CCTransitionFlipAngular::create(float t, CCScene* s, tOrientation o)
{
    CCTransitionFlipAngular* pScene = new CCTransitionFlipAngular();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

CCTransitionFlipAngular* CCTransitionFlipAngular::create(float t, CCScene* s)
{
    return CCTransitionFlipAngular::create(t, s, kOrientationRightOver);
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
    m_pInScene->setVisible(false);

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
    inA = (CCActionInterval *)CCSequence::create
        (
            CCDelayTime::create(m_fDuration/2),
            CCSpawn::create
            (
                CCOrbitCamera::create(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, 0, 0),
                CCScaleTo::create(m_fDuration/2, 1),
                CCShow::create(),
                NULL
            ),
            CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)),
            NULL
        );
    outA = (CCActionInterval *)CCSequence::create
        (
            CCSpawn::create
            (
                CCOrbitCamera::create(m_fDuration/2, 1, 0, outAngleZ, outDeltaZ, 0, 0),
                CCScaleTo::create(m_fDuration/2, 0.5f),
                NULL
            ),
            CCHide::create(),
            CCDelayTime::create(m_fDuration/2),                            
            NULL
        );

    m_pInScene->setScale(0.5f);
    m_pInScene->runAction(inA);
    m_pOutScene->runAction(outA);
}

CCTransitionZoomFlipX* CCTransitionZoomFlipX::transitionWithDuration(float t, CCScene* s, tOrientation o)
{
    return CCTransitionZoomFlipX::create(t, s, o);
}

CCTransitionZoomFlipX* CCTransitionZoomFlipX::create(float t, CCScene* s, tOrientation o)
{
    CCTransitionZoomFlipX* pScene = new CCTransitionZoomFlipX();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

CCTransitionZoomFlipX* CCTransitionZoomFlipX::create(float t, CCScene* s)
{
    return CCTransitionZoomFlipX::create(t, s, kOrientationRightOver);
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
    m_pInScene->setVisible(false);

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

    inA = (CCActionInterval *)CCSequence::create
        (
            CCDelayTime::create(m_fDuration/2),
            CCSpawn::create
            (
                CCOrbitCamera::create(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, 90, 0),
                CCScaleTo::create(m_fDuration/2, 1),
                CCShow::create(),
                NULL
            ),
            CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)),
            NULL
        );

    outA = (CCActionInterval *)CCSequence::create
        (
            CCSpawn::create
            (
                CCOrbitCamera::create(m_fDuration/2, 1, 0, outAngleZ, outDeltaZ, 90, 0),
                CCScaleTo::create(m_fDuration/2, 0.5f),
                NULL
            ),                            
            CCHide::create(),
            CCDelayTime::create(m_fDuration/2),
            NULL
        );

    m_pInScene->setScale(0.5f);
    m_pInScene->runAction(inA);
    m_pOutScene->runAction(outA);
}

CCTransitionZoomFlipY* CCTransitionZoomFlipY::transitionWithDuration(float t, CCScene* s, tOrientation o)
{
    return CCTransitionZoomFlipY::create(t, s, o);
}

CCTransitionZoomFlipY* CCTransitionZoomFlipY::create(float t, CCScene* s, tOrientation o)
{
    CCTransitionZoomFlipY* pScene = new CCTransitionZoomFlipY();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

CCTransitionZoomFlipY* CCTransitionZoomFlipY::create(float t, CCScene* s)
{
    return CCTransitionZoomFlipY::create(t, s, kOrientationUpOver);
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
    m_pInScene->setVisible(false);

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

    inA = (CCActionInterval *)CCSequence::create
        (
            CCDelayTime::create(m_fDuration/2),
            CCSpawn::create
            (
                CCOrbitCamera::create(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, -45, 0),
                CCScaleTo::create(m_fDuration/2, 1),
                CCShow::create(),
                NULL
            ),
            CCShow::create(),
            CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)),
            NULL
        );
    outA = (CCActionInterval *)CCSequence::create
        (
            CCSpawn::create
            (
                CCOrbitCamera::create(m_fDuration/2, 1, 0 , outAngleZ, outDeltaZ, 45, 0),
                CCScaleTo::create(m_fDuration/2, 0.5f),
                NULL
            ),                            
            CCHide::create(),
            CCDelayTime::create(m_fDuration/2),                            
            NULL
        );

    m_pInScene->setScale(0.5f);
    m_pInScene->runAction(inA);
    m_pOutScene->runAction(outA);
}

CCTransitionZoomFlipAngular* CCTransitionZoomFlipAngular::transitionWithDuration(float t, CCScene* s, tOrientation o)
{
    return CCTransitionZoomFlipAngular::create(t, s, o);
}

CCTransitionZoomFlipAngular* CCTransitionZoomFlipAngular::create(float t, CCScene* s, tOrientation o)
{
    CCTransitionZoomFlipAngular* pScene = new CCTransitionZoomFlipAngular();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

CCTransitionZoomFlipAngular* CCTransitionZoomFlipAngular::create(float t, CCScene* s)
{
    return CCTransitionZoomFlipAngular::create(t, s, kOrientationRightOver);
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

CCTransitionFade * CCTransitionFade::transitionWithDuration(float duration, CCScene *scene, const ccColor3B& color)
{
    return CCTransitionFade::create(duration, scene, color);
}

CCTransitionFade * CCTransitionFade::create(float duration, CCScene *scene, const ccColor3B& color)
{
    CCTransitionFade * pTransition = new CCTransitionFade();
    pTransition->initWithDuration(duration, scene, color);
    pTransition->autorelease();
    return pTransition;
}

CCTransitionFade* CCTransitionFade::create(float duration,CCScene* scene)
{
    return CCTransitionFade::create(duration, scene, ccBLACK);
}

bool CCTransitionFade::initWithDuration(float duration, CCScene *scene, const ccColor3B& color)
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

bool CCTransitionFade::initWithDuration(float t, CCScene *scene)
{
    this->initWithDuration(t, scene, ccBLACK);
    return true;
}

void CCTransitionFade :: onEnter()
{
    CCTransitionScene::onEnter();

    CCLayerColor* l = CCLayerColor::create(m_tColor);
    m_pInScene->setVisible(false);

    addChild(l, 2, kSceneFade);
    CCNode* f = getChildByTag(kSceneFade);

    CCActionInterval* a = (CCActionInterval *)CCSequence::create
        (
            CCFadeIn::create(m_fDuration/2),
            CCCallFunc::create(this, callfunc_selector(CCTransitionScene::hideOutShowIn)),//CCCallFunc::create:self selector:@selector(hideOutShowIn)],
            CCFadeOut::create(m_fDuration/2),
            CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)), //:self selector:@selector(finish)],
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

CCTransitionCrossFade* CCTransitionCrossFade::create(float t, CCScene* scene)
{
    CCTransitionCrossFade* pScene = new CCTransitionCrossFade();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


CCTransitionCrossFade* CCTransitionCrossFade::transitionWithDuration(float t, CCScene* scene)
{
    CCTransitionCrossFade* pScene = new CCTransitionCrossFade();
    
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
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
    CCLayerColor* layer = CCLayerColor::create(color);

    // create the first render texture for inScene
    CCRenderTexture* inTexture = CCRenderTexture::create((int)size.width, (int)size.height);

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
    CCRenderTexture* outTexture = CCRenderTexture::create((int)size.width, (int)size.height);
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
    CCAction* layerAction = CCSequence::create
    (
        CCFadeTo::create(m_fDuration, 0),
        CCCallFunc::create(this, callfunc_selector(CCTransitionScene::hideOutShowIn)),
        CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)),
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

//
// TurnOffTilesTransition
//
CCTransitionTurnOffTiles::CCTransitionTurnOffTiles()
{
}

CCTransitionTurnOffTiles::~CCTransitionTurnOffTiles()
{
}

CCTransitionTurnOffTiles* CCTransitionTurnOffTiles::create(float t, CCScene* scene)
{
    CCTransitionTurnOffTiles* pScene = new CCTransitionTurnOffTiles();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


CCTransitionTurnOffTiles* CCTransitionTurnOffTiles::transitionWithDuration(float t, CCScene* scene)
{
    CCTransitionTurnOffTiles* pScene = new CCTransitionTurnOffTiles();
    
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
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

    CCTurnOffTiles* toff = CCTurnOffTiles::create( ccg(x,y), m_fDuration);
    CCActionInterval* action = easeActionWithAction(toff);
    m_pOutScene->runAction
    (
        CCSequence::create
        (
            action,
            CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)), 
            CCStopGrid::create(),
            NULL
        )
    );
}


CCActionInterval* CCTransitionTurnOffTiles:: easeActionWithAction(CCActionInterval* action)
{
    return action;
}

//
// SplitCols Transition
//
CCTransitionSplitCols::CCTransitionSplitCols()
{
}
CCTransitionSplitCols::~CCTransitionSplitCols()
{
}

CCTransitionSplitCols* CCTransitionSplitCols::create(float t, CCScene* scene)
{
    CCTransitionSplitCols* pScene = new CCTransitionSplitCols();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


CCTransitionSplitCols* CCTransitionSplitCols::transitionWithDuration(float t, CCScene* scene)
{
    CCTransitionSplitCols* pScene = new CCTransitionSplitCols();
    
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCTransitionSplitCols::onEnter()
{
    CCTransitionScene::onEnter();
    m_pInScene->setVisible(false);

    CCActionInterval* split = action();
    CCActionInterval* seq = (CCActionInterval*)CCSequence::create
    (
        split,
        CCCallFunc::create(this, callfunc_selector(CCTransitionScene::hideOutShowIn)),
        split->reverse(),
        NULL
    );

    this->runAction
    ( 
        CCSequence::create
        (
            easeActionWithAction(seq),
            CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)),
            CCStopGrid::create(),
            NULL
        )
    );
}


CCActionInterval* CCTransitionSplitCols:: action()
{
    return CCSplitCols::create(3, m_fDuration/2.0f);
}


CCActionInterval* CCTransitionSplitCols::easeActionWithAction(CCActionInterval * action)
{
    return CCEaseInOut::create(action, 3.0f);
}


//
// SplitRows Transition
//
CCTransitionSplitRows::CCTransitionSplitRows()
{
}
CCTransitionSplitRows::~CCTransitionSplitRows()
{
}

CCTransitionSplitRows* CCTransitionSplitRows::create(float t, CCScene* scene)
{
    CCTransitionSplitRows* pScene = new CCTransitionSplitRows();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


CCTransitionSplitRows* CCTransitionSplitRows::transitionWithDuration(float t, CCScene* scene)
{
    CCTransitionSplitRows* pScene = new CCTransitionSplitRows();
    
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

CCActionInterval* CCTransitionSplitRows::action()
{
    return CCSplitRows::create(3, m_fDuration/2.0f);
}

//
// FadeTR Transition
//
CCTransitionFadeTR::CCTransitionFadeTR()
{
}
CCTransitionFadeTR::~CCTransitionFadeTR()
{
}

CCTransitionFadeTR* CCTransitionFadeTR::create(float t, CCScene* scene)
{
    CCTransitionFadeTR* pScene = new CCTransitionFadeTR();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


CCTransitionFadeTR* CCTransitionFadeTR::transitionWithDuration(float t, CCScene* scene)
{
    CCTransitionFadeTR* pScene = new CCTransitionFadeTR();
    
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
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
        CCSequence::create
        (
            easeActionWithAction(action),
            CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)), 
            CCStopGrid::create(),
            NULL
        )
    );
}


CCActionInterval*  CCTransitionFadeTR::actionWithSize(const ccGridSize& size)
{
    return CCFadeOutTRTiles::create(size, m_fDuration);
}

CCActionInterval* CCTransitionFadeTR:: easeActionWithAction(CCActionInterval* action)
{
    return action;
}


//
// FadeBL Transition
//

CCTransitionFadeBL::CCTransitionFadeBL()
{
}
CCTransitionFadeBL::~CCTransitionFadeBL()
{
}

CCTransitionFadeBL* CCTransitionFadeBL::create(float t, CCScene* scene)
{
    CCTransitionFadeBL* pScene = new CCTransitionFadeBL();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


CCTransitionFadeBL* CCTransitionFadeBL::transitionWithDuration(float t, CCScene* scene)
{
    CCTransitionFadeBL* pScene = new CCTransitionFadeBL();
    
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

CCActionInterval*  CCTransitionFadeBL::actionWithSize(const ccGridSize& size)
{
    return CCFadeOutBLTiles::create(size, m_fDuration);
}

//
// FadeUp Transition
//
CCTransitionFadeUp::CCTransitionFadeUp()
{
}
CCTransitionFadeUp::~CCTransitionFadeUp()
{
}

CCTransitionFadeUp* CCTransitionFadeUp::create(float t, CCScene* scene)
{
    CCTransitionFadeUp* pScene = new CCTransitionFadeUp();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


CCTransitionFadeUp* CCTransitionFadeUp::transitionWithDuration(float t, CCScene* scene)
{
    CCTransitionFadeUp* pScene = new CCTransitionFadeUp();
    
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

CCActionInterval* CCTransitionFadeUp::actionWithSize(const ccGridSize& size)
{
    return CCFadeOutUpTiles::create(size, m_fDuration);
}

//
// FadeDown Transition
//
CCTransitionFadeDown::CCTransitionFadeDown()
{
}
CCTransitionFadeDown::~CCTransitionFadeDown()
{
}

CCTransitionFadeDown* CCTransitionFadeDown::create(float t, CCScene* scene)
{
    CCTransitionFadeDown* pScene = new CCTransitionFadeDown();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


CCTransitionFadeDown* CCTransitionFadeDown::transitionWithDuration(float t, CCScene* scene)
{
    CCTransitionFadeDown* pScene = new CCTransitionFadeDown();
    
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

CCActionInterval* CCTransitionFadeDown::actionWithSize(const ccGridSize& size)
{
    return CCFadeOutDownTiles::create(size, m_fDuration);
}

NS_CC_END
