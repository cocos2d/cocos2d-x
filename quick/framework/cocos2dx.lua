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

--------------------------------
-- @module cocos2dx

--[[--

针对 cocos2d-x 的一些封装和扩展

预定义的节点事件：

-   cc.NODE_EVENT - enter, exit 等事件
-   cc.NODE_ENTER_FRAME_EVENT - 帧事件
-   cc.NODE_TOUCH_EVENT - 触摸事件
-   cc.NODE_TOUCH_CAPTURE_EVENT - 捕获触摸事件

预定义的层事件：

-   cc.ACCELERATE_EVENT - 重力感应事件
-   cc.KEYPAD_EVENT - 硬件按键事件

预定义的触摸模式：

-   cc.TOUCH_MODE_ALL_AT_ONCE - 多点触摸
-   cc.TOUCH_MODE_ONE_BY_ONE - 单点触摸

]]

local p = cc.PACKAGE_NAME .. ".cocos2dx."

if not cc.p then
-- cc.p exist, so the cocos.init have loaded
require(p .. "Cocos2dConstants")
require(p .. "OpenglConstants")
require(p .. "Cocos2d")
require(p .. "StudioConstants")
end

require(p .. "Event")
require(p .. "ActionEx")
require(p .. "NodeEx")
require(p .. "SceneEx")
require(p .. "SpriteEx")
require(p .. "DrawNodeEx")
