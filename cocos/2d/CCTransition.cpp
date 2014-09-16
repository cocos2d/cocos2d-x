/****************************************************************************
Copyright (c) 2009-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "2d/CCTransition.h"
#include "2d/CCActionInterval.h"
#include "2d/CCActionInstant.h"
#include "2d/CCActionEase.h"
#include "2d/CCActionCamera.h"
#include "2d/CCActionTiledGrid.h"
#include "2d/CCActionGrid.h"
#include "2d/CCLayer.h"
#include "2d/CCRenderTexture.h"
#include "2d/CCNodeGrid.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"

NS_CC_BEGIN

const unsigned int kSceneFade = 0xFADEFADE;

TransitionScene::TransitionScene()
: _inScene(nullptr)
, _outScene(nullptr)
, _duration(0.0f)
, _isInSceneOnTop(false)
, _isSendCleanupToScene(false)
{
}

TransitionScene::~TransitionScene()
{
    CC_SAFE_RELEASE(_inScene);
    CC_SAFE_RELEASE(_outScene);
}

TransitionScene * TransitionScene::create(float t, Scene *scene)
{
    TransitionScene * pScene = new (std::nothrow) TransitionScene();
    if(pScene && pScene->initWithDuration(t,scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return nullptr;
}

bool TransitionScene::initWithDuration(float t, Scene *scene)
{
    CCASSERT( scene != nullptr, "Argument scene must be non-nil");

    if (Scene::init())
    {
        _duration = t;

        // retain
        _inScene = scene;
        _inScene->retain();
        _outScene = Director::getInstance()->getRunningScene();
        if (_outScene == nullptr)
        {
            _outScene = Scene::create();
        }
        _outScene->retain();

        CCASSERT( _inScene != _outScene, "Incoming scene must be different from the outgoing scene" );
        
        sceneOrder();

        return true;
    }
    else
    {
        return false;
    }
}

void TransitionScene::sceneOrder()
{
    _isInSceneOnTop = true;
}

void TransitionScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    Scene::draw(renderer, transform, flags);

    if( _isInSceneOnTop ) {
        _outScene->visit(renderer, transform, flags);
        _inScene->visit(renderer, transform, flags);
    } else {
        _inScene->visit(renderer, transform, flags);
        _outScene->visit(renderer, transform, flags);
    }
}

void TransitionScene::finish()
{
    // clean up
    _inScene->setVisible(true);
    _inScene->setPosition(0,0);
    _inScene->setScale(1.0f);
    _inScene->setRotation(0.0f);
    _inScene->setAdditionalTransform(nullptr);

    _outScene->setVisible(false);
    _outScene->setPosition(0,0);
    _outScene->setScale(1.0f);
    _outScene->setRotation(0.0f);
    _outScene->setAdditionalTransform(nullptr);

    //[self schedule:@selector(setNewScene:) interval:0];
    this->schedule(schedule_selector(TransitionScene::setNewScene), 0);
}

void TransitionScene::setNewScene(float dt)
{    
    CC_UNUSED_PARAM(dt);

    this->unschedule(schedule_selector(TransitionScene::setNewScene));
    
    // Before replacing, save the "send cleanup to scene"
    Director *director = Director::getInstance();
    _isSendCleanupToScene = director->isSendCleanupToScene();
    
    director->replaceScene(_inScene);
    
    // issue #267
    _outScene->setVisible(true);
}

void TransitionScene::hideOutShowIn()
{
    _inScene->setVisible(true);
    _outScene->setVisible(false);
}


// custom onEnter
void TransitionScene::onEnter()
{
    Scene::onEnter();
    
    // disable events while transitions
    _eventDispatcher->setEnabled(false);
    
    // outScene should not receive the onEnter callback
    // only the onExitTransitionDidStart
    _outScene->onExitTransitionDidStart();
    
    _inScene->onEnter();
}

// custom onExit
void TransitionScene::onExit()
{
    Scene::onExit();
    
    // enable events while transitions
    _eventDispatcher->setEnabled(true);
    _outScene->onExit();

    // _inScene should not receive the onEnter callback
    // only the onEnterTransitionDidFinish
    _inScene->onEnterTransitionDidFinish();
}

// custom cleanup
void TransitionScene::cleanup()
{
    Scene::cleanup();

    if( _isSendCleanupToScene )
        _outScene->cleanup();
}

//
// Oriented Transition
//

TransitionSceneOriented::TransitionSceneOriented()
{
}

TransitionSceneOriented::~TransitionSceneOriented()
{
}

TransitionSceneOriented * TransitionSceneOriented::create(float t, Scene *scene, Orientation orientation)
{
    TransitionSceneOriented * newScene = new (std::nothrow) TransitionSceneOriented();
    newScene->initWithDuration(t,scene,orientation);
    newScene->autorelease();
    return newScene;
}

bool TransitionSceneOriented::initWithDuration(float t, Scene *scene, Orientation orientation)
{
    if ( TransitionScene::initWithDuration(t, scene) )
    {
        _orientation = orientation;
    }
    return true;
}

//
// RotoZoom
//
TransitionRotoZoom::TransitionRotoZoom()
{
}

TransitionRotoZoom* TransitionRotoZoom::create(float t, Scene* scene)                   
{                                                               
    TransitionRotoZoom* newScene = new (std::nothrow) TransitionRotoZoom();
    if(newScene && newScene->initWithDuration(t, scene))
    {                                                           
        newScene->autorelease();
        return newScene;
    }                                                           
    CC_SAFE_DELETE(newScene);                                     
    return nullptr;                                                
}

TransitionRotoZoom::~TransitionRotoZoom()
{
}

void TransitionRotoZoom:: onEnter()
{
    TransitionScene::onEnter();

    _inScene->setScale(0.001f);
    _outScene->setScale(1.0f);

    _inScene->setAnchorPoint(Vec2(0.5f, 0.5f));
    _outScene->setAnchorPoint(Vec2(0.5f, 0.5f));

    ActionInterval *rotozoom = (ActionInterval*)(Sequence::create
    (
        Spawn::create
        (
            ScaleBy::create(_duration/2, 0.001f),
            RotateBy::create(_duration/2, 360 * 2),
            nullptr
        ),
        DelayTime::create(_duration/2),
        nullptr
    ));

    _outScene->runAction(rotozoom);
    _inScene->runAction
    (
        Sequence::create
        (
            rotozoom->reverse(),
            CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
            nullptr
        )
    );
}

//
// JumpZoom
//
TransitionJumpZoom::TransitionJumpZoom()
{
}
TransitionJumpZoom::~TransitionJumpZoom()
{
}

TransitionJumpZoom* TransitionJumpZoom::create(float t, Scene* scene)
{
    TransitionJumpZoom* newScene = new (std::nothrow) TransitionJumpZoom();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

void TransitionJumpZoom::onEnter()
{
    TransitionScene::onEnter();
    Size s = Director::getInstance()->getWinSize();

    _inScene->setScale(0.5f);
    _inScene->setPosition(s.width, 0);
    _inScene->setAnchorPoint(Vec2(0.5f, 0.5f));
    _outScene->setAnchorPoint(Vec2(0.5f, 0.5f));

    ActionInterval *jump = JumpBy::create(_duration/4, Vec2(-s.width,0), s.width/4, 2);
    ActionInterval *scaleIn = ScaleTo::create(_duration/4, 1.0f);
    ActionInterval *scaleOut = ScaleTo::create(_duration/4, 0.5f);

    ActionInterval *jumpZoomOut = (ActionInterval*)(Sequence::create(scaleOut, jump, nullptr));
    ActionInterval *jumpZoomIn = (ActionInterval*)(Sequence::create(jump, scaleIn, nullptr));

    ActionInterval *delay = DelayTime::create(_duration/2);

    _outScene->runAction(jumpZoomOut);
    _inScene->runAction
    (
        Sequence::create
        (
            delay,
            jumpZoomIn,
            CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
            nullptr
        )
    );
}

//
// MoveInL
//
TransitionMoveInL::TransitionMoveInL()
{
}

TransitionMoveInL::~TransitionMoveInL()
{
}

TransitionMoveInL* TransitionMoveInL::create(float t, Scene* scene)
{
    TransitionMoveInL* newScene = new (std::nothrow) TransitionMoveInL();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

void TransitionMoveInL::onEnter()
{
    TransitionScene::onEnter();
    this->initScenes();

    ActionInterval *a = this->action();

    _inScene->runAction
    (
        Sequence::create
        (
            this->easeActionWithAction(a),
            CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
            nullptr
        )
    );
}
 
ActionInterval* TransitionMoveInL::action()
{
    return MoveTo::create(_duration, Vec2(0,0));
}

ActionInterval* TransitionMoveInL::easeActionWithAction(ActionInterval* action)
{
    return EaseOut::create(action, 2.0f);
//    return [EaseElasticOut actionWithAction:action period:0.4f];
}

void TransitionMoveInL::initScenes()
{
    Size s = Director::getInstance()->getWinSize();
    _inScene->setPosition(-s.width,0);
}

//
// MoveInR
//
TransitionMoveInR::TransitionMoveInR()
{
}
TransitionMoveInR::~TransitionMoveInR()
{
}

TransitionMoveInR* TransitionMoveInR::create(float t, Scene* scene)
{
    TransitionMoveInR* newScene = new (std::nothrow) TransitionMoveInR();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

void TransitionMoveInR::initScenes()
{
    Size s = Director::getInstance()->getWinSize();
    _inScene->setPosition(s.width,0);
}

//
// MoveInT
//
TransitionMoveInT::TransitionMoveInT()
{
}
TransitionMoveInT::~TransitionMoveInT()
{
}

TransitionMoveInT* TransitionMoveInT::create(float t, Scene* scene)
{
    TransitionMoveInT* newScene = new (std::nothrow) TransitionMoveInT();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

void TransitionMoveInT::initScenes()
{
    Size s = Director::getInstance()->getWinSize();
    _inScene->setPosition(0,s.height);
}

//
// MoveInB
//
TransitionMoveInB::TransitionMoveInB()
{
}
TransitionMoveInB::~TransitionMoveInB()
{
}

TransitionMoveInB* TransitionMoveInB::create(float t, Scene* scene)
{
    TransitionMoveInB* newScene = new (std::nothrow) TransitionMoveInB();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

void TransitionMoveInB::initScenes()
{
    Size s = Director::getInstance()->getWinSize();
    _inScene->setPosition(0,-s.height);
}


//
// SlideInL
//

// The adjust factor is needed to prevent issue #442
// One solution is to use DONT_RENDER_IN_SUBPIXELS images, but NO
// The other issue is that in some transitions (and I don't know why)
// the order should be reversed (In in top of Out or vice-versa).
#define ADJUST_FACTOR 0.5f
TransitionSlideInL::TransitionSlideInL()
{
}

TransitionSlideInL::~TransitionSlideInL()
{
}

void TransitionSlideInL::onEnter()
{
    TransitionScene::onEnter();
    this->initScenes();

    ActionInterval *in = this->action();
    ActionInterval *out = this->action();

    ActionInterval* inAction = easeActionWithAction(in);
    ActionInterval* outAction = (ActionInterval*)Sequence::create
    (
        easeActionWithAction(out),
        CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
        nullptr
    );
    _inScene->runAction(inAction);
    _outScene->runAction(outAction);
}

void TransitionSlideInL::sceneOrder()
{
    _isInSceneOnTop = false;
}

void TransitionSlideInL:: initScenes()
{
    Size s = Director::getInstance()->getWinSize();
    _inScene->setPosition(-(s.width-ADJUST_FACTOR),0);
}

ActionInterval* TransitionSlideInL::action()
{
    Size s = Director::getInstance()->getWinSize();
    return MoveBy::create(_duration, Vec2(s.width-ADJUST_FACTOR,0));
}

ActionInterval* TransitionSlideInL::easeActionWithAction(ActionInterval* action)
{
    return EaseOut::create(action, 2.0f);
}

TransitionSlideInL* TransitionSlideInL::create(float t, Scene* scene)
{
    TransitionSlideInL* newScene = new (std::nothrow) TransitionSlideInL();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

//
// SlideInR
//
TransitionSlideInR::TransitionSlideInR()
{
}
TransitionSlideInR::~TransitionSlideInR()
{
}

TransitionSlideInR* TransitionSlideInR::create(float t, Scene* scene)
{
    TransitionSlideInR* newScene = new (std::nothrow) TransitionSlideInR();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

void TransitionSlideInR::sceneOrder()
{
    _isInSceneOnTop = true;
}

void TransitionSlideInR::initScenes()
{
    Size s = Director::getInstance()->getWinSize();
    _inScene->setPosition(s.width-ADJUST_FACTOR,0);
}


ActionInterval* TransitionSlideInR:: action()
{
    Size s = Director::getInstance()->getWinSize();
    return MoveBy::create(_duration, Vec2(-(s.width-ADJUST_FACTOR),0));
}


//
// SlideInT
//
TransitionSlideInT::TransitionSlideInT()
{
}
TransitionSlideInT::~TransitionSlideInT()
{
}

TransitionSlideInT* TransitionSlideInT::create(float t, Scene* scene)
{
    TransitionSlideInT* newScene = new (std::nothrow) TransitionSlideInT();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

void TransitionSlideInT::sceneOrder()
{
    _isInSceneOnTop = false;
}

void TransitionSlideInT::initScenes()
{
    Size s = Director::getInstance()->getWinSize();
    _inScene->setPosition(0,s.height-ADJUST_FACTOR);
}


ActionInterval* TransitionSlideInT::action()
{
    Size s = Director::getInstance()->getWinSize();
    return MoveBy::create(_duration, Vec2(0,-(s.height-ADJUST_FACTOR)));
}

//
// SlideInB
//
TransitionSlideInB::TransitionSlideInB()
{
}
TransitionSlideInB::~TransitionSlideInB()
{
}

TransitionSlideInB* TransitionSlideInB::create(float t, Scene* scene)
{
    TransitionSlideInB* newScene = new (std::nothrow) TransitionSlideInB();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

void TransitionSlideInB::sceneOrder()
{
    _isInSceneOnTop = true;
}

void TransitionSlideInB:: initScenes()
{
    Size s = Director::getInstance()->getWinSize();
    _inScene->setPosition(0,-(s.height-ADJUST_FACTOR));
}


ActionInterval* TransitionSlideInB:: action()
{
    Size s = Director::getInstance()->getWinSize();
    return MoveBy::create(_duration, Vec2(0,s.height-ADJUST_FACTOR));
}

//
// ShrinkGrow Transition
//
TransitionShrinkGrow::TransitionShrinkGrow()
{
}
TransitionShrinkGrow::~TransitionShrinkGrow()
{
}

TransitionShrinkGrow* TransitionShrinkGrow::create(float t, Scene* scene)
{
    TransitionShrinkGrow* newScene = new (std::nothrow) TransitionShrinkGrow();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

void TransitionShrinkGrow::onEnter()
{
    TransitionScene::onEnter();

    _inScene->setScale(0.001f);
    _outScene->setScale(1.0f);

    _inScene->setAnchorPoint(Vec2(2/3.0f,0.5f));
    _outScene->setAnchorPoint(Vec2(1/3.0f,0.5f));    

    ActionInterval* scaleOut = ScaleTo::create(_duration, 0.01f);
    ActionInterval* scaleIn = ScaleTo::create(_duration, 1.0f);

    _inScene->runAction(this->easeActionWithAction(scaleIn));
    _outScene->runAction
    (
        Sequence::create
        (
            this->easeActionWithAction(scaleOut),
            CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
            nullptr
        )
    );
}
ActionInterval* TransitionShrinkGrow:: easeActionWithAction(ActionInterval* action)
{
    return EaseOut::create(action, 2.0f);
//    return [EaseElasticOut actionWithAction:action period:0.3f];
}

//
// FlipX Transition
//
TransitionFlipX::TransitionFlipX()
{
}
TransitionFlipX::~TransitionFlipX()
{
}

void TransitionFlipX::onEnter()
{
    TransitionSceneOriented::onEnter();

    ActionInterval *inA, *outA;
    _inScene->setVisible(false);

    float inDeltaZ, inAngleZ;
    float outDeltaZ, outAngleZ;

    if( _orientation == TransitionScene::Orientation::RIGHT_OVER )
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

    inA = (ActionInterval*)Sequence::create
        (
            DelayTime::create(_duration/2),
            Show::create(),
            OrbitCamera::create(_duration/2, 1, 0, inAngleZ, inDeltaZ, 0, 0),
            CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
            nullptr
        );

    outA = (ActionInterval *)Sequence::create
        (
            OrbitCamera::create(_duration/2, 1, 0, outAngleZ, outDeltaZ, 0, 0),
            Hide::create(),
            DelayTime::create(_duration/2),                            
            nullptr 
        );

    _inScene->runAction(inA);
    _outScene->runAction(outA);
}

TransitionFlipX* TransitionFlipX::create(float t, Scene* s, Orientation o)
{
    TransitionFlipX* newScene = new (std::nothrow) TransitionFlipX();
    newScene->initWithDuration(t, s, o);
    newScene->autorelease();

    return newScene;
}

TransitionFlipX* TransitionFlipX::create(float t, Scene* s)
{
    return TransitionFlipX::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
}

//
// FlipY Transition
//
TransitionFlipY::TransitionFlipY()
{
}
TransitionFlipY::~TransitionFlipY()
{
}

void TransitionFlipY::onEnter()
{
    TransitionSceneOriented::onEnter();

    ActionInterval *inA, *outA;
    _inScene->setVisible(false);

    float inDeltaZ, inAngleZ;
    float outDeltaZ, outAngleZ;

    if( _orientation == TransitionScene::Orientation::UP_OVER ) 
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

    inA = (ActionInterval*)Sequence::create
        (
            DelayTime::create(_duration/2),
            Show::create(),
            OrbitCamera::create(_duration/2, 1, 0, inAngleZ, inDeltaZ, 90, 0),
            CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
            nullptr
        );
    outA = (ActionInterval*)Sequence::create
        (
            OrbitCamera::create(_duration/2, 1, 0, outAngleZ, outDeltaZ, 90, 0),
            Hide::create(),
            DelayTime::create(_duration/2),                            
            nullptr
        );

    _inScene->runAction(inA);
    _outScene->runAction(outA);

}

TransitionFlipY* TransitionFlipY::create(float t, Scene* s, Orientation o)
{
    TransitionFlipY* newScene = new (std::nothrow) TransitionFlipY();
    newScene->initWithDuration(t, s, o);
    newScene->autorelease();

    return newScene;
}

TransitionFlipY* TransitionFlipY::create(float t, Scene* s)
{
    return TransitionFlipY::create(t, s, TransitionScene::Orientation::UP_OVER);
}

//
// FlipAngular Transition
//
TransitionFlipAngular::TransitionFlipAngular()
{
}

TransitionFlipAngular::~TransitionFlipAngular()
{
}

void TransitionFlipAngular::onEnter()
{
    TransitionSceneOriented::onEnter();

    ActionInterval *inA, *outA;
    _inScene->setVisible(false);

    float inDeltaZ, inAngleZ;
    float outDeltaZ, outAngleZ;

    if( _orientation == TransitionScene::Orientation::RIGHT_OVER ) 
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

    inA = (ActionInterval *)Sequence::create
        (
            DelayTime::create(_duration/2),
            Show::create(),
            OrbitCamera::create(_duration/2, 1, 0, inAngleZ, inDeltaZ, -45, 0),
            CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
            nullptr
        );
    outA = (ActionInterval *)Sequence::create
        (
            OrbitCamera::create(_duration/2, 1, 0, outAngleZ, outDeltaZ, 45, 0),
            Hide::create(),
            DelayTime::create(_duration/2),                            
            nullptr
        );

    _inScene->runAction(inA);
    _outScene->runAction(outA);
}

TransitionFlipAngular* TransitionFlipAngular::create(float t, Scene* s, Orientation o)
{
    TransitionFlipAngular* newScene = new (std::nothrow) TransitionFlipAngular();
    newScene->initWithDuration(t, s, o);
    newScene->autorelease();

    return newScene;
}

TransitionFlipAngular* TransitionFlipAngular::create(float t, Scene* s)
{
    return TransitionFlipAngular::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
}

//
// ZoomFlipX Transition
//
TransitionZoomFlipX::TransitionZoomFlipX()
{
}
TransitionZoomFlipX::~TransitionZoomFlipX()
{
}

void TransitionZoomFlipX::onEnter()
{
    TransitionSceneOriented::onEnter();

    ActionInterval *inA, *outA;
    _inScene->setVisible(false);

    float inDeltaZ, inAngleZ;
    float outDeltaZ, outAngleZ;

    if( _orientation == TransitionScene::Orientation::RIGHT_OVER ) {
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
    inA = (ActionInterval *)Sequence::create
        (
            DelayTime::create(_duration/2),
            Spawn::create
            (
                OrbitCamera::create(_duration/2, 1, 0, inAngleZ, inDeltaZ, 0, 0),
                ScaleTo::create(_duration/2, 1),
                Show::create(),
                nullptr
            ),
            CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
            nullptr
        );
    outA = (ActionInterval *)Sequence::create
        (
            Spawn::create
            (
                OrbitCamera::create(_duration/2, 1, 0, outAngleZ, outDeltaZ, 0, 0),
                ScaleTo::create(_duration/2, 0.5f),
                nullptr
            ),
            Hide::create(),
            DelayTime::create(_duration/2),                            
            nullptr
        );

    _inScene->setScale(0.5f);
    _inScene->runAction(inA);
    _outScene->runAction(outA);
}

TransitionZoomFlipX* TransitionZoomFlipX::create(float t, Scene* s, Orientation o)
{
    TransitionZoomFlipX* newScene = new (std::nothrow) TransitionZoomFlipX();
    newScene->initWithDuration(t, s, o);
    newScene->autorelease();

    return newScene;
}

TransitionZoomFlipX* TransitionZoomFlipX::create(float t, Scene* s)
{
    return TransitionZoomFlipX::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
}

//
// ZoomFlipY Transition
//
TransitionZoomFlipY::TransitionZoomFlipY()
{
}

TransitionZoomFlipY::~TransitionZoomFlipY()
{
}

void TransitionZoomFlipY::onEnter()
{
    TransitionSceneOriented::onEnter();

    ActionInterval *inA, *outA;
    _inScene->setVisible(false);

    float inDeltaZ, inAngleZ;
    float outDeltaZ, outAngleZ;

    if( _orientation== TransitionScene::Orientation::UP_OVER ) {
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

    inA = (ActionInterval *)Sequence::create
        (
            DelayTime::create(_duration/2),
            Spawn::create
            (
                OrbitCamera::create(_duration/2, 1, 0, inAngleZ, inDeltaZ, 90, 0),
                ScaleTo::create(_duration/2, 1),
                Show::create(),
                nullptr
            ),
            CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
            nullptr
        );

    outA = (ActionInterval *)Sequence::create
        (
            Spawn::create
            (
                OrbitCamera::create(_duration/2, 1, 0, outAngleZ, outDeltaZ, 90, 0),
                ScaleTo::create(_duration/2, 0.5f),
                nullptr
            ),                            
            Hide::create(),
            DelayTime::create(_duration/2),
            nullptr
        );

    _inScene->setScale(0.5f);
    _inScene->runAction(inA);
    _outScene->runAction(outA);
}

TransitionZoomFlipY* TransitionZoomFlipY::create(float t, Scene* s, Orientation o)
{
    TransitionZoomFlipY* newScene = new (std::nothrow) TransitionZoomFlipY();
    newScene->initWithDuration(t, s, o);
    newScene->autorelease();

    return newScene;
}

TransitionZoomFlipY* TransitionZoomFlipY::create(float t, Scene* s)
{
    return TransitionZoomFlipY::create(t, s, TransitionScene::Orientation::UP_OVER);
}

//
// ZoomFlipAngular Transition
//
TransitionZoomFlipAngular::TransitionZoomFlipAngular()
{
}
TransitionZoomFlipAngular::~TransitionZoomFlipAngular()
{
}


void TransitionZoomFlipAngular::onEnter()
{
    TransitionSceneOriented::onEnter();

    ActionInterval *inA, *outA;
    _inScene->setVisible(false);

    float inDeltaZ, inAngleZ;
    float outDeltaZ, outAngleZ;

    if( _orientation == TransitionScene::Orientation::RIGHT_OVER ) {
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

    inA = (ActionInterval *)Sequence::create
        (
            DelayTime::create(_duration/2),
            Spawn::create
            (
                OrbitCamera::create(_duration/2, 1, 0, inAngleZ, inDeltaZ, -45, 0),
                ScaleTo::create(_duration/2, 1),
                Show::create(),
                nullptr
            ),
            Show::create(),
            CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
            nullptr
        );
    outA = (ActionInterval *)Sequence::create
        (
            Spawn::create
            (
                OrbitCamera::create(_duration/2, 1, 0 , outAngleZ, outDeltaZ, 45, 0),
                ScaleTo::create(_duration/2, 0.5f),
                nullptr
            ),                            
            Hide::create(),
            DelayTime::create(_duration/2),                            
            nullptr
        );

    _inScene->setScale(0.5f);
    _inScene->runAction(inA);
    _outScene->runAction(outA);
}

TransitionZoomFlipAngular* TransitionZoomFlipAngular::create(float t, Scene* s, Orientation o)
{
    TransitionZoomFlipAngular* newScene = new (std::nothrow) TransitionZoomFlipAngular();
    newScene->initWithDuration(t, s, o);
    newScene->autorelease();

    return newScene;
}

TransitionZoomFlipAngular* TransitionZoomFlipAngular::create(float t, Scene* s)
{
    return TransitionZoomFlipAngular::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
}

//
// Fade Transition
//
TransitionFade::TransitionFade()
{
}
TransitionFade::~TransitionFade()
{
}

TransitionFade * TransitionFade::create(float duration, Scene *scene, const Color3B& color)
{
    TransitionFade * transition = new (std::nothrow) TransitionFade();
    transition->initWithDuration(duration, scene, color);
    transition->autorelease();
    return transition;
}

TransitionFade* TransitionFade::create(float duration,Scene* scene)
{
    return TransitionFade::create(duration, scene, Color3B::BLACK);
}

bool TransitionFade::initWithDuration(float duration, Scene *scene, const Color3B& color)
{
    if (TransitionScene::initWithDuration(duration, scene))
    {
        _color.r = color.r;
        _color.g = color.g;
        _color.b = color.b;
        _color.a = 0;
    }
    return true;
}

bool TransitionFade::initWithDuration(float t, Scene *scene)
{
    this->initWithDuration(t, scene, Color3B::BLACK);
    return true;
}

void TransitionFade :: onEnter()
{
    TransitionScene::onEnter();

    LayerColor* l = LayerColor::create(_color);
    _inScene->setVisible(false);

    addChild(l, 2, kSceneFade);
    Node* f = getChildByTag(kSceneFade);

    ActionInterval* a = (ActionInterval *)Sequence::create
        (
            FadeIn::create(_duration/2),
            CallFunc::create(CC_CALLBACK_0(TransitionScene::hideOutShowIn,this)),
            FadeOut::create(_duration/2),
            CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),

         nullptr
        );
    f->runAction(a);
}

void TransitionFade::onExit()
{
    TransitionScene::onExit();
    this->removeChildByTag(kSceneFade, false);
}

//
// Cross Fade Transition
//
TransitionCrossFade::TransitionCrossFade()
{
}
TransitionCrossFade::~TransitionCrossFade()
{
}

TransitionCrossFade* TransitionCrossFade::create(float t, Scene* scene)
{
    TransitionCrossFade* newScene = new (std::nothrow) TransitionCrossFade();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

void TransitionCrossFade::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    // override draw since both scenes (textures) are rendered in 1 scene
}

void TransitionCrossFade::onEnter()
{
    TransitionScene::onEnter();

    // create a transparent color layer
    // in which we are going to add our rendertextures
    Color4B  color(0,0,0,0);
    Size size = Director::getInstance()->getWinSize();
    LayerColor* layer = LayerColor::create(color);

    // create the first render texture for inScene
    RenderTexture* inTexture = RenderTexture::create((int)size.width, (int)size.height,Texture2D::PixelFormat::RGBA8888,GL_DEPTH24_STENCIL8);

    if (nullptr == inTexture)
    {
        return;
    }

    inTexture->getSprite()->setAnchorPoint( Vec2(0.5f,0.5f) );
    inTexture->setPosition(size.width/2, size.height/2);
    inTexture->setAnchorPoint( Vec2(0.5f,0.5f) );

    // render inScene to its texturebuffer
    inTexture->begin();
    _inScene->visit();
    inTexture->end();

    // create the second render texture for outScene
    RenderTexture* outTexture = RenderTexture::create((int)size.width, (int)size.height,Texture2D::PixelFormat::RGBA8888,GL_DEPTH24_STENCIL8);
    outTexture->getSprite()->setAnchorPoint( Vec2(0.5f,0.5f) );
    outTexture->setPosition(size.width/2, size.height/2);
    outTexture->setAnchorPoint( Vec2(0.5f,0.5f) );

    // render outScene to its texturebuffer
    outTexture->begin();
    _outScene->visit();
    outTexture->end();

    // create blend functions

    BlendFunc blend1 = {GL_ONE, GL_ONE}; // inScene will lay on background and will not be used with alpha
    BlendFunc blend2 = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}; // we are going to blend outScene via alpha 

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
    Action* layerAction = Sequence::create
    (
        FadeTo::create(_duration, 0),
        CallFunc::create(CC_CALLBACK_0(TransitionScene::hideOutShowIn,this)),
        CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
        nullptr
    );


    // run the blend action
    outTexture->getSprite()->runAction( layerAction );

    // add the layer (which contains our two rendertextures) to the scene
    addChild(layer, 2, kSceneFade);
}

// clean up on exit
void TransitionCrossFade::onExit()
{
    // remove our layer and release all containing objects 
    this->removeChildByTag(kSceneFade, false);
    TransitionScene::onExit();
}

//
// TurnOffTilesTransition
//
TransitionTurnOffTiles::TransitionTurnOffTiles()
{
    _outSceneProxy = NodeGrid::create();
    _outSceneProxy->retain();
}

TransitionTurnOffTiles::~TransitionTurnOffTiles()
{
    CC_SAFE_RELEASE(_outSceneProxy);
}

TransitionTurnOffTiles* TransitionTurnOffTiles::create(float t, Scene* scene)
{
    TransitionTurnOffTiles* newScene = new (std::nothrow) TransitionTurnOffTiles();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

// override addScenes, and change the order
void TransitionTurnOffTiles::sceneOrder()
{
    _isInSceneOnTop = false;
}

void TransitionTurnOffTiles::onEnter()
{
    TransitionScene::onEnter();
    _outSceneProxy->setTarget(_outScene);
    _outSceneProxy->onEnter();

    Size s = Director::getInstance()->getWinSize();
    float aspect = s.width / s.height;
    int x = (int)(12 * aspect);
    int y = 12;

    TurnOffTiles* toff = TurnOffTiles::create(_duration, Size(x,y));
    ActionInterval* action = easeActionWithAction(toff);
    _outSceneProxy->runAction
    (
        Sequence::create
        (
            action,
            CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
            StopGrid::create(),
            nullptr
        )
    );
}

void TransitionTurnOffTiles::onExit()
{
    _outSceneProxy->setTarget(nullptr);
    _outSceneProxy->onExit();
    TransitionScene::onExit();
}

void TransitionTurnOffTiles::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    Scene::draw(renderer, transform, flags);
    
    if( _isInSceneOnTop )
    {
        _outSceneProxy->visit(renderer, transform, flags);
        _inScene->visit(renderer, transform, flags);
    } 
    else
    {
        _inScene->visit(renderer, transform, flags);
        _outSceneProxy->visit(renderer, transform, flags);
    }
}


ActionInterval* TransitionTurnOffTiles:: easeActionWithAction(ActionInterval* action)
{
    return action;
}

//
// SplitCols Transition
//
TransitionSplitCols::TransitionSplitCols()
{
    _gridProxy = NodeGrid::create();
    _gridProxy->retain();
}
TransitionSplitCols::~TransitionSplitCols()
{
    CC_SAFE_RELEASE(_gridProxy);
}

TransitionSplitCols* TransitionSplitCols::create(float t, Scene* scene)
{
    TransitionSplitCols* newScene = new (std::nothrow) TransitionSplitCols();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

void TransitionSplitCols::onEnter()
{
    TransitionScene::onEnter();

    _gridProxy->setTarget(_outScene);
    _gridProxy->onEnter();

    ActionInterval* split = action();
    ActionInterval* seq = (ActionInterval*)Sequence::create
    (
        split,
        CallFunc::create(CC_CALLBACK_0(TransitionSplitCols::switchTargetToInscene,this)),
        split->reverse(),
        nullptr
    );

    _gridProxy->runAction
    ( 
        Sequence::create
        (
            easeActionWithAction(seq),
            CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
            StopGrid::create(),
            nullptr
        )
    );
}

void TransitionSplitCols::switchTargetToInscene()
{
    _gridProxy->setTarget(_inScene);
}

void TransitionSplitCols::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    Scene::draw(renderer, transform, flags);
    _gridProxy->visit(renderer, transform, flags);
}

void TransitionSplitCols::onExit()
{
    _gridProxy->setTarget(nullptr);
    _gridProxy->onExit();
    TransitionScene::onExit();
}

ActionInterval* TransitionSplitCols:: action()
{
    return SplitCols::create(_duration/2.0f, 3);
}


ActionInterval* TransitionSplitCols::easeActionWithAction(ActionInterval * action)
{
    return EaseInOut::create(action, 3.0f);
}


//
// SplitRows Transition
//
TransitionSplitRows::TransitionSplitRows()
{
}

TransitionSplitRows::~TransitionSplitRows()
{
}

ActionInterval* TransitionSplitRows::action()
{
    return SplitRows::create(_duration/2.0f, 3);
}

TransitionSplitRows* TransitionSplitRows::create(float t, Scene* scene)
{
    TransitionSplitRows* newScene = new (std::nothrow) TransitionSplitRows();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

//
// FadeTR Transition
//
TransitionFadeTR::TransitionFadeTR()
{
    _outSceneProxy = NodeGrid::create();
    _outSceneProxy->retain();
}
TransitionFadeTR::~TransitionFadeTR()
{
    CC_SAFE_RELEASE(_outSceneProxy);
}

TransitionFadeTR* TransitionFadeTR::create(float t, Scene* scene)
{
    TransitionFadeTR* newScene = new (std::nothrow) TransitionFadeTR();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

void TransitionFadeTR::sceneOrder()
{
    _isInSceneOnTop = false;
}

void TransitionFadeTR::onEnter()
{
    TransitionScene::onEnter();

    _outSceneProxy->setTarget(_outScene);
    _outSceneProxy->onEnter();

    Size s = Director::getInstance()->getWinSize();
    float aspect = s.width / s.height;
    int x = (int)(12 * aspect);
    int y = 12;

    ActionInterval* action  = actionWithSize(Size(x,y));

    _outSceneProxy->runAction
    (
        Sequence::create
        (
            easeActionWithAction(action),
            CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
            StopGrid::create(),
            nullptr
        )
    );
}

void TransitionFadeTR::onExit()
{
    _outSceneProxy->setTarget(nullptr);
    _outSceneProxy->onExit();
    TransitionScene::onExit();
}

void TransitionFadeTR::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    Scene::draw(renderer, transform, flags);
    
    if( _isInSceneOnTop )
    {
        _outSceneProxy->visit(renderer, transform, flags);
        _inScene->visit(renderer, transform, flags);
    } 
    else
    {
        _inScene->visit(renderer, transform, flags);
        _outSceneProxy->visit(renderer, transform, flags);
    }
}

ActionInterval*  TransitionFadeTR::actionWithSize(const Size& size)
{
    return FadeOutTRTiles::create(_duration, size);
}

ActionInterval* TransitionFadeTR:: easeActionWithAction(ActionInterval* action)
{
    return action;
}


//
// FadeBL Transition
//

TransitionFadeBL::TransitionFadeBL()
{
}
TransitionFadeBL::~TransitionFadeBL()
{
}

TransitionFadeBL* TransitionFadeBL::create(float t, Scene* scene)
{
    TransitionFadeBL* newScene = new (std::nothrow) TransitionFadeBL();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

ActionInterval*  TransitionFadeBL::actionWithSize(const Size& size)
{
    return FadeOutBLTiles::create(_duration, size);
}

//
// FadeUp Transition
//
TransitionFadeUp::TransitionFadeUp()
{
}

TransitionFadeUp::~TransitionFadeUp()
{
}

TransitionFadeUp* TransitionFadeUp::create(float t, Scene* scene)
{
    TransitionFadeUp* newScene = new (std::nothrow) TransitionFadeUp();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

ActionInterval* TransitionFadeUp::actionWithSize(const Size& size)
{
    return FadeOutUpTiles::create(_duration, size);
}

//
// FadeDown Transition
//
TransitionFadeDown::TransitionFadeDown()
{
}
TransitionFadeDown::~TransitionFadeDown()
{
}

TransitionFadeDown* TransitionFadeDown::create(float t, Scene* scene)
{
    TransitionFadeDown* newScene = new (std::nothrow) TransitionFadeDown();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

ActionInterval* TransitionFadeDown::actionWithSize(const Size& size)
{
    return FadeOutDownTiles::create(_duration, size);
}

NS_CC_END
