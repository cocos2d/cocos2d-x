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

#pragma once

#include "GestureRecognizer.h"

NS_CC_BEGIN

class PinchGestureRecognizer : public GestureRecognizer
{
public:
    static PinchGestureRecognizer* create();
    std::function<void(PinchGestureRecognizer* recognizer)> onPinch;
    
    float getPinchFactor()     const {return pinchFactor;}
    float getPinchRotation()   const {return pinchRotation;}
    Vec2  getPinchTraslation() const {return pinchTraslation;}
    
private:
    float pinchFactor     {0};
    float pinchRotation   {0};
    Vec2  pinchTraslation {Vec2::ZERO};
    
    PinchGestureRecognizer();
    virtual ~PinchGestureRecognizer();
    
    float computePinchFactor(const TouchesMap& newTouches) const;
    float computeAngle(const TouchesMap& newTouches) const;
    
    bool onTouchBegan(Touch* touch, Event* ev) override;
    void onTouchMoved(Touch* touch, Event* ev) override;
    void onTouchCancelled(Touch* touch, Event* ev) override;
    void onTouchEnded(Touch* touch, Event* ev) override;
};

NS_CC_END
