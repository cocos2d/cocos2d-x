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

#include "CCProtocol.h"

USING_NS_CC_EXT;
using namespace TapRecorder;

RecordAdapter::Interface* Protocol::recordAdapter = nullptr;

void Protocol::setDefaultRecordAdapter()
{
    setRecordAdapter<RecordAdapter::Text>();
}

bool Protocol::update(float dt)
{
    float millsecPassed = toMillisecond(dt);
    
    if ((std::numeric_limits<decltype(durationTime)>::max() - durationTime) < millsecPassed) {
        log("time duration was reached to max count, can't record any more.");
        return false;
    }
    else {
        durationTime += static_cast<unsigned long>(millsecPassed);
    }
    
    if (std::numeric_limits<decltype(durationFrame)>::max() == durationFrame) {
        log("frame duration was reached to max count, can't record any more.");
        return false;
    }
    else {
        durationFrame++;
    }
    
    return true;
}

unsigned long Protocol::toMillisecond(float val)
{
    return val * 1000;
}

void Protocol::resetDurations()
{
    durationTime  = 0;
    durationFrame = 0;
}
