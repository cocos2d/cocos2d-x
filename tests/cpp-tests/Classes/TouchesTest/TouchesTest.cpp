#include "TouchesTest.h"
#include "Ball.h"
#include "Paddle.h"
#include "../testResource.h"

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


//------------------------------------------------------------------
//
// PongScene
//
//------------------------------------------------------------------
PongScene::PongScene()
{
    auto pongLayer = new (std::nothrow) PongLayer();//PongLayer::create();
    addChild(pongLayer);
    pongLayer->release();
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
    
    Paddle* paddle = Paddle::createWithTexture(paddleTexture);
    paddle->setPosition( Vec2(VisibleRect::center().x, VisibleRect::bottom().y + 15) );
	paddlesM.pushBack( paddle );
    
    paddle = Paddle::createWithTexture( paddleTexture );
    paddle->setPosition( Vec2(VisibleRect::center().x, VisibleRect::top().y - kStatusBarHeight - 15) );
    paddlesM.pushBack( paddle );
    
    paddle = Paddle::createWithTexture( paddleTexture );
    paddle->setPosition( Vec2(VisibleRect::center().x, VisibleRect::bottom().y + 100) );
    paddlesM.pushBack( paddle );
    
    paddle = Paddle::createWithTexture( paddleTexture );
    paddle->setPosition( Vec2(VisibleRect::center().x, VisibleRect::top().y - kStatusBarHeight - 100) );
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

void PongScene::runThisTest()
{
    Director::getInstance()->replaceScene(this);
}
