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

#include "cocos2d.h"
#include "CCTimeLine.h"

NS_TIMELINE_BEGIN

typedef void (cocos2d::CCObject::*SEL_TimelineFrameEventCallFunc)(Frame *);

#define timelineFrameEvent_selector(_SELECTOR) (SEL_TimelineFrameEventCallFunc)(&_SELECTOR)

class CC_EX_DLL ActionTimeline : public cocos2d::CCAction
{
public:

    static ActionTimeline* create();

    ActionTimeline();
    virtual ~ActionTimeline();

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

    /**
     * Set action's frame event callback function
     */
    void setFrameEventCallFunc  (CCObject *target, SEL_TimelineFrameEventCallFunc callFunc);
    void clearFrameEventCallFunc();

    /** Inherit from cocos2d::Action. */

    /** Returns a clone of ActionTimeline */
    virtual ActionTimeline* clone() const; 

    /** Returns a reverse of ActionTimeline. 
     *  Not implement yet.
     */
    virtual ActionTimeline* reverse() const { return NULL; }

    virtual void step(float delta); 
    virtual void startWithTarget(cocos2d::CCNode *target);  
    virtual bool isDone() { return false; }
    
    /**
     * Returns a user assigned CCDictionary
     *
     * @return A user assigned CCDictionary
     */
    virtual cocos2d::CCDictionary* getScriptObjectDict() const;
    /**
     * Returns a user assigned CCDictionary
     *
     * The scriptObjectDict will be retained once in this method,
     * and the previous scriptObjectDict (if existed) will be relese.
     * The scriptObjectDict will be released in destructure.
     *
     * @param A user assigned CCObject
     */
    virtual void setScriptObjectDict(cocos2d::CCDictionary* scriptObjectDict);
protected:
    friend class Frame;

    void foreachNodeDescendant(cocos2d::CCNode* parent);

    virtual void gotoFrame  (int frameIndex);
    virtual void stepToFrame(int frameIndex);

    /** emit frame event, call it when enter a frame*/
    void emitFrameEvent(Frame* frame);

    std::map<int, cocos2d::CCArray*> _timelineMap; // <int, cocos2d::Vector<Timeline*>>
    cocos2d::CCArray* _timelineList;      // cocos2d::Vector<Timeline*>

    int     _duration;
    double  _time;
    float   _timeSpeed;
    float   _frameInternal;
    bool    _playing;
    int     _currentFrame;
    int     _startFrame;
    int     _endFrame;
    bool    _loop;


    SEL_TimelineFrameEventCallFunc _frameEventCallFunc;
    cocos2d::CCObject*     _frameEventTarget;
    
    cocos2d::CCDictionary* _scriptObjectDict;
};

NS_TIMELINE_END


#endif /*__CCTIMELINE_ACTION_H__*/
