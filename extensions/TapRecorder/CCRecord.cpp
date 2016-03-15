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

#include "CCRecord.h"
#include "extensions/TapRecorder/CCUtilTapRecorder.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace TapRecorder;

const int Record::CAPTURE_TOUCH_ID = -99;

const std::string Record::KEY_TOUCH_ID      = "touchId";
const std::string Record::KEY_DURATION_UNIT = "durationUnit";
const std::string Record::KEY_DURATION      = "duration";
const std::string Record::KEY_EVENT_TYPE    = "eventType";
const std::string Record::KEY_POSITION_X    = "positionX";
const std::string Record::KEY_POSITION_Y    = "positionY";

Record::Record()
: touchId(-1)
, durationUnit(Frame)
, duration(0)
, eventType(EventTouch::EventCode::BEGAN)
, position(Vec2::ZERO)
{
}

Record::Record(const std::string& _captureName, DurationUnit _unit, unsigned long _duration)
: touchId(Record::CAPTURE_TOUCH_ID)
, durationUnit(_unit)
, duration(_duration)
, eventType(EventTouch::EventCode::BEGAN)
, position(Vec2::ZERO)
{
}

Record::Record(StringifiedMapRecord& map)
{
    touchId      = atoi(map[KEY_TOUCH_ID].c_str());
    durationUnit = static_cast<DurationUnit>(atoi(map[Record::KEY_DURATION_UNIT].c_str()));
    duration     = std::strtoul(map[Record::KEY_DURATION].c_str(), nullptr, 0);
    eventType    = static_cast<EventTouch::EventCode>(atoi(map[Record::KEY_EVENT_TYPE].c_str()));
    position     = Vec2(atof(map[Record::KEY_POSITION_X].c_str()),
                        atof(map[Record::KEY_POSITION_Y].c_str()));
}

Record::Record(int _touchId, DurationUnit _unit, unsigned long _duration, EventTouch::EventCode _eventType, Vec2 _postion)
: touchId(_touchId)
, durationUnit(_unit)
, duration(_duration)
, eventType(_eventType)
, position(_postion)
{
}

Record::StringifiedMapRecord Record::toStringifiedMap()
{
    std::map<std::string, std::string> map;
    map[KEY_TOUCH_ID]      = Util::to_string<int>(touchId);
    map[KEY_DURATION_UNIT] = Util::to_string<int>(static_cast<int>(durationUnit));
    map[KEY_DURATION]      = Util::to_string<unsigned long>(duration);
    map[KEY_EVENT_TYPE]    = Util::to_string<int>(static_cast<int>(eventType));
    map[KEY_POSITION_X]    = Util::to_string<float>(position.x);
    map[KEY_POSITION_Y]    = Util::to_string<float>(position.y);
    
    return map;
}

bool Record::isEqualTo(const Record& another)
{
    return (touchId      == another.touchId
            && eventType == another.eventType
            && duration  == another.duration
            && position  == another.position);
}
