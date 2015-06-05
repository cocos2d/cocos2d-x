/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#ifndef __cocos2d_libs__CCEventFocus__
#define __cocos2d_libs__CCEventFocus__

#include "base/CCEvent.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

namespace ui {
    class Widget;
}

/** @class EventFocus
 * @brief @~english Focus event.
 * @~chinese 焦点事件.
 */
class CC_DLL EventFocus : public Event
{
public:
    /** @~english Constructor.
     *
     * @~chinese 构造函数.
     * 
     * @param widgetLoseFocus @~english The widget which lose focus.
     * @~chinese 失去焦点的界面组件.
     * @param widgetGetFocus @~english The widget which get focus.
     * @~chinese 获得焦点的界面组件.
     * @js ctor
     */
    EventFocus(ui::Widget* widgetLoseFocus, ui::Widget* widgetGetFocus);
    
private:
    ui::Widget *_widgetGetFocus;
    ui::Widget *_widgetLoseFocus;
    
    friend class EventListenerFocus;
};


NS_CC_END

// end of base group
/// @}

#endif /* defined(__cocos2d_libs__CCEventFocus__) */
