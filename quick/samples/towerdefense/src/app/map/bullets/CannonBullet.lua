
local CurvedBulletBase = require("app.map.bullets.CurvedBulletBase")
local CannonBullet = class("CannonBullet", CurvedBulletBase)

function CannonBullet:ctor(source, target, delay, spriteName, params)
    if not params then
        params = {
            flyTime = math.random(70, 85) / 100,
            g       = -1000,
            delay   = delay or 0.2,
        }
    end

    self.boomSpriteScale_ = 1

    if not spriteName then spriteName = "#CannonBall01.png" end
    local sprite = display.newSprite(spriteName)
    sprite:setVisible(params.delay == 0)
    return CannonBullet.super.ctor(self, source, target, sprite, params)
end

function CannonBullet:fireBegan()
    CannonBullet.super.fireBegan(self)
    self.sprite_:setVisible(true)
end

function CannonBullet:hit()
    local framesName = self.boomFramesName_
    if not framesName then framesName = "CannonBoom%04d.png" end
    local framesLength = self.boomFramesLength_
    if not framesLength then framesLength = 15 end
    local framesTime = self.boomFramesTime_
    if not framesTime then framesTime = 0.8 end

    local frames    = display.newFrames(framesName, 1, framesLength)
    local boom      = display.newSprite(frames[1])
    local animation = display.newAnimation(frames, framesTime / framesLength)

    local x, y = self.sprite_:getPosition()
    boom:setPosition(x, y + 10)
    boom:setScale(math.random(100, 120) / 100 * self.boomSpriteScale_)
    boom:playAnimationOnce(animation, "removeWhenFinished")

    local parent = self.sprite_:getParent()
    parent:addChild(boom, self.sprite_:getLocalZOrder())
end

return CannonBullet
