#include "TransitionsTest.h"
#include "CCDirector.h"
#include "CCSprite.h"
#include "CCMenu.h"
#include "CCLabel.h"
#include "CCTransition.h"
#include "CCRadialTransition.h"
#include "CCPageTurnTransition.h"

#define MAX_LAYER	37
#define TRANSITION_DURATION (1.2f)

static const char s_back1[]         = "/NEWPLUS/TDA_DATA/Data/cocos2d_tests/Images/background1.png";
static const char s_back2[]         = "/NEWPLUS/TDA_DATA/Data/cocos2d_tests/Images/background2.png";
static const char s_pPathB1[]       = "/NEWPLUS/TDA_DATA/Data/cocos2d_tests/Images/b1.png";
static const char s_pPathB2[]       = "/NEWPLUS/TDA_DATA/Data/cocos2d_tests/Images/b2.png";
static const char s_pPathR1[]       = "/NEWPLUS/TDA_DATA/Data/cocos2d_tests/Images/r1.png";
static const char s_pPathR2[]       = "/NEWPLUS/TDA_DATA/Data/cocos2d_tests/Images/r2.png";
static const char s_pPathF1[]       = "/NEWPLUS/TDA_DATA/Data/cocos2d_tests/Images/f1.png";
static const char s_pPathF2[]       = "/NEWPLUS/TDA_DATA/Data/cocos2d_tests/Images/f2.png";


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

static std::string transitions[] = {
    "JumpZoomTransition",
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
};

static int s_nSceneIdx = 0;

CCTransitionScene* createTransition(int nIndex, ccTime t, CCScene* s)
{
    switch(nIndex)
    {
    case 0: return CCJumpZoomTransition::transitionWithDuration(t, s);
    case 1: return CCCrossFadeTransition::transitionWithDuration(t,s);
    case 2: return CCRadialCCWTransition::transitionWithDuration(t,s);
    case 3: return CCRadialCWTransition::transitionWithDuration(t,s);
    case 4: return PageTransitionForward::transitionWithDuration(t, s);
    case 5: return PageTransitionBackward::transitionWithDuration(t, s);
    case 6: return CCFadeTRTransition::transitionWithDuration(t, s);
    case 7: return CCFadeBLTransition::transitionWithDuration(t, s);
    case 8: return CCFadeUpTransition::transitionWithDuration(t, s);
    case 9: return CCFadeDownTransition::transitionWithDuration(t, s);
    case 10: return CCTurnOffTilesTransition::transitionWithDuration(t, s);
    case 11: return CCSplitRowsTransition::transitionWithDuration(t, s);
    case 12: return CCSplitColsTransition::transitionWithDuration(t, s);
    case 13: return CCFadeTransition::transitionWithDuration(t, s);
    case 14: return FadeWhiteTransition::transitionWithDuration(t, s);
    case 15: return FlipXLeftOver::transitionWithDuration(t, s);
    case 16: return FlipXRightOver::transitionWithDuration(t, s);
    case 17: return FlipYUpOver::transitionWithDuration(t, s);
    case 18: return FlipYDownOver::transitionWithDuration(t, s);
    case 19: return FlipAngularLeftOver::transitionWithDuration(t, s);
    case 20: return FlipAngularRightOver::transitionWithDuration(t, s);
    case 21: return ZoomFlipXLeftOver::transitionWithDuration(t, s);
    case 22: return ZoomFlipXRightOver::transitionWithDuration(t, s);
    case 23: return ZoomFlipYUpOver::transitionWithDuration(t, s);
    case 24: return ZoomFlipYDownOver::transitionWithDuration(t, s);
    case 25: return ZoomFlipAngularLeftOver::transitionWithDuration(t, s);
    case 26: return ZoomFlipAngularRightOver::transitionWithDuration(t, s);
    case 27: return CCShrinkGrowTransition::transitionWithDuration(t, s);
    case 28: return CCRotoZoomTransition::transitionWithDuration(t, s);
    case 29: return CCMoveInLTransition::transitionWithDuration(t, s);
    case 30: return CCMoveInRTransition::transitionWithDuration(t, s);
    case 31: return CCMoveInTTransition::transitionWithDuration(t, s);
    case 32: return CCMoveInBTransition::transitionWithDuration(t, s);
    case 33: return CCSlideInLTransition::transitionWithDuration(t, s);
    case 34: return CCSlideInRTransition::transitionWithDuration(t, s);
    case 35: return CCSlideInTTransition::transitionWithDuration(t, s);
    case 36: return CCSlideInBTransition::transitionWithDuration(t, s);
    }

    return NULL;
}							

CCScene* nextTransition( ccTime t, CCScene* s)
{
    s_nSceneIdx++;
    s_nSceneIdx = s_nSceneIdx % MAX_LAYER;

    CCTransitionScene* pTransition = createTransition(s_nSceneIdx, t, s);

    return pTransition;
}

CCScene* backTransition( ccTime t, CCScene* s)
{
    s_nSceneIdx--;
    int total = MAX_LAYER;
    if( s_nSceneIdx < 0 )
        s_nSceneIdx += total;	

    CCTransitionScene* pTransition = createTransition(s_nSceneIdx, t, s);

    return pTransition;
}

CCScene* restartTransition( ccTime t, CCScene* s)
{
    CCTransitionScene* pTransition = createTransition(s_nSceneIdx, t, s);

    return pTransition;
} 

void TransitionsTestScene::runThisTest()
{
    CCLayer * pLayer = new TestLayer1();
    addChild(pLayer);

    CCDirector::getSharedDirector()->replaceScene(this);
}

TestLayer1::TestLayer1(void)
{
    float x,y;

    CGSize size = CCDirector::getSharedDirector()->getWinSize();
    x = size.width;
    y = size.height;

    CCSprite* bg1 = CCSprite::spriteWithFile(s_back1);
    bg1->setPosition( CGPointMake(size.width/2, size.height/2) );
    addChild(bg1, -1);

    CCLabel* title = CCLabel::labelWithString( (transitions[s_nSceneIdx]).c_str(), "Thonburi", 32 );
    addChild(title);
    title->setColor( ccc3(255,32,32) );
    title->setPosition( CGPointMake(x/2, y-100) );

    CCLabel* label = CCLabel::labelWithString("SCENE 1", "Marker Felt", 38);
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

    CCDirector::getSharedDirector()->replaceScene( restartTransition(TRANSITION_DURATION, s) );
}

void TestLayer1::nextCallback(NSObject* pSender)
{
    CCScene* s = new TransitionsTestScene();

    CCLayer* pLayer = new TestLayer2();
    s->addChild(pLayer);

    CCDirector::getSharedDirector()->replaceScene( nextTransition(TRANSITION_DURATION, s) );
}

void TestLayer1::backCallback(NSObject* pSender)
{
    CCScene* s = new TransitionsTestScene();

    CCLayer* pLayer = new TestLayer2();
    s->addChild(pLayer);

    CCDirector::getSharedDirector()->replaceScene( backTransition(TRANSITION_DURATION, s) );
}

void TestLayer1::step(ccTime dt)
{

}

TestLayer2::TestLayer2()
{
    float x,y;

    CGSize size = CCDirector::getSharedDirector()->getWinSize();
    x = size.width;
    y = size.height;

    CCSprite* bg1 = CCSprite::spriteWithFile(s_back2);
    bg1->setPosition( CGPointMake(size.width/2, size.height/2) );
    addChild(bg1, -1);

    CCLabel* title = CCLabel::labelWithString((transitions[s_nSceneIdx]).c_str(), "Thonburi", 32 );
    addChild(title);
    title->setColor( ccc3(255,32,32) );
    title->setPosition( CGPointMake(x/2, y-100) );

    CCLabel* label = CCLabel::labelWithString("SCENE 2", "Marker Felt", 38);
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
    CCScene* s = CCScene::node();

    CCLayer* pLayer = new TestLayer1();
    s->addChild(pLayer);

    CCDirector::getSharedDirector()->replaceScene( restartTransition(TRANSITION_DURATION, s) );
}

void TestLayer2::nextCallback(NSObject* pSender)
{
    CCScene* s = CCScene::node();

    CCLayer* pLayer = new TestLayer1();
    s->addChild(pLayer);

    CCDirector::getSharedDirector()->replaceScene( nextTransition(TRANSITION_DURATION, s) );
}

void TestLayer2::backCallback(NSObject* pSender)
{
    CCScene* s = CCScene::node();

    CCLayer* pLayer = new TestLayer1();
    s->addChild(pLayer);

    CCDirector::getSharedDirector()->replaceScene( backTransition(TRANSITION_DURATION, s) );
}

void TestLayer2::step(ccTime dt)
{

}
