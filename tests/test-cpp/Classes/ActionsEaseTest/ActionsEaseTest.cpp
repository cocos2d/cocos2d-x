/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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
    
    auto move = MoveBy::create(3, Point(VisibleRect::right().x-130,0));
    auto move_back = move->reverse();
    
    auto move_ease_in = EaseIn::create(move->clone(), 2.5f);
    auto move_ease_in_back = move_ease_in->reverse();
    
    auto move_ease_out = EaseOut::create(move->clone(), 2.5f);
    auto move_ease_out_back = move_ease_out->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), NULL);
    auto seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), NULL);
    auto seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), NULL);
    
    
    auto a2 = _grossini->runAction(RepeatForever::create(seq1));
    a2->setTag(1);

    auto a1 = _tamara->runAction(RepeatForever::create(seq2));
    a1->setTag(1);

    auto a = _kathia->runAction(RepeatForever::create(seq3));
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

std::string SpriteEase::title() const
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

    auto move = MoveBy::create(3, Point(VisibleRect::right().x-130,0));
//    id move_back = move->reverse();
    
    auto move_ease_inout1 = EaseInOut::create(move->clone(), 0.65f);
    auto move_ease_inout_back1 = move_ease_inout1->reverse();
    
    auto move_ease_inout2 = EaseInOut::create(move->clone(), 1.35f);
    auto move_ease_inout_back2 = move_ease_inout2->reverse();

    auto move_ease_inout3 = EaseInOut::create(move->clone(), 1.0f);
    auto move_ease_inout_back3 = move_ease_inout3->reverse();
    
    auto delay = DelayTime::create(0.25f);

    auto seq1 = Sequence::create( move_ease_inout1, delay, move_ease_inout_back1, delay->clone(), NULL);
    auto seq2 = Sequence::create( move_ease_inout2, delay->clone(), move_ease_inout_back2, delay->clone(), NULL);
    auto seq3 = Sequence::create( move_ease_inout3, delay->clone(), move_ease_inout_back3, delay->clone(), NULL);
        
    _tamara->runAction(RepeatForever::create(seq1));
    _kathia->runAction(RepeatForever::create(seq2));
    _grossini->runAction(RepeatForever::create(seq3));
}


std::string SpriteEaseInOut::title() const
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
    
    auto move = MoveBy::create(3, Point(VisibleRect::right().x-130,0));
    auto move_back = move->reverse();
    
    auto move_ease_in = EaseExponentialIn::create(move->clone());
    auto move_ease_in_back = move_ease_in->reverse();
    
    auto move_ease_out = EaseExponentialOut::create(move->clone());
    auto move_ease_out_back = move_ease_out->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), NULL);
    auto seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), NULL);
    auto seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), NULL);
    

    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
    _kathia->runAction( RepeatForever::create(seq3));
}


std::string SpriteEaseExponential::title() const
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

    auto move = MoveBy::create(3, Point(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease = EaseExponentialInOut::create(move->clone() );
    auto move_ease_back = move_ease->reverse();    //--> reverse()
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create( move, delay, move_back, delay->clone(), NULL);
    auto seq2 = Sequence::create( move_ease, delay, move_ease_back, delay->clone(), NULL);
    
    this->positionForTwo();
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));

}


std::string SpriteEaseExponentialInOut::title() const
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

    auto move = MoveBy::create(3, Point(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease_in = EaseSineIn::create(move->clone() );
    auto move_ease_in_back = move_ease_in->reverse();
    
    auto move_ease_out = EaseSineOut::create(move->clone() );
    auto move_ease_out_back = move_ease_out->reverse();
    
    auto delay = DelayTime::create(0.25f);
        
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), NULL);
    auto seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), NULL);
    auto seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), NULL);
    
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
    _kathia->runAction( RepeatForever::create(seq3));    

}


std::string SpriteEaseSine::title() const
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

    auto move = MoveBy::create(3, Point(VisibleRect::right().x-130,0));
    auto move_back = move->reverse();
    
    auto move_ease = EaseSineInOut::create(move->clone() );
    auto move_ease_back = move_ease->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), NULL);
    auto seq2 = Sequence::create(move_ease, delay->clone(), move_ease_back, delay->clone(), NULL);

    this->positionForTwo();

    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
}


std::string SpriteEaseSineInOut::title() const
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
    
    auto move = MoveBy::create(3, Point(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease_in = EaseElasticIn::create(move->clone() );
    auto move_ease_in_back = move_ease_in->reverse();
    
    auto move_ease_out = EaseElasticOut::create(move->clone() );
    auto move_ease_out_back = move_ease_out->reverse();
    
    auto delay = DelayTime::create(0.25f);

    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), NULL);
    auto seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), NULL);
    auto seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), NULL);
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
    _kathia->runAction( RepeatForever::create(seq3));    
}


std::string SpriteEaseElastic::title() const
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
    
    auto move = MoveBy::create(3, Point(VisibleRect::right().x-130, 0));

    auto move_ease_inout1 = EaseElasticInOut::create(move->clone(), 0.3f);
    auto move_ease_inout_back1 = move_ease_inout1->reverse();
    
    auto move_ease_inout2 = EaseElasticInOut::create(move->clone(), 0.45f);
    auto move_ease_inout_back2 = move_ease_inout2->reverse();
    
    auto move_ease_inout3 = EaseElasticInOut::create(move->clone(), 0.6f);
    auto move_ease_inout_back3 = move_ease_inout3->reverse();
    
    auto delay = DelayTime::create(0.25f);
        
    auto seq1 = Sequence::create(move_ease_inout1, delay, move_ease_inout_back1, delay->clone(), NULL);
    auto seq2 = Sequence::create(move_ease_inout2, delay->clone(), move_ease_inout_back2, delay->clone(), NULL);
    auto seq3 = Sequence::create(move_ease_inout3, delay->clone(), move_ease_inout_back3, delay->clone(), NULL);
    
    _tamara->runAction( RepeatForever::create(seq1));
    _kathia->runAction( RepeatForever::create(seq2));
    _grossini->runAction( RepeatForever::create(seq3)); 
}


std::string SpriteEaseElasticInOut::title() const
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
    
    auto move = MoveBy::create(3, Point(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease_in = EaseBounceIn::create(move->clone() );
    auto move_ease_in_back = move_ease_in->reverse();
    
    auto move_ease_out = EaseBounceOut::create(move->clone() );
    auto move_ease_out_back = move_ease_out->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), NULL);
    auto seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), NULL);
    auto seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), NULL);
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
    _kathia->runAction( RepeatForever::create(seq3));    
}


std::string SpriteEaseBounce::title() const
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

    auto move = MoveBy::create(3, Point(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease = EaseBounceInOut::create(move->clone() );
    auto move_ease_back = move_ease->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), NULL);
    auto seq2 = Sequence::create(move_ease, delay->clone(), move_ease_back, delay->clone(), NULL);
    
    this->positionForTwo();
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
}


std::string SpriteEaseBounceInOut::title() const
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
    
    auto move = MoveBy::create(3, Point(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease_in = EaseBackIn::create(move->clone());
    auto move_ease_in_back = move_ease_in->reverse();
    
    auto move_ease_out = EaseBackOut::create( move->clone());
    auto move_ease_out_back = move_ease_out->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), NULL);
    auto seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), NULL);
    auto seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), NULL);
    
    _grossini->runAction(RepeatForever::create(seq1));
    _tamara->runAction(RepeatForever::create(seq2));
    _kathia->runAction(RepeatForever::create(seq3));    
}


std::string SpriteEaseBack::title() const
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
    
    auto move = MoveBy::create(3, Point(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease = EaseBackInOut::create(move->clone() );
    auto move_ease_back = move_ease->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), NULL);
    auto seq2 = Sequence::create(move_ease, delay->clone(), move_ease_back, delay->clone(), NULL);
    
    this->positionForTwo();
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));    
}


std::string SpriteEaseBackInOut::title() const
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
    
    auto s = Director::getInstance()->getWinSize();

    // rotate and jump
    auto jump1 = JumpBy::create(4, Point(-s.width+80, 0), 100, 4);
    auto jump2 = jump1->reverse();
    auto rot1 = RotateBy::create(4, 360*2);
    auto rot2 = rot1->reverse();
    
    auto seq3_1 = Sequence::create(jump2, jump1, NULL);
    auto seq3_2 = Sequence::create( rot1, rot2, NULL);
    auto spawn = Spawn::create(seq3_1, seq3_2, NULL);
    auto action = Speed::create(RepeatForever::create(spawn), 1.0f);
    action->setTag(kTagAction1);
    
    auto action2 = action->clone();
    auto action3 = action->clone();

    action2->setTag(kTagAction1);
    action3->setTag(kTagAction1);
    
    _grossini->runAction(action2);
    _tamara->runAction(action3);
    _kathia->runAction(action);
    
    this->schedule(schedule_selector(SpeedTest::altertime), 1.0f);//:@selector(altertime:) interval:1.0f];
}

void SpeedTest::altertime(float dt)
{    
    auto action1 = static_cast<Speed*>(_grossini->getActionByTag(kTagAction1));
    auto action2 = static_cast<Speed*>(_tamara->getActionByTag(kTagAction1));
    auto action3 = static_cast<Speed*>(_kathia->getActionByTag(kTagAction1));
    
    action1->setSpeed( CCRANDOM_MINUS1_1() * 2 );
    action2->setSpeed( CCRANDOM_MINUS1_1() * 2 );
    action3->setSpeed( CCRANDOM_MINUS1_1() * 2 );
}

std::string SpeedTest::title() const
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

    auto layer = createEaseLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* backEaseAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    auto layer = createEaseLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* restartEaseAction()
{
    auto layer = createEaseLayer(sceneIdx);
    layer->autorelease();

    return layer;
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
    _grossini->setPosition(Point(VisibleRect::left().x+60, VisibleRect::bottom().y + VisibleRect::getVisibleRect().size.height*1/5));
    _tamara->setPosition(Point( VisibleRect::left().x+60, VisibleRect::bottom().y + VisibleRect::getVisibleRect().size.height*4/5));
    _kathia->setVisible(false);
}


std::string EaseSpriteDemo::title() const
{
    return "No title";
}

void EaseSpriteDemo::onEnter()
{
    BaseTest::onEnter();

    // Or you can create an sprite using a filename. PNG and BMP files are supported. Probably TIFF too
    _grossini = Sprite::create(s_pathGrossini); _grossini->retain();
    _tamara = Sprite::create(s_pathSister1); _tamara->retain();
    _kathia = Sprite::create(s_pathSister2); _kathia->retain();
    
    addChild( _grossini, 3);
    addChild( _kathia, 2);
    addChild( _tamara, 1);

    _grossini->setPosition(Point(VisibleRect::left().x + 60, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*1/5));
    _kathia->setPosition(Point(VisibleRect::left().x + 60, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*2.5f/5));
    _tamara->setPosition(Point(VisibleRect::left().x + 60, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*4/5));
}

void EaseSpriteDemo::restartCallback(Object* sender)
{
    auto s = new ActionsEaseTestScene();//CCScene::create();
    s->addChild(restartEaseAction()); 

    Director::getInstance()->replaceScene(s);
    s->release();
}

void EaseSpriteDemo::nextCallback(Object* sender)
{
    auto s = new ActionsEaseTestScene();//CCScene::create();
    s->addChild( nextEaseAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void EaseSpriteDemo::backCallback(Object* sender)
{
    auto s = new ActionsEaseTestScene();//CCScene::create();
    s->addChild( backEaseAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void ActionsEaseTestScene::runThisTest()
{
    auto layer = nextEaseAction();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}
