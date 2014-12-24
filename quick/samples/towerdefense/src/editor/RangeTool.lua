
local ToolBase = require("editor.ToolBase")
local RangeTool = class("RangeTool", ToolBase)

function RangeTool:ctor(toolbar, map)
    RangeTool.super.ctor(self, "RangeTool", toolbar, map)

    self.currentRange_ = nil
    self.drag_         = nil

    self.buttons = {
        {
            name          = "CreateRange",
            image         = "#CreateRangeButton.png",
            imageSelected = "#CreateRangeButtonSelected.png",
        },
        {
            name          = "SelectRange",
            image         = "#SelectRangeButton.png",
            imageSelected = "#SelectRangeButtonSelected.png",
        },
        {
            name          = "RemoveRange",
            image         = "#RemoveRangeButton.png",
            imageSelected = "#RemoveRangeButtonSelected.png",
        }
    }
end

function RangeTool:selected(selectedButtonName)
    RangeTool.super.selected(self, selectedButtonName)

    if selectedButtonName ~= "SelectRange" then
        self:setCurrentRange()
    end
end

function RangeTool:unselected()
    self:setCurrentRange()
end

function RangeTool:setCurrentRange(range)
    if self.currentRange_ and self.currentRange_ ~= range then
        self.currentRange_:setSelected(false)
        self.currentRange_:updateView()
    end
    self.currentRange_ = range
    self.currentRangeResize_ = nil
    if range then
        range:setSelected(true)
        range:updateView()
    end
end

function RangeTool:onTouchCreateRange(event, x, y)
    if event == "began" then
        local range = self.map_:newObject("range", {x = x, y = y})
        self:setCurrentRange(range)
        self.toolbar_:selectButton("RangeTool", 2)
        return true
    end
end

function RangeTool:onTouchSelectRange(event, x, y)
    if event == "began" then
        if self.currentRange_ and self.currentRange_:checkPointInHandler(x, y) then
            self.currentRangeResize_ = {lastX = x}
            return true
        end

        for id, range in pairs(self.map_:getObjectsByClassId("range")) do
            if range:checkPointIn(x, y) then
                self:setCurrentRange(range)
                local rangeX, rangeY = range:getPosition()
                self.drag_ = {
                    startX  = rangeX,
                    startY  = rangeY,
                    offsetX = rangeX - x,
                    offsetY = rangeY - y
                }
                return true
            end
        end

        return RangeTool.TOUCH_IGNORED

    elseif event == "moved" then
        if not self.currentRangeResize_ then
            local nx, ny = x + self.drag_.offsetX, y + self.drag_.offsetY
            self.currentRange_:setPosition(nx, ny)
            self.currentRange_:updateView()
        else
            local offset = x - self.currentRangeResize_.lastX
            self.currentRangeResize_.lastX = x
            self.currentRange_:setRadius(self.currentRange_:getRadius() + offset)
            self.currentRange_:updateView()
        end
    end
end

function RangeTool:onTouchRemoveRange(event, x, y)
    if event == "began" then
        for id, range in pairs(self.map_:getObjectsByClassId("range")) do
            if range:checkPointIn(x, y) then
                self:setCurrentRange()
                self.map_:removeObject(range)
                return false
            end
        end
        return RangeTool.TOUCH_IGNORED
    end
end

function RangeTool:onTouch(event, x, y)
    local x, y = self.map_:getCamera():convertToMapPosition(x, y)

    if self.selectedButtonName_ == "CreateRange" then
        return self:onTouchCreateRange(event, x, y)
    elseif self.selectedButtonName_ == "SelectRange" then
        return self:onTouchSelectRange(event, x, y)
    elseif self.selectedButtonName_ == "RemoveRange" then
        return self:onTouchRemoveRange(event, x, y)
    end
end

return RangeTool
