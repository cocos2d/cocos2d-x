--[[

Copyright (c) 2011-2014 chukong-inc.com

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

]]

--[[--

定义 cocos2dx 中的事件

]]

local c = cc

-- cocos2dx 引擎级事件
c.NODE_EVENT                 = 0
c.NODE_ENTER_FRAME_EVENT     = 1
c.NODE_TOUCH_EVENT           = 2
c.NODE_TOUCH_CAPTURE_EVENT   = 3
c.MENU_ITEM_CLICKED_EVENT    = 4
c.ACCELERATE_EVENT           = 5
c.KEYPAD_EVENT               = 6

c.NODE_TOUCH_CAPTURING_PHASE = 0
c.NODE_TOUCH_TARGETING_PHASE = 1
