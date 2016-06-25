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

#define TAP_MOVE_DELTA 100
#define TAP_MAX_BEETWEEN_TOUCHES 0.5f // in seconds

NS_CC_BEGIN

struct TouchInfo
{
    TouchInfo(Point p, uint c = 0)
    {
        point = p;
        touchCount = c;
    }
    Point point {0, 0};
    uint touchCount {0};
};

class TapGestureRecognizer : public GestureRecognizer
{
public:
    static TapGestureRecognizer* create(uint fingerCount = 1, uint tapNumber = 1, float maxTime = TAP_MAX_BEETWEEN_TOUCHES);    
    std::function<void(TapGestureRecognizer*)> onTap;
    
private:
    std::unordered_map<int, int> touchesCount; // for each id stores the tap count
    const uint tapNumber;
    uint tapCount {0};
    
    TapGestureRecognizer(uint fingerCount, uint tapNumber, float maxTime);
    virtual ~TapGestureRecognizer();
    
    // helper
    bool touchEndCheck(Touch* touch);
    bool existNeighbor(Point aPoint, int& touchIndex);
    void reset(float dt = 0); // reset recognizer status
    
    bool onTouchBegan(Touch* touch, Event* ev) override;
    void onTouchMoved(Touch* touch, Event* ev) override;
    void onTouchCancelled(Touch* touch, Event* ev) override;
    void onTouchEnded(Touch* touch, Event* ev) override;
};

NS_CC_END