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


#ifndef __CCPROCESSBASE_H__
#define __CCPROCESSBASE_H__

#include "../utils/CCArmatureDefine.h"
#include "../datas/CCDatas.h"

NS_CC_EXT_BEGIN

enum AnimationType
{
    SINGLE_FRAME = -4,          //! the animation just have one frame
    ANIMATION_NO_LOOP,          //! the animation isn't loop

    ANIMATION_TO_LOOP_FRONT,    //! the animation loop from front
    ANIMATION_TO_LOOP_BACK,     //! the animation loop from back

    ANIMATION_LOOP_FRONT,       //! the animation loop from front
    ANIMATION_LOOP_BACK,        //! the animation loop from back

    ANIMATION_MAX,

};

/**
 *  @js NA
 *  @lua NA
 */
class  CC_EX_DLL CCProcessBase : public CCObject
{
public:
    CCProcessBase(void);
    ~CCProcessBase(void);

    /**
     * Play animation by animation name.
     *
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
    virtual void play(int durationTo, int durationTween,  int loop, int tweenEasing);

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
     * You should never call this function, unless you know what you do
     * Update the Process, include current process, current frame and son on
     *
     * @param The duration since last update
     */
    virtual void update(float dt);

    virtual int getCurrentFrameIndex();

protected:

    virtual void gotoFrame(int frameIndex);

    /**
     * Update(float dt) will call this handler, you can handle your logic here
     */
    virtual void updateHandler() {};

protected:
    //! Scale the process speed
    CC_SYNTHESIZE(float, m_fProcessScale, ProcessScale);

    //! Set and get whether the aniamtion is pause
    CC_SYNTHESIZE(bool, m_bIsPause, IsPause);

    //! Set and get whether the aniamtion is complete
    CC_SYNTHESIZE(bool, m_bIsComplete, IsComplete);

    //! Set and get whether the aniamtion is playing
    CC_SYNTHESIZE(bool, m_bIsPlaying, IsPlaying);

    //! Current percent this process arrived
    CC_SYNTHESIZE(float, m_fCurrentPercent, CurrentPercent);

    //! The raw duration
    CC_SYNTHESIZE(int, m_iRawDuration, RawDuration);

    //! The animation whether or not loop
    CC_SYNTHESIZE(AnimationType, m_eLoopType, LoopType);

    //! The tween easing effect
    CC_SYNTHESIZE(CCTweenType, m_eTweenEasing, TweenEasing);

protected:
    //! The durantion frame count will run
    int m_iDurationTween;

    //! Current frame this process arrived, this frame is tween frame
    float m_fCurrentFrame;
    //! Frame index it the time line
    int m_iCurFrameIndex;

    //! Next frame this process need run to
    int m_iNextFrameIndex;


    bool m_bIsLoopBack;

    //! The animation update speed
    float m_fAnimationInternal;
};

NS_CC_EXT_END

#endif /*__CCPROCESSBASE_H__*/
