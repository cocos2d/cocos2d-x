
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
-- @module UIStretch

--[[--

quick 拉伸控件

]]

local UIStretch = class("UIStretch")

-- start --

--------------------------------
-- quick 拉伸控件
-- @function [parent=#UIStretch] new

-- end --

function UIStretch:ctor()
    cc(self):addComponent("components.ui.LayoutProtocol"):exportMethods()
    self:setLayoutSizePolicy(display.AUTO_SIZE, display.AUTO_SIZE)
    self.position_ = {x = 0, y = 0}
    self.anchorPoint_ = display.ANCHOR_POINTS[display.CENTER]
end

-- start --

--------------------------------
-- 得到位置信息
-- @function [parent=#UIStretch] getPosition
-- @return number#number  x
-- @return number#number  y

-- end --

function UIStretch:getPosition()
    return self.position_.x, self.position_.y
end

-- start --

--------------------------------
-- 得到x位置信息
-- @function [parent=#UIStretch] getPositionX
-- @return number#number  x

-- end --

function UIStretch:getPositionX()
    return self.position_.x
end

-- start --

--------------------------------
-- 得到y位置信息
-- @function [parent=#UIStretch] getPositionY
-- @return number#number  y

-- end --

function UIStretch:getPositionY()
    return self.position_.y
end

-- start --

--------------------------------
-- 设置位置信息
-- @function [parent=#UIStretch] setPosition
-- @param number x x的位置
-- @param number y y的位置

-- end --

function UIStretch:setPosition(x, y)
    self.position_.x, self.position_.y = x, y
end

-- start --

--------------------------------
-- 设置x位置信息
-- @function [parent=#UIStretch] setPositionX
-- @param number x x的位置

-- end --

function UIStretch:setPositionX(x)
    self.position_.x = x
end

-- start --

--------------------------------
-- 设置y位置信息
-- @function [parent=#UIStretch] setPositionY
-- @param number y y的位置

-- end --

function UIStretch:setPositionY(y)
    self.position_.y = y
end

-- start --

--------------------------------
-- 得到锚点位置信息
-- @function [parent=#UIStretch] getAnchorPoint
-- @return table#table  位置信息

-- end --

function UIStretch:getAnchorPoint()
    return self.anchorPoint_
end

-- start --

--------------------------------
-- 设置锚点位置
-- @function [parent=#UIStretch] setAnchorPoint
-- @param ap 锚点

-- end --

function UIStretch:setAnchorPoint(ap)
    self.anchorPoint_ = ap
end


return UIStretch
