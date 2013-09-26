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
    inline float getElapsed(void) { return m_elapsed; }

    /** initializes the action */
    bool initWithDuration(float d);

    /** returns true if the action has finished */
    virtual bool isDone(void);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void step(float dt);
    virtual void startWithTarget(CCNode *pTarget);
    /** returns a reversed action */
    virtual CCActionInterval* reverse(void);

public:

    /** creates the action */
    static CCActionInterval* create(float d);

public:
    //extension in CCGridAction 
    void setAmplitudeRate(float amp);
    float getAmplitudeRate(void);

protected:
    float m_elapsed;
    bool   m_bFirstTick;
};

/** @brief Runs actions sequentially, one after another
 */
class CC_DLL CCSequence : public CCActionInterval
{
public:
    /**
     * @js NA
     * @lua NA
     */
    ~CCSequence(void);

    /** initializes the action 
     * @lua NA
     */
    bool initWithTwoActions(CCFiniteTimeAction *pActionOne, CCFiniteTimeAction *pActionTwo);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    /**
     * @lua NA
     */
    virtual void startWithTarget(CCNode *pTarget);
    /**
     * @lua NA
     */
    virtual void stop(void);
    /**
     * @lua NA
     */
    virtual void update(float t);
    virtual CCActionInterval* reverse(void);

public:

    /** helper constructor to create an array of sequenceable actions 
     * @lua NA
     */
    static CCSequence* create(CCFiniteTimeAction *pAction1, ...);
    /** helper constructor to create an array of sequenceable actions given an array 
     * @js NA
     */
    static CCSequence* create(CCArray *arrayOfActions);
    /** helper constructor to create an array of sequence-able actions 
     * @js NA
     * @lua NA
     */
    static CCSequence* createWithVariableList(CCFiniteTimeAction *pAction1, va_list args);
    /** creates the action 
     * @js NA
     */
    static CCSequence* createWithTwoActions(CCFiniteTimeAction *pActionOne, CCFiniteTimeAction *pActionTwo);

protected:
    CCFiniteTimeAction *m_pActions[2];
    float m_split;
    int m_last;
};

/** @brief Repeats an action a number of times.
 * To repeat an action forever use the CCRepeatForever action.
 */
class CC_DLL CCRepeat : public CCActionInterval
{
public:
    /**
     *  @js NA
     *  @lua NA
     */
    ~CCRepeat(void);

    /** initializes a CCRepeat action. Times is an unsigned integer between 1 and pow(2,30) */
    bool initWithAction(CCFiniteTimeAction *pAction, unsigned int times);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void stop(void);
    virtual void update(float dt);
    virtual bool isDone(void);
    virtual CCActionInterval* reverse(void);

    inline void setInnerAction(CCFiniteTimeAction *pAction)
    {
        if (m_pInnerAction != pAction)
        {
            CC_SAFE_RETAIN(pAction);
            CC_SAFE_RELEASE(m_pInnerAction);
            m_pInnerAction = pAction;
        }
    }

    inline CCFiniteTimeAction* getInnerAction()
    {
        return m_pInnerAction;
    }

public:

    /** creates a CCRepeat action. Times is an unsigned integer between 1 and pow(2,30) */
    static CCRepeat* create(CCFiniteTimeAction *pAction, unsigned int times);
protected:
    unsigned int m_uTimes;
    unsigned int m_uTotal;
    float m_fNextDt;
    bool m_bActionInstant;
    /** Inner action */
    CCFiniteTimeAction *m_pInnerAction;
};

/** @brief Repeats an action for ever.
To repeat the an action for a limited number of times use the Repeat action.
@warning This action can't be Sequenceable because it is not an IntervalAction
*/
class CC_DLL CCRepeatForever : public CCActionInterval
{
public:
    /**
     *  @js ctor
     */
    CCRepeatForever()
        : m_pInnerAction(NULL)
    {}
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCRepeatForever();

    /** initializes the action */
    bool initWithAction(CCActionInterval *pAction);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void startWithTarget(CCNode* pTarget);
    virtual void step(float dt);
    virtual bool isDone(void);
    virtual CCActionInterval* reverse(void);

    inline void setInnerAction(CCActionInterval *pAction)
    {
        if (m_pInnerAction != pAction)
        {
            CC_SAFE_RELEASE(m_pInnerAction);
            m_pInnerAction = pAction;
            CC_SAFE_RETAIN(m_pInnerAction);
        }
    }

    inline CCActionInterval* getInnerAction()
    {
        return m_pInnerAction;
    }

public:

    /** creates the action */
    static CCRepeatForever* create(CCActionInterval *pAction);
protected:
    /** Inner action */
    CCActionInterval *m_pInnerAction;
};

/** @brief Spawn a new action immediately
 */
class CC_DLL CCSpawn : public CCActionInterval
{
public:
    /**
     * @js NA
     * @lua NA
     */
    ~CCSpawn(void);

    /** initializes the Spawn action with the 2 actions to spawn 
     * @lua NA
     */
    bool initWithTwoActions(CCFiniteTimeAction *pAction1, CCFiniteTimeAction *pAction2);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    /**
     * @lua NA
     */
    virtual void startWithTarget(CCNode *pTarget);
    /**
     * @lua NA
     */
    virtual void stop(void);
    /**
     * @lua NA
     */
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);

public:

    /** helper constructor to create an array of spawned actions 
     * @lua NA
     */
    static CCSpawn* create(CCFiniteTimeAction *pAction1, ...);
    
    /** helper constructor to create an array of spawned actions 
     * @js  NA
     * @lua NA
     */
    static CCSpawn* createWithVariableList(CCFiniteTimeAction *pAction1, va_list args);

    /** helper constructor to create an array of spawned actions given an array 
     * @js NA
     */
    static CCSpawn* create(CCArray *arrayOfActions);

    /** creates the Spawn action 
     * @js NA
     */
    static CCSpawn* createWithTwoActions(CCFiniteTimeAction *pAction1, CCFiniteTimeAction *pAction2);

protected:
    CCFiniteTimeAction *m_pOne;
    CCFiniteTimeAction *m_pTwo;
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
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    
protected:
    float m_fDstAngleX;
    float m_fStartAngleX;
    float m_fDiffAngleX;
    
    float m_fDstAngleY;
    float m_fStartAngleY;
    float m_fDiffAngleY;
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
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    
protected:
    float m_fAngleX;
    float m_fStartAngleX;
    float m_fAngleY;
    float m_fStartAngleY;
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
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual CCActionInterval* reverse(void);
    virtual void update(float time);

public:
    /** creates the action */
    static CCMoveBy* create(float duration, const CCPoint& deltaPosition);
protected:
    CCPoint m_positionDelta;
    CCPoint m_startPosition;
    CCPoint m_previousPosition;
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
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);

public:
    /** creates the action */
    static CCMoveTo* create(float duration, const CCPoint& position);
protected:
    CCPoint m_endPosition;
};

/** Skews a CCNode object to given angles by modifying it's skewX and skewY attributes
@since v1.0
*/
class CC_DLL CCSkewTo : public CCActionInterval
{
public:
    /**
     *  @js ctor
     */
    CCSkewTo();
    virtual bool initWithDuration(float t, float sx, float sy);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

public:

    /** creates the action */
    static CCSkewTo* create(float t, float sx, float sy);
protected:
    float m_fSkewX;
    float m_fSkewY;
    float m_fStartSkewX;
    float m_fStartSkewY;
    float m_fEndSkewX;
    float m_fEndSkewY;
    float m_fDeltaX;
    float m_fDeltaY;
};

/** Skews a CCNode object by skewX and skewY degrees
@since v1.0
*/
class CC_DLL CCSkewBy : public CCSkewTo
{
public:
    virtual bool initWithDuration(float t, float sx, float sy);
    virtual void startWithTarget(CCNode *pTarget);
    virtual CCActionInterval* reverse(void);

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
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);

public:
    /** creates the action */
    static CCJumpBy* create(float duration, const CCPoint& position, float height, unsigned int jumps);
protected:
    CCPoint         m_startPosition;
    CCPoint         m_delta;
    float           m_height;
    unsigned int    m_nJumps;
    CCPoint         m_previousPos;
};

/** @brief Moves a CCNode object to a parabolic position simulating a jump movement by modifying it's position attribute.
*/ 
class CC_DLL CCJumpTo : public CCJumpBy
{
public:
    virtual void startWithTarget(CCNode *pTarget);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);

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
    /** initializes the action with a duration and a bezier configuration 
     *  @lua NA
     */
    bool initWithDuration(float t, const ccBezierConfig& c);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    /**
     *  @lua NA
     */
    virtual void startWithTarget(CCNode *pTarget);
    /**
     *  @lua NA
     */
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);

public:
    /** creates the action with a duration and a bezier configuration 
     *  @code
     *  when this function bound to js,the input params are changed
     *  js: var create(var t, var pointTable)
     *  @endcode
     */
    static CCBezierBy* create(float t, const ccBezierConfig& c);
protected:
    ccBezierConfig m_sConfig;
    CCPoint m_startPosition;
    CCPoint m_previousPosition;
};

/** @brief An action that moves the target with a cubic Bezier curve to a destination point.
 @since v0.8.2
 */
class CC_DLL CCBezierTo : public CCBezierBy
{
public:
    /**
     *  @lua NA
     */
    virtual void startWithTarget(CCNode *pTarget);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** creates the action with a duration and a bezier configuration
     *  @code
     *  when this function bound to js,the input params are changed
     *  js: var create(var t, var pointTable)
     *  @endcode
     */
    static CCBezierTo* create(float t, const ccBezierConfig& c);
    /**
     *  @lua NA
     */
    bool initWithDuration(float t, const ccBezierConfig &c);
    
protected:
    ccBezierConfig m_sToConfig;
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
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

public:

    /** creates the action with the same scale factor for X and Y */
    static CCScaleTo* create(float duration, float s);

    /** creates the action with and X factor and a Y factor */
    static CCScaleTo* create(float duration, float sx, float sy);
protected:
    float m_fScaleX;
    float m_fScaleY;
    float m_fStartScaleX;
    float m_fStartScaleY;
    float m_fEndScaleX;
    float m_fEndScaleY;
    float m_fDeltaX;
    float m_fDeltaY;
};

/** @brief Scales a CCNode object a zoom factor by modifying it's scale attribute.
*/
class CC_DLL CCScaleBy : public CCScaleTo
{
public:
    virtual void startWithTarget(CCNode *pTarget);
    virtual CCActionInterval* reverse(void);
    /**
     *  @js NA
     *  @lua NA
     */
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
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);

public:

    /** creates the action */
    static CCBlink* create(float duration, unsigned int uBlinks);
    
    virtual void startWithTarget(CCNode *pTarget);
    virtual void stop();
    
protected:
    unsigned int m_nTimes;
    bool m_bOriginalState;
};

/** @brief Fades In an object that implements the CCRGBAProtocol protocol. It modifies the opacity from 0 to 255.
 The "reverse" of this action is FadeOut
 */
class CC_DLL CCFadeIn : public CCActionInterval
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    /**
     *  @js NA
     *  @lua NA
     */
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
    virtual CCActionInterval* reverse(void);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);

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
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

public:
    /** creates an action with duration and opacity */
    static CCFadeTo* create(float duration, GLubyte opacity);
protected:
    GLubyte m_toOpacity;
    GLubyte m_fromOpacity;
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
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

public:
    /** creates an action with duration and color */
    static CCTintTo* create(float duration, GLubyte red, GLubyte green, GLubyte blue);
protected:
    ccColor3B m_to;
    ccColor3B m_from;
};

/** @brief Tints a CCNode that implements the CCNodeRGB protocol from current tint to a custom one.
 @since v0.7.2
 */
class CC_DLL CCTintBy : public CCActionInterval
{
public:
    /** initializes the action with duration and color */
    bool initWithDuration(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);

public:
    /** creates an action with duration and color */
    static CCTintBy* create(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue);
protected:
    GLshort m_deltaR;
    GLshort m_deltaG;
    GLshort m_deltaB;

    GLshort m_fromR;
    GLshort m_fromG;
    GLshort m_fromB;
};

/** @brief Delays the action a certain amount of seconds
*/
class CC_DLL CCDelayTime : public CCActionInterval
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    /**
     *  @js NA
     *  @lua NA
     */
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
    /**
     *  @js ctor
     */
    ~CCReverseTime(void);
    /**
     *  @js NA
     *  @lua NA
     */
    CCReverseTime();

    /** initializes the action */
    bool initWithAction(CCFiniteTimeAction *pAction);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void stop(void);
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);

public:
    /** creates the action */
    static CCReverseTime* create(CCFiniteTimeAction *pAction);
protected:
    CCFiniteTimeAction *m_pOther;
};

class CCTexture2D;
/** @brief Animates a sprite given the name of an Animation */
class CC_DLL CCAnimate : public CCActionInterval
{
public:
    /**
     *  @js ctor
     */
    CCAnimate();
    /**
     *  @js NA
     *  @lua NA
     */
    ~CCAnimate();

    /** initializes the action with an Animation and will restore the original frame when the animation is over */
    bool initWithAnimation(CCAnimation *pAnimation);

    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void stop(void);
    virtual void update(float t);
    virtual CCActionInterval* reverse(void);

public:
    /** creates the action with an Animation and will restore the original frame when the animation is over */
    static CCAnimate* create(CCAnimation *pAnimation);
    CC_SYNTHESIZE_RETAIN(CCAnimation*, m_pAnimation, Animation)
protected:
    std::vector<float>* m_pSplitTimes;
    int                m_nNextFrame;
    CCSpriteFrame*  m_pOrigFrame;
       unsigned int    m_uExecutedLoops;
};

/** Overrides the target of an action so that it always runs on the target
 * specified at action creation rather than the one specified by runAction.
 */
class CC_DLL CCTargetedAction : public CCActionInterval
{
public:
    /**
     *  @js ctor
     */
    CCTargetedAction();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTargetedAction();

    /** Create an action with the specified action and forced target */
    static CCTargetedAction* create(CCNode* pTarget, CCFiniteTimeAction* pAction);

    /** Init an action with the specified action and forced target */
    bool initWithTarget(CCNode* pTarget, CCFiniteTimeAction* pAction);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void stop(void);
    virtual void update(float time);

    /** This is the target that the action will be forced to run with */
    CC_SYNTHESIZE_RETAIN(CCNode*, m_pForcedTarget, ForcedTarget);
private:
    CCFiniteTimeAction* m_pAction;
};

// end of actions group
/// @}

NS_CC_END

#endif //__ACTION_CCINTERVAL_ACTION_H__
