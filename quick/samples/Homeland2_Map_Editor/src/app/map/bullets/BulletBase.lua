
local math2d = require("math2d")
local BulletBase = class("BulletBase")

BulletBase.FLAG_NORMAL     = 0
BulletBase.FLAG_FROM_SKILL = 1

function BulletBase:ctor(source, target, sprite, delay)
    self.source_   = source
    self.target_   = target
    self.sprite_   = sprite
    self.delay_    = checknumber(delay)
    self.flag_     = 0

    self.damage_   = math.random(source.minDamage_, source.maxDamage_)
    self.damageScale_ = 1

    self.hit_      = math.random(100) <= source.hitrate_
    self.critical_ = math.random(100) <= source.critical_
    self.startX_   = source.x_ + source.radiusOffsetX_ + source.fireOffsetX_
    self.startY_   = source.y_ + source.radiusOffsetY_ + source.fireOffsetY_
    self.prevX_    = self.startX_
    self.prevY_    = self.startY_

    self.time_     = 0
    self.over_     = false
    self.isBegan_  = false
end

function BulletBase:setFlag(flag)
    self.flag_ = flag
end

function BulletBase:getView()
    return self.sprite_
end

function BulletBase:removeView()
    self.sprite_:removeSelf()
end

function BulletBase:tick(dt)
    if not self.isBegan_ then
        if self.delay_ <= 0 then
            self:fireBegan()
        else
            self.delay_ = self.delay_ - dt
            return
        end
    end

    self.time_ = self.time_ + dt
    self:tickBullet(dt)
end

function BulletBase:fireBegan()
    if self.source_.destroyed_ then
        self.time_    = 0
        self.over_    = true
        self.isBegan_ = false
        return
    end

    local source = self.source_
    self.startX_  = source.x_ + source.radiusOffsetX_ + source.fireOffsetX_
    self.startY_  = source.y_ + source.radiusOffsetY_ + source.fireOffsetY_
    self.prevX_   = self.startX_
    self.prevY_   = self.startY_
    self.isBegan_ = true
end

function BulletBase:tickBullet(dt)
end

function BulletBase:checkHit()
    if not self.hit_ then
        self:miss()
        return false
    end

    local target = self.target_
    if target and (target.collisionLock_ > 0 or not target.collisionEnabled_ or target.destroyed_) then
        self:miss()
        return false
    end

    local x, y = self.sprite_:getPosition()
    local targetX = target.x_ + target.radiusOffsetX_
    local targetY = target.y_ + target.radiusOffsetY_

    if math2d.dist(x, y, targetX, targetY) <= target.radius_ then
        self:hit()
        return true
    end

    self:miss()
    return false
end

function BulletBase:hit()
end

function BulletBase:miss()
end

function BulletBase:isOver()
    return self.over_
end

return BulletBase
