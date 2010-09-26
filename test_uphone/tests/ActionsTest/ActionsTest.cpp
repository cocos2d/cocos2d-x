#include "ActionsTest.h"
#include "../testResource.h"

static Int32 s_nActionIdx = -1;

CCLayer* CreateLayer(Int32 nIndex)
{
    CCLayer * pLayer = NULL;

    switch (nIndex)
    {
    case ACTION_MANUAL_LAYER:
        pLayer = new ActionManual(); break;
    case ACTION_MOVE_LAYER:
        pLayer = new ActionMove(); break;
    case ACTION_SCALE_LAYER:
        pLayer = new ActionScale(); break;
    case ACTION_ROTATE_LAYER:
        pLayer = new ActionRotate(); break;
    case ACTION_JUMP_LAYER:
        pLayer = new ActionJump(); break;
    case ACTION_BEZIER_LAYER:
        pLayer = new ActionBezier(); break;
    case ACTION_BLINK_LAYER:
        pLayer = new ActionBlink(); break;
    case ACTION_FADE_LAYER:
        pLayer = new ActionFade(); break;
    case ACTION_TINT_LAYER:
        pLayer = new ActionTint(); break;
    case ACTION_ANIMATE_LAYER:
        pLayer = new ActionAnimate(); break;
    case ACTION_SEQUENCE_LAYER:
        pLayer = new ActionSequence(); break;
    case ACTION_SEQUENCE2_LAYER:
        pLayer = new ActionSequence2(); break;
    case ACTION_SPAWN_LAYER:
        pLayer = new ActionSpawn(); break;
    case ACTION_REVERSE:
        pLayer = new ActionReverse(); break;
    case ACTION_DELAYTIME_LAYER:
        pLayer = new ActionDelayTime(); break;
    case ACTION_REPEAT_LAYER:
        pLayer = new ActionRepeat(); break;
    case ACTION_REPEATEFOREVER_LAYER:
        pLayer = new ActionRepeatForever(); break;
    case ACTION_ROTATETOREPEATE_LAYER:
        pLayer = new ActionRotateToRepeat(); break;
    case ACTION_ROTATEJERK_LAYER:
        pLayer = new ActionRotateJerk(); break;    
    case ACTION_CALLFUNC_LAYER:
        pLayer = new ActionCallFunc(); break;
    case ACTION_REVERSESEQUENCE_LAYER:
        pLayer = new ActionReverseSequence(); break;
    case ACTION_REVERSESEQUENCE2_LAYER:
        pLayer = new ActionReverseSequence2(); break;
    case ACTION_ORBIT_LAYER:
        pLayer = new ActionOrbit(); break;
    case ACTION_FLLOW_LAYER:
        pLayer = new ActionFollow(); break;
    default:
        break;
    }

    return pLayer;
}

CCLayer* NextAction()
{
    ++s_nActionIdx;
    s_nActionIdx = s_nActionIdx % ACTION_LAYER_COUNT;

    CCLayer* pLayer = CreateLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* BackAction()
{
    --s_nActionIdx;
    if( s_nActionIdx < 0 )
        s_nActionIdx += ACTION_LAYER_COUNT;	

    CCLayer* pLayer = CreateLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* RestartAction()
{
    CCLayer* pLayer = CreateLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}


void ActionsTestScene::runThisTest()
{
    s_nActionIdx = -1;
    addChild(NextAction());

    CCDirector::getSharedDirector()->replaceScene(this);
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
    CCLayer::onEnter();

    // Example:
    // You can create a sprite using a Texture2D
    CCTexture2D *tex = new CCTexture2D();
    UIImage* pImage = new UIImage();
    std::string fullpath( CCFileUtils::fullPathFromRelativePath(s_pPathGrossini));
    pImage->initWithContentsOfFile(fullpath);
    tex->initWithImage( pImage );
    m_grossini = CCSprite::spriteWithTexture(tex);
    m_grossini->retain();
    delete pImage;
    tex->release();

    // Example:
    // Or you can create an sprite using a filename. only PNG is supported now. Probably TIFF too
    m_tamara = CCSprite::spriteWithFile(s_pPathSister1); 
    m_tamara->retain();

    m_kathia = CCSprite::spriteWithFile(s_pPathSister2);
    m_kathia->retain();

    addChild(m_grossini, 1);
    addChild(m_tamara, 2);
    addChild(m_kathia, 3);

    CGSize s = CCDirector::getSharedDirector()->getWinSize();

    m_grossini->setPosition( CGPointMake(s.width/2, s.height/3));
    m_tamara->setPosition( CGPointMake(s.width/2, 2*s.height/3));
    m_kathia->setPosition( CGPointMake(s.width/2, s.height/2)); 

    // add title and subtitle
    std::string str = title();
    const char * pTitle = str.c_str();
    CCLabel* label = CCLabel::labelWithString(pTitle, "Arial", 18);
    addChild(label, 1);
    label->setPosition( CGPointMake(s.width/2, s.height - 30) );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() ) 
    {
        CCLabel* l = CCLabel::labelWithString(strSubtitle.c_str(), "Thonburi", 22);
        addChild(l, 1);
        l->setPosition( CGPointMake(s.width/2, s.height - 60) );
    }	

    // add menu
    CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(ActionsDemo::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(ActionsDemo::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(ActionsDemo::nextCallback) );

    CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

    menu->setPosition( CGPointZero );
    item1->setPosition( CGPointMake( s.width/2 - 100,30) );
    item2->setPosition( CGPointMake( s.width/2, 30) );
    item3->setPosition( CGPointMake( s.width/2 + 100,30) );

    addChild(menu, 1);
}

void ActionsDemo::onExit()
{
    m_grossini->release();
    m_tamara->release();
    m_kathia->release();

    CCLayer::onExit();
}

void ActionsDemo::restartCallback(NSObject* pSender)
{
    CCScene* s = new ActionsTestScene();
    s->addChild( RestartAction() );
    CCDirector::getSharedDirector()->replaceScene(s);
    s->release();
}

void ActionsDemo::nextCallback(NSObject* pSender)
{
    CCScene* s = new ActionsTestScene();
    s->addChild( NextAction() );
    CCDirector::getSharedDirector()->replaceScene(s);
    s->release();
}

void ActionsDemo::backCallback(NSObject* pSender)
{
    CCScene* s = new ActionsTestScene();
    s->addChild( BackAction() );
    CCDirector::getSharedDirector()->replaceScene(s);
    s->release();
}

void ActionsDemo::centerSprites(unsigned int numberOfSprites)
{
    CGSize s = CCDirector::getSharedDirector()->getWinSize();

    if( numberOfSprites == 1 ) 
    {
        m_tamara->setIsVisible(false);
        m_kathia->setIsVisible(false);
        m_grossini->setPosition(CGPointMake(s.width/2, s.height/2));
    }
    else if( numberOfSprites == 2 ) 
    {		
        m_kathia->setPosition( CGPointMake(s.width/3, s.height/2));
        m_tamara->setPosition( CGPointMake(2*s.width/3, s.height/2));
        m_grossini->setIsVisible(false);
    } 
    else if( numberOfSprites == 3 ) 
    {
        m_grossini->setPosition( CGPointMake(s.width/2, s.height/2));
        m_tamara->setPosition( CGPointMake(s.width/4, s.height/2));
        m_kathia->setPosition( CGPointMake(3 * s.width/4, s.height/2));
    }
}

void ActionsDemo::alignSpritesLeft(unsigned int numberOfSprites)
{
    CGSize s = CCDirector::getSharedDirector()->getWinSize();

    if( numberOfSprites == 1 ) 
    {
        m_tamara->setIsVisible(false);
        m_kathia->setIsVisible(false);
        m_grossini->setPosition(CGPointMake(60, s.height/2));
    } 
    else if( numberOfSprites == 2 ) 
    {		
        m_kathia->setPosition( CGPointMake(60, s.height/3));
        m_tamara->setPosition( CGPointMake(60, 2*s.height/3));
        m_grossini->setIsVisible( false );
    } 
    else if( numberOfSprites == 3 ) 
    {
        m_grossini->setPosition( CGPointMake(60, s.height/2));
        m_tamara->setPosition( CGPointMake(60, 2*s.height/3));
        m_kathia->setPosition( CGPointMake(60, s.height/3));
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

    CGSize s = CCDirector::getSharedDirector()->getWinSize();

    m_tamara->setScaleX( 2.5f);
    m_tamara->setScaleY( -1.0f);
    m_tamara->setPosition( CGPointMake(100,70) );
    m_tamara->setOpacity( 128);

    m_grossini->setRotation( 120);
    m_grossini->setPosition( CGPointMake(s.width/2, s.height/2));
    m_grossini->setColor( ccc3( 255,0,0));

    m_kathia->setPosition( CGPointMake(s.width-100, s.height/2));
    m_kathia->setColor( ccBLUE);
}

std::string ActionManual::subtitle()
{
    return "Manual Transformation";
}

//------------------------------------------------------------------
//
//	ActionMove
//
//------------------------------------------------------------------
void ActionMove::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    CGSize s = CCDirector::getSharedDirector()->getWinSize();

    CCIntervalAction*  actionTo = CCMoveTo::actionWithDuration(2, CGPointMake(s.width-40, s.height-40));
    CCIntervalAction*  actionBy = CCMoveBy::actionWithDuration(2, CGPointMake(80,80));
    CCIntervalAction*  actionByBack = actionBy->reverse();

    m_tamara->runAction( actionTo);
    m_grossini->runAction( CCSequence::actions(actionBy, actionByBack, NULL));
    m_kathia->runAction(CCMoveTo::actionWithDuration(1, CGPointMake(40,40)));
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

    CCIntervalAction*  actionTo = CCScaleTo::actionWithDuration( 2, 0.5f);
    CCIntervalAction*  actionBy = CCScaleBy::actionWithDuration(2 ,  2);
    CCIntervalAction*  actionBy2 = CCScaleBy::actionWithDuration(2, 0.25f, 4.5f);
    CCIntervalAction*  actionByBack = actionBy->reverse();

    m_tamara->runAction( actionTo);
    m_grossini->runAction( CCSequence::actions(actionBy, actionByBack, NULL));
    m_kathia->runAction( CCSequence::actions(actionBy2, actionBy2->reverse(), NULL));
}

std::string ActionScale::subtitle()
{
    return "ScaleTo / ScaleBy";
}

//------------------------------------------------------------------
//
//	ActionRotate
//
//------------------------------------------------------------------
void ActionRotate::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    CCIntervalAction*  actionTo = CCRotateTo::actionWithDuration( 2, 45);
    CCIntervalAction*  actionTo2 = CCRotateTo::actionWithDuration( 2, -45);
    CCIntervalAction*  actionTo0 = CCRotateTo::actionWithDuration(2 , 0);
    m_tamara->runAction( CCSequence::actions(actionTo, actionTo0, NULL));

    CCIntervalAction*  actionBy = CCRotateBy::actionWithDuration(2 ,  360);
    CCIntervalAction*  actionByBack = actionBy->reverse();
    m_grossini->runAction( CCSequence::actions(actionBy, actionByBack, NULL));

    m_kathia->runAction( CCSequence::actions(actionTo2, actionTo0->copy()->autorelease(), NULL));
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

    CCIntervalAction*  actionTo = CCJumpTo::actionWithDuration(2, CGPointMake(300,300), 50, 4);
    CCIntervalAction*  actionBy = CCJumpBy::actionWithDuration(2, CGPointMake(300,0), 50, 4);
    CCIntervalAction*  actionUp = CCJumpBy::actionWithDuration(2, CGPointMake(0,0), 80, 4);
    CCIntervalAction*  actionByBack = actionBy->reverse();

    m_tamara->runAction( actionTo);
    m_grossini->runAction( CCSequence::actions(actionBy, actionByBack, NULL));
    m_kathia->runAction( CCRepeatForever::actionWithAction(actionUp));
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

    CGSize s = CCDirector::getSharedDirector()->getWinSize();

    //
    // startPosition can be any coordinate, but since the movement
    // is relative to the Bezier curve, make it (0,0)
    //

    centerSprites(3);

    // sprite 1
    ccBezierConfig bezier;
    bezier.controlPoint_1 = CGPointMake(0, s.height/2);
    bezier.controlPoint_2 = CGPointMake(300, -s.height/2);
    bezier.endPosition = CGPointMake(300,100);

    CCIntervalAction*  bezierForward = CCBezierBy::actionWithDuration(3, bezier);
    CCIntervalAction*  bezierBack = bezierForward->reverse();	
    CCAction*  rep = CCRepeatForever::actionWithAction((CCIntervalAction*)CCSequence::actions( bezierForward, bezierBack, NULL));


    // sprite 2
    m_tamara->setPosition(CGPointMake(80,160));
    ccBezierConfig bezier2;
    bezier2.controlPoint_1 = CGPointMake(100, s.height/2);
    bezier2.controlPoint_2 = CGPointMake(200, -s.height/2);
    bezier2.endPosition = CGPointMake(240,160);

    CCIntervalAction*  bezierTo1 = CCBezierTo::actionWithDuration(2, bezier2);	

    // sprite 3
    m_kathia->setPosition(CGPointMake(400,160));
    CCIntervalAction*  bezierTo2 = CCBezierTo::actionWithDuration(2, bezier2);

    m_grossini->runAction( rep);
    m_tamara->runAction(bezierTo1);
    m_kathia->runAction(bezierTo2);

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

    CCIntervalAction*  action1 = CCBlink::actionWithDuration(2, 10);
    CCIntervalAction*  action2 = CCBlink::actionWithDuration(2, 5);

    m_tamara->runAction( action1);
    m_kathia->runAction(action2);
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

    m_tamara->setOpacity( 0 );
    CCIntervalAction*  action1 = CCFadeIn::actionWithDuration(1.0f);
    CCIntervalAction*  action1Back = action1->reverse();

    CCIntervalAction*  action2 = CCFadeOut::actionWithDuration(1.0f);
    CCIntervalAction*  action2Back = action2->reverse();

    m_tamara->runAction( CCSequence::actions( action1, action1Back, NULL));
    m_kathia->runAction( CCSequence::actions( action2, action2Back, NULL));
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

    CCIntervalAction*  action1 = CCTintTo::actionWithDuration(2, 255, 0, 255);
    CCIntervalAction*  action2 = CCTintBy::actionWithDuration(2, -127, -255, -127);
    CCIntervalAction*  action2Back = action2->reverse();

    m_tamara->runAction( action1);
    m_kathia->runAction( CCSequence::actions( action2, action2Back, NULL));
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

    centerSprites(1);

    CCAnimation* animation = CCAnimation::animationWithName("dance", 0.2f);
    char frameName[100] = {0};
    for( int i=1;i<15;i++)
    {
        sprintf(frameName, "/NEWPLUS/TDA_DATA/Data/cocos2d_tests/Images/grossini_dance_%02d.png", i);
        animation->addFrameWithFileName(frameName);
    }

    CCIntervalAction*  action = CCAnimate::actionWithAnimation( animation, false);
    CCIntervalAction*  action_back = action->reverse();

    m_grossini->runAction( CCSequence::actions( action, action_back, NULL));
}

std::string ActionAnimate::subtitle()
{
    return "Animation";
}

//------------------------------------------------------------------
//
//	ActionSequence
//
//------------------------------------------------------------------
void ActionSequence::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    CCFiniteTimeAction*  action = CCSequence::actions(
        CCMoveBy::actionWithDuration( 2, CGPointMake(240,0)),
        CCRotateBy::actionWithDuration( 2,  540),
        NULL);

    m_grossini->runAction(action);
}

std::string ActionSequence::subtitle()
{
    return "Sequence: Move + Rotate";
}

//------------------------------------------------------------------
//
//	ActionSequence2
//
//------------------------------------------------------------------
void ActionSequence2::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    m_grossini->setIsVisible(false);

    CCFiniteTimeAction*  action = CCSequence::actions(
        CCPlace::actionWithPosition(CGPointMake(200,200)),
        CCShow::action(),
        CCMoveBy::actionWithDuration(1, CGPointMake(100,0)),
        CCCallFunc::actionWithTarget(this, callfunc_selector(ActionSequence2::callback1)),
        CCCallFuncN::actionWithTarget(this, callfuncN_selector(ActionSequence2::callback2)),
        CCCallFuncND::actionWithTarget(this, callfuncND_selector(ActionSequence2::callback3), (void*)0xbebabeba),
        NULL);

    m_grossini->runAction(action);
}

void ActionSequence2::callback1()
{
    CGSize s = CCDirector::getSharedDirector()->getWinSize();
    CCLabel *label = CCLabel::labelWithString("callback 1 called", "Marker Felt", 16);
    label->setPosition(CGPointMake( s.width/4*1,s.height/2));

    addChild(label);
}

void ActionSequence2::callback2(CCNode* sender)
{
    CGSize s = CCDirector::getSharedDirector()->getWinSize();
    CCLabel *label = CCLabel::labelWithString("callback 2 called", "Marker Felt", 16);
    label->setPosition(CGPointMake( s.width/4*2,s.height/2));

    addChild(label);
}

void ActionSequence2::callback3(CCNode* sender, void* data)
{
    CGSize s = CCDirector::getSharedDirector()->getWinSize();
    CCLabel *label = CCLabel::labelWithString("callback 3 called", "Marker Felt", 16);
    label->setPosition(CGPointMake( s.width/4*3,s.height/2));

    addChild(label);
}

std::string ActionSequence2::subtitle()
{
    return "Sequence of InstantActions";
}

//------------------------------------------------------------------
//
//	ActionCallFunc
//
//------------------------------------------------------------------
void ActionCallFunc::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    CCFiniteTimeAction*  action = CCSequence::actions(
        CCMoveBy::actionWithDuration(2, CGPointMake(200,0)),
        CCCallFunc::actionWithTarget(this, callfunc_selector(ActionCallFunc::callback1)), 
        NULL);

    CCFiniteTimeAction*  action2 = CCSequence::actions(
        CCScaleBy::actionWithDuration(2 ,  2),
        CCFadeOut::actionWithDuration(2),
        CCCallFuncN::actionWithTarget(this, callfuncN_selector(ActionSequence2::callback2)), 
        NULL);

    CCFiniteTimeAction*  action3 = CCSequence::actions(
        CCRotateBy::actionWithDuration(3 , 360),
        CCFadeOut::actionWithDuration(2),
        CCCallFuncND::actionWithTarget(this, callfuncND_selector(ActionSequence2::callback3), (void*)0xbebabeba), 
        NULL);

    m_grossini->runAction(action);
    m_tamara->runAction(action2);
    m_kathia->runAction(action3);
}


void ActionCallFunc::callback1()
{
    CGSize s = CCDirector::getSharedDirector()->getWinSize();
    CCLabel *label = CCLabel::labelWithString("callback 1 called", "Marker Felt", 16);
    label->setPosition(CGPointMake( s.width/4*1,s.height/2));

    addChild(label);
}

void ActionCallFunc::callback2(CCNode* pSender)
{
    CGSize s = CCDirector::getSharedDirector()->getWinSize();
    CCLabel *label = CCLabel::labelWithString("callback 2 called", "Marker Felt", 16);
    label->setPosition(CGPointMake( s.width/4*2,s.height/2));

    addChild(label);
}

void ActionCallFunc::callback3(CCNode* pTarget, void* data)
{
    CGSize s = CCDirector::getSharedDirector()->getWinSize();
    CCLabel *label = CCLabel::labelWithString("callback 3 called", "Marker Felt", 16);
    label->setPosition(CGPointMake( s.width/4*3,s.height/2));
    addChild(label);
}

std::string ActionCallFunc::subtitle()
{
    return "Callbacks: CallFunc and friends";
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


    CCAction*  action = CCSpawn::actions(
        CCJumpBy::actionWithDuration(2, CGPointMake(300,0), 50, 4),
        CCRotateBy::actionWithDuration( 2,  720),
        NULL);

    m_grossini->runAction(action);
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

    CCFiniteTimeAction*  action = CCSequence::actions(
        CCDelayTime::actionWithDuration(1),
        CCCallFuncN::actionWithTarget( this, callfuncN_selector(ActionRepeatForever::repeatForever) ), 
        NULL);

    m_grossini->runAction(action);
}

void ActionRepeatForever::repeatForever(CCNode* pSender)
{
    CCRepeatForever *repeat = CCRepeatForever::actionWithAction( CCRotateBy::actionWithDuration(1.0f, 360) );

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

    CCIntervalAction*  act1 = CCRotateTo::actionWithDuration(1, 90);
    CCIntervalAction*  act2 = CCRotateTo::actionWithDuration(1, 0);
    CCIntervalAction*  seq = (CCIntervalAction*)(CCSequence::actions(act1, act2, NULL));
    CCAction*  rep1 = CCRepeatForever::actionWithAction(seq);
    CCIntervalAction*  rep2 = CCRepeat::actionWithAction((CCFiniteTimeAction*)(seq->copy()->autorelease()), 10);

    m_tamara->runAction(rep1);
    m_kathia->runAction(rep2);
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

    CCFiniteTimeAction*  seq = CCSequence::actions(
        CCRotateTo::actionWithDuration(0.5f, -20),
        CCRotateTo::actionWithDuration(0.5f, 20),
        NULL);

    CCIntervalAction*  rep1 = CCRepeat::actionWithAction(seq, 10);
    CCAction*  rep2 = CCRepeatForever::actionWithAction( (CCIntervalAction*)(seq->copy()->autorelease()) );

    m_tamara->runAction(rep1);
    m_kathia->runAction(rep2);
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

    CCIntervalAction*  jump = CCJumpBy::actionWithDuration(2, CGPointMake(300,0), 50, 4);
    CCFiniteTimeAction*  action = CCSequence::actions( jump, jump->reverse(), NULL);

    m_grossini->runAction(action);
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

    CCIntervalAction*  move = CCMoveBy::actionWithDuration(1, CGPointMake(150,0));
    CCFiniteTimeAction*  action = CCSequence::actions( move, CCDelayTime::actionWithDuration(2), move, NULL);

    m_grossini->runAction(action);
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

    CCIntervalAction*  move1 = CCMoveBy::actionWithDuration(1, CGPointMake(250,0));
    CCIntervalAction*  move2 = CCMoveBy::actionWithDuration(1, CGPointMake(0,50));
    CCFiniteTimeAction*  seq = CCSequence::actions( move1, move2, move1->reverse(), NULL);
    CCFiniteTimeAction*  action = CCSequence::actions( seq, seq->reverse(), NULL);

    m_grossini->runAction(action);
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
    CCIntervalAction*  move1 = CCMoveBy::actionWithDuration(1, CGPointMake(250,0));
    CCIntervalAction*  move2 = CCMoveBy::actionWithDuration(1, CGPointMake(0,50));
    CCToggleVisibility*  tog1 = new CCToggleVisibility();
    CCToggleVisibility*  tog2 = new CCToggleVisibility();
    tog1->autorelease();
    tog2->autorelease();
    CCFiniteTimeAction*  seq = CCSequence::actions( move1, tog1, move2, tog2, move1->reverse(), NULL);
    CCIntervalAction*  action = CCRepeat::actionWithAction((CCIntervalAction*)(CCSequence::actions( seq, seq->reverse(), NULL)), 3);



    // Test:
    //   Also test that the reverse of Hide is Show, and vice-versa
    m_kathia->runAction(action);

    CCIntervalAction*  move_tamara = CCMoveBy::actionWithDuration(1, CGPointMake(100,0));
    CCIntervalAction*  move_tamara2 = CCMoveBy::actionWithDuration(1, CGPointMake(50,0));
    CCInstantAction*  hide = new CCHide();
    hide->autorelease();
    CCFiniteTimeAction*  seq_tamara = CCSequence::actions( move_tamara, hide, move_tamara2, NULL);
    CCFiniteTimeAction*  seq_back = seq_tamara->reverse();
    m_tamara->runAction( CCSequence::actions( seq_tamara, seq_back, NULL));
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


    CCIntervalAction*  a1 = CCMoveBy::actionWithDuration(1, CGPointMake(150,0));
    CCIntervalAction*  action1 = CCRepeat::actionWithAction(
        CCSequence::actions( CCPlace::actionWithPosition(CGPointMake(60,60)), a1, NULL) , 
        3); 
    CCAction*  action2 = CCRepeatForever::actionWithAction(
        (CCIntervalAction*)(CCSequence::actions((CCIntervalAction*)(a1->copy()->autorelease()), a1->reverse(), NULL))
        );

    m_kathia->runAction(action1);
    m_tamara->runAction(action2);
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

    CCIntervalAction*  orbit1 = CCOrbitCamera::actionWithDuration(2,1, 0, 0, 180, 0, 0);
    CCFiniteTimeAction*  action1 = CCSequence::actions(
        orbit1,
        orbit1->reverse(),
        NULL);

    CCIntervalAction*  orbit2 = CCOrbitCamera::actionWithDuration(2,1, 0, 0, 180, -45, 0);
    CCFiniteTimeAction*  action2 = CCSequence::actions(
        orbit2,
        orbit2->reverse(),
        NULL);

    CCIntervalAction*  orbit3 = CCOrbitCamera::actionWithDuration(2,1, 0, 0, 180, 90, 0);
    CCFiniteTimeAction*  action3 = CCSequence::actions(
        orbit3,
        orbit3->reverse(),
        NULL);

    m_kathia->runAction(CCRepeatForever::actionWithAction((CCIntervalAction*)action1));
    m_tamara->runAction(CCRepeatForever::actionWithAction((CCIntervalAction*)action2));
    m_grossini->runAction(CCRepeatForever::actionWithAction((CCIntervalAction*)action3));

    CCIntervalAction*  move = CCMoveBy::actionWithDuration(3, CGPointMake(100,-100));
    CCIntervalAction*  move_back = move->reverse();
    CCFiniteTimeAction*  seq = CCSequence::actions(move, move_back, NULL);
    CCAction*  rfe = CCRepeatForever::actionWithAction((CCIntervalAction*)seq);
    m_kathia->runAction(rfe);
    m_tamara->runAction((CCAction*)(rfe->copy()->autorelease()));
    m_grossini->runAction((CCAction*)(rfe->copy()->autorelease()));
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
    CGSize s = CCDirector::getSharedDirector()->getWinSize();

    m_grossini->setPosition(CGPointMake(-200, s.height / 2));
    CCIntervalAction* move      = CCMoveBy::actionWithDuration(2, CGPointMake(s.width * 3, 0));
    CCIntervalAction* move_back = move->reverse();
    CCFiniteTimeAction* seq       = CCSequence::actions(move, move_back, NULL);
    CCAction* rep               = CCRepeatForever::actionWithAction((CCIntervalAction*)seq);

    m_grossini->runAction(rep);

    this->runAction(CCFollow::actionWithTarget(m_grossini, CGRectMake(0, 0, s.width * 2 - 100, s.height)));
}

std::string ActionFollow::subtitle()
{
    return "Follow action";
}
