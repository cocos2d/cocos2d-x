
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
            size = cc.size(500, 600),
            label = "TOUCH ME !",
            labelColor = cc.c3b(255, 0, 0)})
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
        -- event.name 是触摸事件的状态：began, moved, ended, cancelled, added（仅限多点触摸）, removed（仅限多点触摸）
        -- event.points 包含所有触摸点，按照 events.point[id] = {x = ?, y = ?} 的结构组织
        local str = {}
        for id, point in pairs(event.points) do
            str[#str + 1] = string.format("id: %s, x: %0.2f, y: %0.2f", point.id, point.x, point.y)
        end
        local pointsCount = #str
        table.sort(str)
        labelPoints:setString(table.concat(str, "\n"))

        if event.name == "began" or event.name == "added" then
            self.touchIndex = self.touchIndex + 1
            for id, point in pairs(event.points) do
                local cursor = display.newSprite("Cursor.png")
                    :pos(point.x, point.y)
                    :scale(1.2)
                    :addTo(self)
                self.cursors[id] = cursor
            end
        elseif event.name == "moved" then
            for id, point in pairs(event.points) do
                local cursor = self.cursors[id]
                local rect = self.sprite:getBoundingBox()
                if cc.rectContainsPoint(rect, cc.p(point.x, point.y)) then
                    -- 检查触摸点的位置是否在矩形内
                    cursor:setPosition(point.x, point.y)
                    cursor:setVisible(true)
                else
                    cursor:setVisible(false)
                end
            end
        elseif event.name == "removed" then
            for id, point in pairs(event.points) do
                self.cursors[id]:removeSelf()
                self.cursors[id] = nil
            end
        else
            for _, cursor in pairs(self.cursors) do
                cursor:removeSelf()
            end
            self.cursors = {}
        end

        local label = string.format("sprite: %s , count = %d, index = %d", event.name, pointsCount, self.touchIndex)
        self.sprite.label:setString(label)

        if event.name == "ended" or event.name == "cancelled" then
            self.sprite.label:setString("")
            labelPoints:setString("")
        end

        -- 返回 true 表示要响应该触摸事件，并继续接收该触摸事件的状态变化
        return true
    end)

    cc.ui.UILabel.new({
        text = "注册多点触摸后，目标将收到所有触摸点的数据\nadded 和 removed 指示触摸点的加入和移除",
        size= 24})
        :align(display.CENTER, display.cx, display.top - 80)
        :addTo(self)

    --

    app:createNextButton(self)
    app:createTitle(self, "多点触摸测试 - 响应触摸事件")
end

return TestMultiTouches1Scene
