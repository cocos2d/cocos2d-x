#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "cocos2d.h"

USING_NS_CC;

typedef enum tagPaddleState 
{
    kPaddleStateGrabbed,
    kPaddleStateUngrabbed
} PaddleState; 

class Paddle : public Sprite, public TargetedTouchDelegate
{
    PaddleState        _state;

public:
    Paddle(void);
    virtual ~Paddle(void);

    Rect rect();
    bool initWithTexture(Texture2D* aTexture);
    virtual void onEnter();
    virtual void onExit();
    bool containsTouchLocation(Touch* touch);
    virtual bool ccTouchBegan(Touch* touch, Event* event);
    virtual void ccTouchMoved(Touch* touch, Event* event);
    virtual void ccTouchEnded(Touch* touch, Event* event);
    virtual Object* copyWithZone(Zone *pZone);

    virtual void touchDelegateRetain();
    virtual void touchDelegateRelease();

    static Paddle* paddleWithTexture(Texture2D* aTexture);
};

#endif
