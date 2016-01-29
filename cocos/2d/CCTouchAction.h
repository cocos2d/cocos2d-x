//
//  CCTouchAction.h
//  cocos2d_libs
//
//  Created by kuwabara yuki on 2016/01/25.
//
//

#ifndef TouchSimulator_CCTouchAction_h
#define TouchSimulator_CCTouchAction_h

#include "base/CCTouch.h"
#include "math/Vec2.h"
#include "2d/CCAction.h"
#include "2d/CCActionInstant.h"
#include "2d/CCActionInterval.h"

NS_CC_BEGIN

/**
 * @class ActionTouchManager
 * @brief manages Touch instances for Action.
 * @details All action that handles Touch should issue and delete touch through this class.
 */
class CC_DLL ActionTouchManager
{
public:
    /** Returns a managed Touch.
     *
     * @return A managed Touch.
     */
    static cocos2d::Touch* createTouch();
    
    /** Returns an issued Touch with touch id.
     *
     * @param  id Touch id.
     * @return Returns an issued Touch that has given id, or nullptr.
     */
    static cocos2d::Touch* getTouch(int id);
    
    /** Deletes an issued Touch with touch id.
     *
     * @param id Touch id.
     */
    static void deleteTouch(int id);
    
    /** Deletes an issued Touch with Touch instance.
     *
     * @param touch Touch instance.
     */
    static void deleteTouch(cocos2d::Touch* touch);
    
    /** Returns not engaged touch id.
     *
     * @return available touch id.
     */
    static int getAvailableTouchId();
    
protected:
    ActionTouchManager(){}
    virtual ~ActionTouchManager(){}
    
    CC_DISALLOW_COPY_AND_ASSIGN(ActionTouchManager);
    
    /**
     * A container for issued touches.
     */
    static std::vector<cocos2d::Touch*> _claimedTouches;
};

/**
 * @class TouchActionInstant
 * @brief Base class for instant touch actions.
 * @details All instant touch action such as TouchBegan, TouchMoved. should extend this class.
 * @ingroup Actions
 */
class CC_DLL TouchActionInstant : public cocos2d::ActionInstant
{
public:
    bool initWithPosition(cocos2d::Touch* touch, cocos2d::Vec2 pos, const bool absolute = false);
    
    // Overrides
    virtual void update(float time) override;
    virtual cocos2d::ActionInstant* reverse() const override;
    virtual TouchActionInstant* clone() const override;
    
protected:
    TouchActionInstant(){}
    virtual ~TouchActionInstant(){}
    
    CC_DISALLOW_COPY_AND_ASSIGN(TouchActionInstant);
    
    cocos2d::Vec2 _baseTapPos;
    cocos2d::Touch* _touch = nullptr;
    EventTouch::EventCode _code;
    
    /**
     * define position as absolute or target relative position
     */
    bool _useAbsolutePosition = false;
    
    virtual void dispatchTouchEvent(cocos2d::EventTouch::EventCode code);
};

/**
 * @class TouchActionInterval
 * @brief Base class for touch actions with interval.
 * @details All interval touch action such as Swipe, Pinch. should extend this class.
 * @ingroup Actions
 */
class CC_DLL TouchActionInterval : public cocos2d::ActionInterval
{
public:
    // Overrides
    virtual void update(float time) override;
    virtual cocos2d::ActionInterval* reverse() const override;
    virtual TouchActionInterval* clone() const override;
    
protected:
    TouchActionInterval(){}
    virtual ~TouchActionInterval(){}
    
    CC_DISALLOW_COPY_AND_ASSIGN(TouchActionInterval);
    
    /**
     * define position as absolute or target relative position
     */
    bool _useAbsolutePosition = false;
};

/**
 * @class TouchBegan
 * @brief Performs beginning of a touch
 * @details Performs beginning of a touch with Touch instance.
 *          Touch instance is not deleted until it is used to TouchEnded or TouchCancelled.
 *          Otherwise, user has a responsibility to delete the instance.
 * @ingroup Actions
 */
class CC_DLL TouchBegan : public TouchActionInstant
{
public:
    static TouchBegan* create(cocos2d::Touch* touch);
    static TouchBegan* create(cocos2d::Touch* touch, cocos2d::Vec2 pos, const bool absolute = false);
    
CC_CONSTRUCTOR_ACCESS:
    TouchBegan() {
        _code = cocos2d::EventTouch::EventCode::BEGAN;
    }
    virtual ~TouchBegan(){}
};

/**
 * @class TouchCancelled
 * @brief Performs cancellation of a touch
 * @details Performs cancellation of a touch with Touch instance.
 *          Given Touch instance is deleted after touch event was dispatched.
 * @ingroup Actions
 */
class CC_DLL TouchCancelled : public TouchActionInstant
{
public:
    static TouchCancelled* create(cocos2d::Touch* touch);
    static TouchCancelled* create(cocos2d::Touch* touch, cocos2d::Vec2 pos, const bool absolute = false);
    
CC_CONSTRUCTOR_ACCESS:
    TouchCancelled() {
        _code = cocos2d::EventTouch::EventCode::CANCELLED;
    }
    virtual ~TouchCancelled(){}
};

/**
 * @class TouchEnded
 * @brief Performs end of a touch
 * @details Performs end of a touch with Touch instance.
 *          Given Touch instance is deleted after touch event was dispatched.
 * @ingroup Actions
 */
class CC_DLL TouchEnded : public TouchActionInstant
{
public:
    static TouchEnded* create(cocos2d::Touch* touch);
    static TouchEnded* create(cocos2d::Touch* touch, cocos2d::Vec2 pos, const bool absolute = false);
    
CC_CONSTRUCTOR_ACCESS:
    TouchEnded() {
        _code = cocos2d::EventTouch::EventCode::ENDED;
    }
    virtual ~TouchEnded(){}
};

/**
 * @class TouchMoved
 * @brief Performs movement of a touch
 * @details Performs movement of a touch with Touch instance.
 *          Touch instance is not deleted until it is used to TouchEnded or TouchCancelled.
 *          Otherwise, user has a responsibility to delete the instance.
 *          Also if the instance has not performed TouchBegin, unclaimed instance may not perform following touch actions.
 * @ingroup Actions
 */
class CC_DLL TouchMoved : public TouchActionInstant
{
public:
    static TouchMoved* create(cocos2d::Touch* touch);
    static TouchMoved* create(cocos2d::Touch* touch, cocos2d::Vec2 pos, const bool absolute = false);
    
CC_CONSTRUCTOR_ACCESS:
    TouchMoved() {
        _code = cocos2d::EventTouch::EventCode::MOVED;
    }
    virtual ~TouchMoved(){}
};


/**
 * @class Tap
 * @brief Performs tap gesture
 * @details Performs tap gesture.
 *          A touch instance is automatically handled.
 * @ingroup Actions
 */
class CC_DLL Tap : public cocos2d::Sequence
{
public:
    static Tap* create();
    static Tap* create(float duration, cocos2d::Vec2 pos, const bool absolute = false);
    static Tap* createWithTwoActions(cocos2d::FiniteTimeAction *actionOne, cocos2d::FiniteTimeAction *actionTwo);
};

/**
 * @class Swipe
 * @brief Base class of swipe action variants
 * @details All swipe actions should inherit this class.
 * @ingroup Actions
 */
class CC_DLL Swipe : public cocos2d::ActionInterval
{
protected:
    cocos2d::Touch* _touch = nullptr;
    cocos2d::Vec2 _firstPosition;
    cocos2d::Vec2 _currentPosition;
    
    void dispatchTouchEvent(cocos2d::EventTouch::EventCode code);
    
    /**
     * keeps touches in screen if they went over the screen bound.
     */
    void keepTouchScreen();
    
CC_CONSTRUCTOR_ACCESS:
    Swipe(){};
    ~Swipe(){};
};

/**
 * @class SwipeBetween
 * @brief Performs swipe between specific targets
 * @details It treats xy position as absolute position.
 *          The Target node's position is not considered.
 *          Touch instances are automatically handled.
 * @ingroup Actions
 */
class CC_DLL SwipeBetween : public Swipe
{
public:
    static SwipeBetween* create(float duration, cocos2d::Vec2 from, cocos2d::Vec2 to);
    
    bool initWithPositions(float duration, cocos2d::Vec2 from, cocos2d::Vec2 to);
    void update(float dt);
    
CC_CONSTRUCTOR_ACCESS:
    SwipeBetween(){};
    ~SwipeBetween(){};
    
private:
    cocos2d::Vec2 _firstPosition;
    cocos2d::Vec2 _positionDelta;
};

/**
 * @class SwipeBy
 * @brief Performs swipe from target's position for specific distance.
 * @details Origin of xy position will be target's position. Touche instances are automatically handled.
 * @ingroup Actions
 */
class CC_DLL SwipeBy : public Swipe
{
public:
    static SwipeBy* create(float duration, cocos2d::Vec2 distance);
    
    bool initWithPosition(float duration, cocos2d::Vec2 distance);
    void update(float dt);
    
CC_CONSTRUCTOR_ACCESS:
    SwipeBy(){};
    ~SwipeBy(){};
    
private:
    cocos2d::Vec2 _positionDelta;
};

/**
 * @class SwipeTo
 * @brief Performs swipe from target's position to specific position.
 * @details Origin of xy position will be target's position. Touche instances are automatically handled.
 * @ingroup Actions
 */
class CC_DLL SwipeTo : public Swipe
{
public:
    static SwipeTo* create(float duration, cocos2d::Vec2 to);
    
    bool initWithPosition(float duration, cocos2d::Vec2 to);
    void update(float dt);
    
CC_CONSTRUCTOR_ACCESS:
    SwipeTo(){};
    ~SwipeTo(){};
    
private:
    cocos2d::Vec2 _destPosition;
    cocos2d::Vec2 _positionDelta;
};

/**
 * @class Pinch
 * @brief Base class of pinch action variants
 * @details All pinch actions should inherit this class.
 * @ingroup Actions
 */
class CC_DLL Pinch : public TouchActionInterval
{
public:
    cocos2d::Touch* _touch1 = nullptr;
    cocos2d::Touch* _touch2 = nullptr;
    cocos2d::Vec2 _currentPosition1;
    cocos2d::Vec2 _currentPosition2;
    
    bool initWithPositions(float duration, cocos2d::Vec2 center, float initialDistance, float pinchDistance, const bool absolute = false, const float degree = 0.0f);
    
    void update(float dt);
    
    void dispatchTouchEvent(cocos2d::EventTouch::EventCode code);
    
    /**
     * keeps touches in screen if they went over the screen bound.
     */
    void keepTouchScreen();
    
protected:
    cocos2d::Vec2 _center;
    cocos2d::Vec2 _targetFirstPosition;
    cocos2d::Vec2 _firstPosition1;
    cocos2d::Vec2 _firstPosition2;
    float _radian;
    float _distanceDelta;
    
    virtual void addDeltaDistance(float dt) = 0;
};

/**
 * @class PinchIn
 * @brief Performs pinch in
 * @details Touch instances are automatically handled.
 * @ingroup Actions
 */
class CC_DLL PinchIn : public Pinch
{
public:
    static PinchIn* create(float duration, cocos2d::Vec2 center, float initialDistance, float pinchDistance, const bool absolute = false, const float degree = 0.0f);
    
CC_CONSTRUCTOR_ACCESS:
    PinchIn(){};
    ~PinchIn(){};
    
protected:
    virtual void addDeltaDistance(float dt);
};

/**
 * @class PinchOut
 * @brief Performs pinch out
 * @details Touch instances are automatically handled.
 * @ingroup Actions
 */
class CC_DLL PinchOut : public Pinch
{
public:
    static PinchOut* create(float duration, cocos2d::Vec2 center, float initialDistance, float pinchDistance, const bool absolute = false, const float degree = 0.0f);
    
CC_CONSTRUCTOR_ACCESS:
    PinchOut(){};
    ~PinchOut(){};
    
protected:
    virtual void addDeltaDistance(float dt);
};

NS_CC_END

#endif /* TouchSimulator_CCTouchAction_h */
