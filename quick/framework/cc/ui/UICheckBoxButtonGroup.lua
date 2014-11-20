
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
-- @module UICheckBoxButtonGroup

--[[--

quick CheckButton组控件

]]

local UIBoxLayout = import(".UIBoxLayout")
local UICheckBoxButton = import(".UICheckBoxButton")

local UIGroup = import(".UIGroup")
local UICheckBoxButtonGroup = class("UICheckBoxButtonGroup", UIGroup)

UICheckBoxButtonGroup.BUTTON_SELECT_CHANGED = "BUTTON_SELECT_CHANGED"

-- start --

--------------------------------
-- UICheckBoxButtonGroup构建函数
-- @function [parent=#UICheckBoxButtonGroup] new
-- @param integer direction checkBox排列方向

-- end --

function UICheckBoxButtonGroup:ctor(direction)
    UICheckBoxButtonGroup.super.ctor(self)
    self:setLayout(UIBoxLayout.new(direction or display.LEFT_TO_RIGHT))
    self.buttons_ = {}
    self.currentSelectedIndex_ = 0
end

-- start --

--------------------------------
-- 加入一个checkBox
-- @function [parent=#UICheckBoxButtonGroup] addButton
-- @param UICheckBoxButton button checkBox
-- @return UICheckBoxButtonGroup#UICheckBoxButtonGroup  自身
-- @see UICheckBoxButton

-- end --

function UICheckBoxButtonGroup:addButton(button)
    self:addChild(button)
    self.buttons_[#self.buttons_ + 1] = button
    self:getLayout():addWidget(button):apply(self)
    button:onButtonClicked(handler(self, self.onButtonStateChanged_))
    button:onButtonStateChanged(handler(self, self.onButtonStateChanged_))
    return self
end

-- start --

--------------------------------
-- 按index移除掉一个checkBox
-- @function [parent=#UICheckBoxButtonGroup] removeButtonAtIndex
-- @param integer index 要移除checkBox的位置
-- @return UICheckBoxButtonGroup#UICheckBoxButtonGroup  自身

-- end --

function UICheckBoxButtonGroup:removeButtonAtIndex(index)
    assert(self.buttons_[index] ~= nil, "UICheckBoxButtonGroup:removeButtonAtIndex() - invalid index")

    local button = self.buttons_[index]
    local layout = self:getLayout()
    layout:removeWidget(button)
    layout:apply(self)

    button:removeFromParent()
    table.remove(self.buttons_, index)

    if self.currentSelectedIndex_ == index then
        self:updateButtonState_(nil)
    elseif index < self.currentSelectedIndex_ then
        self:updateButtonState_(self.buttons_[self.currentSelectedIndex_ - 1])
    end

    return self
end

-- start --

--------------------------------
-- 按index获取checkBox
-- @function [parent=#UICheckBoxButtonGroup] getButtonAtIndex
-- @param integer index 要获取checkBox的位置
-- @return UICheckBoxButton#UICheckBoxButton 

-- end --

function UICheckBoxButtonGroup:getButtonAtIndex(index)
    return self.buttons_[index]
end

-- start --

--------------------------------
-- 得到UICheckBoxButton的总数
-- @function [parent=#UICheckBoxButtonGroup] getButtonsCount
-- @return integer#integer 

-- end --

function UICheckBoxButtonGroup:getButtonsCount()
    return #self.buttons_
end

-- start --

--------------------------------
-- 设置margin
-- @function [parent=#UICheckBoxButtonGroup] setButtonsLayoutMargin
-- @param number top 上边的空白
-- @param number right 右边的空白
-- @param number bottom 下边的空白
-- @param number left 左边的空白
-- @return UICheckBoxButtonGroup#UICheckBoxButtonGroup  自身

-- end --

function UICheckBoxButtonGroup:setButtonsLayoutMargin(top, right, bottom, left)
    for _, button in ipairs(self.buttons_) do
        button:setLayoutMargin(top, right, bottom, left)
    end
    self:getLayout():apply(self)
    return self
end

function UICheckBoxButtonGroup:addButtonSelectChangedEventListener(callback)
    return self:addEventListener(UICheckBoxButtonGroup.BUTTON_SELECT_CHANGED, callback)
end

-- start --

--------------------------------
-- 注册checkbox状态变化listener
-- @function [parent=#UICheckBoxButtonGroup] onButtonSelectChanged
-- @param function callback
-- @return UICheckBoxButtonGroup#UICheckBoxButtonGroup  自身

-- end --

function UICheckBoxButtonGroup:onButtonSelectChanged(callback)
    self:addButtonSelectChangedEventListener(callback)
    return self
end

function UICheckBoxButtonGroup:onButtonStateChanged_(event)
    if event.name == UICheckBoxButton.STATE_CHANGED_EVENT and event.target:isButtonSelected() == false then
        return
    end
    self:updateButtonState_(event.target)
end

function UICheckBoxButtonGroup:updateButtonState_(clickedButton)
    local currentSelectedIndex = 0
    for index, button in ipairs(self.buttons_) do
        if button == clickedButton then
            currentSelectedIndex = index
            if not button:isButtonSelected() then
                button:setButtonSelected(true)
            end
        else
            if button:isButtonSelected() then
                button:setButtonSelected(false)
            end
        end
    end
    if self.currentSelectedIndex_ ~= currentSelectedIndex then
        local last = self.currentSelectedIndex_
        self.currentSelectedIndex_ = currentSelectedIndex
        self:dispatchEvent({name = UICheckBoxButtonGroup.BUTTON_SELECT_CHANGED, selected = currentSelectedIndex, last = last})
    end
end

return UICheckBoxButtonGroup
