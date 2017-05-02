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

#define SWIPE_TIMEOUT 0.3f // in seconds

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) // for test

#define SWIPE_X_DELTA      (visibleSize.width * 0.015f)
#define SWIPE_Y_DELTA      (visibleSize.width * 0.015f)
#define SWIPE_X_TOLLERANCE (visibleSize.width * 0.010f)
#define SWIPE_Y_TOLLERANCE (visibleSize.width * 0.010f)

#else // can be adjusted 

#define SWIPE_X_DELTA      (visibleSize.width * 0.04f)
#define SWIPE_Y_DELTA      (visibleSize.width * 0.04f)
#define SWIPE_X_TOLLERANCE (visibleSize.width * 0.02f)
#define SWIPE_Y_TOLLERANCE (visibleSize.width * 0.02f)

#endif

NS_CC_BEGIN

class SwipeGestureRecognizer : public GestureRecognizer
{
public:
    enum class SwipeStatus
    {
        SWIPE_NOT_DETECTED,
        SWIPE_UP,
        SWIPE_DOWN,
        SWIPE_LEFT,
        SWIPE_RIGHT
    };
    
    static SwipeGestureRecognizer* create();    
    std::function<void(SwipeGestureRecognizer*)> onSwipe {nullptr};
    SwipeStatus getSwipeDirection() {return swipeDirection;}
    
private:
    SwipeStatus swipeDirection {SwipeStatus::SWIPE_NOT_DETECTED};
    
    SwipeGestureRecognizer();
    virtual ~SwipeGestureRecognizer();
    
    void swipeCheck(Touch* touch);
    void timeout(float dt) override;
    
    bool onTouchBegan(Touch* touch, Event* ev) override;
    void onTouchMoved(Touch* touch, Event* ev) override;
    void onTouchCancelled(Touch* touch, Event* ev) override;
    void onTouchEnded(Touch* touch, Event* ev) override;
};

NS_CC_END