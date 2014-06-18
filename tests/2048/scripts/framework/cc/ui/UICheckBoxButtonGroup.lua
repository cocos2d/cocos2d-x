
local UIBoxLayout = import(".UIBoxLayout")
local UICheckBoxButton = import(".UICheckBoxButton")

local UIGroup = import(".UIGroup")
local UICheckBoxButtonGroup = class("UICheckBoxButtonGroup", UIGroup)

UICheckBoxButtonGroup.BUTTON_SELECT_CHANGED = "BUTTON_SELECT_CHANGED"

function UICheckBoxButtonGroup:ctor(direction)
    UICheckBoxButtonGroup.super.ctor(self)
    self:setLayout(UIBoxLayout.new(direction or display.LEFT_TO_RIGHT))
    self.buttons_ = {}
    self.currentSelectedIndex_ = 0
end

function UICheckBoxButtonGroup:addButton(button)
    self:addChild(button)
    self.buttons_[#self.buttons_ + 1] = button
    self:getLayout():addWidget(button):apply(self)
    button:onButtonClicked(handler(self, self.onButtonStateChanged_))
    button:onButtonStateChanged(handler(self, self.onButtonStateChanged_))
    return self
end

function UICheckBoxButtonGroup:removeButtonAtIndex(index)
    assert(self.buttons_[index] ~= nil, "UICheckBoxButtonGroup:removeButtonAtIndex() - invalid index")

    local button = self.buttons_[index]
    local layout = self:getLayout()
    layout:removeWidget(button)
    layout:apply(self)

    button:removeSelf()
    table.remove(self.buttons_, index)

    if self.currentSelectedIndex_ == index then
        self:updateButtonState_(nil)
    elseif index < self.currentSelectedIndex_ then
        self:updateButtonState_(self.buttons_[self.currentSelectedIndex_ - 1])
    end

    return self
end

function UICheckBoxButtonGroup:getButtonAtIndex(index)
    return self.buttons_[index]
end

function UICheckBoxButtonGroup:getButtonsCount()
    return #self.buttons_
end

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
