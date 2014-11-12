
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

quick 拉伸控件

]]

local UIStretch = class("UIStretch")

function UIStretch:ctor()
    cc(self):addComponent("components.ui.LayoutProtocol"):exportMethods()
    self:setLayoutSizePolicy(display.AUTO_SIZE, display.AUTO_SIZE)
    self.position_ = {x = 0, y = 0}
    self.anchorPoint_ = display.ANCHOR_POINTS[display.CENTER]
end

--[[--

得到位置信息

@return number x
@return number y

]]
function UIStretch:getPosition()
    return self.position_.x, self.position_.y
end

--[[--

得到x位置信息

@return number x

]]
function UIStretch:getPositionX()
    return self.position_.x
end

--[[--

得到y位置信息

@return number y

]]
function UIStretch:getPositionY()
    return self.position_.y
end


--[[--

设置位置信息

@param number x x的位置
@param number y y的位置

]]
function UIStretch:setPosition(x, y)
    self.position_.x, self.position_.y = x, y
end

--[[--

设置x位置信息

@param number x x的位置

]]
function UIStretch:setPositionX(x)
    self.position_.x = x
end

--[[--

设置y位置信息

@param number y y的位置

]]
function UIStretch:setPositionY(y)
    self.position_.y = y
end

--[[--

得到锚点位置信息

@return table 位置信息

]]
function UIStretch:getAnchorPoint()
    return self.anchorPoint_
end

--[[--

设置锚点位置

@param ap 锚点

]]
function UIStretch:setAnchorPoint(ap)
    self.anchorPoint_ = ap
end


return UIStretch
