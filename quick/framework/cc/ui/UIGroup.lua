
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
-- @module UIGroup

--[[--

quick UIGroup控件

]]

local UIBoxLayout = import(".UIBoxLayout")
local UIImage = import(".UIImage")

local UIGroup = class("UIGroup", function()
    return display.newNode()
end)

-- start --

--------------------------------
-- UIGroup构建函数
-- @function [parent=#UIGroup] new

-- end --

function UIGroup:ctor()
    makeUIControl_(self)
    self:setLayout(UIBoxLayout.new(display.LEFT_TO_RIGHT))
    self:setLayoutSizePolicy(display.AUTO_SIZE, display.AUTO_SIZE)
    self:align(display.LEFT_BOTTOM)
end

-- start --

--------------------------------
-- 添加一个控件
-- @function [parent=#UIGroup] addWidget
-- @param node widget 控件
-- @return UIGroup#UIGroup 

-- end --

function UIGroup:addWidget(widget)
    self:addChild(widget)
    self:getLayout():addWidget(widget)
    return self
end

-- start --

--------------------------------
-- 触摸监听函数
-- @function [parent=#UIGroup] onTouch
-- @param function listener 函数
-- @return UIGroup#UIGroup 

-- end --

function UIGroup:onTouch(listener)
    if not listener then listener = function() return true end end
    if USE_DEPRECATED_EVENT_ARGUMENTS then
        self:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
            return listener(event.name, event.x, event.y, event.prevX, event.prevY)
        end)
    else
        self:addNodeEventListener(cc.NODE_TOUCH_EVENT, listener)
    end
    return self
end

-- start --

--------------------------------
-- 打开触摸功能
-- @function [parent=#UIGroup] enableTouch
-- @param boolean enabled
-- @return UIGroup#UIGroup 

-- end --

function UIGroup:enableTouch(enabled)
    self:setTouchEnabled(enabled)
    return self
end

-- start --

--------------------------------
-- 设置大小
-- @function [parent=#UIGroup] setLayoutSize
-- @param number width
-- @param number height
-- @return UIGroup#UIGroup 

-- end --

function UIGroup:setLayoutSize(width, height)
    self:getComponent("components.ui.LayoutProtocol"):setLayoutSize(width, height)
    if self.backgroundSprite_ then
        self.backgroundSprite_:setLayoutSize(self:getLayoutSize())
    end
    return self
end

-- start --

--------------------------------
-- 设置背景图片
-- @function [parent=#UIGroup] setBackgroundImage
-- @param string filename 图片名
-- @param table args 图片控件的参数表
-- @return UIGroup#UIGroup 
-- @see UIImage

-- end --

function UIGroup:setBackgroundImage(filename, args)
    self.backgroundSprite_ = UIImage.new(filename, args):setLayoutSize(self:getLayoutSize())
    self:addChild(self.backgroundSprite_)
    return self
end

return UIGroup
