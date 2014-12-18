
local StaticObjectsProperties = require("app.properties.StaticObjectsProperties")
local StaticObject            = require("app.map.StaticObject")
local MapConstants            = require("app.map.MapConstants")
local EditorConstants         = require("editor.EditorConstants")

local ToolBase = require("editor.ToolBase")
local ObjectTool = class("ObjectTool", ToolBase)

ObjectTool.TOOLBOX_PADDING     = 98
ObjectTool.TOOLBOX_ICON_SIZE   = 96
ObjectTool.TOOLBOX_MAX_COLUMNS = 8
ObjectTool.TOOLBOX_ZORDER      = 20000
ObjectTool.BREAK_BINDING_DIST  = 20

function ObjectTool:ctor(toolbar, map)
    ObjectTool.super.ctor(self, "ObjectTool", toolbar, map)

    self.currentObject_              = nil
    self.currentObjectBindingPathId_ = nil
    self.drag_                       = nil
    self.bindLabel_                  = nil

    self.buttons = {
        {
            name          = "CreateObject",
            image         = "#CreateObjectButton.png",
            imageSelected = "#CreateObjectButtonSelected.png",
        },
        {
            name          = "SelectObject",
            image         = "#SelectObjectButton.png",
            imageSelected = "#SelectObjectButtonSelected.png",
        },
        {
            name          = "RemoveObject",
            image         = "#RemoveObjectButton.png",
            imageSelected = "#RemoveObjectButtonSelected.png",
        },
        {
            name          = "BindObjectToPath",
            image         = "#BindObjectToPathButton.png",
            imageSelected = "#BindObjectToPathButtonSelected.png",
            imageDisabled = "#BindObjectToPathButtonDisabled.png",
        },
    }

    self.toolbar_:addEventListener("UPDATE_OBJECT", function(event)
        self:setMoreButtonsEnabled(true)
    end)
end

function ObjectTool:selected(selectedButtonName)
    ObjectTool.super.selected(self, selectedButtonName)

    if selectedButtonName == "BindObjectToPath" then
        self.currentObject_:updateView()
        self:createObjectBindingLabel("选择要绑定的路径点", "static")
    else
        self:removeObjectBindingLabel()
        if selectedButtonName == "CreateObject" or selectedButtonName == "RemoveObject" then
            self:setCurrentObject()
        end
    end
    self:removeToolbox()
end

function ObjectTool:unselected()
    self:setCurrentObject()
    self:removeToolbox()
end

function ObjectTool:setMoreButtonsEnabled(isEnabled)
    if isEnabled and self.currentObject_ and self.currentObject_:hasBehavior("MovableBehavior") then
        self.buttons[4].sprite:setButtonEnabled(true)
    else
        self.buttons[4].sprite:setButtonEnabled(false)
    end
end

function ObjectTool:removeToolbox()
    if self.toolbox_ then
        self.toolbox_:removeSelf()
        self.toolbox_ = nil
    end
end

function ObjectTool:setCurrentObject(object)
    if self.currentObject_ and self.currentObject_ ~= object then
        self.currentObject_:setSelected(false)
        self.currentObject_:updateView()
        self.toolbar_:dispatchEvent({name = "UNSELECT_OBJECT"})
    end

    self.currentObject_ = object
    self.currentObjectResize_ = nil
    if object then
        object:setSelected(true)
        object:updateView()
        self:setMoreButtonsEnabled(true)
        self.toolbar_:dispatchEvent({name = "SELECT_OBJECT", object = object})
    else
        self:setMoreButtonsEnabled(false)
    end
end

function ObjectTool:createObjectBindingLabel(text, isStaticLabel)
    self:removeObjectBindingLabel()

    local x, y = self.currentObject_:getPosition()
    local label = cc.ui.UILabel.new({
        text         = text,
        size         = 20,
        align        = cc.ui.TEXT_ALIGN_CENTER,
        color        = cc.c3b(255, 100, 100),
        x            = labelX,
        y            = labelY,
    }):align(display.CENTER)
    label:enableOutline(cc.c4b(255, 255, 255, 255), 2)
    label:setPosition(x, y + 100)
    self.map_:getDebugLayer():addChild(label, EditorConstants.BINDING_LABEL_ZORDER)

    if not isStaticLabel then
        transition.moveBy(label, {y = 10, time = 0.5})
        transition.fadeOut(label, {time = 0.5, delay = 1.7, onComplete = function()
            label:removeSelf()
        end})
    else
        self.bindLabel_ = label
    end
end

function ObjectTool:removeObjectBindingLabel()
    if self.bindLabel_ then
        self.bindLabel_:removeSelf()
        self.bindLabel_ = nil
    end
end

function ObjectTool:onTouchCreateObject(event, x, y)
    if event == "began" then
        if not self.toolbox_ then
            self:removeToolbox()
            self:showToolbox(x, y)
            return false
        else
            local object = self.toolbox_:checkPoint(x, y)
            if object then
                self:setCurrentObject(object)
                self:removeToolbox()
                self.toolbar_:selectButton("ObjectTool", 2)
                return false
            end
            return ObjectTool.TOUCH_IGNORED
        end
    end
end

function ObjectTool:onTouchSelectObject(event, x, y)
    if event == "began" then
        for id, object in pairs(self.map_:getAllObjects()) do
            local classId = object:getClassId()
            if (classId == "static" or classId == "entity") and object:checkPointIn(x, y) then
                local isDragBegin = self.currentObject_ == object
                self:setCurrentObject(object)

                self.currentObjectBindingPathId_ = nil
                if object:hasBehavior("MovableBehavior") then
                    self.currentObjectBindingPathId_ = object:getBindingPathId()
                end

                local objectX, objectY = object:getPosition()
                self.drag_ = {
                    startX  = objectX,
                    startY  = objectY,
                    offsetX = objectX - x,
                    offsetY = objectY - y
                }
                self.map_:setAllObjectsZOrder()

                return isDragBegin
            end
        end

        return ObjectTool.TOUCH_IGNORED

    elseif event == "moved" then
        local nx, ny = x + self.drag_.offsetX, y + self.drag_.offsetY
        if self.currentObject_:hasBehavior("MovableBehavior") and self.currentObjectBindingPathId_ then
            local path = self.map_:getObject(self.currentObjectBindingPathId_)
            local pointIndex = path:checkPointAtPoint(nx, ny, ObjectTool.BREAK_BINDING_DIST)
            if pointIndex then
                self.currentObject_:bindPath(path, pointIndex)
            else
                self.currentObject_:unbindPath()
                self.currentObject_:setPosition(nx, ny)
            end
        else
            self.currentObject_:setPosition(nx, ny)
        end

        self.currentObject_:updateView()
        self.map_:setAllObjectsZOrder()

    else
        self.toolbar_:dispatchEvent({name = "UPDATE_OBJECT", object = self.currentObject_})

        if self.currentObjectBindingPathId_ and not self.currentObject_:isBinding() then
            self:createObjectBindingLabel("对象已经解除绑定")
        end
        self.currentObjectBindingPathId_ = nil

    end
end

function ObjectTool:onTouchRemoveObject(event, x, y)
    if event == "began" then
        for id, object in pairs(self.map_:getAllObjects()) do
            local classId = object:getClassId()
            if (classId == "static" or classId == "entity") and object:checkPointIn(x, y) then
                self:setCurrentObject()
                self.map_:removeObject(object)
                return false
            end
        end
        return ObjectTool.TOUCH_IGNORED
    end
end

function ObjectTool:onTouchBindObjectToPath(event, x, y)
    if event == "began" then
        for id, path in pairs(self.map_:getObjectsByClassId("path")) do
            local index = path:checkPointAtPoint(x, y, EditorConstants.CHECK_POINT_DIST)
            if index then
                -- 连接对象到指定路径
                self.currentObject_:bindPath(path, index)
                self:setCurrentObject(self.currentObject_)

                self.toolbar_:selectButton("ObjectTool", 2)
                self:createObjectBindingLabel("对象已经绑定到路径")
                return false
            end
        end

        return ObjectTool.TOUCH_IGNORED
    end

end

function ObjectTool:onTouch(event, x, y)
    local x, y = self.map_:getCamera():convertToMapPosition(x, y)

    if self.selectedButtonName_ == "CreateObject" then
        return self:onTouchCreateObject(event, x, y)
    elseif self.selectedButtonName_ == "SelectObject" then
        return self:onTouchSelectObject(event, x, y)
    elseif self.selectedButtonName_ == "RemoveObject" then
        return self:onTouchRemoveObject(event, x, y)
    elseif self.selectedButtonName_ == "BindObjectToPath" then
        return self:onTouchBindObjectToPath(event, x, y)
    end
end

function ObjectTool:showToolbox(mapX, mapY)
    assert(self.toolbox_ == nil)
    local layer = display.newNode()
    layer:setPosition(mapX, mapY)

    local allIds = StaticObjectsProperties.getAllIds()
    local count = #allIds
    local maxColumns = math.ceil(math.sqrt(count))
    if maxColumns > ObjectTool.TOOLBOX_MAX_COLUMNS then
        maxColumns = ObjectTool.TOOLBOX_MAX_COLUMNS
    end
    local rows = math.ceil(count / maxColumns)
    local columns = maxColumns
    if count < maxColumns then columns = count end

    local x = -(columns / 2) * ObjectTool.TOOLBOX_PADDING + ObjectTool.TOOLBOX_PADDING / 2
    local y = (rows / 2) * ObjectTool.TOOLBOX_PADDING - ObjectTool.TOOLBOX_PADDING / 2
    local width, height = self.map_:getSize()

    local minX = ObjectTool.TOOLBOX_PADDING / 2
    if mapX + x < minX then x = minX - mapX end

    local maxX = width - (columns - 0.5) * ObjectTool.TOOLBOX_PADDING
    if mapX + x > maxX then x = maxX - mapX end

    local minY = (rows - 0.5) * ObjectTool.TOOLBOX_PADDING
    if mapY + y < minY then y = minY - mapY  end

    local maxY = height - ObjectTool.TOOLBOX_PADDING / 2
    if mapY + y > maxY then y = maxY - mapY end

    local left = mapX + x - ObjectTool.TOOLBOX_PADDING / 2
    local top = mapY + y + ObjectTool.TOOLBOX_PADDING / 2

    local bgWidth = columns * ObjectTool.TOOLBOX_PADDING + 4
    local bgHeight = rows * ObjectTool.TOOLBOX_PADDING + 4
    local rect = utils.drawRect(
                    cc.rect(x - ObjectTool.TOOLBOX_PADDING / 2 - 2,
                        y - bgHeight + ObjectTool.TOOLBOX_PADDING / 2 + 2,
                        bgWidth,
                        bgHeight),
                    {fillColor = cc.c4f(1,1,1,80/255),
                    borderColor = cc.c4f(0.5,0.5,0.5,80/255)})
    -- rect:setFill(true)
    -- rect:setLineColor(cc.c4fFromc4b(cc.c4b(120, 120, 120, 80)))
    -- rect:setOpacity(80)
    -- rect:setPosition(x + bgWidth / 2 - ObjectTool.TOOLBOX_PADDING / 2 - 2,
    --                  y - bgHeight / 2 + ObjectTool.TOOLBOX_PADDING / 2 + 2)
    layer:addChild(rect)

    local col = 0
    for i, id in ipairs(allIds) do
        local define = StaticObjectsProperties.get(id)
        local sprite
        if define.framesName then
            sprite = display.newSprite("#" .. string.format(define.framesName, define.framesBegin))
        else
            local imageName = define.imageName
            if type(imageName) == "table" then
                imageName = imageName[1]
            end
            sprite = display.newSprite(imageName)
        end
        local size   = sprite:getContentSize()
        local scale  = 1
        if size.width > ObjectTool.TOOLBOX_ICON_SIZE then
            scale = ObjectTool.TOOLBOX_ICON_SIZE / size.width
        end

        if size.height * scale > ObjectTool.TOOLBOX_ICON_SIZE then
            scale = ObjectTool.TOOLBOX_ICON_SIZE / size.height
        end
        sprite:setScale(scale)

        local rect = utils.drawRect(
                    cc.rect(x - ObjectTool.TOOLBOX_ICON_SIZE/2,
                        y - ObjectTool.TOOLBOX_ICON_SIZE/2,
                        ObjectTool.TOOLBOX_ICON_SIZE,
                        ObjectTool.TOOLBOX_ICON_SIZE),
                    {fillColor = cc.c4f(1,1,1,70/255),
                    borderColor = cc.c4f(32/255, 32/255, 32/255, 120/255)})
        -- rect:setFill(true)
        -- rect:setLineColor(cc.c4fFromc4b(cc.c4b(32, 32, 32, 120)))
        -- rect:setOpacity(70)
        -- rect:setPosition(x, y)
        layer:addChild(rect)

        layer:addChild(sprite)
        sprite:setPosition(x, y)

        col = col + 1
        if col >= columns then
            x = x - ObjectTool.TOOLBOX_PADDING * (columns - 1)
            y = y - ObjectTool.TOOLBOX_PADDING
            col = 0
        else
            x = x + ObjectTool.TOOLBOX_PADDING
        end
    end

    local map = self.map_
    function layer:checkPoint(x, y)
        local col = math.floor((x - left) / ObjectTool.TOOLBOX_PADDING) + 1
        local row = math.floor((top - y) / ObjectTool.TOOLBOX_PADDING) + 1
        if col < 1 or col > columns or row < 1 or row > rows then
            return
        end

        local index = (row - 1) * columns + col
        if not allIds[index] then return end

        local defineId = allIds[index]
        local define = StaticObjectsProperties.get(defineId)
        local state = {x = mapX, y = mapY, defineId = defineId}
        local object = map:newObject(define.classId, state)
        map:setAllObjectsZOrder()
        return object
    end

    self.toolbox_ = layer
    self.map_:getMarksLayer():addChild(self.toolbox_, ObjectTool.TOOLBOX_ZORDER)
end

return ObjectTool
