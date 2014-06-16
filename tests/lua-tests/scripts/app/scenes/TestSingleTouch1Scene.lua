
import("..includes.functions")

local TestSingleTouch1Scene = class("TestSingleTouch1Scene", function()
    return display.newScene("TestSingleTouch1Scene")
end)

function TestSingleTouch1Scene:ctor()
    -- createTouchableSprite() 定义在 includes/functions.lua 中
    self.sprite = createTouchableSprite({
            image = "WhiteButton.png",
            size = CCSize(500, 300),
            label = "TOUCH ME !",
            labelColor = cc.c3(255, 0, 0)})
        :pos(display.cx, display.cy)
        :addTo(self)
    drawBoundingBox(self, self.sprite, cc.c4f(0, 1.0, 0, 1.0))

    -- 启用触摸
    self.sprite:setTouchEnabled(true)
    -- 添加触摸事件处理函数
    self.sprite:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        -- event.name 是触摸事件的状态：began, moved, ended, cancelled
        -- event.x, event.y 是触摸点当前位置
        -- event.prevX, event.prevY 是触摸点之前的位置
        local label = string.format("sprite: %s x,y: %0.2f, %0.2f", event.name, event.x, event.y)
        self.sprite.label:setString(label)

        -- 返回 true 表示要响应该触摸事件，并继续接收该触摸事件的状态变化
        return true
    end)

    --

    app:createNextButton(self)
    app:createTitle(self, "单点触摸测试 - 响应触摸事件")
end

return TestSingleTouch1Scene
