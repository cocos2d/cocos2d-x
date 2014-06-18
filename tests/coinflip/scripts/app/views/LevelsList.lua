
local LevelsListCell = import(".LevelsListCell")
local Levels = import("..data.Levels")

local PageControl = import("..ui.PageControl")
local LevelsList = class("LevelsList", PageControl)

LevelsList.INDICATOR_MARGIN = 46

function LevelsList:ctor(rect)
    LevelsList.super.ctor(self, rect, PageControl.DIRECTION_HORIZONTAL)

    -- add cells
    local rows, cols = 4, 4
    if display.height > 1000 then rows = rows + 1 end

    local numPages = math.ceil(Levels.numLevels() / (rows * cols))
    local levelIndex = 1

    for pageIndex = 1, numPages do
        local endLevelIndex = levelIndex + (rows * cols) - 1
        if endLevelIndex > Levels.numLevels() then
            endLevelIndex = Levels.numLevels()
        end
        local cell = LevelsListCell.new(cc.size(display.width, rect.height), levelIndex, endLevelIndex, rows, cols)
        cell:addEventListener("onTapLevelIcon", function(event) return self:onTapLevelIcon(event) end)
        self:addCell(cell)
        levelIndex = endLevelIndex + 1
    end

    -- add indicators
    local x = (self:getClippingRect().width - LevelsList.INDICATOR_MARGIN * (numPages - 1)) / 2
    local y = self:getClippingRect().y + 20

    self.indicator_ = display.newSprite("#LevelListsCellSelected.png")
    self.indicator_:setPosition(x, y)
    self.indicator_.firstX_ = x

    for pageIndex = 1, numPages do
        local icon = display.newSprite("#LevelListsCellIndicator.png")
        icon:setPosition(x, y)
        self:addChild(icon)
        x = x + LevelsList.INDICATOR_MARGIN
    end

    self:addChild(self.indicator_)
end

function LevelsList:scrollToCell(index, animated, time)
    LevelsList.super.scrollToCell(self, index, animated, time)

    transition.stopTarget(self.indicator_)
    local x = self.indicator_.firstX_ + (self:getCurrentIndex() - 1) * LevelsList.INDICATOR_MARGIN
    if animated then
        time = time or self.defaultAnimateTime
        transition.moveTo(self.indicator_, {x = x, time = time / 2})
    else
        self.indicator_:setPositionX(x)
    end
end

function LevelsList:onTapLevelIcon(event)
    self:dispatchEvent({name = "onTapLevelIcon", levelIndex = event.levelIndex})
end

return LevelsList
