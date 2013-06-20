/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2011 Ricardo Quesada
Copyright (c) 2011 Zynga Inc.

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

#ifndef __ACTION_CCINTERVAL_ACTION_H__
#define __ACTION_CCINTERVAL_ACTION_H__

#include "base_nodes/CCNode.h"
#include "CCAction.h"
#include "CCProtocols.h"
#include "sprite_nodes/CCSpriteFrame.h"
#include "sprite_nodes/CCAnimation.h"
#include <vector>

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/** 
@brief An interval action is an action that takes place within a certain period of time.
It has an start time, and a finish time. The finish time is the parameter
duration plus the start time.

These CCActionInterval actions have some interesting properties, like:
- They can run normally (default)
- They can run reversed with the reverse method
- They can run with the time altered with the Accelerate, AccelDeccel and Speed actions.

For example, you can simulate a Ping Pong effect running the action normally and
then running it again in Reverse mode.

Example:

CCAction *pingPongAction = CCSequence::actions(action, action->reverse(), NULL);
*/
class CC_DLL CCActionInterval : public CCFiniteTimeAction
{
public:
    /** how many seconds had elapsed since the actions started to run. */
    inline float getElapsed(void) { return _elapsed; }

    /** initializes the action */
    bool initWithDuration(float d);

    /** returns true if the action has finished */
    virtual bool isDone(void);

    virtual void step(float dt);
    virtual void startWithTarget(CCNode *pTarget);

    /** returns a reversed action */
    virtual CCActionInterval* reverse() const = 0;

	virtual CCActionInterval *clone() const = 0;

public:
    //extension in CCGridAction 
    void setAmplitudeRate(float amp);
    float getAmplitudeRate(void);

protected:
    float _elapsed;
    bool   _firstTick;
};

/** @brief Runs actions sequentially, one after another
 */
class CC_DLL CCSequence : public CCActionInterval
{
public:
    ~CCSequence(void);

    /** initializes the action */
    bool initWithTwoActions(CCFiniteTimeAction *pActionOne, CCFiniteTimeAction *pActionTwo);

    virtual CCObject* copyWithZone(CCZone* pZone);
	/** returns a new clone of the action */
    virtual CCSequence* clone() const;

	/** returns a new reversed action */
	virtual CCSequence* reverse() const;

    virtual void startWithTarget(CCNode *pTarget);
    virtual void stop(void);
    virtual void update(float t);

public:

    /** helper constructor to create an array of sequenceable actions */
    static CCSequence* create(CCFiniteTimeAction *pAction1, ...);
    /** helper constructor to create an array of sequenceable actions given an array */
    static CCSequence* create(CCArray *arrayOfActions);
    /** helper constructor to create an array of sequence-able actions */
    static CCSequence* createWithVariableList(CCFiniteTimeAction *pAction1, va_list args);
    /** creates the action */
    static CCSequence* createWithTwoActions(CCFiniteTimeAction *pActionOne, CCFiniteTimeAction *pActionTwo);

protected:
    CCFiniteTimeAction *_actions[2];
    float _split;
    int _last;
};

/** @brief Repeats an action a number of times.
 * To repeat an action forever use the CCRepeatForever action.
 */
class CC_DLL CCRepeat : public CCActionInterval
{
public:
    ~CCRepeat(void);

    /** initializes a CCRepeat action. Times is an unsigned integer between 1 and pow(2,30) */
    bool initWithAction(CCFiniteTimeAction *pAction, unsigned int times);

    virtual CCObject* copyWithZone(CCZone* pZone);
	/** returns a new clone of the action */
    virtual CCRepeat* clone() const;

	/** returns a new reversed action */
	virtual CCRepeat* reverse() const;

    virtual void startWithTarget(CCNode *pTarget);
    virtual void stop(void);
    virtual void update(float dt);
    virtual bool isDone(void);

    inline void setInnerAction(CCFiniteTimeAction *pAction)
    {
        if (_innerAction != pAction)
        {
            CC_SAFE_RETAIN(pAction);
            CC_SAFE_RELEASE(_innerAction);
            _innerAction = pAction;
        }
    }

    inline CCFiniteTimeAction* getInnerAction()
    {
        return _innerAction;
    }

public:

    /** creates a CCRepeat action. Times is an unsigned integer between 1 and pow(2,30) */
    static CCRepeat* create(CCFiniteTimeAction *pAction, unsigned int times);
protected:
    unsigned int _times;
    unsigned int _total;
    float _nextDt;
    bool _actionInstant;
    /** Inner action */
    CCFiniteTimeAction *_innerAction;
};

/** @brief Repeats an action for ever.
To repeat the an action for a limited number of times use the Repeat action.
@warning This action can't be Sequenceable because it is not an IntervalAction
*/
class CC_DLL CCRepeatForever : public CCActionInterval
{
public:
    CCRepeatForever()
        : _innerAction(NULL)
    {}
    virtual ~CCRepeatForever();

    /** initializes the action */
    bool initWithAction(CCActionInterval *pAction);
    virtual CCObject* copyWithZone(CCZone *pZone);
	/** returns a new clone of the action */
    virtual CCRepeatForever* clone() const;

	/** returns a new reversed action */
	virtual CCRepeatForever* reverse(void) const;

    virtual void startWithTarget(CCNode* pTarget);
    virtual void step(float dt);
    virtual bool isDone(void);

    inline void setInnerAction(CCActionInterval *pAction)
    {
        if (_innerAction != pAction)
        {
            CC_SAFE_RELEASE(_innerAction);
            _innerAction = pAction;
            CC_SAFE_RETAIN(_innerAction);
        }
    }

    inline CCActionInterval* getInnerAction()
    {
        return _innerAction;
    }

public:

    /** creates the action */
    static CCRepeatForever* create(CCActionInterval *pAction);
protected:
    /** Inner action */
    CCActionInterval *_innerAction;
};

/** @brief Spawn a new action immediately
 */
class CC_DLL CCSpawn : public CCActionInterval
{
public:
    ~CCSpawn(void);

    /** initializes the Spawn action with the 2 actions to spawn */
    bool initWithTwoActions(CCFiniteTimeAction *pAction1, CCFiniteTimeAction *pAction2);

    virtual CCObject* copyWithZone(CCZone* pZone);
	/** returns a new clone of the action */
    virtual CCSpawn* clone() const;

	/** returns a new reversed action */
	virtual CCSpawn* reverse(void) const;

    virtual void startWithTarget(CCNode *pTarget);
    virtual void stop(void);
    virtual void update(float time);

public:

    /** helper constructor to create an array of spawned actions */
    static CCSpawn* create(CCFiniteTimeAction *pAction1, ...);
    
    /** helper constructor to create an array of spawned actions */
    static CCSpawn* createWithVariableList(CCFiniteTimeAction *pAction1, va_list args);

    /** helper constructor to create an array of spawned actions given an array */
    static CCSpawn* create(CCArray *arrayOfActions);

    /** creates the Spawn action */
    static CCSpawn* createWithTwoActions(CCFiniteTimeAction *pAction1, CCFiniteTimeAction *pAction2);

protected:
    CCFiniteTimeAction *_one;
    CCFiniteTimeAction *_two;
};

/** @brief Rotates a CCNode object to a certain angle by modifying it's
 rotation attribute.
 The direction will be decided by the shortest angle.
*/ 
class CC_DLL CCRotateTo : public CCActionInterval
{
public:
    /** creates the action */
    static CCRotateTo* create(float fDuration, float fDeltaAngle);
    /** initializes the action */
    bool initWithDuration(float fDuration, float fDeltaAngle);
    
    /** creates the action with separate rotation angles */
    static CCRotateTo* create(float fDuration, float fDeltaAngleX, float fDeltaAngleY);
    virtual bool initWithDuration(float fDuration, float fDeltaAngleX, float fDeltaAngleY);

    virtual CCObject* copyWithZone(CCZone* pZone);

	/** returns a new clone of the action */
    virtual CCRotateTo* clone() const;

	/** returns a new reversed action */
    virtual CCRotateTo* reverse() const;

    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    
protected:
    float _dstAngleX;
    float _startAngleX;
    float _diffAngleX;
    
    float _dstAngleY;
    float _startAngleY;
    float _diffAngleY;
};

/** @brief Rotates a CCNode object clockwise a number of degrees by modifying it's rotation attribute.
*/
class CC_DLL CCRotateBy : public CCActionInterval
{
public:
    /** creates the action */
    static CCRotateBy* create(float fDuration, float fDeltaAngle);
    /** initializes the action */
    bool initWithDuration(float fDuration, float fDeltaAngle);
    
    static CCRotateBy* create(float fDuration, float fDeltaAngleX, float fDeltaAngleY);
    bool initWithDuration(float fDuration, float fDeltaAngleX, float fDeltaAngleY);

    virtual CCObject* copyWithZone(CCZone* pZone);
	/** returns a new clone of the action */
    virtual CCRotateBy* clone() const;

	/** returns a new reversed action */
	virtual CCRotateBy* reverse(void) const;

    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

    
protected:
    float _angleX;
    float _startAngleX;
    float _angleY;
    float _startAngleY;
};

/**  Moves a CCNode object x,y pixels by modifying it's position attribute.
 x and y are relative to the position of the object.
 Several CCMoveBy actions can be concurrently called, and the resulting
 movement will be the sum of individual movements.
 @since v2.1beta2-custom
 */
class CC_DLL CCMoveBy : public CCActionInterval
{
public:
    /** initializes the action */
    bool initWithDuration(float duration, const CCPoint& deltaPosition);

    virtual CCObject* copyWithZone(CCZone* pZone);
	/** returns a new clone of the action */
    virtual CCMoveBy* clone() const;

	/** returns a new reversed action */
	virtual CCMoveBy* reverse(void) const;

    virtual void startWithTarget(CCNode *pTarget);

    virtual void update(float time);

public:
    /** creates the action */
    static CCMoveBy* create(float duration, const CCPoint& deltaPosition);
protected:
    CCPoint _positionDelta;
    CCPoint _startPosition;
    CCPoint _previousPosition;
};

/** Moves a CCNode object to the position x,y. x and y are absolute coordinates by modifying it's position attribute.
 Several CCMoveTo actions can be concurrently called, and the resulting
 movement will be the sum of individual movements.
 @since v2.1beta2-custom
 */
class CC_DLL CCMoveTo : public CCMoveBy
{
public:
    /** initializes the action */
    bool initWithDuration(float duration, const CCPoint& position);

    virtual CCObject* copyWithZone(CCZone* pZone);
	/** returns a new clone of the action */
    virtual CCMoveTo* clone() const;

    virtual void startWithTarget(CCNode *pTarget);

public:
    /** creates the action */
    static CCMoveTo* create(float duration, const CCPoint& position);
protected:
    CCPoint _endPosition;
};

/** Skews a CCNode object to given angles by modifying it's skewX and skewY attributes
@since v1.0
*/
class CC_DLL CCSkewTo : public CCActionInterval
{
public:
    CCSkewTo();
    virtual bool initWithDuration(float t, float sx, float sy);
    virtual CCObject* copyWithZone(CCZone* pZone);
	/** returns a new clone of the action */
    virtual CCSkewTo* clone() const;
	/** returns a new reversed action */
	virtual CCSkewTo* reverse(void) const;

    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

public:

    /** creates the action */
    static CCSkewTo* create(float t, float sx, float sy);
protected:
    float _skewX;
    float _skewY;
    float _startSkewX;
    float _startSkewY;
    float _endSkewX;
    float _endSkewY;
    float _deltaX;
    float _deltaY;
};

/** Skews a CCNode object by skewX and skewY degrees
@since v1.0
*/
class CC_DLL CCSkewBy : public CCSkewTo
{
public:
    virtual bool initWithDuration(float t, float sx, float sy);
    virtual void startWithTarget(CCNode *pTarget);

	/** returns a new clone of the action */
    virtual CCSkewBy* clone() const;
	/** returns a new reversed action */
	virtual CCSkewBy* reverse(void) const;


public:

    /** creates the action */
    static CCSkewBy* create(float t, float deltaSkewX, float deltaSkewY);
};

/** @brief Moves a CCNode object simulating a parabolic jump movement by modifying it's position attribute.
*/
class CC_DLL CCJumpBy : public CCActionInterval
{
public:
    /** initializes the action */
    bool initWithDuration(float duration, const CCPoint& position, float height, unsigned int jumps);

    virtual CCObject* copyWithZone(CCZone* pZone);
	/** returns a new clone of the action */
    virtual CCJumpBy* clone() const;
	/** returns a new reversed action */
	virtual CCJumpBy* reverse(void) const;

    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

public:
    /** creates the action */
    static CCJumpBy* create(float duration, const CCPoint& position, float height, unsigned int jumps);
protected:
    CCPoint         _startPosition;
    CCPoint         _delta;
    float           _height;
    unsigned int    _jumps;
    CCPoint         _previousPos;
};

/** @brief Moves a CCNode object to a parabolic position simulating a jump movement by modifying it's position attribute.
*/ 
class CC_DLL CCJumpTo : public CCJumpBy
{
public:
    virtual void startWithTarget(CCNode *pTarget);
    virtual CCObject* copyWithZone(CCZone* pZone);
	/** returns a new clone of the action */
    virtual CCJumpTo* clone() const;
	/** returns a new reversed action */
	virtual CCJumpTo* reverse(void) const;

public:
    /** creates the action */
    static CCJumpTo* create(float duration, const CCPoint& position, float height, int jumps);
};

/** @typedef bezier configuration structure
 */
typedef struct _ccBezierConfig {
    //! end position of the bezier
    CCPoint endPosition;
    //! Bezier control point 1
    CCPoint controlPoint_1;
    //! Bezier control point 2
    CCPoint controlPoint_2;
} ccBezierConfig;

/** @brief An action that moves the target with a cubic Bezier curve by a certain distance.
 */
class CC_DLL CCBezierBy : public CCActionInterval
{
public:
    /** initializes the action with a duration and a bezier configuration */
    bool initWithDuration(float t, const ccBezierConfig& c);

    virtual CCObject* copyWithZone(CCZone* pZone);
	/** returns a new clone of the action */
    virtual CCBezierBy* clone() const;
	/** returns a new reversed action */
	virtual CCBezierBy* reverse(void) const;

    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

public:
    /** creates the action with a duration and a bezier configuration */
    static CCBezierBy* create(float t, const ccBezierConfig& c);
protected:
    ccBezierConfig _config;
    CCPoint _startPosition;
    CCPoint _previousPosition;
};

/** @brief An action that moves the target with a cubic Bezier curve to a destination point.
 @since v0.8.2
 */
class CC_DLL CCBezierTo : public CCBezierBy
{
public:
    virtual void startWithTarget(CCNode *pTarget);
    virtual CCObject* copyWithZone(CCZone* pZone);
	/** returns a new clone of the action */
    virtual CCBezierTo* clone() const;
	/** returns a new reversed action */
	virtual CCBezierTo* reverse(void) const;

public:

    /** creates the action with a duration and a bezier configuration */
    static CCBezierTo* create(float t, const ccBezierConfig& c);
    bool initWithDuration(float t, const ccBezierConfig &c);
    
protected:
    ccBezierConfig _toConfig;
};

/** @brief Scales a CCNode object to a zoom factor by modifying it's scale attribute.
 @warning This action doesn't support "reverse"
 */
class CC_DLL CCScaleTo : public CCActionInterval
{
public:
    /** initializes the action with the same scale factor for X and Y */
    bool initWithDuration(float duration, float s);

    /** initializes the action with and X factor and a Y factor */
    bool initWithDuration(float duration, float sx, float sy);

    virtual CCObject* copyWithZone(CCZone* pZone);
	/** returns a new clone of the action */
    virtual CCScaleTo* clone() const;
	/** returns a new reversed action */
	virtual CCScaleTo* reverse(void) const;

    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

public:

    /** creates the action with the same scale factor for X and Y */
    static CCScaleTo* create(float duration, float s);

    /** creates the action with and X factor and a Y factor */
    static CCScaleTo* create(float duration, float sx, float sy);
protected:
    float _scaleX;
    float _scaleY;
    float _startScaleX;
    float _startScaleY;
    float _endScaleX;
    float _endScaleY;
    float _deltaX;
    float _deltaY;
};

/** @brief Scales a CCNode object a zoom factor by modifying it's scale attribute.
*/
class CC_DLL CCScaleBy : public CCScaleTo
{
public:
    virtual void startWithTarget(CCNode *pTarget);
	/** returns a new clone of the action */
    virtual CCScaleBy* clone() const;
	/** returns a new reversed action */
	virtual CCScaleBy* reverse(void) const;

    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** creates the action with the same scale factor for X and Y */
    static CCScaleBy* create(float duration, float s);

    /** creates the action with and X factor and a Y factor */
    static CCScaleBy* create(float duration, float sx, float sy);
};

/** @brief Blinks a CCNode object by modifying it's visible attribute
*/
class CC_DLL CCBlink : public CCActionInterval
{
public:
    /** initializes the action */
    bool initWithDuration(float duration, unsigned int uBlinks);

	/** returns a new clone of the action */
    virtual CCBlink* clone() const;
	/** returns a new reversed action */
	virtual CCBlink* reverse(void) const;

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(float time);

public:

    /** creates the action */
    static CCBlink* create(float duration, unsigned int uBlinks);
    
    virtual void startWithTarget(CCNode *pTarget);
    virtual void stop();
    
protected:
    unsigned int _times;
    bool _originalState;
};

/** @brief Fades In an object that implements the CCRGBAProtocol protocol. It modifies the opacity from 0 to 255.
 The "reverse" of this action is FadeOut
 */
class CC_DLL CCFadeIn : public CCActionInterval
{
public:
    virtual void update(float time);

	/** returns a new clone of the action */
    virtual CCFadeIn* clone() const;
	/** returns a new reversed action */
	virtual CCActionInterval* reverse(void) const;

    virtual CCObject* copyWithZone(CCZone* pZone);

public:
    /** creates the action */
    static CCFadeIn* create(float d);
};

/** @brief Fades Out an object that implements the CCRGBAProtocol protocol. It modifies the opacity from 255 to 0.
 The "reverse" of this action is FadeIn
*/
class CC_DLL CCFadeOut : public CCActionInterval
{
public:
    virtual void update(float time);
    virtual CCObject* copyWithZone(CCZone* pZone);
	/** returns a new clone of the action */
    virtual CCFadeOut* clone() const;
	/** returns a new reversed action */
	virtual CCActionInterval* reverse(void) const;


public:

    /** creates the action */
    static CCFadeOut* create(float d);
};

/** @brief Fades an object that implements the CCRGBAProtocol protocol. It modifies the opacity from the current value to a custom one.
 @warning This action doesn't support "reverse"
 */
class CC_DLL CCFadeTo : public CCActionInterval
{
public:
    /** initializes the action with duration and opacity */
    bool initWithDuration(float duration, GLubyte opacity);

	/** returns a new clone of the action */
    virtual CCFadeTo* clone() const;
	/** returns a new reversed action */
	virtual CCFadeTo* reverse(void) const;

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

public:
    /** creates an action with duration and opacity */
    static CCFadeTo* create(float duration, GLubyte opacity);
protected:
    GLubyte _toOpacity;
    GLubyte _fromOpacity;
};

/** @brief Tints a CCNode that implements the CCNodeRGB protocol from current tint to a custom one.
 @warning This action doesn't support "reverse"
 @since v0.7.2
*/
class CC_DLL CCTintTo : public CCActionInterval
{
public:
    /** initializes the action with duration and color */
    bool initWithDuration(float duration, GLubyte red, GLubyte green, GLubyte blue);

	/** returns a new clone of the action */
    virtual CCTintTo* clone() const;
	/** returns a new reversed action */
	virtual CCTintTo* reverse(void) const;

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

public:
    /** creates an action with duration and color */
    static CCTintTo* create(float duration, GLubyte red, GLubyte green, GLubyte blue);
protected:
    ccColor3B _to;
    ccColor3B _from;
};

/** @brief Tints a CCNode that implements the CCNodeRGB protocol from current tint to a custom one.
 @since v0.7.2
 */
class CC_DLL CCTintBy : public CCActionInterval
{
public:
    /** initializes the action with duration and color */
    bool initWithDuration(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue);

	/** returns a new clone of the action */
    virtual CCTintBy* clone() const;
	/** returns a new reversed action */
	virtual CCTintBy* reverse() const;

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

public:
    /** creates an action with duration and color */
    static CCTintBy* create(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue);
protected:
    GLshort _deltaR;
    GLshort _deltaG;
    GLshort _deltaB;

    GLshort _fromR;
    GLshort _fromG;
    GLshort _fromB;
};

/** @brief Delays the action a certain amount of seconds
*/
class CC_DLL CCDelayTime : public CCActionInterval
{
public:
    virtual void update(float time);
	/** returns a new reversed action */
    virtual CCDelayTime* reverse() const;
	/** returns a new clone of the action */
    virtual CCDelayTime* clone() const;
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** creates the action */
    static CCDelayTime* create(float d);
};

/** @brief Executes an action in reverse order, from time=duration to time=0
 
 @warning Use this action carefully. This action is not
 sequenceable. Use it as the default "reversed" method
 of your own actions, but using it outside the "reversed"
 scope is not recommended.
*/
class CC_DLL CCReverseTime : public CCActionInterval
{
public:
    ~CCReverseTime(void);
    CCReverseTime();

    /** initializes the action */
    bool initWithAction(CCFiniteTimeAction *pAction);

	/** returns a new reversed action */
	virtual CCReverseTime* reverse() const;
	/** returns a new clone of the action */
    virtual CCReverseTime* clone() const;
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void stop(void);
    virtual void update(float time);

public:
    /** creates the action */
    static CCReverseTime* create(CCFiniteTimeAction *pAction);
protected:
    CCFiniteTimeAction *_other;
};

class CCTexture2D;
/** @brief Animates a sprite given the name of an Animation */
class CC_DLL CCAnimate : public CCActionInterval
{
public:
    CCAnimate();
    ~CCAnimate();

    /** initializes the action with an Animation and will restore the original frame when the animation is over */
    bool initWithAnimation(CCAnimation *pAnimation);
	
	int getNextFrame();

	/** returns a new clone of the action */
    virtual CCAnimate* clone() const;
	/** returns a new reversed action */
    virtual CCAnimate* reverse() const;

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void stop(void);
    virtual void update(float t);



public:
    /** creates the action with an Animation and will restore the original frame when the animation is over */
    static CCAnimate* create(CCAnimation *pAnimation);
    CC_SYNTHESIZE_RETAIN(CCAnimation*, _animation, Animation)
protected:
    std::vector<float>* _splitTimes;
    int                _nextFrame;
    CCSpriteFrame*  _origFrame;
       unsigned int    _executedLoops;
};

/** Overrides the target of an action so that it always runs on the target
 * specified at action creation rather than the one specified by runAction.
 */
class CC_DLL CCTargetedAction : public CCActionInterval
{
public:
    CCTargetedAction();
    virtual ~CCTargetedAction();

    /** Create an action with the specified action and forced target */
    static CCTargetedAction* create(CCNode* pTarget, CCFiniteTimeAction* pAction);

    /** Init an action with the specified action and forced target */
    bool initWithTarget(CCNode* pTarget, CCFiniteTimeAction* pAction);

	/** returns a new clone of the action */
    virtual CCTargetedAction* clone() const;
	/** returns a new reversed action */
    virtual CCTargetedAction* reverse() const;

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void stop(void);
    virtual void update(float time);

    /** This is the target that the action will be forced to run with */
    CC_SYNTHESIZE_RETAIN(CCNode*, _forcedTarget, ForcedTarget);
private:
    CCFiniteTimeAction* _action;
};

// end of actions group
/// @}

NS_CC_END

#endif //__ACTION_CCINTERVAL_ACTION_H__
