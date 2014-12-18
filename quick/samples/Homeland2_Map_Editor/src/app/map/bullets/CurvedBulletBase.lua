
local math2d          = require("math2d")
local radians4point   = math2d.radians4point
local radians2degrees = math2d.radians2degrees
local degrees2radians = math2d.degrees2radians
local pointAtCircle   = math2d.pointAtCircle
local dist            = math2d.dist

local BulletBase = require("app.map.bullets.BulletBase")
local CurvedBulletBase = class("CurvedBulletBase", BulletBase)

function CurvedBulletBase:ctor(source, target, sprite, params)
    CurvedBulletBase.super.ctor(self, source, target, sprite, params.delay)
    self.flyTime_    = checknumber(params.flyTime)
    self.g_          = checknumber(params.g)
    self.isRotation_ = checkbool(params.isRotation)
end

function CurvedBulletBase:fireBegan()
    CurvedBulletBase.super.fireBegan(self)

    local target = self.target_
    local targetX, targetY
    if target:hasBehavior("MovableBehavior") and target:isMoving() then
        targetX, targetY = target:getFuturePosition(self.flyTime_ + self.delay_)
    else
        targetX, targetY = target.x_, target.y_
    end
    targetX = targetX + target.radiusOffsetX_ + target.hitOffsetX_
    targetY = targetY + target.radiusOffsetY_ + target.hitOffsetY_

    -- 子弹会落在目标中心点的一定范围内
    local radius = target.radius_
    local offset = radius * (math.random(0, 70) / 100)
    if math.random(1, 2) % 2 == 0 then
        targetX = targetX + offset
    else
        targetX = targetX - offset
    end

    offset = radius * (math.random(0, 70) / 100) * 0.7
    if math.random(1, 2) % 2 == 0 then
        targetY = targetY + offset * 0.5
    else
        targetY = targetY - offset * 0.5
    end

    self.targetX_    = targetX
    self.targetY_    = targetY
    self.timeOffset_ = self.delay_
    local ft = self.flyTime_

    self.offsetX_    = (self.targetX_ - self.startX_) / ft
    self.offsetY_    = ((self.targetY_ - self.startY_) - ((self.g_ * ft) * (ft / 2))) / ft

    self.sprite_:setPosition(self.startX_, self.startY_)
end

function CurvedBulletBase:tickBullet(dt)
    local time = self.time_ - self.timeOffset_

    local x = self.startX_ + time * self.offsetX_
    local y = self.startY_ + time * self.offsetY_ + self.g_ * time * time / 2
    self.sprite_:setPosition(x, y)

    if self.isRotation_ then
        local degrees = radians2degrees(radians4point(self.prevX_, self.prevY_, x, y))
        self.prevX_, self.prevY_ = x, y
        self.sprite_:setRotation(degrees)
    end

    if time >= self.flyTime_ then
        self.over_ = true
    end
end

return CurvedBulletBase
