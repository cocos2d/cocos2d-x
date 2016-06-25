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

#include "PinchGestureRecognizer.h"
#include "GestureRecognizerUtils.h"

NS_CC_BEGIN

PinchGestureRecognizer* PinchGestureRecognizer::create()
{
    auto r = new PinchGestureRecognizer();
    if (r and r->init())
    {
        r->autorelease();
        return r;
    }
    CC_SAFE_DELETE(r);
    return nullptr;
}

PinchGestureRecognizer::PinchGestureRecognizer() : GestureRecognizer(2) // pinch sempre con due dita
{
    //CCLOG("Constructor PinchGestureRecognizer");
}

PinchGestureRecognizer::~PinchGestureRecognizer()
{
    //CCLOG("Destructor PinchGestureRecognizer");
}

bool PinchGestureRecognizer::onTouchBegan(Touch* touch, Event* ev) 
{
    if (touches.size() < 2)
    {
        status = GestureStatus::POSSIBLE;
        touches.insert({touch->getID(), touch->getLocation()});

        if (touches.size() == 2) 
        {
            status = GestureStatus::BEGAN;
            gestureLocation = mean(touches);
            if (onPinch)
                onPinch(this); // "GestureStatus::BEGAN"
        }
        return true;
    }
    else
        return false; // no others touch tracking
}

void PinchGestureRecognizer::onTouchMoved(Touch* touch, Event* ev) 
{
    if (touches.size() == 2)
    {
        status = GestureStatus::CHANGED;
        
        TouchesMap updatedTouches;
        updatedTouches.insert({touch->getID(), touch->getLocation()});
        
        for (auto& pair : touches) // add tracked points that not moved
            updatedTouches.insert({pair.first, pair.second});
        
        if (updatedTouches.size() == 2)
        {
            pinchFactor     = computePinchFactor(updatedTouches);
            pinchRotation   = computeAngle(updatedTouches);
            
            auto newLocation = mean(updatedTouches); // gesture center
            pinchTraslation  = newLocation - gestureLocation; // move delta
            gestureLocation  = newLocation;
            
            touches = updatedTouches; // touch map update

            if (onPinch)
                onPinch(this); // "GestureStatus::CHANGED"
        }
    }
}

void PinchGestureRecognizer::onTouchCancelled(Touch* touch, Event* ev) 
{
    //CCLOG("PinchGestureRecognizer::onTouchCancelled (touch id %d)", touch->getID());
    status = GestureStatus::FAILED;
    if (onPinch)
        onPinch(this); // "GestureStatus::FAILED"
    onTouchEnded(touch, ev);
}

void PinchGestureRecognizer::onTouchEnded(Touch* touch, Event* ev) 
{
    touches.erase(touch->getID());
    
    if (status == GestureStatus::CHANGED and touches.empty()) // all fingers lifted
    {
        status = GestureStatus::RECOGNIZED;
        if (onPinch)
            onPinch(this); // "GestureStatus::RECOGNIZED"
    }
}

float PinchGestureRecognizer::computePinchFactor(const TouchesMap& newTouches) const 
{
    auto it = touches.begin();
    auto pair1 = *(it++);
    auto pair2 = *(it);
    
    auto pointNew1 = newTouches.at(pair1.first);
    auto pointNew2 = newTouches.at(pair2.first);
    
    auto oldDist     = pair1.second.distance(pair2.second);
    auto currDist    = pointNew1.distance(pointNew2);
    
    return currDist / oldDist;
}

float PinchGestureRecognizer::computeAngle(const TouchesMap &newTouches) const
{
    auto it = touches.begin();
    auto pair1 = *(it++);
    auto pair2 = *it;
    
    auto pointNew1 = newTouches.at(pair1.first);
    auto pointNew2 = newTouches.at(pair2.first);
    
    auto dir     = pair1.second - pair2.second;
    auto currDir = pointNew1 - pointNew2;
    
    return computeSignedAngle(dir, currDir);
}

NS_CC_END