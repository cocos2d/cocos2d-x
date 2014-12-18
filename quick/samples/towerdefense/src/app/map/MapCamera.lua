
local math2d = require("math2d")
local MapConstants = require("app.map.MapConstants")

local MapCamera = class("MapCamera")

function MapCamera:ctor(map)
    self.map_           = map

    self.zooming_       = false
    self.scale_         = 1
    self.actualScale_   = 1
    self.offsetX_       = 0
    self.offsetY_       = 0
    self.offsetLimit_   = nil
    self.margin_        = {top = 0, right = 0, bottom = 0, left = 0}

    local width, height = map:getSize()
    local minScaleV     = display.height / height
    local minScaleH     = display.width / width
    local minScale      = minScaleV

    if minScaleH > minScale then minScale = minScaleH end
    self.minScale_ = minScale
end

--[[--

返回地图的边空

]]
function MapCamera:getMargin()
    return clone(self.margin_)
end

--[[--

设置地图卷动的边空

]]
function MapCamera:setMargin(top, right, bottom, left)
    if self.zooming_ then return end

    if type(top)    == "number" then self.margin_.top = top end
    if type(right)  == "number" then self.margin_.right = right end
    if type(bottom) == "number" then self.margin_.bottom = bottom end
    if type(left)   == "number" then self.margin_.left = left end
    self:resetOffsetLimit()
end

--[[--

返回地图当前的缩放比例

]]
function MapCamera:getScale()
    return self.scale_
end

--[[--

设置地图当前的缩放比例

]]
function MapCamera:setScale(scale)
    if self.zooming_ then return end

    self.scale_ = scale
    if scale < self.minScale_ then scale = self.minScale_ end
    self.actualScale_ = scale
    self:resetOffsetLimit()
    self:setOffset(self.offsetX_, self.offsetY_)

    local backgroundLayer = self.map_:getBackgroundLayer()
    local batchLayer      = self.map_:getBatchLayer()
    local marksLayer      = self.map_:getMarksLayer()
    local debugLayer      = self.map_:getDebugLayer()

    backgroundLayer:setScale(scale)
    batchLayer:setScale(scale)
    marksLayer:setScale(scale)
    if debugLayer then debugLayer:setScale(scale) end
end

--[[--

动态调整摄像机的缩放比例

]]
function MapCamera:zoomTo(scale, x, y)
    self.zooming_ = true
    self.scale_ = scale
    if scale < self.minScale_ then scale = self.minScale_ end
    self.actualScale_ = scale
    self:resetOffsetLimit()

    local backgroundLayer = self.map_:getBackgroundLayer()
    local batchLayer      = self.map_:getBatchLayer()
    local marksLayer      = self.map_:getMarksLayer()
    local debugLayer      = self.map_:getDebugLayer()

    transition.removeAction(self.backgroundLayerAction_)
    transition.removeAction(self.batchLayerAction_)
    transition.removeAction(self.marksLayerAction_)
    if debugLayer then
        transition.stopTarget(debugLayer)
    end

    self.backgroundLayerAction_ = transition.scaleTo(backgroundLayer, {scale = scale, time = MapConstants.ZOOM_TIME})
    self.batchLayerAction_ = transition.scaleTo(batchLayer, {scale = scale, time = MapConstants.ZOOM_TIME})
    self.marksLayerAction_ = transition.scaleTo(marksLayer, {scale = scale, time = MapConstants.ZOOM_TIME})
    if debugLayer then
        transition.scaleTo(debugLayer, {scale = scale, time = MapConstants.ZOOM_TIME})
    end

    if type(x) ~= "number" then return end

    if x < self.offsetLimit_.minX then
        x = self.offsetLimit_.minX
    end
    if x > self.offsetLimit_.maxX then
        x = self.offsetLimit_.maxX
    end
    if y < self.offsetLimit_.minY then
        y = self.offsetLimit_.minY
    end
    if y > self.offsetLimit_.maxY then
        y = self.offsetLimit_.maxY
    end

    self.offsetX_, self.offsetY_ = x, y

    transition.moveTo(backgroundLayer, {
        x = x,
        y = y,
        time = MapConstants.ZOOM_TIME,
        onComplete = function()
            self.zooming_ = false
        end
    })
    transition.moveTo(batchLayer, {x = x, y = y, time = MapConstants.ZOOM_TIME})
    transition.moveTo(marksLayer, {x = x, y = y, time = MapConstants.ZOOM_TIME})
    if debugLayer then
        transition.moveTo(debugLayer, {x = x, y = y, time = MapConstants.ZOOM_TIME})
    end
end

--[[--

返回地图当前的卷动偏移量

]]
function MapCamera:getOffset()
    return self.offsetX_, self.offsetY_
end

--[[--

设置地图卷动的偏移量

]]
function MapCamera:setOffset(x, y, movingSpeed, onComplete)
    if self.zooming_ then return end

    if x < self.offsetLimit_.minX then
        x = self.offsetLimit_.minX
    end
    if x > self.offsetLimit_.maxX then
        x = self.offsetLimit_.maxX
    end
    if y < self.offsetLimit_.minY then
        y = self.offsetLimit_.minY
    end
    if y > self.offsetLimit_.maxY then
        y = self.offsetLimit_.maxY
    end

    self.offsetX_, self.offsetY_ = x, y

    if type(movingSpeed) == "number" and movingSpeed > 0 then
        transition.stopTarget(self.bgSprite_)
        transition.stopTarget(self.batch_)
        transition.stopTarget(self.marksLayer_)
        if self.debugLayer_ then
            transition.stopTarget(self.debugLayer_)
        end

        local cx, cy = self.bgSprite_:getPosition()
        local mtx = cx / movingSpeed
        local mty = cy / movingSpeed
        local movingTime
        if mtx > mty then
            movingTime = mtx
        else
            movingTime = mty
        end

        transition.moveTo(self.bgSprite_, {
            x = x,
            y = y,
            time = movingTime,
            onComplete = onComplete
        })
        transition.moveTo(self.batch_, {x = x, y = y, time = movingTime})
        transition.moveTo(self.marksLayer_, {x = x, y = y, time = movingTime})
        if self.debugLayer_ then
            transition.moveTo(self.debugLayer_, {x = x, y = y, time = movingTime})
        end
    else
        self.map_:getBackgroundLayer():setPosition(x, y)
        self.map_:getBatchLayer():setPosition(x, y)
        self.map_:getMarksLayer():setPosition(x, y)
        local debugLayer = self.map_:getDebugLayer()
        if debugLayer then debugLayer:setPosition(x, y) end
    end
end

--[[--

移动指定的偏移量

]]
function MapCamera:moveOffset(offsetX, offsetY)
    self:setOffset(self.offsetX_ + offsetX, self.offsetY_ + offsetY)
end

--[[--

返回地图的卷动限制

]]
function MapCamera:getOffsetLimit()
    return clone(self.offsetLimit_)
end

--[[--

更新地图的卷动限制

]]
function MapCamera:resetOffsetLimit()
    local mapWidth, mapHeight = self.map_:getSize()
    self.offsetLimit_ = {
        minX = display.width - self.margin_.right - mapWidth * self.actualScale_,
        maxX = self.margin_.left,
        minY = display.height - self.margin_.top - mapHeight * self.actualScale_,
        maxY = self.margin_.bottom,
    }
end

--[[--

将屏幕坐标转换为地图坐标

]]
function MapCamera:convertToMapPosition(x, y)
    return (x - self.offsetX_) / self.actualScale_, (y - self.offsetY_) / self.actualScale_
end

--[[--

将地图坐标转换为屏幕坐标

]]
function MapCamera:convertToWorldPosition(x, y)
    return x * self.actualScale_ + self.offsetX_, y * self.actualScale_ + self.offsetY_
end

--[[--

将指定的地图坐标转换为摄像机坐标

]]
function MapCamera:convertToCameraPosition(x, y)
    local left = -(x - (display.width - self.margin_.left - self.margin_.right) / 2)
    local bottom = -(y - (display.height - self.margin_.top - self.margin_.bottom) / 2)
    return left, bottom
end

return MapCamera
