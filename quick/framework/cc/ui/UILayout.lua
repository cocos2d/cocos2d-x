
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

quick 布局控件

]]

local UIStretch = import(".UIStretch")

local UILayout = class("UILayout")

local nameIndex_ = 1

--[[--

布局控件构建函数

@param string name 布局控件名字

]]
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

--[[--

返回布局控件名字

@return string

]]
function UILayout:getName()
    return self.name_
end

--[[--

添加一个布局

@param node layout 布局node
@param number weight 布局所占的weight,默认为1

@return UILayout

]]
function UILayout:addLayout(layout, weight)
    self:addWidget(layout, weight)
    self.persistent_[#self.persistent_ + 1] = layout
    return self
end

--[[--

添加一个widget

@param node widget 控件
@param number weight 控件所占的weight,默认为1

@return UILayout

]]
function UILayout:addWidget(widget, weight)
    self.order_ = self.order_ + 1
    self.widgets_[widget] = {weight = weight or 1, order = self.order_}
    return self
end

--[[--

移除一个widget

@param node widget 要移除的控件

@return UILayout

]]
function UILayout:removeWidget(widget)
    for w, _ in pairs(self.widgets_) do
        if w == widget then
            self.widgets_[w] = nil
            break
        end
    end
    return self
end

--[[--

增加一个可伸展的布局

@param number weight 可伸展布展所占的weight

@return UILayout

]]
function UILayout:addStretch(weight)
    local stretch = UIStretch.new()
    self:addWidget(stretch, weight)
    self.persistent_[#self.persistent_ + 1] = stretch
    return self
end

--[[--

返回位置信息

@return number x
@return number y

]]
function UILayout:getPosition()
    return self.position_.x, self.position_.y
end

--[[--

返回x位置信息

@return number x

]]
function UILayout:getPositionX()
    return self.position_.x
end

--[[--

返回y位置信息

@return number y

]]
function UILayout:getPositionY()
    return self.position_.y
end

--[[--

设置位置信息

@param number x
@param number y

]]
function UILayout:setPosition(x, y)
    self.position_.x, self.position_.y = x, y
end

--[[--

设置x位置信息

@param number x

]]
function UILayout:setPositionX(x)
    self.position_.x = x
end

--[[--

设置y位置信息

@param number y

]]
function UILayout:setPositionY(y)
    self.position_.y = y
end

--[[--

返回锚点信息

@return table 锚点位置

]]
function UILayout:getAnchorPoint()
    return self.anchorPoint_
end

--[[--

设置锚点信息

@param table 锚点位置

]]
function UILayout:setAnchorPoint(ap)
    self.anchorPoint_ = ap
end

function UILayout:apply(container)
end

return UILayout
