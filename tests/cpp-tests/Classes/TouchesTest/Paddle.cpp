/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "Paddle.h"

USING_NS_CC;

Paddle::Paddle(void)
{
}

Paddle::~Paddle(void)
{
}

Rect Paddle::getRect()
{
    auto s = getTexture()->getContentSize();
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

Paddle* Paddle::createWithTexture(Texture2D* aTexture)
{
    Paddle* pPaddle = new (std::nothrow) Paddle();
    pPaddle->initWithTexture(aTexture);
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
    Sprite::onEnter();
    
    // Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(Paddle::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Paddle::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Paddle::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Paddle::onExit()
{
//    auto director = Director::getInstance();
//    director->getTouchDispatcher()->removeDelegate(this);
    Sprite::onExit();
}    

bool Paddle::containsTouchLocation(Touch* touch)
{
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool Paddle::onTouchBegan(Touch* touch, Event* event)
{
    CCLOG("Paddle::onTouchBegan id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
    
    if (_state != kPaddleStateUngrabbed) return false;
    if ( !containsTouchLocation(touch) ) return false;
    
    _state = kPaddleStateGrabbed;
    CCLOG("return true");
    return true;
}

void Paddle::onTouchMoved(Touch* touch, Event* event)
{
    // If it weren't for the TouchDispatcher, you would need to keep a reference
    // to the touch from touchBegan and check that the current touch is the same
    // as that one.
    // Actually, it would be even more complicated since in the Cocos dispatcher
    // you get Sets instead of 1 UITouch, so you'd need to loop through the set
    // in each touchXXX method.
    
    CCLOG("Paddle::onTouchMoved id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
    
    CCASSERT(_state == kPaddleStateGrabbed, "Paddle - Unexpected state!");    
    
    auto touchPoint = touch->getLocation();
    
    setPosition( Vec2(touchPoint.x, getPosition().y) );
}

Paddle* Paddle::clone() const
{
    Paddle* ret = Paddle::createWithTexture(_texture);
    ret->_state = _state;
    ret->setPosition(getPosition());
    ret->setAnchorPoint(getAnchorPoint());
    return ret;
}

void Paddle::onTouchEnded(Touch* touch, Event* event)
{
    CCASSERT(_state == kPaddleStateGrabbed, "Paddle - Unexpected state!");    
    
    _state = kPaddleStateUngrabbed;
} 
