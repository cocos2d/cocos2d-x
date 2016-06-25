/****************************************************************************
Copyright (c) 2016 Alfonso Grillo

    drakon.cocos@gmail.com

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

#include "SwipeGestureRecognizer.h"
#include "GestureRecognizerUtils.h"

NS_CC_BEGIN

SwipeGestureRecognizer* SwipeGestureRecognizer::create()
{
    auto r = new SwipeGestureRecognizer;
    if (r and r->init())
    {
        r->autorelease();
        return r;
    }
    CC_SAFE_DELETE(r);
    return nullptr;
}

SwipeGestureRecognizer::SwipeGestureRecognizer() : GestureRecognizer()
{
    //CCLOG("Constructor SwipeGestureRecognizer");
    timeoutSeconds = SWIPE_TIMEOUT;
}

SwipeGestureRecognizer::~SwipeGestureRecognizer()
{
    //CCLOG("Destructor di SwipeGestureRecognizer");
}

bool SwipeGestureRecognizer::onTouchBegan(Touch* touch, Event* ev) 
{
    if (touches.empty()) { // empty map, new recognition
        status = GestureStatus::POSSIBLE;
        scheduleTimeout(CC_CALLBACK_1(SwipeGestureRecognizer::timeout, this));
        touches.insert({touch->getID(), touch->getLocation()});
    }
    else { // second finger
        status = GestureStatus::FAILED;
        if (onSwipe)
            onSwipe(this);
        
        return false;
    }
    return true;
}

void SwipeGestureRecognizer::onTouchMoved(Touch* touch, Event* ev) 
{
    if (status == GestureStatus::POSSIBLE)
        swipeCheck(touch);
}

void SwipeGestureRecognizer::onTouchCancelled(Touch* touch, Event* ev) 
{
    //CCLOG("SwipeGestureRecognizer::onTouchCancelled (touch id %d)", touch->getID());
    status = GestureStatus::FAILED;
    onTouchEnded(touch, ev);
}

void SwipeGestureRecognizer::onTouchEnded(Touch* touch, Event* ev) 
{
    touches.erase(touch->getID());
}

void SwipeGestureRecognizer::timeout(float dt)
{
    //CCLOG("Swipe Timeout");
    if (status == GestureStatus::POSSIBLE)
        status = GestureStatus::FAILED;
}

void SwipeGestureRecognizer::swipeCheck(Touch* touch)
{
    int id = touch->getID();
    
    if (mapHasKey(touches, id)) // tracked touch
    {
        Point currPoint = touch->getLocation();
        Point lastPoint = touches.at(id);
        Point delta = currPoint - lastPoint;
        float xOffset = delta.x;
        float yOffset = delta.y;
        
        //CCLOG("delta (x:%f, y:%f)", xOffset, yOffset);
        
        if (xOffset > SWIPE_X_DELTA and fabs(yOffset) < SWIPE_Y_TOLLERANCE)
        {
            //CCLOG("swipe right");
            status = GestureStatus::RECOGNIZED;
            swipeDirection = SwipeStatus::SWIPE_RIGHT;
        }
        else if (xOffset < -SWIPE_X_DELTA and fabs(yOffset) < SWIPE_Y_TOLLERANCE)
        {
            //CCLOG("swipe left");
            status = GestureStatus::RECOGNIZED;
            swipeDirection = SwipeStatus::SWIPE_LEFT;
        }
        else if (fabs(xOffset) < SWIPE_X_TOLLERANCE and yOffset > SWIPE_Y_DELTA)
        {
            //CCLOG("swipe up");
            status = GestureStatus::RECOGNIZED;
            swipeDirection = SwipeStatus::SWIPE_UP;
        }
        else if (fabs(xOffset) < SWIPE_X_TOLLERANCE and yOffset < -SWIPE_Y_DELTA)
        {
            //CCLOG("swipe down");
            status = GestureStatus::RECOGNIZED;
            swipeDirection = SwipeStatus::SWIPE_DOWN;
        }
        
        if (status == GestureStatus::RECOGNIZED and onSwipe)
            onSwipe(this);
        
        touches.at(id) = currPoint;
    }
}

NS_CC_END