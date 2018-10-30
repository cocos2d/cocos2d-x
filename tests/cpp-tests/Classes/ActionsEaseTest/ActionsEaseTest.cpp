/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

USING_NS_CC;

enum {
    kTagAction1 = 1,
    kTagAction2 = 2,
    kTagSlider = 1,
};


//------------------------------------------------------------------
//
// SpriteDemo
//
//------------------------------------------------------------------
void EaseSpriteDemo::centerSprites(unsigned int numberOfSprites)
{
    auto s = Director::getInstance()->getWinSize();
    
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
        _grossini->setPosition(s.width/2, s.height/2);
    }
    else if( numberOfSprites == 2 )
    {
        _kathia->setPosition(s.width/3, s.height/2);
        _tamara->setPosition(2*s.width/3, s.height/2);
        _grossini->setVisible(false);
    }
    else if( numberOfSprites == 3 )
    {
        _grossini->setPosition(s.width/2, s.height/2);
        _tamara->setPosition(s.width/4, s.height/2);
        _kathia->setPosition(3 * s.width/4, s.height/2);
    }
}


//------------------------------------------------------------------
//
// SpriteEase
//
//------------------------------------------------------------------

void SpriteEase::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130,0));
    auto move_back = move->reverse();
    
    auto move_ease_in = EaseIn::create(move->clone(), 2.5f);
    auto move_ease_in_back = move_ease_in->reverse();
    
    auto move_ease_out = EaseOut::create(move->clone(), 2.5f);
    auto move_ease_out_back = move_ease_out->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), nullptr);
    auto seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), nullptr);
    
    
    auto a2 = _grossini->runAction(RepeatForever::create(seq1));
    a2->setTag(1);

    auto a1 = _tamara->runAction(RepeatForever::create(seq2));
    a1->setTag(1);

    auto a = _kathia->runAction(RepeatForever::create(seq3));
    a->setTag(1);

    schedule(CC_SCHEDULE_SELECTOR(SpriteEase::testStopAction), 6.25f);
}


void SpriteEase::testStopAction(float dt)
{
    unschedule(CC_SCHEDULE_SELECTOR(SpriteEase::testStopAction));
    _tamara->stopActionByTag(1);
    _kathia->stopActionByTag(1);
    _grossini->stopActionByTag(1);
}

std::string SpriteEase::subtitle() const
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

    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130,0));
//    id move_back = move->reverse();
    
    auto move_ease_inout1 = EaseInOut::create(move->clone(), 0.65f);
    auto move_ease_inout_back1 = move_ease_inout1->reverse();
    
    auto move_ease_inout2 = EaseInOut::create(move->clone(), 1.35f);
    auto move_ease_inout_back2 = move_ease_inout2->reverse();

    auto move_ease_inout3 = EaseInOut::create(move->clone(), 1.0f);
    auto move_ease_inout_back3 = move_ease_inout3->reverse();
    
    auto delay = DelayTime::create(0.25f);

    auto seq1 = Sequence::create( move_ease_inout1, delay, move_ease_inout_back1, delay->clone(), nullptr);
    auto seq2 = Sequence::create( move_ease_inout2, delay->clone(), move_ease_inout_back2, delay->clone(), nullptr);
    auto seq3 = Sequence::create( move_ease_inout3, delay->clone(), move_ease_inout_back3, delay->clone(), nullptr);
        
    _tamara->runAction(RepeatForever::create(seq1));
    _kathia->runAction(RepeatForever::create(seq2));
    _grossini->runAction(RepeatForever::create(seq3));
}


std::string SpriteEaseInOut::subtitle() const
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
    
    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130,0));
    auto move_back = move->reverse();
    
    auto move_ease_in = EaseExponentialIn::create(move->clone());
    auto move_ease_in_back = move_ease_in->reverse();
    
    auto move_ease_out = EaseExponentialOut::create(move->clone());
    auto move_ease_out_back = move_ease_out->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), nullptr);
    auto seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), nullptr);
    

    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
    _kathia->runAction( RepeatForever::create(seq3));
}


std::string SpriteEaseExponential::subtitle() const
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

    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease = EaseExponentialInOut::create(move->clone() );
    auto move_ease_back = move_ease->reverse();    //--> reverse()
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create( move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create( move_ease, delay, move_ease_back, delay->clone(), nullptr);
    
    this->positionForTwo();
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));

}


std::string SpriteEaseExponentialInOut::subtitle() const
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

    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease_in = EaseSineIn::create(move->clone() );
    auto move_ease_in_back = move_ease_in->reverse();
    
    auto move_ease_out = EaseSineOut::create(move->clone() );
    auto move_ease_out_back = move_ease_out->reverse();
    
    auto delay = DelayTime::create(0.25f);
        
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), nullptr);
    auto seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), nullptr);
    
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
    _kathia->runAction( RepeatForever::create(seq3));    

}


std::string SpriteEaseSine::subtitle() const
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

    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130,0));
    auto move_back = move->reverse();
    
    auto move_ease = EaseSineInOut::create(move->clone() );
    auto move_ease_back = move_ease->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease, delay->clone(), move_ease_back, delay->clone(), nullptr);

    this->positionForTwo();

    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
}


std::string SpriteEaseSineInOut::subtitle() const
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
    
    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease_in = EaseElasticIn::create(move->clone() );
    auto move_ease_in_back = move_ease_in->reverse();
    
    auto move_ease_out = EaseElasticOut::create(move->clone() );
    auto move_ease_out_back = move_ease_out->reverse();
    
    auto delay = DelayTime::create(0.25f);

    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), nullptr);
    auto seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), nullptr);
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
    _kathia->runAction( RepeatForever::create(seq3));    
}


std::string SpriteEaseElastic::subtitle() const
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
    
    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));

    auto move_ease_inout1 = EaseElasticInOut::create(move->clone(), 0.3f);
    auto move_ease_inout_back1 = move_ease_inout1->reverse();
    
    auto move_ease_inout2 = EaseElasticInOut::create(move->clone(), 0.45f);
    auto move_ease_inout_back2 = move_ease_inout2->reverse();
    
    auto move_ease_inout3 = EaseElasticInOut::create(move->clone(), 0.6f);
    auto move_ease_inout_back3 = move_ease_inout3->reverse();
    
    auto delay = DelayTime::create(0.25f);
        
    auto seq1 = Sequence::create(move_ease_inout1, delay, move_ease_inout_back1, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease_inout2, delay->clone(), move_ease_inout_back2, delay->clone(), nullptr);
    auto seq3 = Sequence::create(move_ease_inout3, delay->clone(), move_ease_inout_back3, delay->clone(), nullptr);
    
    _tamara->runAction( RepeatForever::create(seq1));
    _kathia->runAction( RepeatForever::create(seq2));
    _grossini->runAction( RepeatForever::create(seq3)); 
}


std::string SpriteEaseElasticInOut::subtitle() const
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
    
    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease_in = EaseBounceIn::create(move->clone() );
    auto move_ease_in_back = move_ease_in->reverse();
    
    auto move_ease_out = EaseBounceOut::create(move->clone() );
    auto move_ease_out_back = move_ease_out->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), nullptr);
    auto seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), nullptr);
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
    _kathia->runAction( RepeatForever::create(seq3));    
}


std::string SpriteEaseBounce::subtitle() const
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

    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease = EaseBounceInOut::create(move->clone() );
    auto move_ease_back = move_ease->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease, delay->clone(), move_ease_back, delay->clone(), nullptr);
    
    this->positionForTwo();
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
}


std::string SpriteEaseBounceInOut::subtitle() const
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
    
    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease_in = EaseBackIn::create(move->clone());
    auto move_ease_in_back = move_ease_in->reverse();
    
    auto move_ease_out = EaseBackOut::create( move->clone());
    auto move_ease_out_back = move_ease_out->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), nullptr);
    auto seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), nullptr);
    
    _grossini->runAction(RepeatForever::create(seq1));
    _tamara->runAction(RepeatForever::create(seq2));
    _kathia->runAction(RepeatForever::create(seq3));    
}


std::string SpriteEaseBack::subtitle() const
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
    
    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease = EaseBackInOut::create(move->clone() );
    auto move_ease_back = move_ease->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease, delay->clone(), move_ease_back, delay->clone(), nullptr);
    
    this->positionForTwo();
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));    
}


std::string SpriteEaseBackInOut::subtitle() const
{
    return "EaseBackInOut action";
}

//------------------------------------------------------------------
//
// SpriteEaseBezier
//
//------------------------------------------------------------------

void SpriteEaseBezier::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    
    //
    // startPosition can be any coordinate, but since the movement
    // is relative to the Bezier curve, make it (0,0)
    //
    
    centerSprites(3);
    
    // sprite 1
    ccBezierConfig bezier;
    bezier.controlPoint_1 = Vec2(0, s.height/2);
    bezier.controlPoint_2 = Vec2(300, -s.height/2);
    bezier.endPosition = Vec2(300,100);
    
    auto bezierForward = BezierBy::create(3, bezier);
    auto bezierEaseForward = EaseBezierAction::create(bezierForward);
    bezierEaseForward->setBezierParamer(0.5, 0.5, 1.0, 1.0);
    
    auto bezierEaseBack = bezierEaseForward->reverse();
    auto rep = RepeatForever::create(Sequence::create( bezierEaseForward, bezierEaseBack, nullptr));
    
    
    // sprite 2
    _tamara->setPosition(80,160);
	ccBezierConfig bezier2;
    bezier2.controlPoint_1 = Vec2(100, s.height/2);
    bezier2.controlPoint_2 = Vec2(200, -s.height/2);
    bezier2.endPosition = Vec2(240,160);
    
    auto bezierTo1 = BezierTo::create(2, bezier2);
    auto bezierEaseTo1 = EaseBezierAction::create(bezierTo1);
    bezierEaseTo1->setBezierParamer(0.5, 0.5, 1.0, 1.0);
    
    // sprite 3
    _kathia->setPosition(400,160);
    auto bezierTo2 = BezierTo::create(2, bezier2);
    auto bezierEaseTo2 = EaseBezierAction::create(bezierTo2);
    bezierEaseTo2->setBezierParamer(0.0, 0.5, -5.0, 1.0);

    
    _grossini->runAction( rep);
    _tamara->runAction(bezierEaseTo1);
    _kathia->runAction(bezierEaseTo2);
    
}

std::string SpriteEaseBezier::subtitle()const
{
    return "SpriteEaseBezier action";
}

//------------------------------------------------------------------
//
// SpriteEaseQuadratic
//
//------------------------------------------------------------------

void SpriteEaseQuadratic::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease_in = EaseQuadraticActionIn::create(move->clone() );
    auto move_ease_in_back = move_ease_in->reverse();
    
    auto move_ease_out = EaseQuadraticActionOut::create(move->clone() );
    auto move_ease_out_back = move_ease_out->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), nullptr);
    auto seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), nullptr);
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
    _kathia->runAction( RepeatForever::create(seq3));
}

std::string SpriteEaseQuadratic::subtitle() const
{
    return "SpriteEaseQuadratic action";
}

//------------------------------------------------------------------
//
// SpriteEaseQuadraticInOut
//
//------------------------------------------------------------------

void SpriteEaseQuadraticInOut::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease = EaseQuadraticActionInOut::create(move->clone() );
    auto move_ease_back = move_ease->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease, delay->clone(), move_ease_back, delay->clone(), nullptr);
    
    this->positionForTwo();
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
}

std::string SpriteEaseQuadraticInOut::subtitle()const
{
    return "SpriteEaseQuadraticInOut action";
}


//------------------------------------------------------------------
//
// SpriteEaseQuartic
//
//------------------------------------------------------------------

void SpriteEaseQuartic::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease_in = EaseQuarticActionIn::create(move->clone() );
    auto move_ease_in_back = move_ease_in->reverse();
    
    auto move_ease_out = EaseQuarticActionOut::create(move->clone() );
    auto move_ease_out_back = move_ease_out->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), nullptr);
    auto seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), nullptr);
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
    _kathia->runAction( RepeatForever::create(seq3));
}

std::string SpriteEaseQuartic::subtitle()const
{
    return "SpriteEaseQuartic action";
}

//------------------------------------------------------------------
//
// SpriteEaseQuarticInOut
//
//------------------------------------------------------------------

void SpriteEaseQuarticInOut::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease = EaseQuarticActionInOut::create(move->clone() );
    auto move_ease_back = move_ease->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease, delay->clone(), move_ease_back, delay->clone(), nullptr);
    
    this->positionForTwo();
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
}

std::string SpriteEaseQuarticInOut::subtitle()const
{
    return "SpriteEaseQuarticInOut action";
}

//------------------------------------------------------------------
//
// SpriteEaseQuintic
//
//------------------------------------------------------------------

void SpriteEaseQuintic::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease_in = EaseQuinticActionIn::create(move->clone() );
    auto move_ease_in_back = move_ease_in->reverse();
    
    auto move_ease_out = EaseQuinticActionOut::create(move->clone() );
    auto move_ease_out_back = move_ease_out->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), nullptr);
    auto seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), nullptr);
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
    _kathia->runAction( RepeatForever::create(seq3));
}

std::string SpriteEaseQuintic::subtitle()const
{
    return "SpriteEaseQuintic action";
}


//------------------------------------------------------------------
//
// SpriteEaseQuinticInOut
//
//------------------------------------------------------------------

void SpriteEaseQuinticInOut::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease = EaseQuinticActionInOut::create(move->clone() );
    auto move_ease_back = move_ease->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease, delay->clone(), move_ease_back, delay->clone(), nullptr);
    
    this->positionForTwo();
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
}

std::string SpriteEaseQuinticInOut::subtitle()const
{
    return "SpriteEaseQuinticInOut action";
}

//------------------------------------------------------------------
//
// SpriteEaseCircle
//
//------------------------------------------------------------------

void SpriteEaseCircle::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease_in = EaseCircleActionIn::create(move->clone() );
    auto move_ease_in_back = move_ease_in->reverse();
    
    auto move_ease_out = EaseCircleActionOut::create(move->clone() );
    auto move_ease_out_back = move_ease_out->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), nullptr);
    auto seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), nullptr);
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
    _kathia->runAction( RepeatForever::create(seq3));
}

std::string SpriteEaseCircle::subtitle()const
{
    return "SpriteEaseCircle action";
}


//------------------------------------------------------------------
//
// SpriteEaseCircleInOut
//
//------------------------------------------------------------------

void SpriteEaseCircleInOut::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease = EaseCircleActionInOut::create(move->clone() );
    auto move_ease_back = move_ease->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease, delay->clone(), move_ease_back, delay->clone(), nullptr);
    
    this->positionForTwo();
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
}

std::string SpriteEaseCircleInOut::subtitle()const
{
    return "SpriteEaseCircleInOut action";
}

//------------------------------------------------------------------
//
// SpriteEaseCubic
//
//------------------------------------------------------------------

void SpriteEaseCubic::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease_in = EaseCubicActionIn::create(move->clone() );
    auto move_ease_in_back = move_ease_in->reverse();
    
    auto move_ease_out = EaseCubicActionOut::create(move->clone() );
    auto move_ease_out_back = move_ease_out->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), nullptr);
    auto seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), nullptr);
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
    _kathia->runAction( RepeatForever::create(seq3));
}

std::string SpriteEaseCubic::subtitle()const
{
    return "SpriteEaseCubic action";
}


//------------------------------------------------------------------
//
// SpriteEaseCubicInOut
//
//------------------------------------------------------------------

void SpriteEaseCubicInOut::onEnter()
{
    EaseSpriteDemo::onEnter();
    
    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();
    
    auto move_ease = EaseCubicActionInOut::create(move->clone() );
    auto move_ease_back = move_ease->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease, delay->clone(), move_ease_back, delay->clone(), nullptr);
    
    this->positionForTwo();
    
    _grossini->runAction( RepeatForever::create(seq1));
    _tamara->runAction( RepeatForever::create(seq2));
}

std::string SpriteEaseCubicInOut::title()const
{
    return "SpriteEaseCubicInOut action";
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
    auto jump1 = JumpBy::create(4, Vec2(-s.width+80, 0), 100, 4);
    auto jump2 = jump1->reverse();
    auto rot1 = RotateBy::create(4, 360*2);
    auto rot2 = rot1->reverse();
    
    auto seq3_1 = Sequence::create(jump2, jump1, nullptr);
    auto seq3_2 = Sequence::create( rot1, rot2, nullptr);
    auto spawn = Spawn::create(seq3_1, seq3_2, nullptr);
    auto action = Speed::create(RepeatForever::create(spawn), 1.0f);
    action->setTag(kTagAction1);
    
    auto action2 = action->clone();
    auto action3 = action->clone();

    action2->setTag(kTagAction1);
    action3->setTag(kTagAction1);
    
    _grossini->runAction(action2);
    _tamara->runAction(action3);
    _kathia->runAction(action);
    
    this->schedule(CC_SCHEDULE_SELECTOR(SpeedTest::altertime), 1.0f);//:@selector(altertime:) interval:1.0f];
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

std::string SpeedTest::subtitle() const
{
    return "Speed action";
}

//------------------------------------------------------------------
//
// EaseSpriteDemo
//
//------------------------------------------------------------------

ActionsEaseTests::ActionsEaseTests()
{
    ADD_TEST_CASE(SpriteEase);
    ADD_TEST_CASE(SpriteEaseInOut);
    ADD_TEST_CASE(SpriteEaseExponential);
    ADD_TEST_CASE(SpriteEaseExponentialInOut);
    ADD_TEST_CASE(SpriteEaseSine);
    ADD_TEST_CASE(SpriteEaseSineInOut);
    ADD_TEST_CASE(SpriteEaseElastic);
    ADD_TEST_CASE(SpriteEaseElasticInOut);
    ADD_TEST_CASE(SpriteEaseBounce);
    ADD_TEST_CASE(SpriteEaseBounceInOut);
    ADD_TEST_CASE(SpriteEaseBack);
    ADD_TEST_CASE(SpriteEaseBackInOut);
    ADD_TEST_CASE(SpriteEaseBezier);
    ADD_TEST_CASE(SpriteEaseQuadratic);
    ADD_TEST_CASE(SpriteEaseQuadraticInOut);
    ADD_TEST_CASE(SpriteEaseQuartic);
    ADD_TEST_CASE(SpriteEaseQuarticInOut);
    ADD_TEST_CASE(SpriteEaseQuintic);
    ADD_TEST_CASE(SpriteEaseQuinticInOut);
    ADD_TEST_CASE(SpriteEaseCircle);
    ADD_TEST_CASE(SpriteEaseCircleInOut);
    ADD_TEST_CASE(SpriteEaseCubic);
    ADD_TEST_CASE(SpriteEaseCubicInOut);
    ADD_TEST_CASE(SpeedTest);
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
    _grossini->setPosition(VisibleRect::left().x+60, VisibleRect::bottom().y + VisibleRect::getVisibleRect().size.height*1/5);
    _tamara->setPosition(VisibleRect::left().x+60, VisibleRect::bottom().y + VisibleRect::getVisibleRect().size.height*4/5);
    _kathia->setVisible(false);
}


std::string EaseSpriteDemo::subtitle() const
{
    return "No title";
}

void EaseSpriteDemo::onEnter()
{
    TestCase::onEnter();

    // Or you can create an sprite using a filename. PNG and BMP files are supported. Probably TIFF too
    _grossini = Sprite::create(s_pathGrossini); _grossini->retain();
    _tamara = Sprite::create(s_pathSister1); _tamara->retain();
    _kathia = Sprite::create(s_pathSister2); _kathia->retain();
    
    addChild( _grossini, 3);
    addChild( _kathia, 2);
    addChild( _tamara, 1);

    _grossini->setPosition(VisibleRect::left().x + 60, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*1/5);
    _kathia->setPosition(VisibleRect::left().x + 60, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*2.5f/5);
    _tamara->setPosition(VisibleRect::left().x + 60, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*4/5);
}
