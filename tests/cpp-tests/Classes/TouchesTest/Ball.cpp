#include "Ball.h"
#include "Paddle.h"
#include "../VisibleRect.h"

USING_NS_CC;

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

Ball* Ball::ballWithTexture(Texture2D* aTexture)
{
    Ball* pBall = new (std::nothrow) Ball();
    pBall->initWithTexture(aTexture);
    pBall->autorelease();

    return pBall;
}

void Ball::move(float delta)
{
    this->setPosition(getPosition() + _velocity * delta);
    
    if (getPosition().x > VisibleRect::right().x - radius()) 
    {
        setPosition(VisibleRect::right().x - radius(), getPosition().y);
        _velocity.x *= -1;
    } 
    else if (getPosition().x < VisibleRect::left().x + radius()) 
    {
        setPosition(VisibleRect::left().x + radius(), getPosition().y);
        _velocity.x *= -1;
    }
}

void Ball::collideWithPaddle(Paddle* paddle)
{
    auto paddleRect = paddle->getRect();
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
            setPosition(getPosition().x, highY + radius());
            hit = true;
            angleOffset = (float)M_PI / 2;
        }
        else if (getPosition().y < midY && getPosition().y >= lowY - radius()) 
        {
            setPosition(getPosition().x, lowY - radius());
            hit = true;
            angleOffset = -(float)M_PI / 2;
        }
        
        if (hit) 
        {
            float hitAngle = (paddle->getPosition() - getPosition()).getAngle() + angleOffset;
            
            float scalarVelocity = _velocity.getLength() * 1.05f;
            float velocityAngle = -_velocity.getAngle() + 0.5f * hitAngle;
            
            _velocity = Vec2::forAngle(velocityAngle) * scalarVelocity;
        }
    }    
} 
