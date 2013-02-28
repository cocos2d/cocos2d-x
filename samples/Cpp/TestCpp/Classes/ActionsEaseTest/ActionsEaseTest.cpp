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
#define CCCA(x)   (x->copy()->autorelease())
void SpriteEase::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    CCActionInterval* move = CCMoveBy::create(3, ccp(VisibleRect::right().x-130,0));
    CCActionInterval* move_back = move->reverse();
    
    CCActionInterval* move_ease_in = CCEaseIn::create((CCActionInterval*)(move->copy()->autorelease()), 2.5f);
    CCActionInterval* move_ease_in_back = move_ease_in->reverse();
    
    CCActionInterval* move_ease_out = CCEaseOut::create((CCActionInterval*)(move->copy()->autorelease()), 2.5f);
    CCActionInterval* move_ease_out_back = move_ease_out->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
    
    CCSequence* seq1 = CCSequence::create(move, delay, move_back, CCCA(delay), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease_in, CCCA(delay), move_ease_in_back, CCCA(delay), NULL);
    CCSequence* seq3 = CCSequence::create(move_ease_out, CCCA(delay), move_ease_out_back, CCCA(delay), NULL);
    
    
    CCAction *a2 = m_grossini->runAction(CCRepeatForever::create(seq1));
    a2->setTag(1);

    CCAction *a1 = m_tamara->runAction(CCRepeatForever::create(seq2));
    a1->setTag(1);

    CCAction *a = m_kathia->runAction(CCRepeatForever::create(seq3));
    a->setTag(1);

    schedule(schedule_selector(SpriteEase::testStopAction), 6.25f);
}

void SpriteEase::testStopAction(float dt)
{
    unschedule(schedule_selector(SpriteEase::testStopAction));
    m_tamara->stopActionByTag(1);
    m_kathia->stopActionByTag(1);
    m_grossini->stopActionByTag(1);
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
    
    CCActionInterval*  move_ease_inout1 = CCEaseInOut::create((CCActionInterval*)(move->copy()->autorelease()), 0.65f);
    CCActionInterval*  move_ease_inout_back1 = move_ease_inout1->reverse();
    
    CCActionInterval*  move_ease_inout2 = CCEaseInOut::create((CCActionInterval*)(move->copy()->autorelease()), 1.35f);
    CCActionInterval*  move_ease_inout_back2 = move_ease_inout2->reverse();

    CCActionInterval*  move_ease_inout3 = CCEaseInOut::create((CCActionInterval*)(move->copy()->autorelease()), 1.0f);
    CCActionInterval*  move_ease_inout_back3 = move_ease_inout3->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);

    CCSequence*  seq1 = CCSequence::create( move_ease_inout1, delay, move_ease_inout_back1, CCCA(delay), NULL);
    CCSequence*  seq2 = CCSequence::create( move_ease_inout2, CCCA(delay), move_ease_inout_back2, CCCA(delay), NULL);
    CCSequence*  seq3 = CCSequence::create( move_ease_inout3, CCCA(delay), move_ease_inout_back3, CCCA(delay), NULL);
        
    m_tamara->runAction(CCRepeatForever::create(seq1));
    m_kathia->runAction(CCRepeatForever::create(seq2));
    m_grossini->runAction(CCRepeatForever::create(seq3));
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
    
    CCActionInterval* move_ease_in = CCEaseExponentialIn::create((CCActionInterval*)(move->copy()->autorelease()) );
    CCActionInterval* move_ease_in_back = move_ease_in->reverse();
    
    CCActionInterval* move_ease_out = CCEaseExponentialOut::create((CCActionInterval*)(move->copy()->autorelease()) );
    CCActionInterval* move_ease_out_back = move_ease_out->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
    
    CCSequence* seq1 = CCSequence::create(move, delay, move_back, CCCA(delay), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease_in, CCCA(delay), move_ease_in_back, CCCA(delay), NULL);
    CCSequence* seq3 = CCSequence::create(move_ease_out, CCCA(delay), move_ease_out_back, CCCA(delay), NULL);
    

    m_grossini->runAction( CCRepeatForever::create(seq1));
    m_tamara->runAction( CCRepeatForever::create(seq2));
    m_kathia->runAction( CCRepeatForever::create(seq3));
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
    
    CCActionInterval* move_ease = CCEaseExponentialInOut::create((CCActionInterval*)(move->copy()->autorelease()) );
    CCActionInterval* move_ease_back = move_ease->reverse();    //--> reverse()
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
    
    CCSequence* seq1 = CCSequence::create( move, delay, move_back, CCCA(delay), NULL);
    CCSequence* seq2 = CCSequence::create( move_ease, delay, move_ease_back, CCCA(delay), NULL);
    
    this->positionForTwo();
    
    m_grossini->runAction( CCRepeatForever::create(seq1));
    m_tamara->runAction( CCRepeatForever::create(seq2));

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
    
    CCActionInterval* move_ease_in = CCEaseSineIn::create((CCActionInterval*)(move->copy()->autorelease()) );
    CCActionInterval* move_ease_in_back = move_ease_in->reverse();
    
    CCActionInterval* move_ease_out = CCEaseSineOut::create((CCActionInterval*)(move->copy()->autorelease()) );
    CCActionInterval* move_ease_out_back = move_ease_out->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
        
    CCSequence* seq1 = CCSequence::create(move, delay, move_back, CCCA(delay), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease_in, CCCA(delay), move_ease_in_back, CCCA(delay), NULL);
    CCSequence* seq3 = CCSequence::create(move_ease_out, CCCA(delay), move_ease_out_back, CCCA(delay), NULL);
    
    
    m_grossini->runAction( CCRepeatForever::create(seq1));
    m_tamara->runAction( CCRepeatForever::create(seq2));
    m_kathia->runAction( CCRepeatForever::create(seq3));    

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
    
    CCActionInterval* move_ease = CCEaseSineInOut::create((CCActionInterval*)(move->copy()->autorelease()) );
    CCActionInterval* move_ease_back = move_ease->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
    
    CCSequence* seq1 = CCSequence::create(move, delay, move_back, CCCA(delay), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease, CCCA(delay), move_ease_back, CCCA(delay), NULL);

    this->positionForTwo();

    m_grossini->runAction( CCRepeatForever::create(seq1));
    m_tamara->runAction( CCRepeatForever::create(seq2));
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
    
    CCActionInterval* move_ease_in = CCEaseElasticIn::create((CCActionInterval*)(move->copy()->autorelease()) );
    CCActionInterval* move_ease_in_back = move_ease_in->reverse();
    
    CCActionInterval* move_ease_out = CCEaseElasticOut::create((CCActionInterval*)(move->copy()->autorelease()) );
    CCActionInterval* move_ease_out_back = move_ease_out->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);

    CCSequence* seq1 = CCSequence::create(move, delay, move_back, CCCA(delay), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease_in, CCCA(delay), move_ease_in_back, CCCA(delay), NULL);
    CCSequence* seq3 = CCSequence::create(move_ease_out, CCCA(delay), move_ease_out_back, CCCA(delay), NULL);
    
    m_grossini->runAction( CCRepeatForever::create(seq1));
    m_tamara->runAction( CCRepeatForever::create(seq2));
    m_kathia->runAction( CCRepeatForever::create(seq3));    
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

    CCActionInterval* move_ease_inout1 = CCEaseElasticInOut::create((CCActionInterval*)(move->copy()->autorelease()), 0.3f);
    CCActionInterval* move_ease_inout_back1 = move_ease_inout1->reverse();
    
    CCActionInterval* move_ease_inout2 = CCEaseElasticInOut::create((CCActionInterval*)(move->copy()->autorelease()), 0.45f);
    CCActionInterval* move_ease_inout_back2 = move_ease_inout2->reverse();
    
    CCActionInterval* move_ease_inout3 = CCEaseElasticInOut::create((CCActionInterval*)(move->copy()->autorelease()), 0.6f);
    CCActionInterval* move_ease_inout_back3 = move_ease_inout3->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
        
    CCSequence* seq1 = CCSequence::create(move_ease_inout1, delay, move_ease_inout_back1, CCCA(delay), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease_inout2, CCCA(delay), move_ease_inout_back2, CCCA(delay), NULL);
    CCSequence* seq3 = CCSequence::create(move_ease_inout3, CCCA(delay), move_ease_inout_back3, CCCA(delay), NULL);
    
    m_tamara->runAction( CCRepeatForever::create(seq1));
    m_kathia->runAction( CCRepeatForever::create(seq2));
    m_grossini->runAction( CCRepeatForever::create(seq3)); 
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
    
    CCActionInterval* move_ease_in = CCEaseBounceIn::create((CCActionInterval*)(move->copy()->autorelease()) );
    CCActionInterval* move_ease_in_back = move_ease_in->reverse();
    
    CCActionInterval* move_ease_out = CCEaseBounceOut::create((CCActionInterval*)(move->copy()->autorelease()) );
    CCActionInterval* move_ease_out_back = move_ease_out->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
    
    CCSequence* seq1 = CCSequence::create(move, delay, move_back, CCCA(delay), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease_in, CCCA(delay), move_ease_in_back, CCCA(delay), NULL);
    CCSequence* seq3 = CCSequence::create(move_ease_out, CCCA(delay), move_ease_out_back, CCCA(delay), NULL);
    
    m_grossini->runAction( CCRepeatForever::create(seq1));
    m_tamara->runAction( CCRepeatForever::create(seq2));
    m_kathia->runAction( CCRepeatForever::create(seq3));    
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
    
    CCActionInterval* move_ease = CCEaseBounceInOut::create((CCActionInterval*)(move->copy()->autorelease()) );
    CCActionInterval* move_ease_back = move_ease->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
    
    CCSequence* seq1 = CCSequence::create(move, delay, move_back, CCCA(delay), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease, CCCA(delay), move_ease_back, CCCA(delay), NULL);
    
    this->positionForTwo();
    
    m_grossini->runAction( CCRepeatForever::create(seq1));
    m_tamara->runAction( CCRepeatForever::create(seq2));
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
    
    CCActionInterval* move_ease_in = CCEaseBackIn::create((CCActionInterval*)(move->copy()->autorelease()));
    CCActionInterval* move_ease_in_back = move_ease_in->reverse();
    
    CCActionInterval* move_ease_out = CCEaseBackOut::create((CCActionInterval*)(move->copy()->autorelease()));
    CCActionInterval* move_ease_out_back = move_ease_out->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
    
    CCSequence* seq1 = CCSequence::create(move, delay, move_back, CCCA(delay), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease_in, CCCA(delay), move_ease_in_back, CCCA(delay), NULL);
    CCSequence* seq3 = CCSequence::create(move_ease_out, CCCA(delay), move_ease_out_back, CCCA(delay), NULL);
    
    m_grossini->runAction(CCRepeatForever::create(seq1));
    m_tamara->runAction(CCRepeatForever::create(seq2));
    m_kathia->runAction(CCRepeatForever::create(seq3));    
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
    
    CCActionInterval* move_ease = CCEaseBackInOut::create((CCActionInterval*)(move->copy()->autorelease()) );
    CCActionInterval* move_ease_back = move_ease->reverse();
    
    CCDelayTime *delay = CCDelayTime::create(0.25f);
    
    CCSequence* seq1 = CCSequence::create(move, delay, move_back, CCCA(delay), NULL);
    CCSequence* seq2 = CCSequence::create(move_ease, CCCA(delay), move_ease_back, CCCA(delay), NULL);
    
    this->positionForTwo();
    
    m_grossini->runAction( CCRepeatForever::create(seq1));
    m_tamara->runAction( CCRepeatForever::create(seq2));    
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
    
    CCAction* action2 = (CCAction*)(action->copy()->autorelease());
    CCAction* action3 = (CCAction*)(action->copy()->autorelease());

    action2->setTag(kTagAction1);
    action3->setTag(kTagAction1);
    
    m_grossini->runAction(action2);
    m_tamara->runAction(action3);
    m_kathia->runAction(action);
    
    this->schedule(schedule_selector(SpeedTest::altertime), 1.0f);//:@selector(altertime:) interval:1.0f];
}

void SpeedTest::altertime(float dt)
{    
    CCSpeed* action1 = (CCSpeed*)(m_grossini->getActionByTag(kTagAction1));
    CCSpeed* action2 = (CCSpeed*)(m_tamara->getActionByTag(kTagAction1));
    CCSpeed* action3 = (CCSpeed*)(m_kathia->getActionByTag(kTagAction1));
    
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
    m_grossini->release();
    m_tamara->release();
    m_kathia->release();
}

void EaseSpriteDemo::positionForTwo()
{    
    m_grossini->setPosition(ccp(VisibleRect::left().x+60, VisibleRect::bottom().y + VisibleRect::getVisibleRect().size.height*1/5));
    m_tamara->setPosition(ccp( VisibleRect::left().x+60, VisibleRect::bottom().y + VisibleRect::getVisibleRect().size.height*4/5));
    m_kathia->setVisible(false);
}


std::string EaseSpriteDemo::title()
{
    return "No title";
}

void EaseSpriteDemo::onEnter()
{
    CCLayer::onEnter();

    // Or you can create an sprite using a filename. PNG and BMP files are supported. Probably TIFF too
    m_grossini = CCSprite::create(s_pPathGrossini); m_grossini->retain();
    m_tamara = CCSprite::create(s_pPathSister1); m_tamara->retain();
    m_kathia = CCSprite::create(s_pPathSister2); m_kathia->retain();
    
    addChild( m_grossini, 3);
    addChild( m_kathia, 2);
    addChild( m_tamara, 1);

    m_grossini->setPosition(ccp(VisibleRect::left().x + 60, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*1/5));
    m_kathia->setPosition(ccp(VisibleRect::left().x + 60, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*2.5f/5));
    m_tamara->setPosition(ccp(VisibleRect::left().x + 60, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*4/5));

    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label);
    label->setPosition(ccp(VisibleRect::center().x, VisibleRect::top().y-50));

    CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(EaseSpriteDemo::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(EaseSpriteDemo::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(EaseSpriteDemo::nextCallback) );

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

    menu->setPosition(CCPointZero);
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y + item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y + item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y + item2->getContentSize().height/2));
    
    addChild(menu, 1);    
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
