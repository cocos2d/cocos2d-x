#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "cocos2d.h"

USING_NS_CC;

typedef enum tagPaddleState 
{
    kPaddleStateGrabbed,
    kPaddleStateUngrabbed
} PaddleState; 

class Paddle : public CCSprite, public CCTargetedTouchDelegate
{
    PaddleState        m_state;

public:
    Paddle(void);
    virtual ~Paddle(void);

    CCRect rect();
    bool initWithTexture(CCTexture2D* aTexture);
    virtual void onEnter();
    virtual void onExit();
    bool containsTouchLocation(CCTouch* touch);
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    virtual CCObject* copyWithZone(CCZone *pZone);

    virtual void touchDelegateRetain();
    virtual void touchDelegateRelease();

    static Paddle* paddleWithTexture(CCTexture2D* aTexture);
};

#endif
