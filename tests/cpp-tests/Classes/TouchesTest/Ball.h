#ifndef _BALL_H_
#define _BALL_H_

#include "cocos2d.h"

class Paddle;

class Ball : public cocos2d::Sprite
{
    cocos2d::Vec2 _velocity;
public:
    Ball(void);
    virtual ~Ball(void);

    float radius();
    //BOOL initWithTexture(cocos2d::Texture2D* aTexture);
    //virtual void setTexture(cocos2d::Texture2D* newTexture);
    void move(float delta);
    void collideWithPaddle(Paddle* paddle);


public:
    void setVelocity(cocos2d::Vec2 velocity){_velocity = velocity;}
    cocos2d::Vec2 getVelocity(){return _velocity;}

public:
    static Ball* ballWithTexture(cocos2d::Texture2D* aTexture);
};

#endif
