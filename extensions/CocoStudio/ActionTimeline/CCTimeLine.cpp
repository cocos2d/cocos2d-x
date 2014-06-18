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

#include "CCTimeLine.h"
#include "CCActionTimeline.h"
#include "CCFrame.h"

using namespace cocos2d;

NS_TIMELINE_BEGIN

Timeline* Timeline::create()
{
    Timeline* object = new Timeline();
    if (object && object->init())
    {
        object->autorelease();
        return object;
    }
    CC_SAFE_DELETE(object);
    return NULL;
}

Timeline::Timeline()
    : _frames(NULL)
    , _currentKeyFrame(NULL)
    , _currentKeyFrameIndex(0)
    , _fromIndex(0)
    , _toIndex(0)
    , _betweenDuration(0)
    , _actionTag(0)
    , _timelineAction(NULL)
    , _node(NULL)
{
}

Timeline::~Timeline()
{
    CC_SAFE_DELETE(_frames);
}

bool Timeline::init()
{
    _frames = new cocos2d::CCArray();
    return _frames->init();
}

void Timeline::gotoFrame(int frameIndex)
{
    if(_frames->count() == 0)
        return;

    binarySearchKeyFrame(frameIndex);
    apply(frameIndex);
}

void Timeline::stepToFrame(int frameIndex)
{
    if(_frames->count() == 0)
        return;

    updateCurrentKeyFrame(frameIndex);
    apply(frameIndex);
}

Timeline* Timeline::clone()
{
    Timeline* timeline = Timeline::create();
    timeline->_actionTag = _actionTag;

    CCObject* object = NULL;
    CCARRAY_FOREACH(_frames, object)
    {
        Frame* frame = static_cast<Frame*>(object);
        Frame* newFrame = frame->clone();
        timeline->addFrame(newFrame);
    }

    return timeline;
}

void Timeline::addFrame(Frame* frame)
{
    _frames->addObject(frame);
    frame->setTimeline(this);
}

void Timeline::insertFrame(Frame* frame, int index)
{
    _frames->insertObject(frame, index);
    frame->setTimeline(this);
}

void Timeline::removeFrame(Frame* frame)
{
    _frames->removeObject(frame);
    frame->setTimeline(NULL);
}

void Timeline::setNode(cocos2d::CCNode* node)
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(_frames, object)
    {
        Frame* frame = static_cast<Frame*>(object);
        frame->setNode(node);
    }
}

cocos2d::CCNode* Timeline::getNode() const 
{
    return _node;
}

void Timeline::apply(int frameIndex)
{
    if (_currentKeyFrame)
    {
        float currentPercent = _betweenDuration == 0 ? 0 : (frameIndex - _currentKeyFrameIndex) / (float)_betweenDuration;
        _currentKeyFrame->apply(currentPercent);
    }
}

void Timeline::binarySearchKeyFrame(int frameIndex)
{
    Frame *from = NULL;
    Frame *to   = NULL;

    long length = _frames->count();
    Frame **frames = (Frame **)_frames->data->arr;

    bool needEnterFrame = false;

    do 
    {
        if (frameIndex < frames[0]->getFrameIndex())
        {
            if(_currentKeyFrameIndex >= frames[0]->getFrameIndex())
                needEnterFrame = true;

            from = to = frames[0];
            _currentKeyFrameIndex = 0;
            _betweenDuration = frames[0]->getFrameIndex();
            break;
        }
        else if(frameIndex >= frames[length - 1]->getFrameIndex())
        {
            from = to = frames[length - 1]; 
            _currentKeyFrameIndex = frames[length - 1]->getFrameIndex();
            _betweenDuration = 0;
            break;
        }

        int target = -1;
        int low=0,high=length-1,mid;
        while(low<=high){ 
            mid=(low+high)/2;
            if(frameIndex >= frames[mid]->getFrameIndex() && frameIndex < frames[mid+1]->getFrameIndex()) 
            {
                target = mid;
                break;
            }
            if(frames[mid]->getFrameIndex()>frameIndex)
                high=mid-1; 
            else
                low=mid+1;
        }

        from = frames[target];
        to   = frames[target+1];

        if(target == 0 && _currentKeyFrameIndex<from->getFrameIndex())
            needEnterFrame = true;

        _currentKeyFrameIndex = from->getFrameIndex();
        _betweenDuration = to->getFrameIndex() - from->getFrameIndex();
    } while (0);

    if(needEnterFrame || _currentKeyFrame != from)
    {
        _currentKeyFrame = from;
        _currentKeyFrame->onEnter(to);
    }
}

void Timeline::updateCurrentKeyFrame(int frameIndex)
{
    //! If play to current frame's front or back, then find current frame again
    if (frameIndex < _currentKeyFrameIndex || frameIndex >= _currentKeyFrameIndex + _betweenDuration)
    {
        Frame *from = NULL;
        Frame *to   = NULL;

        do 
        {
            Frame **frames = (Frame **)_frames->data->arr;

            long length = _frames->count();

            if (frameIndex < frames[0]->getFrameIndex())
            {
                from = to = frames[0];
                _currentKeyFrameIndex = 0;
                _betweenDuration = frames[0]->getFrameIndex();
                break;
            }
            else if(frameIndex >= frames[length - 1]->getFrameIndex())
            {
                from = to = frames[length - 1];
                _currentKeyFrameIndex = frames[length - 1]->getFrameIndex();
                _betweenDuration = 0;
                break;
            }

            do
            {
                _fromIndex = _toIndex;
                from = frames[_fromIndex];
                _currentKeyFrameIndex  = from->getFrameIndex();

                _toIndex = _fromIndex + 1;
                if (_toIndex >= length)
                {
                    _toIndex = 0;
                }

                to = frames[_toIndex];

                if (frameIndex == from->getFrameIndex())
                {
                    break;
                }
            }
            while (frameIndex < from->getFrameIndex() || frameIndex >= to->getFrameIndex());

            _betweenDuration = to->getFrameIndex() - from->getFrameIndex();

        } while (0);

        _currentKeyFrame = from;
        _currentKeyFrame->onEnter(to);
    }
}

NS_TIMELINE_END
