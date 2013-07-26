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

    //extension in GridAction
    void setAmplitudeRate(float amp);
    float getAmplitudeRate(void);

    //
    // Overrides
    //
    virtual bool isDone(void) const override;
    virtual void step(float dt) override;
    virtual void startWithTarget(Node *target) override;
    virtual ActionInterval* reverse() const override = 0;
	virtual ActionInterval *clone() const override = 0;


protected:
    float _elapsed;
    bool   _firstTick;
};

/** @brief Runs actions sequentially, one after another
 */
class CC_DLL Sequence : public ActionInterval
{
public:
    /** helper constructor to create an array of sequenceable actions */
    static Sequence* create(FiniteTimeAction *pAction1, ...) CC_REQUIRES_NULL_TERMINATION;
    /** helper constructor to create an array of sequenceable actions given an array */
    static Sequence* create(Array *arrayOfActions);
    /** helper constructor to create an array of sequence-able actions */
    static Sequence* createWithVariableList(FiniteTimeAction *pAction1, va_list args);
    /** creates the action */
    static Sequence* createWithTwoActions(FiniteTimeAction *pActionOne, FiniteTimeAction *pActionTwo);

    virtual ~Sequence(void);

    /** initializes the action */
    bool initWithTwoActions(FiniteTimeAction *pActionOne, FiniteTimeAction *pActionTwo);

    //
    // Overrides
    //
    virtual Sequence* clone() const override;
	virtual Sequence* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float t) override;

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
    /** creates a Repeat action. Times is an unsigned integer between 1 and pow(2,30) */
    static Repeat* create(FiniteTimeAction *pAction, unsigned int times);

    virtual ~Repeat(void);

    /** initializes a Repeat action. Times is an unsigned integer between 1 and pow(2,30) */
    bool initWithAction(FiniteTimeAction *pAction, unsigned int times);

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

    //
    // Overrides
    //
    virtual Repeat* clone() const override;
	virtual Repeat* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float dt) override;
    virtual bool isDone(void) const override;

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
    /** creates the action */
    static RepeatForever* create(ActionInterval *pAction);

    RepeatForever()
        : _innerAction(NULL)
    {}
    virtual ~RepeatForever();

    /** initializes the action */
    bool initWithAction(ActionInterval *pAction);

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

    //
    // Overrides
    //
    virtual RepeatForever* clone() const override;
	virtual RepeatForever* reverse(void) const override;
    virtual void startWithTarget(Node* target) override;
    virtual void step(float dt) override;
    virtual bool isDone(void) const override;

protected:
    /** Inner action */
    ActionInterval *_innerAction;
};

/** @brief Spawn a new action immediately
 */
class CC_DLL Spawn : public ActionInterval
{
public:
    /** helper constructor to create an array of spawned actions */
    static Spawn* create(FiniteTimeAction *pAction1, ...) CC_REQUIRES_NULL_TERMINATION;

    /** helper constructor to create an array of spawned actions */
    static Spawn* createWithVariableList(FiniteTimeAction *pAction1, va_list args);

    /** helper constructor to create an array of spawned actions given an array */
    static Spawn* create(Array *arrayOfActions);

    /** creates the Spawn action */
    static Spawn* createWithTwoActions(FiniteTimeAction *pAction1, FiniteTimeAction *pAction2);

    virtual ~Spawn(void);

    /** initializes the Spawn action with the 2 actions to spawn */
    bool initWithTwoActions(FiniteTimeAction *pAction1, FiniteTimeAction *pAction2);

    //
    // Overrides
    //
    virtual Spawn* clone() const override;
	virtual Spawn* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float time) override;

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
    /** creates the action with separate rotation angles */
    static RotateTo* create(float fDuration, float fDeltaAngleX, float fDeltaAngleY);

    /** creates the action */
    static RotateTo* create(float fDuration, float fDeltaAngle);
    /** initializes the action */
    bool initWithDuration(float fDuration, float fDeltaAngle);
    
    bool initWithDuration(float fDuration, float fDeltaAngleX, float fDeltaAngleY);

    //
    // Overrides
    //
    virtual RotateTo* clone() const override;
    virtual RotateTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
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

    //
    // Override
    //
    virtual RotateBy* clone() const override;
	virtual RotateBy* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
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
    /** creates the action */
    static MoveBy* create(float duration, const Point& deltaPosition);

    /** initializes the action */
    bool initWithDuration(float duration, const Point& deltaPosition);

    //
    // Overrides
    //
    virtual MoveBy* clone() const override;
	virtual MoveBy* reverse(void) const  override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

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
    /** creates the action */
    static MoveTo* create(float duration, const Point& position);

    /** initializes the action */
    bool initWithDuration(float duration, const Point& position);

    //
    // Overrides
    //
    virtual MoveTo* clone() const override;
    virtual void startWithTarget(Node *target) override;

protected:
    Point _endPosition;
};

/** Skews a Node object to given angles by modifying it's skewX and skewY attributes
@since v1.0
*/
class CC_DLL SkewTo : public ActionInterval
{
public:
    /** creates the action */
    static SkewTo* create(float t, float sx, float sy);

    SkewTo();
    bool initWithDuration(float t, float sx, float sy);

    //
    // Overrides
    //
    virtual SkewTo* clone() const override;
	virtual SkewTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

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
    /** creates the action */
    static SkewBy* create(float t, float deltaSkewX, float deltaSkewY);

    bool initWithDuration(float t, float sx, float sy);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual SkewBy* clone() const  override;
	virtual SkewBy* reverse(void) const override;
};

/** @brief Moves a Node object simulating a parabolic jump movement by modifying it's position attribute.
*/
class CC_DLL JumpBy : public ActionInterval
{
public:
    /** creates the action */
    static JumpBy* create(float duration, const Point& position, float height, int jumps);

    /** initializes the action */
    bool initWithDuration(float duration, const Point& position, float height, int jumps);

    //
    // Overrides
    //
    virtual JumpBy* clone() const override;
	virtual JumpBy* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

protected:
    Point           _startPosition;
    Point           _delta;
    float           _height;
    int             _jumps;
    Point           _previousPos;
};

/** @brief Moves a Node object to a parabolic position simulating a jump movement by modifying it's position attribute.
*/ 
class CC_DLL JumpTo : public JumpBy
{
public:
    /** creates the action */
    static JumpTo* create(float duration, const Point& position, float height, int jumps);

    //
    // Override
    //
    virtual void startWithTarget(Node *target) override;
    virtual JumpTo* clone() const override;
	virtual JumpTo* reverse(void) const override;
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
    /** creates the action with a duration and a bezier configuration */
    static BezierBy* create(float t, const ccBezierConfig& c);

    /** initializes the action with a duration and a bezier configuration */
    bool initWithDuration(float t, const ccBezierConfig& c);

    //
    // Overrides
    //
    virtual BezierBy* clone() const override;
	virtual BezierBy* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

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
    /** creates the action with a duration and a bezier configuration */
    static BezierTo* create(float t, const ccBezierConfig& c);
    bool initWithDuration(float t, const ccBezierConfig &c);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual BezierTo* clone() const override;
	virtual BezierTo* reverse(void) const override;

protected:
    ccBezierConfig _toConfig;
};

/** @brief Scales a Node object to a zoom factor by modifying it's scale attribute.
 @warning This action doesn't support "reverse"
 */
class CC_DLL ScaleTo : public ActionInterval
{
public:
    /** creates the action with the same scale factor for X and Y */
    static ScaleTo* create(float duration, float s);

    /** creates the action with and X factor and a Y factor */
    static ScaleTo* create(float duration, float sx, float sy);

    /** initializes the action with the same scale factor for X and Y */
    bool initWithDuration(float duration, float s);

    /** initializes the action with and X factor and a Y factor */
    bool initWithDuration(float duration, float sx, float sy);

    //
    // Overrides
    //
    virtual ScaleTo* clone() const override;
	virtual ScaleTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

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
    /** creates the action with the same scale factor for X and Y */
    static ScaleBy* create(float duration, float s);

    /** creates the action with and X factor and a Y factor */
    static ScaleBy* create(float duration, float sx, float sy);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual ScaleBy* clone() const override;
	virtual ScaleBy* reverse(void) const override;
};

/** @brief Blinks a Node object by modifying it's visible attribute
*/
class CC_DLL Blink : public ActionInterval
{
public:
    /** creates the action */
    static Blink* create(float duration, int blinks);

    /** initializes the action */
    bool initWithDuration(float duration, int blinks);

    //
    // Overrides
    //
    virtual Blink* clone() const override;
	virtual Blink* reverse(void) const override;
    virtual void update(float time) override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop() override;
    
protected:
    int _times;
    bool _originalState;
};

/** @brief Fades In an object that implements the RGBAProtocol protocol. It modifies the opacity from 0 to 255.
 The "reverse" of this action is FadeOut
 */
class CC_DLL FadeIn : public ActionInterval
{
public:
    /** creates the action */
    static FadeIn* create(float d);

    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual FadeIn* clone() const override;
	virtual ActionInterval* reverse(void) const override;
};

/** @brief Fades Out an object that implements the RGBAProtocol protocol. It modifies the opacity from 255 to 0.
 The "reverse" of this action is FadeIn
*/
class CC_DLL FadeOut : public ActionInterval
{
public:
    /** creates the action */
    static FadeOut* create(float d);

    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual FadeOut* clone() const  override;
	virtual ActionInterval* reverse(void) const override;
};

/** @brief Fades an object that implements the RGBAProtocol protocol. It modifies the opacity from the current value to a custom one.
 @warning This action doesn't support "reverse"
 */
class CC_DLL FadeTo : public ActionInterval
{
public:
    /** creates an action with duration and opacity */
    static FadeTo* create(float duration, GLubyte opacity);

    /** initializes the action with duration and opacity */
    bool initWithDuration(float duration, GLubyte opacity);

    //
    // Overrides
    //
    virtual FadeTo* clone() const override;
	virtual FadeTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

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
    /** creates an action with duration and color */
    static TintTo* create(float duration, GLubyte red, GLubyte green, GLubyte blue);

    /** initializes the action with duration and color */
    bool initWithDuration(float duration, GLubyte red, GLubyte green, GLubyte blue);

    //
    // Overrides
    //
    virtual TintTo* clone() const override;
	virtual TintTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

protected:
    Color3B _to;
    Color3B _from;
};

/** @brief Tints a Node that implements the NodeRGB protocol from current tint to a custom one.
 @since v0.7.2
 */
class CC_DLL TintBy : public ActionInterval
{
public:
    /** creates an action with duration and color */
    static TintBy* create(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue);

    /** initializes the action with duration and color */
    bool initWithDuration(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue);

    //
    // Overrides
    //
    virtual TintBy* clone() const override;
	virtual TintBy* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

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
    /** creates the action */
    static DelayTime* create(float d);

    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual DelayTime* reverse() const override;
    virtual DelayTime* clone() const override;
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
    /** creates the action */
    static ReverseTime* create(FiniteTimeAction *pAction);

    virtual ~ReverseTime(void);
    ReverseTime();

    /** initializes the action */
    bool initWithAction(FiniteTimeAction *pAction);

    //
    // Overrides
    //
	virtual ReverseTime* reverse() const override;
    virtual ReverseTime* clone() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float time) override;

protected:
    FiniteTimeAction *_other;
};

class Texture2D;
/** @brief Animates a sprite given the name of an Animation */
class CC_DLL Animate : public ActionInterval
{
public:
    /** creates the action with an Animation and will restore the original frame when the animation is over */
    static Animate* create(Animation *pAnimation);

    Animate();
    virtual ~Animate();

    /** initializes the action with an Animation and will restore the original frame when the animation is over */
    bool initWithAnimation(Animation *pAnimation);

    /** sets the Animation object to be animated */
    void setAnimation( Animation* animation );
    /** returns the Animation object that is being animated */
    Animation* getAnimation() { return _animation; }
    const Animation* getAnimation() const { return _animation; }

    //
    // Overrides
    //
    virtual Animate* clone() const override;
    virtual Animate* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float t) override;

protected:
    std::vector<float>* _splitTimes;
    int             _nextFrame;
    SpriteFrame*    _origFrame;
    unsigned int    _executedLoops;
    Animation*      _animation;
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
    static TargetedAction* create(Node* target, FiniteTimeAction* pAction);

    /** Init an action with the specified action and forced target */
    bool initWithTarget(Node* target, FiniteTimeAction* pAction);

    /** Sets the target that the action will be forced to run with */
    void setForcedTarget(Node* forcedTarget);
    /** returns the target that the action is forced to run with */
    Node* getForcedTarget() { return _forcedTarget; }
    const Node* getForcedTarget() const { return _forcedTarget; }

    //
    // Overrides
    //
    virtual TargetedAction* clone() const override;
    virtual TargetedAction* reverse() const  override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float time) override;

private:
    FiniteTimeAction* _action;
    Node* _forcedTarget;
};

// end of actions group
/// @}

NS_CC_END

#endif //__ACTION_CCINTERVAL_ACTION_H__
