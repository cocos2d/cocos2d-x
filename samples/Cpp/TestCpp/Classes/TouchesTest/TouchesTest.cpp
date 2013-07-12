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
    PongLayer *pongLayer = new PongLayer();//PongLayer::create();
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
    _ballStartingVelocity = Point(20.0f, -100.0f);
    
    _ball = Ball::ballWithTexture( TextureCache::getInstance()->addImage(s_Ball) );
    _ball->setPosition( VisibleRect::center() );
    _ball->setVelocity( _ballStartingVelocity );
    addChild( _ball );
    _ball->retain();
    
    Texture2D* paddleTexture = TextureCache::getInstance()->addImage(s_Paddle);
    
    Array *paddlesM = Array::createWithCapacity(4);
    
    Paddle* paddle = Paddle::createWithTexture(paddleTexture);
    paddle->setPosition( Point(VisibleRect::center().x, VisibleRect::bottom().y + 15) );
    paddlesM->addObject( paddle );
    
    paddle = Paddle::createWithTexture( paddleTexture );
    paddle->setPosition( Point(VisibleRect::center().x, VisibleRect::top().y - kStatusBarHeight - 15) );
    paddlesM->addObject( paddle );
    
    paddle = Paddle::createWithTexture( paddleTexture );
    paddle->setPosition( Point(VisibleRect::center().x, VisibleRect::bottom().y + 100) );
    paddlesM->addObject( paddle );
    
    paddle = Paddle::createWithTexture( paddleTexture );
    paddle->setPosition( Point(VisibleRect::center().x, VisibleRect::top().y - kStatusBarHeight - 100) );
    paddlesM->addObject( paddle );
    
    _paddles = paddlesM->clone();
    _paddles->retain();
    
    Object* pObj = NULL;
    CCARRAY_FOREACH(_paddles, pObj)
    {
        paddle = static_cast<Paddle*>(pObj);

        if(!paddle)
            break;

        addChild(paddle);
    }

    schedule( schedule_selector(PongLayer::doStep) );
}

PongLayer::~PongLayer()
{
    _ball->release();
    _paddles->release();
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

    Paddle* paddle = NULL;
    Object* pObj = NULL;
    CCARRAY_FOREACH(_paddles, pObj)
    {
        paddle = static_cast<Paddle*>(pObj);

        if(!paddle)
            break;

        _ball->collideWithPaddle( paddle );
    }

    if (_ball->getPosition().y > VisibleRect::top().y - kStatusBarHeight + _ball->radius())
        resetAndScoreBallForPlayer( kLowPlayer );
    else if (_ball->getPosition().y < VisibleRect::bottom().y-_ball->radius())
        resetAndScoreBallForPlayer( kHighPlayer );
    _ball->draw();
} 

void PongScene::runThisTest()
{
    Director::getInstance()->replaceScene(this);
}
