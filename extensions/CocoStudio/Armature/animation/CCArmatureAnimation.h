/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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


#ifndef __CCANIMATION_H__
#define __CCANIMATION_H__

#include "CCProcessBase.h"
#include <queue>

NS_CC_EXT_BEGIN


enum MovementEventType
{
    START,
    COMPLETE,
    LOOP_COMPLETE
};


class CCArmature;
class CCBone;

typedef void (CCObject::*SEL_MovementEventCallFunc)(CCArmature *, MovementEventType, const char *);
typedef void (CCObject::*SEL_FrameEventCallFunc)(CCBone *, const char *, int, int);

#define movementEvent_selector(_SELECTOR) (SEL_MovementEventCallFunc)(&_SELECTOR)
#define frameEvent_selector(_SELECTOR) (SEL_FrameEventCallFunc)(&_SELECTOR)

struct CCFrameEvent
{
    CCBone *bone;
    const char *frameEventName;
    int originFrameIndex;
    int currentFrameIndex;
};

/**
 *  @lua NA
 */
class  CCArmatureAnimation : public CCProcessBase
{
public:
    /**
     * Create with a CCArmature
     * @param armature The CCArmature CCArmatureAnimation will bind to
     */
    static CCArmatureAnimation *create(CCArmature *armature);
public:
    CCArmatureAnimation();
    virtual ~CCArmatureAnimation(void);

    /**
     * Init with a CCArmature
     * @param armature The CCArmature CCArmatureAnimation will bind to
     */
    virtual bool init(CCArmature *armature);

    /**
     * Scale animation play speed.
     * This method is deprecated, please use setSpeedScale.
     * @param animationScale Scale value
     */
    CC_DEPRECATED_ATTRIBUTE virtual void setAnimationScale(float animationScale);
    CC_DEPRECATED_ATTRIBUTE virtual float getAnimationScale() const;

    /**
     * Scale animation play speed.
     * @param animationScale Scale value
     */
    virtual void setSpeedScale(float speedScale);
    virtual float getSpeedScale() const;

    //! The animation update speed
    virtual void setAnimationInternal(float animationInternal);

    using CCProcessBase::play;
    /**
     * Play animation by animation name.
     *
     * @param  animationName  The animation name you want to play
     * @param  durationTo The frames between two animation changing-over.
     *         It's meaning is changing to this animation need how many frames
     *
     *         -1 : use the value from CCMovementData get from flash design panel
     * @param  durationTween  The frame count you want to play in the game.
     *         if  _durationTween is 80, then the animation will played 80 frames in a loop
     *
     *         -1 : use the value from CCMovementData get from flash design panel
     *
     * @param  loop   Whether the animation is loop
     *
     *         loop < 0 : use the value from CCMovementData get from flash design panel
     *         loop = 0 : this animation is not loop
     *         loop > 0 : this animation is loop
     *
     * @param  tweenEasing CCTween easing is used for calculate easing effect
     *
     *         TWEEN_EASING_MAX : use the value from CCMovementData get from flash design panel
     *         -1 : fade out
     *         0  : line
     *         1  : fade in
     *         2  : fade in and out
     *
     */
    void play(const char *animationName, int durationTo = -1, int durationTween = -1,  int loop = -1, int tweenEasing = TWEEN_EASING_MAX);

    /**
     * Play animation by index, the other param is the same to play.
     * @param  animationIndex  the animation index you want to play
     */
    void playByIndex(int animationIndex,  int durationTo = -1, int durationTween = -1,  int loop = -1, int tweenEasing = TWEEN_EASING_MAX);

    /**
     * Go to specified frame and play current movement.
     * You need first switch to the movement you want to play, then call this function.
     * 
     * example : playByIndex(0);
     *           gotoAndPlay(0);
     *           playByIndex(1);
     *           gotoAndPlay(0);
     *           gotoAndPlay(15);
     */
    virtual void gotoAndPlay(int frameIndex);

    /**
     * Go to specified frame and pause current movement.
     */
    virtual void gotoAndPause(int frameIndex);

    /**
     * Pause the Process
     */
    virtual void pause();
    /**
     * Resume the Process
     */
    virtual void resume();
    /**
     * Stop the Process
     */
    virtual void stop();


    /**
     * Get movement count
     */
    int getMovementCount();

    void update(float dt);

    /**
     * Get current movementID
     * @return The name of current movement
     */
    std::string getCurrentMovementID();

    /**
     * Set armature's movement event callback function
     * To disconnect this event, just setMovementEventCallFunc(NULL, NULL);
     */
    void setMovementEventCallFunc(CCObject *target, SEL_MovementEventCallFunc callFunc);

    /**
     * Set armature's frame event callback function
     * To disconnect this event, just setFrameEventCallFunc(NULL, NULL);
     */
    void setFrameEventCallFunc(CCObject *target, SEL_FrameEventCallFunc callFunc);


    /** 
     * Returns a user assigned CCObject
     *
     * @return A user assigned CCObject
     * @js NA
     */
    virtual CCObject* getUserObject();
    /**
     * Returns a user assigned CCObject
     *
     * The UserObject will be retained once in this method,
     * and the previous UserObject (if existed) will be relese.
     * The UserObject will be released in destructure.
     *
     * @param A user assigned CCObject
     */
    virtual void setUserObject(CCObject *pUserObject);
protected:

    /**
     * Update(float dt) will call this handler, you can handle your logic here
     * @js NA
     */
    void updateHandler();

    /**
     * Update current key frame, and process auto stop, pause
     * @js NA
     */
    void updateFrameData(float currentPercent);

    /**
     * Emit a frame event
     * @js NA
     */
    void frameEvent(CCBone *bone, const char *frameEventName, int originFrameIndex, int currentFrameIndex);

    inline bool isIgnoreFrameEvent() { return m_bIgnoreFrameEvent; }

    friend class CCTween;
protected:
    //! CCAnimationData save all MovementDatas this animation used.
    CC_SYNTHESIZE_RETAIN(CCAnimationData *, m_pAnimationData, AnimationData);

    //! Scale the animation speed
    float m_fSpeedScale;

    CCMovementData *m_pMovementData;            //! CCMovementData save all MovementFrameDatas this animation used.

    CCArmature *m_pArmature;                    //! A weak reference of armature

    std::string m_strMovementID;                //! Current movment's name

    int m_iToIndex;	                            //! The frame index in CCMovementData->m_pMovFrameDataArr, it's different from m_iFrameIndex.

    CCArray *m_pTweenList;

    bool m_bIgnoreFrameEvent;

    std::queue<CCFrameEvent*> m_sFrameEventQueue;

    CCObject *m_pUserObject;
protected:
    /**
     * MovementEvent CallFunc.
     * @param CCArmature* a CCArmature
     * @param MovementEventType, Event Type, like START, COMPLETE.
     * @param const char*, Movement ID, also called Movement Name
     */
    SEL_MovementEventCallFunc m_sMovementEventCallFunc;

    /**
     * FrameEvent CallFunc.
     * @param CCBone*, a CCBone
     * @param const char*, the name of this frame event
     * @param int, origin frame index
     * @param int, current frame index, animation may be delayed
     */
    SEL_FrameEventCallFunc m_sFrameEventCallFunc;


    CCObject *m_sMovementEventTarget;
    CCObject *m_sFrameEventTarget;
};

NS_CC_EXT_END

#endif /*__CCANIMATION_H__*/
