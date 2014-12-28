
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
-- @module UIPushButton

--[[--

quick 按钮控件

]]

local UIButton = import(".UIButton")
local UIPushButton = class("UIPushButton", UIButton)

UIPushButton.NORMAL   = "normal"
UIPushButton.PRESSED  = "pressed"
UIPushButton.DISABLED = "disabled"

-- start --

--------------------------------
-- 按钮控件构建函数
-- @function [parent=#UIPushButton] ctor
-- @param table images 各种状态的图片
-- @param table options 参数表 其中scale9为是否缩放

--[[--

按钮控件构建函数

状态值:
-   normal 正常状态
-   pressed 按下状态
-   disabled 无效状态

]]
-- end --

function UIPushButton:ctor(images, options)
    UIPushButton.super.ctor(self, {
        {name = "disable", from = {"normal", "pressed"}, to = "disabled"},
        {name = "enable",  from = {"disabled"}, to = "normal"},
        {name = "press",   from = "normal",  to = "pressed"},
        {name = "release", from = "pressed", to = "normal"},
    }, "normal", options)
    if type(images) ~= "table" then images = {normal = images} end
    self:setButtonImage(UIPushButton.NORMAL, images["normal"], true)
    self:setButtonImage(UIPushButton.PRESSED, images["pressed"], true)
    self:setButtonImage(UIPushButton.DISABLED, images["disabled"], true)

    self.args_ = {images, options}
end

function UIPushButton:setButtonImage(state, image, ignoreEmpty)
    assert(state == UIPushButton.NORMAL
        or state == UIPushButton.PRESSED
        or state == UIPushButton.DISABLED,
        string.format("UIPushButton:setButtonImage() - invalid state %s", tostring(state)))
    UIPushButton.super.setButtonImage(self, state, image, ignoreEmpty)

    if state == UIPushButton.NORMAL then
        if not self.images_[UIPushButton.PRESSED] then
            self.images_[UIPushButton.PRESSED] = image
        end
        if not self.images_[UIPushButton.DISABLED] then
            self.images_[UIPushButton.DISABLED] = image
        end
    end

    return self
end

function UIPushButton:onTouch_(event)
    local name, x, y = event.name, event.x, event.y
    if name == "began" then
        self.touchBeganX = x
        self.touchBeganY = y
        if not self:checkTouchInSprite_(x, y) then return false end
        self.fsm_:doEvent("press")
        self:dispatchEvent({name = UIButton.PRESSED_EVENT, x = x, y = y, touchInTarget = true})
        return true
    end

    -- must the begin point and current point in Button Sprite
    local touchInTarget = self:checkTouchInSprite_(self.touchBeganX, self.touchBeganY)
                        and self:checkTouchInSprite_(x, y)
    if name == "moved" then
        if touchInTarget and self.fsm_:canDoEvent("press") then
            self.fsm_:doEvent("press")
            self:dispatchEvent({name = UIButton.PRESSED_EVENT, x = x, y = y, touchInTarget = true})
        elseif not touchInTarget and self.fsm_:canDoEvent("release") then
            self.fsm_:doEvent("release")
            self:dispatchEvent({name = UIButton.RELEASE_EVENT, x = x, y = y, touchInTarget = false})
        end
    else
        if self.fsm_:canDoEvent("release") then
            self.fsm_:doEvent("release")
            self:dispatchEvent({name = UIButton.RELEASE_EVENT, x = x, y = y, touchInTarget = touchInTarget})
        end
        if name == "ended" and touchInTarget then
            self:dispatchEvent({name = UIButton.CLICKED_EVENT, x = x, y = y, touchInTarget = true})
        end
    end
end

function UIPushButton:createCloneInstance_()
    return UIPushButton.new(unpack(self.args_))
end

return UIPushButton
