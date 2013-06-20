#include "ActionsProgressTest.h"
#include "../testResource.h"

static int sceneIdx = -1; 

#define MAX_LAYER    7

Layer* nextAction();
Layer* backAction();
Layer* restartAction();

Layer* createLayer(int nIndex)
{
    switch(nIndex)
    {
        case 0: return new SpriteProgressToRadial();
        case 1: return new SpriteProgressToHorizontal();
        case 2: return new SpriteProgressToVertical();
        case 3: return new SpriteProgressToRadialMidpointChanged();
        case 4: return new SpriteProgressBarVarious();
        case 5: return new SpriteProgressBarTintAndFade();
        case 6: return new SpriteProgressWithSpriteFrame();
    }

    return NULL;
}

Layer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    Layer* pLayer = createLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

Layer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    Layer* pLayer = createLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

Layer* restartAction()
{
    Layer* pLayer = createLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
} 


void ProgressActionsTestScene::runThisTest()
{
    addChild(nextAction());
    Director::sharedDirector()->replaceScene(this);
}


//------------------------------------------------------------------
//
// SpriteDemo
//
//------------------------------------------------------------------
SpriteDemo::SpriteDemo(void)
{
}

SpriteDemo::~SpriteDemo(void)
{
}

std::string SpriteDemo::title()
{
    return "ActionsProgressTest";
}

std::string SpriteDemo::subtitle()
{
    return "";
}

void SpriteDemo::onEnter()
{
    BaseTest::onEnter();

    LayerColor *background = LayerColor::create(ccc4(255,0,0,255));
    addChild(background, -10);
}

void SpriteDemo::restartCallback(Object* pSender)
{
    Scene* s = new ProgressActionsTestScene();
    s->addChild(restartAction()); 

    Director::sharedDirector()->replaceScene(s);
    s->release();
}

void SpriteDemo::nextCallback(Object* pSender)
{
    Scene* s = new ProgressActionsTestScene();
    s->addChild( nextAction() );
    Director::sharedDirector()->replaceScene(s);
    s->release();
}

void SpriteDemo::backCallback(Object* pSender)
{
    Scene* s = new ProgressActionsTestScene();
    s->addChild( backAction() );
    Director::sharedDirector()->replaceScene(s);
    s->release();
} 

//------------------------------------------------------------------
//
// SpriteProgressToRadial
//
//------------------------------------------------------------------
void SpriteProgressToRadial::onEnter()
{
    SpriteDemo::onEnter();
    
    Size s = Director::sharedDirector()->getWinSize();

    ProgressTo *to1 = ProgressTo::create(2, 100);
    ProgressTo *to2 = ProgressTo::create(2, 100);

    ProgressTimer *left = ProgressTimer::create(Sprite::create(s_pPathSister1));
    left->setType( kProgressTimerTypeRadial );
    addChild(left);
    left->setPosition(ccp(100, s.height/2));
    left->runAction( RepeatForever::create(to1));
    
    ProgressTimer *right = ProgressTimer::create(Sprite::create(s_pPathBlock));
    right->setType(kProgressTimerTypeRadial);
    // Makes the ridial CCW
    right->setReverseProgress(true);
    addChild(right);
    right->setPosition(ccp(s.width-100, s.height/2));
    right->runAction( RepeatForever::create(to2));
}

std::string SpriteProgressToRadial::subtitle()
{
    return "ProgressTo Radial";
}

//------------------------------------------------------------------
//
// SpriteProgressToHorizontal
//
//------------------------------------------------------------------

void SpriteProgressToHorizontal::onEnter()
{
    SpriteDemo::onEnter();
    
    Size s = Director::sharedDirector()->getWinSize();
    
    ProgressTo *to1 = ProgressTo::create(2, 100);
    ProgressTo *to2 = ProgressTo::create(2, 100);
    
    ProgressTimer *left = ProgressTimer::create(Sprite::create(s_pPathSister1));
    left->setType(kProgressTimerTypeBar);
    //    Setup for a bar starting from the left since the midpoint is 0 for the x
    left->setMidpoint(ccp(0,0));
    //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
    left->setBarChangeRate(ccp(1, 0));
    addChild(left);
    left->setPosition(ccp(100, s.height/2));
    left->runAction( RepeatForever::create(to1));
    
    ProgressTimer *right = ProgressTimer::create(Sprite::create(s_pPathSister2));
    right->setType(kProgressTimerTypeBar);
    //    Setup for a bar starting from the left since the midpoint is 1 for the x
    right->setMidpoint(ccp(1, 0));
    //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
    right->setBarChangeRate(ccp(1, 0));
    addChild(right);
    right->setPosition(ccp(s.width-100, s.height/2));
    right->runAction( RepeatForever::create(to2));
}

std::string SpriteProgressToHorizontal::subtitle()
{
    return "ProgressTo Horizontal";
}

//------------------------------------------------------------------
//
// SpriteProgressToVertical
//
//------------------------------------------------------------------
void SpriteProgressToVertical::onEnter()
{
    SpriteDemo::onEnter();
    
    Size s = Director::sharedDirector()->getWinSize();
    
    ProgressTo *to1 = ProgressTo::create(2, 100);
    ProgressTo *to2 = ProgressTo::create(2, 100);
    
    ProgressTimer *left = ProgressTimer::create(Sprite::create(s_pPathSister1));
    left->setType(kProgressTimerTypeBar);

    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left->setMidpoint(ccp(0,0));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left->setBarChangeRate(ccp(0, 1));
    addChild(left);
    left->setPosition(ccp(100, s.height/2));
    left->runAction( RepeatForever::create(to1));
    
    ProgressTimer *right = ProgressTimer::create(Sprite::create(s_pPathSister2));
    right->setType(kProgressTimerTypeBar);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right->setMidpoint(ccp(0, 1));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right->setBarChangeRate(ccp(0, 1));
    addChild(right);
    right->setPosition(ccp(s.width-100, s.height/2));
    right->runAction( RepeatForever::create(to2));
}

std::string SpriteProgressToVertical::subtitle()
{
    return "ProgressTo Vertical";
}

//------------------------------------------------------------------
//
// SpriteProgressToRadialMidpointChanged
//
//------------------------------------------------------------------
void SpriteProgressToRadialMidpointChanged::onEnter()
{
    SpriteDemo::onEnter();

    Size s = Director::sharedDirector()->getWinSize();

    ProgressTo *action = ProgressTo::create(2, 100);

    /**
   *  Our image on the left should be a radial progress indicator, clockwise
   */
    ProgressTimer *left = ProgressTimer::create(Sprite::create(s_pPathBlock));
    left->setType(kProgressTimerTypeRadial);
    addChild(left);
    left->setMidpoint(ccp(0.25f, 0.75f));
    left->setPosition(ccp(100, s.height/2));
    left->runAction(RepeatForever::create(action->clone()));

    /**
   *  Our image on the left should be a radial progress indicator, counter clockwise
   */
    ProgressTimer *right = ProgressTimer::create(Sprite::create(s_pPathBlock));
    right->setType(kProgressTimerTypeRadial);
    right->setMidpoint(ccp(0.75f, 0.25f));

    /**
   *  Note the reverse property (default=NO) is only added to the right image. That's how
   *  we get a counter clockwise progress.
   */
    addChild(right);
    right->setPosition(ccp(s.width-100, s.height/2));
    right->runAction(RepeatForever::create(action->clone()));
}

std::string SpriteProgressToRadialMidpointChanged::subtitle()
{
    return "Radial w/ Different Midpoints";
}

//------------------------------------------------------------------
//
// SpriteProgressBarVarious
//
//------------------------------------------------------------------
void SpriteProgressBarVarious::onEnter()
{
    SpriteDemo::onEnter();

    Size s = Director::sharedDirector()->getWinSize();

    ProgressTo *to = ProgressTo::create(2, 100);

    ProgressTimer *left = ProgressTimer::create(Sprite::create(s_pPathSister1));
    left->setType(kProgressTimerTypeBar);

    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left->setBarChangeRate(ccp(1, 0));
    addChild(left);
    left->setPosition(ccp(100, s.height/2));
    left->runAction(RepeatForever::create(to->clone()));

    ProgressTimer *middle = ProgressTimer::create(Sprite::create(s_pPathSister2));
    middle->setType(kProgressTimerTypeBar);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle->setBarChangeRate(ccp(1,1));
    addChild(middle);
    middle->setPosition(ccp(s.width/2, s.height/2));
    middle->runAction(RepeatForever::create(to->clone()));

    ProgressTimer *right = ProgressTimer::create(Sprite::create(s_pPathSister2));
    right->setType(kProgressTimerTypeBar);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right->setBarChangeRate(ccp(0, 1));
    addChild(right);
    right->setPosition(ccp(s.width-100, s.height/2));
    right->runAction(RepeatForever::create(to->clone()));
}

std::string SpriteProgressBarVarious::subtitle()
{
    return "ProgressTo Bar Mid";
}

//------------------------------------------------------------------
//
// SpriteProgressBarTintAndFade
//
//------------------------------------------------------------------
void SpriteProgressBarTintAndFade::onEnter()
{
    SpriteDemo::onEnter();

    Size s = Director::sharedDirector()->getWinSize();

    ProgressTo *to = ProgressTo::create(6, 100);
	auto tint = Sequence::create(TintTo::create(1, 255, 0, 0),
								   TintTo::create(1, 0, 255, 0),
								   TintTo::create(1, 0, 0, 255),
								   NULL);
	auto fade = Sequence::create(FadeTo::create(1.0f, 0),
								   FadeTo::create(1.0f, 255),
								   NULL);

    ProgressTimer *left = ProgressTimer::create(Sprite::create(s_pPathSister1));
    left->setType(kProgressTimerTypeBar);

    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left->setBarChangeRate(ccp(1, 0));
    addChild(left);
    left->setPosition(ccp(100, s.height/2));
    left->runAction(RepeatForever::create(to->clone()));
    left->runAction(RepeatForever::create(tint->clone()));

    left->addChild(LabelTTF::create("Tint", "Marker Felt", 20.0f));

    ProgressTimer *middle = ProgressTimer::create(Sprite::create(s_pPathSister2));
    middle->setType(kProgressTimerTypeBar);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle->setBarChangeRate(ccp(1, 1));
    addChild(middle);
    middle->setPosition(ccp(s.width/2, s.height/2));
    middle->runAction(RepeatForever::create(to->clone()));
    middle->runAction(RepeatForever::create(fade->clone()));

    middle->addChild(LabelTTF::create("Fade", "Marker Felt", 20.0f));

    ProgressTimer *right = ProgressTimer::create(Sprite::create(s_pPathSister2));
    right->setType(kProgressTimerTypeBar);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right->setBarChangeRate(ccp(0, 1));
    addChild(right);
    right->setPosition(ccp(s.width-100, s.height/2));
    right->runAction(RepeatForever::create(to->clone()));
	right->runAction(RepeatForever::create(tint->clone()));
    right->runAction(RepeatForever::create(fade->clone()));

    right->addChild(LabelTTF::create("Tint and Fade", "Marker Felt", 20.0f));
}

std::string SpriteProgressBarTintAndFade::subtitle()
{
    return "ProgressTo Bar Mid";
}

//------------------------------------------------------------------
//
// SpriteProgressWithSpriteFrame
//
//------------------------------------------------------------------
void SpriteProgressWithSpriteFrame::onEnter()
{
    SpriteDemo::onEnter();

    Size s = Director::sharedDirector()->getWinSize();

    ProgressTo *to = ProgressTo::create(6, 100);

    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zwoptex/grossini.plist");

    ProgressTimer *left = ProgressTimer::create(Sprite::createWithSpriteFrameName("grossini_dance_01.png"));
    left->setType(kProgressTimerTypeBar);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left->setBarChangeRate(ccp(1, 0));
    addChild(left);
    left->setPosition(ccp(100, s.height/2));
    left->runAction(RepeatForever::create(to->clone()));

    ProgressTimer *middle = ProgressTimer::create(Sprite::createWithSpriteFrameName("grossini_dance_02.png"));
    middle->setType(kProgressTimerTypeBar);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle->setBarChangeRate(ccp(1, 1));
    addChild(middle);
    middle->setPosition(ccp(s.width/2, s.height/2));
    middle->runAction(RepeatForever::create(to->clone()));

    ProgressTimer *right = ProgressTimer::create(Sprite::createWithSpriteFrameName("grossini_dance_03.png"));
    right->setType(kProgressTimerTypeRadial);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right->setBarChangeRate(ccp(0, 1));
    addChild(right);
    right->setPosition(ccp(s.width-100, s.height/2));
    right->runAction(RepeatForever::create(to->clone()));
}

std::string SpriteProgressWithSpriteFrame::subtitle()
{
    return "Progress With Sprite Frame";
}
