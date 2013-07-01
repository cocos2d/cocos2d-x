#ifndef _BALL_H_
#define _BALL_H_

#include "cocos2d.h"

class Paddle;

USING_NS_CC;

class Ball : public Sprite
{
    Point _velocity;
public:
    Ball(void);
    virtual ~Ball(void);

    float radius();
    //BOOL initWithTexture(Texture2D* aTexture);
    //virtual void setTexture(Texture2D* newTexture);
    void move(float delta);
    void collideWithPaddle(Paddle* paddle);


public:
    void setVelocity(Point velocity){_velocity = velocity;}
    Point getVelocity(){return _velocity;}

public:
    static Ball* ballWithTexture(Texture2D* aTexture);
};

#endif
