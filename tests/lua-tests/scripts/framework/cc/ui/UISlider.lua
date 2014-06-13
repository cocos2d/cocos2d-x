
local UISlider = class("UISlider", function()
    return display.newNode()
end)

UISlider.BAR             = "bar"
UISlider.BUTTON          = "button"
UISlider.BAR_PRESSED     = "bar_pressed"
UISlider.BUTTON_PRESSED  = "button_pressed"
UISlider.BAR_DISABLED    = "bar_disabled"
UISlider.BUTTON_DISABLED = "button_disabled"

UISlider.PRESSED_EVENT = "PRESSED_EVENT"
UISlider.RELEASE_EVENT = "RELEASE_EVENT"
UISlider.STATE_CHANGED_EVENT = "STATE_CHANGED_EVENT"
UISlider.VALUE_CHANGED_EVENT = "VALUE_CHANGED_EVENT"

UISlider.BAR_ZORDER = 0
UISlider.BUTTON_ZORDER = 1

function UISlider:ctor(direction, images, options)
    self.fsm_ = {}
    cc(self.fsm_)
        :addComponent("components.behavior.StateMachine")
        :exportMethods()
    self.fsm_:setupState({
        initial = {state = "normal", event = "startup", defer = false},
        events = {
            {name = "disable", from = {"normal", "pressed"}, to = "disabled"},
            {name = "enable",  from = {"disabled"}, to = "normal"},
            {name = "press",   from = "normal",  to = "pressed"},
            {name = "release", from = "pressed", to = "normal"},
        },
        callbacks = {
            onchangestate = handler(self, self.onChangeState_),
        }
    })

    makeUIControl_(self)
    self:setLayoutSizePolicy(display.FIXED_SIZE, display.FIXED_SIZE)

    options = checktable(options)
    self.direction_ = direction
    self.isHorizontal_ = direction == display.LEFT_TO_RIGHT or direction == display.RIGHT_TO_LEFT
    self.images_ = clone(images)
    self.scale9_ = options.scale9
    self.scale9Size_ = nil
    self.min_ = checknumber(options.min or 0)
    self.max_ = checknumber(options.max or 100)
    self.value_ = self.min_
    self.buttonPositionRange_ = {min = 0, max = 0}
    self.buttonPositionOffset_ = {x = 0, y = 0}
    self.touchInButtonOnly_ = true
    if type(options.touchInButton) == "boolean" then
        self.touchInButtonOnly_ = options.touchInButton
    end

    self.buttonRotation_ = 0
    self.barSprite_ = nil
    self.buttonSprite_ = nil
    self.currentBarImage_ = nil
    self.currentButtonImage_ = nil

    self:updateImage_()
    self:updateButtonPosition_()

    self:setTouchEnabled(true)
    self:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        return self:onTouch_(event.name, event.x, event.y)
    end)
end

function UISlider:setSliderSize(width, height)
    assert(self.scale9_, "UISlider:setSliderSize() - can't change size for non-scale9 slider")
    self.scale9Size_ = {width, height}
    if self.barSprite_ then
        self.barSprite_:setContentSize(CCSize(self.scale9Size_[1], self.scale9Size_[2]))
    end
    return self
end

function UISlider:setSliderEnabled(enabled)
    self:setTouchEnabled(enabled)
    if enabled and self.fsm_:canDoEvent("enable") then
        self.fsm_:doEventForce("enable")
        self:dispatchEvent({name = UISlider.STATE_CHANGED_EVENT, state = self.fsm_:getState()})
    elseif not enabled and self.fsm_:canDoEvent("disable") then
        self.fsm_:doEventForce("disable")
        self:dispatchEvent({name = UISlider.STATE_CHANGED_EVENT, state = self.fsm_:getState()})
    end
    return self
end

function UISlider:align(align, x, y)
    display.align(self, align, x, y)
    self:updateImage_()
    return self
end

function UISlider:isButtonEnabled()
    return self.fsm_:canDoEvent("disable")
end

function UISlider:getSliderValue()
    return self.value_
end

function UISlider:setSliderValue(value)
    assert(value >= self.min_ and value <= self.max_, "UISlider:setSliderValue() - invalid value")
    if self.value_ ~= value then
        self.value_ = value
        self:updateButtonPosition_()
        self:dispatchEvent({name = UISlider.VALUE_CHANGED_EVENT, value = self.value_})
    end
    return self
end

function UISlider:setSliderButtonRotation(rotation)
    self.buttonRotation_ = rotation
    self:updateImage_()
    return self
end

function UISlider:addSliderValueChangedEventListener(callback)
    return self:addEventListener(UISlider.VALUE_CHANGED_EVENT, callback)
end

function UISlider:onSliderValueChanged(callback)
    self:addSliderValueChangedEventListener(callback)
    return self
end

function UISlider:addSliderPressedEventListener(callback)
    return self:addEventListener(UISlider.PRESSED_EVENT, callback)
end

function UISlider:onSliderPressed(callback)
    self:addSliderPressedEventListener(callback)
    return self
end

function UISlider:addSliderReleaseEventListener(callback)
    return self:addEventListener(UISlider.RELEASE_EVENT, callback)
end

function UISlider:onSliderRelease(callback)
    self:addSliderReleaseEventListener(callback)
    return self
end

function UISlider:addSliderStateChangedEventListener(callback)
    return self:addEventListener(UISlider.STATE_CHANGED_EVENT, callback)
end

function UISlider:onSliderStateChanged(callback)
    self:addSliderStateChangedEventListener(callback)
    return self
end

function UISlider:onTouch_(event, x, y)
    if event == "began" then
        if not self:checkTouchInButton_(x, y) then return false end
        local buttonPosition = self:convertToWorldSpace(self.buttonSprite_:getPositionInCCPoint())
        self.buttonPositionOffset_.x = buttonPosition.x - x
        self.buttonPositionOffset_.y = buttonPosition.y - y
        self.fsm_:doEvent("press")
        self:dispatchEvent({name = UISlider.PRESSED_EVENT, x = x, y = y, touchInTarget = true})
        return true
    end

    local touchInTarget = self:checkTouchInButton_(x, y)
    x = x + self.buttonPositionOffset_.x
    y = y + self.buttonPositionOffset_.y
    local buttonPosition = self:convertToNodeSpace(CCPoint(x, y))
    x = buttonPosition.x
    y = buttonPosition.y
    local offset = 0

    if self.isHorizontal_ then
        if x < self.buttonPositionRange_.min then
            x = self.buttonPositionRange_.min
        elseif x > self.buttonPositionRange_.max then
            x = self.buttonPositionRange_.max
        end
        if self.direction_ == display.LEFT_TO_RIGHT then
            offset = (x - self.buttonPositionRange_.min) / self.buttonPositionRange_.length
        else
            offset = (self.buttonPositionRange_.max - x) / self.buttonPositionRange_.length
        end
    else
        if y < self.buttonPositionRange_.min then
            y = self.buttonPositionRange_.min
        elseif y > self.buttonPositionRange_.max then
            y = self.buttonPositionRange_.max
        end
        if self.direction_ == display.TOP_TO_BOTTOM then
            offset = (self.buttonPositionRange_.max - y) / self.buttonPositionRange_.length
        else
            offset = (y - self.buttonPositionRange_.min) / self.buttonPositionRange_.length
        end
    end

    self:setSliderValue(offset * (self.max_ - self.min_) + self.min_)

    if event ~= "moved" and self.fsm_:canDoEvent("release") then
        self.fsm_:doEvent("release")
        self:dispatchEvent({name = UISlider.RELEASE_EVENT, x = x, y = y, touchInTarget = touchInTarget})
    end
end

function UISlider:checkTouchInButton_(x, y)
    if not self.buttonSprite_ then return false end
    if self.touchInButtonOnly_ then
        return self.buttonSprite_:getCascadeBoundingBox():containsPoint(CCPoint(x, y))
    else
        return self:getCascadeBoundingBox():containsPoint(CCPoint(x, y))
    end
end

function UISlider:updateButtonPosition_()
    if not self.barSprite_ or not self.buttonSprite_ then return end

    local x, y = 0, 0
    local barSize = self.barSprite_:getContentSize()
    local buttonSize = self.buttonSprite_:getContentSize()
    local offset = (self.value_ - self.min_) / (self.max_ - self.min_)
    local ap = self:getAnchorPoint()

    if self.isHorizontal_ then
        x = x - barSize.width * ap.x
        y = y + barSize.height * (0.5 - ap.y)
        self.buttonPositionRange_.length = barSize.width - buttonSize.width
        self.buttonPositionRange_.min = x + buttonSize.width / 2
        self.buttonPositionRange_.max = self.buttonPositionRange_.min + self.buttonPositionRange_.length
        if self.direction_ == display.LEFT_TO_RIGHT then
            x = self.buttonPositionRange_.min + offset * self.buttonPositionRange_.length
        else
            x = self.buttonPositionRange_.min + (1 - offset) * self.buttonPositionRange_.length
        end
    else
        x = x - barSize.width * (0.5 - ap.x)
        y = y - barSize.height * ap.y
        self.buttonPositionRange_.length = barSize.height - buttonSize.height
        self.buttonPositionRange_.min = y + buttonSize.height / 2
        self.buttonPositionRange_.max = self.buttonPositionRange_.min + self.buttonPositionRange_.length
        if self.direction_ == display.TOP_TO_BOTTOM then
            y = self.buttonPositionRange_.min + (1 - offset) * self.buttonPositionRange_.length
        else
            y = self.buttonPositionRange_.min + offset * self.buttonPositionRange_.length
        end
    end

    self.buttonSprite_:setPosition(x, y)
end

function UISlider:updateImage_()
    local state = self.fsm_:getState()

    local barImageName = "bar"
    local buttonImageName = "button"
    local barImage = self.images_[barImageName]
    local buttonImage = self.images_[buttonImageName]
    if state ~= "normal" then
        barImageName = barImageName .. "_" .. state
        buttonImageName = buttonImageName .. "_" .. state
    end

    if self.images_[barImageName] then
        barImage = self.images_[barImageName]
    end
    if self.images_[buttonImageName] then
        buttonImage = self.images_[buttonImageName]
    end

    if barImage then
        if self.currentBarImage_ ~= barImage then
            if self.barSprite_ then
                self.barSprite_:removeFromParentAndCleanup(true)
                self.barSprite_ = nil
            end

            if self.scale9_ then
                self.barSprite_ = display.newScale9Sprite(barImage)
                if not self.scale9Size_ then
                    local size = self.barSprite_:getContentSize()
                    self.scale9Size_ = {size.width, size.height}
                else
                    self.barSprite_:setContentSize(CCSize(self.scale9Size_[1], self.scale9Size_[2]))
                end
            else
                self.barSprite_ = display.newSprite(barImage)
            end
            self:addChild(self.barSprite_, UISlider.BAR_ZORDER)
        end

        self.barSprite_:setAnchorPoint(self:getAnchorPoint())
        self.barSprite_:setPosition(0, 0)
    else
        printError("UISlider:updateImage_() - not set bar image for state %s", state)
    end

    if buttonImage then
        if self.currentButtonImage_ ~= buttonImage then
            if self.buttonSprite_ then
                self.buttonSprite_:removeFromParentAndCleanup(true)
                self.buttonSprite_ = nil
            end
            self.buttonSprite_ = display.newSprite(buttonImage)
            self:addChild(self.buttonSprite_, UISlider.BUTTON_ZORDER)
        end

        self.buttonSprite_:setPosition(0, 0)
        self.buttonSprite_:setRotation(self.buttonRotation_)
        self:updateButtonPosition_()
    else
        printError("UISlider:updateImage_() - not set button image for state %s", state)
    end
end

function UISlider:onChangeState_(event)
    if self:isRunning() then
        self:updateImage_()
    end
end

return UISlider
