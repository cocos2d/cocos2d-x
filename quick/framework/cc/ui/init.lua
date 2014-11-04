
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

初始化 cc.ui 扩展

cc.ui 提供了一套 quick 专属的纯 lua UI控件模块

]]

local c = cc
local ui = {}

function makeUIControl_(control)
    cc(control)
    control:addComponent("components.ui.LayoutProtocol"):exportMethods()
    control:addComponent("components.behavior.EventProtocol"):exportMethods()

    control:setCascadeOpacityEnabled(true)
    control:setCascadeColorEnabled(true)
    control:addNodeEventListener(c.NODE_EVENT, function(event)
        if event.name == "cleanup" then
            control:removeAllEventListeners()
        end
    end)
end

ui.TEXT_ALIGN_LEFT    = cc.TEXT_ALIGNMENT_LEFT
ui.TEXT_ALIGN_CENTER  = cc.TEXT_ALIGNMENT_CENTER
ui.TEXT_ALIGN_RIGHT   = cc.TEXT_ALIGNMENT_RIGHT
ui.TEXT_VALIGN_TOP    = cc.VERTICAL_TEXT_ALIGNMENT_TOP
ui.TEXT_VALIGN_CENTER = cc.VERTICAL_TEXT_ALIGNMENT_CENTER
ui.TEXT_VALIGN_BOTTOM = cc.VERTICAL_TEXT_ALIGNMENT_BOTTOM

ui.UIGroup               = import(".UIGroup")
ui.UIImage               = import(".UIImage")
ui.UIPushButton          = import(".UIPushButton")
ui.UICheckBoxButton      = import(".UICheckBoxButton")
ui.UICheckBoxButtonGroup = import(".UICheckBoxButtonGroup")
ui.UIInput               = import(".UIInput")
ui.UILabel               = import(".UILabel")
ui.UISlider              = import(".UISlider")
ui.UIBoxLayout           = import(".UIBoxLayout")
ui.UIScrollView          = import(".UIScrollView")
ui.UIListView            = import(".UIListView")
ui.UIPageView            = import(".UIPageView")
ui.UILoadingBar          = import(".UILoadingBar")

return ui
