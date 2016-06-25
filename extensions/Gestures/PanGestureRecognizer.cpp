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

#include "PanGestureRecognizer.h"

NS_CC_BEGIN

PanGestureRecognizer* PanGestureRecognizer::create(uint fingerCount)
{
    auto r = new PanGestureRecognizer(fingerCount);
    if (r and r->init())
    {
        r->autorelease();
        return r;
    }
    CC_SAFE_DELETE(r);
    return nullptr;
}

PanGestureRecognizer::PanGestureRecognizer(uint fingers) : GestureRecognizer(fingers)
{
    //CCLOG("Constructor PanGestureRecognizer");
}

PanGestureRecognizer::~PanGestureRecognizer()
{
    //CCLOG("Destructor PanGestureRecognizer");
}

bool PanGestureRecognizer::onTouchBegan(Touch* touch, Event* ev) 
{
    if (touches.size() < fingerNumber) // touches storing
    {
        status = GestureStatus::POSSIBLE;
        touches.insert({touch->getID(), touch->getLocation()});

        if (touches.size() == fingerNumber) // acquired the wanted number of touches
        {
            status = GestureStatus::BEGAN;
            gestureLocation = mean(touches);
            if (onPan)
                onPan(this); // 'GestureStatus::BEGAN'
        }
        return true;
    }
    else
        return false; // no others touch tracking
}

void PanGestureRecognizer::onTouchMoved(Touch* touch, Event* ev) 
{
    if (touches.size() == fingerNumber) // wanted number of touches
    {
        status = GestureStatus::CHANGED;
        
        TouchesMap updatedTouches;
        updatedTouches.insert({touch->getID(), touch->getLocation()});
        
        for (auto& pair : touches) // add tracked points that not moved
            updatedTouches.insert({pair.first, pair.second});
        
        auto oldMedia = mean(touches);
        auto newMedia = mean(updatedTouches);
        gestureLocation = newMedia;
        traslation      = newMedia - oldMedia;
        touches = updatedTouches; // update touches
        //CCLOG("Pan traslation: (%f, %f)", traslation.x, traslation.y);
        if (onPan)
            onPan(this); // 'GestureStatus::CHANGED'
    }
}

void PanGestureRecognizer::onTouchCancelled(Touch* touch, Event* ev) 
{
    //CCLOG("PanGestureRecognizer::onTouchCancelled (touch id %d)", touch->getID());
    status = GestureStatus::FAILED;
    if (onPan)
        onPan(this); // 'GestureStatus::FAILED'
    onTouchEnded(touch, ev);
}

void PanGestureRecognizer::onTouchEnded(Touch* touch, Event* ev) 
{
    touches.erase(touch->getID());
    
    if (status == GestureStatus::CHANGED and touches.empty()) // all fingers were lift
    {
        status = GestureStatus::RECOGNIZED;
        if (onPan)
            onPan(this); // 'GestureStatus::RECOGNIZED'
    }
}

NS_CC_END

