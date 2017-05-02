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

#include "LongPressGestureRecognizer.h"

NS_CC_BEGIN

LongPressGestureRecognizer* LongPressGestureRecognizer::create(float timeout, uint fingers)
{
    auto r = new LongPressGestureRecognizer(timeout, fingers);
    if (r and r->init())
    {
        r->autorelease();
        return r;
    }
    CC_SAFE_DELETE(r);
    return nullptr;
}

LongPressGestureRecognizer::LongPressGestureRecognizer(float timeout, uint fingers) : GestureRecognizer(fingers)
{
    //CCLOG("Constructor LongPressGestureRecognizer");
    timeoutSeconds = timeout;
}

LongPressGestureRecognizer::~LongPressGestureRecognizer() 
{
    //CCLOG("Destructor LongPressGestureRecognizer");
}

bool LongPressGestureRecognizer::onTouchBegan(Touch* touch, Event* ev) 
{
    if (touches.empty()) // empty map, new recognition
    {
        status = GestureStatus::POSSIBLE;
        reset();
        scheduleTimeout(CC_CALLBACK_1(LongPressGestureRecognizer::timeout, this));
    }
    
    if (touches.size() < fingerNumber)
        touches.insert({touch->getID(), {touch->getLocation()}}); // does nothing if certain id is alredy in the map
    else  { // too many touches!
        status = GestureStatus::FAILED;
        if (onLongPress) 
            onLongPress(this);
        return false;
    }
    
    return true;
}

void LongPressGestureRecognizer::onTouchMoved(Touch* touch, Event* ev) 
{
    if (status == GestureStatus::POSSIBLE)
    {
        auto pOld = touches.at(touch->getID());
        auto pNew = touch->getLocation();

        if (pOld.distance(pNew) >= LONGPRESS_MOVE_DELTA) // finger moved too much
            status = GestureStatus::FAILED;
    }
}

void LongPressGestureRecognizer::onTouchCancelled(Touch* touch, Event* ev) 
{
    //CCLOG("LongPressGestureRecognizer::onTouchCancelled (touch id %d)", touch->getID());
    status = GestureStatus::FAILED;
    onTouchEnded(touch, ev);
}

void LongPressGestureRecognizer::onTouchEnded(Touch* touch, Event* ev) 
{
    touches.erase(touch->getID());
    
    if (status == GestureStatus::RECOGNIZED and touches.empty()) // release after recognition
    {
        status = GestureStatus::POSSIBLE; 
        if (onLongPress)
            onLongPress(this);
    }
    else if (touches.size() < fingerNumber) // fingers lifted early
    {
        status = GestureStatus::FAILED;
        if (onLongPress)
            onLongPress(this);
    }
}

void LongPressGestureRecognizer::reset()
{
    //CCLOG("Reset called");
    unschedule(GESTURE_TIMEOUT_KEY);
    touches.clear();
}

void LongPressGestureRecognizer::timeout(float dt)
{
    //CCLOG("Timeout Longpress");
    if (status == GestureStatus::POSSIBLE and touches.size() == fingerNumber)
    {
        //CCLOG("Long press detected with %d fingers", fingerNumber);
        status = GestureStatus::RECOGNIZED;
        gestureLocation = mean(touches);
        if (onLongPress)
            onLongPress(this);
    }
}

NS_CC_END