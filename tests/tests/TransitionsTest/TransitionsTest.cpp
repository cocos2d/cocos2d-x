#include "TransitionsTest.h"
#include "../testResource.h"

#define TRANSITION_DURATION (1.2f)

class FadeWhiteTransition : public CCFadeTransition 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCFadeTransition::transitionWithDuration(t, s, ccWHITE); 
    }
};

class FlipXLeftOver : public CCFlipXTransition 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCFlipXTransition::transitionWithDuration(t, s, kOrientationLeftOver);
    }
};

class FlipXRightOver : public CCFlipXTransition 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCFlipXTransition::transitionWithDuration(t, s, kOrientationRightOver);
    }
};

class FlipYUpOver : public CCFlipYTransition 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCFlipYTransition::transitionWithDuration(t, s, kOrientationUpOver); 
    }
};

class FlipYDownOver : public CCFlipYTransition 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCFlipYTransition::transitionWithDuration(t, s, kOrientationDownOver); 
    }
};

class FlipAngularLeftOver : public CCFlipAngularTransition 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCFlipAngularTransition::transitionWithDuration(t, s, kOrientationLeftOver); 
    }
};

class FlipAngularRightOver : public CCFlipAngularTransition 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCFlipAngularTransition::transitionWithDuration(t, s, kOrientationRightOver);
    }
};

class ZoomFlipXLeftOver : public CCZoomFlipXTransition 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCZoomFlipXTransition::transitionWithDuration(t, s, kOrientationLeftOver); 
    }
};

class ZoomFlipXRightOver : public CCZoomFlipXTransition 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCZoomFlipXTransition::transitionWithDuration(t, s, kOrientationRightOver);
    }
};

class ZoomFlipYUpOver : public CCZoomFlipYTransition 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCZoomFlipYTransition::transitionWithDuration(t, s, kOrientationUpOver); 

    }
};

class ZoomFlipYDownOver : public CCZoomFlipYTransition 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCZoomFlipYTransition::transitionWithDuration(t, s, kOrientationDownOver); 
    }
};

class ZoomFlipAngularLeftOver : public CCZoomFlipAngularTransition 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCZoomFlipAngularTransition::transitionWithDuration(t, s, kOrientationLeftOver); 
    }
};

class ZoomFlipAngularRightOver : public CCZoomFlipAngularTransition 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCZoomFlipAngularTransition::transitionWithDuration(t, s, kOrientationRightOver);
    }
};

class PageTransitionForward : public CCPageTurnTransition
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCPageTurnTransition::transitionWithDuration(t, s, false);
    }
};

class PageTransitionBackward : public CCPageTurnTransition
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCPageTurnTransition::transitionWithDuration(t, s, true);
    }
};

#define MAX_LAYER	37

static std::string transitions[MAX_LAYER] = {
    "JumpZoomTransition",
    "FadeTransition",
    "FadeWhiteTransition",
    "FlipXLeftOver",
    "FlipXRightOver",
    "FlipYUpOver",
    "FlipYDownOver",
    "FlipAngularLeftOver",
    "FlipAngularRightOver",
    "ZoomFlipXLeftOver",
    "ZoomFlipXRightOver",
    "ZoomFlipYUpOver",
    "ZoomFlipYDownOver",
    "ZoomFlipAngularLeftOver",
    "ZoomFlipAngularRightOver",
    "ShrinkGrowTransition",
    "RotoZoomTransition",
    "MoveInLTransition",
    "MoveInRTransition",
    "MoveInTTransition",
    "MoveInBTransition",
    "SlideInLTransition",
    "SlideInRTransition",
    "SlideInTTransition",
    "SlideInBTransition",

    "CCCrossFadeTransition",
    "CCRadialCCWTransition",
    "CCRadialCWTransition",
    "PageTransitionForward",
    "PageTransitionBackward",
    "FadeTRTransition",
    "FadeBLTransition",
    "FadeUpTransition",
    "FadeDownTransition",
    "TurnOffTilesTransition",
    "SplitRowsTransition",
    "SplitColsTransition",
};
static int s_nSceneIdx = 0;

CCTransitionScene* createTransition(int nIndex, ccTime t, CCScene* s)
{
    switch(nIndex)
    {
    case 0: return CCJumpZoomTransition::transitionWithDuration(t, s);
    case 1: return CCFadeTransition::transitionWithDuration(t, s);
    case 2: return FadeWhiteTransition::transitionWithDuration(t, s);
    case 3: return FlipXLeftOver::transitionWithDuration(t, s);
    case 4: return FlipXRightOver::transitionWithDuration(t, s);
    case 5: return FlipYUpOver::transitionWithDuration(t, s);
    case 6: return FlipYDownOver::transitionWithDuration(t, s);
    case 7: return FlipAngularLeftOver::transitionWithDuration(t, s);
    case 8: return FlipAngularRightOver::transitionWithDuration(t, s);
    case 9: return ZoomFlipXLeftOver::transitionWithDuration(t, s);
    case 10: return ZoomFlipXRightOver::transitionWithDuration(t, s);
    case 11: return ZoomFlipYUpOver::transitionWithDuration(t, s);
    case 12: return ZoomFlipYDownOver::transitionWithDuration(t, s);
    case 13: return ZoomFlipAngularLeftOver::transitionWithDuration(t, s);
    case 14: return ZoomFlipAngularRightOver::transitionWithDuration(t, s);
    case 15: return CCShrinkGrowTransition::transitionWithDuration(t, s);
    case 16: return CCRotoZoomTransition::transitionWithDuration(t, s);
    case 17: return CCMoveInLTransition::transitionWithDuration(t, s);
    case 18: return CCMoveInRTransition::transitionWithDuration(t, s);
    case 19: return CCMoveInTTransition::transitionWithDuration(t, s);
    case 20: return CCMoveInBTransition::transitionWithDuration(t, s);
    case 21: return CCSlideInLTransition::transitionWithDuration(t, s);
    case 22: return CCSlideInRTransition::transitionWithDuration(t, s);
    case 23: return CCSlideInTTransition::transitionWithDuration(t, s);
    case 24: return CCSlideInBTransition::transitionWithDuration(t, s);

    case 25: return CCCrossFadeTransition::transitionWithDuration(t,s);
    case 26: return CCRadialCCWTransition::transitionWithDuration(t,s);
    case 27: return CCRadialCWTransition::transitionWithDuration(t,s);
    case 28: return PageTransitionForward::transitionWithDuration(t, s);
    case 29: return PageTransitionBackward::transitionWithDuration(t, s);
    case 30: return CCFadeTRTransition::transitionWithDuration(t, s);
    case 31: return CCFadeBLTransition::transitionWithDuration(t, s);
    case 32: return CCFadeUpTransition::transitionWithDuration(t, s);
    case 33: return CCFadeDownTransition::transitionWithDuration(t, s);
    case 34: return CCTurnOffTilesTransition::transitionWithDuration(t, s);
    case 35: return CCSplitRowsTransition::transitionWithDuration(t, s);
    case 36: return CCSplitColsTransition::transitionWithDuration(t, s);
    default: break;
    }

    return NULL;
}							


void TransitionsTestScene::runThisTest()
{
    CCLayer * pLayer = new TestLayer1();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}

TestLayer1::TestLayer1(void)
{
    float x,y;

    CGSize size = CCDirector::sharedDirector()->getWinSize();
    x = size.width;
    y = size.height;

    CCSprite* bg1 = CCSprite::spriteWithFile(s_back1);
    bg1->setPosition( CGPointMake(size.width/2, size.height/2) );
    addChild(bg1, -1);

    CCLabelTTF* title = CCLabelTTF::labelWithString( (transitions[s_nSceneIdx]).c_str(), "Thonburi", 32 );
    addChild(title);
    title->setColor( ccc3(255,32,32) );
    title->setPosition( CGPointMake(x/2, y-100) );

    CCLabelTTF* label = CCLabelTTF::labelWithString("SCENE 1", "Marker Felt", 38);
    label->setColor( ccc3(16,16,255));
    label->setPosition( CGPointMake(x/2,y/2));	
    addChild( label);

    // menu
    CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(TestLayer1::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(TestLayer1::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(TestLayer1::nextCallback) );

    CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

    menu->setPosition( CGPointZero );
    item1->setPosition( CGPointMake( size.width/2 - 100,30) );
    item2->setPosition( CGPointMake( size.width/2, 30) );
    item3->setPosition( CGPointMake( size.width/2 + 100,30) );

    addChild(menu, 1);	

    schedule( schedule_selector(TestLayer1::step), 1.0f); 
}

TestLayer1::~TestLayer1(void)
{

}

void TestLayer1::restartCallback(NSObject* pSender)
{
    CCScene* s = new TransitionsTestScene();

    CCLayer* pLayer = new TestLayer2();
    s->addChild(pLayer);

    CCScene* pScene = createTransition(s_nSceneIdx, TRANSITION_DURATION, s);
    s->release();
    pLayer->release();
    if (pScene)
    {
        CCDirector::sharedDirector()->replaceScene(pScene);
    }    
}

void TestLayer1::nextCallback(NSObject* pSender)
{
    s_nSceneIdx++;
    s_nSceneIdx = s_nSceneIdx % MAX_LAYER;

    CCScene* s = new TransitionsTestScene();

    CCLayer* pLayer = new TestLayer2();
    s->addChild(pLayer);

    CCScene* pScene = createTransition(s_nSceneIdx, TRANSITION_DURATION, s);
    s->release();
    pLayer->release();
    if (pScene)
    {
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

void TestLayer1::backCallback(NSObject* pSender)
{
    s_nSceneIdx--;
    int total = MAX_LAYER;
    if( s_nSceneIdx < 0 )
        s_nSceneIdx += total;	

    CCScene* s = new TransitionsTestScene();

    CCLayer* pLayer = new TestLayer2();
    s->addChild(pLayer);

    CCScene* pScene = createTransition(s_nSceneIdx, TRANSITION_DURATION, s);
    s->release();
    pLayer->release();
    if (pScene)
    {
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

void TestLayer1::step(ccTime dt)
{

}

TestLayer2::TestLayer2()
{
    float x,y;

    CGSize size = CCDirector::sharedDirector()->getWinSize();
    x = size.width;
    y = size.height;

    CCSprite* bg1 = CCSprite::spriteWithFile(s_back2);
    bg1->setPosition( CGPointMake(size.width/2, size.height/2) );
    addChild(bg1, -1);

    CCLabelTTF* title = CCLabelTTF::labelWithString((transitions[s_nSceneIdx]).c_str(), "Thonburi", 32 );
    addChild(title);
    title->setColor( ccc3(255,32,32) );
    title->setPosition( CGPointMake(x/2, y-100) );

    CCLabelTTF* label = CCLabelTTF::labelWithString("SCENE 2", "Marker Felt", 38);
    label->setColor( ccc3(16,16,255));
    label->setPosition( CGPointMake(x/2,y/2));	
    addChild( label);

    // menu
    CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(TestLayer2::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(TestLayer2::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(TestLayer2::nextCallback) );

    CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

    menu->setPosition( CGPointZero );
    item1->setPosition( CGPointMake( x/2 - 100,30) );
    item2->setPosition( CGPointMake( x/2, 30) );
    item3->setPosition( CGPointMake( x/2 + 100,30) );

    addChild(menu, 1);	

    schedule(schedule_selector(TestLayer2::step), 1.0f);
}

TestLayer2::~TestLayer2()
{

}

void TestLayer2::restartCallback(NSObject* pSender)
{
    CCScene* s = new TransitionsTestScene();

    CCLayer* pLayer = new TestLayer1();
    s->addChild(pLayer);

    CCScene* pScene = createTransition(s_nSceneIdx, TRANSITION_DURATION, s);
    s->release();
    pLayer->release();
    if (pScene)
    {
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

void TestLayer2::nextCallback(NSObject* pSender)
{
    s_nSceneIdx++;
    s_nSceneIdx = s_nSceneIdx % MAX_LAYER;

    CCScene* s = new TransitionsTestScene();

    CCLayer* pLayer = new TestLayer1();
    s->addChild(pLayer);

    CCScene* pScene = createTransition(s_nSceneIdx, TRANSITION_DURATION, s);
    s->release();
    pLayer->release();
    if (pScene)
    {
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

void TestLayer2::backCallback(NSObject* pSender)
{
    s_nSceneIdx--;
    int total = MAX_LAYER;
    if( s_nSceneIdx < 0 )
        s_nSceneIdx += total;	

    CCScene* s = new TransitionsTestScene();

    CCLayer* pLayer = new TestLayer1();
    s->addChild(pLayer);

    CCScene* pScene = createTransition(s_nSceneIdx, TRANSITION_DURATION, s);
    s->release();
    pLayer->release();
    if (pScene)
    {
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

void TestLayer2::step(ccTime dt)
{

}
