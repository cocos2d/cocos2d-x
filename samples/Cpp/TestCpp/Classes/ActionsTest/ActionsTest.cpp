#include "ActionsTest.h"
#include "../testResource.h"
#include "cocos2d.h"

static std::function<CCLayer*()> createFunctions[] = {
    CL(ActionManual),
    CL(ActionMove),
    CL(ActionRotate),
    CL(ActionScale),
    CL(ActionSkew),
    CL(ActionRotationalSkew),
    CL(ActionRotationalSkewVSStandardSkew),
    CL(ActionSkewRotateScale),
    CL(ActionJump),
    CL(ActionCardinalSpline),
    CL(ActionCatmullRom),
    CL(ActionBezier),
    CL(ActionBlink),
    CL(ActionFade),
    CL(ActionTint),
    CL(ActionAnimate),
    CL(ActionSequence),
    CL(ActionSequence2),
	CL(ActionRemoveSelf),
    CL(ActionSpawn),
    CL(ActionReverse),
    CL(ActionDelayTime),
    CL(ActionRepeat),
    CL(ActionRepeatForever),
    CL(ActionRotateToRepeat),
    CL(ActionRotateJerk),
    CL(ActionCallFunction),
    CL(ActionCallFunc),
    CL(ActionCallFuncND),
    CL(ActionReverseSequence),
    CL(ActionReverseSequence2),
    CL(ActionOrbit),
    CL(ActionFollow),
    CL(ActionTargeted),
    CL(ActionMoveStacked),
    CL(ActionMoveJumpStacked),
    CL(ActionMoveBezierStacked),
    CL(ActionCardinalSplineStacked),
    CL(ActionCatmullRomStacked),
    CL(PauseResumeActions),
    CL(Issue1305),
    CL(Issue1305_2),
    CL(Issue1288),
    CL(Issue1288_2),
    CL(Issue1327),
    CL(Issue1398)
};

static int sceneIdx=-1;
#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))

static CCLayer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

static CCLayer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

static CCLayer* restartAction()
{
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

void ActionsTestScene::runThisTest()
{
    sceneIdx = -1;
    addChild(nextAction());

    CCDirector::sharedDirector()->replaceScene(this);
}


std::string ActionsDemo::title()
{
    return "ActionsTest";
}

std::string ActionsDemo::subtitle()
{
    return "";
}

void ActionsDemo::onEnter()
{
    BaseTest::onEnter();

    // Or you can create an sprite using a filename. only PNG is supported now. Probably TIFF too
    _grossini = CCSprite::create(s_pPathGrossini);
    _grossini->retain();

    _tamara = CCSprite::create(s_pPathSister1); 
    _tamara->retain();

    _kathia = CCSprite::create(s_pPathSister2);
    _kathia->retain();

    addChild(_grossini, 1);
    addChild(_tamara, 2);
    addChild(_kathia, 3);

    _grossini->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height/3));
    _tamara->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*2/3));
    _kathia->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height/2)); 
}

void ActionsDemo::onExit()
{
    _grossini->release();
    _tamara->release();
    _kathia->release();

    BaseTest::onExit();
}

void ActionsDemo::restartCallback(CCObject* pSender)
{
    CCScene* s = new ActionsTestScene();
    s->addChild( restartAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void ActionsDemo::nextCallback(CCObject* pSender)
{
    CCScene* s = new ActionsTestScene();
    s->addChild( nextAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void ActionsDemo::backCallback(CCObject* pSender)
{
    CCScene* s = new ActionsTestScene();
    s->addChild( backAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void ActionsDemo::centerSprites(unsigned int numberOfSprites)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    if( numberOfSprites == 0 )
    {
        _tamara->setVisible(false);
        _kathia->setVisible(false);
        _grossini->setVisible(false);
    } 
    else if ( numberOfSprites == 1 ) 
    {
        _tamara->setVisible(false);
        _kathia->setVisible(false);
        _grossini->setPosition(ccp(s.width/2, s.height/2));
    }
    else if( numberOfSprites == 2 ) 
    {        
        _kathia->setPosition( ccp(s.width/3, s.height/2));
        _tamara->setPosition( ccp(2*s.width/3, s.height/2));
        _grossini->setVisible(false);
    } 
    else if( numberOfSprites == 3 ) 
    {
        _grossini->setPosition( ccp(s.width/2, s.height/2));
        _tamara->setPosition( ccp(s.width/4, s.height/2));
        _kathia->setPosition( ccp(3 * s.width/4, s.height/2));
    }
}

void ActionsDemo::alignSpritesLeft(unsigned int numberOfSprites)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    if( numberOfSprites == 1 ) 
    {
        _tamara->setVisible(false);
        _kathia->setVisible(false);
        _grossini->setPosition(ccp(60, s.height/2));
    } 
    else if( numberOfSprites == 2 ) 
    {        
        _kathia->setPosition( ccp(60, s.height/3));
        _tamara->setPosition( ccp(60, 2*s.height/3));
        _grossini->setVisible( false );
    } 
    else if( numberOfSprites == 3 ) 
    {
        _grossini->setPosition( ccp(60, s.height/2));
        _tamara->setPosition( ccp(60, 2*s.height/3));
        _kathia->setPosition( ccp(60, s.height/3));
    }
}

//------------------------------------------------------------------
//
// ActionManual
//
//------------------------------------------------------------------
void ActionManual::onEnter()
{
    ActionsDemo::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    _tamara->setScaleX( 2.5f);
    _tamara->setScaleY( -1.0f);
    _tamara->setPosition( ccp(100,70) );
    _tamara->setOpacity( 128);

    _grossini->setRotation( 120);
    _grossini->setPosition( ccp(s.width/2, s.height/2));
    _grossini->setColor( ccc3( 255,0,0));

    _kathia->setPosition( ccp(s.width-100, s.height/2));
    _kathia->setColor( ccBLUE);
}

std::string ActionManual::subtitle()
{
    return "Manual Transformation";
}

//------------------------------------------------------------------
//
//    ActionMove
//
//------------------------------------------------------------------
void ActionMove::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCActionInterval*  actionTo = CCMoveTo::create(2, ccp(s.width-40, s.height-40));
    CCActionInterval*  actionBy = CCMoveBy::create(2, ccp(80,80));
    CCActionInterval*  actionByBack = actionBy->reverse();

    _tamara->runAction( actionTo);
    _grossini->runAction( CCSequence::create(actionBy, actionByBack, NULL));
    _kathia->runAction(CCMoveTo::create(1, ccp(40,40)));
}

std::string ActionMove::subtitle()
{
    return "MoveTo / MoveBy";
}

//------------------------------------------------------------------
//
// ActionScale
//
//------------------------------------------------------------------
void ActionScale::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    CCActionInterval*  actionTo = CCScaleTo::create(2.0f, 0.5f);
    CCActionInterval*  actionBy = CCScaleBy::create(2.0f, 1.0f, 10.0f);
    CCActionInterval*  actionBy2 = CCScaleBy::create(2.0f, 5.0f, 1.0f);

    _grossini->runAction( actionTo);
    _tamara->runAction( CCSequence::create(actionBy, actionBy->reverse(), NULL));
    _kathia->runAction( CCSequence::create(actionBy2, actionBy2->reverse(), NULL));
}

std::string ActionScale::subtitle()
{
    return "ScaleTo / ScaleBy";
}

//------------------------------------------------------------------
//
//    ActionSkew
//
//------------------------------------------------------------------
void ActionSkew::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    CCActionInterval *actionTo = CCSkewTo::create(2, 37.2f, -37.2f);
    CCActionInterval *actionToBack = CCSkewTo::create(2, 0, 0);
    CCActionInterval *actionBy = CCSkewBy::create(2, 0.0f, -90.0f);
    CCActionInterval *actionBy2 = CCSkewBy::create(2, 45.0f, 45.0f);
    CCActionInterval *actionByBack = actionBy->reverse();

    _tamara->runAction(CCSequence::create(actionTo, actionToBack, NULL));
    _grossini->runAction(CCSequence::create(actionBy, actionByBack, NULL));

    _kathia->runAction(CCSequence::create(actionBy2, actionBy2->reverse(), NULL));
}

string ActionSkew::subtitle()
{
    return "SkewTo / SkewBy";
}

// ActionRotationalSkew
void ActionRotationalSkew::onEnter()
{
    ActionsDemo::onEnter();

    this->centerSprites(3);

    CCRotateTo* actionTo = CCRotateTo::create(2, 37.2f, -37.2f);
    CCRotateTo* actionToBack = CCRotateTo::create(2, 0, 0);
    CCRotateBy* actionBy = CCRotateBy::create(2, 0.0f, -90.0f);
    CCRotateBy* actionBy2 = CCRotateBy::create(2, 45.0f, 45.0f);
    CCRotateBy* actionByBack = (CCRotateBy*)actionBy->reverse();

    _tamara->runAction(CCSequence::create(actionTo, actionToBack, NULL));
    _grossini->runAction(CCSequence::create(actionBy, actionByBack, NULL));

    _kathia->runAction(CCSequence::create(actionBy2, actionBy2->reverse(), NULL));
}

std::string ActionRotationalSkew::subtitle()
{
    return "RotationalSkewTo / RotationalSkewBy";
}



//ActionRotationalSkewVSStandardSkew
void ActionRotationalSkewVSStandardSkew::onEnter()
{
    ActionsDemo::onEnter();

    _tamara->removeFromParentAndCleanup(true);
    _grossini->removeFromParentAndCleanup(true);
    _kathia->removeFromParentAndCleanup(true);

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSize boxSize = CCSizeMake(100.0f, 100.0f);

    CCLayerColor *box = CCLayerColor::create(ccc4(255,255,0,255));
    box->setAnchorPoint(ccp(0.5,0.5));
    box->setContentSize( boxSize );
    box->ignoreAnchorPointForPosition(false);
    box->setPosition(ccp(s.width/2, s.height - 100 - box->getContentSize().height/2));
    this->addChild(box);
    CCLabelTTF *label = CCLabelTTF::create("Standard cocos2d Skew", "Marker Felt", 16);
    label->setPosition(ccp(s.width/2, s.height - 100 + label->getContentSize().height));
    this->addChild(label);
    CCSkewBy* actionTo = CCSkewBy::create(2, 360, 0);
    CCSkewBy* actionToBack = CCSkewBy::create(2, -360, 0);

    box->runAction(CCSequence::create(actionTo, actionToBack, NULL));

    box = CCLayerColor::create(ccc4(255,255,0,255));
    box->setAnchorPoint(ccp(0.5,0.5));
    box->setContentSize(boxSize);
    box->ignoreAnchorPointForPosition(false);
    box->setPosition(ccp(s.width/2, s.height - 250 - box->getContentSize().height/2));
    this->addChild(box);
    label = CCLabelTTF::create("Rotational Skew", "Marker Felt", 16);
    label->setPosition(ccp(s.width/2, s.height - 250 + label->getContentSize().height/2));
    this->addChild(label);
    CCRotateBy* actionTo2 = CCRotateBy::create(2, 360, 0);
    CCRotateBy* actionToBack2 = CCRotateBy::create(2, -360, 0);
    box->runAction(CCSequence::create(actionTo2, actionToBack2, NULL));
}
std::string ActionRotationalSkewVSStandardSkew::subtitle()
{
    return "Skew Comparison";
}

// ActionSkewRotateScale
void ActionSkewRotateScale::onEnter()
{
    ActionsDemo::onEnter();

    _tamara->removeFromParentAndCleanup(true);
    _grossini->removeFromParentAndCleanup(true);
    _kathia->removeFromParentAndCleanup(true);

    CCSize boxSize = CCSizeMake(100.0f, 100.0f);

    CCLayerColor *box = CCLayerColor::create(ccc4(255, 255, 0, 255));
    box->setAnchorPoint(ccp(0, 0));
    box->setPosition(ccp(190, 110));
    box->setContentSize(boxSize);

    static float markrside = 10.0f;
    CCLayerColor *uL = CCLayerColor::create(ccc4(255, 0, 0, 255));
    box->addChild(uL);
    uL->setContentSize(CCSizeMake(markrside, markrside));
    uL->setPosition(ccp(0.f, boxSize.height - markrside));
    uL->setAnchorPoint(ccp(0, 0));

    CCLayerColor *uR = CCLayerColor::create(ccc4(0, 0, 255, 255));
    box->addChild(uR);
    uR->setContentSize(CCSizeMake(markrside, markrside));
    uR->setPosition(ccp(boxSize.width - markrside, boxSize.height - markrside));
    uR->setAnchorPoint(ccp(0, 0));
    addChild(box);

    CCActionInterval *actionTo = CCSkewTo::create(2, 0.f, 2.f);
    CCActionInterval *rotateTo = CCRotateTo::create(2, 61.0f);
    CCActionInterval *actionScaleTo = CCScaleTo::create(2, -0.44f, 0.47f);

    CCActionInterval *actionScaleToBack = CCScaleTo::create(2, 1.0f, 1.0f);
    CCActionInterval *rotateToBack = CCRotateTo::create(2, 0);
    CCActionInterval *actionToBack = CCSkewTo::create(2, 0, 0);

    box->runAction(CCSequence::create(actionTo, actionToBack, NULL));
    box->runAction(CCSequence::create(rotateTo, rotateToBack, NULL));
    box->runAction(CCSequence::create(actionScaleTo, actionScaleToBack, NULL));
}

string ActionSkewRotateScale::subtitle()
{
    return "Skew + Rotate + Scale";
}

//------------------------------------------------------------------
//
//    ActionRotate
//
//------------------------------------------------------------------
void ActionRotate::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    CCActionInterval*  actionTo = CCRotateTo::create( 2, 45);
    CCActionInterval*  actionTo2 = CCRotateTo::create( 2, -45);
    CCActionInterval*  actionTo0 = CCRotateTo::create(2 , 0);
    _tamara->runAction( CCSequence::create(actionTo, actionTo0, NULL));

    CCActionInterval*  actionBy = CCRotateBy::create(2 ,  360);
    CCActionInterval*  actionByBack = actionBy->reverse();
    _grossini->runAction( CCSequence::create(actionBy, actionByBack, NULL));

    _kathia->runAction( CCSequence::create(actionTo2, actionTo0->copy()->autorelease(), NULL));
}

std::string ActionRotate::subtitle()
{
    return "RotateTo / RotateBy";
}

//------------------------------------------------------------------
//
// ActionJump
//
//------------------------------------------------------------------
void ActionJump::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    CCActionInterval*  actionTo = CCJumpTo::create(2, ccp(300,300), 50, 4);
    CCActionInterval*  actionBy = CCJumpBy::create(2, ccp(300,0), 50, 4);
    CCActionInterval*  actionUp = CCJumpBy::create(2, ccp(0,0), 80, 4);
    CCActionInterval*  actionByBack = actionBy->reverse();

    _tamara->runAction( actionTo);
    _grossini->runAction( CCSequence::create(actionBy, actionByBack, NULL));
    _kathia->runAction( CCRepeatForever::create(actionUp));
}
std::string ActionJump::subtitle()
{
    return "JumpTo / JumpBy";
}

//------------------------------------------------------------------
//
// ActionBezier
//
//------------------------------------------------------------------
void ActionBezier::onEnter()
{
    ActionsDemo::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    //
    // startPosition can be any coordinate, but since the movement
    // is relative to the Bezier curve, make it (0,0)
    //

    centerSprites(3);

    // sprite 1
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp(0, s.height/2);
    bezier.controlPoint_2 = ccp(300, -s.height/2);
    bezier.endPosition = ccp(300,100);

    CCActionInterval*  bezierForward = CCBezierBy::create(3, bezier);
    CCActionInterval*  bezierBack = bezierForward->reverse();    
    CCAction*  rep = CCRepeatForever::create(CCSequence::create( bezierForward, bezierBack, NULL));


    // sprite 2
    _tamara->setPosition(ccp(80,160));
    ccBezierConfig bezier2;
    bezier2.controlPoint_1 = ccp(100, s.height/2);
    bezier2.controlPoint_2 = ccp(200, -s.height/2);
    bezier2.endPosition = ccp(240,160);

    CCActionInterval*  bezierTo1 = CCBezierTo::create(2, bezier2);    

    // sprite 3
    _kathia->setPosition(ccp(400,160));
    CCActionInterval*  bezierTo2 = CCBezierTo::create(2, bezier2);

    _grossini->runAction( rep);
    _tamara->runAction(bezierTo1);
    _kathia->runAction(bezierTo2);

}

std::string ActionBezier::subtitle()
{
    return "BezierBy / BezierTo";
}

//------------------------------------------------------------------
//
// ActionBlink
//
//------------------------------------------------------------------
void ActionBlink::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(2);

    CCActionInterval*  action1 = CCBlink::create(2, 10);
    CCActionInterval*  action2 = CCBlink::create(2, 5);

    _tamara->runAction( action1);
    _kathia->runAction(action2);
}

std::string  ActionBlink::subtitle()
{
    return "Blink";
}

//------------------------------------------------------------------
//
// ActionFade
//
//------------------------------------------------------------------
void ActionFade::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(2);

    _tamara->setOpacity( 0 );
    CCActionInterval*  action1 = CCFadeIn::create(1.0f);
    CCActionInterval*  action1Back = action1->reverse();

    CCActionInterval*  action2 = CCFadeOut::create(1.0f);
    CCActionInterval*  action2Back = action2->reverse();

    _tamara->runAction( CCSequence::create( action1, action1Back, NULL));
    _kathia->runAction( CCSequence::create( action2, action2Back, NULL));
}

std::string  ActionFade::subtitle()
{
    return "FadeIn / FadeOut";
}

//------------------------------------------------------------------
//
// ActionTint
//
//------------------------------------------------------------------

void ActionTint::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(2);

    CCActionInterval*  action1 = CCTintTo::create(2, 255, 0, 255);
    CCActionInterval*  action2 = CCTintBy::create(2, -127, -255, -127);
    CCActionInterval*  action2Back = action2->reverse();

    _tamara->runAction( action1);
    _kathia->runAction( CCSequence::create( action2, action2Back, NULL));
}

std::string  ActionTint::subtitle()
{
    return "TintTo / TintBy";
}

//------------------------------------------------------------------
//
// ActionAnimate
//
//------------------------------------------------------------------
void ActionAnimate::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);


    //
    // Manual animation
    //
    CCAnimation* animation = CCAnimation::create();
    for( int i=1;i<15;i++)
    {
        char szName[100] = {0};
        sprintf(szName, "Images/grossini_dance_%02d.png", i);
        animation->addSpriteFrameWithFileName(szName);
    }
    // should last 2.8 seconds. And there are 14 frames.
    animation->setDelayPerUnit(2.8f / 14.0f);
    animation->setRestoreOriginalFrame(true);

    CCAnimate* action = CCAnimate::create(animation);
    _grossini->runAction(CCSequence::create(action, action->reverse(), NULL));
    
    //
    // File animation
    //
    // With 2 loops and reverse
    CCAnimationCache *cache = CCAnimationCache::sharedAnimationCache();
    cache->addAnimationsWithFile("animations/animations-2.plist");
    CCAnimation *animation2 = cache->animationByName("dance_1");

    CCAnimate* action2 = CCAnimate::create(animation2);
    _tamara->runAction(CCSequence::create(action2, action2->reverse(), NULL));

// TODO:
//     observer_ = [[NSNotificationCenter defaultCenter] addObserverForName:CCAnimationFrameDisplayedNotification object:nil queue:nil usingBlock:^(NSNotification* notification) {
// 
//         NSDictionary *userInfo = [notification userInfo);
//         NSLog(@"object %@ with data %@", [notification object), userInfo );
//     });


    //
    // File animation
    //
    // with 4 loops
    CCAnimation *animation3 = (CCAnimation *)animation2->copy()->autorelease();
    animation3->setLoops(4);


    CCAnimate* action3 = CCAnimate::create(animation3);
    _kathia->runAction(action3);
}

void ActionAnimate::onExit()
{
    ActionsDemo::onExit();
    //TODO:[[NSNotificationCenter defaultCenter] removeObserver:observer_);
}

std::string ActionAnimate::title()
{
    return "Animation";
}

std::string ActionAnimate::subtitle()
{
    return "Center: Manual animation. Border: using file format animation";
}

//------------------------------------------------------------------
//
//    ActionSequence
//
//------------------------------------------------------------------
void ActionSequence::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    CCFiniteTimeAction*  action = CCSequence::create(
        CCMoveBy::create( 2, ccp(240,0)),
        CCRotateBy::create( 2,  540),
        NULL);

    _grossini->runAction(action);
}

std::string ActionSequence::subtitle()
{
    return "Sequence: Move + Rotate";
}

//------------------------------------------------------------------
//
//    ActionSequence2
//
//------------------------------------------------------------------
void ActionSequence2::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    _grossini->setVisible(false);

    CCFiniteTimeAction*  action = CCSequence::create(
		CCPlace::create(ccp(200,200)),
		CCShow::create(),
		CCMoveBy::create(1, ccp(100,0)),
		// CC_CALLBACK_0 == std::bind( &function, instance, ...)
		CCCallFunc::create( CC_CALLBACK_0(ActionSequence2::callback1,this)),
		CCCallFunc::create( CC_CALLBACK_0(ActionSequence2::callback2,this,_grossini)),
		CCCallFunc::create( CC_CALLBACK_0(ActionSequence2::callback3,this,_grossini,(void*)0xbebabeba)),
		NULL);

    _grossini->runAction(action);
}

void ActionSequence2::callback1()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF *label = CCLabelTTF::create("callback 1 called", "Marker Felt", 16);
    label->setPosition(ccp( s.width/4*1,s.height/2));

    addChild(label);
}

void ActionSequence2::callback2(CCNode* sender)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF *label = CCLabelTTF::create("callback 2 called", "Marker Felt", 16);
    label->setPosition(ccp( s.width/4*2,s.height/2));

    addChild(label);
}

void ActionSequence2::callback3(CCNode* sender, void* data)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF *label = CCLabelTTF::create("callback 3 called", "Marker Felt", 16);
    label->setPosition(ccp( s.width/4*3,s.height/2));

    addChild(label);
}

std::string ActionSequence2::subtitle()
{
    return "Sequence of InstantActions";
}

//------------------------------------------------------------------
//
//    ActionCallFunc
//    DEPRECATED. Use the std::function() API instead
//
//------------------------------------------------------------------
void ActionCallFunc::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    CCFiniteTimeAction*  action = CCSequence::create(
        CCMoveBy::create(2, ccp(200,0)),
        CCCallFunc::create(this, callfunc_selector(ActionCallFunc::callback1)), 
        NULL);

    CCFiniteTimeAction*  action2 = CCSequence::create(
        CCScaleBy::create(2 ,  2),
        CCFadeOut::create(2),
        CCCallFuncN::create(this, callfuncN_selector(ActionSequence2::callback2)), 
        NULL);

    CCFiniteTimeAction*  action3 = CCSequence::create(
        CCRotateBy::create(3 , 360),
        CCFadeOut::create(2),
        CCCallFuncND::create(this, callfuncND_selector(ActionSequence2::callback3), (void*)0xbebabeba), 
        NULL);

    _grossini->runAction(action);
    _tamara->runAction(action2);
    _kathia->runAction(action3);
}


void ActionCallFunc::callback1()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF *label = CCLabelTTF::create("callback 1 called", "Marker Felt", 16);
    label->setPosition(ccp( s.width/4*1,s.height/2));

    addChild(label);
}

void ActionCallFunc::callback2(CCNode* pSender)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF *label = CCLabelTTF::create("callback 2 called", "Marker Felt", 16);
    label->setPosition(ccp( s.width/4*2,s.height/2));

    addChild(label);
}

void ActionCallFunc::callback3(CCNode* pTarget, void* data)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF *label = CCLabelTTF::create("callback 3 called", "Marker Felt", 16);
    label->setPosition(ccp( s.width/4*3,s.height/2));
    addChild(label);
}

std::string ActionCallFunc::subtitle()
{
    return "Callbacks: CallFunc. Old way. Avoid it";
}

//------------------------------------------------------------------
//
// ActionCallFuncND
// DEPRECATED. Use the std::function() API instead
//
//------------------------------------------------------------------
void ActionCallFuncND::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(1);

    CCFiniteTimeAction* action = CCSequence::create(CCMoveBy::create(2.0f, ccp(200,0)),
        CCCallFuncND::create(this, callfuncND_selector(ActionCallFuncND::removeFromParentAndCleanup), (void*)true),
        NULL);

    _grossini->runAction(action);
}

std::string ActionCallFuncND::title()
{
    return "CallFuncND + auto remove";
}

std::string ActionCallFuncND::subtitle()
{
    return "CallFuncND + removeFromParentAndCleanup. Grossini dissapears in 2s";
}

void ActionCallFuncND::removeFromParentAndCleanup(CCNode* pSender, void* data)
{
    bool bCleanUp = data != NULL;
    _grossini->removeFromParentAndCleanup(bCleanUp);
}

//------------------------------------------------------------------
//
//    ActionCallFunction
//
//------------------------------------------------------------------
void ActionCallFunction::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);


	CCFiniteTimeAction*  action1 = CCSequence::create(
													  CCMoveBy::create(2, ccp(200,0)),
													  CCCallFunc::create( std::bind(&ActionCallFunction::callback1, this) ),
													  CCCallFunc::create(
																			 // lambda
																			 [&](){
																				 CCSize s = CCDirector::sharedDirector()->getWinSize();
																				 CCLabelTTF *label = CCLabelTTF::create("called:lambda callback", "Marker Felt", 16);
																				 label->setPosition(ccp( s.width/4*1,s.height/2-40));
																				 this->addChild(label);
																			 }  ),
													  NULL);

    CCFiniteTimeAction*  action2 = CCSequence::create(
													  CCScaleBy::create(2 ,  2),
													  CCFadeOut::create(2),
													  CCCallFunc::create( std::bind(&ActionCallFunction::callback2, this, _tamara) ),
													  NULL);

    CCFiniteTimeAction*  action3 = CCSequence::create(
													  CCRotateBy::create(3 , 360),
													  CCFadeOut::create(2),
													  CCCallFunc::create( std::bind(&ActionCallFunction::callback3, this, _kathia, (void*)42) ),
													  NULL);

    _grossini->runAction(action1);
    _tamara->runAction(action2);
    _kathia->runAction(action3);
}


void ActionCallFunction::callback1()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF *label = CCLabelTTF::create("callback 1 called", "Marker Felt", 16);
    label->setPosition(ccp( s.width/4*1,s.height/2));

    addChild(label);
}

void ActionCallFunction::callback2(CCNode* sender)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF *label = CCLabelTTF::create("callback 2 called", "Marker Felt", 16);
    label->setPosition(ccp( s.width/4*2,s.height/2));

    addChild(label);

	CCLOG("sender is: %p", sender);
}

void ActionCallFunction::callback3(CCNode* sender, void* data)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF *label = CCLabelTTF::create("callback 3 called", "Marker Felt", 16);
    label->setPosition(ccp( s.width/4*3,s.height/2));
    addChild(label);

	CCLOG("target is: %p, data is: %ld", sender, (long)data);
}

std::string ActionCallFunction::subtitle()
{
    return "Callbacks: CallFunc with std::function()";
}
//------------------------------------------------------------------
//
// ActionSpawn
//
//------------------------------------------------------------------

void ActionSpawn::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);


    CCAction*  action = CCSpawn::create(
        CCJumpBy::create(2, ccp(300,0), 50, 4),
        CCRotateBy::create( 2,  720),
        NULL);

    _grossini->runAction(action);
}

std::string ActionSpawn::subtitle()
{
    return "Spawn: Jump + Rotate";
}


//------------------------------------------------------------------
//
// ActionRepeatForever
//
//------------------------------------------------------------------
void ActionRepeatForever::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(1);

    CCFiniteTimeAction*  action = CCSequence::create(
        CCDelayTime::create(1),
        CCCallFunc::create( std::bind( &ActionRepeatForever::repeatForever, this, _grossini) ),
        NULL);

    _grossini->runAction(action);
}

void ActionRepeatForever::repeatForever(CCNode* pSender)
{
    CCRepeatForever *repeat = CCRepeatForever::create( CCRotateBy::create(1.0f, 360) );

    pSender->runAction(repeat);
}

std::string ActionRepeatForever::subtitle()
{
    return "CallFuncN + RepeatForever";
}


//------------------------------------------------------------------
//
// ActionRotateToRepeat
//
//------------------------------------------------------------------
void ActionRotateToRepeat::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(2);

    CCActionInterval*  act1 = CCRotateTo::create(1, 90);
    CCActionInterval*  act2 = CCRotateTo::create(1, 0);
    CCActionInterval*  seq = CCSequence::create(act1, act2, NULL);
    CCAction*  rep1 = CCRepeatForever::create(seq);
    CCActionInterval*  rep2 = CCRepeat::create((CCFiniteTimeAction*)(seq->copy()->autorelease()), 10);

    _tamara->runAction(rep1);
    _kathia->runAction(rep2);
}

std::string ActionRotateToRepeat ::subtitle()
{
    return "Repeat/RepeatForever + RotateTo";
}


//------------------------------------------------------------------
//
// ActionRotateJerk
//
//------------------------------------------------------------------
void ActionRotateJerk::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(2);

    CCFiniteTimeAction*  seq = CCSequence::create(
        CCRotateTo::create(0.5f, -20),
        CCRotateTo::create(0.5f, 20),
        NULL);

    CCActionInterval*  rep1 = CCRepeat::create(seq, 10);
    CCAction*  rep2 = CCRepeatForever::create( (CCActionInterval*)(seq->copy()->autorelease()) );

    _tamara->runAction(rep1);
    _kathia->runAction(rep2);
}

std::string ActionRotateJerk::subtitle()
{
    return "RepeatForever / Repeat + Rotate";
}

//------------------------------------------------------------------
//
// ActionReverse
//
//------------------------------------------------------------------
void ActionReverse::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    CCActionInterval*  jump = CCJumpBy::create(2, ccp(300,0), 50, 4);
    CCFiniteTimeAction*  action = CCSequence::create( jump, jump->reverse(), NULL);

    _grossini->runAction(action);
}

std::string ActionReverse::subtitle()
{
    return "Reverse an action";
}


//------------------------------------------------------------------
//
// ActionDelayTime
//
//------------------------------------------------------------------
void ActionDelayTime::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    CCActionInterval*  move = CCMoveBy::create(1, ccp(150,0));
    CCFiniteTimeAction*  action = CCSequence::create( move, CCDelayTime::create(2), move, NULL);

    _grossini->runAction(action);
}

std::string ActionDelayTime::subtitle()
{
    return "DelayTime: m + delay + m";
}


//------------------------------------------------------------------
//
// ActionReverseSequence
//
//------------------------------------------------------------------
void ActionReverseSequence::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    CCActionInterval*  move1 = CCMoveBy::create(1, ccp(250,0));
    CCActionInterval*  move2 = CCMoveBy::create(1, ccp(0,50));
    CCFiniteTimeAction*  seq = CCSequence::create( move1, move2, move1->reverse(), NULL);
    CCFiniteTimeAction*  action = CCSequence::create( seq, seq->reverse(), NULL);

    _grossini->runAction(action);
}

std::string ActionReverseSequence::subtitle()
{
    return "Reverse a sequence";
}


//------------------------------------------------------------------
//
// ActionReverseSequence2
//
//------------------------------------------------------------------
void ActionReverseSequence2::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(2);


    // Test:
    //   Sequence should work both with IntervalAction and InstantActions
    CCActionInterval*  move1 = CCMoveBy::create(1, ccp(250,0));
    CCActionInterval*  move2 = CCMoveBy::create(1, ccp(0,50));
    CCToggleVisibility*  tog1 = new CCToggleVisibility();
    CCToggleVisibility*  tog2 = new CCToggleVisibility();
    tog1->autorelease();
    tog2->autorelease();
    CCFiniteTimeAction*  seq = CCSequence::create( move1, tog1, move2, tog2, move1->reverse(), NULL);
    CCActionInterval*  action = CCRepeat::create(CCSequence::create( seq, seq->reverse(), NULL), 3);



    // Test:
    //   Also test that the reverse of Hide is Show, and vice-versa
    _kathia->runAction(action);

    CCActionInterval*  move_tamara = CCMoveBy::create(1, ccp(100,0));
    CCActionInterval*  move_tamara2 = CCMoveBy::create(1, ccp(50,0));
    CCActionInstant*  hide = CCHide::create();
    CCFiniteTimeAction*  seq_tamara = CCSequence::create( move_tamara, hide, move_tamara2, NULL);
    CCFiniteTimeAction*  seq_back = seq_tamara->reverse();
    _tamara->runAction( CCSequence::create( seq_tamara, seq_back, NULL));
}
std::string ActionReverseSequence2::subtitle()
{
    return "Reverse sequence 2";
}

//------------------------------------------------------------------
//
// ActionRepeat
//
//------------------------------------------------------------------
void ActionRepeat::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(2);


    CCActionInterval*  a1 = CCMoveBy::create(1, ccp(150,0));
    CCActionInterval*  action1 = CCRepeat::create(
        CCSequence::create( CCPlace::create(ccp(60,60)), a1, NULL) , 
        3); 
    CCAction*  action2 = CCRepeatForever::create(
        CCSequence::create((CCActionInterval*)(a1->copy()->autorelease()), a1->reverse(), NULL)
        );

    _kathia->runAction(action1);
    _tamara->runAction(action2);
}

std::string ActionRepeat::subtitle()
{
    return "Repeat / RepeatForever actions";
}

//------------------------------------------------------------------
//
// ActionOrbit
//
//------------------------------------------------------------------
void ActionOrbit::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    CCActionInterval*  orbit1 = CCOrbitCamera::create(2,1, 0, 0, 180, 0, 0);
    CCSequence*  action1 = CCSequence::create(
        orbit1,
        orbit1->reverse(),
        NULL);

    CCActionInterval*  orbit2 = CCOrbitCamera::create(2,1, 0, 0, 180, -45, 0);
    CCSequence*  action2 = CCSequence::create(
        orbit2,
        orbit2->reverse(),
        NULL);

    CCActionInterval*  orbit3 = CCOrbitCamera::create(2,1, 0, 0, 180, 90, 0);
    CCSequence*  action3 = CCSequence::create(
        orbit3,
        orbit3->reverse(),
        NULL);

    _kathia->runAction(CCRepeatForever::create(action1));
    _tamara->runAction(CCRepeatForever::create(action2));
    _grossini->runAction(CCRepeatForever::create(action3));

    CCActionInterval*  move = CCMoveBy::create(3, ccp(100,-100));
    CCActionInterval*  move_back = move->reverse();
    CCSequence*  seq = CCSequence::create(move, move_back, NULL);
    CCAction*  rfe = CCRepeatForever::create(seq);
    _kathia->runAction(rfe);
    _tamara->runAction((CCAction*)(rfe->copy()->autorelease()));
    _grossini->runAction((CCAction*)(rfe->copy()->autorelease()));
}

std::string ActionOrbit::subtitle()
{
    return "OrbitCamera action";
}

//------------------------------------------------------------------
//
// ActionFollow
//
//------------------------------------------------------------------
void ActionFollow::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(1);
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    _grossini->setPosition(ccp(-200, s.height / 2));
    CCActionInterval* move      = CCMoveBy::create(2, ccp(s.width * 3, 0));
    CCActionInterval* move_back = move->reverse();
    CCSequence* seq       = CCSequence::create(move, move_back, NULL);
    CCAction* rep               = CCRepeatForever::create(seq);

    _grossini->runAction(rep);

    this->runAction(CCFollow::create(_grossini, CCRectMake(0, 0, s.width * 2 - 100, s.height)));
}

void ActionFollow::draw()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
	float x = winSize.width*2 - 100;
	float y = winSize.height;
    
	CCPoint vertices[] = { ccp(5,5), ccp(x-5,5), ccp(x-5,y-5), ccp(5,y-5) };
	ccDrawPoly(vertices, 4, true);
}

std::string ActionFollow::subtitle()
{
    return "Follow action";
}

void ActionTargeted::onEnter()
{
    ActionsDemo::onEnter();
    centerSprites(2);


    CCJumpBy* jump1 = CCJumpBy::create(2,CCPointZero,100,3);
    CCJumpBy* jump2 = (CCJumpBy*)jump1->copy()->autorelease();
    CCRotateBy* rot1 =  CCRotateBy::create(1, 360);
    CCRotateBy* rot2 = (CCRotateBy*)rot1->copy()->autorelease();

    CCTargetedAction *t1 = CCTargetedAction::create(_kathia, jump2);
    CCTargetedAction *t2 = CCTargetedAction::create(_kathia, rot2);


    CCSequence* seq = (CCSequence*)CCSequence::create(jump1, t1, rot1, t2, NULL);
    CCRepeatForever *always = CCRepeatForever::create(seq);

    _tamara->runAction(always);
}

std::string ActionTargeted::title()
{
    return "ActionTargeted";
}

std::string ActionTargeted::subtitle()
{
    return "Action that runs on another target. Useful for sequences";
}

//#pragma mark - ActionStacked

void ActionStacked::onEnter()
{
    ActionsDemo::onEnter();
        
    this->centerSprites(0);
    
    this->setTouchEnabled(true);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    this->addNewSpriteWithCoords(ccp(s.width/2, s.height/2));
}

void ActionStacked::addNewSpriteWithCoords(CCPoint p)
{
    int idx = CCRANDOM_0_1() * 1400 / 100;
    int x = (idx%5) * 85;
    int y = (idx/5) * 121;
    
    
    CCSprite *sprite = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(x,y,85,121));
    
    sprite->setPosition(p);
    this->addChild(sprite);
    
    this->runActionsInSprite(sprite);
}

void ActionStacked::runActionsInSprite(CCSprite *sprite)
{
    // override me
}

void ActionStacked::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCSetIterator it;
    CCTouch* touch;

    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);

        if(!touch)
            break;

        CCPoint location = touch->getLocation();

        addNewSpriteWithCoords( location );
    }
}

std::string ActionStacked::title()
{
    return "Override me";
}

std::string ActionStacked::subtitle()
{
    return "Tap screen";
}

//#pragma mark - ActionMoveStacked


void ActionMoveStacked::runActionsInSprite(CCSprite *sprite)
{
    sprite->runAction(
        CCRepeatForever::create(
                CCSequence::create(
                CCMoveBy::create(0.05f, ccp(10,10)),
                CCMoveBy::create(0.05f, ccp(-10,-10)),
       NULL)));
    
    CCMoveBy* action = CCMoveBy::create(2.0f, ccp(400,0));
    CCMoveBy* action_back = (CCMoveBy*)action->reverse();
    
    sprite->runAction(
      CCRepeatForever::create(
        CCSequence::create(action, action_back, NULL)
      ));
}


std::string ActionMoveStacked::title()
{
    return "Stacked CCMoveBy/To actions";
}

//#pragma mark - ActionMoveJumpStacked

void ActionMoveJumpStacked::runActionsInSprite(CCSprite *sprite)
{
    sprite->runAction(
          CCRepeatForever::create(
            CCSequence::create(
             CCMoveBy::create(0.05f, ccp(10,2)),
             CCMoveBy::create(0.05f, ccp(-10,-2)),
             NULL)));
    
    CCJumpBy* jump = CCJumpBy::create(2.0f, ccp(400,0), 100, 5);
    CCJumpBy* jump_back = (CCJumpBy*)jump->reverse();
    
    sprite->runAction(
      CCRepeatForever::create(
          CCSequence::create(jump, jump_back, NULL)
          ));
}

std::string ActionMoveJumpStacked::title()
{
    return "tacked Move + Jump actions";
}

//#pragma mark - ActionMoveBezierStacked

void ActionMoveBezierStacked::runActionsInSprite(CCSprite *sprite)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    // sprite 1
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp(0, s.height/2);
    bezier.controlPoint_2 = ccp(300, -s.height/2);
    bezier.endPosition = ccp(300,100);
    
    CCBezierBy* bezierForward = CCBezierBy::create(3, bezier);
    CCBezierBy* bezierBack = (CCBezierBy*)bezierForward->reverse();
    CCSequence* seq = CCSequence::create(bezierForward, bezierBack, NULL);
    CCRepeatForever* rep = CCRepeatForever::create(seq);
    sprite->runAction(rep);
    
    sprite->runAction(
     CCRepeatForever::create(
      CCSequence::create(
       CCMoveBy::create(0.05f, ccp(10,0)),
       CCMoveBy::create(0.05f, ccp(-10,0)),
       NULL)));
}

std::string ActionMoveBezierStacked::title()
{
    return "Stacked Move + Bezier actions";
}


//#pragma mark - ActionCatmullRomStacked

void ActionCatmullRomStacked::onEnter()
{
    ActionsDemo::onEnter();
    
    this->centerSprites(2);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    //
    // sprite 1 (By)
    //
    // startPosition can be any coordinate, but since the movement
    // is relative to the Catmull Rom curve, it is better to start with (0,0).
    //
    
    _tamara->setPosition(ccp(50,50));
    
    CCPointArray *array = CCPointArray::create(20);
    
    array->addControlPoint(ccp(0,0));
    array->addControlPoint(ccp(80,80));
    array->addControlPoint(ccp(s.width-80,80));
    array->addControlPoint(ccp(s.width-80,s.height-80));
    array->addControlPoint(ccp(80,s.height-80));
    array->addControlPoint(ccp(80,80));
    array->addControlPoint(ccp(s.width/2, s.height/2));
    
    CCCatmullRomBy *action = CCCatmullRomBy::create(3, array);
    CCCatmullRomBy* reverse = (CCCatmullRomBy*)action->reverse();
    
    CCSequence *seq = CCSequence::create(action, reverse, NULL);
    
    _tamara->runAction(seq);
    
    
    _tamara->runAction(
     CCRepeatForever::create(
      CCSequence::create(
       CCMoveBy::create(0.05f, ccp(10,0)),
       CCMoveBy::create(0.05f, ccp(-10,0)),
       NULL)));
    
    
    //
    // sprite 2 (To)
    //
    // The startPosition is not important here, because it uses a "To" action.
    // The initial position will be the 1st point of the Catmull Rom path
    //
    
    CCPointArray *array2 = CCPointArray::create(20);
    
    array2->addControlPoint(ccp(s.width/2, 30));
    array2->addControlPoint(ccp(s.width-80,30));
    array2->addControlPoint(ccp(s.width-80,s.height-80));
    array2->addControlPoint(ccp(s.width/2,s.height-80));
    array2->addControlPoint(ccp(s.width/2, 30));
    
    
    CCCatmullRomTo *action2 = CCCatmullRomTo::create(3, array2);
    CCCatmullRomTo* reverse2 = (CCCatmullRomTo*)action2->reverse();
    
    CCSequence *seq2 = CCSequence::create(action2, reverse2, NULL);
    
    _kathia->runAction(seq2);
    
    
    _kathia->runAction(
     CCRepeatForever::create(
      CCSequence::create(
       CCMoveBy::create(0.05f, ccp(10,0)),
       CCMoveBy::create(0.05f, ccp(-10,0)),
       NULL)));
    
    
    array->retain();
    _array1 = array;
    array2->retain();
    _array2 = array2;
}

ActionCatmullRomStacked::~ActionCatmullRomStacked()
{
    CC_SAFE_RELEASE(_array1);
    CC_SAFE_RELEASE(_array2);
}

void ActionCatmullRomStacked::draw()
{
    ActionsDemo::draw();
    
    // move to 50,50 since the "by" path will start at 50,50
    kmGLPushMatrix();
    kmGLTranslatef(50, 50, 0);
    ccDrawCatmullRom(_array1,50);
    kmGLPopMatrix();
    
    ccDrawCatmullRom(_array2,50);
}

std::string ActionCatmullRomStacked::title()
{
    return "Stacked MoveBy + CatmullRom actions";
}

std::string ActionCatmullRomStacked::subtitle()
{
    return "MoveBy + CatmullRom at the same time in the same sprite";
}


//#pragma mark - ActionCardinalSplineStacked

void ActionCardinalSplineStacked::onEnter()
{
    ActionsDemo::onEnter();
    
    this->centerSprites(2);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCPointArray *array = CCPointArray::create(20);
    
    array->addControlPoint(ccp(0, 0));
    array->addControlPoint(ccp(s.width/2-30,0));
    array->addControlPoint(ccp(s.width/2-30,s.height-80));
    array->addControlPoint(ccp(0, s.height-80));
    array->addControlPoint(ccp(0, 0));
    
    
    //
    // sprite 1 (By)
    //
    // Spline with no tension (tension==0)
    //
    
    
    CCCatmullRomBy *action = (CCCatmullRomBy*)CCCardinalSplineBy::create(3, array, 0);
    CCCatmullRomBy* reverse = (CCCatmullRomBy*)action->reverse();
    
    CCSequence *seq = CCSequence::create(action, reverse, NULL);
    
    _tamara->setPosition(ccp(50,50));
    _tamara->runAction(seq);
    
    _tamara->runAction(
     CCRepeatForever::create(
      CCSequence::create(
       CCMoveBy::create(0.05f, ccp(10,0)),
       CCMoveBy::create(0.05f, ccp(-10,0)),
       NULL)));
    
    
    //
    // sprite 2 (By)
    //
    // Spline with high tension (tension==1)
    //
    
    CCCatmullRomBy *action2 = (CCCatmullRomBy*)CCCardinalSplineBy::create(3, array, 1);
    CCCatmullRomBy* reverse2 = (CCCatmullRomBy*)action2->reverse();
    
    CCSequence *seq2 = CCSequence::create(action2, reverse2, NULL);
    
    _kathia->setPosition(ccp(s.width/2,50));
    
    _kathia->runAction(seq2);
    
    _kathia->runAction(
     CCRepeatForever::create(
      CCSequence::create(
       CCMoveBy::create(0.05f, ccp(10,0)),
       CCMoveBy::create(0.05f, ccp(-10,0)),
       NULL)));
    
    
    array->retain();
    _array = array;
}

ActionCardinalSplineStacked::~ActionCardinalSplineStacked()
{
    CC_SAFE_RELEASE(_array);
}

void ActionCardinalSplineStacked::draw()
{
    ActionsDemo::draw();
    
    // move to 50,50 since the "by" path will start at 50,50
    kmGLPushMatrix();
    kmGLTranslatef(50, 50, 0);
    ccDrawCardinalSpline(_array, 0, 100);
    kmGLPopMatrix();
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    kmGLPushMatrix();
    kmGLTranslatef(s.width/2, 50, 0);
    ccDrawCardinalSpline(_array, 1, 100);
    kmGLPopMatrix();
}

std::string ActionCardinalSplineStacked::title()
{
    return "Stacked MoveBy + CardinalSpline actions";
}

std::string ActionCardinalSplineStacked::subtitle()
{
    return "CCMoveBy + CCCardinalSplineBy/To at the same time";
}

// Issue1305
void Issue1305::onEnter()
{
    ActionsDemo::onEnter();
    centerSprites(0);

    _spriteTmp = CCSprite::create("Images/grossini.png");
    /* c++ can't support block, so we use CCCallFuncN instead.
    [spriteTmp_ runAction:[CCCallBlockN actionWithBlock:^(CCNode* node) {
        NSLog(@"This message SHALL ONLY appear when the sprite is added to the scene, NOT BEFORE");
    }] );
    */

    _spriteTmp->runAction(CCCallFunc::create(std::bind(&Issue1305::log, this, _spriteTmp)));
    _spriteTmp->retain();

    scheduleOnce(schedule_selector(Issue1305::addSprite), 2);
}

void Issue1305::log(CCNode* pSender)
{
    CCLog("This message SHALL ONLY appear when the sprite is added to the scene, NOT BEFORE");
}

void Issue1305::onExit()
{
    _spriteTmp->stopAllActions();
    _spriteTmp->release();
    ActionsDemo::onExit();
}

void Issue1305::addSprite(float dt)
{
    _spriteTmp->setPosition(ccp(250,250));
    addChild(_spriteTmp);
}

std::string Issue1305::title()
{
    return "Issue 1305";
}

std::string Issue1305::subtitle()
{
    return "In two seconds you should see a message on the console. NOT BEFORE.";
}

void Issue1305_2::onEnter()
{
    ActionsDemo::onEnter();
    centerSprites(0);

    CCSprite *spr = CCSprite::create("Images/grossini.png");
    spr->setPosition(ccp(200,200));
    addChild(spr);

    CCMoveBy* act1 = CCMoveBy::create(2 ,ccp(0, 100));
    /* c++ can't support block, so we use CCCallFuncN instead.
    id act2 = [CCCallBlock actionWithBlock:^{
        NSLog(@"1st block");
    });
    id act3 = [CCMoveBy create:2, ccp(0, -100));
    id act4 = [CCCallBlock actionWithBlock:^{
        NSLog(@"2nd block");
    });
    id act5 = [CCMoveBy create:2, ccp(100, -100));
    id act6 = [CCCallBlock actionWithBlock:^{
        NSLog(@"3rd block");
    });
    id act7 = [CCMoveBy create:2, ccp(-100, 0));
    id act8 = [CCCallBlock actionWithBlock:^{
        NSLog(@"4th block");
    });
    */

    CCCallFunc* act2 = CCCallFunc::create( std::bind( &Issue1305_2::printLog1, this));
    CCMoveBy* act3 = CCMoveBy::create(2, ccp(0, -100));
    CCCallFunc* act4 = CCCallFunc::create( std::bind( &Issue1305_2::printLog2, this));
    CCMoveBy* act5 = CCMoveBy::create(2, ccp(100, -100));
    CCCallFunc* act6 = CCCallFunc::create( std::bind( &Issue1305_2::printLog3, this));
    CCMoveBy* act7 = CCMoveBy::create(2, ccp(-100, 0));
    CCCallFunc* act8 = CCCallFunc::create( std::bind( &Issue1305_2::printLog4, this));

    CCFiniteTimeAction* actF = CCSequence::create(act1, act2, act3, act4, act5, act6, act7, act8, NULL);

    //    [spr runAction:actF);
    CCDirector::sharedDirector()->getActionManager()->addAction(actF ,spr, false);

}

void Issue1305_2::printLog1()
{
    CCLog("1st block");
}

void Issue1305_2::printLog2()
{
    CCLog("2nd block");
}

void Issue1305_2::printLog3()
{
    CCLog("3rd block");
}

void Issue1305_2::printLog4()
{
    CCLog("4th block");
}

std::string Issue1305_2::title()
{
    return "Issue 1305 #2";
}

std::string Issue1305_2::subtitle()
{
    return "See console. You should only see one message for each block";
}

void Issue1288::onEnter()
{
    ActionsDemo::onEnter();
    centerSprites(0);

    CCSprite *spr = CCSprite::create("Images/grossini.png");
    spr->setPosition(ccp(100, 100));
    addChild(spr);

    CCMoveBy* act1 = CCMoveBy::create(0.5, ccp(100, 0));
    CCMoveBy* act2 = (CCMoveBy*)act1->reverse();
    CCFiniteTimeAction* act3 = CCSequence::create(act1, act2, NULL);
    CCRepeat* act4 = CCRepeat::create(act3, 2);

    spr->runAction(act4);
}

std::string Issue1288::title()
{
    return "Issue 1288";
}

std::string Issue1288::subtitle()
{
    return "Sprite should end at the position where it started.";
}

void Issue1288_2::onEnter()
{
    ActionsDemo::onEnter();
    centerSprites(0);

    CCSprite *spr = CCSprite::create("Images/grossini.png");
    spr->setPosition(ccp(100, 100));
    addChild(spr);

    CCMoveBy* act1 = CCMoveBy::create(0.5, ccp(100, 0));
    spr->runAction(CCRepeat::create(act1, 1));
}

std::string Issue1288_2::title()
{
    return "Issue 1288 #2";
}

std::string Issue1288_2::subtitle()
{
    return "Sprite should move 100 pixels, and stay there";
}


void Issue1327::onEnter()
{
    ActionsDemo::onEnter();
    centerSprites(0);

    CCSprite *spr = CCSprite::create("Images/grossini.png");
    spr->setPosition(ccp(100, 100));
    addChild(spr);

    CCCallFunc* act1 = CCCallFunc::create( std::bind(&Issue1327::logSprRotation, this, spr));
    CCRotateBy* act2 = CCRotateBy::create(0.25, 45);
    CCCallFunc* act3 = CCCallFunc::create( std::bind(&Issue1327::logSprRotation, this, spr));
    CCRotateBy* act4 = CCRotateBy::create(0.25, 45);
    CCCallFunc* act5 = CCCallFunc::create( std::bind(&Issue1327::logSprRotation, this, spr));
    CCRotateBy* act6 = CCRotateBy::create(0.25, 45);
    CCCallFunc* act7 = CCCallFunc::create( std::bind(&Issue1327::logSprRotation, this, spr));
    CCRotateBy* act8 = CCRotateBy::create(0.25, 45);
    CCCallFunc* act9 = CCCallFunc::create( std::bind(&Issue1327::logSprRotation, this, spr));

    CCFiniteTimeAction* actF = CCSequence::create(act1, act2, act3, act4, act5, act6, act7, act8, act9, NULL);
    spr->runAction(actF);
}

std::string Issue1327::title()
{
    return "Issue 1327";
}

std::string Issue1327::subtitle()
{
    return "See console: You should see: 0, 45, 90, 135, 180";
}

void Issue1327::logSprRotation(CCNode* pSender)
{
    CCLog("%f", ((CCSprite*)pSender)->getRotation());
}

//Issue1398
void Issue1398::incrementInteger()
{
    _testInteger++;
    CCLog("incremented to %d", _testInteger);
}

void Issue1398::onEnter()
{
    ActionsDemo::onEnter();
    this->centerSprites(0);

    _testInteger = 0;
    CCLog("testInt = %d", _testInteger);

    this->runAction(
        CCSequence::create(
			CCCallFunc::create( std::bind(&Issue1398::incrementIntegerCallback, this, (void*)"1")),
			CCCallFunc::create( std::bind(&Issue1398::incrementIntegerCallback, this, (void*)"2")),
			CCCallFunc::create( std::bind(&Issue1398::incrementIntegerCallback, this, (void*)"3")),
			CCCallFunc::create( std::bind(&Issue1398::incrementIntegerCallback, this, (void*)"4")),
			CCCallFunc::create( std::bind(&Issue1398::incrementIntegerCallback, this, (void*)"5")),
			CCCallFunc::create( std::bind(&Issue1398::incrementIntegerCallback, this, (void*)"6")),
			CCCallFunc::create( std::bind(&Issue1398::incrementIntegerCallback, this, (void*)"7")),
			CCCallFunc::create( std::bind(&Issue1398::incrementIntegerCallback, this, (void*)"8")),
            NULL));
}

void Issue1398::incrementIntegerCallback(void* data)
{
    this->incrementInteger();
    CCLog("%s", (char*)data);
}

std::string Issue1398::subtitle()
{
    return "See console: You should see an 8";
}

std::string Issue1398::title()
{
    return "Issue 1398";
}

/** ActionCatmullRom
 */
void ActionCatmullRom::onEnter()
{
    ActionsDemo::onEnter();
    
    this->centerSprites(2);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    //
    // sprite 1 (By)
    //
    // startPosition can be any coordinate, but since the movement
    // is relative to the Catmull Rom curve, it is better to start with (0,0).
    //
    
    _tamara->setPosition(ccp(50, 50));
    
    CCPointArray *array = CCPointArray::create(20);
    
    array->addControlPoint(ccp(0, 0));
    array->addControlPoint(ccp(80, 80));
    array->addControlPoint(ccp(s.width - 80, 80));
    array->addControlPoint(ccp(s.width - 80, s.height - 80));
    array->addControlPoint(ccp(80, s.height - 80));
    array->addControlPoint(ccp(80, 80));
    array->addControlPoint(ccp(s.width / 2, s.height / 2));
    
    CCCatmullRomBy *action = CCCatmullRomBy::create(3, array);
    CCFiniteTimeAction *reverse = action->reverse();
    
    CCFiniteTimeAction *seq = CCSequence::create(action, reverse, NULL);
    
    _tamara->runAction(seq);
    
    
    //
    // sprite 2 (To)
    //
    // The startPosition is not important here, because it uses a "To" action.
    // The initial position will be the 1st point of the Catmull Rom path
    //    
    
    CCPointArray *array2 = CCPointArray::create(20);
    
    array2->addControlPoint(ccp(s.width / 2, 30));
    array2->addControlPoint(ccp(s.width  -80, 30));
    array2->addControlPoint(ccp(s.width - 80, s.height - 80));
    array2->addControlPoint(ccp(s.width / 2, s.height - 80));
    array2->addControlPoint(ccp(s.width / 2, 30));
    
    CCCatmullRomTo *action2 = CCCatmullRomTo::create(3, array2);
    CCFiniteTimeAction *reverse2 = action2->reverse();
    
    CCFiniteTimeAction *seq2 = CCSequence::create(action2, reverse2, NULL);
    
    _kathia->runAction(seq2);
    
    _array1 = array;
    _array1->retain();
    _array2 = array2;
    _array2->retain();
}

ActionCatmullRom::~ActionCatmullRom()
{
    _array1->release();
    _array2->release();
}

void ActionCatmullRom::draw()
{
    ActionsDemo::draw();
    
    // move to 50,50 since the "by" path will start at 50,50
    kmGLPushMatrix();
    kmGLTranslatef(50, 50, 0);
    ccDrawCatmullRom(_array1, 50);
    kmGLPopMatrix();
    
    ccDrawCatmullRom(_array2,50);
}

string ActionCatmullRom::title()
{
    return "CatmullRomBy / CatmullRomTo";
}

string ActionCatmullRom::subtitle()
{
    return "Catmull Rom spline paths. Testing reverse too";
}

/** ActionCardinalSpline
 */
void ActionCardinalSpline::onEnter()
{
    ActionsDemo::onEnter();
    
    this->centerSprites(2);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCPointArray *array = CCPointArray::create(20);
    
    array->addControlPoint(ccp(0, 0));
    array->addControlPoint(ccp(s.width/2-30, 0));
    array->addControlPoint(ccp(s.width/2-30, s.height-80));
    array->addControlPoint(ccp(0, s.height-80));
    array->addControlPoint(ccp(0, 0));
    
    //
    // sprite 1 (By)
    //
    // Spline with no tension (tension==0)
    //
    
    CCCardinalSplineBy *action = CCCardinalSplineBy::create(3, array, 0);
    CCActionInterval *reverse = action->reverse();
    
    CCFiniteTimeAction *seq = CCSequence::create(action, reverse, NULL);
    
    _tamara->setPosition(ccp(50, 50));
    _tamara->runAction(seq);
    
    //
    // sprite 2 (By)
    //
    // Spline with high tension (tension==1)
    //
    
    CCCardinalSplineBy *action2 = CCCardinalSplineBy::create(3, array, 1);
    CCActionInterval *reverse2 = action2->reverse();
    
    CCFiniteTimeAction *seq2 = CCSequence::create(action2, reverse2, NULL);
    
    _kathia->setPosition(ccp(s.width/2, 50));
    _kathia->runAction(seq2);
    
    _array = array;
    array->retain();
}

ActionCardinalSpline::~ActionCardinalSpline()
{
    _array->release();
}

void ActionCardinalSpline::draw()
{
    ActionsDemo::draw();
    
    // move to 50,50 since the "by" path will start at 50,50
    kmGLPushMatrix();
    kmGLTranslatef(50, 50, 0);
    ccDrawCardinalSpline(_array, 0, 100);
    kmGLPopMatrix();
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    kmGLPushMatrix();
    kmGLTranslatef(s.width/2, 50, 0);
    ccDrawCardinalSpline(_array, 1, 100);
    kmGLPopMatrix();
}

string ActionCardinalSpline::title()
{
    return "CardinalSplineBy / CardinalSplineTo";
}

string ActionCardinalSpline::subtitle()
{
    return "Cardinal Spline paths. Testing different tensions for one array";
}

/** PauseResumeActions
 */

PauseResumeActions::PauseResumeActions()
: _pausedTargets(NULL)
{

}

PauseResumeActions::~PauseResumeActions()
{
    CC_SAFE_RELEASE(_pausedTargets);
}

void PauseResumeActions::onEnter()
{
    ActionsDemo::onEnter();
    
    this->centerSprites(3);
    
    _tamara->runAction(CCRepeatForever::create(CCRotateBy::create(3, 360)));
    _grossini->runAction(CCRepeatForever::create(CCRotateBy::create(3, -360)));
    _kathia->runAction(CCRepeatForever::create(CCRotateBy::create(3, 360)));
    
    this->schedule(schedule_selector(PauseResumeActions::pause), 3, false, 0);
    this->schedule(schedule_selector(PauseResumeActions::resume), 5, false, 0);
}

string PauseResumeActions::title()
{
    return "PauseResumeActions";
}

string PauseResumeActions::subtitle()
{
    return "All actions pause at 3s and resume at 5s";
}

void PauseResumeActions::pause(float dt)
{
    CCLog("Pausing");
    CCDirector *director = CCDirector::sharedDirector();

    CC_SAFE_RELEASE(_pausedTargets);
    _pausedTargets = director->getActionManager()->pauseAllRunningActions();
    CC_SAFE_RETAIN(_pausedTargets);
}

void PauseResumeActions::resume(float dt)
{
    CCLog("Resuming");
    CCDirector *director = CCDirector::sharedDirector();
    director->getActionManager()->resumeTargets(_pausedTargets);
}

//------------------------------------------------------------------
//
//    ActionRemoveSelf
//
//------------------------------------------------------------------
void ActionRemoveSelf::onEnter()
{
	ActionsDemo::onEnter();

	alignSpritesLeft(1);

	CCFiniteTimeAction*  action = CCSequence::create(
		CCMoveBy::create( 2, ccp(240,0)),
		CCRotateBy::create( 2,  540),
		CCScaleTo::create(1,0.1f),
		CCRemoveSelf::create(),
		NULL);

	_grossini->runAction(action);
}

std::string ActionRemoveSelf::subtitle()
{
	return "Sequence: Move + Rotate + Scale + RemoveSelf";
}
