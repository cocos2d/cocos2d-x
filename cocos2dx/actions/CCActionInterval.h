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

These ActionInterval actions have some interesting properties, like:
- They can run normally (default)
- They can run reversed with the reverse method
- They can run with the time altered with the Accelerate, AccelDeccel and Speed actions.

For example, you can simulate a Ping Pong effect running the action normally and
then running it again in Reverse mode.

Example:

Action *pingPongAction = Sequence::actions(action, action->reverse(), NULL);
*/
class CC_DLL ActionInterval : public FiniteTimeAction
{
public:
    /** how many seconds had elapsed since the actions started to run. */
    inline float getElapsed(void) { return _elapsed; }

    /** initializes the action */
    bool initWithDuration(float d);

    /** returns true if the action has finished */
    virtual bool isDone(void);

    virtual void step(float dt);
    virtual void startWithTarget(Node *pTarget);

    /** returns a reversed action */
    virtual ActionInterval* reverse() const = 0;

	virtual ActionInterval *clone() const = 0;

public:
    //extension in GridAction 
    void setAmplitudeRate(float amp);
    float getAmplitudeRate(void);

protected:
    float _elapsed;
    bool   _firstTick;
};

/** @brief Runs actions sequentially, one after another
 */
class CC_DLL Sequence : public ActionInterval
{
public:
    ~Sequence(void);

    /** initializes the action */
    bool initWithTwoActions(FiniteTimeAction *pActionOne, FiniteTimeAction *pActionTwo);

    virtual Object* copyWithZone(Zone* pZone);
	/** returns a new clone of the action */
    virtual Sequence* clone() const;

	/** returns a new reversed action */
	virtual Sequence* reverse() const;

    virtual void startWithTarget(Node *pTarget);
    virtual void stop(void);
    virtual void update(float t);

public:

    /** helper constructor to create an array of sequenceable actions */
    static Sequence* create(FiniteTimeAction *pAction1, ...);
    /** helper constructor to create an array of sequenceable actions given an array */
    static Sequence* create(Array *arrayOfActions);
    /** helper constructor to create an array of sequence-able actions */
    static Sequence* createWithVariableList(FiniteTimeAction *pAction1, va_list args);
    /** creates the action */
    static Sequence* createWithTwoActions(FiniteTimeAction *pActionOne, FiniteTimeAction *pActionTwo);

protected:
    FiniteTimeAction *_actions[2];
    float _split;
    int _last;
};

/** @brief Repeats an action a number of times.
 * To repeat an action forever use the RepeatForever action.
 */
class CC_DLL Repeat : public ActionInterval
{
public:
    ~Repeat(void);

    /** initializes a Repeat action. Times is an unsigned integer between 1 and pow(2,30) */
    bool initWithAction(FiniteTimeAction *pAction, unsigned int times);

    virtual Object* copyWithZone(Zone* pZone);
	/** returns a new clone of the action */
    virtual Repeat* clone() const;

	/** returns a new reversed action */
	virtual Repeat* reverse() const;

    virtual void startWithTarget(Node *pTarget);
    virtual void stop(void);
    virtual void update(float dt);
    virtual bool isDone(void);

    inline void setInnerAction(FiniteTimeAction *pAction)
    {
        if (_innerAction != pAction)
        {
            CC_SAFE_RETAIN(pAction);
            CC_SAFE_RELEASE(_innerAction);
            _innerAction = pAction;
        }
    }

    inline FiniteTimeAction* getInnerAction()
    {
        return _innerAction;
    }

public:

    /** creates a Repeat action. Times is an unsigned integer between 1 and pow(2,30) */
    static Repeat* create(FiniteTimeAction *pAction, unsigned int times);
protected:
    unsigned int _times;
    unsigned int _total;
    float _nextDt;
    bool _actionInstant;
    /** Inner action */
    FiniteTimeAction *_innerAction;
};

/** @brief Repeats an action for ever.
To repeat the an action for a limited number of times use the Repeat action.
@warning This action can't be Sequenceable because it is not an IntervalAction
*/
class CC_DLL RepeatForever : public ActionInterval
{
public:
    RepeatForever()
        : _innerAction(NULL)
    {}
    virtual ~RepeatForever();

    /** initializes the action */
    bool initWithAction(ActionInterval *pAction);
    virtual Object* copyWithZone(Zone *pZone);
	/** returns a new clone of the action */
    virtual RepeatForever* clone() const;

	/** returns a new reversed action */
	virtual RepeatForever* reverse(void) const;

    virtual void startWithTarget(Node* pTarget);
    virtual void step(float dt);
    virtual bool isDone(void);

    inline void setInnerAction(ActionInterval *pAction)
    {
        if (_innerAction != pAction)
        {
            CC_SAFE_RELEASE(_innerAction);
            _innerAction = pAction;
            CC_SAFE_RETAIN(_innerAction);
        }
    }

    inline ActionInterval* getInnerAction()
    {
        return _innerAction;
    }

public:

    /** creates the action */
    static RepeatForever* create(ActionInterval *pAction);
protected:
    /** Inner action */
    ActionInterval *_innerAction;
};

/** @brief Spawn a new action immediately
 */
class CC_DLL Spawn : public ActionInterval
{
public:
    ~Spawn(void);

    /** initializes the Spawn action with the 2 actions to spawn */
    bool initWithTwoActions(FiniteTimeAction *pAction1, FiniteTimeAction *pAction2);

    virtual Object* copyWithZone(Zone* pZone);
	/** returns a new clone of the action */
    virtual Spawn* clone() const;

	/** returns a new reversed action */
	virtual Spawn* reverse(void) const;

    virtual void startWithTarget(Node *pTarget);
    virtual void stop(void);
    virtual void update(float time);

public:

    /** helper constructor to create an array of spawned actions */
    static Spawn* create(FiniteTimeAction *pAction1, ...);
    
    /** helper constructor to create an array of spawned actions */
    static Spawn* createWithVariableList(FiniteTimeAction *pAction1, va_list args);

    /** helper constructor to create an array of spawned actions given an array */
    static Spawn* create(Array *arrayOfActions);

    /** creates the Spawn action */
    static Spawn* createWithTwoActions(FiniteTimeAction *pAction1, FiniteTimeAction *pAction2);

protected:
    FiniteTimeAction *_one;
    FiniteTimeAction *_two;
};

/** @brief Rotates a Node object to a certain angle by modifying it's
 rotation attribute.
 The direction will be decided by the shortest angle.
*/ 
class CC_DLL RotateTo : public ActionInterval
{
public:
    /** creates the action */
    static RotateTo* create(float fDuration, float fDeltaAngle);
    /** initializes the action */
    bool initWithDuration(float fDuration, float fDeltaAngle);
    
    /** creates the action with separate rotation angles */
    static RotateTo* create(float fDuration, float fDeltaAngleX, float fDeltaAngleY);
    virtual bool initWithDuration(float fDuration, float fDeltaAngleX, float fDeltaAngleY);

    virtual Object* copyWithZone(Zone* pZone);

	/** returns a new clone of the action */
    virtual RotateTo* clone() const;

	/** returns a new reversed action */
    virtual RotateTo* reverse() const;

    virtual void startWithTarget(Node *pTarget);
    virtual void update(float time);
    
protected:
    float _dstAngleX;
    float _startAngleX;
    float _diffAngleX;
    
    float _dstAngleY;
    float _startAngleY;
    float _diffAngleY;
};

/** @brief Rotates a Node object clockwise a number of degrees by modifying it's rotation attribute.
*/
class CC_DLL RotateBy : public ActionInterval
{
public:
    /** creates the action */
    static RotateBy* create(float fDuration, float fDeltaAngle);
    /** initializes the action */
    bool initWithDuration(float fDuration, float fDeltaAngle);
    
    static RotateBy* create(float fDuration, float fDeltaAngleX, float fDeltaAngleY);
    bool initWithDuration(float fDuration, float fDeltaAngleX, float fDeltaAngleY);

    virtual Object* copyWithZone(Zone* pZone);
	/** returns a new clone of the action */
    virtual RotateBy* clone() const;

	/** returns a new reversed action */
	virtual RotateBy* reverse(void) const;

    virtual void startWithTarget(Node *pTarget);
    virtual void update(float time);

    
protected:
    float _angleX;
    float _startAngleX;
    float _angleY;
    float _startAngleY;
};

/**  Moves a Node object x,y pixels by modifying it's position attribute.
 x and y are relative to the position of the object.
 Several MoveBy actions can be concurrently called, and the resulting
 movement will be the sum of individual movements.
 @since v2.1beta2-custom
 */
class CC_DLL MoveBy : public ActionInterval
{
public:
    /** initializes the action */
    bool initWithDuration(float duration, const Point& deltaPosition);

    virtual Object* copyWithZone(Zone* pZone);
	/** returns a new clone of the action */
    virtual MoveBy* clone() const;

	/** returns a new reversed action */
	virtual MoveBy* reverse(void) const;

    virtual void startWithTarget(Node *pTarget);

    virtual void update(float time);

public:
    /** creates the action */
    static MoveBy* create(float duration, const Point& deltaPosition);
protected:
    Point _positionDelta;
    Point _startPosition;
    Point _previousPosition;
};

/** Moves a Node object to the position x,y. x and y are absolute coordinates by modifying it's position attribute.
 Several MoveTo actions can be concurrently called, and the resulting
 movement will be the sum of individual movements.
 @since v2.1beta2-custom
 */
class CC_DLL MoveTo : public MoveBy
{
public:
    /** initializes the action */
    bool initWithDuration(float duration, const Point& position);

    virtual Object* copyWithZone(Zone* pZone);
	/** returns a new clone of the action */
    virtual MoveTo* clone() const;

    virtual void startWithTarget(Node *pTarget);

public:
    /** creates the action */
    static MoveTo* create(float duration, const Point& position);
protected:
    Point _endPosition;
};

/** Skews a Node object to given angles by modifying it's skewX and skewY attributes
@since v1.0
*/
class CC_DLL SkewTo : public ActionInterval
{
public:
    SkewTo();
    virtual bool initWithDuration(float t, float sx, float sy);
    virtual Object* copyWithZone(Zone* pZone);
	/** returns a new clone of the action */
    virtual SkewTo* clone() const;
	/** returns a new reversed action */
	virtual SkewTo* reverse(void) const;

    virtual void startWithTarget(Node *pTarget);
    virtual void update(float time);

public:

    /** creates the action */
    static SkewTo* create(float t, float sx, float sy);
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

/** Skews a Node object by skewX and skewY degrees
@since v1.0
*/
class CC_DLL SkewBy : public SkewTo
{
public:
    virtual bool initWithDuration(float t, float sx, float sy);
    virtual void startWithTarget(Node *pTarget);

	/** returns a new clone of the action */
    virtual SkewBy* clone() const;
	/** returns a new reversed action */
	virtual SkewBy* reverse(void) const;


public:

    /** creates the action */
    static SkewBy* create(float t, float deltaSkewX, float deltaSkewY);
};

/** @brief Moves a Node object simulating a parabolic jump movement by modifying it's position attribute.
*/
class CC_DLL JumpBy : public ActionInterval
{
public:
    /** initializes the action */
    bool initWithDuration(float duration, const Point& position, float height, unsigned int jumps);

    virtual Object* copyWithZone(Zone* pZone);
	/** returns a new clone of the action */
    virtual JumpBy* clone() const;
	/** returns a new reversed action */
	virtual JumpBy* reverse(void) const;

    virtual void startWithTarget(Node *pTarget);
    virtual void update(float time);

public:
    /** creates the action */
    static JumpBy* create(float duration, const Point& position, float height, unsigned int jumps);
protected:
    Point         _startPosition;
    Point         _delta;
    float           _height;
    unsigned int    _jumps;
    Point         _previousPos;
};

/** @brief Moves a Node object to a parabolic position simulating a jump movement by modifying it's position attribute.
*/ 
class CC_DLL JumpTo : public JumpBy
{
public:
    virtual void startWithTarget(Node *pTarget);
    virtual Object* copyWithZone(Zone* pZone);
	/** returns a new clone of the action */
    virtual JumpTo* clone() const;
	/** returns a new reversed action */
	virtual JumpTo* reverse(void) const;

public:
    /** creates the action */
    static JumpTo* create(float duration, const Point& position, float height, int jumps);
};

/** @typedef bezier configuration structure
 */
typedef struct _ccBezierConfig {
    //! end position of the bezier
    Point endPosition;
    //! Bezier control point 1
    Point controlPoint_1;
    //! Bezier control point 2
    Point controlPoint_2;
} ccBezierConfig;

/** @brief An action that moves the target with a cubic Bezier curve by a certain distance.
 */
class CC_DLL BezierBy : public ActionInterval
{
public:
    /** initializes the action with a duration and a bezier configuration */
    bool initWithDuration(float t, const ccBezierConfig& c);

    virtual Object* copyWithZone(Zone* pZone);
	/** returns a new clone of the action */
    virtual BezierBy* clone() const;
	/** returns a new reversed action */
	virtual BezierBy* reverse(void) const;

    virtual void startWithTarget(Node *pTarget);
    virtual void update(float time);

public:
    /** creates the action with a duration and a bezier configuration */
    static BezierBy* create(float t, const ccBezierConfig& c);
protected:
    ccBezierConfig _config;
    Point _startPosition;
    Point _previousPosition;
};

/** @brief An action that moves the target with a cubic Bezier curve to a destination point.
 @since v0.8.2
 */
class CC_DLL BezierTo : public BezierBy
{
public:
    virtual void startWithTarget(Node *pTarget);
    virtual Object* copyWithZone(Zone* pZone);
	/** returns a new clone of the action */
    virtual BezierTo* clone() const;
	/** returns a new reversed action */
	virtual BezierTo* reverse(void) const;

public:

    /** creates the action with a duration and a bezier configuration */
    static BezierTo* create(float t, const ccBezierConfig& c);
    bool initWithDuration(float t, const ccBezierConfig &c);
    
protected:
    ccBezierConfig _toConfig;
};

/** @brief Scales a Node object to a zoom factor by modifying it's scale attribute.
 @warning This action doesn't support "reverse"
 */
class CC_DLL ScaleTo : public ActionInterval
{
public:
    /** initializes the action with the same scale factor for X and Y */
    bool initWithDuration(float duration, float s);

    /** initializes the action with and X factor and a Y factor */
    bool initWithDuration(float duration, float sx, float sy);

    virtual Object* copyWithZone(Zone* pZone);
	/** returns a new clone of the action */
    virtual ScaleTo* clone() const;
	/** returns a new reversed action */
	virtual ScaleTo* reverse(void) const;

    virtual void startWithTarget(Node *pTarget);
    virtual void update(float time);

public:

    /** creates the action with the same scale factor for X and Y */
    static ScaleTo* create(float duration, float s);

    /** creates the action with and X factor and a Y factor */
    static ScaleTo* create(float duration, float sx, float sy);
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

/** @brief Scales a Node object a zoom factor by modifying it's scale attribute.
*/
class CC_DLL ScaleBy : public ScaleTo
{
public:
    virtual void startWithTarget(Node *pTarget);
	/** returns a new clone of the action */
    virtual ScaleBy* clone() const;
	/** returns a new reversed action */
	virtual ScaleBy* reverse(void) const;

    virtual Object* copyWithZone(Zone* pZone);

public:

    /** creates the action with the same scale factor for X and Y */
    static ScaleBy* create(float duration, float s);

    /** creates the action with and X factor and a Y factor */
    static ScaleBy* create(float duration, float sx, float sy);
};

/** @brief Blinks a Node object by modifying it's visible attribute
*/
class CC_DLL Blink : public ActionInterval
{
public:
    /** initializes the action */
    bool initWithDuration(float duration, unsigned int uBlinks);

	/** returns a new clone of the action */
    virtual Blink* clone() const;
	/** returns a new reversed action */
	virtual Blink* reverse(void) const;

    virtual Object* copyWithZone(Zone* pZone);
    virtual void update(float time);

public:

    /** creates the action */
    static Blink* create(float duration, unsigned int uBlinks);
    
    virtual void startWithTarget(Node *pTarget);
    virtual void stop();
    
protected:
    unsigned int _times;
    bool _originalState;
};

/** @brief Fades In an object that implements the RGBAProtocol protocol. It modifies the opacity from 0 to 255.
 The "reverse" of this action is FadeOut
 */
class CC_DLL FadeIn : public ActionInterval
{
public:
    virtual void update(float time);

	/** returns a new clone of the action */
    virtual FadeIn* clone() const;
	/** returns a new reversed action */
	virtual ActionInterval* reverse(void) const;

    virtual Object* copyWithZone(Zone* pZone);

public:
    /** creates the action */
    static FadeIn* create(float d);
};

/** @brief Fades Out an object that implements the RGBAProtocol protocol. It modifies the opacity from 255 to 0.
 The "reverse" of this action is FadeIn
*/
class CC_DLL FadeOut : public ActionInterval
{
public:
    virtual void update(float time);
    virtual Object* copyWithZone(Zone* pZone);
	/** returns a new clone of the action */
    virtual FadeOut* clone() const;
	/** returns a new reversed action */
	virtual ActionInterval* reverse(void) const;


public:

    /** creates the action */
    static FadeOut* create(float d);
};

/** @brief Fades an object that implements the RGBAProtocol protocol. It modifies the opacity from the current value to a custom one.
 @warning This action doesn't support "reverse"
 */
class CC_DLL FadeTo : public ActionInterval
{
public:
    /** initializes the action with duration and opacity */
    bool initWithDuration(float duration, GLubyte opacity);

	/** returns a new clone of the action */
    virtual FadeTo* clone() const;
	/** returns a new reversed action */
	virtual FadeTo* reverse(void) const;

    virtual Object* copyWithZone(Zone* pZone);
    virtual void startWithTarget(Node *pTarget);
    virtual void update(float time);

public:
    /** creates an action with duration and opacity */
    static FadeTo* create(float duration, GLubyte opacity);
protected:
    GLubyte _toOpacity;
    GLubyte _fromOpacity;
};

/** @brief Tints a Node that implements the NodeRGB protocol from current tint to a custom one.
 @warning This action doesn't support "reverse"
 @since v0.7.2
*/
class CC_DLL TintTo : public ActionInterval
{
public:
    /** initializes the action with duration and color */
    bool initWithDuration(float duration, GLubyte red, GLubyte green, GLubyte blue);

	/** returns a new clone of the action */
    virtual TintTo* clone() const;
	/** returns a new reversed action */
	virtual TintTo* reverse(void) const;

    virtual Object* copyWithZone(Zone* pZone);
    virtual void startWithTarget(Node *pTarget);
    virtual void update(float time);

public:
    /** creates an action with duration and color */
    static TintTo* create(float duration, GLubyte red, GLubyte green, GLubyte blue);
protected:
    ccColor3B _to;
    ccColor3B _from;
};

/** @brief Tints a Node that implements the NodeRGB protocol from current tint to a custom one.
 @since v0.7.2
 */
class CC_DLL TintBy : public ActionInterval
{
public:
    /** initializes the action with duration and color */
    bool initWithDuration(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue);

	/** returns a new clone of the action */
    virtual TintBy* clone() const;
	/** returns a new reversed action */
	virtual TintBy* reverse() const;

    virtual Object* copyWithZone(Zone* pZone);
    virtual void startWithTarget(Node *pTarget);
    virtual void update(float time);

public:
    /** creates an action with duration and color */
    static TintBy* create(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue);
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
class CC_DLL DelayTime : public ActionInterval
{
public:
    virtual void update(float time);
	/** returns a new reversed action */
    virtual DelayTime* reverse() const;
	/** returns a new clone of the action */
    virtual DelayTime* clone() const;
    virtual Object* copyWithZone(Zone* pZone);

public:

    /** creates the action */
    static DelayTime* create(float d);
};

/** @brief Executes an action in reverse order, from time=duration to time=0
 
 @warning Use this action carefully. This action is not
 sequenceable. Use it as the default "reversed" method
 of your own actions, but using it outside the "reversed"
 scope is not recommended.
*/
class CC_DLL ReverseTime : public ActionInterval
{
public:
    ~ReverseTime(void);
    ReverseTime();

    /** initializes the action */
    bool initWithAction(FiniteTimeAction *pAction);

	/** returns a new reversed action */
	virtual ReverseTime* reverse() const;
	/** returns a new clone of the action */
    virtual ReverseTime* clone() const;
    virtual Object* copyWithZone(Zone* pZone);
    virtual void startWithTarget(Node *pTarget);
    virtual void stop(void);
    virtual void update(float time);

public:
    /** creates the action */
    static ReverseTime* create(FiniteTimeAction *pAction);
protected:
    FiniteTimeAction *_other;
};

class Texture2D;
/** @brief Animates a sprite given the name of an Animation */
class CC_DLL Animate : public ActionInterval
{
public:
    Animate();
    ~Animate();

    /** initializes the action with an Animation and will restore the original frame when the animation is over */
    bool initWithAnimation(Animation *pAnimation);

	/** returns a new clone of the action */
    virtual Animate* clone() const;
	/** returns a new reversed action */
    virtual Animate* reverse() const;

    virtual Object* copyWithZone(Zone* pZone);
    virtual void startWithTarget(Node *pTarget);
    virtual void stop(void);
    virtual void update(float t);



public:
    /** creates the action with an Animation and will restore the original frame when the animation is over */
    static Animate* create(Animation *pAnimation);
    CC_SYNTHESIZE_RETAIN(Animation*, _animation, Animation)
protected:
    std::vector<float>* _splitTimes;
    int                _nextFrame;
    SpriteFrame*  _origFrame;
       unsigned int    _executedLoops;
};

/** Overrides the target of an action so that it always runs on the target
 * specified at action creation rather than the one specified by runAction.
 */
class CC_DLL TargetedAction : public ActionInterval
{
public:
    TargetedAction();
    virtual ~TargetedAction();

    /** Create an action with the specified action and forced target */
    static TargetedAction* create(Node* pTarget, FiniteTimeAction* pAction);

    /** Init an action with the specified action and forced target */
    bool initWithTarget(Node* pTarget, FiniteTimeAction* pAction);

	/** returns a new clone of the action */
    virtual TargetedAction* clone() const;
	/** returns a new reversed action */
    virtual TargetedAction* reverse() const;

    virtual Object* copyWithZone(Zone* pZone);
    virtual void startWithTarget(Node *pTarget);
    virtual void stop(void);
    virtual void update(float time);

    /** This is the target that the action will be forced to run with */
    CC_SYNTHESIZE_RETAIN(Node*, _forcedTarget, ForcedTarget);
private:
    FiniteTimeAction* _action;
};

// end of actions group
/// @}

NS_CC_END

#endif //__ACTION_CCINTERVAL_ACTION_H__
