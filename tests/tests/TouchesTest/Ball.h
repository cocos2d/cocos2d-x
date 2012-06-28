#ifndef _BALL_H_
#define _BALL_H_

#include "cocos2d.h"

class Paddle;

USING_NS_CC;

class Ball : public CCSprite
{
    CCPoint m_velocity;
public:
    Ball(void);
    virtual ~Ball(void);

    float radius();
    //BOOL initWithTexture(CCTexture2D* aTexture);
    //virtual void setTexture(CCTexture2D* newTexture);
    void move(float delta);
    void collideWithPaddle(Paddle* paddle);


public:
    void setVelocity(CCPoint velocity){m_velocity = velocity;}
    CCPoint getVelocity(){return m_velocity;}

public:
    static Ball* ballWithTexture(CCTexture2D* aTexture);
};

#endif
