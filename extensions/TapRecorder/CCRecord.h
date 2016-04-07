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

#ifndef TapRecorder_Record_h
#define TapRecorder_Record_h

#include <map>
#include "extensions/ExtensionMacros.h"
#include "math/Vec2.h"
#include "base/CCEventTouch.h"

NS_CC_EXT_BEGIN

namespace TapRecorder
{
    enum DurationUnit { Millisecond, Frame };
    
    struct Record
    {
    public:
        typedef std::map<std::string, std::string> StringifiedMapRecord;
        
        Record();
        Record(const std::string&, DurationUnit, unsigned long);
        Record(StringifiedMapRecord&);
        Record(int, DurationUnit, unsigned long, cocos2d::EventTouch::EventCode, cocos2d::Vec2);
        
        static const int CAPTURE_TOUCH_ID;
        
        static const std::string KEY_TOUCH_ID;
        static const std::string KEY_DURATION_UNIT;
        static const std::string KEY_DURATION;
        static const std::string KEY_EVENT_TYPE;
        static const std::string KEY_POSITION_X;
        static const std::string KEY_POSITION_Y;
        
        int                            touchId;
        DurationUnit                   durationUnit;
        unsigned long                  duration;
        cocos2d::EventTouch::EventCode eventType;
        cocos2d::Vec2                  position;
        
        StringifiedMapRecord toStringifiedMap();
        bool isEqualTo(const Record&);
    };
    
    typedef std::vector<Record> Records;
}

NS_CC_EXT_END

#endif /* TapRecorder_Record_h */
