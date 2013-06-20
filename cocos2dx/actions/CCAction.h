/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

#ifndef __ACTIONS_CCACTION_H__
#define __ACTIONS_CCACTION_H__

#include "cocoa/CCObject.h"
#include "cocoa/CCGeometry.h"
#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

enum {
    //! Default tag
    kActionTagInvalid = -1,
};

/**
 * @addtogroup actions
 * @{
 */

/** 
@brief Base class for Action objects.
 */
class CC_DLL Action : public Clonable, public Object
{
public:
    Action(void);

    virtual ~Action(void);

    const char* description();

	/** returns a clone of action */
	virtual Action* clone() const = 0;

    //! return true if the action has finished
    virtual bool isDone(void);

    //! called before the action start. It will also set the target.
    virtual void startWithTarget(Node *pTarget);

    /** 
    called after the action has finished. It will set the 'target' to nil.
    IMPORTANT: You should never call "[action stop]" manually. Instead, use: "target->stopAction(action);"
    */
    virtual void stop(void);

    //! called every frame with it's delta time. DON'T override unless you know what you are doing.
    virtual void step(float dt);

    /** 
    called once per frame. time a value between 0 and 1

    For example: 
    - 0 means that the action just started
    - 0.5 means that the action is in the middle
    - 1 means that the action is over
    */
    virtual void update(float time);
    
    inline Node* getTarget(void) { return _target; }
    /** The action will modify the target properties. */
    inline void setTarget(Node *pTarget) { _target = pTarget; }
    
    inline Node* getOriginalTarget(void) { return _originalTarget; } 
    /** Set the original target, since target can be nil.
    Is the target that were used to run the action. Unless you are doing something complex, like ActionManager, you should NOT call this method.
    The target is 'assigned', it is not 'retained'.
    @since v0.8.2
    */
    inline void setOriginalTarget(Node *pOriginalTarget) { _originalTarget = pOriginalTarget; }

    inline int getTag(void) { return _tag; }
    inline void setTag(int nTag) { _tag = nTag; }

public:

protected:
    Node    *_originalTarget;
    /** The "target".
    The target will be set with the 'startWithTarget' method.
    When the 'stop' method is called, target will be set to nil.
    The target is 'assigned', it is not 'retained'.
    */
    Node    *_target;
    /** The action tag. An identifier of the action */
    int     _tag;
};

/** 
@brief 
 Base class actions that do have a finite time duration.
 Possible actions:
   - An action with a duration of 0 seconds
   - An action with a duration of 35.5 seconds

 Infinite time actions are valid
 */
class CC_DLL FiniteTimeAction : public Action
{
public:
    FiniteTimeAction()
	: _duration(0)
    {}
    virtual ~FiniteTimeAction(){}
    //! get duration in seconds of the action
    inline float getDuration(void) { return _duration; }
    //! set duration in seconds of the action
    inline void setDuration(float duration) { _duration = duration; }

    /** returns a new reversed action */
    virtual FiniteTimeAction* reverse() const = 0;

	/** returns a clone of action */
	virtual FiniteTimeAction* clone() const = 0;

protected:
    //! duration in seconds
    float _duration;
};

class ActionInterval;
class RepeatForever;

/** 
 @brief Changes the speed of an action, making it take longer (speed>1)
 or less (speed<1) time.
 Useful to simulate 'slow motion' or 'fast forward' effect.
 @warning This action can't be Sequenceable because it is not an IntervalAction
 */
class CC_DLL Speed : public Action
{
public:
    Speed();
    virtual ~Speed(void);

    inline float getSpeed(void) { return _speed; }
    /** alter the speed of the inner function in runtime */
    inline void setSpeed(float fSpeed) { _speed = fSpeed; }

    /** initializes the action */
    bool initWithAction(ActionInterval *pAction, float fSpeed);

    virtual Object* copyWithZone(Zone *pZone);

	/** returns a new clone of the action */
	virtual Speed* clone() const;
    /** returns a new reversed action */
    virtual Speed* reverse(void) const;

    virtual void startWithTarget(Node* pTarget);
    virtual void stop();
    virtual void step(float dt);
    virtual bool isDone(void);

    void setInnerAction(ActionInterval *pAction);

    inline ActionInterval* getInnerAction()
    {
        return _innerAction;
    }

public:
    /** create the action */
    static Speed* create(ActionInterval* pAction, float fSpeed);
protected:
    float _speed;
    ActionInterval *_innerAction;
};

/** 
@brief Follow is an action that "follows" a node.

Eg:
layer->runAction(Follow::actionWithTarget(hero));

Instead of using Camera as a "follower", use this action instead.
@since v0.99.2
*/
class CC_DLL Follow : public Action
{
public:
    Follow()
		: _followedNode(NULL)
        , _boundarySet(false)
        , _boundaryFullyCovered(false)        
        , _leftBoundary(0.0)
        , _rightBoundary(0.0)
        , _topBoundary(0.0)
        , _bottomBoundary(0.0)
		, _worldRect(RectZero)
    {}
    virtual ~Follow(void);
    
    inline bool isBoundarySet(void) { return _boundarySet; }
    /** alter behavior - turn on/off boundary */
    inline void setBoudarySet(bool bValue) { _boundarySet = bValue; }

    /** initializes the action with a set boundary */
    bool initWithTarget(Node *pFollowedNode, const Rect& rect = RectZero);

    virtual Object* copyWithZone(Zone *pZone);
	/** returns a clone of action */
	virtual Follow* clone() const;
    virtual void step(float dt);
    virtual bool isDone(void);
    virtual void stop(void);

public:
    /** creates the action with a set boundary,
    It will work with no boundary if @param rect is equal to RectZero.
    */
    static Follow* create(Node *pFollowedNode, const Rect& rect = RectZero);
protected:
    // node to follow
    Node *_followedNode;

    // whether camera should be limited to certain area
    bool _boundarySet;

    // if screen size is bigger than the boundary - update not needed
    bool _boundaryFullyCovered;

    // fast access to the screen dimensions
    Point _halfScreenSize;
    Point _fullScreenSize;

    // world boundaries
    float _leftBoundary;
    float _rightBoundary;
    float _topBoundary;
    float _bottomBoundary;
	Rect _worldRect;

};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTIONS_CCACTION_H__
