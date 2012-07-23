#include "TransitionsTest.h"
#include "../testResource.h"
#include "CCConfiguration.h"

#define TRANSITION_DURATION (1.2f)

class FadeWhiteTransition : public CCTransitionFade 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCTransitionFade::transitionWithDuration(t, s, ccWHITE); 
    }
};

class FlipXLeftOver : public CCTransitionFlipX 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCTransitionFlipX::transitionWithDuration(t, s, kOrientationLeftOver);
    }
};

class FlipXRightOver : public CCTransitionFlipX 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCTransitionFlipX::transitionWithDuration(t, s, kOrientationRightOver);
    }
};

class FlipYUpOver : public CCTransitionFlipY 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCTransitionFlipY::transitionWithDuration(t, s, kOrientationUpOver); 
    }
};

class FlipYDownOver : public CCTransitionFlipY 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCTransitionFlipY::transitionWithDuration(t, s, kOrientationDownOver); 
    }
};

class FlipAngularLeftOver : public CCTransitionFlipAngular 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCTransitionFlipAngular::transitionWithDuration(t, s, kOrientationLeftOver); 
    }
};

class FlipAngularRightOver : public CCTransitionFlipAngular 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCTransitionFlipAngular::transitionWithDuration(t, s, kOrientationRightOver);
    }
};

class ZoomFlipXLeftOver : public CCTransitionZoomFlipX 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCTransitionZoomFlipX::transitionWithDuration(t, s, kOrientationLeftOver); 
    }
};

class ZoomFlipXRightOver : public CCTransitionZoomFlipX 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCTransitionZoomFlipX::transitionWithDuration(t, s, kOrientationRightOver);
    }
};

class ZoomFlipYUpOver : public CCTransitionZoomFlipY 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCTransitionZoomFlipY::transitionWithDuration(t, s, kOrientationUpOver); 

    }
};

class ZoomFlipYDownOver : public CCTransitionZoomFlipY 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCTransitionZoomFlipY::transitionWithDuration(t, s, kOrientationDownOver); 
    }
};

class ZoomFlipAngularLeftOver : public CCTransitionZoomFlipAngular 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCTransitionZoomFlipAngular::transitionWithDuration(t, s, kOrientationLeftOver); 
    }
};

class ZoomFlipAngularRightOver : public CCTransitionZoomFlipAngular 
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        return CCTransitionZoomFlipAngular::transitionWithDuration(t, s, kOrientationRightOver);
    }
};

class PageTransitionForward : public CCTransitionPageTurn
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        CCDirector::sharedDirector()->setDepthTest(true);
        return CCTransitionPageTurn::transitionWithDuration(t, s, false);
    }
};

class PageTransitionBackward : public CCTransitionPageTurn
{
public:
    static CCTransitionScene* transitionWithDuration(ccTime t, CCScene* s)
    {
        CCDirector::sharedDirector()->setDepthTest(true);
        return CCTransitionPageTurn::transitionWithDuration(t, s, true);
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

    "CCTransitionCrossFade",
    "CCTransitionRadialCCW",
    "CCTransitionRadialCW",
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
    // fix bug #486, without setDepthTest(false), FlipX,Y will flickers
    CCDirector::sharedDirector()->setDepthTest(false);

    switch(nIndex)
    {
    case 0: return CCTransitionJumpZoom::transitionWithDuration(t, s);
    case 1: return CCTransitionFade::transitionWithDuration(t, s);
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
    case 15: return CCTransitionShrinkGrow::transitionWithDuration(t, s);
    case 16: return CCTransitionRotoZoom::transitionWithDuration(t, s);
    case 17: return CCTransitionMoveInL::transitionWithDuration(t, s);
    case 18: return CCTransitionMoveInR::transitionWithDuration(t, s);
    case 19: return CCTransitionMoveInT::transitionWithDuration(t, s);
    case 20: return CCTransitionMoveInB::transitionWithDuration(t, s);
    case 21: return CCTransitionSlideInL::transitionWithDuration(t, s);
    case 22: return CCTransitionSlideInR::transitionWithDuration(t, s);
    case 23: return CCTransitionSlideInT::transitionWithDuration(t, s);
    case 24: return CCTransitionSlideInB::transitionWithDuration(t, s);
    case 25: 
		{
			if (CCConfiguration::sharedConfiguration()->getGlesVersion() <= GLES_VER_1_0)
			{
				CCMessageBox("The Opengl ES version is lower than 1.1, and TransitionCrossFade may not run correctly, it is ignored.", "Cocos2d-x Hint");
				return NULL;
			}
			else
			{
				return CCTransitionCrossFade::transitionWithDuration(t,s);
			}
		}
		break;
    case 26: 
		{
			if (CCConfiguration::sharedConfiguration()->getGlesVersion() <= GLES_VER_1_0)
			{
				CCMessageBox("The Opengl ES version is lower than 1.1, and TransitionRadialCCW may not run correctly, it is ignored.", "Cocos2d-x Hint");
				return NULL;
			}
			else
			{
				return CCTransitionRadialCCW::transitionWithDuration(t,s);
			}
		}
		break;
    case 27: 
		{
			if (CCConfiguration::sharedConfiguration()->getGlesVersion() <= GLES_VER_1_0)
			{
				CCMessageBox("The Opengl ES version is lower than 1.1, and TransitionRadialCW may not run correctly, it is ignored.", "Cocos2d-x Hint");
				return NULL;
			}
			else
			{
				return CCTransitionRadialCW::transitionWithDuration(t,s);
			}
		}
		break;
    case 28: return PageTransitionForward::transitionWithDuration(t, s);
    case 29: return PageTransitionBackward::transitionWithDuration(t, s);
    case 30: return CCTransitionFadeTR::transitionWithDuration(t, s);
    case 31: return CCTransitionFadeBL::transitionWithDuration(t, s);
    case 32: return CCTransitionFadeUp::transitionWithDuration(t, s);
    case 33: return CCTransitionFadeDown::transitionWithDuration(t, s);
    case 34: return CCTransitionTurnOffTiles::transitionWithDuration(t, s);
    case 35: return CCTransitionSplitRows::transitionWithDuration(t, s);
    case 36: return CCTransitionSplitCols::transitionWithDuration(t, s);
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

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    x = size.width;
    y = size.height;

    CCSprite* bg1 = CCSprite::spriteWithFile(s_back1);
    bg1->setPosition( CCPointMake(size.width/2, size.height/2) );
    addChild(bg1, -1);

    CCLabelTTF* title = CCLabelTTF::labelWithString( (transitions[s_nSceneIdx]).c_str(), "Thonburi", 32 );
    addChild(title);
    title->setColor( ccc3(255,32,32) );
    title->setPosition( CCPointMake(x/2, y-100) );

    CCLabelTTF* label = CCLabelTTF::labelWithString("SCENE 1", "Marker Felt", 38);
    label->setColor( ccc3(16,16,255));
    label->setPosition( CCPointMake(x/2,y/2));	
    addChild( label);

    // menu
    CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(TestLayer1::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(TestLayer1::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(TestLayer1::nextCallback) );

    CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

    menu->setPosition( CCPointZero );
    item1->setPosition( CCPointMake( size.width/2 - 100,30) );
    item2->setPosition( CCPointMake( size.width/2, 30) );
    item3->setPosition( CCPointMake( size.width/2 + 100,30) );

    addChild(menu, 1);	

    schedule( schedule_selector(TestLayer1::step), 1.0f); 
}

TestLayer1::~TestLayer1(void)
{

}

void TestLayer1::restartCallback(CCObject* pSender)
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

void TestLayer1::nextCallback(CCObject* pSender)
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

void TestLayer1::backCallback(CCObject* pSender)
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

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    x = size.width;
    y = size.height;

    CCSprite* bg1 = CCSprite::spriteWithFile(s_back2);
    bg1->setPosition( CCPointMake(size.width/2, size.height/2) );
    addChild(bg1, -1);

    CCLabelTTF* title = CCLabelTTF::labelWithString((transitions[s_nSceneIdx]).c_str(), "Thonburi", 32 );
    addChild(title);
    title->setColor( ccc3(255,32,32) );
    title->setPosition( CCPointMake(x/2, y-100) );

    CCLabelTTF* label = CCLabelTTF::labelWithString("SCENE 2", "Marker Felt", 38);
    label->setColor( ccc3(16,16,255));
    label->setPosition( CCPointMake(x/2,y/2));	
    addChild( label);

    // menu
    CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(TestLayer2::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(TestLayer2::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(TestLayer2::nextCallback) );

    CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

    menu->setPosition( CCPointZero );
    item1->setPosition( CCPointMake( x/2 - 100,30) );
    item2->setPosition( CCPointMake( x/2, 30) );
    item3->setPosition( CCPointMake( x/2 + 100,30) );

    addChild(menu, 1);	

    schedule(schedule_selector(TestLayer2::step), 1.0f);
}

TestLayer2::~TestLayer2()
{

}

void TestLayer2::restartCallback(CCObject* pSender)
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

void TestLayer2::nextCallback(CCObject* pSender)
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

void TestLayer2::backCallback(CCObject* pSender)
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
