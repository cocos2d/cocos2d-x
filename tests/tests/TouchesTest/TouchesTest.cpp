#include "TouchesTest.h"
#include "Ball.h"
#include "Paddle.h"
#include "../testResource.h"

enum tagPlayer 
{
	kHighPlayer,
	kLowPlayer
} PlayerTouches;	

#define kStatusBarHeight 20.0f
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
:TestScene(true)
{
	PongLayer *pongLayer = new PongLayer();//PongLayer::node();
	addChild(pongLayer);
    pongLayer->release();
}

void PongScene::MainMenuCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->setDeviceOrientation(CCDeviceOrientationPortrait);
    TestScene::MainMenuCallback(pSender);
}

//------------------------------------------------------------------
//
// PongLayer
//
//------------------------------------------------------------------
PongLayer::PongLayer()
{
	m_ballStartingVelocity = CCPointMake(20.0f, -100.0f);
	
    m_ball = Ball::ballWithTexture( CCTextureCache::sharedTextureCache()->addImage(s_Ball) );
	m_ball->setPosition( CCPointMake(160.0f, 240.0f) );
	m_ball->setVelocity( m_ballStartingVelocity );
	addChild( m_ball );
	m_ball->retain();
	
	CCTexture2D* paddleTexture = CCTextureCache::sharedTextureCache()->addImage(s_Paddle);
	
	CCMutableArray<CCObject *> *paddlesM = new CCMutableArray<CCObject *>(4);
	
	Paddle* paddle = Paddle::paddleWithTexture(paddleTexture);
	paddle->setPosition( CCPointMake(160, 15) );
	paddlesM->addObject( paddle );
	
	paddle = Paddle::paddleWithTexture( paddleTexture );
	paddle->setPosition( CCPointMake(160, 480 - kStatusBarHeight - 15) );
	paddlesM->addObject( paddle );
	
	paddle = Paddle::paddleWithTexture( paddleTexture );
	paddle->setPosition( CCPointMake(160, 100) );
	paddlesM->addObject( paddle );
	
	paddle = Paddle::paddleWithTexture( paddleTexture );
	paddle->setPosition( CCPointMake(160, 480 - kStatusBarHeight - 100) );
	paddlesM->addObject( paddle );
	
	m_paddles = paddlesM->copy();
	
    CCMutableArray<CCObject *>::CCMutableArrayIterator it;
	for(it = m_paddles->begin(); it != m_paddles->end(); it++)
	{
		paddle = (Paddle*)(*it);

		if(!paddle)
			break;

		addChild(paddle);
	}

	paddlesM->release();

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
	m_ball->setPosition( CCPointMake(160.0f, 240.0f) );
	
	// TODO -- scoring
}

void PongLayer::doStep(ccTime delta)
{
	m_ball->move(delta);

	Paddle* paddle;
    CCMutableArray<CCObject *>::CCMutableArrayIterator it;
	for(it = m_paddles->begin(); it != m_paddles->end(); it++)
	{
		paddle = (Paddle*)(*it);

		if(!paddle)
			break;

		m_ball->collideWithPaddle( paddle );
	}

	if (m_ball->getPosition().y > 480 - kStatusBarHeight + m_ball->radius())
		resetAndScoreBallForPlayer( kLowPlayer );
	else if (m_ball->getPosition().y < -m_ball->radius())
		resetAndScoreBallForPlayer( kHighPlayer );
    m_ball->draw();
} 

void PongScene::runThisTest()
{
    CCDirector::sharedDirector()->replaceScene(this);
}
