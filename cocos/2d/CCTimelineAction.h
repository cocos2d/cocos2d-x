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

#include "2d/CCNode.h"
#include "2d/CCAction.h"
#include "2d/CCTimeLine.h"
#include "base/CCRef.h"
#include "renderer/CCRenderer.h"

NS_CC_BEGIN

typedef void (Ref::*SEL_FrameEventCallFunc)(Frame *);
#define frameEvent_selector(_SELECTOR) (SEL_FrameEventCallFunc)(&_SELECTOR)

class CC_DLL TimelineActionData : public Ref
{
public:
    static TimelineActionData* create(int actionTag);

    virtual void setActionTag(int actionTag) { _actionTag = actionTag; }
    virtual int getActionTag() { return _actionTag; }
protected:
    TimelineActionData();
    virtual bool init(int actionTag);

    int _actionTag;
};


class CC_DLL TimelineAction : public Action
{
public:
    static TimelineAction* create();

    TimelineAction();
    virtual ~TimelineAction();

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

    /** Goto the specified frame index, and pause at this index.
     * @param startIndex The animation will pause at this index.
     */
    virtual void gotoFrameAndPause(int startIndex);

    /** Pause the animation. */
    virtual void pause();
    /** Resume the animation. */
    virtual void resume();

    /** Whether or not Action is playing. */
    virtual bool isPlaying();

    /** Set the animation speed, this will speed up or slow down the speed. */
    virtual void  setTimeSpeed(float speed);
    /** Get current animation speed. */
    virtual float getTimeSpeed();

    /** duration of the whole action*/
    virtual void setDuration(int duration) { _duration = duration; }
    virtual int  getDuration() { return _duration; }

    /** End frame of this action.
      * When action play to this frame, if action is not loop, then it will stop, 
      * or it will play from start frame again. */
    virtual void setEndFrame(int endFrame) { _endFrame = endFrame; }
    virtual int  getEndFrame() { return _endFrame; }

    /** Get current frame. */
    virtual int  getCurrentFrame() { return _currentFrame; }

    /** add Timeline to TimelineAction */
    virtual void addTimeline(Timeline* timeline);
    virtual void removeTimeline(Timeline* timeline);

    /** Set TimelineAction's frame event callback function */
    void setFrameEventCallFunc(std::function<void(Frame *)> listener);
    void clearFrameEventCallFunc();

    /** emit frame event, call it when enter a frame*/
    void emitFrameEvent(Frame* frame);

    /** Inherit from Action. */

    /** Returns a clone of TimelineAction */
    virtual TimelineAction* clone() const override; 

    /** Returns a reverse of TimelineAction. 
     *  Not implement yet.
     */
    virtual TimelineAction* reverse() const override { return nullptr; }

    virtual void step(float delta) override; 
    virtual void startWithTarget(Node *target) override;  
    virtual bool isDone() const override { return false; }
protected:
    virtual void gotoFrame(int frameIndex);
    virtual void stepToFrame(int frameIndex);

    std::map<int, Vector<Timeline*>> _timelineMap;
    Vector<Timeline*> _timelineList;

    int     _duration;
    double  _time;
    float   _timeSpeed;
    float   _frameInternal;
    bool    _playing;
    int     _currentFrame;
    int     _endFrame;
    bool    _loop;

    std::function<void(Frame*)> _frameEventListener;
};

NS_CC_END


#endif /*__CCTIMELINE_ACTION_H__*/
