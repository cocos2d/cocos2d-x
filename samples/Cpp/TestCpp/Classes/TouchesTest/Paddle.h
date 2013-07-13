#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "cocos2d.h"

USING_NS_CC;

typedef enum tagPaddleState 
{
    kPaddleStateGrabbed,
    kPaddleStateUngrabbed
} PaddleState; 

class Paddle : public Sprite, public TargetedTouchDelegate, public Clonable
{
    PaddleState        _state;

public:
    Paddle(void);
    virtual ~Paddle(void);

    Rect getRect();
    bool initWithTexture(Texture2D* aTexture);
    virtual void onEnter();
    virtual void onExit();
    bool containsTouchLocation(Touch* touch);
    virtual bool ccTouchBegan(Touch* touch, Event* event);
    virtual void ccTouchMoved(Touch* touch, Event* event);
    virtual void ccTouchEnded(Touch* touch, Event* event);
    virtual Paddle* clone() const;

    static Paddle* createWithTexture(Texture2D* aTexture);
};

#endif
