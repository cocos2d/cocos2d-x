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

#include "CCActionTimeline.h"

#include "cocostudio/CCObjectExtensionData.h"

USING_NS_CC;

NS_TIMELINE_BEGIN

// ActionTimelineData
ActionTimelineData* ActionTimelineData::create(int actionTag)
{
    ActionTimelineData * ret = new (std::nothrow) ActionTimelineData();
    if (ret && ret->init(actionTag))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

ActionTimelineData::ActionTimelineData()
    : _actionTag(0)
{
}

bool ActionTimelineData::init(int actionTag)
{
    _actionTag = actionTag;
    return true;
}


// ActionTimeline
ActionTimeline* ActionTimeline::create()
{
    ActionTimeline* object = new (std::nothrow) ActionTimeline();
    if (object && object->init())
    {
        object->autorelease();
        return object;
    }
    CC_SAFE_DELETE(object);
    return nullptr;
}

ActionTimeline::ActionTimeline()
    : _duration(0)
    , _time(0)
    , _timeSpeed(1)
    , _frameInternal(1/60.0f)
    , _playing(false)
    , _currentFrame(0)
    , _startFrame(0)
    , _endFrame(0)
    , _frameEventListener(nullptr)
    , _lastFrameListener(nullptr)
{
}

ActionTimeline::~ActionTimeline()
{
}

bool ActionTimeline::init()
{
    return true;
}

void ActionTimeline::play(std::string name, bool loop)
{
    if (_animationInfos.find(name) == _animationInfos.end())
    {
        CCLOG("Can't find animation info for %s", name.c_str());
        return;
    }

    AnimationInfo& index = _animationInfos[name];
    gotoFrameAndPlay(index.startIndex, index.endIndex, loop);
}

void ActionTimeline::gotoFrameAndPlay(int startIndex)
{
    gotoFrameAndPlay(startIndex, true);
}

void ActionTimeline::gotoFrameAndPlay(int startIndex, bool loop)
{
    gotoFrameAndPlay(startIndex, _duration, loop);
}

void ActionTimeline::gotoFrameAndPlay(int startIndex, int endIndex, bool loop)
{
    gotoFrameAndPlay(startIndex, endIndex, startIndex, loop);
}

void ActionTimeline::gotoFrameAndPlay(int startIndex, int endIndex, int currentFrameIndex, bool loop)
{
    _startFrame = startIndex;
    _endFrame = endIndex;
    _currentFrame = currentFrameIndex;
    _loop = loop;
    _time = _currentFrame*_frameInternal;

    resume();
    gotoFrame(_currentFrame);
}

void ActionTimeline::gotoFrameAndPause(int startIndex)
{
    _startFrame = _currentFrame = startIndex;
    _time       = _currentFrame * _frameInternal;

    pause();
    gotoFrame(_currentFrame);
}

void ActionTimeline::pause()
{
    _playing = false;
}

void ActionTimeline::resume()
{
    _playing = true;
}

bool ActionTimeline::isPlaying() const
{
    return _playing;
}

void ActionTimeline::setCurrentFrame(int frameIndex)
{
    if (frameIndex >= _startFrame && frameIndex <= _endFrame)
    {
        _currentFrame = frameIndex;
        _time = _currentFrame*_frameInternal;
    }
    else
    {
        CCLOG("frame index is not between start frame and end frame");
    }
}

ActionTimeline* ActionTimeline::clone() const
{
    ActionTimeline* newAction = ActionTimeline::create();
    newAction->setDuration(_duration);
    newAction->setTimeSpeed(_timeSpeed);

    for (auto timelines : _timelineMap)
    {
        for(auto timeline : timelines.second)
        {      
            Timeline* newTimeline = timeline->clone();
            newAction->addTimeline(newTimeline);
        }
    }
    
    for( auto info : _animationInfos)
    {
        newAction->addAnimationInfo(info.second);
    }
    return newAction;
}

void ActionTimeline::step(float delta)
{
    if (!_playing || _timelineMap.size() == 0 || _duration == 0)
    {
        return;
    }

    _time += delta * _timeSpeed;
    _currentFrame = (int)(_time / _frameInternal);

    stepToFrame(_currentFrame);

    if(_time > _endFrame * _frameInternal)
    {
        if(_lastFrameListener != nullptr)
            _lastFrameListener();

        _playing = _loop;
        if(!_playing)
            _time = _endFrame * _frameInternal;
        else           
            gotoFrameAndPlay(_startFrame, _endFrame, _loop);
    }

}

typedef std::function<void(Node*)> tCallBack;
void foreachNodeDescendant(Node* parent, tCallBack callback)
{
    callback(parent);

    auto& children = parent->getChildren();
    for (auto child : children)
    {
        foreachNodeDescendant(child, callback);
    }
}

void ActionTimeline::startWithTarget(Node *target)
{
    Action::startWithTarget(target);
    this->setTag(target->getTag());

    foreachNodeDescendant(target, 
        [this, target](Node* child)
    {
        ObjectExtensionData* data = dynamic_cast<ObjectExtensionData*>(child->getUserObject());

        if(data)
        {
            int actionTag = data->getActionTag();
            if(_timelineMap.find(actionTag) != _timelineMap.end())
            {
                auto timelines = this->_timelineMap[actionTag];
                for (auto timeline : timelines)
                {
                    timeline->setNode(child);
                }
            }
        }
    });
}

void ActionTimeline::addTimeline(Timeline* timeline)
{
    int tag = timeline->getActionTag();
    if (_timelineMap.find(tag) == _timelineMap.end())
    {
        _timelineMap[tag] = Vector<Timeline*>();
    }

    if (!_timelineMap[tag].contains(timeline))
    {
        _timelineList.pushBack(timeline);
        _timelineMap[tag].pushBack(timeline);
        timeline->setActionTimeline(this);
    }
}

void ActionTimeline::removeTimeline(Timeline* timeline)
{
    int tag = timeline->getActionTag();
    if (_timelineMap.find(tag) != _timelineMap.end())
    {
        if(_timelineMap[tag].contains(timeline))
        {
            _timelineMap[tag].eraseObject(timeline);
            _timelineList.eraseObject(timeline);
            timeline->setActionTimeline(nullptr);
        }
    }
}


void ActionTimeline::addAnimationInfo(const AnimationInfo& animationInfo)
{
    if (_animationInfos.find(animationInfo.name) != _animationInfos.end())
    {
        CCLOG("Animation (%s) already exists.", animationInfo.name.c_str());
        return;
    }

    _animationInfos[animationInfo.name] = animationInfo;
}

void ActionTimeline::removeAnimationInfo(std::string animationName)
{
    if (_animationInfos.find(animationName) == _animationInfos.end())
    {
        CCLOG("AnimationInfo (%s) not exists.", animationName.c_str());
        return;
    }

    _animationInfos.erase(animationName);
}

bool ActionTimeline::IsAnimationInfoExists(const std::string& animationName)
{
    return _animationInfos.find(animationName) != _animationInfos.end();
}

AnimationInfo ActionTimeline::getAnimationInfo(const std::string &animationName)
{
    return _animationInfos.find(animationName)->second;
}

void ActionTimeline::setFrameEventCallFunc(std::function<void(Frame *)> listener)
{
    _frameEventListener = listener;
}

void ActionTimeline::clearFrameEventCallFunc()
{
    _frameEventListener = nullptr;
}

void ActionTimeline::setLastFrameCallFunc(std::function<void()> listener)
{
    _lastFrameListener = listener;
}

void ActionTimeline::clearLastFrameCallFunc()
{
    _lastFrameListener = nullptr;
}

void ActionTimeline::emitFrameEvent(Frame* frame)
{
    if(_frameEventListener)
    {
        _frameEventListener(frame);
    }
}

void ActionTimeline::gotoFrame(int frameIndex)
{
    if(_target == nullptr)
        return;

    ssize_t size = _timelineList.size();
    for(ssize_t i = 0; i < size; i++)
    {      
        _timelineList.at(i)->gotoFrame(frameIndex);
    }
}

void ActionTimeline::stepToFrame(int frameIndex)
{
    ssize_t size = _timelineList.size();
    for(ssize_t i = 0; i < size; i++)
    {      
        _timelineList.at(i)->stepToFrame(frameIndex);
    }
}
NS_TIMELINE_END
