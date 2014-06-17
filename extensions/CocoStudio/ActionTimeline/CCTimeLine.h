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

#ifndef __CCTIMELINE_H__
#define __CCTIMELINE_H__

#include "CCFrame.h"
#include "ExtensionExport.h"

NS_TIMELINE_BEGIN

class ActionTimeline;

class CC_EX_DLL Timeline : public cocos2d::CCObject
{
public:
    static Timeline* create();

    Timeline();
    virtual ~Timeline();

    virtual bool init();

    virtual void gotoFrame  (int frameIndex);
    virtual void stepToFrame(int frameIndex);

    virtual const cocos2d::CCArray* getFrames() { return _frames; }
    virtual void addFrame(Frame* frame);
    virtual void insertFrame(Frame* frame, int index);
    virtual void removeFrame(Frame* frame);

    virtual void setActionTag(int tag) { _actionTag = tag; }
    virtual int  getActionTag() const { return _actionTag; }

    virtual void setNode(cocos2d::CCNode* node);
    virtual cocos2d::CCNode* getNode() const;

    virtual void setActionTimeline(ActionTimeline* action) { _timelineAction = action; }
    virtual ActionTimeline* getActionTimeline() const { return _timelineAction; }

    virtual Timeline* clone();

protected:
    virtual void apply(int frameIndex);

    virtual void binarySearchKeyFrame (int frameIndex);
    virtual void updateCurrentKeyFrame(int frameIndex);

    cocos2d::CCArray* _frames; // <Frame*>
    Frame* _currentKeyFrame;
    int _currentKeyFrameIndex;

    int _fromIndex;
    int _toIndex;
    int _betweenDuration;
    int _actionTag;

    ActionTimeline*  _timelineAction;
    cocos2d::CCNode* _node;
};

NS_TIMELINE_END


#endif /*__CCTIMELINE_H__*/
