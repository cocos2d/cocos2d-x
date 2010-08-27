#ifndef _BALL_H_
#define _BALL_H_

#include "cocos2d.h"

class Paddle;

using namespace cocos2d;

class Ball : public CCSprite
{
	CGPoint m_velocity;
public:
	Ball(void);
	virtual ~Ball(void);

	float radius();
	//BOOL initWithTexture(CCTexture2D* aTexture);
	//virtual void setTexture(CCTexture2D* newTexture);
	void move(ccTime delta);
	void collideWithPaddle(Paddle* paddle);


public:
	void setVelocity(CGPoint velocity){m_velocity = velocity;}
	CGPoint getVelocity(){return m_velocity;}

public:
	static Ball* ballWithTexture(CCTexture2D* aTexture);
};

#endif
