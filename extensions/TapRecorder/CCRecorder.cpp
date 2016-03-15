/****************************************************************************
 Copyright (c) 2016 Yuki Kuwabara <do_low@hotmail.com>
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

#include "CCRecorder.h"
#include "base/CCScheduler.h"
#include "base/CCEventDispatcher.h"
#include "extensions/TapRecorder/CCCapture.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace TapRecorder;

# pragma mark Recorder

std::string Recorder::updateKey = "recorder_update";

Recorder::Recorder()
: Protocol()
, _currentDurationUnit(DurationUnit::Frame)
, _initialized(false)
, _recording(false)
, _recordMillseconds(0)
, _recordFrames(0)
, _listenerOneByOne(nullptr)
, _listenerAllAtOnce(nullptr)
, _listenerTapEmultor(new EventListenerTapRecorder<Recorder>())
, _outputPath("")
{
}

Recorder::~Recorder()
{
    delete _listenerTapEmultor;
    _listenerTapEmultor = nullptr;
}

EventListenerTapRecorder<Recorder>* Recorder::getEventListener()
{
    return _listenerTapEmultor;
}

void Recorder::init()
{
    if (_initialized)
        return;

    // start count duration for abs time
    this->beginUpdate();
    
    _initialized = true;
}

void Recorder::beginUpdate()
{
    Director* director = Director::getInstance();
    Scheduler* scheduler = Director::getInstance()->getScheduler();
    if (scheduler->isScheduled("recorder_update", this))
        return;
    
    scheduler->schedule(std::bind(&Recorder::update, this, std::placeholders::_1), this, director->getAnimationInterval(), false, updateKey);
}

bool Recorder::record(DurationUnit unit)
{
    if (_recording)
        return false;
    
    _recording = true;
    
    _currentDurationUnit = unit;
    
    _listenerOneByOne = EventListenerTouchOneByOne::create();
    _listenerOneByOne->onTouchBegan     = std::bind(&Recorder::onTouchBegan,     this, std::placeholders::_1, std::placeholders::_2);
    _listenerOneByOne->onTouchMoved     = std::bind(&Recorder::onTouchMoved,     this, std::placeholders::_1, std::placeholders::_2);
    _listenerOneByOne->onTouchEnded     = std::bind(&Recorder::onTouchEnded,     this, std::placeholders::_1, std::placeholders::_2);
    _listenerOneByOne->onTouchCancelled = std::bind(&Recorder::onTouchCancelled, this, std::placeholders::_1, std::placeholders::_2);
    
    _listenerAllAtOnce = EventListenerTouchAllAtOnce::create();
    _listenerAllAtOnce->onTouchesBegan     = std::bind(&Recorder::onTouchesBegan,     this, std::placeholders::_1, std::placeholders::_2);
    _listenerAllAtOnce->onTouchesMoved     = std::bind(&Recorder::onTouchesMoved,     this, std::placeholders::_1, std::placeholders::_2);
    _listenerAllAtOnce->onTouchesEnded     = std::bind(&Recorder::onTouchesEnded,     this, std::placeholders::_1, std::placeholders::_2);
    _listenerAllAtOnce->onTouchesCancelled = std::bind(&Recorder::onTouchesCancelled, this, std::placeholders::_1, std::placeholders::_2);
    
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithFixedPriority(_listenerOneByOne,  -9999);
    eventDispatcher->addEventListenerWithFixedPriority(_listenerAllAtOnce, -9999);
    
    Capture::getInstance()->getEventListener()->bindEventCallback("tapemulator_recorder_capture", [this](Capture* cap, int eventType){
        if (eventType == Capture::EventType::BEGAN)
            add(Record("", _currentDurationUnit, ((_currentDurationUnit == DurationUnit::Millisecond) ? durationTime : durationFrame)));
    });
    
    beginUpdate();
    
    _listenerTapEmultor->dispatchEvent(EventType::BEGAN);
    
    return true;
}
bool Recorder::recordForSeconds(DurationUnit unit, unsigned long seconds)
{
    if (_recording)
        return false;
    
    _recordMillseconds = toMillisecond(static_cast<float>(seconds));
    _recordFrames      = 0;
    
    record(unit);
    
    return true;
}
bool Recorder::recordForFrames(DurationUnit unit, unsigned long frames)
{
    if (_recording)
        return false;
    
    _recordMillseconds = 0;
    _recordFrames      = frames;
    
    record(unit);
    
    return true;
}

bool Recorder::stop()
{
    if (!isRecording())
        return false;
    
    _recording = false;
    
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->removeEventListener(_listenerOneByOne);
    eventDispatcher->removeEventListener(_listenerAllAtOnce);
    
    Director::getInstance()->getScheduler()->unschedule(updateKey, this);
    
    _listenerTapEmultor->dispatchEvent(EventType::FINISHED);
    
    return true;
}

bool Recorder::isRecording()
{
    return _recording;
}

void Recorder::add(Record record)
{
    // Same tap between OneByOne and AllAtOnce possibly passed.
    if (records.size() > 0 && record.isEqualTo(records.at(records.size() - 1)))
        return;
    
    records.push_back(record);
}

void Recorder::add(Touch* touch, EventTouch::EventCode code)
{
    add(touch->getID(), _currentDurationUnit, code, Director::getInstance()->convertToGL(touch->getLocationInView()));
}

void Recorder::add(int touchId, DurationUnit unit, EventTouch::EventCode eventType, cocos2d::Vec2 pos)
{
    add(Record({touchId, unit, ((unit == DurationUnit::Millisecond) ? durationTime : durationFrame), eventType, pos}));
}

void Recorder::clear()
{
    records.clear();
}

bool Recorder::save(const std::string& filename)
{
    if (isRecording()) {
        log("can not be saved while recording. please stop recording before save");
        return false;
    }
    
    if (records.size() == 0) {
        log("no taps are recorded, nothing to save");
        return false;
    }
    
    if (recordAdapter == nullptr)
        setDefaultRecordAdapter();
    
    std::vector<std::string> extraInfo = {};
    
    _outputPath = "";
    recordAdapter->save(filename, records, extraInfo);
    if (extraInfo.size() > 0)
        _outputPath = extraInfo.at(0);
    
    _listenerTapEmultor->dispatchEvent(EventType::SAVED);
    
    return true;
}
std::string Recorder::lastSavePath()
{
    return _outputPath;
}

void Recorder::update(float dt)
{
    if (!Protocol::update(dt)) {
        if (isRecording())
            _listenerTapEmultor->dispatchEvent(EventType::CANCELLED);
        stop();
        return;
    }
    
    // stop if current duration went over the recording duration which defined in advance
    if (_recordMillseconds > 0 && durationTime >= _recordMillseconds) {
        _listenerTapEmultor->dispatchEvent(EventType::FINISHED);
        stop();
    }
    else if (_recordFrames > 0 && durationTime >= _recordFrames) {
        _listenerTapEmultor->dispatchEvent(EventType::FINISHED);
        stop();
    }
    
    return;
}

# pragma mark touch listener methods

bool Recorder::onTouchBegan(Touch* touch, Event*)
{
    add(touch, EventTouch::EventCode::BEGAN);
    return true;
}
void Recorder::onTouchMoved(Touch* touch, Event*)
{
    add(touch, EventTouch::EventCode::MOVED);
}
void Recorder::onTouchEnded(Touch* touch, Event*)
{
    add(touch, EventTouch::EventCode::ENDED);
}
void Recorder::onTouchCancelled(Touch* touch, Event*)
{
    add(touch, EventTouch::EventCode::CANCELLED);
}

void Recorder::onTouchesBegan(std::vector<Touch*> touches, Event* event)
{
    for (Touch* touch : touches)
        add(touch, EventTouch::EventCode::BEGAN);
}
void Recorder::onTouchesMoved(std::vector<Touch*> touches, Event* event)
{
    for (Touch* touch : touches)
        add(touch, EventTouch::EventCode::MOVED);
}
void Recorder::onTouchesEnded(std::vector<Touch*> touches, Event* event)
{
    for (Touch* touch : touches)
        add(touch, EventTouch::EventCode::ENDED);
}
void Recorder::onTouchesCancelled(std::vector<Touch*> touches, Event* event)
{
    for (Touch* touch : touches)
        add(touch, EventTouch::EventCode::CANCELLED);
}
