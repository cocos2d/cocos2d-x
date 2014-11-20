
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
-- @module UILayout

--[[--

quick 布局控件

]]

local UIStretch = import(".UIStretch")

local UILayout = class("UILayout")

local nameIndex_ = 1

-- start --

--------------------------------
-- 布局控件构建函数
-- @function [parent=#UILayout] new
-- @param string name 布局控件名字

-- end --

function UILayout:ctor(name)
    cc(self):addComponent("components.ui.LayoutProtocol"):exportMethods()
    self:setLayoutSizePolicy(display.AUTO_SIZE, display.AUTO_SIZE)
    if not name then
        name = string.format("layout-%d", nameIndex_)
        nameIndex_ = nameIndex_ + 1
    end
    self.name_ = name
    self.position_ = {x = 0, y = 0}
    self.anchorPoint_ = display.ANCHOR_POINTS[display.CENTER]
    self.order_ = 0

    self.widgets_ = {}
    local m = {__mode = "k"}
    setmetatable(self.widgets_, m)

    self.persistent_ = {}
end

-- start --

--------------------------------
-- 返回布局控件名字
-- @function [parent=#UILayout] getName
-- @return string#string 

-- end --

function UILayout:getName()
    return self.name_
end

-- start --

--------------------------------
-- 添加一个布局
-- @function [parent=#UILayout] addLayout
-- @param node layout 布局node
-- @param number weight 布局所占的weight,默认为1
-- @return UILayout#UILayout 

-- end --

function UILayout:addLayout(layout, weight)
    self:addWidget(layout, weight)
    self.persistent_[#self.persistent_ + 1] = layout
    return self
end

-- start --

--------------------------------
-- 添加一个widget
-- @function [parent=#UILayout] addWidget
-- @param node widget 控件
-- @param number weight 控件所占的weight,默认为1
-- @return UILayout#UILayout 

-- end --

function UILayout:addWidget(widget, weight)
    self.order_ = self.order_ + 1
    self.widgets_[widget] = {weight = weight or 1, order = self.order_}
    return self
end

-- start --

--------------------------------
-- 移除一个widget
-- @function [parent=#UILayout] removeWidget
-- @param node widget 要移除的控件
-- @return UILayout#UILayout 

-- end --

function UILayout:removeWidget(widget)
    for w, _ in pairs(self.widgets_) do
        if w == widget then
            self.widgets_[w] = nil
            break
        end
    end
    return self
end

-- start --

--------------------------------
-- 增加一个可伸展的布局
-- @function [parent=#UILayout] addStretch
-- @param number weight 可伸展布展所占的weight
-- @return UILayout#UILayout 

-- end --

function UILayout:addStretch(weight)
    local stretch = UIStretch.new()
    self:addWidget(stretch, weight)
    self.persistent_[#self.persistent_ + 1] = stretch
    return self
end

-- start --

--------------------------------
-- 返回位置信息
-- @function [parent=#UILayout] getPosition
-- @return number#number  x
-- @return number#number  y

-- end --

function UILayout:getPosition()
    return self.position_.x, self.position_.y
end

-- start --

--------------------------------
-- 返回x位置信息
-- @function [parent=#UILayout] getPositionX
-- @return number#number  x

-- end --

function UILayout:getPositionX()
    return self.position_.x
end

-- start --

--------------------------------
-- 返回y位置信息
-- @function [parent=#UILayout] getPositionY
-- @return number#number  y

-- end --

function UILayout:getPositionY()
    return self.position_.y
end

-- start --

--------------------------------
-- 设置位置信息
-- @function [parent=#UILayout] setPosition
-- @param number x
-- @param number y

-- end --

function UILayout:setPosition(x, y)
    self.position_.x, self.position_.y = x, y
end

-- start --

--------------------------------
-- 设置x位置信息
-- @function [parent=#UILayout] setPositionX
-- @param number x

-- end --

function UILayout:setPositionX(x)
    self.position_.x = x
end

-- start --

--------------------------------
-- 设置y位置信息
-- @function [parent=#UILayout] setPositionY
-- @param number y

-- end --

function UILayout:setPositionY(y)
    self.position_.y = y
end

-- start --

--------------------------------
-- 返回锚点信息
-- @function [parent=#UILayout] getAnchorPoint
-- @return table#table  锚点位置

-- end --

function UILayout:getAnchorPoint()
    return self.anchorPoint_
end

-- start --

--------------------------------
-- 设置锚点信息
-- @function [parent=#UILayout] setAnchorPoint
-- @param table 锚点位置

-- end --

function UILayout:setAnchorPoint(ap)
    self.anchorPoint_ = ap
end

function UILayout:apply(container)
end

return UILayout
