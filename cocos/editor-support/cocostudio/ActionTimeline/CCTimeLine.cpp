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

USING_NS_CC;

NS_TIMELINE_BEGIN

Timeline* Timeline::create()
{
    Timeline* object = new (std::nothrow) Timeline();
    if (object)
    {
        object->autorelease();
        return object;
    }
    CC_SAFE_DELETE(object);
    return nullptr;
}

Timeline::Timeline()
    : _currentKeyFrame(nullptr)
    , _currentKeyFrameIndex(0)
    , _fromIndex(0)
    , _toIndex(0)
    , _betweenDuration(0)
    , _actionTag(0)
    , _actionTimeline(nullptr)
    , _node(nullptr)
{
}

Timeline::~Timeline()
{
}

void Timeline::gotoFrame(int frameIndex)
{
    if(_frames.size() == 0)
        return;

    binarySearchKeyFrame(frameIndex);
    apply(frameIndex);
}

void Timeline::stepToFrame(int frameIndex)
{
    if(_frames.size() == 0)
        return;

    updateCurrentKeyFrame(frameIndex);
    apply(frameIndex);
}

Timeline* Timeline::clone()
{
    Timeline* timeline = Timeline::create();
    timeline->_actionTag = _actionTag;

    for (auto frame : _frames)
    {
        Frame* newFrame = frame->clone();
        timeline->addFrame(newFrame);
    }

    return timeline;
}

Timeline* Timeline::reverse(const int& duration) const
{
	Timeline* rvsTimeline = Timeline::create();
	rvsTimeline->_actionTag = _actionTag;
	if (_frames.empty())
		return rvsTimeline;

	auto frameNumI = _frames.size() - 1;
    auto rvframe = _frames.at(frameNumI)->clone();
    do
    {
		rvframe->setFrameIndex(duration - rvframe->getFrameIndex());
		rvsTimeline->addFrame(rvframe);
        if(frameNumI == 0)
            break;
        auto preF = _frames.at(frameNumI -1)->clone();
        rvframe->setTween(preF->isTween());
        auto tweenT = preF->getTweenType();
        auto tweenV = preF->getEasingParams();
        if(tweenT == cocos2d::tweenfunc::TweenType::CUSTOM_EASING
           && tweenV.size() >= 8)
        {
            auto tmp  = tweenV[2];
            tweenV[2] = tweenV[5];
            tweenV[5] = tmp;
            tmp = tweenV[4];
            tweenV[4] = tweenV[3];
            tweenV[3] = tmp;
        }
        rvframe->setEasingParams(tweenV);
        rvframe->setTweenType(tweenT);
        rvframe = preF;
        frameNumI--;
    }while(frameNumI >= 0);
	return rvsTimeline;
}

void Timeline::addFrame(Frame* frame)
{
    _frames.pushBack(frame);
    frame->setTimeline(this);
}

void Timeline::insertFrame(Frame* frame, int index)
{
    _frames.insert(index, frame);
    frame->setTimeline(this);
}

void Timeline::removeFrame(Frame* frame)
{
    _frames.eraseObject(frame);
    frame->setTimeline(nullptr);
}

void Timeline::setNode(Node* node)
{
    for (auto frame : _frames)
    {
        frame->setNode(node);
    }
}

Node* Timeline::getNode() const
{
    return _node;
}

void Timeline::apply(unsigned int frameIndex)
{
    if (_currentKeyFrame)
    {
        float currentPercent = _betweenDuration == 0 ? 0 : (frameIndex - _currentKeyFrameIndex) / (float)_betweenDuration;
        _currentKeyFrame->apply(currentPercent);
    }
}

void Timeline::binarySearchKeyFrame(unsigned int frameIndex)
{
    Frame *from = nullptr;
    Frame *to   = nullptr;

    long length = _frames.size();
    bool needEnterFrame = false;

    do 
    {
        if (frameIndex < _frames.at(0)->getFrameIndex())
        {
            if(_currentKeyFrameIndex >= _frames.at(0)->getFrameIndex())
                needEnterFrame = true;

            _fromIndex = 0;
            _toIndex = 0;
            
            from = to = _frames.at(0);
            _currentKeyFrameIndex = 0;
            _betweenDuration = _frames.at(0)->getFrameIndex();
            break;
        }
        else if(frameIndex >= _frames.at(length - 1)->getFrameIndex())
        {
            _fromIndex = (int)(length - 1);
            _toIndex = 0;
            
            from = to = _frames.at(length - 1); 
            _currentKeyFrameIndex = _frames.at(length - 1)->getFrameIndex();
            _betweenDuration = 0;
            break;
        }

        long target = -1;
        long low=0,high=length-1,mid=0;
        while(low<=high){ 
            mid=(low+high)/2;
            if(frameIndex >= _frames.at(mid)->getFrameIndex() && frameIndex < _frames.at(mid+1)->getFrameIndex()) 
            {
                target = mid;
                break;
            }
            if(_frames.at(mid)->getFrameIndex()>frameIndex)
                high=mid-1; 
            else
                low=mid+1;
        }
        
        _fromIndex = (int)target;

        if(length > 1)
            _toIndex = (int)(target + 1);
        else
            _toIndex = (int)target;

        from = _frames.at(_fromIndex);
        to   = _frames.at(_toIndex);

        if(target == 0 && _currentKeyFrameIndex<from->getFrameIndex())
            needEnterFrame = true;

        _currentKeyFrameIndex = from->getFrameIndex();
        _betweenDuration = to->getFrameIndex() - from->getFrameIndex();
    } while (0);

    if(needEnterFrame || _currentKeyFrame != from)
    {
        _currentKeyFrame = from;
        _currentKeyFrame->onEnter(to, frameIndex);
    }
}

void Timeline::updateCurrentKeyFrame(unsigned int frameIndex)
{
    //! If play to current frame's front or back, then find current frame again
    if (frameIndex < _currentKeyFrameIndex || frameIndex >= _currentKeyFrameIndex + _betweenDuration)
    {
        Frame *from = nullptr;
        Frame *to = nullptr;

        do 
        {
            long length = _frames.size();

            if (frameIndex < _frames.at(0)->getFrameIndex())
            {
                from = to = _frames.at(0);
                _currentKeyFrameIndex = 0;
                _betweenDuration = _frames.at(0)->getFrameIndex();
                break;
            }
            else if(frameIndex >= _frames.at(length - 1)->getFrameIndex())
            {
				unsigned int lastFrameIndex = _frames.at(length - 1)->getFrameIndex();
                if(_currentKeyFrameIndex >= lastFrameIndex)
                    return;
                frameIndex = lastFrameIndex;
            }

            do
            {
                _fromIndex = _toIndex;
                from = _frames.at(_fromIndex);
                _currentKeyFrameIndex  = from->getFrameIndex();

                _toIndex = _fromIndex + 1;
                if ((ssize_t)_toIndex >= length)
                {
                    _toIndex = 0;
                }

                to = _frames.at(_toIndex);

                if(frameIndex == from->getFrameIndex())
                    break;
                if(frameIndex > from->getFrameIndex() && frameIndex < to->getFrameIndex())
                    break;
                if(from->isEnterWhenPassed())
                    from->onEnter(to, from->getFrameIndex());
            }
            while (true);

            if(_fromIndex == length-1)
                to = from;
            
            _betweenDuration = to->getFrameIndex() - from->getFrameIndex();
            
        } while (0);

        _currentKeyFrame = from;
        _currentKeyFrame->onEnter(to, frameIndex);
        
    }
}

NS_TIMELINE_END
