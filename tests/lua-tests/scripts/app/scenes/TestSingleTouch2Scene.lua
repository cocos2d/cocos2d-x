
import("..includes.functions")

local TestSingleTouch2Scene = class("TestSingleTouch2Scene", function()
    return display.newScene("TestSingleTouch2Scene")
end)

function TestSingleTouch2Scene:ctor()
    -- parentButton 是 button1 的父节点
    self.parentButton = createTouchableSprite({
            image = "WhiteButton.png",
            size = CCSize(600, 500),
            label = "TOUCH ME !",
            labelColor = cc.c3(255, 0, 0)})
        :pos(display.cx, display.cy)
        :addTo(self)
    self.parentButton.name = "parentButton"
    drawBoundingBox(self, self.parentButton, cc.c4f(0, 1.0, 0, 1.0))
    self.parentButton:setTouchEnabled(true)
    self.parentButton:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        local label = string.format("parentButton: %s x,y: %0.2f, %0.2f", event.name, event.x, event.y)
        self.parentButton.label:setString(label)
        return true
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
            self.parentButton:setTouchCaptureEnabled(button:isButtonSelected())
        end)
        :pos(display.cx - 160, display.top - 80)
        :addTo(self)

    cc.ui.UILabel.new({
        text = "当不允许父对象捕获触摸事件时，\n父对象及其包含的所有子对象都将得不到触摸事件",
        size= 24})
        :align(display.CENTER, display.cx, display.top - 140)
        :addTo(self)

    --

    app:createNextButton(self)
    app:createTitle(self, "单点触摸测试 - 事件穿透和事件捕获")
end

return TestSingleTouch2Scene
