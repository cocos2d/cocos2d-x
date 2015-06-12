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

#ifndef __CCTIMELINE_ACTION_H__
#define __CCTIMELINE_ACTION_H__

#include "CCTimeLine.h"
#include "cocostudio/CocosStudioExport.h"
#include "2d/CCAction.h"

NS_TIMELINE_BEGIN

struct AnimationInfo
{
    AnimationInfo():startIndex(0),endIndex(0){}
    AnimationInfo(const std::string& otherName, int otherStartIndex, int otherEndIndex)
    :name(otherName),
    startIndex(otherStartIndex),
    endIndex(otherEndIndex)
    {
    }
    std::string name;
    int startIndex;
    int endIndex;
};

class CC_STUDIO_DLL ActionTimelineData : public cocos2d::Ref
{
public:
    /**
    * @~english Allocates and initializes an `ActionTimelineData`.
    * @~chinese 分配并且初始化一段`ActionTimelineData`对象。
    * @param actionTag @~english Action tag.
    * @~chinese 动作TAG。
    * @return @~english An initialized `ActionTimelineData` which is marked as "autorelease".
    * @~chinese 一个初始化过并且设置为自动释放的`ActionTimelineData`对象。
    */
    static ActionTimelineData* create(int actionTag);

    /**
    * @~english Set action tag.
    * @~chinese 设置动作TAG。
    * @param actionTag @~english Action tag.
    * @~chinese 动作TAG。
    */
    virtual void setActionTag(int actionTag) { _actionTag = actionTag; }
    /**
    * @~english Get action tag.
    * @~chinese 获取动作TAG。
    * @return @~english Action tag.
    * @~chinese 动作TAG。
    */
    virtual int getActionTag() const { return _actionTag; }
CC_CONSTRUCTOR_ACCESS:
    ActionTimelineData();
    /**
    * @~english Initializes an `ActionTimelineData`.
    * @~chinese 初始化一段`ActionTimelineData`。
    * @param actionTag  @~english Action tag.
    * @~chinese 动作TAG。
    */
    virtual bool init(int actionTag);
protected:
    int _actionTag;
};


class CC_STUDIO_DLL ActionTimeline : public cocos2d::Action
{
public:
    friend class Frame;

    /**
    * @~english Allocates and initializes an `ActionTimeline`.
    * @~chinese 分配并且初始化一段`ActionTimeline`对象。
    * @param actionTag @~english Action tag.
    * @~chinese 动作TAG。
    * @return @~english An initialized `ActionTimeline` which is marked as "autorelease".
    * @~chinese 一个初始化过并且设置为自动释放的`ActionTimeline`对象。
    */
    static ActionTimeline* create();

    ActionTimeline();
    virtual ~ActionTimeline();

    /**
    * @~english Play specified animation.
    * @~chinese 播放指定的动画。
    * @param animationName @~english Name of specified animation.
    * @~chinese 指定动画的名称。
    * @param loop @~english Is play loop.
    * @~chinese 是否循环播放。
    */
    virtual void play(std::string animationName, bool loop);

    virtual bool init();

    /** @~english Goto the specified frame index, and start playing from this index.
    * @~chinese 跳转到指定帧并从该帧开始播放动画。
     * @param startIndex @~english The animation will play from this index.
     * @~chinese 动画将从此帧开始播放。
     */
    virtual void gotoFrameAndPlay(int startIndex);

    /** @~english Goto the specified frame index, and start playing from this index.
    * @~chinese 跳转至指定帧索引，并从该索引开始播放动画。
     * @param startIndex @~english The animation will play from this index.
     * @~chinese 动画将从该索引位置开始播放。
     * @param loop @~english Whether or not the animation need loop. 
     * @~chinese 动画是否循环播放。
     */
    virtual void gotoFrameAndPlay(int startIndex, bool loop);

    /** @~english Goto the specified frame index, and start playing from start index, end at end index.
    * @~chinese 跳转到指定帧并从该帧开始播放动画，播放到指定的结束帧位置停止。
     * @param startIndex @~english The animation will play from this index.
     * @~chinese 动画将从此帧开始播放。
     * @param endIndex @~english The animation will end at this index.
     * @~chinese 动画播放到此帧结束。
     * @param loop @~english Whether or not the animation need loop. 
     * @~chinese 动画是否循环播放。
     */
    virtual void gotoFrameAndPlay(int startIndex, int endIndex, bool loop);

    /** @~english Goto the specified frame index, and start playing from start index, end at end index.
    * @~chinese跳转到指定帧，并且从起始帧开始播放，到结束帧停止。
     * @param startIndex @~english The animation will play from this index.
     * @~chinese 动画将从此帧开始播放。
     * @param endIndex @~english The animation will end at this index.
     * @~chinese 动画播放到此帧结束。
     * @param currentFrameIndex @~english set current frame index. 
     * @~chinese 设置当前帧索引。
     * @param loop @~english Whether or not the animation need loop. 
     * @~chinese 动画是否循环播放。
     */
    virtual void gotoFrameAndPlay(int startIndex, int endIndex, int currentFrameIndex, bool loop);

    /** @~english Goto the specified frame index, and pause at this index.
    * @~chinese 跳转到指定帧并且暂停在该帧。
     * @param startIndex @~english The animation will pause at this index.
     * @~chinese 动画将暂停在该帧。
     */
    virtual void gotoFrameAndPause(int startIndex);

    /** @~english Pause the animation. 
     * @~chinese 暂停动画。
    */
    virtual void pause();
    /** @~english Resume the animation. 
    * @~chinese 继续动画。
    */
    virtual void resume();

    /** @~english Whether or not Action is playing.
    * @~chinese 是否在播放。
    */
    virtual bool isPlaying() const;

    /** @~english Set the animation speed, this will speed up or slow down the speed. 
    * @~chinese 设置动画速度，使动画加速或减速。
    * @param speed @~english Animation speed.
    * @~chinese 动画播放速度。
    */
    virtual void  setTimeSpeed(float speed) { _timeSpeed = speed; }

    /** @~english Get current animation speed.
     *   @~chinese 获取当前动画速度。
     * @return @~english Animation speed.
     * @~chinese 动画播放速度。
     */
    virtual float getTimeSpeed() const { return _timeSpeed; }

    /** @~english Set duration of the whole action.
    *   @~chinese 设置整体动画时长。
    * @param duration @~english Animation duration.
    * @~chinese 动画时长。
    */
    virtual void setDuration(int duration) { _duration = duration; }
    /** @~english Get duration of the whole action.
    *   @~chinese 获取动画时长。
    * @return @~english Animation duration.
    * @~chinese 动画时长。
    */
    virtual int  getDuration() const { return _duration; }

    /** @~english Get start frame index of this action.
    *   @~chinese 动画的起始帧索引。
    * @return @~english Start frame index.
    * @~chinese 起始帧索引。
    */
    virtual int getStartFrame() const { return _startFrame; }

    /** @~english End frame of this action.
    *   When action play to this frame, if action is not loop, then it will stop,  or it will play from start frame again. 
    *   @~chinese 动画的结束帧索引。
    *   当动画播放到该帧时，如果非循环播放，则动画停止。否则会从起始帧从头播放。
    * @return @~english End frame.
    * @~chinese 结束帧索引。
    */
    virtual int  getEndFrame() const { return _endFrame; }

    /** @~english Set current frame index, this will cause action plays to this frame. 
    *   @~chinese 设置当前帧索引，将会使动画播放至该帧。
    * @param frameIndex @~english Current frame index.
    * @~chinese 当前帧索引。
    */
    virtual void setCurrentFrame(int frameIndex);
    /** @~english Get current frame. 
    *   @~chinese 获取当前帧索引。
    * @return @~english Current frame index.
    * @~chinese 当前帧索引。
    */
    virtual int  getCurrentFrame() const { return _currentFrame; }

    /** @~english Add Timeline to ActionTimeline.
    *   @~chinese 将时间轴加入动画时间轴。
    * @param timeline @~english Timeline.
    * @~chinese 时间轴。
    */
    virtual void addTimeline(Timeline* timeline);
    /** @~english Remove Timeline to ActionTimeline.
    *   @~chinese 将时间轴从动画时间轴中移除。
    * @param timeline @~english Timeline.
    * @~chinese 时间轴。
    */
    virtual void removeTimeline(Timeline* timeline);

    /** @~english Get timelines.
    *   @~chinese 获取时间轴列表。
    * @return @~english Timelines.
    * @~chinese 时间轴列表。
    */
    virtual const cocos2d::Vector<Timeline*>& getTimelines() const { return _timelineList; }
    
    /** AnimationInfo*/
    /** @~english Add animationInfo.
    *   @~chinese 增加动画信息。
    * @param animationInfo @~english Animation info.
    * @~chinese 动画信息。
    */
    virtual void addAnimationInfo(const AnimationInfo& animationInfo);
    /** @~english Remove animationInfo.
    *   @~chinese 移除动画信息。
    * @param animationName @~english Name of animation info.
    * @~chinese 动画信息的名称。
    */
    virtual void removeAnimationInfo(std::string animationName);
    /** @~english Is animationInfo exists.
    *   @~chinese 是否动画信息存在。
    * @param animationName @~english Name of animation info.
    * @~chinese 动画信息的名称。
    * @return @~english Is exists.
    * @~chinese 是否存在。
    */
    virtual bool IsAnimationInfoExists(const std::string& animationName);
    /** @~english Get animationInfo.
    *   @~chinese 获取动画信息。
    * @param animationInfo @~english Animation info name.
    * @~chinese 动画信息的名称。
    */
    virtual AnimationInfo getAnimationInfo(const std::string& animationName);

    /** @~english Set ActionTimeline's frame event callback function.
    *   @~chinese 设置动画时间轴的帧事件回调函数。
    * @param listener @~english Callback function .
    * @~chinese 回调函数。
    */
    void setFrameEventCallFunc(std::function<void(Frame *)> listener);
    /** @~english Clear ActionTimeline's frame event callback function.
    *   @~chinese 清除动画时间轴的帧事件回调函数。
    */
    void clearFrameEventCallFunc();

    /** @~english Last frame callback will call when arriving last frame.
    *   @~chinese 动画播放至最后一帧时，将会调用最后一帧的回调。
    * @param listener @~english Callback function .
    * @~chinese 回调函数。
    */
    void setLastFrameCallFunc(std::function<void()> listener);
    /** @~english Clear last frame callback.
    *   @~chinese 清除动画播放至最后一帧时调用最后一帧的回调。
    */
    void clearLastFrameCallFunc();

    /** Inherit from Action. */

    /** Returns a clone of ActionTimeline */
    virtual ActionTimeline* clone() const override; 

    /** Returns a reverse of ActionTimeline. 
     *  Not implement yet.
     */
    virtual ActionTimeline* reverse() const override { return nullptr; }

    virtual void step(float delta) override; 
    virtual void startWithTarget(cocos2d::Node *target) override;  
    virtual bool isDone() const override { return false; }
protected:
    virtual void gotoFrame(int frameIndex);
    virtual void stepToFrame(int frameIndex);

    /** emit frame event, call it when enter a frame*/
    virtual void emitFrameEvent(Frame* frame);

    std::map<int, cocos2d::Vector<Timeline*>> _timelineMap;
    cocos2d::Vector<Timeline*> _timelineList;

    int     _duration;
    double  _time;
    float   _timeSpeed;
    float   _frameInternal;
    bool    _playing;
    int     _currentFrame;
    int     _startFrame;
    int     _endFrame;
    bool    _loop;

    std::function<void(Frame*)> _frameEventListener;
    std::function<void()> _lastFrameListener;
    std::map<std::string, AnimationInfo> _animationInfos;
};

NS_TIMELINE_END


#endif /*__CCTIMELINE_ACTION_H__*/
