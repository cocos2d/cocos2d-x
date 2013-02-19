#include "ActionsProgressTest.h"
#include "../testResource.h"

static int sceneIdx = -1; 

#define MAX_LAYER    7

CCLayer* nextAction();
CCLayer* backAction();
CCLayer* restartAction();

CCLayer* createLayer(int nIndex)
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

CCLayer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    CCLayer* pLayer = createLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    CCLayer* pLayer = createLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* restartAction()
{
    CCLayer* pLayer = createLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
} 


void ProgressActionsTestScene::runThisTest()
{
    addChild(nextAction());
    CCDirector::sharedDirector()->replaceScene(this);
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
    CCLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Arial", 18);
    addChild(label, 1);
    label->setPosition( ccp(s.width/2, s.height-50) );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() ) 
    {
        CCLabelTTF* l = CCLabelTTF::create(strSubtitle.c_str(), "Thonburi", 22);
        addChild(l, 1);
        l->setPosition( ccp(s.width/2, s.height-80) );
    }    

    CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(SpriteDemo::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(SpriteDemo::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(SpriteDemo::nextCallback) );

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);
    menu->setPosition(CCPointZero);
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));   
    addChild(menu, 1);    

    CCLayerColor *background = CCLayerColor::create(ccc4(255,0,0,255));
    addChild(background, -10);
}

void SpriteDemo::restartCallback(CCObject* pSender)
{
    CCScene* s = new ProgressActionsTestScene();
    s->addChild(restartAction()); 

    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void SpriteDemo::nextCallback(CCObject* pSender)
{
    CCScene* s = new ProgressActionsTestScene();
    s->addChild( nextAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void SpriteDemo::backCallback(CCObject* pSender)
{
    CCScene* s = new ProgressActionsTestScene();
    s->addChild( backAction() );
    CCDirector::sharedDirector()->replaceScene(s);
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
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCProgressTo *to1 = CCProgressTo::create(2, 100);
    CCProgressTo *to2 = CCProgressTo::create(2, 100);

    CCProgressTimer *left = CCProgressTimer::create(CCSprite::create(s_pPathSister1));
    left->setType( kCCProgressTimerTypeRadial );
    addChild(left);
    left->setPosition(ccp(100, s.height/2));
    left->runAction( CCRepeatForever::create(to1));
    
    CCProgressTimer *right = CCProgressTimer::create(CCSprite::create(s_pPathBlock));
    right->setType(kCCProgressTimerTypeRadial);
    // Makes the ridial CCW
    right->setReverseProgress(true);
    addChild(right);
    right->setPosition(ccp(s.width-100, s.height/2));
    right->runAction( CCRepeatForever::create(to2));
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
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCProgressTo *to1 = CCProgressTo::create(2, 100);
    CCProgressTo *to2 = CCProgressTo::create(2, 100);
    
    CCProgressTimer *left = CCProgressTimer::create(CCSprite::create(s_pPathSister1));
    left->setType(kCCProgressTimerTypeBar);
    //    Setup for a bar starting from the left since the midpoint is 0 for the x
    left->setMidpoint(ccp(0,0));
    //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
    left->setBarChangeRate(ccp(1, 0));
    addChild(left);
    left->setPosition(ccp(100, s.height/2));
    left->runAction( CCRepeatForever::create(to1));
    
    CCProgressTimer *right = CCProgressTimer::create(CCSprite::create(s_pPathSister2));
    right->setType(kCCProgressTimerTypeBar);
    //    Setup for a bar starting from the left since the midpoint is 1 for the x
    right->setMidpoint(ccp(1, 0));
    //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
    right->setBarChangeRate(ccp(1, 0));
    addChild(right);
    right->setPosition(ccp(s.width-100, s.height/2));
    right->runAction( CCRepeatForever::create(to2));
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
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCProgressTo *to1 = CCProgressTo::create(2, 100);
    CCProgressTo *to2 = CCProgressTo::create(2, 100);
    
    CCProgressTimer *left = CCProgressTimer::create(CCSprite::create(s_pPathSister1));
    left->setType(kCCProgressTimerTypeBar);

    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left->setMidpoint(ccp(0,0));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left->setBarChangeRate(ccp(0, 1));
    addChild(left);
    left->setPosition(ccp(100, s.height/2));
    left->runAction( CCRepeatForever::create(to1));
    
    CCProgressTimer *right = CCProgressTimer::create(CCSprite::create(s_pPathSister2));
    right->setType(kCCProgressTimerTypeBar);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right->setMidpoint(ccp(0, 1));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right->setBarChangeRate(ccp(0, 1));
    addChild(right);
    right->setPosition(ccp(s.width-100, s.height/2));
    right->runAction( CCRepeatForever::create(to2));
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

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCProgressTo *action = CCProgressTo::create(2, 100);

    /**
   *  Our image on the left should be a radial progress indicator, clockwise
   */
    CCProgressTimer *left = CCProgressTimer::create(CCSprite::create(s_pPathBlock));
    left->setType(kCCProgressTimerTypeRadial);
    addChild(left);
    left->setMidpoint(ccp(0.25f, 0.75f));
    left->setPosition(ccp(100, s.height/2));
    left->runAction(CCRepeatForever::create((CCActionInterval *)action->copy()->autorelease()));

    /**
   *  Our image on the left should be a radial progress indicator, counter clockwise
   */
    CCProgressTimer *right = CCProgressTimer::create(CCSprite::create(s_pPathBlock));
    right->setType(kCCProgressTimerTypeRadial);
    right->setMidpoint(ccp(0.75f, 0.25f));

    /**
   *  Note the reverse property (default=NO) is only added to the right image. That's how
   *  we get a counter clockwise progress.
   */
    addChild(right);
    right->setPosition(ccp(s.width-100, s.height/2));
    right->runAction(CCRepeatForever::create((CCActionInterval *)action->copy()->autorelease()));
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

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCProgressTo *to = CCProgressTo::create(2, 100);

    CCProgressTimer *left = CCProgressTimer::create(CCSprite::create(s_pPathSister1));
    left->setType(kCCProgressTimerTypeBar);

    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left->setBarChangeRate(ccp(1, 0));
    addChild(left);
    left->setPosition(ccp(100, s.height/2));
    left->runAction(CCRepeatForever::create((CCActionInterval *)to->copy()->autorelease()));

    CCProgressTimer *middle = CCProgressTimer::create(CCSprite::create(s_pPathSister2));
    middle->setType(kCCProgressTimerTypeBar);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle->setBarChangeRate(ccp(1,1));
    addChild(middle);
    middle->setPosition(ccp(s.width/2, s.height/2));
    middle->runAction(CCRepeatForever::create((CCActionInterval *)to->copy()->autorelease()));

    CCProgressTimer *right = CCProgressTimer::create(CCSprite::create(s_pPathSister2));
    right->setType(kCCProgressTimerTypeBar);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right->setBarChangeRate(ccp(0, 1));
    addChild(right);
    right->setPosition(ccp(s.width-100, s.height/2));
    right->runAction(CCRepeatForever::create((CCActionInterval *)to->copy()->autorelease()));
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

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCProgressTo *to = CCProgressTo::create(6, 100);
    CCAction *tint = CCSequence::create(CCTintTo::create(1, 255, 0, 0),
                                         CCTintTo::create(1, 0, 255, 0),
                                         CCTintTo::create(1, 0, 0, 255),
                                         NULL);
    CCAction *fade = CCSequence::create(CCFadeTo::create(1.0f, 0),
                                         CCFadeTo::create(1.0f, 255),
                                         NULL);

    CCProgressTimer *left = CCProgressTimer::create(CCSprite::create(s_pPathSister1));
    left->setType(kCCProgressTimerTypeBar);

    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left->setBarChangeRate(ccp(1, 0));
    addChild(left);
    left->setPosition(ccp(100, s.height/2));
    left->runAction(CCRepeatForever::create((CCActionInterval *)to->copy()->autorelease()));
    left->runAction(CCRepeatForever::create((CCActionInterval *)tint->copy()->autorelease()));

    left->addChild(CCLabelTTF::create("Tint", "Marker Felt", 20.0f));

    CCProgressTimer *middle = CCProgressTimer::create(CCSprite::create(s_pPathSister2));
    middle->setType(kCCProgressTimerTypeBar);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle->setBarChangeRate(ccp(1, 1));
    addChild(middle);
    middle->setPosition(ccp(s.width/2, s.height/2));
    middle->runAction(CCRepeatForever::create((CCActionInterval *)to->copy()->autorelease()));
    middle->runAction(CCRepeatForever::create((CCActionInterval *)fade->copy()->autorelease()));

    middle->addChild(CCLabelTTF::create("Fade", "Marker Felt", 20.0f));

    CCProgressTimer *right = CCProgressTimer::create(CCSprite::create(s_pPathSister2));
    right->setType(kCCProgressTimerTypeBar);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right->setBarChangeRate(ccp(0, 1));
    addChild(right);
    right->setPosition(ccp(s.width-100, s.height/2));
    right->runAction(CCRepeatForever::create((CCActionInterval *)to->copy()->autorelease()));
    right->runAction(CCRepeatForever::create((CCActionInterval *)tint->copy()->autorelease()));
    right->runAction(CCRepeatForever::create((CCActionInterval *)fade->copy()->autorelease()));

    right->addChild(CCLabelTTF::create("Tint and Fade", "Marker Felt", 20.0f));
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

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCProgressTo *to = CCProgressTo::create(6, 100);

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zwoptex/grossini.plist");

    CCProgressTimer *left = CCProgressTimer::create(CCSprite::createWithSpriteFrameName("grossini_dance_01.png"));
    left->setType(kCCProgressTimerTypeBar);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left->setBarChangeRate(ccp(1, 0));
    addChild(left);
    left->setPosition(ccp(100, s.height/2));
    left->runAction(CCRepeatForever::create((CCActionInterval *)to->copy()->autorelease()));

    CCProgressTimer *middle = CCProgressTimer::create(CCSprite::createWithSpriteFrameName("grossini_dance_02.png"));
    middle->setType(kCCProgressTimerTypeBar);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle->setBarChangeRate(ccp(1, 1));
    addChild(middle);
    middle->setPosition(ccp(s.width/2, s.height/2));
    middle->runAction(CCRepeatForever::create((CCActionInterval *)to->copy()->autorelease()));

    CCProgressTimer *right = CCProgressTimer::create(CCSprite::createWithSpriteFrameName("grossini_dance_03.png"));
    right->setType(kCCProgressTimerTypeRadial);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right->setBarChangeRate(ccp(0, 1));
    addChild(right);
    right->setPosition(ccp(s.width-100, s.height/2));
    right->runAction(CCRepeatForever::create((CCActionInterval *)to->copy()->autorelease()));
}

std::string SpriteProgressWithSpriteFrame::subtitle()
{
    return "Progress With Sprite Frame";
}
