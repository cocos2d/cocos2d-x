
local ObjectBase = require("app.map.ObjectBase")
local Range = class("Range", ObjectBase)

Range.DEFAULT_RADIUS = 80
Range.MIN_RADIUS     = 16
Range.MAX_RADIUS     = 500

function Range:ctor(id, state, map)
    Range.super.ctor(self, id, state, map)
    self.valid_            = true
    self.collisionEnabled_ = true
    self.radius_           = checkint(self.radius_)
    if self.radius_ <= 0 then
        self.radius_ = Range.DEFAULT_RADIUS
    end
end

--[[--

返回区域半径

]]
function Range:getRadius()
    return self.radius_
end

--[[--

设置区域半径

]]
function Range:setRadius(radius)
    if radius < Range.MIN_RADIUS then radius = Range.MIN_RADIUS end
    if radius > Range.MAX_RADIUS then radius = Range.MAX_RADIUS end
    self.radius_ = math.round(radius)
end

--[[--

导出 Range 对象的状态

]]
function Range:vardump()
    local state = Range.super.vardump(self)
    state.radius = self.radius_
    return state
end

return Range
