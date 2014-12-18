
local EditorConstants = require("editor.EditorConstants")
local ToolBase = require("editor.ToolBase")
local PathTool = class("PathTool", ToolBase)

PathTool.LINK_CHECK_DIST = 12

function PathTool:ctor(toolbar, map)
    PathTool.super.ctor(self, "PathTool", toolbar, map)

    self.currentPath_       = nil
    self.currentPointIndex_ = nil
    self.currentPointLabel_ = nil
    self.link_              = nil

    self.buttons = {
        {
            name          = "CreatePath",
            image         = "#CreatePathButton.png",
            imageSelected = "#CreatePathButtonSelected.png",
        },
        {
            name          = "SelectPathPoint",
            image         = "#SelectPathPointButton.png",
            imageSelected = "#SelectPathPointButtonSelected.png",
        },
        {
            name          = "AddPathPoint",
            image         = "#AddPathPointButton.png",
            imageSelected = "#AddPathPointButtonSelected.png",
            imageDisabled = "#AddPathPointButtonDisabled.png",
        },
        {
            name          = "RemovePathPoint",
            image         = "#RemovePathPointButton.png",
            imageSelected = "#RemovePathPointButtonSelected.png",
            imageDisabled = "#RemovePathPointButtonDisabled.png",
        },
    }
end

function PathTool:selected(selectedButtonName)
    PathTool.super.selected(self, selectedButtonName)

    if selectedButtonName == "CreatePath" then
        self:setCurrentPath()
    end
    self:setMoreButtonsEnabled(self.currentPath_ ~= nil)
    if self.currentPointLabel_ then
        self.currentPointLabel_:setVisible(false)
    end
end

function PathTool:unselected()
    self:setMoreButtonsEnabled(false)
    self:setCurrentPath()
end

function PathTool:setMoreButtonsEnabled(isEnabled)
    self.buttons[3].sprite:setButtonEnabled(isEnabled)
    self.buttons[4].sprite:setButtonEnabled(isEnabled)
end

function PathTool:setCurrentPath(path, pointIndex)
    if self.currentPath_ and self.currentPath_ ~= path then
        self.currentPath_:setSelected(false)
        self.currentPath_:updateView()
        self:removePointLabel()
    end

    self.currentPath_ = path
    self.currentPointIndex_ = pointIndex
    if path then
        path:setSelected(true)
        path:updateView()
        local x, y = path:getPoint(pointIndex)
        self:showPointLabel(x + 10, y + 20, tostring(pointIndex))
    end
end

function PathTool:showPointLabel(x, y, text)
    if not self.currentPointLabel_ then
        self.currentPointLabel_ = cc.ui.UILabel.new({
            text         = "000",
            font         = EditorConstants.LABEL_FONT,
            size         = EditorConstants.LABEL_FONT_SIZE + 10,
            color        = cc.c3b(255, 0, 0),
            align        = cc.ui.TEXT_ALIGN_CENTER,
        }):align(display.CENTER)
        self.currentPointLabel_:enableOutline(cc.c4b(255, 255, 255, 255), 2)
        self.map_:getDebugLayer():addChild(self.currentPointLabel_, EditorConstants.LABEL_ZORDER)
    else
        self.currentPointLabel_:setVisible(true)
    end

    self.currentPointLabel_:setString(text)
    self.currentPointLabel_:setPosition(x, y)
end

function PathTool:removePointLabel()
    if self.currentPointLabel_ then
        self.currentPointLabel_:removeSelf()
        self.currentPointLabel_ = nil
    end
end

function PathTool:movePoint(x, y)
    self.currentPath_:movePoint(self.currentPointIndex_, x, y)
    self.currentPath_:updateView()
    self.currentPointLabel_:setPosition(x + 10, y + 20)
end

function PathTool:checkPointAtPath(x, y)
    for id, path in pairs(self.map_:getObjectsByClassId("path")) do
        local index = path:checkPointAtPoint(x, y, EditorConstants.CHECK_POINT_DIST)
        if index then return path, index end
    end
end

function PathTool:onTouch(event, x, y)
    local x, y = self.map_:getCamera():convertToMapPosition(x, y)
    if self.selectedButtonName_ == "CreatePath" then
        return self:onTouchCreatePath(event, x, y)
    elseif self.selectedButtonName_ == "AddPathPoint" then
        return self:onTouchAddPathPoint(event, x, y)
    elseif self.selectedButtonName_ == "SelectPathPoint" then
        return self:onTouchSelectPathPoint(event, x, y)
    elseif self.selectedButtonName_ == "RemovePathPoint" then
        return self:onTouchRemovePathPoint(event, x, y)
    end
end

function PathTool:onTouchCreatePath(event, x, y)
    if event == "began" then
        local state = {points = {{x, y}}}
        self:setCurrentPath(self.map_:newObject("path", state), 1)
        self:setMoreButtonsEnabled(true)
        self.toolbar_:selectButton("PathTool", 3) -- AddPathPoint
        return true
    end
end

function PathTool:onTouchAddPathPoint(event, x, y)
    if event == "began" then
        local index = self.currentPath_:checkPointAtPoint(x, y, EditorConstants.CHECK_POINT_DIST)
        if index then
            -- 如果点击已有的点，则移动这个点
            self:setCurrentPath(self.currentPath_, index)
        else
            local index = self.currentPath_:checkPointAtSegment(x, y, EditorConstants.CHECK_POINT_DIST)
            if index then
                -- 如果点击在路径上，则插入一个点
                self.currentPath_:insertPointAfterIndex(index, x, y)
                self:setCurrentPath(self.currentPath_, index + 1)
            else
                -- 否则追加一个点
                self.currentPath_:appendPoint(x, y)
                self:setCurrentPath(self.currentPath_, self.currentPath_:getPointsCount())
            end
            self.currentPath_:updateView()
        end

        return true

    elseif event == "moved" then
        self:movePoint(x, y)

    else
        self.currentPointIndex_ = nil
        if self.currentPointLabel_ then
            self.currentPointLabel_:setVisible(false)
        end

    end
end

function PathTool:onTouchSelectPathPoint(event, x, y)
    if event == "began" then
        -- 检查是否选中了某条路径上的点
        local path, index = self:checkPointAtPath(x, y)
        if path then
            local isDragBegin = self.currentPath_ == path
            self:setCurrentPath(path, index)
            self:setMoreButtonsEnabled(true)
            return isDragBegin
        end

        return PathTool.TOUCH_IGNORED

    elseif event == "moved" then
        self:movePoint(x, y)

    else
        self.currentPointIndex_ = nil
        if self.currentPointLabel_ then
            self.currentPointLabel_:setVisible(false)
        end

    end
end

function PathTool:onTouchRemovePathPoint(event, x, y)
    if event == "began" then
        local index = self.currentPath_:checkPointAtPoint(x, y, EditorConstants.CHECK_POINT_DIST)
        if index then
            -- 删除选中的点
            self.currentPath_:removePoint(index)
            if self.currentPath_:getPointsCount() < 1 then
                -- 如果路径上所有点都已经被删除，则删除该路径
                self.map_:removeObject(self.currentPath_)
                self:setCurrentPath()
                self.toolbar_:selectButton("PathTool", 2)
            else
                self.currentPath_:updateView()
            end

            return false
        end

        return PathTool.TOUCH_IGNORED
    end
end

return PathTool
