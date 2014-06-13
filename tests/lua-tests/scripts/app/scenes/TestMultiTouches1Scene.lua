
import("..includes.functions")

local TestMultiTouches1Scene = class("TestMultiTouches1Scene", function()
    return display.newScene("TestMultiTouches1Scene")
end)

function TestMultiTouches1Scene:ctor()
    self.cursors = {}
    self.touchIndex = 0

    -- createTouchableSprite() 定义在 includes/functions.lua 中
    self.sprite = createTouchableSprite({
            image = "WhiteButton.png",
            size = CCSize(500, 600),
            label = "TOUCH ME !",
            labelColor = cc.c3(255, 0, 0)})
        :pos(display.cx, display.cy)
        :addTo(self)
    drawBoundingBox(self, self.sprite, cc.c4f(0, 1.0, 0, 1.0))

    local labelPoints = cc.ui.UILabel.new({text = "", size = 24})
        :align(display.CENTER_TOP, display.cx, display.top - 120)
        :addTo(self)

    -- 启用触摸
    self.sprite:setTouchEnabled(true)
    -- 设置触摸模式
    self.sprite:setTouchMode(cc.TOUCH_MODE_ALL_AT_ONCE) -- 多点
    -- self.sprite:setTouchMode(cc.TOUCH_MODE_ONE_BY_ONE) -- 单点（默认模式）
    -- 添加触摸事件处理函数
    self.sprite:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        -- event.name 是触摸事件的状态：began, moved, ended, cancelled
        -- event.x, event.y 是触摸点当前位置
        -- event.prevX, event.prevY 是触摸点之前的位置
        local str = {}
        for id, point in pairs(event.points) do
            str[#str + 1] = string.format("id: %s, x: %0.2f, y: %0.2f", point.id, point.x, point.y)
        end
        local pointsCount = #str
        table.sort(str)
        labelPoints:setString(table.concat(str, "\n"))

        if event.name == "began" then
            self.touchIndex = self.touchIndex + 1
            for id, point in pairs(event.points) do
                local cursor = display.newSprite("Cursor.png")
                    :pos(point.x, point.y)
                    :addTo(self)
                self.cursors[id] = cursor
            end
        elseif event.name == "moved" then
            for id, cursor in pairs(self.cursors) do
                local point = event.points[id]
                if point then
                    cursor:setOpacity(255)
                    cursor:setPosition(point.x, point.y)
                else
                    cursor:setOpacity(128)
                end
            end
        else
            for _, cursor in pairs(self.cursors) do
                cursor:removeSelf()
            end
            self.cursors = {}
        end

        local label = string.format("sprite: %s , count = %d, index = %d", event.name, pointsCount, self.touchIndex)
        self.sprite.label:setString(label)
        print(label)

        if event.name == "ended" or event.name == "cancelled" then
            print("")
        end

        -- 返回 true 表示要响应该触摸事件，并继续接收该触摸事件的状态变化
        return true
    end)

    --

    app:createNextButton(self)
    app:createTitle(self, "多点触摸测试 - 响应触摸事件")
end

return TestMultiTouches1Scene
