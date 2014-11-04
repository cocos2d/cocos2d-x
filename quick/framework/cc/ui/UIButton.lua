
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

quick Button控件

]]

local UIButton = class("UIButton", function()
    return display.newNode()
end)

UIButton.CLICKED_EVENT = "CLICKED_EVENT"
UIButton.PRESSED_EVENT = "PRESSED_EVENT"
UIButton.RELEASE_EVENT = "RELEASE_EVENT"
UIButton.STATE_CHANGED_EVENT = "STATE_CHANGED_EVENT"

UIButton.IMAGE_ZORDER = -100
UIButton.LABEL_ZORDER = 0

--[[--

UIButton构建函数

@param table events 按钮状态表
@param string initialState 初始状态
@param table options 参数表

]]
function UIButton:ctor(events, initialState, options)
    self.fsm_ = {}
    cc(self.fsm_)
        :addComponent("components.behavior.StateMachine")
        :exportMethods()
    self.fsm_:setupState({
        initial = {state = initialState, event = "startup", defer = false},
        events = events,
        callbacks = {
            onchangestate = handler(self, self.onChangeState_),
        }
    })

    makeUIControl_(self)
    self:setLayoutSizePolicy(display.FIXED_SIZE, display.FIXED_SIZE)
    self:setButtonEnabled(true)
    self:addNodeEventListener(cc.NODE_TOUCH_EVENT, handler(self, self.onTouch_))

    self.touchInSpriteOnly_ = options and options.touchInSprite
    self.currentImage_ = nil
    self.images_ = {}
    self.sprite_ = {}
    self.scale9_ = options and options.scale9
    self.flipX_ = options and options.flipX
    self.flipY_ = options and options.flipY
    self.scale9Size_ = nil
    self.labels_ = {}
    self.labelOffset_ = {0, 0}
    self.labelAlign_ = display.CENTER
    self.initialState_ = initialState

    display.align(self, display.CENTER)

    if "boolean" ~= type(self.flipX_) then
        self.flipX_ = false
    end
    if "boolean" ~= type(self.flipY_) then
        self.flipY_ = false
    end

    self:addNodeEventListener(cc.NODE_EVENT, function(event)
        if event.name == "enter" then
            self:updateButtonImage_()
        end
    end)
end

--[[--

停靠位置

@param number align 锚点位置
@param number x
@param number y

@return UIButton

]]
function UIButton:align(align, x, y)
    display.align(self, align, x, y)
    self:updateButtonImage_()
    self:updateButtonLable_()

    local size = self:getCascadeBoundingBox().size
    local ap = self:getAnchorPoint()

    -- self:setPosition(x + size.width * (ap.x - 0.5), y + size.height * (0.5 - ap.y))
    return self
end

--[[--

设置按钮特定状态的图片

@param string state 状态
@param string image 图片路径
@param boolean ignoreEmpty 是否忽略空的图片路径

@return UIButton

]]
function UIButton:setButtonImage(state, image, ignoreEmpty)
    if ignoreEmpty and image == nil then return end
    self.images_[state] = image
    if state == self.fsm_:getState() then
        self:updateButtonImage_()
    end
    return self
end

--[[--

设置按钮特定状态的文字node

@param string state 状态
@param node label 文字node

@return UIButton

]]
function UIButton:setButtonLabel(state, label)
    if not label then
        label = state
        state = self:getDefaultState_()
    end
    assert(label ~= nil, "UIButton:setButtonLabel() - invalid label")

    if type(state) == "table" then state = state[1] end
    local currentLabel = self.labels_[state]
    if currentLabel then currentLabel:removeSelf() end

    self.labels_[state] = label
    self:addChild(label, UIButton.LABEL_ZORDER)
    self:updateButtonLable_()
    return self
end

--[[--

返回按钮特定状态的文字

@param string state 状态

@return node 文字label

]]
function UIButton:getButtonLabel(state)
    if not state then
        state = self:getDefaultState_()
    end
    if type(state) == "table" then state = state[1] end
    return self.labels_[state]
end

--[[--

设置按钮特定状态的文字

@param string state 状态
@param string text 文字

@return UIButton

]]
function UIButton:setButtonLabelString(state, text)
    assert(self.labels_ ~= nil, "UIButton:setButtonLabelString() - not add label")
    if text == nil then
        text = state
        for _, label in pairs(self.labels_) do
            label:setString(text)
        end
    else
        local label = self.labels_[state]
        if label then label:setString(text) end
    end
    return self
end

--[[--

返回文字标签的偏移

@return number x
@return number y

]]
function UIButton:getButtonLabelOffset()
    return self.labelOffset_[1], self.labelOffset_[2]
end

--[[--

设置文字标签的偏移

@param number x
@param number y

@return UIButton

]]
function UIButton:setButtonLabelOffset(ox, oy)
    self.labelOffset_ = {ox, oy}
    self:updateButtonLable_()
    return self
end

--[[--

得到文字标签的停靠方式

@return number

]]
function UIButton:getButtonLabelAlignment()
    return self.labelAlign_
end

--[[--

设置文字标签的停靠方式

@param number align

@return UIButton

]]
function UIButton:setButtonLabelAlignment(align)
    self.labelAlign_ = align
    self:updateButtonLable_()
    return self
end

--[[--

设置按钮的大小

@param number width
@param number height

@return UIButton

]]
function UIButton:setButtonSize(width, height)
    -- assert(self.scale9_, "UIButton:setButtonSize() - can't change size for non-scale9 button")
    self.scale9Size_ = {width, height}
    for i,v in ipairs(self.sprite_) do
        if self.scale9_ then
            v:setContentSize(cc.size(self.scale9Size_[1], self.scale9Size_[2]))
        else
            local size = v:getContentSize()
            local scaleX = v:getScaleX()
            local scaleY = v:getScaleY()
            scaleX = scaleX * self.scale9Size_[1]/size.width
            scaleY = scaleY * self.scale9Size_[2]/size.height
            v:setScaleX(scaleX)
            v:setScaleY(scaleY)
        end
    end
    return self
end

--[[--

设置按钮是否有效

@param boolean enabled 是否有效

@return UIButton

]]
function UIButton:setButtonEnabled(enabled)
    self:setTouchEnabled(enabled)
    if enabled and self.fsm_:canDoEvent("enable") then
        self.fsm_:doEventForce("enable")
        self:dispatchEvent({name = UIButton.STATE_CHANGED_EVENT, state = self.fsm_:getState()})
    elseif not enabled and self.fsm_:canDoEvent("disable") then
        self.fsm_:doEventForce("disable")
        self:dispatchEvent({name = UIButton.STATE_CHANGED_EVENT, state = self.fsm_:getState()})
    end
    return self
end

--[[--

返回按钮是否有效

@return boolean

]]
function UIButton:isButtonEnabled()
    return self.fsm_:canDoEvent("disable")
end

function UIButton:addButtonClickedEventListener(callback)
    return self:addEventListener(UIButton.CLICKED_EVENT, callback)
end

--[[--

注册用户点击监听

@param function callback 监听函数

@return UIButton

]]
function UIButton:onButtonClicked(callback)
    self:addButtonClickedEventListener(callback)
    return self
end

function UIButton:addButtonPressedEventListener(callback)
    return self:addEventListener(UIButton.PRESSED_EVENT, callback)
end

--[[--

注册用户按下监听

@param function callback 监听函数

@return UIButton

]]
function UIButton:onButtonPressed(callback)
    self:addButtonPressedEventListener(callback)
    return self
end

function UIButton:addButtonReleaseEventListener(callback)
    return self:addEventListener(UIButton.RELEASE_EVENT, callback)
end

--[[--

注册用户释放监听

@param function callback 监听函数

@return UIButton

]]
function UIButton:onButtonRelease(callback)
    self:addButtonReleaseEventListener(callback)
    return self
end

function UIButton:addButtonStateChangedEventListener(callback)
    return self:addEventListener(UIButton.STATE_CHANGED_EVENT, callback)
end

--[[--

注册按钮状态变化监听

@param function callback 监听函数

@return UIButton

]]
function UIButton:onButtonStateChanged(callback)
    self:addButtonStateChangedEventListener(callback)
    return self
end

function UIButton:onChangeState_(event)
    if self:isRunning() then
        self:updateButtonImage_()
        self:updateButtonLable_()
    end
end

function UIButton:onTouch_(event)
    printError("UIButton:onTouch_() - must override in inherited class")
end

function UIButton:updateButtonImage_()
    local state = self.fsm_:getState()
    local image = self.images_[state]

    if not image then
        for _, s in pairs(self:getDefaultState_()) do
            image = self.images_[s]
            if image then break end
        end
    end
    if image then
        if self.currentImage_ ~= image then
            for i,v in ipairs(self.sprite_) do
                v:removeFromParent(true)
            end
            self.sprite_ = {}
            self.currentImage_ = image

            if "table" == type(image) then
                for i,v in ipairs(image) do
                    if self.scale9_ then
                        self.sprite_[i] = display.newScale9Sprite(v)
                        if not self.scale9Size_ then
                            local size = self.sprite_[i]:getContentSize()
                            self.scale9Size_ = {size.width, size.height}
                        else
                            self.sprite_[i]:setContentSize(cc.size(self.scale9Size_[1], self.scale9Size_[2]))
                        end
                    else
                        self.sprite_[i] = display.newSprite(v)
                    end
                    self:addChild(self.sprite_[i], UIButton.IMAGE_ZORDER)
                    if self.sprite_[i].setFlippedX then
                        if self.flipX_ then
                            self.sprite_[i]:setFlippedX(self.flipX_ or false)
                        end
                        if self.flipY_ then
                            self.sprite_[i]:setFlippedY(self.flipY_ or false)
                        end
                    end
                end
            else
                if self.scale9_ then
                    self.sprite_[1] = display.newScale9Sprite(image)
                    if not self.scale9Size_ then
                        local size = self.sprite_[1]:getContentSize()
                        self.scale9Size_ = {size.width, size.height}
                    else
                        self.sprite_[1]:setContentSize(cc.size(self.scale9Size_[1], self.scale9Size_[2]))
                    end
                else
                    self.sprite_[1] = display.newSprite(image)
                end
                if self.sprite_[1].setFlippedX then
                    if self.flipX_ then
                        self.sprite_[1]:setFlippedX(self.flipX_ or false)
                    end
                    if self.flipY_ then
                        self.sprite_[1]:setFlippedY(self.flipY_ or false)
                    end
                end
                self:addChild(self.sprite_[1], UIButton.IMAGE_ZORDER)
            end
        end

        for i,v in ipairs(self.sprite_) do
            v:setAnchorPoint(self:getAnchorPoint())
            v:setPosition(0, 0)
        end
    elseif not self.labels_ then
        printError("UIButton:updateButtonImage_() - not set image for state %s", state)
    end
end

function UIButton:updateButtonLable_()
    if not self.labels_ then return end
    local state = self.fsm_:getState()
    local label = self.labels_[state]

    if not label then
        for _, s in pairs(self:getDefaultState_()) do
            label = self.labels_[s]
            if label then break end
        end
    end

    local ox, oy = self.labelOffset_[1], self.labelOffset_[2]
    if self.sprite_[1] then
        local ap = self:getAnchorPoint()
        local spriteSize = self.sprite_[1]:getContentSize()
        ox = ox + spriteSize.width * (0.5 - ap.x)
        oy = oy + spriteSize.height * (0.5 - ap.y)
    end

    for _, l in pairs(self.labels_) do
        l:setVisible(l == label)
        l:align(self.labelAlign_, ox, oy)
    end
end

function UIButton:getDefaultState_()
    return {self.initialState_}
end

function UIButton:checkTouchInSprite_(x, y)
    if self.touchInSpriteOnly_ then
        return self.sprite_[1] and self.sprite_[1]:getCascadeBoundingBox():containsPoint(cc.p(x, y))
    else
        return self:getCascadeBoundingBox():containsPoint(cc.p(x, y))
    end
end

return UIButton
