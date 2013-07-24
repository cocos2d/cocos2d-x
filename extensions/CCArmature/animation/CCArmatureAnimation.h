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

namespace cocos2d { namespace extension { namespace armature {


enum MovementEventType
{
	START,
	COMPLETE,
	LOOP_COMPLETE
};


class Armature;
class Bone;

class  ArmatureAnimation : public ProcessBase
{
public:
    /**
     * Create with a Armature
     * @param armature The Armature ArmatureAnimation will bind to
     */
    static ArmatureAnimation *create(Armature *armature);
public:
    ArmatureAnimation();
    virtual ~ArmatureAnimation(void);

    /**
     * Init with a Armature
     * @param armature The Armature ArmatureAnimation will bind to
     */
    virtual bool init(Armature *armature);

    /**
     * Scale animation play speed.
     * @param animationScale Scale value
     */
    virtual void setAnimationScale(float animationScale);

    /**
     * Play animation by animation name.
     *
     * @param  animationName  The animation name you want to play
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
    //! AnimationData save all MovementDatas this animation used.
    CC_SYNTHESIZE_RETAIN(AnimationData *, _animationData, AnimationData);


    MovementData *_movementData;				//! MovementData save all MovementFrameDatas this animation used.

    Armature *_armature;						//! A weak reference of armature

    std::string _movementID;				//! Current movment's name

    int _prevFrameIndex;						//! Prev key frame index
    int _toIndex;								//! The frame index in MovementData->_movFrameDataArr, it's different from _frameIndex.

    Array *_tweenList;
public:
    /**
     * MovementEvent signal. This will emit a signal when trigger a event.
     * The 1st param is the Armature. The 2nd param is Event Type, like START, COMPLETE. The 3rd param is Movement ID, also called Movement Name.
     */
    sigslot::signal3<Armature *, MovementEventType, const char *> MovementEventSignal;

    sigslot::signal2<Bone *, const char *> FrameEventSignal;
};

}}} // namespace cocos2d { namespace extension { namespace armature {

#endif /*__CCANIMATION_H__*/
