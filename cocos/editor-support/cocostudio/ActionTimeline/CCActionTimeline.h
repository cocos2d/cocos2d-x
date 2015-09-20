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

typedef struct AnimationInfo
{
    AnimationInfo()
        :startIndex(0)
        ,endIndex(0)
    {
    }

    AnimationInfo(const std::string& otherName, int otherStartIndex, int otherEndIndex)
    :name(otherName)
    ,startIndex(otherStartIndex)
    ,endIndex(otherEndIndex)
    {
    }

    std::string name;
    int startIndex;
    int endIndex;

    //need set call back before clip added to ActionTimeline
    // or see @ActionTimeline::setAnimationEndCallBack
    std::function<void()> clipEndCallBack;
} AnimationClip;

class CC_STUDIO_DLL ActionTimelineData : public cocos2d::Ref
{
public:
    static ActionTimelineData* create(int actionTag);

    virtual void setActionTag(int actionTag) { _actionTag = actionTag; }
    virtual int getActionTag() const { return _actionTag; }
CC_CONSTRUCTOR_ACCESS:
    ActionTimelineData();
    virtual bool init(int actionTag);
protected:
    int _actionTag;
};


class CC_STUDIO_DLL ActionTimeline : public cocos2d::Action
{
public:
    friend class Frame;

    static ActionTimeline* create();

    ActionTimeline();
    virtual ~ActionTimeline();

    virtual void play(std::string animationName, bool loop);

    virtual bool init();

    /** Goto the specified frame index, and start playing from this index.
     * @param startIndex The animation will play from this index.
     */
    virtual void gotoFrameAndPlay(int startIndex);

    /** Goto the specified frame index, and start playing from this index.
     * @param startIndex The animation will play from this index.
     * @param loop Whether or not the animation need loop. 
     */
    virtual void gotoFrameAndPlay(int startIndex, bool loop);

    /** Goto the specified frame index, and start playing from start index, end at end index.
     * @param startIndex The animation will play from this index.
     * @param endIndex The animation will end at this index.
     * @param loop Whether or not the animation need loop. 
     */
    virtual void gotoFrameAndPlay(int startIndex, int endIndex, bool loop);

    /** Goto the specified frame index, and start playing from start index, end at end index.
     * @param startIndex The animation will play from this index.
     * @param endIndex The animation will end at this index.
     * @param currentFrameIndex set current frame index. 
     * @param loop Whether or not the animation need loop. 
     */
    virtual void gotoFrameAndPlay(int startIndex, int endIndex, int currentFrameIndex, bool loop);

    /** Goto the specified frame index, and pause at this index.
     * @param startIndex The animation will pause at this index.
     */
    virtual void gotoFrameAndPause(int startIndex);

    /** Pause the animation. */
    virtual void pause();
    /** Resume the animation. */
    virtual void resume();

    /** Whether or not Action is playing. */
    virtual bool isPlaying() const;

    /** Set the animation speed, this will speed up or slow down the speed. */
    virtual void  setTimeSpeed(float speed) { _timeSpeed = speed; }
    /** Get current animation speed. */
    virtual float getTimeSpeed() const { return _timeSpeed; }

    /** duration of the whole action*/
    virtual void setDuration(int duration) { _duration = duration; }
    virtual int  getDuration() const { return _duration; }

    /** Start frame index of this action*/
    virtual int getStartFrame() const { return _startFrame; }

    /** End frame of this action.
      * When action play to this frame, if action is not loop, then it will stop, 
      * or it will play from start frame again. */
    virtual int  getEndFrame() const { return _endFrame; }

    /** Set current frame index, this will cause action plays to this frame. */
    virtual void setCurrentFrame(int frameIndex);
    /** Get current frame. */
    virtual int  getCurrentFrame() const { return _currentFrame; }

    /** add Timeline to ActionTimeline */
    virtual void addTimeline(Timeline* timeline);
    virtual void removeTimeline(Timeline* timeline);

    virtual const cocos2d::Vector<Timeline*>& getTimelines() const { return _timelineList; }
    
    /** AnimationInfo*/
    virtual void addAnimationInfo(const AnimationInfo& animationInfo);
    virtual void removeAnimationInfo(std::string animationName);
    virtual bool IsAnimationInfoExists(const std::string& animationName);
    virtual const AnimationInfo& getAnimationInfo(const std::string& animationName);
    /**add a frame end call back to animation's end frame
     * @param animationName  @addFrameEndCallFunc, make the animationName as funcKey
     * @param func the callback function
     */
    virtual void setAnimationEndCallFunc(const std::string animationName, std::function<void()> func);

    /** Set ActionTimeline's frame event callback function */
    void setFrameEventCallFunc(std::function<void(Frame *)> listener);
    void clearFrameEventCallFunc();

    /** Last frame callback will call when arriving last frame */
    void setLastFrameCallFunc(std::function<void()> listener);
    void clearLastFrameCallFunc();

    /** add a callback function after played frameIndex
     * @param frameIndex the frame index call back after
     * @param funcKey for identity the callback function
     * @param func the callback function
     */
    virtual void addFrameEndCallFunc(int frameIndex, const std::string& funcKey, std::function<void()> func);
    // remove callback function after frameIndex which identified with funcKey
    virtual void removeFrameEndCallFunc(int frameIndex, const std::string& funcKey);
    // clear callback functions after frameIndex
    virtual void removeFrameEndCallFuncs(int frameIndex);
    // clear all the callback functions after frameIndexs in this actiontimeline
    virtual void clearFrameEndCallFuncs();

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

    // emit call back after frameIndex played
    virtual void emitFrameEndCallFuncs(int frameIndex);

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
    std::map<int, std::map<std::string, std::function<void()> > > _frameEndCallFuncs;
    std::map<std::string, AnimationInfo> _animationInfos;
};

NS_TIMELINE_END


#endif /*__CCTIMELINE_ACTION_H__*/
