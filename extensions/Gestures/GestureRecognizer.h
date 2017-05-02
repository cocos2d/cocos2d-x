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

#include <algorithm>
#include <vector>
#include <unordered_map>
#include "cocos2d.h"

using TouchesMap = std::unordered_map<int, cocos2d::Point>;

/**
 * Discrete   Gestures: Long press, Tap, Swipe
 * Continuous Gestures: Pinch, Pan
 **/

enum class GestureStatus
{
    POSSIBLE,   // initial state
    RECOGNIZED, // recognized gesture (ended in the continuous gesture case)
    FAILED,     // recognition failed
    BEGAN,      // continuous gesture began
    CHANGED,    // continuous gesture change state
    CANCELED    // continuous gesture canceled
};

#define GESTURE_DEBUG_AREA   (1<<0)
#define GESTURE_DEBUG_POINTS (1<<1) 
#define GESTURE_DEBUG_ALL    (0XFFFFFFFF)
#define GESTURE_TIMEOUT_KEY "GestureRecognizerTimeoutKey"

NS_CC_BEGIN

class GestureRecognizer : public Node 
{
public:
    static std::vector<Color4F> touchColors;
    
    GestureRecognizer(uint fingers = 1);
    virtual ~GestureRecognizer();
    
    /**
     * 
     * @param mode enable-disable debug mode
     * @param mask specify what informations will be drawn
     */
    void setDebugMode(bool mode, uint mask = GESTURE_DEBUG_ALL);
    bool isDebugModeEnabled();
    
    // getters
    GestureStatus  getStatus()  const {return status;}
    Point getGestureLocation() const {return gestureLocation;}
    
    // setters
    void setEnabled(bool _enabled) {enabled = _enabled;}
    void setSwallowTouches(bool swallow);
    
    /**
     * 
     * @param enabled If enabled the content size of the recognizer will match with it's parent one
     */
    void setFillParentEnabled(bool enabled);
    

    /**
     * Automatically disable the fill parent feature
     * @param contentSize
     */
    virtual void setContentSize(const Size& contentSize);
    
protected:    
    // Dati membro
    bool enabled {true}; // if false the recognizer does not receive the touches
    bool isFillParentEnabled {true};
    const uint fingerNumber;
    Size visibleSize;
    EventListenerTouchOneByOne* listener {nullptr};
    Point gestureLocation {Point::ZERO};
    TouchesMap touches; // key touch id -> value location of the point
    GestureStatus status {GestureStatus::POSSIBLE};
    float timeoutSeconds {0}; // timeout for gesture recognition
    
    // Debug stuff
    uint debugMask {0};
    DrawNode* debugNode {nullptr};
    
    bool isTouchInNode(Touch* t);
    void scheduleTimeout(std::function<void(float)> func);
    virtual void timeout(float dt){};
    Point mean(const TouchesMap& map) const;
    
    // Pure virtual function implemented by subclasses
    virtual bool onTouchBegan(Touch* touch, Event* ev)     = 0;
    virtual void onTouchMoved(Touch* touch, Event* ev)     = 0;
    virtual void onTouchCancelled(Touch* touch, Event* ev) = 0;
    virtual void onTouchEnded(Touch* touch, Event* ev)     = 0; 
    virtual void update(float delta);
    
private:
    void addTouchListener();
    void addDebugArea();
    void resetDebugNode();
    
    /*
     * Functions linked to the EventListenerTouchOneByOne
     */
    virtual bool _onTouchBegan(Touch* touch, Event* ev);
    virtual void _onTouchMoved(Touch* touch, Event* ev);
    virtual void _onTouchCancelled(Touch* touch, Event* ev);
    virtual void _onTouchEnded(Touch* touch, Event* ev);
};

NS_CC_END