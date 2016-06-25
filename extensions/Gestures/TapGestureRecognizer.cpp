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

#include "TapGestureRecognizer.h"

NS_CC_BEGIN

TapGestureRecognizer* TapGestureRecognizer::create(uint fingerCount, uint tapNumber, float maxTime)
{
    auto r = new TapGestureRecognizer(fingerCount, tapNumber, maxTime);
    if (r and r->init())
    {
        r->autorelease();
        return r;
    }
    CC_SAFE_DELETE(r);
    return nullptr;
}

TapGestureRecognizer::TapGestureRecognizer(uint fingers, uint taps, float maxTime) : GestureRecognizer(fingers), tapNumber(taps)
{
    //CCLOG("Constructor TapGestureRecognizer");
    timeoutSeconds = maxTime;
}

TapGestureRecognizer::~TapGestureRecognizer()
{
    //CCLOG("Destructor TapGestureRecognizer");
}

bool TapGestureRecognizer::onTouchBegan(Touch* touch, Event* ev) 
{
    if (touches.empty()) // empty map, new recognition
    {
        status = GestureStatus::POSSIBLE;
        reset();
        scheduleTimeout(CC_CALLBACK_1(TapGestureRecognizer::reset, this));
    }
    
    touches.insert({touch->getID(), touch->getLocation()});
    touchesCount.insert({touch->getID(), 0}); // tap counter for each id start at 0
    
    if (touches.size() > fingerNumber) { // too many touches!
        status = GestureStatus::FAILED;
        reset();
        return false;
    }
    return true;
}

void TapGestureRecognizer::onTouchMoved(Touch* touch, Event* ev) 
{
    if (status == GestureStatus::POSSIBLE)
    {
        int neighborIndex;
        if (not existNeighbor(touch->getLocation(), neighborIndex)) // there isn't a neighobor of touched point
        { // finger moved here
            status = GestureStatus::FAILED;
            reset();
        }
    }
}

void TapGestureRecognizer::onTouchCancelled(Touch* touch, Event* ev) 
{
    //CCLOG("TapGestureRecognizer::onTouchCancelled (touch id %d)", touch->getID());
    status = GestureStatus::FAILED;
    reset();
}

void TapGestureRecognizer::onTouchEnded(Touch* touch, Event* ev) 
{
    if (status == GestureStatus::POSSIBLE and touches.size() == fingerNumber)
    {
        if ( touchEndCheck(touch) ) // all fingers lifted
            tapCount++;
        
        if (tapCount == tapNumber)
        {
            //CCLOG("%u Tap with %u fingers detected", tapNumber, fingerNumber);
            status = GestureStatus::RECOGNIZED;
            gestureLocation = mean(touches);
            reset(); // for next recognition
        }
    }
}

/**
 * 
 * @param aPoint Point of we search the neighbor
 * @param touchIndex output parameter, id of the neighbor
 * @return true if neighbor is found
 */
bool TapGestureRecognizer::existNeighbor(Point aPoint, int& touchIndex)
{
    for (auto& p : touches)
    {
        auto p2 = p.second;
        
        if (aPoint.distance(p2) <= TAP_MOVE_DELTA)
        {
            touchIndex = p.first;
            return true;
        }
    }
    return false;
}

/**
 * 
 * @param touch
 * @return true when there exist "fingerNumber" touches with counter equals to "tapCount + 1"
 */
bool TapGestureRecognizer::touchEndCheck(Touch* touch)
{
    int neighborIndex;
    if (existNeighbor(touch->getLocation(), neighborIndex))
        touchesCount.at(neighborIndex)++; // update counter relative to lifted finger
    
    auto count = std::count_if(touchesCount.begin(), touchesCount.end(), [=](const std::pair<int, int>& p){return p.second == (int)tapCount + 1;});
    return count == fingerNumber;
}

void TapGestureRecognizer::reset(float dt)
{
    //CCLOG("Reset called");
    if (onTap)
        onTap(this);
    
    unschedule(GESTURE_TIMEOUT_KEY);
    touches.clear();
    touchesCount.clear();
    tapCount = 0;
}

NS_CC_END