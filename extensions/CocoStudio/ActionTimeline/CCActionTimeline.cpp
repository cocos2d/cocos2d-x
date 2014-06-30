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
#include "CCNodeReader.h"

using namespace cocos2d;

NS_TIMELINE_BEGIN

ActionTimeline* ActionTimeline::create()
{
    ActionTimeline* object = new ActionTimeline();
    if (object && object->init())
    {
        object->autorelease();
        return object;
    }
    CC_SAFE_DELETE(object);
    return NULL;
}

ActionTimeline::ActionTimeline()
    : _timelineList(NULL)
    , _duration(0)
    , _time(0)
    , _timeSpeed(1)
    , _frameInternal(1/60.0f)
    , _playing(false)
    , _currentFrame(0)
    , _startFrame(0)
    , _endFrame(0)
    , _frameEventCallFunc(NULL)
    , _frameEventTarget(NULL)
    , _scriptObjectDict(NULL)
{
}

ActionTimeline::~ActionTimeline()
{
    std::map<int, cocos2d::CCArray*>::const_iterator i = _timelineMap.begin();
    for (; i != _timelineMap.end(); i++)
    {
        CCArray* timelines = i->second;
        CC_SAFE_DELETE(timelines);
    }

    CC_SAFE_DELETE(_timelineList);
    CC_SAFE_RELEASE_NULL(_scriptObjectDict);
}

bool ActionTimeline::init()
{
    _timelineList = new cocos2d::CCArray();
    _timelineList->init();

    return true;
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
    if (frameIndex >= _startFrame && frameIndex >= _endFrame)
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
    
    std::map<int, cocos2d::CCArray*>::const_iterator i = _timelineMap.begin();
    for (; i != _timelineMap.end(); i++)
    {
        CCObject* object = NULL;
        CCARRAY_FOREACH(i->second, object)
        {      
            Timeline* timeline = static_cast<Timeline*>(object);
            Timeline* newTimeline = timeline->clone();
            newAction->addTimeline(newTimeline);
        }
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
        _playing = _loop;
        if(!_playing)
            _time = _endFrame * _frameInternal;
        else           
            _time = _startFrame * _frameInternal;
    }

}


void ActionTimeline::foreachNodeDescendant(CCNode* parent)
{
    TimelineActionData* data = dynamic_cast<TimelineActionData*>(parent->getUserObject());
    CCObject* object = NULL;

    if(data)
    {
        int actionTag = data->getActionTag();

        if(_timelineMap.find(actionTag) != _timelineMap.end())
        {
            CCArray* timelines = this->_timelineMap[actionTag];
            CCARRAY_FOREACH (timelines, object)
            {
                Timeline* timeline = static_cast<Timeline*>(object);
                timeline->setNode(parent);
            }
        }
    }

    CCArray* children = parent->getChildren();
    CCARRAY_FOREACH (children, object)
    {
        CCNode* child = static_cast<CCNode*>(object);
        foreachNodeDescendant(child);
    }
}

void ActionTimeline::startWithTarget(CCNode *target)
{
    CCAction::startWithTarget(target);

    foreachNodeDescendant(target);
}

void ActionTimeline::addTimeline(Timeline* timeline)
{
    int tag = timeline->getActionTag();
    if (_timelineMap.find(tag) == _timelineMap.end())
    {
        CCArray* timelines = new CCArray();
        timelines->init();
        _timelineMap[tag] = timelines;
    }

    if (!_timelineMap[tag]->containsObject(timeline))
    {
        _timelineList->addObject(timeline);
        _timelineMap[tag]->addObject(timeline);
        timeline->setActionTimeline(this);
    }
}

void ActionTimeline::removeTimeline(Timeline* timeline)
{
    int tag = timeline->getActionTag();
    if (_timelineMap.find(tag) != _timelineMap.end())
    {
        if(_timelineMap[tag]->containsObject(timeline))
        {
            _timelineMap[tag]->removeObject(timeline);
            _timelineList->removeObject(timeline);
            timeline->setActionTimeline(NULL);
        }
    }
}

void ActionTimeline::setFrameEventCallFunc  (CCObject *target, SEL_TimelineFrameEventCallFunc callFunc)
{
    _frameEventTarget   = target;
    _frameEventCallFunc = callFunc;
}

void ActionTimeline::clearFrameEventCallFunc()
{
    _frameEventTarget   = NULL;
    _frameEventCallFunc = NULL;
}

void ActionTimeline::emitFrameEvent(Frame* frame)
{
    if (_frameEventTarget != NULL && _frameEventCallFunc != NULL)
    {
        (_frameEventTarget->*_frameEventCallFunc)(frame);
    }
}

void ActionTimeline::gotoFrame(int frameIndex)
{
    int size = _timelineList->count();
    Timeline** timelines = (Timeline**)_timelineList->data->arr;
    for(int i = 0; i<size; i++)
    {      
        timelines[i]->gotoFrame(frameIndex);
    }
}

void ActionTimeline::stepToFrame(int frameIndex)
{
    int size = _timelineList->count();
    Timeline** timelines = (Timeline**)_timelineList->data->arr;
    for(int i = 0; i<size; i++)
    {      
        timelines[i]->stepToFrame(frameIndex);
    }
}

void ActionTimeline::setScriptObjectDict(cocos2d::CCDictionary *scriptObjectDict)
{
    CC_SAFE_RETAIN(scriptObjectDict);
    CC_SAFE_RELEASE(_scriptObjectDict);
    _scriptObjectDict = scriptObjectDict;
}

cocos2d::CCDictionary* ActionTimeline::getScriptObjectDict() const
{
    return _scriptObjectDict;
}

NS_TIMELINE_END
