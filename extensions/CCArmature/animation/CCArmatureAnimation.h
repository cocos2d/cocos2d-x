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
#include "../external_tool/sigslot.h"

NS_CC_EXT_BEGIN


enum MovementEventType
{
	START,
	COMPLETE,
	LOOP_COMPLETE
};


class CCArmature;
class CCBone;

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
     * @param animationScale Scale value
     */
    virtual void setAnimationScale(float animationScale);
	virtual float getAnimationScale() const;

	/**
     * Scale animation play speed.
     * @param animationScale Scale value
     */
	virtual void setSpeedScale(float speedScale);
	virtual float getSpeedScale() const;

	//! The animation update speed
	virtual void setAnimationInternal(float animationInternal);

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
     * @param  _animationIndex  the animation index you want to play
     */
    void playByIndex(int animationIndex,  int durationTo = -1, int durationTween = -1,  int loop = -1, int tweenEasing = TWEEN_EASING_MAX);

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
     * Get current movementID;
	 * @return The name of current movement
     */
	std::string getCurrentMovementID();
protected:

    /**
     * Update(float dt) will call this handler, you can handle your logic here
     */
    void updateHandler();

    /**
     * Update current key frame, and process auto stop, pause
     */
    void updateFrameData(float currentPercent);

protected:
    //! CCAnimationData save all MovementDatas this animation used.
    CC_SYNTHESIZE_RETAIN(CCAnimationData *, m_pAnimationData, AnimationData);

	//! Scale the animation speed
	float m_fSpeedScale;

    CCMovementData *m_pMovementData;				//! CCMovementData save all MovementFrameDatas this animation used.

    CCArmature *m_pArmature;						//! A weak reference of armature

    std::string m_strMovementID;				//! Current movment's name

    int m_iToIndex;								//! The frame index in CCMovementData->m_pMovFrameDataArr, it's different from m_iFrameIndex.

    CCArray *m_pTweenList;
public:
    /**
     * MovementEvent signal. This will emit a signal when trigger a event.
	 * @param CCArmature* a CCArmature
	 * @param MovementEventType, Event Type, like START, COMPLETE.
	 * @param const char*, Movement ID, also called Movement Name
     */
    sigslot::signal3<CCArmature *, MovementEventType, const char *> MovementEventSignal;

	/**
     * FrameEvent signal. This will emit a signal when trigger a event.
	 * @param CCBone*, a CCBone
	 * @param const char*, the name of this frame event
	 * @param int, origin frame index
	 * @param int, current frame index, animation may be delayed
     */
    sigslot::signal4<CCBone *, const char *, int, int> FrameEventSignal;
};

NS_CC_EXT_END

#endif /*__CCANIMATION_H__*/
