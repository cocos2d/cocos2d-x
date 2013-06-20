#include "TransitionsTest.h"
#include "../testResource.h"
#include "CCConfiguration.h"

#define TRANSITION_DURATION (1.2f)

class FadeWhiteTransition : public TransitionFade 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFade::create(t, s, ccWHITE); 
    }
};

class FlipXLeftOver : public TransitionFlipX 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFlipX::create(t, s, kTransitionOrientationLeftOver);
    }
};

class FlipXRightOver : public TransitionFlipX 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFlipX::create(t, s, kTransitionOrientationRightOver);
    }
};

class FlipYUpOver : public TransitionFlipY 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFlipY::create(t, s, kTransitionOrientationUpOver); 
    }
};

class FlipYDownOver : public TransitionFlipY 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFlipY::create(t, s, kTransitionOrientationDownOver); 
    }
};

class FlipAngularLeftOver : public TransitionFlipAngular 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFlipAngular::create(t, s, kTransitionOrientationLeftOver); 
    }
};

class FlipAngularRightOver : public TransitionFlipAngular 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFlipAngular::create(t, s, kTransitionOrientationRightOver);
    }
};

class ZoomFlipXLeftOver : public TransitionZoomFlipX 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionZoomFlipX::create(t, s, kTransitionOrientationLeftOver); 
    }
};

class ZoomFlipXRightOver : public TransitionZoomFlipX 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionZoomFlipX::create(t, s, kTransitionOrientationRightOver);
    }
};

class ZoomFlipYUpOver : public TransitionZoomFlipY 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionZoomFlipY::create(t, s, kTransitionOrientationUpOver); 

    }
};

class ZoomFlipYDownOver : public TransitionZoomFlipY 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionZoomFlipY::create(t, s, kTransitionOrientationDownOver); 
    }
};

class ZoomFlipAngularLeftOver : public TransitionZoomFlipAngular 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionZoomFlipAngular::create(t, s, kTransitionOrientationLeftOver); 
    }
};

class ZoomFlipAngularRightOver : public TransitionZoomFlipAngular 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionZoomFlipAngular::create(t, s, kTransitionOrientationRightOver);
    }
};

class PageTransitionForward : public TransitionPageTurn
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        Director::sharedDirector()->setDepthTest(true);
        return TransitionPageTurn::create(t, s, false);
    }
};

class PageTransitionBackward : public TransitionPageTurn
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        Director::sharedDirector()->setDepthTest(true);
        return TransitionPageTurn::create(t, s, true);
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

TransitionScene* createTransition(int nIndex, float t, Scene* s)
{
    // fix bug #486, without setDepthTest(false), FlipX,Y will flickers
    Director::sharedDirector()->setDepthTest(false);

    switch(nIndex)
    {
    case 0: return TransitionJumpZoom::create(t, s);

    case 1: return TransitionProgressRadialCCW::create(t, s);
    case 2: return TransitionProgressRadialCW::create(t, s);
    case 3: return TransitionProgressHorizontal::create(t, s);
    case 4: return TransitionProgressVertical::create(t, s);
    case 5: return TransitionProgressInOut::create(t, s);
    case 6: return TransitionProgressOutIn::create(t, s);

    case 7: return TransitionCrossFade::create(t,s);

    case 8: return PageTransitionForward::create(t, s);
    case 9: return PageTransitionBackward::create(t, s);
    case 10: return TransitionFadeTR::create(t, s);
    case 11: return TransitionFadeBL::create(t, s);
    case 12: return TransitionFadeUp::create(t, s);
    case 13: return TransitionFadeDown::create(t, s);

    case 14: return TransitionTurnOffTiles::create(t, s);

    case 15: return TransitionSplitRows::create(t, s);
    case 16: return TransitionSplitCols::create(t, s);

    case 17: return TransitionFade::create(t, s);
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

    case 31: return TransitionShrinkGrow::create(t, s);
    case 32: return TransitionRotoZoom::create(t, s);

    case 33: return TransitionMoveInL::create(t, s);
    case 34: return TransitionMoveInR::create(t, s);
    case 35: return TransitionMoveInT::create(t, s);
    case 36: return TransitionMoveInB::create(t, s);

    case 37: return TransitionSlideInL::create(t, s);
    case 38: return TransitionSlideInR::create(t, s);
    case 39: return TransitionSlideInT::create(t, s);
    case 40: return TransitionSlideInB::create(t, s);

    default: break;
    }

    return NULL;
}                            


void TransitionsTestScene::runThisTest()
{
    Layer * pLayer = new TestLayer1();
    addChild(pLayer);
    pLayer->release();

    Director::sharedDirector()->replaceScene(this);
}

TestLayer1::TestLayer1(void)
{
    float x,y;

    Size size = Director::sharedDirector()->getWinSize();
    x = size.width;
    y = size.height;

    Sprite* bg1 = Sprite::create(s_back1);
    bg1->setPosition( ccp(size.width/2, size.height/2) );
    addChild(bg1, -1);

    LabelTTF* title = LabelTTF::create( (transitions[s_nSceneIdx]).c_str(), "Thonburi", 32 );
    addChild(title);
    title->setColor( ccc3(255,32,32) );
    title->setPosition( ccp(x/2, y-100) );

    LabelTTF* label = LabelTTF::create("SCENE 1", "Marker Felt", 38);
    label->setColor( ccc3(16,16,255));
    label->setPosition( ccp(x/2,y/2));    
    addChild( label);

    // menu
    MenuItemImage *item1 = MenuItemImage::create(s_pPathB1, s_pPathB2, CC_CALLBACK_1(TestLayer1::backCallback, this) );
    MenuItemImage *item2 = MenuItemImage::create(s_pPathR1, s_pPathR2, CC_CALLBACK_1(TestLayer1::restartCallback, this) );
    MenuItemImage *item3 = MenuItemImage::create(s_pPathF1, s_pPathF2, CC_CALLBACK_1(TestLayer1::nextCallback, this) );

    Menu *menu = Menu::create(item1, item2, item3, NULL);

    menu->setPosition( PointZero );
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

    addChild(menu, 1);    

    schedule( schedule_selector(TestLayer1::step), 1.0f); 
}

TestLayer1::~TestLayer1(void)
{

}

void TestLayer1::restartCallback(Object* pSender)
{
    Scene* s = new TransitionsTestScene();

    Layer* pLayer = new TestLayer2();
    s->addChild(pLayer);

    Scene* pScene = createTransition(s_nSceneIdx, TRANSITION_DURATION, s);
    s->release();
    pLayer->release();
    if (pScene)
    {
        Director::sharedDirector()->replaceScene(pScene);
    }    
}

void TestLayer1::nextCallback(Object* pSender)
{
    s_nSceneIdx++;
    s_nSceneIdx = s_nSceneIdx % MAX_LAYER;

    Scene* s = new TransitionsTestScene();

    Layer* pLayer = new TestLayer2();
    s->addChild(pLayer);

    Scene* pScene = createTransition(s_nSceneIdx, TRANSITION_DURATION, s);
    s->release();
    pLayer->release();
    if (pScene)
    {
        Director::sharedDirector()->replaceScene(pScene);
    }
}

void TestLayer1::backCallback(Object* pSender)
{
    s_nSceneIdx--;
    int total = MAX_LAYER;
    if( s_nSceneIdx < 0 )
        s_nSceneIdx += total;    

    Scene* s = new TransitionsTestScene();

    Layer* pLayer = new TestLayer2();
    s->addChild(pLayer);

    Scene* pScene = createTransition(s_nSceneIdx, TRANSITION_DURATION, s);
    s->release();
    pLayer->release();
    if (pScene)
    {
        Director::sharedDirector()->replaceScene(pScene);
    }
}

void TestLayer1::step(float dt)
{

}

void TestLayer1::onEnter()
{
    Layer::onEnter();
    CCLog("Scene 1 onEnter");
}

void TestLayer1::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    CCLog("Scene 1: onEnterTransitionDidFinish");
}

void TestLayer1::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
    CCLog("Scene 1: onExitTransitionDidStart");
}

void TestLayer1::onExit()
{
    Layer::onExit();
    CCLog("Scene 1 onExit");
}

TestLayer2::TestLayer2()
{
    float x,y;

    Size size = Director::sharedDirector()->getWinSize();
    x = size.width;
    y = size.height;

    Sprite* bg1 = Sprite::create(s_back2);
    bg1->setPosition( ccp(size.width/2, size.height/2) );
    addChild(bg1, -1);

    LabelTTF* title = LabelTTF::create((transitions[s_nSceneIdx]).c_str(), "Thonburi", 32 );
    addChild(title);
    title->setColor( ccc3(255,32,32) );
    title->setPosition( ccp(x/2, y-100) );

    LabelTTF* label = LabelTTF::create("SCENE 2", "Marker Felt", 38);
    label->setColor( ccc3(16,16,255));
    label->setPosition( ccp(x/2,y/2));    
    addChild( label);

    // menu
    MenuItemImage *item1 = MenuItemImage::create(s_pPathB1, s_pPathB2, CC_CALLBACK_1(TestLayer2::backCallback, this) );
    MenuItemImage *item2 = MenuItemImage::create(s_pPathR1, s_pPathR2, CC_CALLBACK_1(TestLayer2::restartCallback, this) );
    MenuItemImage *item3 = MenuItemImage::create(s_pPathF1, s_pPathF2, CC_CALLBACK_1(TestLayer2::nextCallback, this) );

    Menu *menu = Menu::create(item1, item2, item3, NULL);

    menu->setPosition( PointZero );
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

    addChild(menu, 1);    

    schedule(schedule_selector(TestLayer2::step), 1.0f);
}

TestLayer2::~TestLayer2()
{

}

void TestLayer2::restartCallback(Object* pSender)
{
    Scene* s = new TransitionsTestScene();

    Layer* pLayer = new TestLayer1();
    s->addChild(pLayer);

    Scene* pScene = createTransition(s_nSceneIdx, TRANSITION_DURATION, s);
    s->release();
    pLayer->release();
    if (pScene)
    {
        Director::sharedDirector()->replaceScene(pScene);
    }
}

void TestLayer2::nextCallback(Object* pSender)
{
    s_nSceneIdx++;
    s_nSceneIdx = s_nSceneIdx % MAX_LAYER;

    Scene* s = new TransitionsTestScene();

    Layer* pLayer = new TestLayer1();
    s->addChild(pLayer);

    Scene* pScene = createTransition(s_nSceneIdx, TRANSITION_DURATION, s);
    s->release();
    pLayer->release();
    if (pScene)
    {
        Director::sharedDirector()->replaceScene(pScene);
    }
}

void TestLayer2::backCallback(Object* pSender)
{
    s_nSceneIdx--;
    int total = MAX_LAYER;
    if( s_nSceneIdx < 0 )
        s_nSceneIdx += total;    

    Scene* s = new TransitionsTestScene();

    Layer* pLayer = new TestLayer1();
    s->addChild(pLayer);

    Scene* pScene = createTransition(s_nSceneIdx, TRANSITION_DURATION, s);
    s->release();
    pLayer->release();
    if (pScene)
    {
        Director::sharedDirector()->replaceScene(pScene);
    }
}

void TestLayer2::step(float dt)
{

}

void TestLayer2::onEnter()
{
    Layer::onEnter();
    CCLog("Scene 2 onEnter");
}

void TestLayer2::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    CCLog("Scene 2: onEnterTransitionDidFinish");
}

void TestLayer2::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
    CCLog("Scene 2: onExitTransitionDidStart");
}

void TestLayer2::onExit()
{
    Layer::onExit();
    CCLog("Scene 2 onExit");
}
