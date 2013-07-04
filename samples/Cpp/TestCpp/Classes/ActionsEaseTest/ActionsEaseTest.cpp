#include "ActionsEaseTest.h"
#include "../testResource.h"

enum {
    kTagAction1 = 1,
    kTagAction2 = 2,
    kTagSlider = 1,
};

Layer* nextEaseAction();
Layer* backEaseAction();
Layer* restartEaseAction();

//------------------------------------------------------------------
//
// SpriteEase
//
//------------------------------------------------------------------

void SpriteEase::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    ActionInterval* move = MoveBy::create(3, ccp(VisibleRect::right().x-130,0));
    ActionInterval* move_back = move->reverse();
    
    ActionInterval* move_ease_in = EaseIn::create(move->clone(), 2.5f);
    ActionInterval* move_ease_in_back = move_ease_in->reverse();
    
    ActionInterval* move_ease_out = EaseOut::create(move->clone(), 2.5f);
    ActionInterval* move_ease_out_back = move_ease_out->reverse();
    
    DelayTime *delay = DelayTime::create(0.25f);
    
    Sequence* seq1 = Sequence::create(move, delay, move_back, delay->clone(), NULL);
    Sequence* seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), NULL);
    Sequence* seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), NULL);
    
    
    Action *a2 = _grossini->runAction(RepeatForever::create(seq1));
    a2->setTag(1);

    Action *a1 = _tamara->runAction(RepeatForever::create(seq2));
    a1->setTag(1);

    Action *a = _kathia->runAction(RepeatForever::create(seq3));
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

    ActionInterval*  move = MoveBy::create(3, ccp(VisibleRect::right().x-130,0));
//    id move_back = move->reverse();
    
    ActionInterval*  move_ease_inout1 = EaseInOut::create(move->clone(), 0.65f);
    ActionInterval*  move_ease_inout_back1 = move_ease_inout1->reverse();
    
    ActionInterval*  move_ease_inout2 = EaseInOut::create(move->clone(), 1.35f);
    ActionInterval*  move_ease_inout_back2 = move_ease_inout2->reverse();

    ActionInterval*  move_ease_inout3 = EaseInOut::create(move->clone(), 1.0f);
    ActionInterval*  move_ease_inout_back3 = move_ease_inout3->reverse();
    
    DelayTime *delay = DelayTime::create(0.25f);

    Sequence*  seq1 = Sequence::create( move_ease_inout1, delay, move_ease_inout_back1, delay->clone(), NULL);
    Sequence*  seq2 = Sequence::create( move_ease_inout2, delay->clone(), move_ease_inout_back2, delay->clone(), NULL);
    Sequence*  seq3 = Sequence::create( move_ease_inout3, delay->clone(), move_ease_inout_back3, delay->clone(), NULL);
        
    _tamara->runAction(RepeatForever::create(seq1));
    _kathia->runAction(RepeatForever::create(seq2));
    _grossini->runAction(RepeatForever::create(seq3));
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
    
    ActionInterval* move = MoveBy::create(3, ccp(VisibleRect::right().x-130,0));
    ActionInterval* move_back = move->reverse();
    
    ActionInterval* move_ease_in = EaseExponentialIn::create(move->clone());
    ActionInterval* move_ease_in_back = move_ease_in->reverse();
    
    ActionInterval* move_ease_out = EaseExponentialOut::create(move->clone());
    ActionInterval* move_ease_out_back = move_ease_out->reverse();
    
    DelayTime *delay = DelayTime::create(0.25f);
    
    Sequence* seq1 = Sequence::create(move, delay, move_back, delay->clone(), NULL);
    Sequence* seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), NULL);
    Sequence* seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), NULL);
    

    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
    _kathia->runAction( RepeatForever::create(seq3));
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

    ActionInterval* move = MoveBy::create(3, ccp(VisibleRect::right().x-130, 0));
    ActionInterval* move_back = move->reverse();
    
    ActionInterval* move_ease = EaseExponentialInOut::create(move->clone() );
    ActionInterval* move_ease_back = move_ease->reverse();    //--> reverse()
    
    DelayTime *delay = DelayTime::create(0.25f);
    
    Sequence* seq1 = Sequence::create( move, delay, move_back, delay->clone(), NULL);
    Sequence* seq2 = Sequence::create( move_ease, delay, move_ease_back, delay->clone(), NULL);
    
    this->positionForTwo();
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));

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

    ActionInterval* move = MoveBy::create(3, ccp(VisibleRect::right().x-130, 0));
    ActionInterval* move_back = move->reverse();
    
    ActionInterval* move_ease_in = EaseSineIn::create(move->clone() );
    ActionInterval* move_ease_in_back = move_ease_in->reverse();
    
    ActionInterval* move_ease_out = EaseSineOut::create(move->clone() );
    ActionInterval* move_ease_out_back = move_ease_out->reverse();
    
    DelayTime *delay = DelayTime::create(0.25f);
        
    Sequence* seq1 = Sequence::create(move, delay, move_back, delay->clone(), NULL);
    Sequence* seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), NULL);
    Sequence* seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), NULL);
    
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
    _kathia->runAction( RepeatForever::create(seq3));    

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

    ActionInterval* move = MoveBy::create(3, ccp(VisibleRect::right().x-130,0));
    ActionInterval* move_back = move->reverse();
    
    ActionInterval* move_ease = EaseSineInOut::create(move->clone() );
    ActionInterval* move_ease_back = move_ease->reverse();
    
    DelayTime *delay = DelayTime::create(0.25f);
    
    Sequence* seq1 = Sequence::create(move, delay, move_back, delay->clone(), NULL);
    Sequence* seq2 = Sequence::create(move_ease, delay->clone(), move_ease_back, delay->clone(), NULL);

    this->positionForTwo();

    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
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
    
    ActionInterval* move = MoveBy::create(3, ccp(VisibleRect::right().x-130, 0));
    ActionInterval* move_back = move->reverse();
    
    ActionInterval* move_ease_in = EaseElasticIn::create(move->clone() );
    ActionInterval* move_ease_in_back = move_ease_in->reverse();
    
    ActionInterval* move_ease_out = EaseElasticOut::create(move->clone() );
    ActionInterval* move_ease_out_back = move_ease_out->reverse();
    
    DelayTime *delay = DelayTime::create(0.25f);

    Sequence* seq1 = Sequence::create(move, delay, move_back, delay->clone(), NULL);
    Sequence* seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), NULL);
    Sequence* seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), NULL);
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
    _kathia->runAction( RepeatForever::create(seq3));    
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
    
    ActionInterval* move = MoveBy::create(3, ccp(VisibleRect::right().x-130, 0));

    ActionInterval* move_ease_inout1 = EaseElasticInOut::create(move->clone(), 0.3f);
    ActionInterval* move_ease_inout_back1 = move_ease_inout1->reverse();
    
    ActionInterval* move_ease_inout2 = EaseElasticInOut::create(move->clone(), 0.45f);
    ActionInterval* move_ease_inout_back2 = move_ease_inout2->reverse();
    
    ActionInterval* move_ease_inout3 = EaseElasticInOut::create(move->clone(), 0.6f);
    ActionInterval* move_ease_inout_back3 = move_ease_inout3->reverse();
    
    DelayTime *delay = DelayTime::create(0.25f);
        
    Sequence* seq1 = Sequence::create(move_ease_inout1, delay, move_ease_inout_back1, delay->clone(), NULL);
    Sequence* seq2 = Sequence::create(move_ease_inout2, delay->clone(), move_ease_inout_back2, delay->clone(), NULL);
    Sequence* seq3 = Sequence::create(move_ease_inout3, delay->clone(), move_ease_inout_back3, delay->clone(), NULL);
    
    _tamara->runAction( RepeatForever::create(seq1));
    _kathia->runAction( RepeatForever::create(seq2));
    _grossini->runAction( RepeatForever::create(seq3)); 
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
    
    ActionInterval* move = MoveBy::create(3, ccp(VisibleRect::right().x-130, 0));
    ActionInterval* move_back = move->reverse();
    
    ActionInterval* move_ease_in = EaseBounceIn::create(move->clone() );
    ActionInterval* move_ease_in_back = move_ease_in->reverse();
    
    ActionInterval* move_ease_out = EaseBounceOut::create(move->clone() );
    ActionInterval* move_ease_out_back = move_ease_out->reverse();
    
    DelayTime *delay = DelayTime::create(0.25f);
    
    Sequence* seq1 = Sequence::create(move, delay, move_back, delay->clone(), NULL);
    Sequence* seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), NULL);
    Sequence* seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), NULL);
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
    _kathia->runAction( RepeatForever::create(seq3));    
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

    ActionInterval* move = MoveBy::create(3, ccp(VisibleRect::right().x-130, 0));
    ActionInterval* move_back = move->reverse();
    
    ActionInterval* move_ease = EaseBounceInOut::create(move->clone() );
    ActionInterval* move_ease_back = move_ease->reverse();
    
    DelayTime *delay = DelayTime::create(0.25f);
    
    Sequence* seq1 = Sequence::create(move, delay, move_back, delay->clone(), NULL);
    Sequence* seq2 = Sequence::create(move_ease, delay->clone(), move_ease_back, delay->clone(), NULL);
    
    this->positionForTwo();
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
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
    
    ActionInterval* move = MoveBy::create(3, ccp(VisibleRect::right().x-130, 0));
    ActionInterval* move_back = move->reverse();
    
    ActionInterval* move_ease_in = EaseBackIn::create(move->clone());
    ActionInterval* move_ease_in_back = move_ease_in->reverse();
    
    ActionInterval* move_ease_out = EaseBackOut::create( move->clone());
    ActionInterval* move_ease_out_back = move_ease_out->reverse();
    
    DelayTime *delay = DelayTime::create(0.25f);
    
    Sequence* seq1 = Sequence::create(move, delay, move_back, delay->clone(), NULL);
    Sequence* seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), NULL);
    Sequence* seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), NULL);
    
    _grossini->runAction(RepeatForever::create(seq1));
    _tamara->runAction(RepeatForever::create(seq2));
    _kathia->runAction(RepeatForever::create(seq3));    
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
    
    ActionInterval* move = MoveBy::create(3, ccp(VisibleRect::right().x-130, 0));
    ActionInterval* move_back = move->reverse();
    
    ActionInterval* move_ease = EaseBackInOut::create(move->clone() );
    ActionInterval* move_ease_back = move_ease->reverse();
    
    DelayTime *delay = DelayTime::create(0.25f);
    
    Sequence* seq1 = Sequence::create(move, delay, move_back, delay->clone(), NULL);
    Sequence* seq2 = Sequence::create(move_ease, delay->clone(), move_ease_back, delay->clone(), NULL);
    
    this->positionForTwo();
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));    
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
    
    Size s = Director::sharedDirector()->getWinSize();

    // rotate and jump
    ActionInterval *jump1 = JumpBy::create(4, ccp(-s.width+80, 0), 100, 4);
    ActionInterval *jump2 = jump1->reverse();
    ActionInterval *rot1 = RotateBy::create(4, 360*2);
    ActionInterval *rot2 = rot1->reverse();
    
    Sequence* seq3_1 = Sequence::create(jump2, jump1, NULL);
    Sequence* seq3_2 = Sequence::create( rot1, rot2, NULL);
    Spawn* spawn = Spawn::create(seq3_1, seq3_2, NULL);
    Speed* action = Speed::create(RepeatForever::create(spawn), 1.0f);
    action->setTag(kTagAction1);
    
    Action* action2 = action->clone();
    Action* action3 = action->clone();

    action2->setTag(kTagAction1);
    action3->setTag(kTagAction1);
    
    _grossini->runAction(action2);
    _tamara->runAction(action3);
    _kathia->runAction(action);
    
    this->schedule(schedule_selector(SpeedTest::altertime), 1.0f);//:@selector(altertime:) interval:1.0f];
}

void SpeedTest::altertime(float dt)
{    
    Speed* action1 = (Speed*)(_grossini->getActionByTag(kTagAction1));
    Speed* action2 = (Speed*)(_tamara->getActionByTag(kTagAction1));
    Speed* action3 = (Speed*)(_kathia->getActionByTag(kTagAction1));
    
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

Layer* createEaseLayer(int nIndex)
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

Layer* nextEaseAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    Layer* pLayer = createEaseLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

Layer* backEaseAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    Layer* pLayer = createEaseLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

Layer* restartEaseAction()
{
    Layer* pLayer = createEaseLayer(sceneIdx);
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
    _grossini = Sprite::create(s_pPathGrossini); _grossini->retain();
    _tamara = Sprite::create(s_pPathSister1); _tamara->retain();
    _kathia = Sprite::create(s_pPathSister2); _kathia->retain();
    
    addChild( _grossini, 3);
    addChild( _kathia, 2);
    addChild( _tamara, 1);

    _grossini->setPosition(ccp(VisibleRect::left().x + 60, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*1/5));
    _kathia->setPosition(ccp(VisibleRect::left().x + 60, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*2.5f/5));
    _tamara->setPosition(ccp(VisibleRect::left().x + 60, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*4/5));
}

void EaseSpriteDemo::restartCallback(Object* pSender)
{
    Scene* s = new ActionsEaseTestScene();//CCScene::create();
    s->addChild(restartEaseAction()); 

    Director::sharedDirector()->replaceScene(s);
    s->release();
}

void EaseSpriteDemo::nextCallback(Object* pSender)
{
    Scene* s = new ActionsEaseTestScene();//CCScene::create();
    s->addChild( nextEaseAction() );
    Director::sharedDirector()->replaceScene(s);
    s->release();
}

void EaseSpriteDemo::backCallback(Object* pSender)
{
    Scene* s = new ActionsEaseTestScene();//CCScene::create();
    s->addChild( backEaseAction() );
    Director::sharedDirector()->replaceScene(s);
    s->release();
}

void ActionsEaseTestScene::runThisTest()
{
    Layer* pLayer = nextEaseAction();
    addChild(pLayer);

    Director::sharedDirector()->replaceScene(this);
}
