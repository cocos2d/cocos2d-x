#include "Paddle.h"

Paddle::Paddle(void)
{
}

Paddle::~Paddle(void)
{
}

Rect Paddle::rect()
{
    Size s = getTexture()->getContentSize();
    return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

Paddle* Paddle::paddleWithTexture(Texture2D* aTexture)
{
    Paddle* pPaddle = new Paddle();
    pPaddle->initWithTexture( aTexture );
    pPaddle->autorelease();

    return pPaddle;
}

bool Paddle::initWithTexture(Texture2D* aTexture)
{
    if( Sprite::initWithTexture(aTexture) ) 
    {
        _state = kPaddleStateUngrabbed;
    }
    
    return true;
}

void Paddle::onEnter()
{
    Director* pDirector = Director::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    Sprite::onEnter();
}

void Paddle::onExit()
{
    Director* pDirector = Director::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    Sprite::onExit();
}    

bool Paddle::containsTouchLocation(Touch* touch)
{
    return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool Paddle::ccTouchBegan(Touch* touch, Event* event)
{
    if (_state != kPaddleStateUngrabbed) return false;
    if ( !containsTouchLocation(touch) ) return false;
    
    _state = kPaddleStateGrabbed;
    return true;
}

void Paddle::ccTouchMoved(Touch* touch, Event* event)
{
    // If it weren't for the TouchDispatcher, you would need to keep a reference
    // to the touch from touchBegan and check that the current touch is the same
    // as that one.
    // Actually, it would be even more complicated since in the Cocos dispatcher
    // you get Sets instead of 1 UITouch, so you'd need to loop through the set
    // in each touchXXX method.
    
    CCAssert(_state == kPaddleStateGrabbed, "Paddle - Unexpected state!");    
    
    Point touchPoint = touch->getLocation();
    
    setPosition( ccp(touchPoint.x, getPosition().y) );
}

Object* Paddle::copyWithZone(Zone *pZone)
{
    this->retain();
    return this;
}

void Paddle::ccTouchEnded(Touch* touch, Event* event)
{
    CCAssert(_state == kPaddleStateGrabbed, "Paddle - Unexpected state!");    
    
    _state = kPaddleStateUngrabbed;
} 

void Paddle::touchDelegateRetain()
{
    this->retain();
}

void Paddle::touchDelegateRelease()
{
    this->release();
}