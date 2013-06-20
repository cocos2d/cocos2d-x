/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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
#include "misc_nodes/CCRenderTexture.h"
#include "misc_nodes/CCProgressTimer.h"
#include "CCLayer.h"
#include "actions/CCActionInstant.h"
#include "actions/CCActionProgressTimer.h"
#include "support/CCPointExtension.h"

NS_CC_BEGIN

enum {
    kSceneRadial = 0xc001,
};

TransitionProgress::TransitionProgress()
: _to(0.0f)
, _from(0.0f)
, _sceneToBeModified(NULL)
{

}

TransitionProgress* TransitionProgress::create(float t, Scene* scene)
{
    TransitionProgress* pScene = new TransitionProgress();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

// TransitionProgress
void TransitionProgress::onEnter()
{
    TransitionScene::onEnter();

    setupTransition();
    
    // create a transparent color layer
    // in which we are going to add our rendertextures
    Size size = Director::sharedDirector()->getWinSize();

    // create the second render texture for outScene
    RenderTexture *texture = RenderTexture::create((int)size.width, (int)size.height);
    texture->getSprite()->setAnchorPoint(ccp(0.5f,0.5f));
    texture->setPosition(ccp(size.width/2, size.height/2));
    texture->setAnchorPoint(ccp(0.5f,0.5f));

    // render outScene to its texturebuffer
    texture->clear(0, 0, 0, 1);
    texture->begin();
    _sceneToBeModified->visit();
    texture->end();


    //    Since we've passed the outScene to the texture we don't need it.
    if (_sceneToBeModified == _outScene)
    {
        hideOutShowIn();
    }
    //    We need the texture in RenderTexture.
    ProgressTimer *pNode = progressTimerNodeWithRenderTexture(texture);

    // create the blend action
    ActionInterval* layerAction = (ActionInterval*)Sequence::create(
        ProgressFromTo::create(_duration, _from, _to),
        CallFunc::create(this, callfunc_selector(TransitionProgress::finish)), 
        NULL);
    // run the blend action
    pNode->runAction(layerAction);

    // add the layer (which contains our two rendertextures) to the scene
    addChild(pNode, 2, kSceneRadial);
}

// clean up on exit
void TransitionProgress::onExit()
{
    // remove our layer and release all containing objects
    removeChildByTag(kSceneRadial, true);
    TransitionScene::onExit();
}

void TransitionProgress::sceneOrder()
{
    _isInSceneOnTop = false;
}

void TransitionProgress::setupTransition()
{
    _sceneToBeModified = _outScene;
    _from = 100;
    _to = 0;
}

ProgressTimer* TransitionProgress::progressTimerNodeWithRenderTexture(RenderTexture* texture)
{
    CCAssert(false, "override me - abstract class");
    return NULL;
}


// TransitionProgressRadialCCW

ProgressTimer* TransitionProgressRadialCCW::progressTimerNodeWithRenderTexture(RenderTexture* texture)
{
    Size size = Director::sharedDirector()->getWinSize();

    ProgressTimer* pNode = ProgressTimer::create(texture->getSprite());

    // but it is flipped upside down so we flip the sprite
    pNode->getSprite()->setFlipY(true);
    pNode->setType(kProgressTimerTypeRadial);

    //    Return the radial type that we want to use
    pNode->setReverseDirection(false);
    pNode->setPercentage(100);
    pNode->setPosition(ccp(size.width/2, size.height/2));
    pNode->setAnchorPoint(ccp(0.5f,0.5f));
    
    return pNode;
}

TransitionProgressRadialCCW* TransitionProgressRadialCCW::create(float t, Scene* scene)
{
    TransitionProgressRadialCCW* pScene = new TransitionProgressRadialCCW();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

// TransitionProgressRadialCW
TransitionProgressRadialCW* TransitionProgressRadialCW::create(float t, Scene* scene)
{
    TransitionProgressRadialCW* pScene = new TransitionProgressRadialCW();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

ProgressTimer* TransitionProgressRadialCW::progressTimerNodeWithRenderTexture(RenderTexture* texture)
{
    Size size = Director::sharedDirector()->getWinSize();
    
    ProgressTimer* pNode = ProgressTimer::create(texture->getSprite());
    
    // but it is flipped upside down so we flip the sprite
    pNode->getSprite()->setFlipY(true);
    pNode->setType( kProgressTimerTypeRadial );
    
    //    Return the radial type that we want to use
    pNode->setReverseDirection(true);
    pNode->setPercentage(100);
    pNode->setPosition(ccp(size.width/2, size.height/2));
    pNode->setAnchorPoint(ccp(0.5f,0.5f));
    
    return pNode;
}

// TransitionProgressHorizontal
TransitionProgressHorizontal* TransitionProgressHorizontal::create(float t, Scene* scene)
{
    TransitionProgressHorizontal* pScene = new TransitionProgressHorizontal();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

ProgressTimer* TransitionProgressHorizontal::progressTimerNodeWithRenderTexture(RenderTexture* texture)
{    
    Size size = Director::sharedDirector()->getWinSize();

    ProgressTimer* pNode = ProgressTimer::create(texture->getSprite());
    
    // but it is flipped upside down so we flip the sprite
    pNode->getSprite()->setFlipY(true);
    pNode->setType( kProgressTimerTypeBar);
    
    pNode->setMidpoint(ccp(1, 0));
    pNode->setBarChangeRate(ccp(1,0));
    
    pNode->setPercentage(100);
    pNode->setPosition(ccp(size.width/2, size.height/2));
    pNode->setAnchorPoint(ccp(0.5f,0.5f));

    return pNode;
}

// TransitionProgressVertical
TransitionProgressVertical* TransitionProgressVertical::create(float t, Scene* scene)
{
    TransitionProgressVertical* pScene = new TransitionProgressVertical();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

ProgressTimer* TransitionProgressVertical::progressTimerNodeWithRenderTexture(RenderTexture* texture)
{    
    Size size = Director::sharedDirector()->getWinSize();
    
    ProgressTimer* pNode = ProgressTimer::create(texture->getSprite());
    
    // but it is flipped upside down so we flip the sprite
    pNode->getSprite()->setFlipY(true);
    pNode->setType(kProgressTimerTypeBar);
    
    pNode->setMidpoint(ccp(0, 0));
    pNode->setBarChangeRate(ccp(0,1));
    
    pNode->setPercentage(100);
    pNode->setPosition(ccp(size.width/2, size.height/2));
    pNode->setAnchorPoint(ccp(0.5f,0.5f));
    
    return pNode;
}


// TransitionProgressInOut
TransitionProgressInOut* TransitionProgressInOut::create(float t, Scene* scene)
{
    TransitionProgressInOut* pScene = new TransitionProgressInOut();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void TransitionProgressInOut::sceneOrder()
{
    _isInSceneOnTop = false;
}

void TransitionProgressInOut::setupTransition()
{
    _sceneToBeModified = _inScene;
    _from = 0;
    _to = 100;    
}

ProgressTimer* TransitionProgressInOut::progressTimerNodeWithRenderTexture(RenderTexture* texture)
{    
    Size size = Director::sharedDirector()->getWinSize();
    
    ProgressTimer* pNode = ProgressTimer::create(texture->getSprite());
    
    // but it is flipped upside down so we flip the sprite
    pNode->getSprite()->setFlipY(true);
    pNode->setType( kProgressTimerTypeBar);
    
    pNode->setMidpoint(ccp(0.5f, 0.5f));
    pNode->setBarChangeRate(ccp(1, 1));
    
    pNode->setPercentage(0);
    pNode->setPosition(ccp(size.width/2, size.height/2));
    pNode->setAnchorPoint(ccp(0.5f,0.5f));
    
    return pNode;
}


// TransitionProgressOutIn
TransitionProgressOutIn* TransitionProgressOutIn::create(float t, Scene* scene)
{
    TransitionProgressOutIn* pScene = new TransitionProgressOutIn();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

ProgressTimer* TransitionProgressOutIn::progressTimerNodeWithRenderTexture(RenderTexture* texture)
{    
    Size size = Director::sharedDirector()->getWinSize();
    
    ProgressTimer* pNode = ProgressTimer::create(texture->getSprite());
    
    // but it is flipped upside down so we flip the sprite
    pNode->getSprite()->setFlipY(true);
    pNode->setType( kProgressTimerTypeBar );
    
    pNode->setMidpoint(ccp(0.5f, 0.5f));
    pNode->setBarChangeRate(ccp(1, 1));
    
    pNode->setPercentage(100);
    pNode->setPosition(ccp(size.width/2, size.height/2));
    pNode->setAnchorPoint(ccp(0.5f,0.5f));
    
    return pNode;
}

NS_CC_END

