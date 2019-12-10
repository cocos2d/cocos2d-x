/****************************************************************************
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

#include "TouchesTest.h"
#include "Ball.h"
#include "Paddle.h"
#include "../testResource.h"

USING_NS_CC;

enum tagPlayer 
{
    kHighPlayer,
    kLowPlayer
} PlayerTouches;    

#define kStatusBarHeight 0.0f //20.0f
//#define k1UpperLimit (480.0f - kStatusBarHeight)

enum 
{
    kSpriteTag
};

TouchesTests::TouchesTests()
{
    ADD_TEST_CASE(PongScene);
    ADD_TEST_CASE(ForceTouchTest);
}
//------------------------------------------------------------------
//
// PongScene
//
//------------------------------------------------------------------
bool PongScene::init()
{
    if (TestCase::init())
    {
        auto pongLayer = PongLayer::create();
        addChild(pongLayer);

        return true;
    }
    return false;
}

//------------------------------------------------------------------
//
// PongLayer
//
//------------------------------------------------------------------
PongLayer::PongLayer()
{
    _ballStartingVelocity = Vec2(20.0f, -100.0f);
    
    _ball = Ball::ballWithTexture( Director::getInstance()->getTextureCache()->addImage(s_Ball) );
    _ball->setPosition( VisibleRect::center() );
    _ball->setVelocity( _ballStartingVelocity );
    addChild( _ball );
    
    auto paddleTexture = Director::getInstance()->getTextureCache()->addImage(s_Paddle);
    
    Vector<Paddle*> paddlesM(4);
    
    float paddleStep =(VisibleRect::getVisibleRect().size.height - kStatusBarHeight - 30 - 3*paddleTexture->getPixelsHigh())/3 + paddleTexture->getPixelsHigh();
    float nextPaddlePos = VisibleRect::bottom().y + 15;
    Paddle* paddle = Paddle::createWithTexture(paddleTexture);
    paddle->setPosition( Vec2(VisibleRect::center().x, nextPaddlePos));
	paddlesM.pushBack( paddle );
    
    paddle = Paddle::createWithTexture( paddleTexture );
    paddle->setPosition( Vec2(VisibleRect::center().x, nextPaddlePos+=paddleStep) );
    paddlesM.pushBack( paddle );

    paddle = Paddle::createWithTexture( paddleTexture );
    paddle->setPosition( Vec2(VisibleRect::center().x, nextPaddlePos+=paddleStep) );
    paddlesM.pushBack( paddle );

    paddle = Paddle::createWithTexture( paddleTexture );
    paddle->setPosition( Vec2(VisibleRect::center().x, nextPaddlePos+=paddleStep) );
    paddlesM.pushBack( paddle );
    
    _paddles = paddlesM;
    
    for (auto& paddle : _paddles)
    {
        addChild(paddle);
    }

    schedule( CC_SCHEDULE_SELECTOR(PongLayer::doStep) );
}

PongLayer::~PongLayer()
{
}

void PongLayer::resetAndScoreBallForPlayer(int player)
{
    _ballStartingVelocity = _ballStartingVelocity * -1.1f;
    _ball->setVelocity( _ballStartingVelocity );
    _ball->setPosition( VisibleRect::center() );
    
    // TODO -- scoring
}

void PongLayer::doStep(float delta)
{
    _ball->move(delta);

    for (auto& paddle : _paddles)
    {
        _ball->collideWithPaddle( paddle );
    }

    if (_ball->getPosition().y > VisibleRect::top().y - kStatusBarHeight + _ball->radius())
        resetAndScoreBallForPlayer( kLowPlayer );
    else if (_ball->getPosition().y < VisibleRect::bottom().y-_ball->radius())
        resetAndScoreBallForPlayer( kHighPlayer );
}

const char * _Info_Formatter = "Current force value : %0.02f, maximum possible force : %0.02f";
char formatBuffer[256] = {0, };

ForceTouchTest::ForceTouchTest()
{
    auto s = Director::getInstance()->getWinSize();

    _infoLabel = Label::createWithTTF(TTFConfig("fonts/arial.ttf"), "Current force value : 0.00, maximum possible force : 0.00");
    _infoLabel->setPosition(s.width / 2, s.height / 2);
    addChild(_infoLabel);

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(ForceTouchTest::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(ForceTouchTest::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(ForceTouchTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

ForceTouchTest::~ForceTouchTest()
{
}

std::string ForceTouchTest::title() const
{
    return std::string("3D Touch Test");
}

std::string ForceTouchTest::subtitle() const
{
    return std::string("Touch with force to see info label changes\nOnly work on iPhone6s / iPhone6s Plus");
}
    
void ForceTouchTest::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
}

void ForceTouchTest::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    for(auto& t : touches)
    {
        float currentForce = t->getCurrentForce();
        float maxForce = t->getMaxForce();
        sprintf(formatBuffer, _Info_Formatter, currentForce, maxForce);
        _infoLabel->setString(std::string(formatBuffer));
    }
}

void ForceTouchTest::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    sprintf(formatBuffer, _Info_Formatter, 0.0f, 0.0f);
    _infoLabel->setString(std::string(formatBuffer));
}
