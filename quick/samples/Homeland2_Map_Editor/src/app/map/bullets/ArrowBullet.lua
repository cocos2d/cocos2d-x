
local CurvedBulletBase = require("app.map.bullets.CurvedBulletBase")
local ArrowBullet = class("ArrowBullet", CurvedBulletBase)

function ArrowBullet:ctor(source, target, delay)
    local params = {
        flyTime    = math.random(50, 65) / 100,
        g          = -1400,
        isRotation = true,
        delay      = delay or 0,
    }
    local sprite = display.newSprite("#Arrow01.png")
    sprite:setVisible(params.delay == 0)
    return ArrowBullet.super.ctor(self, source, target, sprite, params)
end

function ArrowBullet:fireBegan()
    ArrowBullet.super.fireBegan(self)
    self.sprite_:setVisible(true)
end

function ArrowBullet:hit()
    local arrow = display.newSprite("#BrokenArrow01.png")
    arrow.hideDelay_ = 2.4
    local rotation = self.sprite_:getRotation()
    local x, y = self.sprite_:getPosition()
    if rotation > 90 then
        rotation = rotation - math.random(10, 30)
    else
        rotation = rotation + math.random(10, 30)
    end
    arrow:setRotation(rotation)

    local target = self.target_
    local targetView = target:getView()
    targetView:addChild(arrow)

    local tx, ty = target.x_, target.y_
    local cw, ch = target.spriteSize_[1], target.spriteSize_[2]
    cw = cw / 2
    ch = ch / 2

    if target.flipSprite_ then
        x = tx - x + cw
    else
        x = x - tx + cw
    end
    arrow:setPosition(x, y - ty - target.offsetY_ + ch)

    transition.fadeOut(arrow, {
        time = 0.3,
        delay = math.random(50, 100) / 100,
        onComplete = function()
            if not tolua.isnull(arrow) then
                arrow:removeSelf()
            end
        end
    })
end

return ArrowBullet
