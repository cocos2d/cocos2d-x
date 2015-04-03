
local BugBase = class("BugBase")

BugBase.BUG_TYPE_ANT = "ANT"
BugBase.BUG_TYPE_SPIDER = "SPIDER"

function BugBase:ctor()
    self.position_ = cc.p(0, 0)
    self.rotation_ = 0
    self.type_ = nil
    self.dist_ = 0
    self.destination_ = cc.p(0, 0)
    self.speed_ = 1
    self.touchRange_ = 0
end

function BugBase:getType()
    return self.type_
end

function BugBase:getPosition()
    return self.position_
end

function BugBase:getRotation()
    return self.rotation_
end

function BugBase:getDist()
    return self.dist_
end

function BugBase:setDestination(destination)
    self.destination_ = clone(destination)
    self.dist_ = math.random(display.width / 2 + 100, display.width / 2 + 200)

    local rotation = math.random(0, 360)
    self.position_ = self:calcPosition(rotation, self.dist_, destination)
    self.rotation_ = rotation - 180
    return self
end

local fixedDeltaTime = 1.0 / 60.0
function BugBase:step(dt)
    self.dist_ = self.dist_ - self.speed_ * (dt / fixedDeltaTime)
    self.position_ = self:calcPosition(self.rotation_ + 180, self.dist_, self.destination_)
    return self
end

function BugBase:calcPosition(rotation, dist, destination)
    local radians = rotation * math.pi / 180
    return cc.p(destination.x + math.cos(radians) * dist,
                destination.y - math.sin(radians) * dist)
end

function BugBase:checkTouch(x, y)
    local dx, dy = x - self.position_.x, y - self.position_.y
    local offset = math.sqrt(dx * dx + dy * dy)
    return offset <= self.touchRange_
end

return BugBase
