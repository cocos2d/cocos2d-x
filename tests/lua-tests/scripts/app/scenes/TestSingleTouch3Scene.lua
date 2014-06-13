
import("..includes.functions")

local TestSingleTouch3Scene = class("TestSingleTouch3Scene", function()
    return display.newScene("TestSingleTouch3Scene")
end)

function TestSingleTouch3Scene:ctor()
    -- 这个标志变量用于在触摸事件捕获阶段决定是否接受事件
    self.isTouchCaptureEnabled_ = true

    -- parentButton 是 button1 的父节点
    self.parentButton = createTouchableSprite({
            image = "WhiteButton.png",
            size = CCSize(600, 500),
            label = "TOUCH ME !",
            labelColor = cc.c3(255, 0, 0)})
        :pos(display.cx, display.cy)
        :addTo(self)
    drawBoundingBox(self, self.parentButton, cc.c4f(0, 1.0, 0, 1.0))

    self.parentButton.label2 = cc.ui.UILabel.new({text = "", size = 24, color = cc.c3(0, 0, 255)})
        :align(display.CENTER, 300, 60)
        :addTo(self.parentButton)

    self.parentButton:setTouchEnabled(true)
    self.parentButton:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        local label = string.format("parentButton: %s x,y: %0.2f, %0.2f", event.name, event.x, event.y)
        self.parentButton.label:setString(label)
        printf("%s %s [TARGETING]", "parentButton", event.name)
        if event.name == "ended" or event.name == "cancelled" then
            print("-----------------------------")
        else
            print("")
        end
        return true
    end)

    -- 可以动态捕获触摸事件，并在捕获触摸事件开始时决定是否接受此次事件
    self.parentButton:addNodeEventListener(cc.NODE_TOUCH_CAPTURE_EVENT, function(event)
        if event.name == "began" then
            print("-----------------------------")
        end

        local label = string.format("parentButton CAPTURE: %s x,y: %0.2f, %0.2f", event.name, event.x, event.y)
        self.parentButton.label2:setString(label)
        printf("%s %s [CAPTURING]", "parentButton", event.name)
        if event.name == "began" or event.name == "moved" then
            return self.isTouchCaptureEnabled_
        end
    end)

    -- button1 响应触摸后，会吞噬掉触摸事件
    self.button1 = createTouchableSprite({
            image = "GreenButton.png",
            size = CCSize(400, 160),
            label = "TOUCH ME !"})
        :pos(300, 400)
        :addTo(self.parentButton)
    cc.ui.UILabel.new({text = "SWALLOW = YES\n事件在当前对象处理后被吞噬", size = 24})
        :align(display.CENTER, 200, 90)
        :addTo(self.button1)
    drawBoundingBox(self, self.button1, cc.c4f(1.0, 0, 0, 1.0))

    self.button1:setTouchEnabled(true)
    self.button1:setTouchSwallowEnabled(true) -- 是否吞噬事件，默认值为 true
    self.button1:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        local label = string.format("button1: %s x,y: %0.2f, %0.2f", event.name, event.x, event.y)
        self.button1.label:setString(label)
        printf("%s %s [TARGETING]", "button1", event.name)
        if event.name == "ended" or event.name == "cancelled" then
            print("-----------------------------")
        else
            print("")
        end
        return true
    end)

    -- button2 响应触摸后，不会吞噬掉触摸事件
    self.button2 = createTouchableSprite({
            image = "PinkButton.png",
            size = CCSize(400, 160),
            label = "TOUCH ME !"})
        :pos(300, 200)
        :addTo(self.parentButton)
    cc.ui.UILabel.new({text = "SWALLOW = NO\n事件会传递到下层对象", size = 24})
        :align(display.CENTER, 200, 90)
        :addTo(self.button2)
    drawBoundingBox(self, self.button2, cc.c4f(0, 0, 1.0, 1.0))

    self.button2:setTouchEnabled(true)
    self.button2:setTouchSwallowEnabled(false) -- 当不吞噬事件时，触摸事件会从上层对象往下层对象传递，称为“穿透”
    self.button2:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        local label = string.format("button1: %s x,y: %0.2f, %0.2f", event.name, event.x, event.y)
        self.button2.label:setString(label)
        printf("%s %s [TARGETING]", "button2", event.name)
        return true
    end)

    -- 即便父对象在捕获阶段阻止响应事件，但子对象仍然可以捕获到事件，只是不会触发事件
    self.button2:addNodeEventListener(cc.NODE_TOUCH_CAPTURE_EVENT, function(event)
        printf("%s %s [CAPTURING]", "button2", event.name)
        return true
    end)

    -- 放置一个开关按钮在屏幕上
    local labels = {}
    labels[true] = "父对象【可以】捕获触摸事件"
    labels[false] = "父对象【不能】捕获触摸事件"
    local images = {on = "CheckBoxButton2On.png", off = "CheckBoxButton2Off.png"}
    self.captureEnabledButton = cc.ui.UICheckBoxButton.new(images)
        :setButtonLabel(cc.ui.UILabel.new({text = labels[true], size = 24}))
        :setButtonLabelOffset(40, 0)
        :setButtonSelected(true)
        :onButtonStateChanged(function(event)
            local button = event.target
            button:setButtonLabelString(labels[button:isButtonSelected()])
        end)
        :onButtonClicked(function(event)
            local button = event.target
            self.isTouchCaptureEnabled_ = button:isButtonSelected()
        end)
        :pos(display.cx - 160, display.top - 80)
        :addTo(self)

    cc.ui.UILabel.new({
        text = "事件处理流程：\n1. 【捕获】阶段：从父到子\n2. 【目标】阶段\n3. 【传递】阶段：尝试传递给下层对象",
        size= 24})
        :align(display.CENTER_TOP, display.cx, display.top - 120)
        :addTo(self)

    --

    app:createNextButton(self)
    app:createTitle(self, "单点触摸测试 - 在事件捕获阶段决定是否接受事件")
end

return TestSingleTouch3Scene
