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

void PongScene::MainMenuCallback(CCObject* pSender)
{
    TestScene::MainMenuCallback(pSender);
}

//------------------------------------------------------------------
//
// PongLayer
//
//------------------------------------------------------------------
PongLayer::PongLayer()
{
    m_tWinSize = CCDirector::sharedDirector()->getWinSize();

    m_ballStartingVelocity = CCPointMake(20.0f, -100.0f);
    
    m_ball = Ball::ballWithTexture( CCTextureCache::sharedTextureCache()->addImage(s_Ball) );
    m_ball->setPosition( CCPointMake(m_tWinSize.width/2, m_tWinSize.height/2) );
    m_ball->setVelocity( m_ballStartingVelocity );
    addChild( m_ball );
    m_ball->retain();
    
    CCTexture2D* paddleTexture = CCTextureCache::sharedTextureCache()->addImage(s_Paddle);
    
    CCArray *paddlesM = CCArray::createWithCapacity(4);
    
    Paddle* paddle = Paddle::paddleWithTexture(paddleTexture);
    paddle->setPosition( CCPointMake(m_tWinSize.width/2, 15) );
    paddlesM->addObject( paddle );
    
    paddle = Paddle::paddleWithTexture( paddleTexture );
    paddle->setPosition( CCPointMake(m_tWinSize.width/2, m_tWinSize.height - kStatusBarHeight - 15) );
    paddlesM->addObject( paddle );
    
    paddle = Paddle::paddleWithTexture( paddleTexture );
    paddle->setPosition( CCPointMake(m_tWinSize.width/2, 100) );
    paddlesM->addObject( paddle );
    
    paddle = Paddle::paddleWithTexture( paddleTexture );
    paddle->setPosition( CCPointMake(m_tWinSize.width/2, m_tWinSize.height - kStatusBarHeight - 100) );
    paddlesM->addObject( paddle );
    
    m_paddles = (CCArray*)paddlesM->copy();
    
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_paddles, pObj)
    {
        paddle = (Paddle*)(pObj);

        if(!paddle)
            break;

        addChild(paddle);
    }

    schedule( schedule_selector(PongLayer::doStep) );
}

PongLayer::~PongLayer()
{
    m_ball->release();
    m_paddles->release();
}

void PongLayer::resetAndScoreBallForPlayer(int player)
{
    m_ballStartingVelocity = ccpMult(m_ballStartingVelocity, -1.1f);
    m_ball->setVelocity( m_ballStartingVelocity );
    m_ball->setPosition( CCPointMake(m_tWinSize.width/2, m_tWinSize.height/2) );
    
    // TODO -- scoring
}

void PongLayer::doStep(float delta)
{
    m_ball->move(delta);

    Paddle* paddle = NULL;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_paddles, pObj)
    {
        paddle = (Paddle*)(pObj);

        if(!paddle)
            break;

        m_ball->collideWithPaddle( paddle );
    }

    if (m_ball->getPosition().y > m_tWinSize.height - kStatusBarHeight + m_ball->radius())
        resetAndScoreBallForPlayer( kLowPlayer );
    else if (m_ball->getPosition().y < -m_ball->radius())
        resetAndScoreBallForPlayer( kHighPlayer );
    m_ball->draw();
} 

void PongScene::runThisTest()
{
    CCDirector::sharedDirector()->replaceScene(this);
}
