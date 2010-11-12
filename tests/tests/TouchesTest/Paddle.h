#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "cocos2d.h"

using namespace cocos2d;

typedef enum tagPaddleState 
{
	kPaddleStateGrabbed,
	kPaddleStateUngrabbed
} PaddleState; 

class Paddle : public CCSprite, public CCTargetedTouchDelegate
{
	PaddleState		m_state;

public:
	Paddle(void);
	virtual ~Paddle(void);

	CGRect rect();
	bool initWithTexture(CCTexture2D* aTexture);
	virtual void onEnter();
	virtual void onExit();
	bool containsTouchLocation(CCTouch* touch);
	virtual bool ccTouchBegan(CCTouch* touch, UIEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, UIEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, UIEvent* event);

	static Paddle* paddleWithTexture(CCTexture2D* aTexture);
};

#endif
