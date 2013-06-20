#include "ActionsEaseTest.h"
#include "../testResource.h"

enum {
    kTagAction1 = 1,
    kTagAction2 = 2,
    kTagSlider = 1,
};

CCLayer* nextEaseAction();
CCLayer* backEaseAction();
CCLayer* restartEaseAction();

//------------------------------------------------------------------
//
// SpriteEase
//
//------------------------------------------------------------------

void SpriteEase::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    CCActionInterval* move = CCMoveBy::create(3, ccp(VisibleRect::right().x-130,0));
    CCActionInterval* move_back = move->reverse();
    
    CCActionInterval* move_ease_in = CCEaseIn::create(move->clone(), 2.5f);
    CCActionInterval* move_ease_in_back = move_ease_in->reverse();
    
    CCActionInterval* move_ease_out = CCEaseOut::create(move->clone(), 2.5f);
    CCActionInterval* move_ease_out_back = move_ease_out->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
    
    CCSequence* seq1 = CCSequence::create(move, delay, move_back, delay->clone(), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), NULL);
    CCSequence* seq3 = CCSequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), NULL);
    
    
    CCAction *a2 = _grossini->runAction(CCRepeatForever::create(seq1));
    a2->setTag(1);

    CCAction *a1 = _tamara->runAction(CCRepeatForever::create(seq2));
    a1->setTag(1);

    CCAction *a = _kathia->runAction(CCRepeatForever::create(seq3));
    a->setTag(1);

    schedule(schedule_selector(SpriteEase::testStopAction), 6.25f);
}

void SpriteEase::testStopAction(float dt)
{
    unschedule(schedule_selector(SpriteEase::testStopAction));
    _tamara->stopActionByTag(1);
    _kathia->stopActionByTag(1);
    _grossini->stopActionByTag(1);
}

std::string SpriteEase::title()
{
    return "EaseIn - EaseOut - Stop";
}


//------------------------------------------------------------------
//
// SpriteEaseInOut
//
//------------------------------------------------------------------

void SpriteEaseInOut::onEnter()
{
    EaseSpriteDemo::onEnter();

    CCActionInterval*  move = CCMoveBy::create(3, ccp(VisibleRect::right().x-130,0));
//    id move_back = move->reverse();
    
    CCActionInterval*  move_ease_inout1 = CCEaseInOut::create(move->clone(), 0.65f);
    CCActionInterval*  move_ease_inout_back1 = move_ease_inout1->reverse();
    
    CCActionInterval*  move_ease_inout2 = CCEaseInOut::create(move->clone(), 1.35f);
    CCActionInterval*  move_ease_inout_back2 = move_ease_inout2->reverse();

    CCActionInterval*  move_ease_inout3 = CCEaseInOut::create(move->clone(), 1.0f);
    CCActionInterval*  move_ease_inout_back3 = move_ease_inout3->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);

    CCSequence*  seq1 = CCSequence::create( move_ease_inout1, delay, move_ease_inout_back1, delay->clone(), NULL);
    CCSequence*  seq2 = CCSequence::create( move_ease_inout2, delay->clone(), move_ease_inout_back2, delay->clone(), NULL);
    CCSequence*  seq3 = CCSequence::create( move_ease_inout3, delay->clone(), move_ease_inout_back3, delay->clone(), NULL);
        
    _tamara->runAction(CCRepeatForever::create(seq1));
    _kathia->runAction(CCRepeatForever::create(seq2));
    _grossini->runAction(CCRepeatForever::create(seq3));
}


std::string SpriteEaseInOut::title()
{
    return "EaseInOut and rates";
}

//------------------------------------------------------------------
//
// SpriteEaseExponential
//
//------------------------------------------------------------------

void SpriteEaseExponential::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    CCActionInterval* move = CCMoveBy::create(3, ccp(VisibleRect::right().x-130,0));
    CCActionInterval* move_back = move->reverse();
    
    CCActionInterval* move_ease_in = CCEaseExponentialIn::create(move->clone());
    CCActionInterval* move_ease_in_back = move_ease_in->reverse();
    
    CCActionInterval* move_ease_out = CCEaseExponentialOut::create(move->clone());
    CCActionInterval* move_ease_out_back = move_ease_out->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
    
    CCSequence* seq1 = CCSequence::create(move, delay, move_back, delay->clone(), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), NULL);
    CCSequence* seq3 = CCSequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), NULL);
    

    _grossini->runAction( CCRepeatForever::create(seq1));
    _tamara->runAction( CCRepeatForever::create(seq2));
    _kathia->runAction( CCRepeatForever::create(seq3));
}


std::string SpriteEaseExponential::title()
{
    return "ExpIn - ExpOut actions";
}
//------------------------------------------------------------------
//
// SpriteEaseExponentialInOut
//
//------------------------------------------------------------------

void SpriteEaseExponentialInOut::onEnter()
{
    EaseSpriteDemo::onEnter();

    CCActionInterval* move = CCMoveBy::create(3, ccp(VisibleRect::right().x-130, 0));
    CCActionInterval* move_back = move->reverse();
    
    CCActionInterval* move_ease = CCEaseExponentialInOut::create(move->clone() );
    CCActionInterval* move_ease_back = move_ease->reverse();    //--> reverse()
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
    
    CCSequence* seq1 = CCSequence::create( move, delay, move_back, delay->clone(), NULL);
    CCSequence* seq2 = CCSequence::create( move_ease, delay, move_ease_back, delay->clone(), NULL);
    
    this->positionForTwo();
    
    _grossini->runAction( CCRepeatForever::create(seq1));
    _tamara->runAction( CCRepeatForever::create(seq2));

}


std::string SpriteEaseExponentialInOut::title()
{
    return "EaseExponentialInOut action";
}
//------------------------------------------------------------------
//
// SpriteEaseSine
//
//------------------------------------------------------------------

void SpriteEaseSine::onEnter()
{
    EaseSpriteDemo::onEnter();

    CCActionInterval* move = CCMoveBy::create(3, ccp(VisibleRect::right().x-130, 0));
    CCActionInterval* move_back = move->reverse();
    
    CCActionInterval* move_ease_in = CCEaseSineIn::create(move->clone() );
    CCActionInterval* move_ease_in_back = move_ease_in->reverse();
    
    CCActionInterval* move_ease_out = CCEaseSineOut::create(move->clone() );
    CCActionInterval* move_ease_out_back = move_ease_out->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
        
    CCSequence* seq1 = CCSequence::create(move, delay, move_back, delay->clone(), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), NULL);
    CCSequence* seq3 = CCSequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), NULL);
    
    
    _grossini->runAction( CCRepeatForever::create(seq1));
    _tamara->runAction( CCRepeatForever::create(seq2));
    _kathia->runAction( CCRepeatForever::create(seq3));    

}


std::string SpriteEaseSine::title()
{
    return "EaseSineIn - EaseSineOut";
}
//------------------------------------------------------------------
//
// SpriteEaseSineInOut
//
//------------------------------------------------------------------

void SpriteEaseSineInOut::onEnter()
{
    EaseSpriteDemo::onEnter();

    CCActionInterval* move = CCMoveBy::create(3, ccp(VisibleRect::right().x-130,0));
    CCActionInterval* move_back = move->reverse();
    
    CCActionInterval* move_ease = CCEaseSineInOut::create(move->clone() );
    CCActionInterval* move_ease_back = move_ease->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
    
    CCSequence* seq1 = CCSequence::create(move, delay, move_back, delay->clone(), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease, delay->clone(), move_ease_back, delay->clone(), NULL);

    this->positionForTwo();

    _grossini->runAction( CCRepeatForever::create(seq1));
    _tamara->runAction( CCRepeatForever::create(seq2));
}


std::string SpriteEaseSineInOut::title()
{
    return "EaseSineInOut action";
}
//------------------------------------------------------------------
//
// SpriteEaseElastic
//
//------------------------------------------------------------------

void SpriteEaseElastic::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    CCActionInterval* move = CCMoveBy::create(3, ccp(VisibleRect::right().x-130, 0));
    CCActionInterval* move_back = move->reverse();
    
    CCActionInterval* move_ease_in = CCEaseElasticIn::create(move->clone() );
    CCActionInterval* move_ease_in_back = move_ease_in->reverse();
    
    CCActionInterval* move_ease_out = CCEaseElasticOut::create(move->clone() );
    CCActionInterval* move_ease_out_back = move_ease_out->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);

    CCSequence* seq1 = CCSequence::create(move, delay, move_back, delay->clone(), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), NULL);
    CCSequence* seq3 = CCSequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), NULL);
    
    _grossini->runAction( CCRepeatForever::create(seq1));
    _tamara->runAction( CCRepeatForever::create(seq2));
    _kathia->runAction( CCRepeatForever::create(seq3));    
}


std::string SpriteEaseElastic::title()
{
    return "Elastic In - Out actions";
}

//------------------------------------------------------------------
//
// SpriteEaseElasticInOut
//
//------------------------------------------------------------------

void SpriteEaseElasticInOut::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    CCActionInterval* move = CCMoveBy::create(3, ccp(VisibleRect::right().x-130, 0));

    CCActionInterval* move_ease_inout1 = CCEaseElasticInOut::create(move->clone(), 0.3f);
    CCActionInterval* move_ease_inout_back1 = move_ease_inout1->reverse();
    
    CCActionInterval* move_ease_inout2 = CCEaseElasticInOut::create(move->clone(), 0.45f);
    CCActionInterval* move_ease_inout_back2 = move_ease_inout2->reverse();
    
    CCActionInterval* move_ease_inout3 = CCEaseElasticInOut::create(move->clone(), 0.6f);
    CCActionInterval* move_ease_inout_back3 = move_ease_inout3->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
        
    CCSequence* seq1 = CCSequence::create(move_ease_inout1, delay, move_ease_inout_back1, delay->clone(), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease_inout2, delay->clone(), move_ease_inout_back2, delay->clone(), NULL);
    CCSequence* seq3 = CCSequence::create(move_ease_inout3, delay->clone(), move_ease_inout_back3, delay->clone(), NULL);
    
    _tamara->runAction( CCRepeatForever::create(seq1));
    _kathia->runAction( CCRepeatForever::create(seq2));
    _grossini->runAction( CCRepeatForever::create(seq3)); 
}


std::string SpriteEaseElasticInOut::title()
{
    return "EaseElasticInOut action";
}


//------------------------------------------------------------------
//
// SpriteEaseBounce
//
//------------------------------------------------------------------

void SpriteEaseBounce::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    CCActionInterval* move = CCMoveBy::create(3, ccp(VisibleRect::right().x-130, 0));
    CCActionInterval* move_back = move->reverse();
    
    CCActionInterval* move_ease_in = CCEaseBounceIn::create(move->clone() );
    CCActionInterval* move_ease_in_back = move_ease_in->reverse();
    
    CCActionInterval* move_ease_out = CCEaseBounceOut::create(move->clone() );
    CCActionInterval* move_ease_out_back = move_ease_out->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
    
    CCSequence* seq1 = CCSequence::create(move, delay, move_back, delay->clone(), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), NULL);
    CCSequence* seq3 = CCSequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), NULL);
    
    _grossini->runAction( CCRepeatForever::create(seq1));
    _tamara->runAction( CCRepeatForever::create(seq2));
    _kathia->runAction( CCRepeatForever::create(seq3));    
}


std::string SpriteEaseBounce::title()
{
    return "Bounce In - Out actions";
}


//------------------------------------------------------------------
//
// SpriteEaseBounceInOut
//
//------------------------------------------------------------------

void SpriteEaseBounceInOut::onEnter()
{
    EaseSpriteDemo::onEnter();

    CCActionInterval* move = CCMoveBy::create(3, ccp(VisibleRect::right().x-130, 0));
    CCActionInterval* move_back = move->reverse();
    
    CCActionInterval* move_ease = CCEaseBounceInOut::create(move->clone() );
    CCActionInterval* move_ease_back = move_ease->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
    
    CCSequence* seq1 = CCSequence::create(move, delay, move_back, delay->clone(), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease, delay->clone(), move_ease_back, delay->clone(), NULL);
    
    this->positionForTwo();
    
    _grossini->runAction( CCRepeatForever::create(seq1));
    _tamara->runAction( CCRepeatForever::create(seq2));
}


std::string SpriteEaseBounceInOut::title()
{
    return "EaseBounceInOut action";
}

//------------------------------------------------------------------
//
// SpriteEaseBack
//
//------------------------------------------------------------------

void SpriteEaseBack::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    CCActionInterval* move = CCMoveBy::create(3, ccp(VisibleRect::right().x-130, 0));
    CCActionInterval* move_back = move->reverse();
    
    CCActionInterval* move_ease_in = CCEaseBackIn::create(move->clone());
    CCActionInterval* move_ease_in_back = move_ease_in->reverse();
    
    CCActionInterval* move_ease_out = CCEaseBackOut::create( move->clone());
    CCActionInterval* move_ease_out_back = move_ease_out->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
    
    CCSequence* seq1 = CCSequence::create(move, delay, move_back, delay->clone(), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), NULL);
    CCSequence* seq3 = CCSequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), NULL);
    
    _grossini->runAction(CCRepeatForever::create(seq1));
    _tamara->runAction(CCRepeatForever::create(seq2));
    _kathia->runAction(CCRepeatForever::create(seq3));    
}


std::string SpriteEaseBack::title()
{
    return "Back In - Out actions";
}

//------------------------------------------------------------------
//
// SpriteEaseBackInOut
//
//------------------------------------------------------------------

void SpriteEaseBackInOut::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    CCActionInterval* move = CCMoveBy::create(3, ccp(VisibleRect::right().x-130, 0));
    CCActionInterval* move_back = move->reverse();
    
    CCActionInterval* move_ease = CCEaseBackInOut::create(move->clone() );
    CCActionInterval* move_ease_back = move_ease->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
    
    CCSequence* seq1 = CCSequence::create(move, delay, move_back, delay->clone(), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease, delay->clone(), move_ease_back, delay->clone(), NULL);
    
    this->positionForTwo();
    
    _grossini->runAction( CCRepeatForever::create(seq1));
    _tamara->runAction( CCRepeatForever::create(seq2));    
}


std::string SpriteEaseBackInOut::title()
{
    return "EaseBackInOut action";
}

//------------------------------------------------------------------
//
// SpeedTest
//
//------------------------------------------------------------------

void SpeedTest::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // rotate and jump
    CCActionInterval *jump1 = CCJumpBy::create(4, ccp(-s.width+80, 0), 100, 4);
    CCActionInterval *jump2 = jump1->reverse();
    CCActionInterval *rot1 = CCRotateBy::create(4, 360*2);
    CCActionInterval *rot2 = rot1->reverse();
    
    CCSequence* seq3_1 = CCSequence::create(jump2, jump1, NULL);
    CCSequence* seq3_2 = CCSequence::create( rot1, rot2, NULL);
    CCSpawn* spawn = CCSpawn::create(seq3_1, seq3_2, NULL);
    CCSpeed* action = CCSpeed::create(CCRepeatForever::create(spawn), 1.0f);
    action->setTag(kTagAction1);
    
    CCAction* action2 = action->clone();
    CCAction* action3 = action->clone();

    action2->setTag(kTagAction1);
    action3->setTag(kTagAction1);
    
    _grossini->runAction(action2);
    _tamara->runAction(action3);
    _kathia->runAction(action);
    
    this->schedule(schedule_selector(SpeedTest::altertime), 1.0f);//:@selector(altertime:) interval:1.0f];
}

void SpeedTest::altertime(float dt)
{    
    CCSpeed* action1 = (CCSpeed*)(_grossini->getActionByTag(kTagAction1));
    CCSpeed* action2 = (CCSpeed*)(_tamara->getActionByTag(kTagAction1));
    CCSpeed* action3 = (CCSpeed*)(_kathia->getActionByTag(kTagAction1));
    
    action1->setSpeed( CCRANDOM_MINUS1_1() * 2 );
    action2->setSpeed( CCRANDOM_MINUS1_1() * 2 );
    action3->setSpeed( CCRANDOM_MINUS1_1() * 2 );
}

std::string SpeedTest::title()
{
    return "Speed action";
}

//------------------------------------------------------------------
//
// EaseSpriteDemo
//
//------------------------------------------------------------------

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

static int sceneIdx = -1; 

#define MAX_LAYER    13

CCLayer* createEaseLayer(int nIndex)
{
    switch(nIndex)
    {
        case 0: return new SpriteEase();
        case 1: return new SpriteEaseInOut();
        case 2: return new SpriteEaseExponential();
        case 3: return new SpriteEaseExponentialInOut();
        case 4: return new SpriteEaseSine();
        case 5: return new SpriteEaseSineInOut();
        case 6: return new SpriteEaseElastic();
        case 7: return new SpriteEaseElasticInOut();
        case 8: return new SpriteEaseBounce();
        case 9: return new SpriteEaseBounceInOut();
        case 10: return new SpriteEaseBack();
        case 11: return new SpriteEaseBackInOut();
        case 12: return new SpeedTest();
    }


    return NULL;
}

CCLayer* nextEaseAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    CCLayer* pLayer = createEaseLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* backEaseAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    CCLayer* pLayer = createEaseLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* restartEaseAction()
{
    CCLayer* pLayer = createEaseLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
} 


EaseSpriteDemo::EaseSpriteDemo(void)
{
}

EaseSpriteDemo::~EaseSpriteDemo(void)
{
    _grossini->release();
    _tamara->release();
    _kathia->release();
}

void EaseSpriteDemo::positionForTwo()
{    
    _grossini->setPosition(ccp(VisibleRect::left().x+60, VisibleRect::bottom().y + VisibleRect::getVisibleRect().size.height*1/5));
    _tamara->setPosition(ccp( VisibleRect::left().x+60, VisibleRect::bottom().y + VisibleRect::getVisibleRect().size.height*4/5));
    _kathia->setVisible(false);
}


std::string EaseSpriteDemo::title()
{
    return "No title";
}

void EaseSpriteDemo::onEnter()
{
    BaseTest::onEnter();

    // Or you can create an sprite using a filename. PNG and BMP files are supported. Probably TIFF too
    _grossini = CCSprite::create(s_pPathGrossini); _grossini->retain();
    _tamara = CCSprite::create(s_pPathSister1); _tamara->retain();
    _kathia = CCSprite::create(s_pPathSister2); _kathia->retain();
    
    addChild( _grossini, 3);
    addChild( _kathia, 2);
    addChild( _tamara, 1);

    _grossini->setPosition(ccp(VisibleRect::left().x + 60, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*1/5));
    _kathia->setPosition(ccp(VisibleRect::left().x + 60, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*2.5f/5));
    _tamara->setPosition(ccp(VisibleRect::left().x + 60, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*4/5));
}

void EaseSpriteDemo::restartCallback(CCObject* pSender)
{
    CCScene* s = new ActionsEaseTestScene();//CCScene::create();
    s->addChild(restartEaseAction()); 

    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void EaseSpriteDemo::nextCallback(CCObject* pSender)
{
    CCScene* s = new ActionsEaseTestScene();//CCScene::create();
    s->addChild( nextEaseAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void EaseSpriteDemo::backCallback(CCObject* pSender)
{
    CCScene* s = new ActionsEaseTestScene();//CCScene::create();
    s->addChild( backEaseAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void ActionsEaseTestScene::runThisTest()
{
    CCLayer* pLayer = nextEaseAction();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}
