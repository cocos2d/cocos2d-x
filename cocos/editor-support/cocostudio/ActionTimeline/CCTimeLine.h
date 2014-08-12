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
#include "CCTimelineMacro.h"
#include "cocostudio/CocosStudioExport.h"

NS_TIMELINE_BEGIN

class ActionTimeline;

class CC_STUDIO_DLL Timeline : public cocos2d::Ref
{
public:
    static Timeline* create();

    Timeline();
    virtual ~Timeline();

    virtual void gotoFrame(int frameIndex);
    virtual void stepToFrame(int frameIndex);

    virtual const cocos2d::Vector<Frame*>& getFrames() const { return _frames; }

    virtual void addFrame(Frame* frame);
    virtual void insertFrame(Frame* frame, int index);
    virtual void removeFrame(Frame* frame);

    virtual void setActionTag(int tag) { _actionTag = tag; }
    virtual int  getActionTag() const { return _actionTag; }

    virtual void setNode(cocos2d::Node* node);
    virtual cocos2d::Node* getNode() const;

    virtual void setActionTimeline(ActionTimeline* action) { _ActionTimeline = action; }
    virtual ActionTimeline* getActionTimeline() const { return _ActionTimeline; }

    virtual Timeline* clone();

protected:
    virtual void apply(int frameIndex);

    virtual void binarySearchKeyFrame (int frameIndex);
    virtual void updateCurrentKeyFrame(int frameIndex);

    cocos2d::Vector<Frame*> _frames;
    Frame* _currentKeyFrame;
    int _currentKeyFrameIndex;

    int _fromIndex;
    int _toIndex;
    int _betweenDuration;
    int _actionTag;

    ActionTimeline*  _ActionTimeline;
    cocos2d::Node* _node;
};

NS_TIMELINE_END


#endif /*__CCTIMELINE_H__*/
