#include "Ball.h"
#include "Paddle.h"
#include "../VisibleRect.h"

Ball::Ball(void)
{
}

Ball::~Ball(void)
{
}

float Ball::radius()
{
    return getTexture()->getContentSize().width / 2;
}

Ball* Ball::ballWithTexture(CCTexture2D* aTexture)
{
    Ball* pBall = new Ball();
    pBall->initWithTexture(aTexture);
    pBall->autorelease();

    return pBall;
}

void Ball::move(float delta)
{
    this->setPosition( ccpAdd(getPosition(), ccpMult(m_velocity, delta)) );
    
    if (getPosition().x > VisibleRect::right().x - radius()) 
    {
        setPosition( ccp( VisibleRect::right().x - radius(), getPosition().y) );
        m_velocity.x *= -1;
    } 
    else if (getPosition().x < VisibleRect::left().x + radius()) 
    {
        setPosition( ccp(VisibleRect::left().x + radius(), getPosition().y) );
        m_velocity.x *= -1;
    }
}

void Ball::collideWithPaddle(Paddle* paddle)
{
    CCRect paddleRect = paddle->rect();
    paddleRect.origin.x += paddle->getPosition().x;
    paddleRect.origin.y += paddle->getPosition().y;
    
    float lowY  = paddleRect.getMinY();
    float midY  = paddleRect.getMidY();
    float highY = paddleRect.getMaxY();
    
    float leftX  = paddleRect.getMinX();
    float rightX = paddleRect.getMaxX();
    
    if (getPosition().x > leftX && getPosition().x < rightX) {
    
        bool hit = false;
        float angleOffset = 0.0f; 
        
        if (getPosition().y > midY && getPosition().y <= highY + radius()) 
        {
            setPosition( ccp(getPosition().x, highY + radius()) );
            hit = true;
            angleOffset = (float)M_PI / 2;
        }
        else if (getPosition().y < midY && getPosition().y >= lowY - radius()) 
        {
            setPosition( ccp(getPosition().x, lowY - radius()) );
            hit = true;
            angleOffset = -(float)M_PI / 2;
        }
        
        if (hit) 
        {
            float hitAngle = ccpToAngle(ccpSub(paddle->getPosition(), getPosition())) + angleOffset;
            
            float scalarVelocity = ccpLength(m_velocity) * 1.05f;
            float velocityAngle = -ccpToAngle(m_velocity) + 0.5f * hitAngle;
            
            m_velocity = ccpMult(ccpForAngle(velocityAngle), scalarVelocity);
        }
    }    
} 
