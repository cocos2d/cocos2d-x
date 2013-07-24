#include "Paddle.h"

Paddle::Paddle(void)
{
}

Paddle::~Paddle(void)
{
}

Rect Paddle::getRect()
{
    Size s = getTexture()->getContentSize();
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

Paddle* Paddle::createWithTexture(Texture2D* aTexture)
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
    Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    Sprite::onEnter();
}

void Paddle::onExit()
{
    Director* director = Director::getInstance();
    director->getTouchDispatcher()->removeDelegate(this);
    Sprite::onExit();
}    

bool Paddle::containsTouchLocation(Touch* touch)
{
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
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
    
    CCASSERT(_state == kPaddleStateGrabbed, "Paddle - Unexpected state!");    
    
    Point touchPoint = touch->getLocation();
    
    setPosition( Point(touchPoint.x, getPosition().y) );
}

Paddle* Paddle::clone() const
{
    Paddle* ret = Paddle::createWithTexture(_texture);
    ret->_state = _state;
    ret->setPosition(getPosition());
    ret->setAnchorPoint(getAnchorPoint());
    return ret;
}

void Paddle::ccTouchEnded(Touch* touch, Event* event)
{
    CCASSERT(_state == kPaddleStateGrabbed, "Paddle - Unexpected state!");    
    
    _state = kPaddleStateUngrabbed;
} 
