#include "TransitionsTest.h"
#include "../testResource.h"
#include "CCConfiguration.h"

#define TRANSITION_DURATION (1.2f)

class FadeWhiteTransition : public CCTransitionFade 
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionFade::create(t, s, ccWHITE); 
    }
};

class FlipXLeftOver : public CCTransitionFlipX 
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionFlipX::create(t, s, kCCTransitionOrientationLeftOver);
    }
};

class FlipXRightOver : public CCTransitionFlipX 
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionFlipX::create(t, s, kCCTransitionOrientationRightOver);
    }
};

class FlipYUpOver : public CCTransitionFlipY 
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionFlipY::create(t, s, kCCTransitionOrientationUpOver); 
    }
};

class FlipYDownOver : public CCTransitionFlipY 
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionFlipY::create(t, s, kCCTransitionOrientationDownOver); 
    }
};

class FlipAngularLeftOver : public CCTransitionFlipAngular 
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionFlipAngular::create(t, s, kCCTransitionOrientationLeftOver); 
    }
};

class FlipAngularRightOver : public CCTransitionFlipAngular 
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionFlipAngular::create(t, s, kCCTransitionOrientationRightOver);
    }
};

class ZoomFlipXLeftOver : public CCTransitionZoomFlipX 
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionZoomFlipX::create(t, s, kCCTransitionOrientationLeftOver); 
    }
};

class ZoomFlipXRightOver : public CCTransitionZoomFlipX 
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionZoomFlipX::create(t, s, kCCTransitionOrientationRightOver);
    }
};

class ZoomFlipYUpOver : public CCTransitionZoomFlipY 
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionZoomFlipY::create(t, s, kCCTransitionOrientationUpOver); 

    }
};

class ZoomFlipYDownOver : public CCTransitionZoomFlipY 
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionZoomFlipY::create(t, s, kCCTransitionOrientationDownOver); 
    }
};

class ZoomFlipAngularLeftOver : public CCTransitionZoomFlipAngular 
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionZoomFlipAngular::create(t, s, kCCTransitionOrientationLeftOver); 
    }
};

class ZoomFlipAngularRightOver : public CCTransitionZoomFlipAngular 
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionZoomFlipAngular::create(t, s, kCCTransitionOrientationRightOver);
    }
};

class PageTransitionForward : public CCTransitionPageTurn
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        CCDirector::sharedDirector()->setDepthTest(true);
        return CCTransitionPageTurn::create(t, s, false);
    }
};

class PageTransitionBackward : public CCTransitionPageTurn
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        CCDirector::sharedDirector()->setDepthTest(true);
        return CCTransitionPageTurn::create(t, s, true);
    }
};

#define MAX_LAYER    41

static std::string transitions[MAX_LAYER] = {
    "CCTransitionJumpZoom",

    "CCTransitionProgressRadialCCW",
    "CCTransitionProgressRadialCW",
    "CCTransitionProgressHorizontal",
    "CCTransitionProgressVertical",
    "CCTransitionProgressInOut",
    "CCTransitionProgressOutIn",

    "CCTransitionCrossFade",
    "TransitionPageForward",
    "TransitionPageBackward",
    "CCTransitionFadeTR",
    "CCTransitionFadeBL",
    "CCTransitionFadeUp",
    "CCTransitionFadeDown",
    "CCTransitionTurnOffTiles",
    "CCTransitionSplitRows",
    "CCTransitionSplitCols",

    "CCTransitionFade",
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

    "CCTransitionShrinkGrow",
    "CCTransitionRotoZoom",

    "CCTransitionMoveInL",
    "CCTransitionMoveInR",
    "CCTransitionMoveInT",
    "CCTransitionMoveInB",
    "CCTransitionSlideInL",
    "CCTransitionSlideInR",
    "CCTransitionSlideInT",
    "CCTransitionSlideInB",


};
static int s_nSceneIdx = 0;

CCTransitionScene* createTransition(int nIndex, float t, CCScene* s)
{
    // fix bug #486, without setDepthTest(false), FlipX,Y will flickers
    CCDirector::sharedDirector()->setDepthTest(false);

    switch(nIndex)
    {
    case 0: return CCTransitionJumpZoom::create(t, s);

    case 1: return CCTransitionProgressRadialCCW::create(t, s);
    case 2: return CCTransitionProgressRadialCW::create(t, s);
    case 3: return CCTransitionProgressHorizontal::create(t, s);
    case 4: return CCTransitionProgressVertical::create(t, s);
    case 5: return CCTransitionProgressInOut::create(t, s);
    case 6: return CCTransitionProgressOutIn::create(t, s);

    case 7: return CCTransitionCrossFade::create(t,s);

    case 8: return PageTransitionForward::create(t, s);
    case 9: return PageTransitionBackward::create(t, s);
    case 10: return CCTransitionFadeTR::create(t, s);
    case 11: return CCTransitionFadeBL::create(t, s);
    case 12: return CCTransitionFadeUp::create(t, s);
    case 13: return CCTransitionFadeDown::create(t, s);

    case 14: return CCTransitionTurnOffTiles::create(t, s);

    case 15: return CCTransitionSplitRows::create(t, s);
    case 16: return CCTransitionSplitCols::create(t, s);

    case 17: return CCTransitionFade::create(t, s);
    case 18: return FadeWhiteTransition::create(t, s);

    case 19: return FlipXLeftOver::create(t, s);
    case 20: return FlipXRightOver::create(t, s);
    case 21: return FlipYUpOver::create(t, s);
    case 22: return FlipYDownOver::create(t, s);
    case 23: return FlipAngularLeftOver::create(t, s);
    case 24: return FlipAngularRightOver::create(t, s);

    case 25: return ZoomFlipXLeftOver::create(t, s);
    case 26: return ZoomFlipXRightOver::create(t, s);
    case 27: return ZoomFlipYUpOver::create(t, s);
    case 28: return ZoomFlipYDownOver::create(t, s);
    case 29: return ZoomFlipAngularLeftOver::create(t, s);
    case 30: return ZoomFlipAngularRightOver::create(t, s);

    case 31: return CCTransitionShrinkGrow::create(t, s);
    case 32: return CCTransitionRotoZoom::create(t, s);

    case 33: return CCTransitionMoveInL::create(t, s);
    case 34: return CCTransitionMoveInR::create(t, s);
    case 35: return CCTransitionMoveInT::create(t, s);
    case 36: return CCTransitionMoveInB::create(t, s);

    case 37: return CCTransitionSlideInL::create(t, s);
    case 38: return CCTransitionSlideInR::create(t, s);
    case 39: return CCTransitionSlideInT::create(t, s);
    case 40: return CCTransitionSlideInB::create(t, s);

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

    CCSprite* bg1 = CCSprite::create(s_back1);
    bg1->setPosition( ccp(size.width/2, size.height/2) );
    addChild(bg1, -1);

    CCLabelTTF* title = CCLabelTTF::create( (transitions[s_nSceneIdx]).c_str(), "Thonburi", 32 );
    addChild(title);
    title->setColor( ccc3(255,32,32) );
    title->setPosition( ccp(x/2, y-100) );

    CCLabelTTF* label = CCLabelTTF::create("SCENE 1", "Marker Felt", 38);
    label->setColor( ccc3(16,16,255));
    label->setPosition( ccp(x/2,y/2));    
    addChild( label);

    // menu
    CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(TestLayer1::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(TestLayer1::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(TestLayer1::nextCallback) );

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

    menu->setPosition( CCPointZero );
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

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

void TestLayer1::step(float dt)
{

}

void TestLayer1::onEnter()
{
    CCLayer::onEnter();
    CCLog("Scene 1 onEnter");
}

void TestLayer1::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    CCLog("Scene 1: onEnterTransitionDidFinish");
}

void TestLayer1::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
    CCLog("Scene 1: onExitTransitionDidStart");
}

void TestLayer1::onExit()
{
    CCLayer::onExit();
    CCLog("Scene 1 onExit");
}

TestLayer2::TestLayer2()
{
    float x,y;

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    x = size.width;
    y = size.height;

    CCSprite* bg1 = CCSprite::create(s_back2);
    bg1->setPosition( ccp(size.width/2, size.height/2) );
    addChild(bg1, -1);

    CCLabelTTF* title = CCLabelTTF::create((transitions[s_nSceneIdx]).c_str(), "Thonburi", 32 );
    addChild(title);
    title->setColor( ccc3(255,32,32) );
    title->setPosition( ccp(x/2, y-100) );

    CCLabelTTF* label = CCLabelTTF::create("SCENE 2", "Marker Felt", 38);
    label->setColor( ccc3(16,16,255));
    label->setPosition( ccp(x/2,y/2));    
    addChild( label);

    // menu
    CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(TestLayer2::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(TestLayer2::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(TestLayer2::nextCallback) );

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

    menu->setPosition( CCPointZero );
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

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

void TestLayer2::step(float dt)
{

}

void TestLayer2::onEnter()
{
    CCLayer::onEnter();
    CCLog("Scene 2 onEnter");
}

void TestLayer2::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    CCLog("Scene 2: onEnterTransitionDidFinish");
}

void TestLayer2::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
    CCLog("Scene 2: onExitTransitionDidStart");
}

void TestLayer2::onExit()
{
    CCLayer::onExit();
    CCLog("Scene 2 onExit");
}
