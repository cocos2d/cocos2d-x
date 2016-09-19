/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.

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


#ifndef __CCTWEEN_H__
#define __CCTWEEN_H__

#include "editor-support/cocostudio/CCProcessBase.h"
#include "2d/CCTweenFunction.h"
#include "editor-support/cocostudio/CocosStudioExport.h"

namespace cocostudio {

class Bone;
class ArmatureAnimation;
using cocos2d::tweenfunc::TweenType;

/**
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL Tween : public ProcessBase
{
public:
    /**
     * Create with a Bone
     * @param bone the Bone Tween will bind to
     */
    static Tween *create(Bone *bone);
public:
    Tween(void);
    virtual ~Tween(void);

    /**
     * Init with a Bone
     * @param bone the Bone Tween will bind to
     */
    virtual bool init(Bone *bone);

    using ProcessBase::play;
    /**
     * Start the Process
     *
     * @param  movementBoneData  the MovementBoneData include all FrameData
     * @param  durationTo the number of frames changing to this animation needs.
     * @param  durationTween  the number of frames this animation actual last.
     *
     * @param  loop   whether the animation is loop
     *
     *         loop < 0 : use the value from MovementData get from Action Editor
     *         loop = 0 : this animation is not loop
     *         loop > 0 : this animation is loop
     *
     * @param  tweenEasing    tween easing is used for calculate easing effect
     *
     *         TWEEN_EASING_MAX : use the value from MovementData get from Action Editor
     *         -1 : fade out
     *         0  : line
     *         1  : fade in
     *         2  : fade in and out
     *
     */
    virtual void play(MovementBoneData *movementBoneData, int durationTo, int durationTween,  int loop, int tweenEasing);

    inline void setAnimation(ArmatureAnimation *animation) { _animation = animation; }
    inline ArmatureAnimation *getAnimation() const { return _animation; }

    virtual void gotoAndPlay(int frameIndex);
    virtual void gotoAndPause(int frameIndex);

    virtual void setMovementBoneData(MovementBoneData *data) { _movementBoneData = data; }
    virtual const MovementBoneData *getMovementBoneData() const { return _movementBoneData; }
protected:

    /**
     * Update(float dt) will call this handler, you can handle your logic here
     */
    virtual void updateHandler();

    /**
     * Calculate which frame arrived, and if current frame have event, then call the event listener
     */
    virtual float updateFrameData(float currentPercent);

    /**
     * Calculate the between value of _from and _to, and give it to between frame data
     */
    virtual void setBetween(FrameData *from, FrameData *to, bool limit = true);

    /**
     * According to the percent to calculate current FrameData with tween effect
     */
    virtual FrameData *tweenNodeTo(float percent, FrameData *node = nullptr);

    /**
     * According to the percent to calculate current color with tween effect
     */
    virtual void tweenColorTo(float percent, FrameData *node);

    /**
     * Update display index and process the key frame event when arrived a key frame
     */
    virtual void arriveKeyFrame(FrameData *keyFrameData);
protected:
    //! A weak reference to the current MovementBoneData. The data is in the data pool
    MovementBoneData *_movementBoneData;

    FrameData *_tweenData;          //! The computational tween frame data, //! A weak reference to the Bone's tweenData
    FrameData *_from;               //! From frame data, used for calculate between value
    FrameData *_to;                 //! To frame data, used for calculate between value
    FrameData *_between;            //! Between frame data, used for calculate current FrameData(m_pNode) value


    Bone *_bone;                    //! A weak reference to the Bone

    TweenType _frameTweenEasing;  //! Determine which tween effect current frame use

    int _betweenDuration;           //! Current key frame will last _betweenDuration frames
    int _totalDuration;


    int _fromIndex;                    //! The current frame index in FrameList of MovementBoneData, it's different from m_iFrameIndex
    int _toIndex;                   //! The next frame index in FrameList of MovementBoneData, it's different from m_iFrameIndex

    ArmatureAnimation *_animation;

    bool _passLastFrame;            //! If current frame index is more than the last frame's index
};

}

#endif /*__CCTWEEN_H__*/
