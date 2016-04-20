/****************************************************************************
Copyright (c) 2016 Yuki Kuwabara <do_low@hotmail.com>

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

#include "CCTouchAction.h"

#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"

USING_NS_CC;

# pragma mark ActionTouchManager

std::vector<Touch*> ActionTouchManager::_claimedTouches = {};

Touch* ActionTouchManager::createTouch()
{
    Touch* touch =  new (std::nothrow) Touch();
    touch->setTouchInfo(getAvailableTouchId(), 0.0f, 0.0f);
    _claimedTouches.push_back(touch);
    
    return touch;
}

cocos2d::Touch* ActionTouchManager::getTouch(int id)
{
    std::vector<Touch*>::iterator it;
    it = std::find_if(_claimedTouches.begin(), _claimedTouches.end(), [id](Touch* t){ return t->getID() == id; });
    if (it == _claimedTouches.end())
        return nullptr;
    
    return *it;
}

void ActionTouchManager::deleteTouch(int id)
{
    std::vector<cocos2d::Touch*>::iterator it;
    it = std::find_if(_claimedTouches.begin(), _claimedTouches.end(), [id](Touch* t){ return t->getID() == id; });
    if (it == _claimedTouches.end())
        return;
    
    // release pointer
    (*it)->autorelease();
    // then invalidate iterator
    _claimedTouches.erase(it);
}
void ActionTouchManager::deleteTouch(Touch* touch)
{
    deleteTouch(touch->getID());
}

int ActionTouchManager::getAvailableTouchId()
{
    int id = 0;
    std::vector<Touch*>::iterator it = _claimedTouches.begin();
    
    while (it != _claimedTouches.end()) {
        id++;
        it = std::find_if(_claimedTouches.begin(), _claimedTouches.end(), [&id](Touch* t){ return t->getID() == id; });
    }
    
    return id;
}

# pragma mark -
# pragma mark TouchActionInstant

bool TouchActionInstant::initWithPosition(cocos2d::Touch* touch, Vec2 pos, const bool absolute/* = false*/)
{
    _touch      = touch;
    _baseTapPos = pos;
    _useAbsolutePosition = absolute;
    
    return true;
}

void TouchActionInstant::update(float time)
{
    CC_UNUSED_PARAM(time);
    
    if (_touch == nullptr)
        return;
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 tapPosition = _baseTapPos;
    
    if (!_useAbsolutePosition && _target)
        tapPosition += _target->convertToWorldSpaceAR(_target->getAnchorPoint());
    
    tapPosition = Director::getInstance()->convertToGL(tapPosition);
    
    // culling
    if (tapPosition.x < 0.0f || tapPosition.y < 0.0f ||
        tapPosition.x > visibleSize.width || tapPosition.y > visibleSize.height) {
        return;
    }
    
    _touch->setTouchInfo(_touch->getID(), tapPosition.x, tapPosition.y);
    
    dispatchTouchEvent(_code);
}

ActionInstant* TouchActionInstant::reverse() const
{
    CCASSERT(false, "TouchActionInstant doesn't support the 'reverse' method");
    return nullptr;
}

TouchActionInstant* TouchActionInstant::clone() const
{
    return nullptr;
}


void TouchActionInstant::dispatchTouchEvent(EventTouch::EventCode code)
{
    EventDispatcher* eventDispatcher = nullptr;
    if (_target)
        eventDispatcher = _target->getEventDispatcher();
    else
        eventDispatcher = Director::getInstance()->getEventDispatcher();
    
    EventTouch touchEvent;
    touchEvent.setTouches({_touch});
    touchEvent.setEventCode(code);
    eventDispatcher->dispatchEvent(&touchEvent);
    
    if (code == EventTouch::EventCode::ENDED ||
        code == EventTouch::EventCode::CANCELLED) {
        ActionTouchManager::deleteTouch(_touch);
    }
}

# pragma mark TouchActionInterval

void TouchActionInterval::update(float time)
{
}

ActionInterval* TouchActionInterval::reverse() const
{
    CCASSERT(false, "TouchActionInterval doesn't support the 'reverse' method");
    return nullptr;
}

TouchActionInterval* TouchActionInterval::clone() const
{
    return nullptr;
}

# pragma mark -
# pragma mark TouchBegan

TouchBegan* TouchBegan::create(Touch* touch)
{
    return TouchBegan::create(touch, Vec2::ZERO);
}
TouchBegan* TouchBegan::create(Touch* touch, const Vec2 pos, const bool absolute/* = false*/)
{
    TouchBegan* ret = new (std::nothrow) TouchBegan();
    if (ret && ret->initWithPosition(touch, pos, absolute))
        ret->autorelease();
    
    return ret;
}

# pragma mark TouchCancelled

TouchCancelled* TouchCancelled::create(Touch* touch)
{
    return TouchCancelled::create(touch, Vec2::ZERO);
}
TouchCancelled* TouchCancelled::create(Touch* touch, const Vec2 pos, const bool absolute/* = false*/)
{
    TouchCancelled* ret = new (std::nothrow) TouchCancelled();
    if (ret && ret->initWithPosition(touch, pos, absolute))
        ret->autorelease();
    
    return ret;
}

# pragma mark TouchEnded

TouchEnded* TouchEnded::create(Touch* touch)
{
    return TouchEnded::create(touch, Vec2::ZERO);
}
TouchEnded* TouchEnded::create(Touch* touch, const Vec2 pos, const bool absolute/* = false*/)
{
    TouchEnded* ret = new (std::nothrow) TouchEnded();
    if (ret && ret->initWithPosition(touch, pos, absolute))
        ret->autorelease();
    
    return ret;
}

# pragma mark TouchMoved

TouchMoved* TouchMoved::create(Touch* touch)
{
    return TouchMoved::create(touch, Vec2::ZERO);
}
TouchMoved* TouchMoved::create(Touch* touch, const Vec2 pos, const bool absolute/* = false*/)
{
    TouchMoved* ret = new (std::nothrow) TouchMoved();
    if (ret && ret->initWithPosition(touch, pos, absolute))
        ret->autorelease();
    
    return ret;
}

# pragma mark -
# pragma mark Tap

Tap* Tap::create()
{
    return Tap::create(0.0f, Vec2::ZERO, false);
}
Tap* Tap::create(float duration, Vec2 pos, const bool absolute/* = false*/)
{
    Touch* touch = ActionTouchManager::createTouch();
    if (duration > 0.0f)
        return Tap::createWithTwoActions(TouchBegan::create(touch, pos, absolute),
                                         Tap::createWithTwoActions(DelayTime::create(duration), TouchEnded::create(touch, pos, absolute)));
    else
        return Tap::createWithTwoActions(TouchBegan::create(touch, pos, absolute), TouchEnded::create(touch, pos, absolute));
}

Tap* Tap::createWithTwoActions(FiniteTimeAction *actionOne, FiniteTimeAction *actionTwo)
{
    Tap *sequence = new (std::nothrow) Tap();
    sequence->initWithTwoActions(actionOne, actionTwo);
    sequence->autorelease();
    
    return sequence;
}

# pragma mark -
# pragma mark Swipe

void Swipe::dispatchTouchEvent(EventTouch::EventCode code)
{
    Vec2 uiPos = Director::getInstance()->convertToUI(_currentPosition);
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    
    _touch->setTouchInfo(_touch->getID(), uiPos.x, uiPos.y);
    
    EventTouch touchEvent;
    touchEvent.setTouches({_touch});
    touchEvent.setEventCode(code);
    eventDispatcher->dispatchEvent(&touchEvent);
}

void Swipe::keepTouchScreen()
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    
    if (_currentPosition.x < 0.0f) _currentPosition.x = 0.0f;
    if (_currentPosition.y < 0.0f) _currentPosition.y = 0.0f;
    if (_currentPosition.x > visibleSize.width)  _currentPosition.x = visibleSize.width;
    if (_currentPosition.y > visibleSize.height) _currentPosition.y = visibleSize.height;
}

# pragma mark SwipeBetween

SwipeBetween* SwipeBetween::create(float duration, Vec2 from, Vec2 to)
{
    SwipeBetween* swipe = new (std::nothrow) SwipeBetween();
    swipe->initWithPositions(duration, from, to);
    swipe->autorelease();
    return swipe;
}

bool SwipeBetween::initWithPositions(float duration, Vec2 from, Vec2 to)
{
    ActionInterval::initWithDuration(duration);
    
    _firstPosition = from;
    _positionDelta = to - _firstPosition;
    
    return true;
}

void SwipeBetween::update(float dt)
{
    Vec2 adjustedFirstPosition = _firstPosition;
    if (_target != nullptr)
        adjustedFirstPosition += _target->getPosition();
    
    if (dt < 1.0f && _touch == nullptr) {
        _currentPosition = adjustedFirstPosition;
        _touch = ActionTouchManager::createTouch();
        dispatchTouchEvent(EventTouch::EventCode::BEGAN);
    }
    else {
        if (_currentPosition == _firstPosition + _positionDelta)
            return;
        
        EventTouch::EventCode code = EventTouch::EventCode::MOVED;
        
        if (dt >= 1.0f) {
            dt = 1.0f;
            code = EventTouch::EventCode::ENDED;
        }
        
        _currentPosition = adjustedFirstPosition + (_positionDelta * dt);
        
        keepTouchScreen();
        
        dispatchTouchEvent(code);
        
        if (code == EventTouch::EventCode::ENDED)
            ActionTouchManager::deleteTouch(_touch);
    }
}

# pragma mark SwipeBy

SwipeBy* SwipeBy::create(float duration, Vec2 distance)
{
    SwipeBy* swipe = new (std::nothrow) SwipeBy();
    swipe->initWithPosition(duration, distance);
    swipe->autorelease();
    return swipe;
}

bool SwipeBy::initWithPosition(float duration, Vec2 distance)
{
    ActionInterval::initWithDuration(duration);
    
    _positionDelta = distance;
    
    return true;
}

void SwipeBy::update(float dt)
{
    // SwipeBy requires swiping target
    if (!_target)
        return;
    
    Vec2 targetWorldPos = _target->convertToWorldSpaceAR(_target->getAnchorPoint());
    
    if (dt < 1.0f && _touch == nullptr) {
        _currentPosition = _firstPosition = targetWorldPos;
        _touch = ActionTouchManager::createTouch();
        dispatchTouchEvent(EventTouch::EventCode::BEGAN);
    }
    else {
        if (_touch == nullptr || _currentPosition == _firstPosition + _positionDelta)
            return;
        
        EventTouch::EventCode code = EventTouch::EventCode::MOVED;
        
        if (dt >= 1.0f) {
            dt = 1.0f;
            code = EventTouch::EventCode::ENDED;
        }
        
        _currentPosition = _firstPosition + _positionDelta * dt;
        
        keepTouchScreen();
        
        dispatchTouchEvent(code);
        
        if (code == EventTouch::EventCode::ENDED)
            ActionTouchManager::deleteTouch(_touch);
    }
}


# pragma mark SwipeTo

SwipeTo* SwipeTo::create(float duration, Vec2 to)
{
    SwipeTo* swipe = new (std::nothrow) SwipeTo();
    swipe->initWithPosition(duration, to);
    swipe->autorelease();
    return swipe;
}

bool SwipeTo::initWithPosition(float duration, Vec2 to)
{
    ActionInterval::initWithDuration(duration);
    
    _destPosition = to;
    
    return true;
}

void SwipeTo::update(float dt)
{
    // SwipeTo requires swiping target
    if (!_target)
        return;
    
    Vec2 targetWorldPos = _target->convertToWorldSpaceAR(_target->getAnchorPoint());
    
    if (dt < 1.0f && _touch == nullptr) {
        _currentPosition = _firstPosition = targetWorldPos;
        _positionDelta = _destPosition - _currentPosition;
        _touch = ActionTouchManager::createTouch();
        dispatchTouchEvent(EventTouch::EventCode::BEGAN);
    }
    else {
        if (_touch == nullptr || _currentPosition == _firstPosition + _positionDelta)
            return;
        
        EventTouch::EventCode code = EventTouch::EventCode::MOVED;
        
        if (dt >= 1.0f) {
            dt = 1.0f;
            code = EventTouch::EventCode::ENDED;
        }
        
        _currentPosition = _firstPosition + _positionDelta * dt;
        
        keepTouchScreen();
        
        dispatchTouchEvent(code);
        
        ActionTouchManager::deleteTouch(_touch);
    }
}

# pragma mark -
# pragma mark Pinch

bool Pinch::initWithPositions(float duration, Vec2 center, float initialDistance, float pinchDistance, const bool absolute, const float degree)
{
    ActionInterval::initWithDuration(duration);
    
    _useAbsolutePosition = absolute;
    _distanceDelta       = pinchDistance;
    _center              = center;
    _radian              = CC_DEGREES_TO_RADIANS(degree);
    _firstPosition1 = _firstPosition2 = center;
    
    float eachInitialDistance = initialDistance * 0.5f;
    
    _firstPosition1.x -= eachInitialDistance;
    _firstPosition2.x += eachInitialDistance;
    
    return true;
}

void Pinch::dispatchTouchEvent(EventTouch::EventCode code)
{
    Vec2 uiPos1 = Director::getInstance()->convertToUI(_currentPosition1);
    Vec2 uiPos2 = Director::getInstance()->convertToUI(_currentPosition2);
    
    EventDispatcher* eventDispatcher = nullptr;
    if (_target != nullptr)
        eventDispatcher = _target->getEventDispatcher();
    else
        eventDispatcher = Director::getInstance()->getEventDispatcher();
    
    _touch1->setTouchInfo(_touch1->getID(), uiPos1.x, uiPos1.y);
    _touch2->setTouchInfo(_touch2->getID(), uiPos2.x, uiPos2.y);
    
    EventTouch touchEvent;
    touchEvent.setTouches({_touch1, _touch2});
    touchEvent.setEventCode(code);
    eventDispatcher->dispatchEvent(&touchEvent);
}

void Pinch::update(float dt)
{
    if (dt < 1.0f && _touch1 == nullptr) {
        _targetFirstPosition = Vec2::ZERO;
        
        if (_target && !_useAbsolutePosition)
            _targetFirstPosition += _target->convertToWorldSpaceAR(_target->getAnchorPoint());
            
        _firstPosition1 += _targetFirstPosition;
        _firstPosition2 += _targetFirstPosition;
        _currentPosition1 = _firstPosition1;
        _currentPosition2 = _firstPosition2;
        
        Vec2 relCenter = _center + _targetFirstPosition;
        
        _currentPosition1.rotate(relCenter, _radian);
        _currentPosition2.rotate(relCenter, _radian);
        
        _touch1 = ActionTouchManager::createTouch();
        _touch2 = ActionTouchManager::createTouch();
        
        keepTouchScreen();
        
        dispatchTouchEvent(EventTouch::EventCode::BEGAN);
    }
    else {
        EventTouch::EventCode code = (dt >= 1.0f)
        ? EventTouch::EventCode::ENDED
        : EventTouch::EventCode::MOVED;
        
        _currentPosition1 = _firstPosition1;
        _currentPosition2 = _firstPosition2;
        
        addDeltaDistance(dt);
        
        Vec2 relCenter = _center + _targetFirstPosition;
        
        _currentPosition1.rotate(relCenter, _radian);
        _currentPosition2.rotate(relCenter, _radian);
        
        keepTouchScreen();
        
        dispatchTouchEvent(code);
        
        if (code == EventTouch::EventCode::ENDED) {
            ActionTouchManager::deleteTouch(_touch1);
            ActionTouchManager::deleteTouch(_touch2);
        }
    }
}

void Pinch::keepTouchScreen()
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    
    if (_currentPosition1.x < 0.0f) _currentPosition1.x = 0.0f;
    if (_currentPosition1.y < 0.0f) _currentPosition1.y = 0.0f;
    if (_currentPosition1.x > visibleSize.width)  _currentPosition1.x = visibleSize.width;
    if (_currentPosition1.y > visibleSize.height) _currentPosition1.y = visibleSize.height;
    
    if (_currentPosition2.x < 0.0f) _currentPosition2.x = 0.0f;
    if (_currentPosition2.y < 0.0f) _currentPosition2.y = 0.0f;
    if (_currentPosition2.x > visibleSize.width)  _currentPosition2.x = visibleSize.width;
    if (_currentPosition2.y > visibleSize.height) _currentPosition2.y = visibleSize.height;
}

# pragma mark PinchIn

PinchIn* PinchIn::create(float duration, Vec2 center, float initialDistance, float pinchDistance, const bool absolute, const float degree)
{
    PinchIn* pinch = new (std::nothrow) PinchIn();
    pinch->initWithPositions(duration, center, initialDistance, pinchDistance, absolute, degree);
    pinch->autorelease();
    return pinch;
}

void PinchIn::addDeltaDistance(float dt)
{
    if (dt >= 1.0f)
        dt = 1.0f;
    
    _currentPosition1.x += _distanceDelta * dt;
    _currentPosition2.x -= _distanceDelta * dt;
}

# pragma mark PinchOut

PinchOut* PinchOut::create(float duration, Vec2 center, float initialDistance, float pinchDistance, const bool absolute, const float degree)
{
    PinchOut* pinch = new (std::nothrow) PinchOut();
    pinch->initWithPositions(duration, center, initialDistance, pinchDistance, absolute, degree);
    pinch->autorelease();
    return pinch;
}

void PinchOut::addDeltaDistance(float dt)
{
    if (dt >= 1.0f)
        dt = 1.0f;
    
    _currentPosition1.x -= _distanceDelta * dt;
    _currentPosition2.x += _distanceDelta * dt;
}
