/****************************************************************************
 Copyright (c) 2013-2017 Chukong Technologies Inc.
 
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

#ifndef __cocos2d_libs__TouchEvent__
#define __cocos2d_libs__TouchEvent__

#include "base/CCEvent.h"
#include <vector>

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

class Touch;

#define TOUCH_PERF_DEBUG 1

/** @class EventTouch
 * @brief Touch event.
 */
class CC_DLL EventTouch : public Event
{
public:
    static const int MAX_TOUCHES = 15;
    
    /** EventCode Touch event code.*/
    enum class EventCode
    {
        BEGAN,
        MOVED,
        ENDED,
        CANCELLED
    };

    /** 
     * Constructor.
     * @js NA
     */
    EventTouch();

    /** Get event code.
     *
     * @return The code of the event.
     */
    EventCode getEventCode() const { return _eventCode; }
    
    /** Get the touches.
     *
     * @return The touches of the event.
     */
    const std::vector<Touch*>& getTouches() const { return _touches; }

#if TOUCH_PERF_DEBUG
    /** Set the event code.
     * 
     * @param eventCode A given EventCode.
     */
    void setEventCode(EventCode eventCode) { _eventCode = eventCode; };
    /** Set the touches
     *
     * @param touches A given touches vector.
     */
    void setTouches(const std::vector<Touch*>& touches) { _touches = touches; };
#endif
    
private:
    EventCode _eventCode;
    std::vector<Touch*> _touches;

    friend class GLView;
};


NS_CC_END

// end of base group
/// @}

#endif /* defined(__cocos2d_libs__TouchEvent__) */
