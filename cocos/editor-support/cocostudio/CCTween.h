/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "cocostudio/CCProcessBase.h"
#include "2d/CCTweenFunction.h"
#include "cocostudio/CocosStudioExport.h"

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
     * @~english Create with a Bone
     * @~chinese 用一段骨头来创建缓动
     * @param bone @~english the Bone Tween will bind to
     * @~chinese 用来绑定缓动的一段骨头
     */
    static Tween *create(Bone *bone);
public:
    Tween(void);
    virtual ~Tween(void);

    /**
     * @~english Init with a Bone
     * @~chinese 用一段骨头来初始化缓动
     * @param bone @~english the Bone Tween will bind to
     * @~chinese 用来绑定缓动的一段骨头
     */
    virtual bool init(Bone *bone);

    using ProcessBase::play;
    /**
     * @~english Start the Process
     *
     * @param  movementBoneData  @~english the MovementBoneData include all FrameData
     * @~chinese 活动骨头数据，包含所有帧数据
     * @param  durationTo @~english the number of frames changing to this animation needs.
     * @~chinese 改变到该动画需要的总帧数。
     * @param  durationTween  @~english the number of frames this animation actual last.
     * @~chinese 该段动画实际包含的总帧数
     * @param  loop @~english   whether the animation is loop
     *
     *         loop < 0 : use the value from MovementData get from Action Editor
     *         loop = 0 : this animation is not loop
     *         loop > 0 : this animation is loop
     * @~chinese 动画是否循环。
     *         loop < 0 : 使用从动作编辑器中获得的活动数据中的的值
     *         loop = 0 : 动画不循环
     *         loop > 0 : 动画循环
     *
     * @param  tweenEasing  @~english    tween easing is used for calculate easing effect
     *
     *         TWEEN_EASING_MAX : use the value from MovementData get from Action Editor
     *         -1 : fade out
     *         0  : line
     *         1  : fade in
     *         2  : fade in and out
     * @~chinese 帧补间缓动用来计算缓动效果
     *         TWEEN_EASING_MAX : 使用从动作编辑器中获得的活动数据中的的值
     *         -1 : 淡出
     *         0  : 线性
     *         1  : 淡入
     *         2  : 淡入淡出
     */
    virtual void play(MovementBoneData *movementBoneData, int durationTo, int durationTween,  int loop, int tweenEasing);

    /*
    * @~english Set animation.
    * @~chinese 设置动画。
    * @param animation @~english The animation.
    * @~chinese 动画。
    */
    inline void setAnimation(ArmatureAnimation *animation) { _animation = animation; }
    /*
    * @~english Get animation.
    * @~chinese 获取动画。
    * @return @~english The animation.
    * @~chinese 动画。
    */
    inline ArmatureAnimation *getAnimation() const { return _animation; }

    /**
    * @~english Go to specified frame and play current movement.
    * @~chinese 跳转至指定的帧并从该帧开始播放当前动作。
    * @param frameIndex @~english Index of frame.
    * @~chinese 要跳转的帧索引。
    */
    virtual void gotoAndPlay(int frameIndex);
    /**
    * @~english Go to specified frame and pause current movement.
    * @~chinese 跳转至指定的帧并暂停当前动作。
    * @param frameIndex @~english Index of frame.
    * @~chinese 要跳转的帧索引。
    */
    virtual void gotoAndPause(int frameIndex);

    /*
    * @~english Set movBoneData.
    * @~chinese 设置活动骨头数据。
    * @param data @~english The movBoneData.
    * @~chinese 活动骨头数据。
    */
    virtual void setMovementBoneData(MovementBoneData *data) { _movementBoneData = data; }
    /*
    * @~english Get movBoneData.
    * @~chinese 获取活动骨头数据。
    * @return @~english The movBoneData.
    * @~chinese 活动骨头数据。
    */
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

    TweenType _frameTweenEasing;  //! Dedermine which tween effect current frame use

    int _betweenDuration;           //! Current key frame will last _betweenDuration frames
    int _totalDuration;


    int _fromIndex;				    //! The current frame index in FrameList of MovementBoneData, it's different from m_iFrameIndex
    int _toIndex;                   //! The next frame index in FrameList of MovementBoneData, it's different from m_iFrameIndex

    ArmatureAnimation *_animation;

    bool _passLastFrame;            //! If current frame index is more than the last frame's index
};

}

#endif /*__CCTWEEN_H__*/
