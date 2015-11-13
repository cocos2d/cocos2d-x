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

#ifndef __CCPROCESSBASE_H__
#define __CCPROCESSBASE_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDatas.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {


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
class  CC_STUDIO_DLL ProcessBase : public cocos2d::Ref
{
public:
    ProcessBase(void);
    virtual ~ProcessBase(void);

    /**
     * @~english Play animation by animation name.
     * @~chinese 根据动画名称播放动画。
     *
     * @param  durationTo @~english The frames between two animation changing-over.
     *         It's meaning is changing to this animation need how many frames
     *
     *         -1 : use the value from MovementData get from flash design panel
     * @~chinese 两个动画切换时的需要的帧数。意味着切换到该动画时需要多少帧。
     *    -1：使用Flash的设计面板中MovementData中的值
     *
     * @param  durationTween  @~english The frame count you want to play in the game.
     *         if  _durationTween is 80, then the animation will played 80 frames in a loop
     *
     *         -1 : use the value from MovementData get from flash design panel
     * @~chinese 要在游戏中播放的帧总数。如果设置成80，则在动画将在循环中每次播放80帧。
     * -1：使用Flash的设计面板中MovementData中的值
     *
     * @param  loop @~english   Whether the animation is loop
     *
     *         loop < 0 : use the value from MovementData get from flash design panel
     *         loop = 0 : this animation is not loop
     *         loop > 0 : this animation is loop
     * @~chinese 动画是否循环。
     *         loop < 0 : 使用Flash的设计面板中MovementData中的值
     *         loop = 0 : 不循环
     *         loop > 0 : 循环
     *
     * @param  tweenEasing @~english Tween easing is used for calculate easing effect
     *
     *         TWEEN_EASING_MAX : use the value from MovementData get from flash design panel
     *         -1 : fade out
     *         0  : line
     *         1  : fade in
     *         2  : fade in and out
     * @~chinese 帧补间缓动用来计算缓动效果
     *         TWEEN_EASING_MAX : 使用Flash的设计面板中MovementData中的值
     *         -1 : 淡出
     *         0  : 线性
     *         1  : 淡入
     *         2  : 淡入淡出
     *
     */
    virtual void play(int durationTo, int durationTween,  int loop, int tweenEasing);

    /**
     * @~english Pause the Process
     * @~chinese 暂停进程
     */
    virtual void pause();
    /**
     * @~english Resume the Process
     * @~chinese 恢复进程
     */
    virtual void resume();
    /**
     * @~english Stop the Process
     * @~chinese 停止进程
     */
    virtual void stop();


    /**
     * @~english You should never call this function, unless you know what you do
     * Update the Process, include current process, current frame and son on
     * @~chinese 此方法不应被调用，除非你知道要做的事情。更新进度，包含当前进度，当前帧等等。
     *
     * @param dt @~english The duration since last update
     * @~chinese 从上次updat到现在的时间间隔。
     */
    virtual void update(float dt);

    /**
    * @~english Get current frame index.
    * @~chinese 获取当前帧索引。
    * @return @~english Current frame index.
    * @~chinese 当前帧索引。
    */
    virtual int getCurrentFrameIndex();

    /**
    * @~english Set process scale.
    * @~chinese 设置进度缩放值。
    * @param processScale @~english Process scale.
    * @~chinese 进度缩放值。
    */
    virtual void setProcessScale(float processScale) { _processScale = processScale; }
    /**
    * @~english Get process scale.
    * @~chinese 获取进度缩放值。
    * @return @~english Process scale.
    * @~chinese 进度缩放值。
    */
    virtual float getProcessScale() const { return _processScale; }

    /**
    * @~english Set is pause.
    * @~chinese 设置是否暂停。
    * @param pause @~english Is pause.
    * @~chinese 是否暂停。
    */
    virtual void setIsPause(bool pause) { _isPause = pause; }
    /**
    * @~english Get is pause.
    * @~chinese 获取是否暂停。
    * @return @~english Is pause.
    * @~chinese 是否暂停。
    */
    virtual bool isPause() const { return _isPause; }

    /**
    * @~english Set is complete.
    * @~chinese 设置是否完成。
    * @param complete @~english Is complete.
    * @~chinese 是否完成。
    */
    virtual void setIsComplete(bool complete) { _isComplete = complete; }
    /**
    * @~english Get is complete.
    * @~chinese 获取是否完成。
    * @return @~english Is complete.
    * @~chinese 是否完成。
    */
    virtual bool isComplete() const { return _isComplete; }

    /**
    * @~english Set is playing.
    * @~chinese 设置是否在播放。
    * @param complete @~english Is playing.
    * @~chinese 是否在播放。
    */
    virtual void setIsPlaying(bool playing) { _isPlaying = playing; }
    /**
    * @~english Set is playing.
    * @~chinese 设置是否在播放。
    * @return @~english Is playing.
    * @~chinese 是否在播放。
    */
    virtual bool isPlaying() const { return _isPlaying; }

    /**
    * @~english Get current percent.
    * @~chinese 获取当前进度。
    * @return @~english Current percent.
    * @~chinese 当前进度。
    */
    virtual float getCurrentPercent() const { return _currentPercent; }

    /**
    * @~english Get raw duration.
    * @~chinese 获取原始总长。
    * @return @~english Raw duration.
    * @~chinese 原始总长。
    */
    virtual int getRawDuration() const { return _rawDuration; }

protected:

    virtual void gotoFrame(int frameIndex);

    /**
     * Update(float dt) will call this handler, you can handle your logic here
     */
    virtual void updateHandler() {};

protected:
    //! Scale the process speed
    float _processScale;

    //! Set and get whether the animation is pause
    bool _isPause;

    //! Set and get whether the animation is complete
    bool _isComplete;

    //! Set and get whether the animation is playing
    bool _isPlaying;

    //! Current percent this process arrived
    float _currentPercent;

    //! The raw duration
    int _rawDuration;

    //! The animation whether or not loop
    AnimationType _loopType;

    //! The tween easing effect
    cocos2d::tweenfunc::TweenType _tweenEasing;

    //! The animation update speed
    float _animationInternal;


protected:
    //! The duration frame count will run
    int _durationTween;

    //! Current frame this process arrived, this frame is tween frame
    float _currentFrame;
    //! Frame index it the time line
    int _curFrameIndex;

    //! Next frame this process need run to
    int _nextFrameIndex;


    bool _isLoopBack;
};

}

#endif /*__CCPROCESSBASE_H__*/
