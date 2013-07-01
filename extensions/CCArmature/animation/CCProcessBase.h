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

namespace cocos2d { namespace extension { namespace armature {

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


class  ProcessBase : public Object
{
public:
    ProcessBase(void);
    ~ProcessBase(void);

    /**
     * Play animation by animation name.
     *
     * @param  animation  It will not used in the ProcessBase Class
     * @param  durationTo The frames between two animation changing-over.
     *         It's meaning is changing to this animation need how many frames
     *
     *         -1 : use the value from MovementData get from flash design panel
     * @param  durationTween  The frame count you want to play in the game.
     *         if  _durationTween is 80, then the animation will played 80 frames in a loop
     *
     *         -1 : use the value from MovementData get from flash design panel
     *
     * @param  loop   Whether the animation is loop
     *
     *         loop < 0 : use the value from MovementData get from flash design panel
     *         loop = 0 : this animation is not loop
     *         loop > 0 : this animation is loop
     *
     * @param  tweenEasing Tween easing is used for calculate easing effect
     *
     *         TWEEN_EASING_MAX : use the value from MovementData get from flash design panel
     *         -1 : fade out
     *         0  : line
     *         1  : fade in
     *         2  : fade in and out
     *
     */
    virtual void play(void *animation, int durationTo, int durationTween,  int loop, int tweenEasing);

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


    virtual void gotoFrame(int frameIndex);

    /**
     * You should never call this function, unless you know what you do
     * Update the Process, include current process, current frame and son on
     *
     * @param The duration since last update
     */
    virtual void update(float dt);

    virtual int getCurrentFrameIndex();

protected:


    /**
     * Update(float dt) will call this handler, you can handle your logic here
     */
    virtual void updateHandler() {};

protected:
	//! Scale the animation speed
	CC_SYNTHESIZE_PASS_BY_REF(float, _animationScale, AnimationScale);

    //! Set and get whether the aniamtion is pause
    CC_SYNTHESIZE_PASS_BY_REF(bool, _isPause, IsPause);

    //! Set and get whether the aniamtion is complete
    CC_SYNTHESIZE_PASS_BY_REF(bool, _isComplete, IsComplete);

    //! Set and get whether the aniamtion is playing
    CC_SYNTHESIZE_PASS_BY_REF(bool, _isPlaying, IsPlaying);

    //! Current percent this process arrived
    CC_SYNTHESIZE_PASS_BY_REF(float, _currentPercent, CurrentPercent);

    //! The raw duration
    CC_SYNTHESIZE_PASS_BY_REF(int, _rawDuration, RawDuration);

    //! The animation whether or not loop
    CC_SYNTHESIZE_PASS_BY_REF(AnimationType, _loopType, LoopType);

    //! The tween easing effect
    CC_SYNTHESIZE_PASS_BY_REF(TweenType, _tweenEasing, TweenEasing);

    //! The animation update speed
    CC_SYNTHESIZE_PASS_BY_REF(float, _animationInternal, AnimationInternal);


protected:
    //! The durantion frame count will run
    int _durationTween;

    //! Current frame this process arrived, this frame is tween frame
    float _currentFrame;
    //! Frame index it the time line
    int _curFrameIndex;

    //! Next frame this process need run to
    int _nextFrameIndex;


    bool _isLoopBack;
};

}}} // namespace cocos2d { namespace extension { namespace armature {

#endif /*__CCPROCESSBASE_H__*/
