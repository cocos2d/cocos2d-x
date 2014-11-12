
local ScrollView = class("ScrollView", function(rect)
    if not rect then rect = cc.rect(0, 0, 0, 0) end
    local node = display.newClippingRegionNode(rect)
    node:setNodeEventEnabled(true)
    cc(node):addComponent("components.behavior.EventProtocol"):exportMethods()
    return node
end)

ScrollView.DIRECTION_VERTICAL   = 1
ScrollView.DIRECTION_HORIZONTAL = 2

function ScrollView:ctor(rect, direction)
    assert(direction == ScrollView.DIRECTION_VERTICAL or direction == ScrollView.DIRECTION_HORIZONTAL,
           "ScrollView:ctor() - invalid direction")

    self.dragThreshold = 40
    self.bouncThreshold = 140
    self.defaultAnimateTime = 0.4
    self.defaultAnimateEasing = "backOut"

    self.direction = direction
    self.touchRect = rect
    self.offsetX = 0
    self.offsetY = 0
    self.cells = {}
    self.currentIndex = 0

    self:addNodeEventListener(cc.NODE_EVENT, function(event)
        if event.name == "enter" then
            self:onEnter()
        elseif event.name == "exit" then
            self:onExit()
        end
    end)

    -- create container layer
    self.view = display.newLayer()
    self:addChild(self.view)

    self.view:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        return self:onTouch(event.name, event.x, event.y)
    end)
end

function ScrollView:getCurrentCell()
    if self.currentIndex > 0 then
        return self.cells[self.currentIndex]
    else
        return nil
    end
end

function ScrollView:getCurrentIndex()
    return self.currentIndex
end

function ScrollView:setCurrentIndex(index)
    self:scrollToCell(index)
end

function ScrollView:addCell(cell)
    self.view:addChild(cell)
    self.cells[#self.cells + 1] = cell
    self:reorderAllCells()
    self:dispatchEvent({name = "addCell", count = #self.cells})
end

function ScrollView:insertCellAtIndex(cell, index)
    self.view:addChild(cell)
    table.insert(self.cells, index, cell)
    self:reorderAllCells()
    self:dispatchEvent({name = "insertCellAtIndex", index = index, count = #self.cells})
end

function ScrollView:removeCellAtIndex(index)
    local cell = self.cells[index]
    cell:removeSelf()
    table.remove(self.cells, index)
    self:reorderAllCells()
    self:dispatchEvent({name = "removeCellAtIndex", index = index, count = #self.cells})
end

function ScrollView:getView()
    return self.view
end

function ScrollView:getTouchRect()
    return self.touchRect
end

function ScrollView:setTouchRect(rect)
    self.touchRect = rect
    self:dispatchEvent({name = "setTouchRect", rect = rect})
end

function ScrollView:getClippingRect()
    return self:getClippingRegion()
end

function ScrollView:setClippingRect(rect)
    self:setClippingRegion(rect)
    self:dispatchEvent({name = "setClippingRect", rect = rect})
end

function ScrollView:scrollToCell(index, animated, time, easing)
    local count = #self.cells
    if count < 1 then
        self.currentIndex = 0
        return
    end

    if index < 1 then
        index = 1
    elseif index > count then
        index = count
    end
    self.currentIndex = index

    local offset = 0
    for i = 2, index do
        local cell = self.cells[i - 1]
        local size = cell:getContentSize()
        if self.direction == ScrollView.DIRECTION_HORIZONTAL then
            offset = offset - size.width
        else
            offset = offset + size.height
        end
    end

    self:setContentOffset(offset, animated, time, easing)
    self:dispatchEvent({name = "scrollToCell", animated = animated, time = time, easing = easing})
end

function ScrollView:isTouchEnabled()
    return self.view:isTouchEnabled()
end

function ScrollView:setTouchEnabled(enabled)
    self.view:setTouchEnabled(enabled)
    -- self:setTouchEnabled(enabled)
    self:dispatchEvent({name = "setTouchEnabled", enabled = enabled})
end

---- events

function ScrollView:onTouchBegan(x, y)
    self.drag = {
        currentOffsetX = self.offsetX,
        currentOffsetY = self.offsetY,
        startX = x,
        startY = y,
        isTap = true,
    }

    local cell = self:getCurrentCell()
    cell:onTouch(event, x, y)

    return true
end

function ScrollView:onTouchMoved(x, y)
    local cell = self:getCurrentCell()
    if self.direction == ScrollView.DIRECTION_HORIZONTAL then
        if self.drag.isTap and math.abs(x - self.drag.startX) >= self.dragThreshold then
            self.drag.isTap = false
            cell:onTouch("cancelled", x, y)
        end

        if not self.drag.isTap then
            self:setContentOffset(x - self.drag.startX + self.drag.currentOffsetX)
        else
            cell:onTouch(event, x, y)
        end
    else
        if self.drag.isTap and math.abs(y - self.drag.startY) >= self.dragThreshold then
            self.drag.isTap = false
            cell:onTouch("cancelled", x, y)
        end

        if not self.drag.isTap then
            self:setContentOffset(y - self.drag.startY + self.drag.currentOffsetY)
        else
            cell:onTouch(event, x, y)
        end
    end
end

function ScrollView:onTouchEnded(x, y)
    if self.drag.isTap then
        self:onTouchEndedWithTap(x, y)
    else
        self:onTouchEndedWithoutTap(x, y)
    end
    self.drag = nil
end

function ScrollView:onTouchEndedWithTap(x, y)
    local cell = self:getCurrentCell()
    cell:onTouch(event, x, y)
    cell:onTap(x, y)
end

function ScrollView:onTouchEndedWithoutTap(x, y)
    error("ScrollView:onTouchEndedWithoutTap() - inherited class must override this method")
end

function ScrollView:onTouchCancelled(x, y)
    self.drag = nil
end

function ScrollView:onTouch(event, x, y)
    if self.currentIndex < 1 then return end

    if event == "began" then
        if not cc.rectContainsPoint(self.touchRect, cc.p(x, y)) then return false end
        return self:onTouchBegan(x, y)
    elseif event == "moved" then
        self:onTouchMoved(x, y)
    elseif event == "ended" then
        self:onTouchEnded(x, y)
    else -- cancelled
        self:onTouchCancelled(x, y)
    end
end

---- private methods

function ScrollView:reorderAllCells()
    local count = #self.cells
    local x, y = 0, 0
    local maxWidth, maxHeight = 0, 0
    for i = 1, count do
        local cell = self.cells[i]
        cell:setPosition(x, y)
        if self.direction == ScrollView.DIRECTION_HORIZONTAL then
            local width = cell:getContentSize().width
            if width > maxWidth then maxWidth = width end
            x = x + width
        else
            local height = cell:getContentSize().height
            if height > maxHeight then maxHeight = height end
            y = y - height
        end
    end

    if count > 0 then
        if self.currentIndex < 1 then
            self.currentIndex = 1
        elseif self.currentIndex > count then
            self.currentIndex = count
        end
    else
        self.currentIndex = 0
    end

    local size
    if self.direction == ScrollView.DIRECTION_HORIZONTAL then
        size = cc.size(x, maxHeight)
    else
        size = cc.size(maxWidth, math.abs(y))
    end
    self.view:setContentSize(size)
end

function ScrollView:setContentOffset(offset, animated, time, easing)
    local ox, oy = self.offsetX, self.offsetY
    local x, y = ox, oy
    if self.direction == ScrollView.DIRECTION_HORIZONTAL then
        self.offsetX = offset
        x = offset

        local maxX = self.bouncThreshold
        local minX = -self.view:getContentSize().width - self.bouncThreshold + self.touchRect.width
        if x > maxX then
            x = maxX
        elseif x < minX then
            x = minX
        end
    else
        self.offsetY = offset
        y = offset

        local maxY = self.view:getContentSize().height + self.bouncThreshold - self.touchRect.height
        local minY = -self.bouncThreshold
        if y > maxY then
            y = maxY
        elseif y < minY then
            y = minY
        end
    end

    if animated then
        transition.stopTarget(self.view)
        transition.moveTo(self.view, {
            x = x,
            y = y,
            time = time or self.defaultAnimateTime,
            easing = easing or self.defaultAnimateEasing,
        })
    else
        self.view:setPosition(x, y)
    end
end

function ScrollView:onExit()
    self:removeAllEventListeners()
end

return ScrollView
